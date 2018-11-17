#include "Core/objVector.h"

#include "reader.h"
#include "Clas12/hipoReader.h"
#include "Clas12/protoParticleReader.h"
using namespace clas12;

#include <iostream>
#include <memory>
#include <vector>
using namespace std;


void protoParticleReader::init() {
  hipo::reader *_reader = ((hipoReader*)getDataReader())->getReader();
  rp_beta   = _reader->getBranch<float>("REC::Particle","beta");
  rp_charge = _reader->getBranch<int8_t>("REC::Particle","charge");
  rp_chi2pid= _reader->getBranch<float>("REC::Particle","chi2pid");
  rp_pid    = _reader->getBranch<int32_t>("REC::Particle","pid");
  rp_px     = _reader->getBranch<float>("REC::Particle","px");
  rp_py     = _reader->getBranch<float>("REC::Particle","py");
  rp_pz     = _reader->getBranch<float>("REC::Particle","pz");
  rp_status = _reader->getBranch<int16_t>("REC::Particle","status");
  rp_vx     = _reader->getBranch<float>("REC::Particle","vx");
  rp_vy     = _reader->getBranch<float>("REC::Particle","vy");
  rp_vz     = _reader->getBranch<float>("REC::Particle","vz");
}

void protoParticleReader::processEvent() {
  // get reader from obj pool
  //hipo::reader *reader = (hipo::reader*)getObject("Event");
  //if( !reader ) { cout << " returning;\n"; return; }
 
  //cout << "  protoParticle READER " << endl;
 
  if( ! rp_beta ) return;
  if( rp_beta->getLength() == 0 ) return;
  //cout << "debug 01"<<endl;
  //std::vector<protoParticle> *particles = new std::vector<protoParticle>();
  shared_ptr<core::objVector> particles = make_shared<core::objVector>();
  for( int i=0; i < rp_beta->getLength(); i++ ){
    unique_ptr<protoParticle> p = make_unique<protoParticle>();
    p->id = i;
    p->beta = rp_beta->getValue(i); 
    p->charge = rp_charge->getValue(i); 
    p->chi2pid = rp_chi2pid->getValue(i); 
    p->pid = rp_pid->getValue(i); 
    p->px = rp_px->getValue(i); 
    p->py = rp_py->getValue(i); 
    p->pz = rp_pz->getValue(i); 
    p->status = rp_status->getValue(i); 
    p->vx = rp_vx->getValue(i); 
    p->vy = rp_vy->getValue(i); 
    p->vz = rp_vz->getValue(i); 
    //cout << " ooo " << p->id << " " << p->pid << " " << p->charge << endl;
    particles->push_back( move(p));
    
    //auto *k = particles->back().get();
    //protoParticle *k = dynamic_cast<protoParticle*>(particles->back().get());

    //cout << " --- " << k->id << " " << k->pid << " " << k->charge << endl;
  }
  //cout << particles->size() << " ======= " << endl;
  //for( auto p : *particles ) cout << static_cast<protoParticle*>(&p)->id << endl;
  bookObject( "protoParticles", particles );
  //bookObject( "protoParticles", move(particles) );
}

