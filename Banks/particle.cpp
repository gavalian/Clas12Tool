/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "particle.h"


namespace clas12 {

void   particle::init(const char *bankName, hipo::reader &r){
  initBranches(bankName,r);
  pid_order = getEntryOrder("pid");
  px_order  = getEntryOrder("px");
  py_order  = getEntryOrder("py");
  pz_order  = getEntryOrder("pz");
}

  particle::~particle(){}

}
