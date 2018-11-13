/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "header.h"

namespace clas12 {

  header::~header(){}


  void header::init(const char *bankName, hipo::reader &r){
    initBranches(bankName,r);
    rn_order = getEntryOrder("NRUN");
    en_order  = getEntryOrder("NEVENT");
    trg_order  = getEntryOrder("TRG");
    st_order  = getEntryOrder("STTime");
  }
}
