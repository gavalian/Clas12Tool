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
#include "Core/algorithm.h"

// _______ STL includes __________
#include <unordered_map>
#include <string>

namespace root {

  class particleMaker : public core::algorithm {
   
    public:
      virtual void init();
      virtual void processEvent();
      virtual void terminate() {} 

    private:

      std::unordered_map<int,std::string> _pname;
  };
}

