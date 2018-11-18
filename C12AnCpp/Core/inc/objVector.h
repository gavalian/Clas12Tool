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
#include <memory>
#include <vector>

namespace core {
//////////////////////////////////////////////////////////////////////
//
// Vector of objects, data structure that can be stored in 
// the Temporary Data Container
// the use of unique pointers ensures memory managment
//////////////////////////////////////////////////////////////////////
  class objVector : public object, public std::vector< std::unique_ptr<object> > {

  };
}

