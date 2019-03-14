namespace clas12{};
namespace hipo{};
namespace clas12root{};

using namespace clas12;
using namespace hipo;
using namespace clas12root;

void LoadClas12Root4(){
 
  TString CLAS12TOOL=gSystem->Getenv("CLAS12TOOL");
  TString LIB=CLAS12TOOL+"/lib/";
  gSystem->Load(LIB+"liblz4");
  gSystem->Load(LIB+"libHipo4");
  gSystem->Load(LIB+"libClas12Banks4");
  gSystem->Load(LIB+"libClas12Root4");



}
