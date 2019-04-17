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
#include "node.h"

// if the library is compiled with C++11
// support we will use unordered map which
// is faster than standard map
#if __cplusplus > 199711L
#include <unordered_map>
#endif


namespace hipo {

  //typedef std::auto_ptr<hipo::generic_node> node_pointer;

    class event {

    private:
        std::vector<char> dataBuffer;
        std::map<int,int> eventNodes;

// if the library is compiled with C++11
// define registeredNodes as unordered_map
//#if __cplusplus > 199711L
//        std::unordered_map<int,int> registeredNodes;
//#else
        std::map<int,int> registeredNodes;
//#endif

        std::vector<hipo::generic_node*> nodes;
        //std::vector<std::auto_ptr<hipo::generic_node>> regiteredNodesPtr;
        //void scanEvent();
        void resetNodes();
    public:

        event();
        ~event();

        void showInfo();
        void init(std::vector<char> &buffer);
        void init(const char *buffer, int size);

        int  getEventNode(int group, int item);

        void appendNode(int group, int item, std::vector<int> &vec);
        void appendNode(int group, int item, std::vector<int16_t> &vec);
        void appendNode(int group, int item, std::vector<int8_t> &vec);
        void appendNode(int group, int item, std::vector<float> &vec);
        void appendNode(int group, int item, std::string &vec);

        int   getNodeAddress(int group, int item);
        int   getNodeType(int address);
        int   getNodeLength(int address);
        int   getNodeSize(int address);
        char *getNodePtr(int address);

        std::vector<long>   getLong(   int group, int item);
        std::vector<int>    getInt(    int group, int item);
        std::vector<float>  getFloat(  int group, int item);
        std::string         getString( int group, int item);

        hipo::node<int>    *getIntNode(int group, int item);

        template<class T> hipo::node<T> *getBranch(int group, int item);
        hipo::generic_node              *getEventGenericBranch(int group, int item);

        std::vector<hipo::generic_node*> *getAllBranches(){ return &nodes;}
        //template<class T>   node<T> getNode();
        void scanEvent();
        void scanEventMap();
        std::vector<char> getEventBuffer();
        void reset();
    };
    /*
    template<class T>   node<T> event::getNode(){
        node<T> en;
        en.setLength(4);
        en.setAddress(NULL);
        return en;
    } */
}

namespace hipo {

   template<class T> hipo::node<T> *event::getBranch(int group, int item){
     int size = nodes.size();
     int key  =  ((0x00000000|group)<<16)  | ( (0x00000000|item)<<8);
     registeredNodes[key] = size;
     hipo::node<T> *type = new hipo::node<T>(group,item);
     nodes.push_back(type);
     return type;
   }
}

#endif /* EVENT_H */
