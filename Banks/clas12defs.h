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
  static const short FTOF1A = 0;
  static const short FTOF1B = 1;
  static const short FTOF2 = 2;
  //CDET scint layers same as detectors
  //static const short CND  = 3;
  //static const short CTOF = 4;
  static const short CND1  = 1;
  static const short CND2  = 2;
  static const short CND3  = 3;
 
  static const short PCAL   = 1;
  static const short ECIN   = 4;
  static const short ECOUT  = 7;

  // using indices =vector<short>;
 
}

#endif
