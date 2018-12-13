/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "header.h"

namespace clas12 {


  void header::init(const char *bankName, hipo::reader &r){
    initBranches(bankName,r);
 
    rn_order = getEntryOrder("NRUN");
    en_order  = getEntryOrder("NEVENT");
    et_order  = getEntryOrder("EVNTime");
    ty_order  = getEntryOrder("TYPE");
    ec_order  = getEntryOrder("EvCAT");
    np_order  = getEntryOrder("NPGP");
    trg_order  = getEntryOrder("TRG");
    bcg_order  = getEntryOrder("BCG");
    lt_order  = getEntryOrder("LT");
    st_order  = getEntryOrder("STTime");
    rf_order  = getEntryOrder("RFTime");
    hel_order  = getEntryOrder("Helic");
    pt_order  = getEntryOrder("PTIME");
  }
}
