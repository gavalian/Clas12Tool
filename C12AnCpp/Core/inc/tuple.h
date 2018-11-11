#ifndef _C12TUPLE_H
#define _C12TUPLE_H

#include "object.h"

#include <string>
using std::string;

namespace core {
  class tuple : public object {

    public:
      virtual ~tuple() {};

      virtual void column( string, float &) = 0;

      virtual void fill() = 0;

      virtual void write() = 0;
  };

};

#endif

