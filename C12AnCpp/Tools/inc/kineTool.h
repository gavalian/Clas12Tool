//   ___________  ___        _____        
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
//

// ________ Core includes ______
#include "tuple.h"

// ________ Root includes ______
#include "particle.h"

// ________ STL includes _______
#include <string>

//////////////////////////////////////////////////////////////////////
//
// Tool to fill an ntuple with four-momentum components of a particle
//////////////////////////////////////////////////////////////////////
namespace tools {
  class kineTool {
    public:
      void init() {}

      void execute( core::tuple *, root::particle *, std::string prefix=0 );
  };

}

