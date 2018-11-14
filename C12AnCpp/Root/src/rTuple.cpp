#include "rTuple.h"
#include <iostream>

using namespace root;

rTuple::rTuple( string name , string title ){
  tree = new TTree( name.c_str(), title.c_str() );
}

void rTuple::fill(){
  for( auto &v : _vars ){
    string name = v.first;
    //std::cout << "first " << name << " val " << val << "\n";
    if( ! tree->GetBranch( name.c_str() ) ){
      tree->Branch( name.c_str(), &v.second );
    }
    else{
      tree->SetBranchAddress( name.c_str(), &v.second );
    }
  }
  tree->Fill();
  _vars.clear();
}

void rTuple::write(){
  tree->Write();
};

