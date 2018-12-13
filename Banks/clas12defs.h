#ifndef CLAS12DEFS_H
#define CLAS12DEFS_H


namespace clas12{
  //regions
  static const ushort FT = 1000;
  static const ushort FD = 2000;
  static const ushort CD = 3000;

  
  //detectors
  static const ushort FTOF = 12;
  static const ushort CTOF = 4;
  static const ushort CND  = 3;
  static const ushort CVT   = 5;
  static const ushort DC   = 6;
  static const ushort EC   = 7;
  static const ushort FTCAL   = 10;
  static const ushort FTHODO   = 11;
  static const ushort HTCC   = 15;
  static const ushort LTCC   = 16;


  //layers
  static const ushort FTOF1A = 0;
  static const ushort FTOF1B = 1;
  static const ushort FTOF2 = 2;
  //CDET scint layers same as detectors
  //static const ushort CND  = 3;
  //static const ushort CTOF = 4;
  static const ushort CND1  = 1;
  static const ushort CND2  = 2;
  static const ushort CND3  = 3;
 
  static const ushort PCAL   = 1;
  static const ushort ECIN   = 4;
  static const ushort ECOUT  = 7;

  // using indices =vector<short>;
 
}

#endif
