/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "tracker.h"


namespace clas12 {

 
  tracker::tracker(hipo::schema __schema): clas12::particle_detector(__schema) {

    if(useItem("sector"))_sector_order    = __schema.getEntryOrder("sector");
    if(useItem("status"))_status_order    = __schema.getEntryOrder("status");
    if(useItem("px_nomm"))_pxnomm_order  = __schema.getEntryOrder("px_nomm");
    if(useItem("py_nomm"))_pynomm_order  = __schema.getEntryOrder("py_nomm");
    if(useItem("pz_nomm"))_pznomm_order  = __schema.getEntryOrder("pz_nomm");
    if(useItem("vx_nomm"))_vxnomm_order  = __schema.getEntryOrder("vx_nomm");
    if(useItem("vy_nomm"))_vynomm_order  = __schema.getEntryOrder("vy_nomm");
    if(useItem("vz_nomm"))_vznomm_order  = __schema.getEntryOrder("vz_nomm");
    if(useItem("NDF"))_NDF_order  = __schema.getEntryOrder("NDF");
    if(useItem("NDF_nomm"))_NDFnomm_order  = __schema.getEntryOrder("NDF_nomm");
    if(useItem("q"))_q_order  = __schema.getEntryOrder("q");
    if(useItem("chi2"))_chi2_order  = __schema.getEntryOrder("chi2");
    if(useItem("chi2_nomm"))_chi2nomm_order  = __schema.getEntryOrder("chi2_nomm");
   
  }


}
