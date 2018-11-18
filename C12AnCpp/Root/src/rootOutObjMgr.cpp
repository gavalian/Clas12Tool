#include "Root/rootOutObjMgr.h"

using namespace root;

#include "Root/rTuple.h"
#include "Root/rHist.h"
#include <memory>

rootOutObjMgr::rootOutObjMgr( string foutname ) : _fout(0x0){
  _fname = foutname; 
  open();
}

rootOutObjMgr::~rootOutObjMgr(){
  close();
}

void rootOutObjMgr::open() {
  if( ! _fout ){
    _fout = TFile::Open( _fname.c_str(), "recreate");
  }
}

void rootOutObjMgr::close() {
  if( ! _fout ){
    return;
  }
  if( _fout->IsOpen() ){
    _fout->Write();
    _tuples.clear();
    _hists.clear();
    _fout->Close();
  }
}

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

