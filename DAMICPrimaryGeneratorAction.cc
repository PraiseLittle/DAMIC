#include "DAMICPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iostream>

#include <string>

#include <fstream>
#include <math.h>
using namespace std;

DAMICPrimaryGeneratorAction::DAMICPrimaryGeneratorAction():G4VUserPrimaryGeneratorAction(),fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleDefinition* particle
  = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.,0.,0.));
  fParticleGun->SetParticleEnergy(1);
  fParticleGun->SetParticlePosition(G4ThreeVector(0*m,0.*cm,0.*cm));

}

DAMICPrimaryGeneratorAction::~DAMICPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void DAMICPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  G4ParticleDefinition* particle
  = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

  fParticleGun->SetParticleEnergy(1);
  fParticleGun->SetParticlePosition(G4ThreeVector(0*m,0*m,0*m));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1,0,0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
