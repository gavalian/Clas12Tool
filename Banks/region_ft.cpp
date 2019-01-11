/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "region_ft.h"
#include <iostream>

namespace clas12 {

  ///////////////////////////////////////////////////////
  /// constructor used for stand-alone
  region_ft::region_ft(par_ptr pars,covmat_ptr cm, ft_ptr ftp):
    region_particle(pars,cm,ftp)
  {
    _region=clas12::FT;
  }
  ///////////////////////////////////////////////////////
  ///Constructor used for event,
  ///give all detector banks to prevent crashes when looking for FD
  region_ft::region_ft(par_ptr pars,covmat_ptr cm, cal_ptr calp, scint_ptr scp, trck_ptr trp, cher_ptr chp, ft_ptr ftp):
    region_particle(pars,cm,calp,scp,trp,chp,ftp)
  {
    _region=clas12::FT;
  }
  
  ///////////////////////////////////////////////////////
  /// Temporary until FT banks updated
  double region_ft::getPath(){
    if(_pcal>=0){ //currently no FT path reported
      _ft->setIndex(_pcal); 	
      double ftx=_ft->getX();
      double fty=_ft->getY();
      double ftz=_ft->getZ();
      return sqrt(ftx*ftx+fty*fty+ftz*ftz);
    }
    return 0;
  }
  ////////////////////////////////////////////////////////
  ///check if any FT detectors associated with
  ///current particle and store the detector indices
  bool region_ft::sort(){
    region_particle::sort();
    _pcal=_ft->getIndex(_pentry,clas12::FTCAL);
    
    _phod=_ft->getIndex(_pentry,clas12::FTHODO);
    //check if FT assocciated, must be a FTCAL
    if(_pcal!=-1)
      return true;
    return false;
    
  }
  ///////////////////////////////////////////////////////
  /// Get pointer to FT banks for this particle
  /// This should be used directly to acess data
  /// e.g. p->ft(FTCAL)->getEnergy();
  ///      p->ft(FTHODO)->getEnergy();
  const ft_ptr region_ft::ft(ushort lay) const {
    switch(lay){ 
    case clas12::FTCAL :
      _ft->setIndex(_pcal);return _ft;
    case clas12::FTHODO :
      _ft->setIndex(_phod);return _ft;
    }
    _ft->setIndex(-1);return _ft;
  }
  


}
