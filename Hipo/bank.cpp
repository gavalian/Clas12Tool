/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "bank.h"

namespace hipo {

bank::bank(){

}

bank::~bank(){

}

bank::bank(const char *bankName, hipo::reader &r){
  hipo::dictionary *dict = r.getSchemaDictionary();
  if(dict->hasSchema(bankName)==true){
      hipo::schema schema = dict->getSchema(bankName);
      int group = schema.getGroup();
      std::vector<std::string> entries = schema.getEntryList();
      //printf("bank : %s %d\n",schema.getName().c_str(),group);
      for(int i = 0; i < entries.size(); i++){
          int item = schema.getItem(entries[i].c_str());
          hipo::generic_node *node = r.getGenericBranch( group, item);
          //printf("adding node  %s : %d\n", entries[i].c_str(),item);
          bankNodes.push_back(node);
      }
  }
}

void bank::show(){
   int size = bankNodes.size();
   printf("-------------->>>>>>\n");
   for(int i = 0; i < size; i++){
      printf(" NODE %d type = %d , item = %d size = %d\n",
          i, bankNodes[i]->type(), bankNodes[i]->item(),
          bankNodes[i]->length());
   }
}


int    bank::getSize(){
  return bankNodes[0]->length();
}

int    bank::getInt(   int item, int order){
  generic_node *ptr = bankNodes[item];
  int type = ptr->type();
  switch(type){
    case 1: {
        uint8_t *__ptr8 = reinterpret_cast<uint8_t *>(ptr->getAddress());
        return (int) (__ptr8[order]);
      }
      break;
    case 2: {
        uint16_t *__ptr16 = reinterpret_cast<uint16_t *>(ptr->getAddress());
        return (int) (__ptr16[order]);
      }
      break;
    case 3: {
        uint32_t *__ptr32 = reinterpret_cast<uint32_t *>(ptr->getAddress());
        return (int) (__ptr32[order]);
      }
      break;
    default:
      printf("wrong type");
  }
  return 0;
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
