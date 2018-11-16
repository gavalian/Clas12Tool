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

// _______ STL includes __________
#include <string>

namespace core {
//////////////////////////////////////////////////////////////////////
// Abstract interface for histogram
////////////////////////////////////////////////////////////////////// 
  class hist : public object {
    public:
      hist( std::string, std::string, int, float, float);
      virtual ~hist() {};

      // specific implementation
      virtual void fill( float ) = 0;
    private:
      std::string name;
      std::string title;
      int nbins;
      float min;
      float max;
  };

}

