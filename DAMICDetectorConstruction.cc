#include "DAMICDetectorConstruction.hh"
#include "DAMICDetectorCopperBox.hh"
#include "DAMICDetectorInnerLead.hh"
#include "DAMICDetectorVessel.hh"
#include "DAMICDetectorOutterLead.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MultiUnion.hh"
#include "G4Transform3D.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>


DAMICDetectorConstruction::DAMICDetectorConstruction():G4VUserDetectorConstruction(),fCheckOverlaps(false)
{
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* WorldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Cuivre = nist->FindOrBuildMaterial("G4_Cu");
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;


}

DAMICDetectorConstruction::~DAMICDetectorConstruction(){}

G4VPhysicalVolume* DAMICDetectorConstruction::Construct()
{

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();


  G4Material* WorldMat = G4Material::GetMaterial("G4_AIR");

  G4Box* WorldBox = new G4Box( "WorldBox", 5.0*m, 5.0*m, 5.0*m);

  G4LogicalVolume* WorldLV = new G4LogicalVolume(WorldBox, WorldMat, "WorldLV");


  G4VPhysicalVolume* WorldPV = new G4PVPlacement (0, G4ThreeVector(), WorldLV, "World",0, false, 0, fCheckOverlaps);

  G4LogicalVolume* CopperBoxLV = GetConstructionCopperBox();
  G4LogicalVolume* InnerLeadLV = GetConstructionInnerLead();
  G4LogicalVolume* VesselLV = GetConstructionVessel();
  G4LogicalVolume* OutterLeadLV = GetConstructionOutterLead();

  /*--------CopperBoxPos------*/
  G4double CopperBoxZ = -39.2748*mm;
  G4ThreeVector CopperBoxVect = G4ThreeVector(0,0,CopperBoxZ);
  /*-----------InnerLeadPos------*/
  G4double InnerLeadZ = CopperBoxZ+76.1302*mm;
  G4ThreeVector InnerLeadVect = G4ThreeVector(0,0,InnerLeadZ);
  G4ThreeVector uInner = G4ThreeVector(0,-1,0);
  G4ThreeVector vInner = G4ThreeVector(1,0,0);
  G4ThreeVector wInner = G4ThreeVector(0,0,1);
  G4RotationMatrix* InnerLeadRot = new G4RotationMatrix(uInner, vInner, wInner);

  /*--------OutterLeadPos------*/
  G4double OutterLeadZ = -228.727*mm;
  G4ThreeVector OutterLeadVect = G4ThreeVector(0,0,OutterLeadZ);

  G4PVPlacement* CopperBoxPV = new G4PVPlacement(0, CopperBoxVect, CopperBoxLV, "CopperBoxPV", WorldLV, false, 0, fCheckOverlaps);
  G4PVPlacement* InnerLeadPV = new G4PVPlacement(InnerLeadRot, InnerLeadVect, InnerLeadLV, "InnerLeadPV", WorldLV, false, 0, fCheckOverlaps);
  G4PVPlacement* VesselPV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), VesselLV, "VesselPV", WorldLV, false, 0, fCheckOverlaps);
  G4PVPlacement* OutterLeadPV = new G4PVPlacement(0, OutterLeadVect, OutterLeadLV, "OutterLeadPV", WorldLV, false, 0, fCheckOverlaps);

  return WorldPV;

}
