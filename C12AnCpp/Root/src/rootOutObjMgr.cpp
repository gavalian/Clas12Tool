#include "rootOutObjMgr.h"

using namespace root;

#include "rTuple.h"
#include "rHist.h"
#include <memory>

core::tuple* rootOutObjMgr::mkTuple( std::string name ){
 
  std::string title = name;
  title.insert(0, "ntuple ");
 
  _tuples[name] = std::make_unique<rTuple>(name,title);
  return dynamic_cast<core::tuple*>(_tuples[name].get());
}

core::hist* rootOutObjMgr::mkHist( std::string name, int n, float m, float M ){
 
  std::string title = name;
  title.insert(0, "histo ");
 
  _hists[name] = std::make_unique<rHist>(name,title, n, m, M);
  return dynamic_cast<core::hist*>(_hists[name].get());
}

