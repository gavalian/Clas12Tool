{
  hiporoot::ParticleTree treemaker("/home/dglazier/fastdata/hipo3test/out_clas_004013.evio.99.hipo","test.root");

  treemaker.Branch("P.Time/F");
  treemaker.Branch("PBANK.Px/F");
  treemaker.Branch("PBANK.Py/F");
  treemaker.Branch("PBANK.Pz/F");
  treemaker.Branch("PBANK.Vx/F");
  treemaker.Branch("PBANK.Vy/F");
  treemaker.Branch("PBANK.Vz/F");
  treemaker.Branch("PBANK.Pid/I");

  // treemaker.AddParticleCut("PBANK.Pid==11");
  
  treemaker.Fill();
}
