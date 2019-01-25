/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   event.h
 * Author: gavalian
 *
 * Created on April 12, 2017, 10:14 AM
 */

#ifndef HIPO_EVENT_H
#define HIPO_EVENT_H

#include <iostream>
#include <vector>
#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>

// if the library is compiled with C++11
// support we will use unordered map which
// is faster than standard map
#if __cplusplus > 199711L
#include <unordered_map>
#endif


namespace hipo {

  //typedef std::auto_ptr<hipo::generic_node> node_pointer;

  class structure {

    private:

      std::vector<char> structureBuffer;
      char *structureAddress;
      void setAddress(const char *address);

    public:

      structure(){ structureAddress = NULL;}
      structure(int size){ allocate(size);}

      virtual     ~structure(){}
      bool         allocate(int size);
      int          getSize();
      int          getType();
      int          getGroup();
      int          getItem();
      void         init(const char *buffer, int size);
      const char  *getAddress();
      void         show();

      int          getIntAt   ( int index) {
        return *reinterpret_cast<int32_t*>(&structureAddress[index+8]);
      }
      int16_t      getShortAt ( int index){
        return *reinterpret_cast<int16_t*>(&structureAddress[index+8]);
      }
      int8_t       getByteAt  ( int index){
        return *reinterpret_cast<int8_t*>(&structureAddress[index+8]);
      }
      float        getFloatAt ( int index){
        return *reinterpret_cast<float*>(&structureAddress[index+8]);
      }
      double       getDoubleAt( int index){
        return *reinterpret_cast<double*>(&structureAddress[index+8]);
      }
      long         getLongAt  ( int index){
        return *reinterpret_cast<int64_t*>(&structureAddress[index+8]);
      }

      std::string  getStringAt(int index);

      friend class event;
  };

  class event {

    private:

        std::vector<char> dataBuffer;

    public:

        event();
        event(int size);
        virtual ~event();

        void show();
        void init(std::vector<char> &buffer);
        void init(const char *buffer, int size);
        void                getStructure(hipo::structure &str, int group, int item);
        std::pair<int,int>  getStructurePosition(int group, int item);
        std::vector<char>  &getEventBuffer();
        int                 getSize();
        void                reset();
    };
    /*
    template<class T>   node<T> event::getNode(){
        node<T> en;
        en.setLength(4);
        en.setAddress(NULL);
        return en;
    } */

}
/*
namespace hipo {

   template<class T> hipo::node<T> *event::getBranch(int group, int item){
     int size = nodes.size();
     int key  =  ((0x00000000|group)<<16)  | ( (0x00000000|item)<<8);
     registeredNodes[key] = size;
     hipo::node<T> *type = new hipo::node<T>(group,item);
     nodes.push_back(type);
     return type;
   }
}*/

#endif /* EVENT_H */
