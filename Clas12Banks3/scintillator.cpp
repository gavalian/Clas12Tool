/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "scintillator.h"


namespace clas12 {

 
  void   scintillator::init(const char *bankName, hipo::reader &r,std::string items){
    std::cout<<" scintilator::init "<<bankName<<std::endl;

    particle_detector::init(bankName,r,items);
    
    if(useItem("layer"))_layer_order   = getEntryOrder("layer");
    if(useItem("energy"))_energy_order  = getEntryOrder("energy");
    if(useItem("path"))_path_order    = getEntryOrder("path");
    if(useItem("time"))_time_order    = getEntryOrder("time");
    if(useItem("sector"))_sector_order    = getEntryOrder("sector");
    if(useItem("status"))_status_order    = getEntryOrder("status");
    if(useItem("x"))_x_order  = getEntryOrder("x");
    if(useItem("y"))_y_order  = getEntryOrder("y");
    if(useItem("z"))_z_order  = getEntryOrder("z");
    if(useItem("hx"))_hx_order  = getEntryOrder("hx");
    if(useItem("hy"))_hy_order  = getEntryOrder("hy");
    if(useItem("hz"))_hz_order  = getEntryOrder("hz");
    if(useItem("chi2"))_chi2_order  = getEntryOrder("chi2");
   
  }


}
