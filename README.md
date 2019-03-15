# Clas12Tool

Data Analysis Tools for HIPO data format.

Seperate code is provided for hipo3 and hipo4 format. The corresponding directories, libraries and binaries have an additional 3 or 4 to distinguish. Users are responsible for using the correct format for their hipo files.

Examples are given for running in interactive ROOT sessions and ROOT-Jupyter notebooks.


## HipoX -> Clas12BanksX -> Clas12Root

The Hipo c++ reader library can be used independent of specific banks and ROOT, but depends on Hipo.

The Clas12Banks implementation can be used independent of ROOT, although currently ROOT dictionaries are created for the classes via cmake (this could be removed). This defines the specific CLAS12 DST banks and provides an interface to the data.

The Clas12Root package depends on both Hipo and Clas12Banks. This provides ROOT-like analysis tools for operating on clas12 hipo DSTs.

    HipoDraw
    HipoTreeMaker
    HipoProof

## To Download

git clone --recurse-submodules https://github.com/dglazier/Clas12Tool.git

git checkout hipo34

## To setup Run ROOT

cd Clas12Tool

setenv CLAS12TOOL $PWD  (the actual path can be added in your bashrc or tchrc)

setenv PATH "$PATH":"$CLAS12TOOL/bin"

## To install (either Hipo3 or Hipo4)

   installHipo3  and/or installHipo4


## interactive root session

To start an interactive session with pre-loaded Clas12Root us clas12root3 or clas12root4 instead of root on the command line.

##Ex 1  Looping over events and getting particle information

The clas12reader class performs the correlation of particle and detector inofmation (aka reverse indexing). When looping over particles you are looping over region_particle (see Clas12Banks for full reference). Each region, FT, FD and CD has its own definition of a region_particle so it will only return meaningful data (i.e. a CD particle will return 0 for FD detector information). In addition the getTime, getPath, getDetEnergy functions have predefined meaning for each region, e.g. for FT getTime returns FTCAL time, for FD it returns FTOF1A if it exists, if not it will try FTOF1B, FTOF2 then PCAL.

You can insepct the code $CLAS12TOOL/RunRoot/Ex1_CLAS12Reader.C for more guidance on how to use it.

To run (for hipo3 replace the 4 with a 3):

       clas12root4 $CLAS12TOOL/RunRoot/Ex1_CLAS12Reader.C+ --in=/WHERE/IS/MY/HIPO/file.hipo

Note the use of the + sign after the macro name. This compiles the script meaning it will run much faster.

### Jupyter

To install rootbooks see https://root.cern.ch/how/how-create-rootbook

mkdir myNotebooks

cp -r $CLAS12TOOL/RunRoot/jupy myNotebooks/.

cd myNotebooks/jupy

Start a ROOT note book :

      	root --notebook

Click on the notebook CLAS12Reader3Pi.ipynb and follow the tutorial


##Ex 2 Drawing particle histograms from hipo files

       particleDraw4 /WHERE/IS/MY/HIPO/file.hipo

You will get an interactive ROOT prompt where you can draw histograms:

    ParticleHist [0] hists.Hist1D("P.P",100,0,10,"P.P")
    ParticleHist [1] hists.Hist2D("P.P:P.DetEnergy",100,0,10,100,0,5,"P.P")->Draw("2x1")

Note you only have to call draw once, and then it only has to loop over the date once. The option (2x1) specifies the dimensions of the pads in the produced canvas, the parenthesis is required.

Remember at the end you can save all the histograms to file :

    ParticleHist [0] hists.Save("HistFile.root");

Instead of drawing histograms interactively at the prompt you may give predefined histograms via a script e.g. :

	particleDraw4 /WHERE/IS/MY/HIPO/file.hipo Ex2_HipoDraw.C

See $CLAS12TOOL/RunRoot/Ex2_HipoDraw.C for details.

There are predefined aliases for DST bank detector layers :

        ECIN. , ECOUT. , PCAL. , FTOF1A. , FTOF1B. , FTOF2. , CTOF. , CND1. , CND2. , CND3. , FTCAL. , FTHODO. , HTCC. , LTCC. , DC. , CVT. 
        e.g. ECIN.Energy  , HTCC.Nphe , DC.TrChi2 , CTOF.Time

The REC::Particle bank should be directly accessed with 

        PBANK.
        e.g. PBANK.Pid , PBANK.Px
        
The region particle should be accessed with 

        P.
        e.g. P.Theta , P.P , P.Phi , P.Region , P.Time , P.DetEnergy , P.DeltaEnergy , P.Path , P.Pid , P.CalcMass

### Jupyter
Start a ROOT note book :

      	root --notebook
	
Click on the notebook HipoDraw.ipynb and follow the tutorial

##Ex 4 Filtering and Skimming into a ROOT ntuple (tree)

       particleTree4  /WHERE/IS/MY/HIPO/file.hipo /OUTPUT/tree.root Ex4_TreeMaker.C

The script $CLAS12ROOT/RunRoot/Ex4_TreeMaker.C defines which branches are to be written and what cuts to put on the event topology. You can copy and edit this file to do what you want e.g.

     treemaker.Branch("P.Time/F"); //create tree with time branch
     treemaker.Branch("PBANK.Px/F"); //create tree with particle Px branch


     treemaker.AddExactPid(11,1); //filter events with exactly 1 e-
     treemaker.AddAtLeastPid(211,1);//and at least 1 pi+
     treemaker.AddZeroOfRestPid(); //and zero of any other particle type (default is any)

###Jupyter

Start a ROOT note book :

      	root --notebook

Click on the notebook HipoToRootTree.ipynb and follow the tutorial


##Ex 3 Using HipoSelector & PROOFLite

This assumes you are aware of and understand the ROOT TSelector and PROOF scheme. See https://root.cern.ch/proof.

Create a HipoSelector (similar to tree->MakeSelector("mySelector");), using the executable makeHipoSelector :

       makeHipoSelector mySelector

You should use some meaningful name rather than mySelector.
Edit it to perform the tasks you would like. But use the ProcessEvent function instead of the Process function as you would in a TSelector

To execute :


       clas12proof4 4 mySelector.C Ex3_ProofLite.C

Note 4 = number of workers used, you should change this to however many you would like.

Note mySelector is hard-coded in Ex3_ProofLite.C so for your own selector you should copy and edit this script.

###Jupyter

Start a ROOT note book :

      	root --notebook

Click on the notebook CreateHipoSelector.ipynb and follow instructions. This creates the selector you wish to run.

Once this is complete you should open the notebook HipoProof.ipynb and process the selector with PROOF
