#include "ParticleTree.h"
#include "HipoRootAction.h"
#include "clas12reader.h"
#include <TObjArray.h>
#include <TMacro.h>

namespace hiporoot {

  ParticleTree::ParticleTree(TString filename, TString treefilename): HipoTreeMaker{filename,treefilename}{
    _tempActionName="ParticleTreeAction";

    //Calorimters
    _mapOfParts["ECIN"]="p->cal(ECIN)->";
    _mapOfParts["ECOUT"]="p->cal(ECOUT)->";
    _mapOfParts["PCAL"]="p->cal(PCAL)->";

    //Scintillators
    _mapOfParts["FTOF1A"]="p->sci(FTOF1A)->";
    _mapOfParts["FTOF1B"]="p->sci(FTOF1B)->";
    _mapOfParts["FTOF2"]="p->sci(FTOF2)->";
    _mapOfParts["CTOF"]="p->sci(CTOF)->";
    _mapOfParts["CND1"]="p->sci(CND1)->";
    _mapOfParts["CND2"]="p->sci(CND2)->";
    _mapOfParts["CND3"]="p->sci(CND3)->";

    //FT
    _mapOfParts["FTCAL"]="p->ft(FTCAL)->";
    _mapOfParts["FTHODO"]="p->ft(FTHODO)->";

    //Cherenkov
    _mapOfParts["HTCC"]="p->ft(HTCC)->";
    _mapOfParts["LTCC"]="p->ft(LTCC)->";

    //Trackers
    _mapOfParts["DC"]="p->trk(DC)->";
    _mapOfParts["CVT"]="p->trk(CVT)->";

    //Particles
    _mapOfParts["PBANK"]="p->par()->";

    //Particle Region
    _mapOfParts["P"]="p->";

    //EVENT
    _mapOfParts["EVNT"]="c12.head()->";

  }
  ParticleTree::~ParticleTree(){
    }
  void ParticleTree::Loop(){

     
    while(IsMoreFiles())
      gHipoRootAction->Action(this);
    
  }

  void  ParticleTree::PreCompileAction(){
    std::map<TString,TString> typelabel;
    typelabel["/D"]="Double_t";
    typelabel["/F"]="Float_t";
    typelabel["/I"]="Int_t";
    typelabel["/L"]="Long64_t";
    typelabel["/S"]="Short_t";
    
    TMacro macro(GetCurrMacroName());
  
    TList *lines=macro.GetListOfLines();
    TObject* obj=macro.GetLineWith("class clas12data");
    Int_t place =lines->IndexOf(obj)+2; 
 
    for(UInt_t i=0;i<_branchNames.size();i++){
      TString type=typelabel[_branchTypes[i]];
      TString bname=_branchNames[i];
      bname.ReplaceAll(".","_");
      TString strline=TString("     ")+type + "  "+bname+";";
      lines->AddAt(new TObjString(strline.Data()),place++);

      TString strvar=Form("VVVV%d",i);
      TString vvvvline=macro.GetLineWith(strvar)->GetString();
      vvvvline.ReplaceAll(strvar,bname);
      macro.GetLineWith(strvar)->SetString(vvvvline);
    }
    TString strvar{"if(PCCCC)_treedata"};
    TString ccccline=macro.GetLineWith(strvar)->GetString();
    ccccline.ReplaceAll("PCCCC",_pcut);
    macro.GetLineWith(strvar)->SetString(ccccline);
    
    strvar="if(ECCCC)";
    ccccline=macro.GetLineWith(strvar)->GetString();
    ccccline.ReplaceAll("ECCCC",_evcut);
    macro.GetLineWith(strvar)->SetString(ccccline);
    
    macro.SaveSource(GetCurrMacroName());
  }
}
