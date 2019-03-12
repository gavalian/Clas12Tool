/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "mcparticle.h"


namespace clas12 {

  void   mcparticle::init(const char *bankName, hipo::reader &r){
    initBranches(bankName,r);
    pid_order = getEntryOrder("pid");
    px_order  = getEntryOrder("px");
    py_order  = getEntryOrder("py");
    pz_order  = getEntryOrder("pz");
    vx_order  = getEntryOrder("vx");
    vy_order  = getEntryOrder("vy");
    vz_order  = getEntryOrder("vz");
    mass_order  = getEntryOrder("mass");
    
  }


}
