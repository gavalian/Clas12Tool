////////////////////////////////////////////////////////////////////////
//____________________
//Begin_Html <!--
/* -->
<h1>TEVNTClass</h1>
<pre>
 Created:
           Gagik Gavalian (July/2018)
</pre>
EVENT Class for CLAS12 DSTs.
<pre>
______________________________________________________________________*/
//End_Html
////////////////////////////////////////////////////////////////////////

#include "TEVNTClass.h"

ClassImp(TEVNTClass)

TEVNTClass::TEVNTClass(TEVNTClass *TmpEVNT){
  Id      =   TmpEVNT->Id;
  Charge  =   TmpEVNT->Charge;
  Betta   =   TmpEVNT->Betta;
  Px      =   TmpEVNT->Px;
  Py      =   TmpEVNT->Py;
  Pz      =   TmpEVNT->Pz;
  X       =   TmpEVNT->X;
  Y       =   TmpEVNT->Y;
  Z       =   TmpEVNT->Z;
  Chi2    =   TmpEvent->Chi2;
  Status  =   TmpEvent->Status;
}

void   TEVNTClass::Print(){
  cout << "TEVNTClass::" << endl;
  cout << "ID      " << Id  << endl;
  //cout << "Pmom    " <<  Pmom  << endl;
  //cout << "Mass    " <<  Mass  << endl;
  cout << "Charge  " << (Int_t) Charge  << endl;
  cout << "Betta   " << Beta  << endl;
  cout << "Px      " << Px  << endl;
  cout << "Py      " << Py  << endl;
  cout << "Pz      " << Pz  << endl;
  cout << "X       " << X  << endl;
  cout << "Y       " << Y  << endl;
  cout << "Z       " << Z  << endl;
  cout << "Chi2    " << Chi2  << endl;
  cout << "Status  " << Status  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TEVNTClass.cc
////////////////////////////////////////////////////////////////
