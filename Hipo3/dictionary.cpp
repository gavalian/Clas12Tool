/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "dictionary.h"
#include "utils.h"
#include <stdlib.h>

namespace hipo {

  int   schema::getType( const char* entry){
    if(schemaEntries.count(entry)==0){
      printf("schema:: error, schema %s does no contain entry %s\n",
          schemaName.c_str(), entry);
    }
    return schemaEntries[entry].second;
  }

  int   schema::getMaxStringLength(){
    int length = 0;
    for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
         it!=schemaEntries.end(); ++it){
           if(it->first.size() > length) length = it->first.size();
    }
    return length;
  }

  std::vector<std::string> schema::getEntryList(){
       std::vector<std::string> entries;
       /*
       for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
            it!=schemaEntries.end(); ++it){
              entries.push_back(it->first);
       }*/
       for(int i = 0; i < entryNames.size(); i++){
          entries.push_back(entryNames[i]);
       }
       return entries;
  }

  int   schema::getItem(  const char* entry){
    if(schemaEntries.count(entry)==0){
      printf("schema:: error, schema %s does no contain entry %s\n",
          schemaName.c_str(), entry);
    }
    return schemaEntries[entry].first;
  }

  int   schema::getTypeByString(const char *typestring){
    std::string type = typestring;
    if(type.compare("BYTE")==0){
      return 1;
    } else if(type.compare("SHORT")==0){
      return 2;
    } else if(type.compare("INT")==0){
      return 3;
    } else if(type.compare("FLOAT")==0){
      return 4;
    } else if(type.compare("DOUBLE")==0){
      return 5;
    } else if(type.compare("LONG")==0){
      return 8;
    }
    return 0;
  }

  std::string schema::getTypeStringSimple(int type){
    std::string typeString = "unknown";
    switch(type){
      case 1: typeString = "int8_t"  ; break;
      case 2: typeString = "int16_t" ; break;
      case 3: typeString = "int32_t" ; break;
      case 4: typeString = "float"    ; break;
      case 5: typeString = "double"   ; break;
      case 8: typeString = "int64_t" ; break;
      default: break;
    }
    return typeString;
  }

  std::string schema::getTypeString(int type){
    std::string typeString = "<unknown>";
    switch(type){
      case 1: typeString = "<int8_t>"  ; break;
      case 2: typeString = "<int16_t>" ; break;
      case 3: typeString = "<int32_t>" ; break;
      case 4: typeString = "<float>"    ; break;
      case 5: typeString = "<double>"   ; break;
      case 8: typeString = "<int64_t>" ; break;
      default: break;
    }
    return typeString;
  }
  std::string schema::getBranchVariable(const char *var, int max){
       std::string c_var = var;
       while(c_var.size()<max){
         c_var.insert(0," ");
       }
       std::string::size_type pos = c_var.find_first_of(":", 0);
       while(std::string::npos != pos){
         c_var.replace(pos,1,"_");
         pos = c_var.find_first_of(":", 0);
       }
       return c_var;
  }
  std::string  schema::getRootTypeString(int type){
    std::string typeString = "unknown";
    switch(type){
      case 1: typeString = "Char_t"  ; break;
      case 2: typeString = "Short_t" ; break;
      case 3: typeString = "Int_t" ; break;
      case 4: typeString = "Float_t"    ; break;
      case 5: typeString = "Double_t"   ; break;
      case 8: typeString = "Long64_t" ; break;
      default: break;
    }
    return typeString;
  }
  std::vector<std::string>  schema::getRootBranchesCode(){
     std::vector<std::string> code;
     char c_type[128];
     char c_name[128];
     char c_line[128];
     std::string scname = getName();
     int maxLength = getMaxStringLength();
     std::string  format;

     for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
     it!=schemaEntries.end(); ++it){
       std::string type = getTypeString(it->second.second);

       sprintf(c_type,"%-12s",type.c_str());

       //node.append("  *");
       sprintf(c_name,"*%s_%s",scname.c_str(), it->first.c_str());
       std::string branch = getBranchVariable(c_name,scname.size());
       std::string node("   hipo::node");
       node.append(c_type);
       node.append(branch);
       node.append(";");
       sprintf(c_name,"%s_%s",scname.c_str(), it->first.c_str());
       branch = getBranchVariable(c_name,scname.size());
       std::string rootType = getRootTypeString(it->second.second);
       sprintf(c_line,"   std::vector<%s>   vec_%s;",
        rootType.c_str(),branch.c_str());
       //node.append(c_line);
       code.push_back(node);
       code.push_back(c_line);
     }

     sprintf(c_name,"   if(dictionary->hasSchema(\"%s\")==true){",scname.c_str());
     code.push_back(c_name);
     for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
     it!=schemaEntries.end(); ++it){

       std::string type = getTypeString(it->second.second);
       sprintf(c_type,"%-12s",type.c_str());

         sprintf(c_name,"      if(dictionary->hasEntry(\"%s\",\"%s\")==true){",
         scname.c_str(),it->first.c_str());
         code.push_back(c_name);
         sprintf(c_name,"%s_%s",scname.c_str(), it->first.c_str());
         std::string branch = getBranchVariable(c_name,scname.size());
         sprintf(c_line,"         %s = reader.getBranch%s(\"%s\",\"%s\");",
              branch.c_str(),c_type,getName().c_str(),it->first.c_str());
         code.push_back(c_line);

         sprintf(c_line,"         tree->Branch(\"%s\",&vec_%s);",
                branch.c_str(),branch.c_str());
         code.push_back(c_line);
         code.push_back(std::string("      }"));
     }

     code.push_back(std::string("   }"));
     return code;
  }
  std::vector<std::string>  schema::getRootFillCode(){
    std::vector<std::string> code;
    char c_type[128];
    char c_name[128];
    char c_line[128];
    std::string scname = getName();
    int maxLength = getMaxStringLength();
    std::string  format;
    sprintf(c_name,"   if(dictionary->hasSchema(\"%s\")==true){",scname.c_str());
    code.push_back(c_name);
    for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
    it!=schemaEntries.end(); ++it){

      std::string type = getTypeStringSimple(it->second.second);
      sprintf(c_type,"%-12s",type.c_str());

        sprintf(c_name,"      if(dictionary->hasEntry(\"%s\",\"%s\")==true){",
        scname.c_str(),it->first.c_str());
        code.push_back(c_name);
        sprintf(c_name,"%s_%s",scname.c_str(), it->first.c_str());
        std::string branch = getBranchVariable(c_name,scname.size());

        sprintf(c_line,"         int nsize = %s->getLength();",branch.c_str());
        code.push_back(c_line);
        sprintf(c_line,"         vec_%s.clear();",branch.c_str());
        code.push_back(c_line);
        sprintf(c_line,"         vec_%s.resize(nsize);",branch.c_str());
        code.push_back(c_line);
        sprintf(c_line,"         memcpy(&vec_%s[0],%s->getAddress(),nsize*sizeof(%s));",
              branch.c_str(),branch.c_str(),type.c_str());

        code.push_back(c_line);

        code.push_back(std::string("      }"));
    }
    code.push_back(std::string("   }"));
    return code;
  }


  std::vector<std::string> schema::branchesAccessCode(){

    std::vector<std::string> code;
    std::string scname = getName();
    int maxLength = getMaxStringLength();
    char c_type[128];
    char c_name[128];
    std::string  format;

    for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
         it!=schemaEntries.end(); ++it){
           std::string type = getTypeString(it->second.second);
           sprintf(c_type,"%-12s",type.c_str());
           //node.append(c_type);
           //node.append("  *");
           sprintf(c_name,"%s_%s",scname.c_str(), it->first.c_str());
           std::string branch = getBranchVariable(c_name,scname.size());

           std::string node("      int n_");
           node.append(branch.c_str());
           node.append(" = ");
           node.append(branch.c_str());
           node.append("->getLength();\n");
           node.append("      for(int b = 0; b < n_");
           node.append(branch.c_str());
           node.append("; b++){\n");
           node.append("         std::cout << ");
           node.append(branch.c_str());
           node.append("->getValue(b)");
           node.append(" << \" \" ;\n ");
           node.append("      }\n");
           node.append("      std::cout << std::endl;\n");
           code.push_back(node);
           //std::cout << it->first << " => " << it->second << '\n';
    }
    return code;
  }

  std::vector<std::string> schema::branchesCode(){
    std::vector<std::string> code;
    std::string scname = getName();
    int maxLength = getMaxStringLength();
    char c_type[128];
    char c_name[128];
    std::string  format;

    for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
         it!=schemaEntries.end(); ++it){
           std::string type = getTypeString(it->second.second);
           std::string node("   hipo::node");
           sprintf(c_type,"%-12s",type.c_str());
           node.append(c_type);
           //node.append("  *");
           sprintf(c_name,"*%s_%s",scname.c_str(), it->first.c_str());
           std::string branch = getBranchVariable(c_name,maxLength+scname.size()+2);
           /*node.append(scname);
           node.append("_");
           node.append(it->first);*/
           node.append(branch.c_str());
           node.append(" = reader.getBranch");
           node.append(type.c_str());
           node.append("(\"");
           node.append(scname);
           node.append("\",\"");
           node.append(it->first);
           node.append("\");");
           code.push_back(node);
           //std::cout << it->first << " => " << it->second << '\n';
    }
    return code;
  }

  void schema::ls(){
    for (std::map<std::string, std::pair<int,int> >::iterator it=schemaEntries.begin();
         it!=schemaEntries.end(); ++it){
           printf("\tentry %-25s : item = %8d , type = %4d \n",it->first.c_str(), it->second.first,
           it->second.second);
         }
  }

  /**
   * Dictionary class
   */
  void dictionary::ls(int mode){
    for (std::map<std::string, hipo::schema>::iterator it=mapDict.begin();
         it!=mapDict.end(); ++it){
           printf("Schema %-25s : %9d \n",it->first.c_str(), it->second.getGroup());
           if(mode>0){
             it->second.ls();
           }
         }
  }

bool   dictionary::hasEntry(const char* name, const char* entry)
{
  if(mapDict.count(name)==0) return false;
  return mapDict[name].hasEntry(entry);
}
  std::vector<std::string> dictionary::getSchemaList(){
    std::vector<std::string> list;
    for (std::map<std::string, hipo::schema>::iterator it=mapDict.begin();
         it!=mapDict.end(); ++it){
           list.push_back(it->first);
    }
    return list;
  }

  void dictionary::parse(std::string dictString){
    std::vector<std::string> tokens;
    std::string schemahead = hipo::utils::substring(dictString,"{","}",0);
     hipo::utils::tokenize(schemahead, tokens, ",");
     hipo::schema  schema(tokens[1].c_str());
     //int group = std::stoi(tokens[0]);
     int group = std::atoi(tokens[0].c_str());
     schema.setGroup(group);
     //printf("schema found %s  %d\n", tokens[1].c_str(),group);
     bool status = true;
     int counter = 0;
     int order   = 0;
     while(status){
       std::string item = hipo::utils::substring(dictString, "[","]",order);
       order++;
       if(item.size()<2){
         status = false;
       } else {
         tokens.clear();
         hipo::utils::tokenize(item, tokens, ",");
         //int item = std::stoi(tokens[0]);
         int item = std::atoi(tokens[0].c_str());
         int type = schema.getTypeByString(tokens[2].c_str());
         if(type!=0){
           schema.addEntry(tokens[1].c_str(),item,type);
         } else {
           printf("** error ** entry %s int schema %s has undefined type.\n",
                     schema.getName().c_str(),tokens[1].c_str()
                  );
         }
         /*printf("\t found item %s %s %s\n",tokens[0].c_str(),tokens[1].c_str(),
                tokens[2].c_str());*/
       }
     }
     mapDict[schema.getName()] = schema;
  }


}
