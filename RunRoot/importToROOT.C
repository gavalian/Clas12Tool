{

  gSystem->SetAclicMode(TSystem::kOpt);
  if(TString(gSystem->Getenv("CLAS12TOOL"))==TString()){
    cout<<"You must define the base directory CLAS12TOOL"<<endl;
    exit(0);							    
  }
  
  if(gSystem->Load(TString(gSystem->Getenv("CLAS12TOOL"))+"/Lz4/lib/liblz4.so")==0){
    //Found liblz4 in LD_LIBRARY_PATH 
    gROOT->ProcessLine("#define __LZ4__"); 
    gSystem->AddIncludePath("-D__LZ4__");
    gSystem->AddIncludePath(TString("-I")+gSystem->Getenv("CLAS12TOOL")+"/Lz4/lib");
  }
  else{
    printf("\n   >>>>> LZ4 compression is not supported.");
    printf("\n   >>>>> check if libz4 is installed on your system.");  
    printf("\n   >>>>> and included in LD_LIBRARY_PATH");  
  }

  //Hipo
  gSystem->AddIncludePath(TString("-I")+gSystem->Getenv("CLAS12TOOL")+"/Hipo");
  gROOT->LoadMacro("$CLAS12TOOL/Hipo/utils.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Hipo/dictionary.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Hipo/node.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Hipo/event.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Hipo/record.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Hipo/reader.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Hipo/bank.cpp+");
  
  //Clas12Banks
  gSystem->AddIncludePath(TString("-I")+gSystem->Getenv("CLAS12TOOL")+"/Clas12Banks");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/vectors.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/header.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/particle.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/mcparticle.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/detector.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/scaler.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/vtp.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/particle_detector.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/scintillator.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/tracker.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/traj.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/forwardtagger.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/cherenkov.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/calorimeter.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/covmatrix.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/region_particle.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/region_ft.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/region_fdet.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/region_cdet.cpp+");
  gROOT->LoadMacro("$CLAS12TOOL/Clas12Banks/clas12reader.cpp+");
 

}
