/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "event.h"

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
    event::event(){
        #if __cplusplus > 199711L
            printf("\n*****>>>>> compiled with c++11 support.\n");
        #endif
        // default allocation size for the event is 20 Kb
        //
        dataBuffer.resize(20*1024);
        reset();
        //printf("creating event class.....\n");
        //hipo::node<int> *type = new hipo::node<int>();
        //nodes.push_back(type);
    }

    event::event(int size){
        dataBuffer.resize(size);
        reset();
    }

    event::~event(){

    }

    void event::getStructure(hipo::structure &str, int group, int item){
       std::pair<int,int> index = getStructurePosition(group,item);
       if(index.first>0){
         str.init(&dataBuffer[index.first], index.second + 8);
       } else {
         //printf("*** error *** : structure (%5d,%5d) does not exist\n", group,item);
       }
    }

    void event::init(std::vector<char> &buffer){
        dataBuffer.resize(buffer.size());
        std::memcpy(&dataBuffer[0],&buffer[0],buffer.size());
    }

    std::pair<int,int>  event::getStructurePosition(int group, int item){
      int position = 16;
      int eventSize = *(reinterpret_cast<uint32_t*>(&dataBuffer[4]));
      while(position+8<eventSize){
          uint16_t   gid = *(reinterpret_cast<uint16_t*>(&dataBuffer[position]));
          uint8_t    iid = *(reinterpret_cast<uint8_t*>(&dataBuffer[position+2]));
          uint8_t   type = *(reinterpret_cast<uint8_t*>(&dataBuffer[position+3]));
          int     length = *(reinterpret_cast<int*>(&dataBuffer[position+4]));
          //printf("group = %4d , item = %4d\n",(unsigned int) gid, (unsigned int) iid);
          if(gid==group&&iid==item) return std::make_pair(position,length);
          position += (length + 8);
      }
      return std::make_pair(-1,0);
    }

    void event::init(const char *buffer, int size){
        if(dataBuffer.size()<=size){
         dataBuffer.resize(size);
       }
       std::memcpy(&dataBuffer[0],buffer,size);
       *(reinterpret_cast<uint32_t*>(&dataBuffer[4])) = size;
    }

    int event::getSize(){
      return *(reinterpret_cast<uint32_t*>(&dataBuffer[4]));
    }
    void event::reset(){
        dataBuffer[0] = 'E'; dataBuffer[1] = 'V';
        dataBuffer[2] = 'N'; dataBuffer[3] = 'T';
        *(reinterpret_cast<uint32_t*>(&dataBuffer[ 4])) = 16;
        *(reinterpret_cast<uint32_t*>(&dataBuffer[ 8])) = 0;
        *(reinterpret_cast<uint32_t*>(&dataBuffer[12])) = 0;
    }
    std::vector<char> &event::getEventBuffer(){ return dataBuffer;}
    /*
    template<class T>   node<T> event::getNode(){
        node<T> en;
        en.setLength(4);
        en.setAddress(NULL);
    } */
    void event::show(){
        printf(" EVENT  SIZE = %d\n",getSize());
        int position = 16;
        int eventSize = *(reinterpret_cast<uint32_t*>(&dataBuffer[4]));
        while(position+8<eventSize){
            uint16_t   gid = *(reinterpret_cast<uint16_t*>(&dataBuffer[position]));
            uint8_t    iid = *(reinterpret_cast<uint8_t*>(&dataBuffer[position+2]));
            uint8_t   type = *(reinterpret_cast<uint8_t*>(&dataBuffer[position+3]));
            int     length = *(reinterpret_cast<int*>(&dataBuffer[position+4]));
            //printf("group = %4d , item = %4d\n",(unsigned int) gid, (unsigned int) iid);
            //if(gid==group&&iid==item) return std::make_pair(position,length);
            printf("%12s %9d %4d %12d %12d\n"," ",gid,iid,type,length);
            position += (length + 8);
        }
    }
}
