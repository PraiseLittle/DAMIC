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

G4LogicalVolume* GetConstructionOutterLead()
{
  G4double boxX = 1*m;
  G4double boxY = 1*m;
  G4double boxZ = 1*m;


  G4Box* boxOutterLead = new G4Box("BoxOutterLead", boxX, boxY, boxZ);

  /*--------BottomLead------*/

  G4double BottomLeadX = 304.8*mm;
  G4double BottomLeadY = 304.8*mm;
  G4double BottomLeadZ = 50.8*mm;

  G4Box* boxBottomLeadFinal = new G4Box("boxBottomLeadFinal", BottomLeadX/2, BottomLeadY/2, BottomLeadZ/2);
  G4Material* CopperMain = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * BoxBottomLead = new G4LogicalVolume(boxBottomLeadFinal, CopperMain,"BoxBottomLead");

  /*------InsideLead------*/

  G4double boxInsideX = 304.8*mm;
  G4double boxInsideY = 304.8*mm;
  G4double boxInsideZ = 203.2*mm;
  G4double rmBoxX = 203.2*mm;
  G4double rmBoxY = 203.2*mm;
  G4double rmBoxZ = 203.2*mm;


  G4Box* boxInside = new G4Box("BoxInside", boxInsideX/2, boxInsideY/2, boxInsideZ/2);
  G4Box* rmBoxInside = new G4Box("rmBoxInside", rmBoxX/2, rmBoxY/2, rmBoxZ);

  G4ThreeVector InsideVect = G4ThreeVector(0,0,0);
  G4RotationMatrix* rot0Inside = new G4RotationMatrix;
  G4Transform3D InsideTr = G4Transform3D(*rot0Inside, InsideVect);

  G4SubtractionSolid* InsideLeadFinal = new G4SubtractionSolid("InsideLeadFinal", boxInside, rmBoxInside, InsideTr);

  G4LogicalVolume* InsideLead1 = new G4LogicalVolume(InsideLeadFinal, CopperMain, "InsideLead1");
  G4LogicalVolume* InsideLead2 = new G4LogicalVolume(InsideLeadFinal, CopperMain, "InsideLead2");

  /*-------------TopLead-----------*/

  G4double TopLeadX = 304.8*mm;
  G4double TopLeadY = 304.8*mm;
  G4double TopLeadZ = 25.4*mm;

  G4Box* boxTopLeadFinal = new G4Box("boxTopLeadFinal", TopLeadX/2, TopLeadY/2, TopLeadZ/2);


  G4LogicalVolume * BoxTopLead = new G4LogicalVolume(boxTopLeadFinal, CopperMain,"BoxTopLead");

  /*---------Placement-------*/



  G4Material* Air = G4Material::GetMaterial("G4_AIR");
  G4LogicalVolume* OutterLead = new G4LogicalVolume(boxOutterLead, Air, "OutterLead");

  G4LogicalVolume* Assembly1LV = GetConstructionAssembly1();
  G4LogicalVolume* Assembly2LV = GetConstructionAssembly2();

  /*---------BoxBottomLeadPos-------*/

  G4double BoxBottomLeadZ = -217.424*mm;
  G4ThreeVector BoxBottomLeadVect = G4ThreeVector(0,0,BoxBottomLeadZ);

  /*------Assembly1Pos------*/
  G4double Assembly1Z = BoxBottomLeadZ + 26.187*mm;
  G4ThreeVector Assembly1Vect = G4ThreeVector(0,0,Assembly1Z);

  /*------InsideLead1Pos------*/
  G4double InsideLead1Z = Assembly1Z + 102.3874*mm;
  G4ThreeVector InsideLead1Vect = G4ThreeVector(0,0,InsideLead1Z);

  /*------Assembly2Pos----*/
  G4double Assembly2Z = InsideLead1Z + 102.3874*mm;
  G4ThreeVector Assembly2Vect = G4ThreeVector(0,0,Assembly2Z);

  /*-----InsideLead2Pos-----*/
  G4double InsideLead2Z = Assembly2Z + 102.3874*mm;
  G4ThreeVector InsideLead2Vect = G4ThreeVector(0,0,InsideLead2Z);

  /*------TopLeadPos-----*/
  G4double TopLeadPosZ = InsideLead2Z + 114.3*mm;
  G4ThreeVector TopLeadVect = G4ThreeVector(0,0,TopLeadPosZ);



  G4PVPlacement* Assembly1PV = new G4PVPlacement(0, Assembly1Vect, Assembly1LV, "Assembly1PV", OutterLead, false, 0, false);
  G4PVPlacement* Assembly2PV = new G4PVPlacement(0, Assembly2Vect, Assembly2LV, "Assembly2PV", OutterLead, false, 0, false);
  G4PVPlacement* BoxTopLeadPV = new G4PVPlacement(0, TopLeadVect, BoxTopLead, "BoxTopLeadPV", OutterLead, false, 0, false);
  G4PVPlacement* BoxBottomLeadPV = new G4PVPlacement(0, BoxBottomLeadVect, BoxBottomLead, "BoxBottomLeadPV", OutterLead, false, 0, false);
  G4PVPlacement* InsideLead1PV = new G4PVPlacement(0, InsideLead1Vect, InsideLead1, "InsideLead1PV", OutterLead, false, 0, false);
  G4PVPlacement* InsideLead2PV = new G4PVPlacement(0, InsideLead2Vect, InsideLead2, "InsideLead2PV", OutterLead, false, 0, false);
  return OutterLead;

}

G4LogicalVolume* GetConstructionAssembly1()
{
  G4double boxAssembly1X = 303.53*mm;
  G4double boxAssembly1Y = 303.53*mm;
  G4double boxAssembly1Z = 36.576*mm;

  G4Box* boxAssembly1 = new G4Box("BoxAssembly1", boxAssembly1X, boxAssembly1Y, boxAssembly1Z);

  G4LogicalVolume* RestraintSheetLV = GetConstructionRestraintSheet();
  G4LogicalVolume* RestraintBlocks1LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks2LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks3LV =  GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks4LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* CornerBlocks1LV = GetConstructionCornerLead();
  G4LogicalVolume* CornerBlocks2LV = GetConstructionCornerLead();
  G4LogicalVolume* CornerBlocks3LV = GetConstructionCornerLead();
  G4LogicalVolume* CornerBlocks4LV = GetConstructionCornerLead();

  /*--------RestraintBlocks1Pos*-------*/
  G4double RestraintBlocks1Z = 6.3373*mm;
  G4double RestraintBlocks1Y = -101.346*sqrt(2)/2*mm;
  G4double RestraintBlocks1X = -101.346*sqrt(2)/2*mm;
  G4ThreeVector RestraintBlocks1Vect = G4ThreeVector(RestraintBlocks1X, RestraintBlocks1Y, RestraintBlocks1Z);
  G4ThreeVector uRestraint1 = G4ThreeVector(1,0,0);
  G4ThreeVector vRestraint1 = G4ThreeVector(0,1,0);
  G4ThreeVector wRestraint1 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks1Rot = new G4RotationMatrix(uRestraint1, vRestraint1, wRestraint1);

  /*--------RestraintBlocks2Pos*-------*/
  G4double RestraintBlocks2Z = RestraintBlocks1Z;
  G4double RestraintBlocks2Y = RestraintBlocks1Y;
  G4double RestraintBlocks2X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks2Vect = G4ThreeVector(RestraintBlocks2X, RestraintBlocks2Y, RestraintBlocks2Z);
  G4ThreeVector uRestraint2 = G4ThreeVector(0,-1,0);
  G4ThreeVector vRestraint2 = G4ThreeVector(1,0,0);
  G4ThreeVector wRestraint2 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks2Rot = new G4RotationMatrix(uRestraint2, vRestraint2, wRestraint2);

  /*--------RestraintBlocks3Pos*-------*/
  G4double RestraintBlocks3Z = RestraintBlocks1Z;
  G4double RestraintBlocks3Y = -RestraintBlocks1Y;
  G4double RestraintBlocks3X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks3Vect = G4ThreeVector(RestraintBlocks3X, RestraintBlocks3Y, RestraintBlocks3Z);
  G4ThreeVector uRestraint3 = G4ThreeVector(-1,0,0);
  G4ThreeVector vRestraint3 = G4ThreeVector(0,-1,0);
  G4ThreeVector wRestraint3 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks3Rot = new G4RotationMatrix(uRestraint3, vRestraint3, wRestraint3);

  /*--------RestraintBlocks4Pos*-------*/
  G4double RestraintBlocks4Z = RestraintBlocks1Z;
  G4double RestraintBlocks4Y = -RestraintBlocks1Y;
  G4double RestraintBlocks4X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks4Vect = G4ThreeVector(RestraintBlocks4X, RestraintBlocks4Y, RestraintBlocks4Z);
  G4ThreeVector uRestraint4 = G4ThreeVector(0,1,0);
  G4ThreeVector vRestraint4 = G4ThreeVector(-1,0,0);
  G4ThreeVector wRestraint4 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks4Rot = new G4RotationMatrix(uRestraint4, vRestraint4, wRestraint4);

  /*-------CornerBlocks1Pos--------*/
  G4double CornerBlocks1Z = RestraintBlocks1Z + 17.4625*mm;
  G4double CornerBlocks1Y = RestraintBlocks1Y;
  G4double CornerBlocks1X = RestraintBlocks1X;
  G4ThreeVector CornerBlocks1Vect = G4ThreeVector(CornerBlocks1X, CornerBlocks1Y, CornerBlocks1Z);
  G4ThreeVector uCorner1 = G4ThreeVector(1,0,0);
  G4ThreeVector vCorner1 = G4ThreeVector(0,1,0);
  G4ThreeVector wCorner1 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks1Rot = new G4RotationMatrix(uCorner1, vCorner1, wCorner1);

  /*-------CornerBlocks2Pos--------*/
  G4double CornerBlocks2Z = CornerBlocks1Z;
  G4double CornerBlocks2Y = RestraintBlocks2Y;
  G4double CornerBlocks2X = RestraintBlocks2X;
  G4ThreeVector CornerBlocks2Vect = G4ThreeVector(CornerBlocks2X, CornerBlocks2Y, CornerBlocks2Z);
  G4ThreeVector uCorner2 = G4ThreeVector(0,-1,0);
  G4ThreeVector vCorner2 = G4ThreeVector(1,0,0);
  G4ThreeVector wCorner2 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks2Rot = new G4RotationMatrix(uCorner2, vCorner2, wCorner2);

  /*-------CornerBlocks3Pos--------*/
  G4double CornerBlocks3Z = CornerBlocks1Z;
  G4double CornerBlocks3Y = RestraintBlocks3Y;
  G4double CornerBlocks3X = RestraintBlocks3X;
  G4ThreeVector CornerBlocks3Vect = G4ThreeVector(CornerBlocks3X, CornerBlocks3Y, CornerBlocks3Z);
  G4ThreeVector uCorner3 = G4ThreeVector(-1,0,0);
  G4ThreeVector vCorner3 = G4ThreeVector(0,-1,0);
  G4ThreeVector wCorner3 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks3Rot = new G4RotationMatrix(uCorner3 ,vCorner3, wCorner3);

  /*-------CornerBlocks4Pos--------*/
  G4double CornerBlocks4Z = CornerBlocks1Z;
  G4double CornerBlocks4Y = RestraintBlocks4Y;
  G4double CornerBlocks4X = RestraintBlocks4X;
  G4ThreeVector CornerBlocks4Vect = G4ThreeVector(CornerBlocks4X, CornerBlocks4Y, CornerBlocks4Z);
  G4ThreeVector uCorner4 = G4ThreeVector(0,1,0);
  G4ThreeVector vCorner4 = G4ThreeVector(-1,0,0);
  G4ThreeVector wCorner4 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks4Rot = new G4RotationMatrix(uCorner4, vCorner4, wCorner4);


  G4Material* Air = G4Material::GetMaterial("G4_AIR");
  G4LogicalVolume* Assembly1 = new G4LogicalVolume(boxAssembly1, Air, "OutterLead");



  G4PVPlacement* RestraintSheetPV = new G4PVPlacement(0, G4ThreeVector(0,0,0), RestraintSheetLV, "RestraintSheetPV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks1PV = new G4PVPlacement(RestraintBlocks1Rot, RestraintBlocks1Vect, RestraintBlocks1LV, "RestraintBlocks1PV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks2PV = new G4PVPlacement(RestraintBlocks2Rot, RestraintBlocks2Vect, RestraintBlocks2LV, "RestraintBlocks2PV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks3PV = new G4PVPlacement(RestraintBlocks3Rot, RestraintBlocks3Vect, RestraintBlocks3LV, "RestraintBlocks3PV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks4PV = new G4PVPlacement(RestraintBlocks4Rot, RestraintBlocks4Vect, RestraintBlocks4LV, "RestraintBlocks4PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks1PV = new G4PVPlacement(CornerBlocks1Rot, CornerBlocks1Vect, CornerBlocks1LV, "CornerBlocks1PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks2PV = new G4PVPlacement(CornerBlocks2Rot, CornerBlocks2Vect, CornerBlocks2LV, "CornerBlocks2PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks3PV = new G4PVPlacement(CornerBlocks3Rot, CornerBlocks3Vect, CornerBlocks3LV, "CornerBlocks3PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks4PV = new G4PVPlacement(CornerBlocks4Rot, CornerBlocks4Vect, CornerBlocks4LV, "CornerBlocks4PV", Assembly1, false, 0, false);

  return Assembly1;

}

G4LogicalVolume* GetConstructionAssembly2()
{
  G4double boxAssembly2X = 303.53*mm;
  G4double boxAssembly2Y = 303.53*mm;
  G4double boxAssembly2Z = 36.576*mm;

  G4Box* boxAssembly2 = new G4Box("BoxAssembly2", boxAssembly2X, boxAssembly2Y, boxAssembly2Z);


  G4LogicalVolume* RestraintSheetLV = GetConstructionRestraintSheet();
  G4LogicalVolume* RestraintBlocks1LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks2LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks3LV =  GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks4LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks5LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks6LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks7LV =  GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks8LV = GetConstructionRestraintBlocks();


  /*--------RestraintBlocks1Pos*-------*/
  G4double RestraintBlocks1Z = 6.3373*mm;
  G4double RestraintBlocks1Y = -101.346*sqrt(2)/2*mm;
  G4double RestraintBlocks1X = -101.346*sqrt(2)/2*mm;
  G4ThreeVector RestraintBlocks1Vect = G4ThreeVector(RestraintBlocks1X, RestraintBlocks1Y, RestraintBlocks1Z);
  G4ThreeVector uRestraint1 = G4ThreeVector(1,0,0);
  G4ThreeVector vRestraint1 = G4ThreeVector(0,1,0);
  G4ThreeVector wRestraint1 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks12Rot = new G4RotationMatrix(uRestraint1, vRestraint1, wRestraint1);

  /*--------RestraintBlocks2Pos*-------*/
  G4double RestraintBlocks2Z = -RestraintBlocks1Z;
  G4double RestraintBlocks2Y = RestraintBlocks1Y;
  G4double RestraintBlocks2X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks2Vect = G4ThreeVector(RestraintBlocks2X, RestraintBlocks2Y, RestraintBlocks2Z);

  /*--------RestraintBlocks3Pos*-------*/
  G4double RestraintBlocks3Z = RestraintBlocks1Z;
  G4double RestraintBlocks3Y = RestraintBlocks1Y;
  G4double RestraintBlocks3X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks3Vect = G4ThreeVector(RestraintBlocks3X, RestraintBlocks3Y, RestraintBlocks3Z);
  G4ThreeVector uRestraint3 = G4ThreeVector(0,-1,0);
  G4ThreeVector vRestraint3 = G4ThreeVector(1,0,0);
  G4ThreeVector wRestraint3 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks34Rot = new G4RotationMatrix(uRestraint3, vRestraint3, wRestraint3);

  /*--------RestraintBlocks4Pos*-------*/
  G4double RestraintBlocks4Z = -RestraintBlocks1Z;
  G4double RestraintBlocks4Y = RestraintBlocks1Y;
  G4double RestraintBlocks4X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks4Vect = G4ThreeVector(RestraintBlocks4X, RestraintBlocks4Y, RestraintBlocks4Z);

  /*--------RestraintBlocks5Pos*-------*/
  G4double RestraintBlocks5Z = RestraintBlocks1Z;
  G4double RestraintBlocks5Y = -RestraintBlocks1Y;
  G4double RestraintBlocks5X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks5Vect = G4ThreeVector(RestraintBlocks5X, RestraintBlocks5Y, RestraintBlocks5Z);
  G4ThreeVector uRestraint5 = G4ThreeVector(-1,0,0);
  G4ThreeVector vRestraint5 = G4ThreeVector(0,-1,0);
  G4ThreeVector wRestraint5 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks56Rot = new G4RotationMatrix(uRestraint5, vRestraint5, wRestraint5);

  /*--------RestraintBlocks6Pos*-------*/
  G4double RestraintBlocks6Z = -RestraintBlocks1Z;
  G4double RestraintBlocks6Y = -RestraintBlocks1Y;
  G4double RestraintBlocks6X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks6Vect = G4ThreeVector(RestraintBlocks6X, RestraintBlocks6Y, RestraintBlocks6Z);

  /*--------RestraintBlocks7Pos*-------*/
  G4double RestraintBlocks7Z = RestraintBlocks1Z;
  G4double RestraintBlocks7Y = -RestraintBlocks1Y;
  G4double RestraintBlocks7X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks7Vect = G4ThreeVector(RestraintBlocks7X, RestraintBlocks7Y, RestraintBlocks7Z);
  G4ThreeVector uRestraint7 = G4ThreeVector(0,1,0);
  G4ThreeVector vRestraint7 = G4ThreeVector(-1,0,0);
  G4ThreeVector wRestraint7 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks78Rot = new G4RotationMatrix(uRestraint7, vRestraint7, wRestraint7);

  /*--------RestraintBlocks8Pos*-------*/
  G4double RestraintBlocks8Z = -RestraintBlocks1Z;
  G4double RestraintBlocks8Y = -RestraintBlocks1Y;
  G4double RestraintBlocks8X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks8Vect = G4ThreeVector(RestraintBlocks8X, RestraintBlocks8Y, RestraintBlocks8Z);


  G4Material* Air = G4Material::GetMaterial("G4_AIR");
  G4LogicalVolume* Assembly2 = new G4LogicalVolume(boxAssembly2, Air, "OutterLead");


  G4PVPlacement* RestraintSheetPV = new G4PVPlacement(0, G4ThreeVector(0,0,0), RestraintSheetLV, "RestraintSheetPV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks1PV = new G4PVPlacement(RestraintBlocks12Rot, RestraintBlocks1Vect, RestraintBlocks1LV, "RestraintBlocks1PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks2PV = new G4PVPlacement(RestraintBlocks12Rot, RestraintBlocks2Vect, RestraintBlocks2LV, "RestraintBlocks2PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks3PV = new G4PVPlacement(RestraintBlocks34Rot, RestraintBlocks3Vect, RestraintBlocks3LV, "RestraintBlocks3PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks4PV = new G4PVPlacement(RestraintBlocks34Rot, RestraintBlocks4Vect, RestraintBlocks4LV, "RestraintBlocks4PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks5PV = new G4PVPlacement(RestraintBlocks56Rot, RestraintBlocks5Vect, RestraintBlocks5LV, "RestraintBlocks5PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks6PV = new G4PVPlacement(RestraintBlocks56Rot, RestraintBlocks6Vect, RestraintBlocks6LV, "RestraintBlocks6PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks7PV = new G4PVPlacement(RestraintBlocks78Rot, RestraintBlocks7Vect, RestraintBlocks7LV, "RestraintBlocks7PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks8PV = new G4PVPlacement(RestraintBlocks78Rot, RestraintBlocks8Vect, RestraintBlocks8LV, "RestraintBlocks8PV", Assembly2, false, 0, false);


  return Assembly2;
}

G4LogicalVolume* GetConstructionCornerLead()
{
  G4double bigBoxX = 50.8*mm;
  G4double bigBoxY = 50.8*mm;
  G4double bigBoxZ = 25.4*mm;
  G4double rmTubR= 106.68*mm;
  G4double rmTubH = 25.4*mm;
  G4double angle0 = 0;
  G4double angle360 =  M_PI*2+1;

  G4Box *bigBox = new G4Box("BigBox", bigBoxX/2, bigBoxY/2, bigBoxZ/2);
  G4Tubs *rmTub = new G4Tubs("RmTub", angle0,rmTubR, rmTubH,angle0, angle360 );

  G4RotationMatrix *rot0 = new G4RotationMatrix;
  G4double rmTubVecXY = 76.2*mm;
  G4ThreeVector rmTubVec = G4ThreeVector(rmTubVecXY, rmTubVecXY,0);
  G4Transform3D rmTubTr = G4Transform3D(*rot0, rmTubVec);

  G4SubtractionSolid* cornerLeadFinal = new G4SubtractionSolid("CornerLeadFinal", bigBox, rmTub, rmTubTr);
  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * cornerLead = new G4LogicalVolume(cornerLeadFinal, Copper,"CornerLead");

  return cornerLead;

}

G4LogicalVolume* GetConstructionRestraintBlocks()
{
  G4double bigBoxX = 50.8*mm;
  G4double bigBoxY = 50.8*mm;
  G4double bigBoxZ = 9.525*mm;
  G4double rmBoxX = 66.294;
  G4double rmBoxY = 66.294;
  G4double rmBoxZ = 66.294;

  G4Box * bigBox = new G4Box("BigBox", bigBoxX/2, bigBoxY/2, bigBoxZ/2);
  G4Box * rmBox = new G4Box("RmBox", rmBoxX/2, rmBoxY, rmBoxZ);

  G4RotationMatrix * rot45 = new G4RotationMatrix;
  rot45->rotateZ(M_PI/4);
  G4double rmBoxVecX = 46.99/2*mm;
  G4double rmBoxVecY = 46.99/2*mm;
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxVecX,rmBoxVecY,0);
  G4Transform3D rmBoxTr = G4Transform3D(*rot45, rmBoxVec);


  G4SubtractionSolid* restraintBlocksFinal = new G4SubtractionSolid("RestraintBlocksFinal", bigBox, rmBox, rmBoxTr);
  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * restraintBlocks = new G4LogicalVolume(restraintBlocksFinal, Copper,"RestraintBlocks");

  return restraintBlocks;



}

G4LogicalVolume* GetConstructionRestraintSheet()
{
  G4double bigBoxX = 303.53*mm;
  G4double bigBoxY = 303.53*mm;
  G4double bigBoxZ = 1.5748*mm;
  G4double rmTubR = 209.55/2*mm;
  G4double rmTubH = 1.5748*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;

  G4Box * bigBox = new G4Box("BigBox", bigBoxX/2, bigBoxY/2, bigBoxZ/2);
  G4Tubs* rmTub = new G4Tubs("RmTub", angle0, rmTubR, rmTubH, angle0, angle360);
  G4RotationMatrix* rot0= new G4RotationMatrix;
  G4ThreeVector tubVec = G4ThreeVector(0,0,0);
  G4Transform3D tubTR = G4Transform3D(*rot0, tubVec);

  G4SubtractionSolid * restraintSheetFinal = new G4SubtractionSolid("RestraintSheetFinal", bigBox, rmTub, tubTR);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * restraintSheet = new G4LogicalVolume(restraintSheetFinal, Copper,"RestraintSheet");

  return restraintSheet;

}
