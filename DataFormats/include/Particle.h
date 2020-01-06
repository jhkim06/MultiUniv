#ifndef Particle_h
#define Particle_h

#include "TLorentzVector.h"
#include <iostream>

using namespace std;

class Particle: public TLorentzVector{

public:

  //==== Default Constructor with p4
  Particle();
  //==== TLorentzVector copy constructor.
  Particle(const TLorentzVector& p);
  //==== Copy constructor.
  Particle(const Particle& p);
  //==== Construct from 4-vector components
  Particle(double px, double py, double pz, double e);

  //==== Add Charge
  Particle& operator+=(const Particle& p);

  //==== Assignment operator uses KParticle copy constructor
  Particle& operator=(const Particle& p);

  ~Particle();

  void SetCharge(int q);
  inline int Charge() const {return j_Charge;}

  void SetNtupleIndex(int idx);
  inline int getNtupleIndex() const {return ntuple_index;}

private:
  int j_Charge;
  int ntuple_index;

  ClassDef(Particle,1)

};

#endif
