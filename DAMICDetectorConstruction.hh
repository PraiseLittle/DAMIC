#ifndef DAMICDetectorConstruction_h
#define DAMICDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;


class DAMICDetectorConstruction: public G4VUserDetectorConstruction
{
public:
    DAMICDetectorConstruction();
    ~DAMICDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

private:
    G4bool fCheckOverlaps;

};

#endif
