#include <iostream>
#include <TRint.h>
#include <TString.h>


int main(int argc, char **argv) {

  TRint  *app = new TRint("App", &argc, argv);
// Run the TApplication (not needed if you only want to store the histograms.)
  app->SetPrompt("clas12root [%d] ");

  app->ProcessLine(".x $CLAS12TOOL/RunRoot/LoadClas12Root4.C");
  app->ProcessLine(Form(".x $CLAS12TOOL/RunRoot/LoadProofLib4.C(%s)",argv[1]));
  app->ProcessLine(Form("gProof->Load(\"%s\");",argv[2]));

  app->Run();

  app->Terminate(0);
  
  return 0;
  
}
