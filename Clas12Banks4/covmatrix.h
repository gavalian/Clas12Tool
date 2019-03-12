/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   covmatrix.h
 * Author: dglazier
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef CLAS12_COVMATRIX_H
#define CLAS12_COVMATRIX_H

#include "bank.h"
#include <vector>
#include <map>
#include <memory>

namespace clas12 {
  
  using CovMatrix =std::vector<std::vector<float > >; 
  using IndMatrix =std::vector<std::vector<int > >; 

  class covmatrix : public hipo::bank {

 
  public:

    //covmatrix() { }
    //vmatrix(const char *bankName, hipo::reader &r) : hipo::bank(bankName,r){
    //
    covmatrix(hipo::schema __schema);
 
  
    //get the pindex = corresponding particle index
    int getPindex(int index) { return getInt(_pindex_order,index);}
    int getPindex() { return getInt(_pindex_order,_index);}
    int getIndex() const {return _index;}
    int getIndex(int pindex);
    void setIndex(int ind){_index=ind;}

    const  CovMatrix* matrix();

    /**
    * This is virtual method from hipo::bank it will be called
    * every time a bank is read in the reader. Can be used to sort
    * particles and or map particles by pid or type (i.e. charge)
    */
    
    void notify() final{
      bank::notify();
      scanIndex();
    }
    void scanIndex();
    void print();
    
    private :
    
    CovMatrix _matrix={5,std::vector<float>(5,0)};
    IndMatrix _morder={5,std::vector<int>(5,-1)};
    int  _pindex_order=-1;
    int _index=-1;
    //std::map<int,int> _rmap;
    std::vector<int> _rvec;
  };

  using covmat_ptr=std::shared_ptr<clas12::covmatrix>;
}

#endif /* UTILS_H */
