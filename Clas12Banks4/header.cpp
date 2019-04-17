/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "header.h"

namespace clas12 {

  header::header(hipo::dictionary __factory): hipo::bank(__factory.getSchema("REC::EVNT")) {

    auto sch=getSchema();
     
    rn_order = sch.getEntryOrder("NRUN");
    en_order  = sch.getEntryOrder("NEVENT");
    et_order  = sch.getEntryOrder("EVNTime");
    ty_order  = sch.getEntryOrder("TYPE");
    ec_order  = sch.getEntryOrder("EvCAT");
    np_order  = sch.getEntryOrder("NPGP");
    trg_order  = sch.getEntryOrder("TRG");
    bcg_order  = sch.getEntryOrder("BCG");
    lt_order  = sch.getEntryOrder("LT");
    st_order  = sch.getEntryOrder("STTime");
    rf_order  = sch.getEntryOrder("RFTime");
    hel_order  = sch.getEntryOrder("Helic");
    pt_order  = sch.getEntryOrder("PTIME");
  }

  header::header(hipo::schema __schema): hipo::bank(__schema) {
    auto sch=getSchema();
     
    rn_order = sch.getEntryOrder("NRUN");
    en_order  = sch.getEntryOrder("NEVENT");
    et_order  = sch.getEntryOrder("EVNTime");
    ty_order  = sch.getEntryOrder("TYPE");
    ec_order  = sch.getEntryOrder("EvCAT");
    np_order  = sch.getEntryOrder("NPGP");
    trg_order  = sch.getEntryOrder("TRG");
    bcg_order  = sch.getEntryOrder("BCG");
    lt_order  = sch.getEntryOrder("LT");
    st_order  = sch.getEntryOrder("STTime");
    rf_order  = sch.getEntryOrder("RFTime");
    hel_order  = sch.getEntryOrder("Helic");
    pt_order  = sch.getEntryOrder("PTIME");
  }
}
