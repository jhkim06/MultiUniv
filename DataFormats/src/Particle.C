#include "Particle.h"

ClassImp(Particle)

Particle::Particle() :
  TLorentzVector(),
  j_Charge(0),
  ntuple_index(-1)
{
}

Particle::Particle(const TLorentzVector& p) :
  TLorentzVector(p),
  j_Charge(0),
  ntuple_index(-1)
{
}

Particle::Particle(const Particle& p) :
  TLorentzVector(p),
  j_Charge(p.Charge()),
  ntuple_index(p.getNtupleIndex())
{
}

Particle::Particle(double px, double py, double pz, double e) :
  TLorentzVector(px, py, pz, e),
  j_Charge(0),
  ntuple_index(-1) 
{
}


Particle& Particle::operator=(const Particle& p){
  if(this != &p){
    TLorentzVector::operator=(p);
    j_Charge = p.j_Charge;
    ntuple_index = p.ntuple_index;
  }

  return *this;
}

Particle& Particle::operator+= (const Particle& p){
  TLorentzVector::operator+=(p);
  j_Charge += p.j_Charge;
  return *this;
}

Particle::~Particle()
{
}

void Particle::SetCharge(int q){
  j_Charge = q;
}

void Particle::SetNtupleIndex(int idx){
  ntuple_index = idx;
}
