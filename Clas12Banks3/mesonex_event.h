/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   mesonex_event.h
 * Author: gavalian
 *
 * Created on April 27, 2017, 10:01 AM
 */

#ifndef MESONEX_EVENT_H
#define MESONEX_EVENT_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include "particle.h"
#include "particle_detector.h"
#include "scintillator.h"
#include "calorimeter.h"
#include "cherenkov.h"
#include "forwardtagger.h"
#include "tracker.h"
#include "header.h"
#include "clas12defs.h"

namespace clas12 {

 
  using vecPIDs=std::vector<int >;
  
  class mesonex_event {

  public:

     mesonex_event()=default;

     mesonex_event(hipo::reader &r) {
       init(r);
     }

     ~mesonex_event()=default;

    void    init(hipo::reader &r);
    void reset(){_pentry=0;};
    bool next_particle();

    vecPIDs pids();
    
    void checkTof();
    void checkFT();
    void checkTrack();
    void checkCalorimeter();
    
    double getCalTotEnergy();
    double getTime();
    int    getSector();
    double getPath();
    double getDeltaE();
    double getTrackChi2();
  
    int getPCAL();
    int getECIN();
    int getECOUT();
    int getHTCC();
    int getLTCC();
     
    clas12::particle  &particles(){return _particles;}
    clas12::header    &header(){ return _header;}
    clas12::calorimeter  &calorimeter(){ return  _calorimeter;}
    clas12::scintillator  &tof(){return  _tof;}
    clas12::cherenkov   &cherenkov(){return _cherenkov;}
    clas12::forwardtagger   &ft(){return _ft;}
    clas12::tracker   &track(){return _track;}

    clas12::particle  *particles_ptr(){return &_particles;}
    clas12::header    *header_ptr(){ return &_header;}
    clas12::calorimeter  *calorimeter_ptr(){ return  &_calorimeter;}
    clas12::scintillator  *tof_ptr(){return  &_tof;}
    clas12::cherenkov   *cherenkov_ptr(){return &_cherenkov;}
    clas12::forwardtagger   *ft_ptr(){return &_ft;}
    clas12::tracker   *track_ptr(){return &_track;}

    const int getNParticles(){return _particles.getSize();}

    bool isFT(){return _pftcal!=-1;}
    bool isFTOF(){return _isFTOF;};
    bool isCTOF(){return _isFTOF;};
    bool isCND(){return _isFTOF;};
    bool isECAL(){return (getCalTotEnergy()!=0);};
    
  private:

 
     clas12::particle   _particles;
     clas12::header     _header;
     clas12::calorimeter   _calorimeter;
     clas12::scintillator   _tof;
     clas12::cherenkov   _cherenkov;
     clas12::forwardtagger   _ft;
     clas12::tracker   _track;

     short _ptof=0;
     short _pftcal=0;
     short _pfthodo=0;
     short _pentry=0;
     bool _isFTOF=false;
     bool _isCTOF=false;
     bool _isCND=false;
  
  };
  inline  double mesonex_event::getCalTotEnergy(){
    if(_pftcal>-1) return _ft.getEnergy();
    //note FT hit use EC
    double energy = 0.0;
    getPCAL();
    energy += _calorimeter.getEnergy();
    getECIN();
    energy += _calorimeter.getEnergy();
    getECOUT();   
    energy += _calorimeter.getEnergy();
    return energy;
  }
  
  inline   int mesonex_event::getPCAL(){
    return _calorimeter.getIndex( _pentry,clas12::EC, 1); 
  }

  
  inline  double mesonex_event::getTime(){
    if(_ptof>=0)
      return _tof.getTime();
    if(_pftcal>=0)
      return _ft.getTime();    
    //if no tof hit use EC time
    //    _calorimeter.getIndex(clas12::EC, 1, _pentry); 
    return _calorimeter.getTime();
  }
  inline  int mesonex_event::getSector(){
    if(_track.getIndex()>-1) //use track first
      return _track.getSector();
    if(_ptof>=0)             //then FTOF
      return _tof.getSector();
    if(_pftcal>=0)           //then FT
      return 0;
    //if no tof hit use EC time
    return _calorimeter.getSector();
  }
  inline  double mesonex_event::getPath(){
    if(_ptof>=0)
      return _tof.getPath();
    if(_pftcal>=0){ //currently no FT path reported
      double ftx=_ft.getX();
      double fty=_ft.getY();
      double ftz=_ft.getZ();
      return sqrt(ftx*ftx+fty*fty+ftz*ftz)/100;
    }
    ///   return _ft.getPath();    
    //if no tof hit use EC time
    return _calorimeter.getPath();
  }
  inline   double mesonex_event::getDeltaE(){
    if(_ptof>=0)
      return _tof.getEnergy();
    if(_pfthodo>=0)
      return _ft.getEnergy();
    return 0;
  }

  inline  int mesonex_event::getECIN(){
    return _calorimeter.getIndex( _pentry,clas12::EC, 4); 
  }
  inline  int mesonex_event::getECOUT(){
    return _calorimeter.getIndex( _pentry,clas12::EC, 7); 
  }
  inline  int mesonex_event::getHTCC(){
    return _cherenkov.getIndex( _pentry,clas12::HTCC); 
  }
  inline  int mesonex_event::getLTCC(){
    return _cherenkov.getIndex( _pentry,clas12::LTCC); 
  }
  inline  double mesonex_event::getTrackChi2(){   
    int ndf=  _track.getNDF();
    if(ndf)
      return _track.getChi2()/ndf;
    return 0;
  }
}

#endif /* UTILS_H */
