#ifndef CLAS12DEFS_H
#define CLAS12DEFS_H


namespace clas12{
  //regions
  static const short FT = 1000;
  static const short FD = 2000;
  static const short CD = 3000;

  
  //detectors
  static const short FTOF = 12;
  static const short CTOF = 4;
  static const short CND  = 3;
  static const short CVT   = 5;
  static const short DC   = 6;
  static const short EC   = 7;
  static const short FTCAL   = 10;
  static const short FTHODO   = 11;
  static const short HTCC   = 15;
  static const short LTCC   = 16;


  //layers
  static const short FTOF1A = 1;
  static const short FTOF1B = 2;
  static const short FTOF2 = 3;
  //CDET scint layers same as detectors
  //static const short CND  = 3;
  //static const short CTOF = 4;
  static const short CND1  = 1;
  static const short CND2  = 2;
  static const short CND3  = 3;
 
  static const short PCAL   = 1;
  static const short ECIN   = 4;
  static const short ECOUT  = 7;

  //TRAJECTORY
  static const short TRAJ_HTCC  = 0;
  static const short TRAJ_FMT1  = 1;
  static const short TRAJ_FMT2  = 2;
  static const short TRAJ_FMT3  = 3;
  static const short TRAJ_FMT4  = 4;
  static const short TRAJ_FMT5  = 5;
  static const short TRAJ_FMT6  = 6;
  static const short TRAJ_DC1  = 12;
  static const short TRAJ_DC2  = 18;
  static const short TRAJ_DC3  = 24;
  static const short TRAJ_DC4  = 30;
  static const short TRAJ_DC5  = 36;
  static const short TRAJ_DC6  = 42;
  static const short TRAJ_LTCC  = 43;
  static const short TRAJ_FTOF1A  =46;
  static const short TRAJ_FTOF1B  =45;
  static const short TRAJ_FTOF2  =44;
  static const short TRAJ_PCAL  =47;
  static const short TRAJ_ECAL  =48;

  static const short TRAJ_CD1  = 1;
  static const short TRAJ_CD2  = 2;
  static const short TRAJ_CD3  = 3;
  static const short TRAJ_CD4  = 4;
  static const short TRAJ_CD5  = 5;
  static const short TRAJ_CD6  = 6;
  static const short TRAJ_CD7  = 7;
  static const short TRAJ_CD8  = 8;
  static const short TRAJ_CD9  = 9;
  static const short TRAJ_CD10  = 10;
  static const short TRAJ_CD11  = 11;
  static const short TRAJ_CD12  = 12;
   // using indices =vector<short>;
 
}

#endif
