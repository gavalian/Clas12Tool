#include "Root/rHist.h"

using namespace root;

rHist::rHist(string name, string title, int n, float minedge, float maxedge) : hist(name,title,n,minedge,maxedge){

  _hist = new TH1F( name.c_str(), title.c_str(), n, minedge, maxedge);
}

void rHist::fill( float val ){
  _hist->Fill( val );
}

