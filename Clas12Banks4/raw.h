/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   header.h
 * Author: gavalian
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef EVENT_RAW_H
#define EVENT_RAW_H

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

  class raw : public hipo::bank {


  public:

 

    void   init(const char *bankName, hipo::reader &r);
   
    /**
    * This is virtual method from hipo::bank it will be called
    * every time a bank is read in the reader. Can be used to sort
    * particles and or map particles by pid or type (i.e. charge)
    */
    void notify(){
      //printf("particle class is read again\n");
    }

  private :

    int rn_order;
    int en_order;
    int et_order;
    int ty_order;
    int ec_order;
    int np_order;
    int trg_order;
    int bcg_order;
    int lt_order;
    int st_order;
    int rf_order;
    int hel_order;
    int pt_order;
 
    
  };

  using head_ptr=std::shared_ptr<clas12::raw>;

}

#endif /* UTILS_H */
