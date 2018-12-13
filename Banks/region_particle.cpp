/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "region_particle.h"

namespace clas12 {

  region_particle::region_particle(par_ptr pars,covmat_ptr cm):
    _parts(pars),
    _covmat(cm)
  {
  }
  region_particle::region_particle(par_ptr pars,covmat_ptr cm, ft_ptr ftp):
    _parts(pars),
    _covmat(cm),
    _ft(ftp)
  {
    
  }
  region_particle::region_particle(par_ptr pars,covmat_ptr cm, scint_ptr scp, trck_ptr trp):
    _parts(pars),
    _covmat(cm),
    _scint(scp),
    _trck(trp)
  {
    
  }
  region_particle::region_particle(par_ptr pars,covmat_ptr cm, cal_ptr calp, scint_ptr scp, trck_ptr trp, cher_ptr chp):
    _parts(pars),
    _covmat(cm),
    _cal(calp),
    _scint(scp),
    _trck(trp),
    _cher(chp)
  {
    
  }
  region_particle::region_particle(par_ptr pars,covmat_ptr cm, cal_ptr calp, scint_ptr scp, trck_ptr trp, cher_ptr chp, ft_ptr ftp):
    _parts(pars),
    _covmat(cm),
    _cal(calp),
    _scint(scp),
    _trck(trp),
    _cher(chp),
    _ft(ftp)
  {
    
  }
  

}
