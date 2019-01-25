/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   dictionary.h
 * Author: gavalian
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <string>
#include <vector>


//#include "reader.h"

namespace hipo {

  typedef struct {
    std::string  name;
    std::string  type;
    int          typeId;
    int          typeSize;
    int          offset;
  } schemaEntry_t;

class schema {
  private:

    std::map<std::string, int>    schemaEntriesMap;
    std::vector<schemaEntry_t>    schemaEntries;

    int         groupid;
    int         itemid;
    int         rowLength;
    std::string schemaName;


    int  getTypeSize(int id);
    int  getTypeByString(std::string &typeName);

  public:

    schema(){ groupid = 0; itemid = 0; rowLength = 0;}
    schema(const char *name, int __group,int __item){
      schemaName = name; groupid = __group; itemid = __item;
    }

    virtual ~schema(){}

    void  parse(std::string schString);
    int   getOffset(int item, int order, int rows);
    void  show();
};
  
}

#endif /* NODE_H */
