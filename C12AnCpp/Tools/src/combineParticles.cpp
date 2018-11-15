#include "combineParticles.h"

using namespace tools;

#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
using namespace std;

// core includes 
#include "objVector.h"
#include "object.h"

combineParticles::combineParticles( string n, string o ) : _name(n), _opt(o){ } 

void combineParticles::init() { 

  // trim input
  size_t first = _opt.find_first_not_of(' ');
  size_t last = _opt.find_last_not_of(' ');
  _opt = _opt.substr( first,(last-first+1));

  char delim = '+';
  _sign = 1;
  if( _opt.find(delim) != string::npos ){ }
  else { 
    delim = '-';
    _sign = -1;
    if( _opt.find(delim) != string::npos ){ }
    else{
      _sign = -99;
      cerr << " [WARNING] combineParticles malformed option\n";
      return;
    } 
  }

  vector<string> substrs;
  stringstream ss(_opt);
  string item;
  while(getline(ss,item,delim)){
    substrs.push_back(item);
  }
  if( substrs.size() > 1 ){
    _p1 = substrs[0];
    _p2 = substrs[1];
  }
  else{
    cerr << " [WARNING] combineParticles: too few particles\n";
    _sign = -99;
  }

}


void combineParticles::processEvent(){

  // check if there were no errors in the inputs: sign must be either +1 or -1
  if( abs( _sign ) != 1 ) return;
cout << " yeah!1 "<< _p1 << " " << _p2 << " " << _name <<" " << _sign <<" \n";

  // get input particles
  core::objVector *vp1 = (core::objVector*) getObject(_p1);
  if( ! vp1 ) return;
cout << " yeah!2 \n";

  core::objVector *vp2 = ( _p1 == _p2 ) ? vp1 : (core::objVector*) getObject(_p2);
  if( ! vp2 ) return;
cout << " yeah!3 \n";
  // make candidates
  shared_ptr<core::objVector> cands;

  for( unsigned int ip1=0; ip1 < vp1->size(); ip1++ ){
    root::particle *p1 = (root::particle*) (*vp1)[ip1].get();
    
    unsigned int start2 = ( _p1 == _p2 ) ? ip1+1 : 0;
cout << " ++++ 00  - "<< ip1 << " "<< start2<<" \n";
    for( unsigned int ip2 = start2 ; ip2 < vp2->size(); ip2++ ){
      root::particle *p2 = (root::particle*) (*vp2)[ip2].get();
      
cout << " ++++ 01\n";
unique_ptr<root::particle> p3 = make_unique<root::particle>( (*p1 + *p2) );
cout << p1 << " " << p2 << endl;
//root::particle p = *p1 + *p2;
cout << " ++++ 01 bis\n";
      cands->push_back( make_unique<root::particle>( move(p3) ) ); 
cout << " ++++ 02\n";
      
    }
  }


  bookObject( _name, cands );
}

