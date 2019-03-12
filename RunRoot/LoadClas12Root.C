{

  TString CLAS12TOOL=gSystem->Getenv("CLAS12TOOL");
  TString LIB=CLAS12TOOL+"/lib/";
  gSystem->Load(LIB+"liblz4");
  gSystem->Load(LIB+"libHipo");
  gSystem->Load(LIB+"libClas12");
  gSystem->Load(LIB+"libClas12Root");



}
