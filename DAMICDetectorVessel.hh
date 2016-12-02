#ifndef DAMICDetectorVessel_h
#define DAMICDetectorVessel_h

#include "globals.hh"
class G4LogicalVolume;

G4LogicalVolume* GetConstructionVessel();
G4LogicalVolume* GetConstructionLowerEnd();
G4LogicalVolume* GetConstructionLowerTube();
G4LogicalVolume* GetConstructionLowerFlange();
G4LogicalVolume* GetConstructionUpperFlange();

#endif
