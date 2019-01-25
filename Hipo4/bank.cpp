/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "bank.h"
#include "utils.h"

namespace hipo {
  //==============================================================
  // Definition of class structure, this will class will be extended
  // to represent different objects that will be appended to the event
  //==============================================================

    bool structure::allocate(int size){
      if(structureBuffer.size()<size){
        structureBuffer.resize(size+32);
      }
      return true;
    }
    void structure::initStructureBySize(int __group, int __item, int __type, int __size){
      allocate(__size+8);
      structureAddress = &structureBuffer[0];
      *reinterpret_cast<uint16_t *>(structureAddress) = (uint16_t) __group;
      *reinterpret_cast<uint8_t *>(&structureAddress[2]) = (uint8_t) __item;
      *reinterpret_cast<uint8_t *>(&structureAddress[3]) = (uint8_t) __type;
      *reinterpret_cast<uint32_t *>(&structureAddress[4]) = __size;
    }
    /**
    * returns the size of the structure
    */
    int structure::getSize(){
      int size = *reinterpret_cast<uint32_t *>(structureAddress+4);
      return size;
    }
    // return the type of the structure
    int structure::getType(){
      int type = (int) (*reinterpret_cast<uint8_t *>(structureAddress+3));
      return type;
    }
    // returns the group number of the object
    int structure::getGroup(){
      int group = (int) (*reinterpret_cast<uint16_t *>(structureAddress));
      return group;
    }
    // returns the item number of the structure
    int structure::getItem(){
      int item = (int) (*reinterpret_cast<uint8_t *>(structureAddress+2));
      return item;
    }
    void structure::init(const char *buffer, int size){
      allocate(size);
      memcpy(&structureBuffer[0],buffer,size);
      structureAddress = &structureBuffer[0];
    }

    void structure::show(){
      printf("structure : [%5d,%5d] type = %4d, length = %6d\n",
         getGroup(),getItem(),getType(),getSize());
    }

    std::string  structure::getStringAt(int index){
        int length = getSize();
        char *string_ch = (char *) malloc(length+1);
        std::memcpy(string_ch, &structureBuffer[8],length);
        string_ch[length] = '\0';
        std::string result = string_ch;
        free(string_ch);
        return result;
    }

    const char *structure::getAddress(){
      return structureAddress;
    }
    //====================================================================
    // END of structure class
    //====================================================================
bank::bank(){

}

bank::~bank(){

}


/*void bank::show(){
}*/


}
