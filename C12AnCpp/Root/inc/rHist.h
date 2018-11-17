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
#include "Core/hist.h"

// _______ ROOT includes __________
#include "TH1F.h"

// _______ STL includes __________
#include <string>
using std::string;

namespace root {

  class rHist : public core::hist {
    public:
      rHist( string, string, int, float, float);
      virtual ~rHist() { delete _hist; }
      virtual void fill( float );
    private:
      TH1F *_hist;
  };

};

