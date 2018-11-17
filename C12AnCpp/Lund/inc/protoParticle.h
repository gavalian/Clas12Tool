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
#include "object.h"

namespace lund {

  class protoParticle : public core::object {
    public:
      virtual ~protoParticle() {}

      // following the definitions at:
      // https://gemc.jlab.org/gemc/html/documentation/generator/lund.html
      int id;
      float lifetime;
      int type;
      int pid;
      int motherID;
      int daughterID;
      float px;
      float py;
      float pz;
      float E;
      float M;
      float vx;
      float vy;
      float vz;
  };
}


