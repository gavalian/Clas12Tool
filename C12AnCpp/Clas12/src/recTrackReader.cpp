#include "Clas12/recTrackReader.h"
#include "Core/objMap.h"

#include <memory>

#include "reader.h"
#include "Clas12/hipoReader.h"

using namespace clas12;

void recTrackReader::init(){ 
  hipo::reader *_reader = ((hipoReader*)getDataReader())->getReader();
  REC__Track_NDF       = _reader->getBranch<int16_t>("REC::Track","NDF");
  REC__Track_NDF_nomm  = _reader->getBranch<int16_t>("REC::Track","NDF_nomm");
  REC__Track_chi2      = _reader->getBranch<float>("REC::Track","chi2");
  REC__Track_chi2_nomm = _reader->getBranch<float>("REC::Track","chi2_nomm");
  REC__Track_detector  = _reader->getBranch<int8_t>("REC::Track","detector");
  REC__Track_index     = _reader->getBranch<int16_t>("REC::Track","index");
  REC__Track_pindex    = _reader->getBranch<int16_t>("REC::Track","pindex");   
  REC__Track_px_nomm   = _reader->getBranch<float>("REC::Track","px_nomm");    
  REC__Track_py_nomm   = _reader->getBranch<float>("REC::Track","py_nomm");    
  REC__Track_pz_nomm   = _reader->getBranch<float>("REC::Track","pz_nomm");    
  REC__Track_q         = _reader->getBranch<int8_t>("REC::Track","q");         
  REC__Track_sector    = _reader->getBranch<int8_t>("REC::Track","sector");
  REC__Track_status    = _reader->getBranch<int16_t>("REC::Track","status");
  REC__Track_vx_nomm   = _reader->getBranch<float>("REC::Track","vx_nomm");    
  REC__Track_vy_nomm   = _reader->getBranch<float>("REC::Track","vy_nomm");
  REC__Track_vz_nomm   = _reader->getBranch<float>("REC::Track","vz_nomm");   
}

void recTrackReader::processEvent() {

  if( ! REC__Track_NDF ) return;
  if( REC__Track_NDF->getLength() == 0 ) return;
  
  std::shared_ptr<core::objMap<int>> tracks = std::make_shared<core::objMap<int>>();
  for( int i=0; i<REC__Track_NDF->getLength();i++){
    std::unique_ptr<recTrack> tr = std::make_unique<recTrack>();
    tr->NDF =             REC__Track_NDF->getValue(i);
    tr->NDF_nomm =   REC__Track_NDF_nomm->getValue(i);
    tr->chi2 =           REC__Track_chi2->getValue(i);
    tr->chi2_nomm = REC__Track_chi2_nomm->getValue(i);
    tr->detector =   REC__Track_detector->getValue(i);
    tr->index =         REC__Track_index->getValue(i);
    tr->pindex =       REC__Track_pindex->getValue(i);
    tr->px_nomm =     REC__Track_px_nomm->getValue(i);
    tr->py_nomm =     REC__Track_py_nomm->getValue(i);
    tr->pz_nomm =     REC__Track_pz_nomm->getValue(i);
    tr->q =                 REC__Track_q->getValue(i);
    tr->sector =       REC__Track_sector->getValue(i);
    tr->status =       REC__Track_status->getValue(i);
    tr->vx_nomm =     REC__Track_vx_nomm->getValue(i);
    tr->vy_nomm =     REC__Track_vy_nomm->getValue(i);
    tr->vz_nomm =     REC__Track_vz_nomm->getValue(i);

    (*tracks)[ tr->pindex ] = std::move(tr);
  }

  bookObject("recTracks",tracks);
}

