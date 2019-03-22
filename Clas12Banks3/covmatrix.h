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

namespace clas12 {
  
  using CovMatrix =std::vector<std::vector<float > >; 
  using IndMatrix =std::vector<std::vector<int > >; 

  class covmatrix : public hipo::bank {

 
  public:

    //covmatrix() { }
    //vmatrix(const char *bankName, hipo::reader &r) : hipo::bank(bankName,r){
    //
    
  
    //get the pindex = corresponding particle index
    int getPindex(int index) { return getInt(_pindex_order,index);}
    int getPindex() { return getInt(_pindex_order,_index);}
    int getIndex() const {return _index;}
    int getIndex(int pindex);
    void setIndex(int ind){_index=ind;}
    void setEntry(int ind){_index=ind;}

    const  CovMatrix* matrix();

    float getC11() const { return _matrix[0][0];}
    float getC12() const { return _matrix[0][1];}
    float getC13() const { return _matrix[0][2];}
    float getC14() const { return _matrix[0][3];}
    float getC15() const { return _matrix[0][4];}
    float getC22() const { return _matrix[1][1];}
    float getC23() const { return _matrix[1][2];}
    float getC24() const { return _matrix[1][3];}
    float getC25() const { return _matrix[1][4];}
    float getC33() const { return _matrix[2][2];}
    float getC34() const { return _matrix[2][3];}
    float getC35() const { return _matrix[2][4];}
    float getC44() const { return _matrix[3][3];}
    float getC45() const { return _matrix[3][4];}
    float getC55() const { return _matrix[4][4];}
    
    void   init(const char *bankName, hipo::reader &r);
     /**
    * This is virtual method from hipo::bank it will be called
    * every time a bank is read in the reader. Can be used to sort
    * particles and or map particles by pid or type (i.e. charge)
    */
    
    void notify(){ scanIndex();}
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
