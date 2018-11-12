#ifndef _OBJMAP_H
#define _OBJMAP_H
#include <unordered_map>
#include "object.h"
#include <memory>

namespace core {
  template <class T>
  class objMap : public object, public std::unordered_map< T, std::unique_ptr<object> > {

  };
};

#endif
