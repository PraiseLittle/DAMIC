#include "DAMICActionInitialization.hh"

#include "DAMICPrimaryGeneratorAction.hh"

DAMICActionInitialization::DAMICActionInitialization(DAMICDetectorConstruction* detector)
: G4VUserActionInitialization(),
fDetector(detector)
{

}

DAMICActionInitialization::~DAMICActionInitialization()
{}

void DAMICActionInitialization::BuildForMaster() const
{}

void DAMICActionInitialization::Build() const
{

  DAMICPrimaryGeneratorAction* primary = new DAMICPrimaryGeneratorAction();
  SetUserAction(primary);
}
