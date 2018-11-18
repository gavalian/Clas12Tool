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
#include "Core/tuple.h"

// _______ STL includes __________
#include <string>
using std::string;

// _______ ROOT includes __________
#include "TTree.h"

namespace root {

  class rTuple : public core::tuple {
    public:
      rTuple( string, string );
      virtual ~rTuple() { delete tree; }

      /*void column( string, float * );*/
      void fill();
      void write();
    private:
      TTree *tree;  
  };

};

