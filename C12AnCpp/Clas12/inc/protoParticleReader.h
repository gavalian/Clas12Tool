#include "algorithm.h"
#include "node.h"
#include "protoParticle.h"

namespace clas12 {

  class protoParticleReader : public core::algorithm {
    public:
      protoParticleReader() {};

      virtual void init();
      virtual void processEvent();
      virtual void terminate() {};
       
    private:
      hipo::node<float>      *rp_beta  ;
      hipo::node<int8_t>    *rp_charge ;
      hipo::node<float>    *rp_chi2pid ;
      hipo::node<int32_t>     *rp_pid  ;
      hipo::node<float>       *rp_px   ;
      hipo::node<float>       *rp_py   ;
      hipo::node<float>       *rp_pz   ;
      hipo::node<int16_t>   *rp_status ;
      hipo::node<float>       *rp_vx   ;
      hipo::node<float>       *rp_vy   ;
      hipo::node<float>       *rp_vz   ;

  };

};

