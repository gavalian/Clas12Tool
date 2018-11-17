/*   ___________  ___        _____        
//  / ___<  /_  |/ _ | ___  / ___/__  ___ 
// / /__ / / __// __ |/ _ \/ /__/ _ \/ _ \
// \___//_/____/_/ |_/_//_/\___/ .__/ .__/
//                           /_/  /_/    
// Yet another analysis framework for CLAS12 data, but in C++
//
// Author: fbossu (@ jlab.org)
// Date:   2018/11/16
//
// License: GPLv3 attached
*/

#pragma once

// _______ Hipo includes __________
#include "node.h"

// _______ Core includes __________
#include "Core/algorithm.h"

// _______ Clas12 includes __________
#include "Clas12/protoParticle.h"

namespace clas12 {

  class protoParticleReader : public core::algorithm {
    public:
      protoParticleReader() {};

      virtual void init();
      virtual void processEvent();
      virtual void terminate() {};
       
    private:
      hipo::node<float>      *rp_beta  ;
      hipo::node<int8_t>    *rp_charge ;
      hipo::node<float>    *rp_chi2pid ;
      hipo::node<int32_t>     *rp_pid  ;
      hipo::node<float>       *rp_px   ;
      hipo::node<float>       *rp_py   ;
      hipo::node<float>       *rp_pz   ;
      hipo::node<int16_t>   *rp_status ;
      hipo::node<float>       *rp_vx   ;
      hipo::node<float>       *rp_vy   ;
      hipo::node<float>       *rp_vz   ;

  };

}

