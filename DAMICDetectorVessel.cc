#include "DAMICDetectorVessel.hh"
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


G4LogicalVolume* GetConstructionVessel()
{
  G4double VesselH = 755.65*mm;
  G4double VesselR = 196.977/2*mm;
  G4double A0 = 0;
  G4double A360 = M_PI*2+1;

  G4Tubs* VesselTub = new G4Tubs("VesselTub",A0, VesselR*2, VesselH, A0, A360);
  G4Material* Air = G4Material::GetMaterial("G4_AIR");
  G4LogicalVolume* VesselLV = new G4LogicalVolume(VesselTub, Air,"VesselLV");

  G4LogicalVolume* UpperFlangeLV = GetConstructionUpperFlange();
  G4LogicalVolume* LowerEndLV = GetConstructionLowerEnd();
  G4LogicalVolume* LowerTubeLV = GetConstructionLowerTube();
  G4LogicalVolume* LowerFlangeLV = GetConstructionLowerFlange();


  /*-----------LowerEndPos----------*/
  G4double PosZLowerEnd = -385.7498;/*-387.35*mm;*/
  G4double PosYLowerEnd = 0;
  G4double PosXLowerEnd = 0;
  G4ThreeVector VectLowerEnd = G4ThreeVector(PosXLowerEnd, PosYLowerEnd, PosZLowerEnd);

  /*---------LowerFlangePos---------*/
  G4double PosZLowerFlange = 395.224*mm;
  G4double PosYLowerFlange = 0;
  G4double PosXLowerFlange = 0;
  G4ThreeVector VectLowerFlange = G4ThreeVector(PosXLowerFlange, PosYLowerFlange, PosZLowerFlange);

  /*-------UpperFlangePos---------*/
  G4double PosZUpperFlange = PosZLowerFlange + 28.448*mm;
  G4double PosYUpperFlange = 0;
  G4double PosXUpperFlange = 0;
  G4ThreeVector VectUpperFlange = G4ThreeVector(PosXUpperFlange, PosYUpperFlange, PosZUpperFlange);

  G4PVPlacement* LowerEndPV = new G4PVPlacement(0, VectLowerEnd, LowerEndLV, "LowerEndPV", VesselLV, false, 0, false);
  G4PVPlacement* LowerTubePV = new G4PVPlacement(0, G4ThreeVector(0,0,0), LowerTubeLV, "LowerTubePV", VesselLV, false, 0, false);
  G4PVPlacement* LowerFlangePV = new G4PVPlacement(0, VectLowerFlange, LowerFlangeLV, "LowerFlangePV", VesselLV, false, 0, false);
  G4PVPlacement* UpperFlangePV = new G4PVPlacement(0, VectUpperFlange, UpperFlangeLV, "UpperFlangePV", VesselLV, false, 0, false);


  return VesselLV;
}
G4LogicalVolume* GetConstructionLowerEnd()
{
  G4double depthTot = 12.7*mm;
  G4double depthLittlePart = 3.175*mm;
  G4double depthBigPart = depthTot - depthLittlePart;
  G4double CylRL = 196.6976/2*mm;
  G4double CylRB = 203.2/2*mm;
  G4double zero = 0;
  G4double angle360 = 360;

  G4Tubs * cylMain = new G4Tubs("CylMain", zero, CylRB,depthBigPart/2, zero, angle360);
  G4Tubs * cylLittle = new G4Tubs("CylLittle", zero, CylRL, depthLittlePart/2, zero, angle360);
  G4RotationMatrix* rot0 = new G4RotationMatrix;
  G4ThreeVector lowerEndV = G4ThreeVector(0,0,depthBigPart/2+depthLittlePart/2);
  G4Transform3D lowerEndTr = G4Transform3D(*rot0, lowerEndV);

  G4UnionSolid* lowerEndFinal = new G4UnionSolid( " LowerEndFinal",cylMain, cylLittle, lowerEndTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume *lowerEnd = new G4LogicalVolume(lowerEndFinal, Copper,"LowerEnd");

  return lowerEnd;
}

G4LogicalVolume* GetConstructionLowerTube()
{
  G4double RTubeIn = 196.723/2*mm;
  G4double RTubeOut = 196.977/2*mm;
  G4double HTube  = 755.65*mm;
  G4double zero= 0;
  G4double angle360 = 360;

  G4Tubs* lowerTubeFinal =  new G4Tubs("LowerTubeFinal",RTubeIn, RTubeOut, HTube/2, zero, angle360);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume *lowerTube = new G4LogicalVolume(lowerTubeFinal, Copper,"LowerTube");

  return lowerTube;

}

G4LogicalVolume* GetConstructionLowerFlange()
{

  G4double tubeRin = 196.85/2*mm;
  G4double tubeRout = 304.8/2*mm;
  G4double tubeDepth = 28.448*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;
  G4Tubs * lowerFlangeFinal = new G4Tubs(" LowerFlangeFinal", tubeRin, tubeRout, tubeDepth/2, angle0, angle360 );

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume *lowerFlange= new G4LogicalVolume(lowerFlangeFinal, Copper,"LowerFlange");

  return lowerFlange;
}

G4LogicalVolume* GetConstructionUpperFlange()
{
  G4double tubePrinR = 304.8/2*mm;
  G4double tubePrinH = 28.448*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;
  G4double rmBoxX = 57.15*mm;
  G4double rmBoxY = 152.4*mm;
  G4double rmBoxZ = 28.448*mm;
  G4double rm1TubR = 50.8/2*mm;
  G4double rm1TubH = 28.448*mm;
  G4double rm2TubR = 53.975/2*mm;
  G4double rm2TubH =28.448*mm;

  G4Tubs* tubePrin = new G4Tubs("TubePrin", angle0, tubePrinR, tubePrinH/2, angle0, angle360);
  G4Box* rmBox = new G4Box("RmBox", rmBoxX/2, rmBoxY/2, rmBoxZ);
  G4Tubs* rm1Tub = new G4Tubs("Rm1Tub", angle0, rm1TubR, rm1TubH, angle0, angle360);
  G4Tubs* rm2Tub = new G4Tubs("Rm2Tub", angle0, rm2TubR, rm2TubH, angle0, angle360);

  G4RotationMatrix* rot0 = new G4RotationMatrix;
  G4double rmBoxPosX = 28.575*mm + rmBoxX/2;
  G4ThreeVector rmBoxVect = G4ThreeVector(rmBoxPosX,0,0);
  G4Transform3D rmBoxTr = G4Transform3D(*rot0, rmBoxVect);

  G4double rmTubPosXYVA = 50.8*mm;
  G4ThreeVector rm1TubVect = G4ThreeVector(-rmTubPosXYVA, rmTubPosXYVA,0);
  G4Transform3D rm1TubTr = G4Transform3D(*rot0, rm1TubVect);
  G4ThreeVector rm2TubVect = G4ThreeVector(-rmTubPosXYVA, -rmTubPosXYVA,0);
  G4Transform3D rm2TubTr = G4Transform3D(*rot0, rm2TubVect);

  G4SubtractionSolid* upperFlange1 = new G4SubtractionSolid("UpperFlange1", tubePrin, rmBox, rmBoxTr);
  G4SubtractionSolid* upperFlange2 = new G4SubtractionSolid("UpperFlange2", upperFlange1, rm1Tub, rm1TubTr);
  G4SubtractionSolid* upperFlangeFinal = new G4SubtractionSolid("UpperFlangeFinal", upperFlange2, rm2Tub, rm2TubTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume *upperFlange= new G4LogicalVolume(upperFlangeFinal, Copper,"UpperFlange");

  return upperFlange;
}
