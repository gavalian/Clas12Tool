/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   clas12reader.h
 * Author: dglazier
 *
 */

#ifndef CLAS12READER_H
#define CLAS12READER_H

#include "clas12defs.h"
#include "reader.h"
#include "particle.h"
#include "mcparticle.h"
#include "calorimeter.h"
#include "scintillator.h"
#include "tracker.h"
#include "traj.h"
#include "cherenkov.h"
#include "header.h"
#include "vtp.h"
#include "scaler.h"
#include "covmatrix.h"
#include "forwardtagger.h"
#include "region_particle.h"
#include "region_fdet.h"
#include "region_cdet.h"
#include "region_ft.h"

#include <algorithm>


namespace clas12 {

  class clas12reader  {


  public:


    clas12reader()=default;
    clas12reader(string filename);
    ~clas12reader()=default;

    hipo::reader& getReader(){return _reader;}
    
    bool next();
    bool nextInRecord();
    void sort();
    void readEvent();
   
    void addARegionFDet(){
      //Forward detector needs particles, calorimeter, scintillator,
      //track, cherenkov
      _rfdets.push_back(std::make_shared<region_fdet>(_bparts,_bcovmat,_bcal,_bscint,_btrck,_btraj,_bcher,_bft,_bhead));
    }
     void addARegionCDet(){
      //Forward detector needs particles, calorimeter, scintillator,
      //track, cherenkov
       _rcdets.push_back(std::make_shared<region_cdet>(_bparts,_bcovmat,_bcal,_bscint,_btrck,_btraj,_bcher,_bft,_bhead));
    }
    void addARegionFT(){
      //Forward tagger needs particles and forward tagger
      _rfts.push_back(std::make_shared<region_ft>(_bparts,_bcovmat,_bcal,_bscint,_btrck,_btraj,_bcher,_bft,_bhead));
    }


    const head_ptr head() const{return _bhead;};
    const vtp_ptr vtp() const{return _bvtp;};
    const scaler_ptr scaler() const{return _bscal;};
    const mcpar_ptr mcparts() const{return _bmcparts;};
    
    
    std::vector<region_part_ptr>& getDetParticles(){return _detParticles;}
    std::vector<region_part_ptr>* getDetParticlesPtr(){return &_detParticles;}
    std::vector<region_part_ptr> getByID(int id);

    int getNParticles() const {return _detParticles.size();}
    
  private:

    //reader
    hipo::reader     _reader;
    hipo::event      _event;

    //DST banks
    head_ptr  _bhead;
    par_ptr _bparts;
    mcpar_ptr _bmcparts;
    covmat_ptr _bcovmat;
    cal_ptr  _bcal;
    scint_ptr _bscint;
    trck_ptr _btrck;
    traj_ptr _btraj;
    cher_ptr _bcher;
    ft_ptr _bft;
    vtp_ptr _bvtp;
    scaler_ptr _bscal;

    //Detector region vectors,
    //each particle in an event will have
    //one associated
    std::vector<region_fdet_ptr> _rfdets;
    std::vector<region_cdet_ptr> _rcdets;
    std::vector<region_ft_ptr> _rfts;
    std::vector<region_part_ptr> _detParticles;


    ushort _nparts=0;
    ushort _n_rfdets=0;
    ushort _n_rcdets=0;
    ushort _n_rfts=0;
 
  };
  //helper functions
  
  //filter vectors via a lambda function
  //see for example clas12reader::getByID()
  template <typename Cont, typename Pred>
    Cont container_filter(const Cont &container, Pred predicate){
    Cont result;
    std::copy_if(container.begin(),container.end(),std::back_inserter(result), predicate);
    return std::move(result);
  }

}

#endif /* CLAS12READER_H */
