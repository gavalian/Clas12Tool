#ifndef OBJCONTAINER_H
#define OBJCONTAINER_H

#include <unordered_map>
#include <string>
#include <memory>

#include "object.h"

namespace core {

  class objContainer: public std::unordered_map<std::string,std::shared_ptr<object>> { 
    /*class objContainer: public std::map<std::string,std::unique_ptr<object>> { */
  };
};

#endif

