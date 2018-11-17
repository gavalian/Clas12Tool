#ifndef RECTRACKREADER_H
#define RECTRACKREADER_H

#include "Core/algorithm.h"
#include "Clas12/recTrack.h"
#include "node.h"

namespace clas12 {
  class recTrackReader : public core::algorithm {
    public:
      recTrackReader() {};

      virtual void init();
      virtual void processEvent();
      virtual void terminate() {};

    private:
      hipo::node<int16_t>         *REC__Track_NDF ;
      hipo::node<int16_t>    *REC__Track_NDF_nomm ;
      hipo::node<float>          *REC__Track_chi2 ;
      hipo::node<float>     *REC__Track_chi2_nomm ;
      hipo::node<int8_t>     *REC__Track_detector ;
      hipo::node<int16_t>       *REC__Track_index ;
      hipo::node<int16_t>      *REC__Track_pindex ;
      hipo::node<float>       *REC__Track_px_nomm ;
      hipo::node<float>       *REC__Track_py_nomm ;
      hipo::node<float>       *REC__Track_pz_nomm ;
      hipo::node<int8_t>            *REC__Track_q ;
      hipo::node<int8_t>       *REC__Track_sector ;
      hipo::node<int16_t>      *REC__Track_status ;
      hipo::node<float>       *REC__Track_vx_nomm ;
      hipo::node<float>       *REC__Track_vy_nomm ;
      hipo::node<float>       *REC__Track_vz_nomm ;

  };

};

#endif

