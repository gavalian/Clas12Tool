//Load all the libraries for use in PROOF-lite
// to set the workers run like :
//clas12root4 'LoadProofLib4.C(N)'
void LoadProofLib4(Int_t Nworkers=1){
  
  gSystem->Load("libProof.so");
  TProof *proof =nullptr;
  if(!gProof) 
    proof = TProof::Open("://lite");
  else
    proof=gProof;
  
  Int_t NCores=Nworkers;
  proof->SetParallel(NCores);
  if(gProof->Load(TString(gSystem->Getenv("CLAS12TOOL"))+"/lib/liblz4.so",kTRUE)==0){}
  // get the sandbox directroy
  TString sandbox="~/.proof";
  if(TString(gEnv->GetValue("ProofLite.Sandbox",""))!=TString()){
    sandbox=gEnv->GetValue("ProofLite.Sandbox","");
  }
  //  copy pcm files to sandbox/cache
  gSystem->Exec(Form("cp $CLAS12TOOL/lib/libHipo4_rdict.pcm %s/cache/.",sandbox.Data()));
  gSystem->Exec(Form("cp $CLAS12TOOL/lib/libClas12Banks4_rdict.pcm %s/cache/.",sandbox.Data()));
  gSystem->Exec(Form("cp $CLAS12TOOL/lib/libClas12Root4_rdict.pcm %s/cache/.",sandbox.Data()));
  
  gProof->Load(TString(gSystem->Getenv("CLAS12TOOL"))+"/lib/libHipo4.so",kTRUE);
  gProof->Load(TString(gSystem->Getenv("CLAS12TOOL"))+"/lib/libClas12Banks4.so",kTRUE);
  gProof->Load(TString(gSystem->Getenv("CLAS12TOOL"))+"/lib/libClas12Root4.so",kTRUE);
  
}
