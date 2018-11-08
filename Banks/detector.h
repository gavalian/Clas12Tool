/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   detector.h
 * Author: gavalian
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef DETECTOR_H
#define DETECTOR_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include "bank.h"


namespace clas12 {

  class detector : public hipo::bank {

  private:

    int detector_id_order;
    int  energy_order;
    int  pindex_order;
    int    path_order;
    int    time_order;
    int       x_order;
    int       y_order;
    int       z_order;

  public:
    detector(const char *bankName, hipo::reader &r) : hipo::bank(bankName,r){
       detector_id_order = getEntryOrder("detector");
       energy_order  = getEntryOrder("energy");
       path_order    = getEntryOrder("path");
       time_order    = getEntryOrder("time");
       pindex_order  = getEntryOrder("pindex");
       x_order  = getEntryOrder("x");
       y_order  = getEntryOrder("y");
       z_order  = getEntryOrder("z");
    }

    ~detector();

    int    getDetector(int index) { return getInt(detector_id_order,index);}

    float  getIndex(int index) { return getFloat(pindex_order,index);}
    float  getPath(int index) { return getFloat(path_order,index);}
    float  getTime(int index) { return getFloat(time_order,index);}
    float  getEnergy(int index) { return getFloat(energy_order,index);}
    float  getX(int index) { return getFloat(x_order,index);}
    float  getY(int index) { return getFloat(y_order,index);}
    float  getZ(int index) { return getFloat(z_order,index);}

  };

}

#endif /* UTILS_H */
