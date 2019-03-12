/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "scaler.h"

namespace clas12 {


  void scaler::init(const char *bankName, hipo::reader &r){
    initBranches(bankName,r);
 
    ch_order = getEntryOrder("channel");
    sl_order = getEntryOrder("slot");
    val_order = getEntryOrder("value");
    hel_order = getEntryOrder("helicity");
   }
}
