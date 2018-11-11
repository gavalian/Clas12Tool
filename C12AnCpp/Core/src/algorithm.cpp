#include "algorithm.h"
#include <memory>

using namespace core;

void algorithm::bookObject( std::string name, std::shared_ptr<object> obj){
  (*_obj)[name] = obj;
}

void* algorithm::getObject( std::string name){
  return (*_obj)[name].get();
}

tuple* algorithm::ntuple( std::string name ){
  if( _oom->hasTuple( name ) ){
    return _oom->getTuple( name );
  }
  else{
    return _oom->mkTuple( name );
  }
}

hist* algorithm::histo( std::string name, int bins, float mi, float ma ){

  if( _oom->hasHist( name ) ){
    return _oom->getHist( name );
  }
  else {
    return _oom->mkHist(name, bins, mi, ma );
  }
}

