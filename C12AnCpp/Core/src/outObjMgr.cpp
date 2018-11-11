#include "outObjMgr.h"

using namespace core;

bool outObjMgr::hasTuple( string tpl ){
  if( _tuples.find( tpl ) != _tuples.end() ) return true;
  return false;
}

bool outObjMgr::hasHist( string h ){
  if( _hists.find( h ) != _hists.end() ) return true;
  return false;
}

hist* outObjMgr::getHist( string n ){
  return dynamic_cast<hist*>(_hists[n].get());
}

tuple* outObjMgr::getTuple( string n ){
  return dynamic_cast<tuple*>(_tuples[n].get());
}

