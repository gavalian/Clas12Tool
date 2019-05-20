/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "calorimeter.h"


namespace clas12 {

 
  void   calorimeter::init(const char *bankName, hipo::reader &r,std::string items){
    std::cout<<" calorimeter::init "<<bankName<<std::endl;
    particle_detector::init(bankName,r,items);
    
    if(useItem("layer"))_layer_order   = getEntryOrder("layer");
    if(useItem("energy"))_energy_order  = getEntryOrder("energy");
    if(useItem("path"))_path_order    = getEntryOrder("path");
    if(useItem("time"))_time_order    = getEntryOrder("time");
    if(useItem("x"))_x_order  = getEntryOrder("x");
    if(useItem("y"))_y_order  = getEntryOrder("y");
    if(useItem("z"))_z_order  = getEntryOrder("z");
    if(useItem("status"))_status_order  = getEntryOrder("status");
    if(useItem("sector"))_sector_order  = getEntryOrder("sector");
    if(useItem("chi2"))_chi2_order  = getEntryOrder("chi2");
    if(useItem("du"))_du_order  = getEntryOrder("du");
    if(useItem("dv"))_dv_order  = getEntryOrder("dv");
    if(useItem("dw"))_dw_order  = getEntryOrder("dw");
    if(useItem("hx"))_hx_order  = getEntryOrder("hx");
    if(useItem("hy"))_hy_order  = getEntryOrder("hy");
    if(useItem("hz"))_hz_order  = getEntryOrder("hz");
    if(useItem("lu"))_lu_order  = getEntryOrder("lu");
    if(useItem("lv"))_lv_order  = getEntryOrder("lv");
    if(useItem("m2u"))_m2u_order  = getEntryOrder("m2u");
    if(useItem("m2v"))_m2v_order  = getEntryOrder("m2v");
    if(useItem("m2w"))_m2w_order  = getEntryOrder("m2w");
    if(useItem("m3u"))_m3u_order  = getEntryOrder("m3u");
    if(useItem("m3v"))_m3v_order  = getEntryOrder("m3v");
    if(useItem("m3w"))_m3w_order  = getEntryOrder("m3w");
  }


}
