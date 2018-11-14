#include "tuple.h"

using namespace core;


void tuple::column( std::string name, float var ){
  column(name,var,"");
}

void tuple::column( std::string name, float var, std::string prefix ){
  name.insert(0,prefix);
  _vars[name] = var;  
}

