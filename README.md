# Clas12Tool

Data Analysis Tools for HIPO data format.

Seperate code is provided for hipo3 and hipo4 format. The corresponding directories, libraries and binaries have an additional 3 or 4 to distinguish. Users are responsible for using the correct format for their hipo files.

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

you wil need the following enviroment variable set

setenv CLAS12TOOL /path to Clas12Tool/

## To install (either Hipo3 or Hipo4)

   installHipo3  and/or installHipo4

These scripts are currently only in tcsh, but they are quite simple and should be easily portable to bash




