#ifndef _OBJVECTOR_H
#define _OBJVECTOR_H
#include <vector>
#include "object.h"
#include <memory>

namespace core {
  class objVector : public object, public std::vector< std::unique_ptr<object> > {

  };
};

#endif
