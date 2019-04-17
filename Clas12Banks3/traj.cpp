/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "traj.h"


namespace clas12 {

 
  void   traj::init(const char *bankName, hipo::reader &r,std::string items){

    particle_detector::init(bankName,r,items);

    _cx_order   = getEntryOrder("cx");
    _cy_order   = getEntryOrder("cy");
    _cz_order   = getEntryOrder("cz");
    _detector_id_order   = getEntryOrder("detID");
    _index_order   = getEntryOrder("index");
    _pathlength_order   = getEntryOrder("pathlength");
    _pindex_order   = getEntryOrder("pindex");
    _q_order   = getEntryOrder("q");
    _x_order   = getEntryOrder("x");
    _y_order   = getEntryOrder("y");
    _z_order   = getEntryOrder("z");
    
  }


}
