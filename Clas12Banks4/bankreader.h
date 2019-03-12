/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   bankreader.h
 * Author: dglazier
 *
 */

#ifndef BANKREADER_H
#define BANKREADER_H

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
#include "covmatrix.h"
#include "forwardtagger.h"
/* #include "region_particle.h" */
/* #include "region_fdet.h" */
/* #include "region_cdet.h" */
/* #include "region_ft.h" */

#include <algorithm>


namespace clas12 {

  using bank_ptr= std::shared_ptr<hipo::bank>;
  
  class bankreader  {


  public:


    bankreader()=default;
    bankreader(string filename);
    ~bankreader()=default;

    bool next();
    
 
  private:

    //reader
    hipo::reader     _reader;
    hipo::event      _event;

    //DST banks
    /* bank_ptr  _bhead; */
    /* bank_ptr _bparts; */
    /* bank_ptr _bmcparts; */
    /* bank_ptr _bcovmat; */
    /* bank_ptr  _bcal; */
    /* bank_ptr _bscint; */
    /* bank_ptr _btrck; */
    /* bank_ptr _btraj; */
    /* bank_ptr _bcher; */
    /* bank_ptr _bft; */

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

  };

}

#endif /* CLAS12READER_H */
