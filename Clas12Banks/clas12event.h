/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   clas12event.h
 * Author: gavalian
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef CLAS12_EVENT_H
#define CLAS12_EVENT_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include "particle.h"
#include "detector.h"
#include "vectors.h"
#include "header.h"
#include "clas12defs.h"


namespace clas12 {

 
  class clas12event {

  private:

  /*static const char *vinit[] = {
      "REC::Event","REC::Particle","REC::Calorimeter",
      "REC::Scintillator" };
*/
    std::vector<std::string> banks;

    clas12::header     clas12header;
    clas12::particle   clas12particle;
    clas12::detector   clas12calorimeter;
    clas12::detector   clas12tof;
    clas12::detector   clas12cherenkov;

  public:

    clas12event(){ }

    clas12event(hipo::reader &r) {
      banks.push_back("REC::Event");
      banks.push_back("REC::Particle");
      banks.push_back("REC::Calorimeter");
      banks.push_back("REC::Scintillator");
      init(r);
    }

    ~clas12event(){ }

    void    init(hipo::reader &r);

    double  getStartTime();
    double  getTime  ( int detector, int pindex);
    double  getEnergy( int detector, int pindex);
    double  getPath(   int detector, int pindex);
    double  getBeta(   int detector, int pindex);
    void    getHitPosition(int detector, int pindex, vector3 &vec);
    void    getHitPositionLocal(int detector, int pindex, vector3 &vec);

    clas12::particle  &particles(){return clas12particle;}
    clas12::header    &header(){ return clas12header;}

  };

}

#endif /* UTILS_H */
