#include "Clas12/hipoReader.h"
#include "Clas12/recEventReader.h"
#include "Clas12/recEvent.h"
using namespace clas12;

#include <memory>

void recEvBank::init( const char *bname, hipo::reader &r ){
  initBranches( bname, r );
}

void recEvBank::addBranch( std::string b ){
  order[b] = getEntryOrder(b.c_str());
}

void recEventReader::init() {

  _bank.init( "REC::Event", *static_cast<hipoReader*>(getDataReader())->getReader() );

  std::string brnames[] = {
                           "NRUN",   
                           "NEVENT", 
                           "EVNTime", 
                           "TYPE",   
                           "EvCAT",  
                           "NPGP",   
                           "TRG",    
                           "BCG",    
                           "LT",     
                           "STTime", 
                           "RFTime", 
                           "Helic",  
                           "PTIME"
                            };  
  for( int i=0;i<13;i++) _bank.addBranch( brnames[i] );
}


void recEventReader::processEvent() {

  if( _bank.getSize() == 0 ) return;

  std::shared_ptr<recEvent> rec = std::make_shared<recEvent>();

  rec->NRUN   = _bank.getInt("NRUN",0) ;
  rec->NEVENT = _bank.getInt("NEVENT",0) ;
  rec->EVNTime= _bank.getFloat("EVNTime",0) ;
  rec->TYPE   = _bank.getInt("TYPE",0) ;
  rec->EvCAT  = _bank.getInt("EvCAT",0) ;
  rec->NPGP   = _bank.getInt("NPGP",0) ;
  rec->TRG    = _bank.getLong("TRG",0) ;
  rec->BCG    = _bank.getFloat("BCG",0) ;  
  rec->LT     = _bank.getDouble("LT",0) ;   
  rec->STTime = _bank.getFloat("STTime",0) ;
  rec->RFTime = _bank.getFloat("RFTime",0) ;
  rec->Helic  = _bank.getInt("Helic",0) ;
  rec->PTIME  = _bank.getFloat("PTIME",0) ;
    
  
  bookObject("recEvent",rec);   

}
