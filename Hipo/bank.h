/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   bank.h
 * Author: gavalian
 *
 * Created on April 12, 2017, 10:14 AM
 */

#ifndef HIPO_BANK_H
#define HIPO_BANK_H
#include <iostream>
#include <vector>
#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "node.h"
#include "reader.h"

namespace hipo {

  //typedef std::auto_ptr<hipo::generic_node> node_pointer;

    class bank : public hipo::notification {

    private:
      // pointers of the nodes belonging to the bank
      // this pointers are initialized in the constructor
      // from the dictionary of the passed reader class
      std::vector<generic_node*>  bankNodes;
      // copy of the schema kept in the bank
      hipo::schema                bankSchema;
      std::map<std::string,int>   bankEntryOrder;
      std::vector<int>            bankRows;

      std::string   getDataStringInt(int item);
      std::string   getDataStringLong(int item);
      std::string   getDataStringFloat(int item);
      std::string   getDataStringDouble(int item);




    protected:

      int    getEntryOrder(const char *entryName);
      void   initBranches(const char *bank, hipo::reader &r);
      
    public:

        bank();
        // constructor initializes the nodes in the bank
        // and they will be filled automatically by reader.next()
        // method.
        bank(const char* bankName, hipo::reader &r);

        ~bank();
        // display the content of the bank
        void show();

        void require(const char *rows);
        // returns the rows of the bank
        int        getSize();

        hipo::schema  &getSchema() { return bankSchema;}
        // methods to return values of nodes from the bank
        // item - is the node
        // oreder - is the element of given node
        int        getInt(   int item, int order);
        long       getLong(   int item, int order);
        double     getDouble(   int item, int order);
        float      getFloat( int item, int order);

        virtual  void notify(){ };
  };

}


#endif /* EVENT_H */
