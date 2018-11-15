#ifndef _C12TUPLE_H
#define _C12TUPLE_H

#include "object.h"

#include <map>
/*#include <unordered_map>*/
#include <string>

namespace core {
  class tuple : public object {

    public:
      virtual ~tuple() {};

      virtual void column( std::string, float );
      virtual void column( std::string, float, std::string );

      virtual void fill() = 0;

      virtual void write() = 0;
    protected:
      std::map<std::string,float> _vars;
      /*std::unordered_map<std::string,float> _vars;*/
  };

};

#endif

