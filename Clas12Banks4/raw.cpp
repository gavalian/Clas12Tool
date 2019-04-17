/*
 * To change this license raw, choose License Raws in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "raw.h"

namespace clas12 {


  void raw::init(const char *bankName, hipo::reader &r){
    initBranches(bankName,r);
 
  }
}
