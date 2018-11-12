#include "rTuple.h"

using namespace root;

rTuple::rTuple( string name , string title ){
  tree = new TTree( name.c_str(), title.c_str() );
}

void rTuple::column( string cname, float &var ){

  if( ! tree->GetBranch( cname.c_str() ) ){
    tree->Branch( cname.c_str(), &var );
  }
  else{
    tree->SetBranchAddress( cname.c_str(), &var );
  }
}

void rTuple::fill(){
  tree->Fill();
}

void rTuple::write(){
  tree->Write();
};

