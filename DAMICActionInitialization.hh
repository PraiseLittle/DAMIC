#ifndef damicActionInitialization_hh
#define damicActionInitialization_hh

#include <stdio.h>


#include "G4VUserActionInitialization.hh"

class DAMICDetectorConstruction;

class DAMICActionInitialization:public G4VUserActionInitialization
{
public:
  DAMICActionInitialization(DAMICDetectorConstruction* detector );
  ~DAMICActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
  DAMICDetectorConstruction* fDetector;

};

#endif
