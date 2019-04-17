/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   hallB_event.h
 * Author: dglazier
 *
 */

#ifndef HALLB_EVENT_H
#define HALLB_EVENT_H

#include "clas12defs.h"
#include "reader.h"
#include "particle.h"
#include "mcparticle.h"
#include "calorimeter.h"
#include "scintillator.h"
#include "tracker.h"
#include "cherenkov.h"
#include "header.h"
#include "covmatrix.h"
#include "forwardtagger.h"
#include "region_particle.h"
#include "region_fdet.h"
#include "region_cdet.h"
#include "region_ft.h"

#include <algorithm>


namespace clas12 {

  class hallB_event  {


  public:


    hallB_event()=default;
    hallB_event(hipo::reader &r);
    ~hallB_event()=default;

    bool next();
    bool nextInRecord();
    void sort();
    
    void addARegionFDet(){
      //Forward detector needs particles, calorimeter, scintillator,
      //track, cherenkov
      _rfdets.push_back(std::make_shared<region_fdet>(_bparts,_bcovmat,_bcal,_bscint,_btrck,_bcher,_bft));
    }
     void addARegionCDet(){
      //Forward detector needs particles, calorimeter, scintillator,
      //track, cherenkov
      _rcdets.push_back(std::make_shared<region_cdet>(_bparts,_bcovmat,_bcal,_bscint,_btrck,_bcher,_bft));
    }
    void addARegionFT(){
      //Forward tagger needs particles and forward tagger
      _rfts.push_back(std::make_shared<region_ft>(_bparts,_bcovmat,_bcal,_bscint,_btrck,_bcher,_bft));
    }


    const head_ptr head() const{return _bhead;};
    const mcpar_ptr mcparts() const{return _bmcparts;};
    
    
    std::vector<region_part_ptr>& getDetParticles(){return _detParticles;}
    std::vector<region_part_ptr> getByID(int id);

    int getNParticles() const {return _detParticles.size();}
    
  private:

    //reader
    hipo::reader *_reader=nullptr;
    hipo::event      _event;

    //DST banks
    head_ptr  _bhead;
    par_ptr _bparts;
    mcpar_ptr _bmcparts;
    covmat_ptr _bcovmat;
    cal_ptr  _bcal;
    scint_ptr _bscint;
    trck_ptr _btrck;
    cher_ptr _bcher;
    ft_ptr _bft;

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
  //see for example hallb_event::getByID()
  template <typename Cont, typename Pred>
    Cont container_filter(const Cont &container, Pred predicate){
    Cont result;
    std::copy_if(container.begin(),container.end(),std::back_inserter(result), predicate);
    return std::move(result);
  }

}

#endif /* HALLB_EVENT_H */
