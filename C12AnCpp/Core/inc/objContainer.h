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

#ifndef OBJCONTAINER_H
#define OBJCONTAINER_H

// _______ STL includes __________
#include <unordered_map>
#include <string>
#include <memory>

// _______ Core includes __________
#include "object.h"

namespace core {
//////////////////////////////////////////////////////////////////////
//
// Temporary Data Container
// Algorithms will be able to read and write objects in this container 
////////////////////////////////////////////////////////////////////// 
  class objContainer: public std::unordered_map<std::string,std::shared_ptr<object>> { 
  };
}

#endif

