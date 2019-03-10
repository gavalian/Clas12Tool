#include "ParticleHist.h"
#include "HipoRootAction.h"
#include "clas12reader.h"
#include <TObjArray.h>

namespace hiporoot {

  ParticleHist::ParticleHist(TString filename): HipoHist(filename){
    _tempActionName="ParticleHistAction";

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
  ParticleHist::~ParticleHist(){
    }
  void ParticleHist::Loop(){
    while(IsMoreFiles())
      gHipoRootAction->Action(this);
    
  }
 
}
