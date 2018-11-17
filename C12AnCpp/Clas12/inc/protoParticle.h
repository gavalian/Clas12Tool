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

// _______ Core includes __________
#include "Core/object.h"
#include "Core/protoParticle.h"

namespace clas12 {

  class protoParticle : public core::protoParticle {
    public:
      virtual ~protoParticle() {}
      /*int id;*/
      float beta;
      int charge;
      float chi2pid;
      /*int pid;*/
      /*float px;*/
      /*float py;*/
      /*float pz;*/
      int status;
      /*float vx;*/
      /*float vy;*/
      /*float vz;*/
  };
}

