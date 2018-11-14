#include "tuple.h"
#include "particle.h"

#include <string>

namespace tools {
  class kineTool {
    public:
      void init() {}

      void execute( core::tuple *, root::particle *, std::string prefix=0 );
  };

}

