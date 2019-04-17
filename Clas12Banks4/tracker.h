/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   tracker.h
 * Author: dglazier
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef CLAS12_TRACKER_H
#define CLAS12_TRACKER_H

#include "particle_detector.h"


namespace clas12 {

   class tracker : public particle_detector {

 
  public:


    tracker()=default;

    tracker(hipo::schema __schema);
 
    virtual ~tracker()=default;
    
    //getter funtions for items in tracker bank
    int getNDF(){ 
      if(_index>-1)return getInt(_NDF_order,_index);
      return 0;
    }
    int getNDFnomm(){ 
      if(_index>-1)return getInt(_NDFnomm_order,_index);
      return 0;
    }
    int getSector(){ 
      if(_index>-1)return getInt(_sector_order,_index);
      return 0;
    }
    int getStatus(){ 
      if(_index>-1)return getInt(_status_order,_index);
      return 0;
    }
    double getPXnomm(){ 
      if(_index>-1)return getFloat(_pxnomm_order,_index);
      return 0;
    }
    double getPYnomm(){ 
      if(_index>-1)return getFloat(_pynomm_order,_index);
      return 0;
    }
    double getPZnomm(){ 
      if(_index>-1)return getFloat(_pznomm_order,_index);
      return 0;
    }
    double getVXnomm(){ 
      if(_index>-1)return getFloat(_vxnomm_order,_index);
      return 0;
    }
    double getVYnomm(){ 
      if(_index>-1)return getFloat(_vynomm_order,_index);
      return 0;
    }
    double getVZnomm(){ 
      if(_index>-1)return getFloat(_vznomm_order,_index);
      return 0;
    }
   int getCharge(){ 
      if(_index>-1)return getInt(_q_order,_index);
      return 0;
    }
   double getChi2(){ 
     if(_index>-1)return getFloat(_chi2_order,_index);
     return 0;
   }
   double getChi2nomm(){ 
     if(_index>-1)return getFloat(_chi2nomm_order,_index);
     return 0;
   }
   double getChi2N(){
     auto N=getChi2nomm();
     if(N)return getChi2()/N;
     return 0;
   }
     
 private:

    int    _NDF_order=-1;
    int    _NDFnomm_order=-1;
    int  _sector_order=-1;
    int  _status_order=-1;
    int       _pxnomm_order=-1;
    int       _pynomm_order=-1;
    int       _pznomm_order=-1;
    int       _vxnomm_order=-1;
    int       _vynomm_order=-1;
    int       _vznomm_order=-1;
    int       _q_order=-1;
    int    _chi2_order=-1;
    int    _chi2nomm_order=-1;
 

 
   }; //class tracker

   using trck_ptr=std::shared_ptr<clas12::tracker>;

}//namespace clas12

#endif /* UTILS_H */
