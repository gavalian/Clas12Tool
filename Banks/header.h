/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   particle.h
 * Author: gavalian
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef EVENT_HEADER_H
#define EVENT_HEADER_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include "bank.h"
#include "vectors.h"

namespace clas12 {

  class header : public hipo::bank {

  private:

    int rn_order;
    int en_order;
    int st_order;
    int trg_order;

  public:

    header() { }
    header(const char *bankName, hipo::reader &r) : hipo::bank(bankName,r){
       rn_order = getEntryOrder("NRUN");
       en_order  = getEntryOrder("NEVENT");
       trg_order  = getEntryOrder("TRG");
       st_order  = getEntryOrder("STTime");
    }

    ~header();


    void   init(const char *bankName, hipo::reader &r);
    int    getRunNumber(){ return getInt(rn_order,0); }
    int    getEventNumber(){ return getInt(en_order,0); }
    float  getStartTime(){ return getFloat(st_order,0); }
    long   getTrigger(){ return getLong(trg_order,0); }
    /**
    * This is virtual method from hipo::bank it will be called
    * every time a bank is read in the reader. Can be used to sort
    * particles and or map particles by pid or type (i.e. charge)
    */
    void notify(){
      //printf("particle class is read again\n");
    }
  };

}

#endif /* UTILS_H */
