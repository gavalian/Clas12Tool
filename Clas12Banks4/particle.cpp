/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "particle.h"
#include "dictionary.h"


namespace clas12 {

  particle::particle(hipo::dictionary __factory): hipo::bank(__factory.getSchema("REC::Particle")) {
 
    auto sch=getSchema();
    pid_order = sch.getEntryOrder("pid");
    px_order  = sch.getEntryOrder("px");
    py_order  = sch.getEntryOrder("py");
    pz_order  = sch.getEntryOrder("pz");
    vx_order  = sch.getEntryOrder("vx");
    vy_order  = sch.getEntryOrder("vy");
    vz_order  = sch.getEntryOrder("vz");
    ch_order  = sch.getEntryOrder("charge");
    st_order  = sch.getEntryOrder("status");
    
  }

  particle::particle(hipo::schema __schema): hipo::bank(__schema) {
 
    auto sch=getSchema();
    pid_order = sch.getEntryOrder("pid");
    px_order  = sch.getEntryOrder("px");
    py_order  = sch.getEntryOrder("py");
    pz_order  = sch.getEntryOrder("pz");
    vx_order  = sch.getEntryOrder("vx");
    vy_order  = sch.getEntryOrder("vy");
    vz_order  = sch.getEntryOrder("vz");
    ch_order  = sch.getEntryOrder("charge");
    st_order  = sch.getEntryOrder("status");
    
  }

  
}
