/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "tracker.h"


namespace clas12 {

 
  void   tracker::init(const char *bankName, hipo::reader &r,std::string items){

    particle_detector::init(bankName,r,items);
    
    if(useItem("sector"))_sector_order    = getEntryOrder("sector");
    if(useItem("status"))_status_order    = getEntryOrder("status");
    if(useItem("px_nomm"))_pxnomm_order  = getEntryOrder("px_nomm");
    if(useItem("py_nomm"))_pynomm_order  = getEntryOrder("py_nomm");
    if(useItem("pz_nomm"))_pznomm_order  = getEntryOrder("pz_nomm");
    if(useItem("vx_nomm"))_vxnomm_order  = getEntryOrder("vx_nomm");
    if(useItem("vy_nomm"))_vynomm_order  = getEntryOrder("vy_nomm");
    if(useItem("vz_nomm"))_vznomm_order  = getEntryOrder("vz_nomm");
    if(useItem("NDF"))_NDF_order  = getEntryOrder("NDF");
    if(useItem("NDF_nomm"))_NDFnomm_order  = getEntryOrder("NDF_nomm");
    if(useItem("q"))_q_order  = getEntryOrder("q");
    if(useItem("chi2"))_chi2_order  = getEntryOrder("chi2");
    if(useItem("chi2_nomm"))_chi2nomm_order  = getEntryOrder("chi2_nomm");
   
  }


}
