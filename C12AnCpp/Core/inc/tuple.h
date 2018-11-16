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

#ifndef _C12TUPLE_H
#define _C12TUPLE_H

// _______ Core includes __________
#include "object.h"

// _______ STL includes __________
#include <map>
#include <string>

namespace core {
//////////////////////////////////////////////////////////////////////
// Abstract interface for ntuple
////////////////////////////////////////////////////////////////////// 
  class tuple : public object {

    public:
      virtual ~tuple() {};

      virtual void column( std::string, float );
      virtual void column( std::string, float, std::string );

      // specific inplementation
      virtual void fill() = 0;

      virtual void write() = 0;
    protected:
      std::map<std::string,float> _vars;
  };

}

#endif

