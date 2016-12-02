#ifndef DAMICPrimaryGeneratorAction_hh
#define DAMICPrimaryGeneratorAction_hh



#include <stdio.h>


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
using namespace std;

class G4Event;

class DAMICPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  DAMICPrimaryGeneratorAction();
  ~DAMICPrimaryGeneratorAction();

public:
    virtual void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() {return fParticleGun;};

private:
    G4ParticleGun*  fParticleGun;
};


#endif
