#include "algorithm.h"
#include <memory>

//void core::algorithm::bookObject( std::string name, std::unique_ptr<object> obj){
void core::algorithm::bookObject( std::string name, std::shared_ptr<object> obj){
  //(*_obj)[name] = std::make_unique<object>();
  (*_obj)[name] = obj;
}

void* core::algorithm::getObject( std::string name){
  return (*_obj)[name].get();
}

