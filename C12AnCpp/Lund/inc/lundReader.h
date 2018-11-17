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
#include "dataReader.h"

// _______ STL includes __________
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <fstream>

namespace lund {

  struct lundEv {
      std::array<float, 10> header;
      std::vector< std::array<float, 14> > parts;
  };

  class lundReader : public core::dataReader {
    public:
      lundReader( std::string );
      void open() {};
      void close();
      void* next(); 

      lundEv* getLundEv() { return _ev.get(); }

    private:
      std::unique_ptr<lundEv> _ev;
      std::ifstream _file;
  };

}

