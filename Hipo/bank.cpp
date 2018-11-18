/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "bank.h"
#include "utils.h"

namespace hipo {

bank::bank(){

}

bank::~bank(){

}

bank::bank(const char *bankName, hipo::reader &r){
  initBranches(bankName,r);
}

void bank::initBranches(const char *bank, hipo::reader &r){
  hipo::dictionary *dict = r.getSchemaDictionary();
  if(dict->hasSchema(bank)==true){
      hipo::schema schema = dict->getSchema(bank);

      bankSchema = schema;
      int  group = schema.getGroup();

      std::vector<std::string> entries = schema.getEntryList();
      //printf("bank : %s %d\n",schema.getName().c_str(),group);
      for(int i = 0; i < entries.size(); i++){
          int item = schema.getItem(entries[i].c_str());
          hipo::generic_node *node = r.getGenericBranch( group, item);
          //printf("adding node  %s : %d\n", entries[i].c_str(),item);
          bankNodes.push_back(node);
          bankEntryOrder[entries[i]] = i;
      }
  }
  r.addListener(this);
}
/**
* returns the order of entry for the item in a bank
* with name=entryName
*/
int bank::getEntryOrder(const char *entryName){
  if(bankEntryOrder.count(entryName)==0){
    printf("bank %s does not have entry %s\n",
      bankSchema.getName().c_str(),entryName);
    return -1;
  }
  return bankEntryOrder[entryName];
}

void bank::require(const char *rows){
  std::string expression = rows;
  std::vector<std::string> tokens;
  hipo::utils::tokenize(expression,tokens,std::string(":"));
  for(int i = 0; i < tokens.size(); i++){
    int order = getEntryOrder(tokens[i].c_str());
    printf("requiring row = %s entry order = %d\n",tokens[i].c_str(),order);
  }
}

void bank::show(){
   int size = bankNodes.size();
   std::vector<std::string> entries = bankSchema.getEntryList();
   printf("-------------->>>>>> hipo::bank >>> %s\n",bankSchema.getName().c_str());
   for(int i = 0; i < size; i++){
     int type = bankNodes[i]->type();
      //printf(" NODE %d type = %d , item = %d size = %d\n",
      //    i, bankNodes[i]->type(), bankNodes[i]->item(),
      //    bankNodes[i]->length());
      printf("%12s : ", entries[i].c_str());
          if(type==1||type==2||type==3){
             std::string dataString = getDataStringInt(i);
             printf("%s\n",dataString.c_str());
          }
          if(type==4){
            std::string dataString = getDataStringFloat(i);
            printf("%s\n",dataString.c_str());
          }
          if(type==5){
            std::string dataString = getDataStringDouble(i);
            printf("%s\n",dataString.c_str());
          }
          if(type==8){
            std::string dataString = getDataStringLong(i);
            printf("%s\n",dataString.c_str());
          }

   }
}

std::string bank::getDataStringInt(int item){
  std::string dataString;
  int rows = getSize();
  char line[36];
  for(int i = 0; i < rows; i++){
    sprintf(line,"%10d ",getInt(item,i));
    dataString.append(line);
  }
  return dataString;
}

std::string bank::getDataStringLong(int item){
  std::string dataString;
  int rows = getSize();
  char line[36];
  for(int i = 0; i < rows; i++){
    sprintf(line,"%10lu ",getLong(item,i));
    dataString.append(line);
  }
  return dataString;
}

std::string bank::getDataStringFloat(int item){
  std::string dataString;
  int rows = getSize();
  char line[36];
  for(int i = 0; i < rows; i++){
    sprintf(line,"%10.4f ",getFloat(item,i));
    dataString.append(line);
  }
  return dataString;
}

std::string bank::getDataStringDouble(int item){
  std::string dataString;
  int rows = getSize();
  char line[36];
  for(int i = 0; i < rows; i++){
    sprintf(line,"%10.4f ",getDouble(item,i));
    dataString.append(line);
  }
  return dataString;
}

int    bank::getSize(){
  return bankNodes[0]->length();
}

int    bank::getInt(   int item, int order){
  generic_node *ptr = bankNodes[item];
  int type = ptr->type();
  switch(type){
    case 1: {
        int8_t *__ptr8 = reinterpret_cast<int8_t *>(ptr->getAddress());
        return (int) (__ptr8[order]);
      }
      break;
    case 2: {
        int16_t *__ptr16 = reinterpret_cast<int16_t *>(ptr->getAddress());
        return (int) (__ptr16[order]);
      }
      break;
    case 3: {
        int32_t *__ptr32 = reinterpret_cast<int32_t *>(ptr->getAddress());
        return (int) (__ptr32[order]);
      }
      break;
    default:
      printf("wrong type");
  }
  return 0;
}

long   bank::getLong(   int item, int order){
  generic_node *ptr = bankNodes[item];
  int type = ptr->type();
  switch(type){
    case 8: {
        long *__ptr8 = reinterpret_cast<long *>(ptr->getAddress());
        return (__ptr8[order]);
      }
      break;
    default:
      printf("wrong type");
  }
  return 0;
}

double     bank::getDouble(   int item, int order){
  generic_node *ptr = bankNodes[item];
  int type = ptr->type();
  switch(type){
    case 5: {
        double *__ptr8 = reinterpret_cast<double *>(ptr->getAddress());
        return (__ptr8[order]);
      }
      break;
    default:
      printf("wrong type");
  }
  return 0.0;
}

float  bank::getFloat( int item, int order){
  generic_node *ptr = bankNodes[item];
  int type = ptr->type();
  switch(type){
    case 4: {
        float *__ptr8 = reinterpret_cast<float *>(ptr->getAddress());
        return (__ptr8[order]);
      }
      break;
    default:
      printf("wrong type");
  }
 return 0.0;
}

}
