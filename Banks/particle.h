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

  class particle : public hipo::bank {

  private:

    int pid_order;
    int px_order;
    int py_order;
    int pz_order;
    int vx_order;
    int vy_order;
    int vz_order;

  public:
    particle(const char *bankName, hipo::reader &r) : hipo::bank(bankName,r){
       pid_order = getEntryOrder("pid");
       px_order  = getEntryOrder("px");
       py_order  = getEntryOrder("py");
       pz_order  = getEntryOrder("pz");
    }

    ~particle();

    int    getPid(int index) { return getInt(pid_order,index);}
    float  getPx(int index)  { return getFloat(px_order,index);}
    float  getPy(int index)  { return getFloat(py_order,index);}
    float  getPz(int index)  { return getFloat(pz_order,index);}

    void  getVector3(int index, vector3 &vect){
      vect.setXYZ(getFloat(px_order,index),getFloat(py_order,index),
            getFloat(pz_order,index));
    }

    void getVector4(int index, vector4 &vect, double mass){
      vect.setXYZM(getFloat(px_order,index),getFloat(py_order,index),
            getFloat(pz_order,index),mass);
    }
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
