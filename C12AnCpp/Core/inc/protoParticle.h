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

namespace core {

  class protoParticle : public core::object {
    public:
      virtual ~protoParticle() {}
      int id;
      int pid;
      float px;
      float py;
      float pz;
      float vx;
      float vy;
      float vz;
  };
}

