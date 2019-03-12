/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "cherenkov.h"


namespace clas12 {

 
  void   cherenkov::init(const char *bankName, hipo::reader &r,std::string items){
    std::cout<<" cherenkov::init "<<bankName<<std::endl;

    particle_detector::init(bankName,r,items);
    
    if(useItem("nphe"))_nphe_order  = getEntryOrder("nphe");
    if(useItem("path"))_path_order    = getEntryOrder("path");
    if(useItem("time"))_time_order    = getEntryOrder("time");
    if(useItem("x"))_x_order  = getEntryOrder("x");
    if(useItem("y"))_y_order  = getEntryOrder("y");
    if(useItem("z"))_z_order  = getEntryOrder("z");
    if(useItem("status"))_status_order  = getEntryOrder("status");
    if(useItem("sector"))_sector_order  = getEntryOrder("sector");
    if(useItem("chi2"))_chi2_order  = getEntryOrder("chi2");
    if(useItem("theta"))_theta_order  = getEntryOrder("theta");
    if(useItem("phi"))_phi_order  = getEntryOrder("phi");
    if(useItem("dtheta"))_dtheta_order  = getEntryOrder("dtheta");
    if(useItem("dphi"))_dphi_order  = getEntryOrder("dphi");
  }


}
