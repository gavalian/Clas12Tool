////////////////////////////////////////////////////////////////////////
// File TEVNTClass.h
//
// Initial Author: Gagik Gavalian  JLAB  07/10/2018
//
// This file is generated borrowed from original CLASTool library.
// original authors: G.Gavalian & M.Holtrop
////////////////////////////////////////////////////////////////////////
#ifndef _TEVNTClass_
#define _TEVNTClass_
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"
#include "TVector3.h"
#include "TMath.h"

class TEVNTClass {

public:

 Int_t     Id;     //-> Particle Data Group ID (from SEB)
 Char_t    Charge; //-> charge (from tracking)
 Float_t   Betta;  //-> Particle velocity in the units of c (=R_trk/TOF/c)
 Float_t   Px;     //-> Momentum Vector X component.
 Float_t   Py;     //-> Momentum Vector Y component.
 Float_t   Pz;     //-> Momentum Vector Z component.
 Float_t   X;      //-> "Vertex" Vector X component. The vertex is actually a projection onto a plane.
 Float_t   Y;      //-> "Vertex" Vector Y component. The vertex is actually a projection onto a plane.
 Float_t   Z;      //-> "Vertex" Vector Z component. The vertex is actually a projection onto a plane.
 Float_t   Chi2;   //-> Quality of PID
 Int_t     Status; //-> Defines the status of the particle.
 public:
  TEVNTClass(){};
  TEVNTClass(TEVNTClass *TmpEVNT);
  ~TEVNTClass(){};
  //Bool_t IsEVNT(){return(kTRUE);};    // True, since it is an EVNT class
  //Bool_t IsGSIM(){return(kFALSE);};   // False...
  void 	 Print();
  //
  //
  //
  //
  ClassDef(TEVNTClass,1) //Class for accessing the EVNT bank: particle information
};
#endif
