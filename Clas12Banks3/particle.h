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

#ifndef PARTICLE_H
#define PARTICLE_H

#include "bank.h"
#include "vectors.h"

namespace clas12 {

  class particle : public hipo::bank {

  private:

    int pid_order;
    int px_order;
    int py_order;
    int pz_order;
    int vx_order;
    int vy_order;
    int vz_order;
    int ch_order;
    int st_order;
    
    short _entry=0;
    
  public:

    particle() = default;

  particle(const char *bankName, hipo::reader &r) : hipo::bank(bankName,r){};

    ~particle() = default;


    void   init(const char *bankName, hipo::reader &r);
    int    getPid(int index) { return getInt(pid_order,index);}
    float  getPx(int index)  { return getFloat(px_order,index);}
    float  getPy(int index)  { return getFloat(py_order,index);}
    float  getPz(int index)  { return getFloat(pz_order,index);}
    float  getVx(int index)  { return getFloat(vx_order,index);}
    float  getVy(int index)  { return getFloat(vy_order,index);}
    float  getVz(int index)  { return getFloat(vz_order,index);}
    int    getCharge(int index)  { return getInt(ch_order,index);}
    int    getStatus(int index)  { return getInt(st_order,index);}

    int    getPid() { return getInt(pid_order,_entry);}
    float  getPx()  { return getFloat(px_order,_entry);}
    float  getPy()  { return getFloat(py_order,_entry);}
    float  getPz()  { return getFloat(pz_order,_entry);}
    float  getVx()  { return getFloat(vx_order,_entry);}
    float  getVy()  { return getFloat(vy_order,_entry);}
    float  getVz()  { return getFloat(vz_order,_entry);}
    int    getCharge()  { return getInt(ch_order,_entry);}
    int    getStatus()  { return getInt(st_order,_entry);}

    void  getVector3(int index, vector3 &vect){
      vect.setXYZ(getFloat(px_order,index),getFloat(py_order,index),
            getFloat(pz_order,index));
    }

    void getVector4(int index, vector4 &vect, double mass){
      vect.setXYZM(getFloat(px_order,index),getFloat(py_order,index),
            getFloat(pz_order,index),mass);
    }
 
    float getP(){
      auto x= getFloat(px_order,_entry);
      auto y= getFloat(py_order,_entry);
      auto z= getFloat(pz_order,_entry);
      return sqrt(x*x+y*y+z*z);
    }
   void setEntry(short i){ _entry=i;}
    short getEntry() const {return _entry;}
    /**
    * This is virtual method from hipo::bank it will be called
    * every time a bank is read in the reader. Can be used to sort
    * particles and or map particles by pid or type (i.e. charge)
    */
    void notify() override {
      //printf("particle class is read again\n");
    }
  };
  
  using par_ptr=std::shared_ptr<clas12::particle>;

}

#endif /* UTILS_H */
