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

#ifndef EVENT_HEADER_H
#define EVENT_HEADER_H

#include <iostream>
#include <vector>
#include <memory>
#include "bank.h"
#include "vectors.h"

namespace clas12 {

  class header : public hipo::bank {


  public:

 
    header(hipo::dictionary __factory);
    header(hipo::schema __schema);
   virtual ~header() = default;
 
    int    getRunNumber(){ return getInt(rn_order,0); }
    int    getEventNumber(){ return getInt(en_order,0); }
    int    getHelicity(){ return getInt(hel_order,0); }
    int    getType(){ return getInt(ty_order,0); }
    float  getStartTime(){ return getFloat(st_order,0); }
    float  getRFTime(){ return getFloat(rf_order,0); }
    float  getPTime(){ return getFloat(pt_order,0); }
    float  getEVNime(){ return getFloat(et_order,0); }
    float  getBCG(){ return getFloat(bcg_order,0); }
    float  getNPGP(){ return getInt(np_order,0); }
    float  getLT(){ return getFloat(lt_order,0); }
    long   getTrigger(){ return getLong(trg_order,0); }
    
    /**
    * This is virtual method from hipo::bank it will be called
    * every time a bank is read in the reader. Can be used to sort
    * particles and or map particles by pid or type (i.e. charge)
    */
    void notify() final{
      bank::notify();
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

  using head_ptr=std::shared_ptr<clas12::header>;

}

#endif /* UTILS_H */
