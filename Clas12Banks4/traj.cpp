/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "traj.h"


namespace clas12 {

 
  traj::traj(hipo::schema __schema): clas12::particle_detector(__schema) {

    _cx_order   =  __schema.getEntryOrder("cx");
    _cy_order   =  __schema.getEntryOrder("cy");
    _cz_order   =  __schema.getEntryOrder("cz");
    _detector_id_order   =  __schema.getEntryOrder("detID");
    _index_order   =  __schema.getEntryOrder("index");
    _pathlength_order   =  __schema.getEntryOrder("pathlength");
    _pindex_order   =  __schema.getEntryOrder("pindex");
    _q_order   =  __schema.getEntryOrder("q");
    _x_order   =  __schema.getEntryOrder("x");
    _y_order   =  __schema.getEntryOrder("y");
    _z_order   =  __schema.getEntryOrder("z");
    
  }


}
