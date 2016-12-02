#include "DAMICDetectorInnerLead.hh"
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


G4LogicalVolume* GetConstructionInnerLead()
{
  G4double InnerLeadR = 189.23/2*mm;
  G4double InnerLeadH = 192.532*mm;
  G4double A0 = 0;
  G4double A360 = 2*M_PI+1;

  G4Tubs* InnerLeadTub = new G4Tubs("InnerLeadTub", A0, InnerLeadR*2, InnerLeadH, A0, A360);

  G4Material* Air = G4Material::GetMaterial("G4_AIR");
  G4LogicalVolume* InnerLeadLV = new G4LogicalVolume(InnerLeadTub, Air,"InnerLeadLV");

  G4LogicalVolume* AncientLead1LV = GetConstructionAncientLead1();
  G4LogicalVolume* AncientLead2LV = GetConstructionAncientLead2();
  G4LogicalVolume* BoxMountingPlateLV = GetConstructionBoxMountingPlate();
  G4LogicalVolume* GoodLead1LV = GetConstructionGoodLead();
  G4LogicalVolume* GoodLead2LV = GetConstructionGoodLead();
  G4LogicalVolume* GoodLead3LV = GetConstructionGoodLead();
  G4LogicalVolume* SpacerPlate1LV = GetConstructionSpacerPlate();
  G4LogicalVolume* SpacerPlate2LV = GetConstructionSpacerPlate();


  /*-----------SpacerPlate1Pos--------*/
  G4double PosSpacerPlate1Z = 0;
  G4double PosSpacerPlate1Y = 0;
  G4double PosSpacerPlate1X = 0;
  G4ThreeVector VectSpacerPlate1 = G4ThreeVector(PosSpacerPlate1X, PosSpacerPlate1Y, PosSpacerPlate1Z);

  /*--------GoodLead1Pos---------*/
  G4double PosGoodLead1Z = 26.924*mm;
  G4double PosGoodLead1Y = 0;
  G4double PosGoodLead1X = 0;
  G4ThreeVector VectGoodLead1 = G4ThreeVector(PosGoodLead1X, PosGoodLead1Y, PosGoodLead1Z);

  /*--------GoodLead2Pos---------*/
  G4double PosGoodLead2Z = -PosGoodLead1Z;
  G4double PosGoodLead2Y = 0;
  G4double PosGoodLead2X = 0;
  G4ThreeVector VectGoodLead2 = G4ThreeVector(PosGoodLead2X, PosGoodLead2Y, PosGoodLead2Z);

  /*--------GoodLead3Pos---------*/
  G4double PosGoodLead3Z = PosGoodLead2Z - 50.8*mm;
  G4double PosGoodLead3Y = 0;
  G4double PosGoodLead3X = 0;
  G4ThreeVector VectGoodLead3 = G4ThreeVector(PosGoodLead3X, PosGoodLead3Y, PosGoodLead3Z);

  /*-----------SpacerPlate2Pos--------*/
  G4double PosSpacerPlate2Z = PosGoodLead3Z - 26.924*mm;
  G4double PosSpacerPlate2Y = 0;
  G4double PosSpacerPlate2X = 0;
  G4ThreeVector VectSpacerPlate2 = G4ThreeVector(PosSpacerPlate2X, PosSpacerPlate2Y, PosSpacerPlate2Z);

  /*-------AncientLead2Pos------*/
  G4double AncientLead2Z = PosGoodLead1Z+38.1*mm;
  G4double AncientLead2Y = 0;
  G4double AncientLead2X = 0;
  G4double COSSIN3P4 = sqrt(2)/2;
  G4ThreeVector VectAncientLead2 = G4ThreeVector(AncientLead2X, AncientLead2Y, AncientLead2Z);
  G4ThreeVector uAncient2 = G4ThreeVector(-COSSIN3P4,-COSSIN3P4,0);
  G4ThreeVector vAncient2 = G4ThreeVector(COSSIN3P4,-COSSIN3P4,0);
  G4ThreeVector wAncient2 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RotAncientLead2 = new G4RotationMatrix(uAncient2,vAncient2,wAncient2);

  /*-------AncientLead1Pos------*/
  G4double AncientLead1Z = AncientLead2Z;
  G4double AncientLead1Y = 0;
  G4double AncientLead1X = 0;
  G4ThreeVector VectAncientLead1 = G4ThreeVector(AncientLead1X, AncientLead1Y, AncientLead1Z);
  G4ThreeVector uAncient1 = G4ThreeVector(COSSIN3P4,COSSIN3P4,0);
  G4ThreeVector vAncient1 = G4ThreeVector(-COSSIN3P4,COSSIN3P4,0);
  G4ThreeVector wAncient1 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RotAncientLead1 = new G4RotationMatrix(uAncient1,vAncient1,wAncient1);

  /*--------BoxMountingPlate-------*/
  G4double BoxMountingPlateZ = AncientLead2Z + 17.526*mm;
  G4double BoxMountingPlateY = 0;
  G4double BoxMountingPlateX = 0;
  G4ThreeVector VectBoxMountingPlate = G4ThreeVector(BoxMountingPlateX, BoxMountingPlateY, BoxMountingPlateZ);
  G4ThreeVector uPlate = G4ThreeVector(-1,0,0);
  G4ThreeVector vPlate = G4ThreeVector(0,-1,0);
  G4ThreeVector wPlate = G4ThreeVector(0,0,1);
  G4RotationMatrix* RotBoxMountingPlate = new G4RotationMatrix(uPlate,vPlate,wPlate);


  G4PVPlacement* AncientLead1PV = new G4PVPlacement(RotAncientLead1, VectAncientLead1, AncientLead1LV, "AncientLead1PV", InnerLeadLV, false, 0, false);
  G4PVPlacement* AncientLead12PV = new G4PVPlacement(RotAncientLead2, VectAncientLead2, AncientLead2LV, "AncientLead2PV", InnerLeadLV, false, 0, false);
  G4PVPlacement* BoxMountingPlatePV = new G4PVPlacement(RotBoxMountingPlate, VectBoxMountingPlate, BoxMountingPlateLV, "BoxMountingPlatePV", InnerLeadLV, false, 0, false);
  G4PVPlacement* GoodLeadPV1 = new G4PVPlacement(0, VectGoodLead1, GoodLead1LV, "GoodLead1PV", InnerLeadLV, false, 0, false);
  G4PVPlacement* GoodLeadPV2 = new G4PVPlacement(0, VectGoodLead2, GoodLead2LV, "GoodLead2PV", InnerLeadLV, false, 0, false);
  G4PVPlacement* GoodLeadPV3 = new G4PVPlacement(0, VectGoodLead3, GoodLead3LV, "GoodLead3PV", InnerLeadLV, false, 0, false);
  G4PVPlacement* SpacerPlate1PV = new G4PVPlacement(0, VectSpacerPlate1, SpacerPlate1LV, "SpacerPlate1PV", InnerLeadLV, false, 0, false);
  G4PVPlacement* SpacerPlate2PV = new G4PVPlacement(0, VectSpacerPlate2, SpacerPlate2LV, "SpacerPlate2PV", InnerLeadLV, false, 0, false);


  return InnerLeadLV;
}


G4LogicalVolume* GetConstructionAncientLead1()
{
  G4double cylRin = 15.748*mm;
  G4double cylRout = 91.948*mm;
  G4double cylH = 25.4*mm;
  G4double angle0 = 0;
  G4double angle180 = M_PI;

  G4Tubs* cylLead = new G4Tubs("CylLead", cylRin, cylRout, cylH/2, angle0, angle180);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * ancientLead1 = new G4LogicalVolume(cylLead, Copper,"AncientLead1");

  return ancientLead1;


}


G4LogicalVolume* GetConstructionAncientLead2()
{
  G4double cylRin = 15.748*mm;
  G4double cylRout = 91.948*mm;
  G4double cylH = 25.4*mm;
  G4double angle0 = 0;
  G4double angle180 = M_PI;
  G4double rmBoxX = 6.223*mm;
  G4double rmBoxY = 31.75*mm;
  G4double rmBoxZ = 25.4*mm;

  G4Tubs* cylLead = new G4Tubs("CylLead", cylRin, cylRout, cylH/2, angle0, angle180);
  G4Box * rmBox = new G4Box ("rmBox", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix * rotBox = new G4RotationMatrix;
  rotBox->rotateZ(M_PI/4);
  G4double rmBoxVecX = cylRout * cos(M_PI/4);
  G4double rmBoxVecY = cylRout * sin(M_PI/4);
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxVecX, rmBoxVecY, 0);
  G4Transform3D rmBoxTr = G4Transform3D(*rotBox, rmBoxVec);

  G4SubtractionSolid* ancientLead2Final = new G4SubtractionSolid("AncientLead2Final", cylLead, rmBox, rmBoxTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * ancientLead2 = new G4LogicalVolume(ancientLead2Final, Copper,"AncientLead2");

  return ancientLead2;

}

G4LogicalVolume* GetConstructionBoxMountingPlate()
{
  G4double rmCylROut = 127/2*mm;
  G4double rmCylRIn = 28.575/2*mm;
  G4double rmCylH = 6.35*mm;
  G4double cylRIn = 28.575/2*mm;
  G4double cylROut = 185.166/2*mm;
  G4double cylH = 9.652*mm;
  G4double rmBoxX = 9.525*mm;
  G4double rmBoxY = 30.48*mm;
  G4double rmBoxZ = 9.652*mm;
  G4double angle0 = 0;
  G4double angle360 = 2*M_PI+1;

  G4Tubs* rmCyl = new G4Tubs("RmCyl", 0, rmCylROut, rmCylH, angle0, angle360);
  G4Tubs* cyl = new G4Tubs("Cyl", cylRIn, cylROut, cylH/2, angle0, angle360);
  G4Box* rmBox = new G4Box("RmBox", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix *rot0 = new G4RotationMatrix;
  G4double rmCylZ = cylH/2;
  G4double rmBoxXVec = cylROut;
  G4ThreeVector rmCylVec = G4ThreeVector(0,0,rmCylZ);
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxXVec,0,0);
  G4Transform3D rmCylTr = G4Transform3D(*rot0, rmCylVec);
  G4Transform3D rmBoxTr = G4Transform3D(*rot0, rmBoxVec);

  G4SubtractionSolid* boxMountPlate = new G4SubtractionSolid("BoxMountPlate", cyl, rmCyl, rmCylTr);
  G4SubtractionSolid* boxMountPlateFinal = new G4SubtractionSolid("BoxMountPlateFinal", boxMountPlate, rmBox, rmBoxTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * boxMountingPlate = new G4LogicalVolume(boxMountPlateFinal, Copper,"BoxMountingPlate");

  return boxMountingPlate;
}

G4LogicalVolume* GetConstructionGoodLead()
{
  G4double cylRIn = 31.75/2*mm;
  G4double cylROut = 184.15/2*mm;
  G4double cylH = 50.8*mm;
  G4double rmBoxX = 9.525*mm;
  G4double rmBoxY = 30.48*mm;
  G4double rmBoxZ = 50.8*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;

  G4Tubs * cylGood = new G4Tubs("CylGood", cylRIn, cylROut, cylH/2, angle0, angle360);
  G4Box* rmBoxGood = new G4Box("RmBoxGood", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix * rot0 = new G4RotationMatrix;
  G4double rmBoxXVec = -cylROut;
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxXVec, 0, 0);
  G4Transform3D rmBoxTr = G4Transform3D(*rot0, rmBoxVec);

  G4SubtractionSolid * goodLeadFinal = new G4SubtractionSolid("GoodLeadFinal", cylGood, rmBoxGood, rmBoxTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * goodLead = new G4LogicalVolume(goodLeadFinal, Copper,"GoodLead");

  return goodLead;
}

G4LogicalVolume* GetConstructionSpacerPlate()
{
  G4double cylRIn = 28.575/2*mm;
  G4double cylROut = 189.23/2*mm;
  G4double cylH = 3.048*mm;
  G4double rmBoxX = 9.525*mm;
  G4double rmBoxY = 30.48*mm;
  G4double rmBoxZ = 3.048*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;

  G4Tubs * cylGood = new G4Tubs("CylGood", cylRIn, cylROut, cylH/2, angle0, angle360);
  G4Box* rmBoxGood = new G4Box("RmBoxGood", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix * rot0 = new G4RotationMatrix;
  G4double rmBoxXVec = -cylROut;
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxXVec, 0, 0);
  G4Transform3D rmBoxTr = G4Transform3D(*rot0, rmBoxVec);

  G4SubtractionSolid * spacerPlateFinal = new G4SubtractionSolid("SpacerPlateFinal", cylGood, rmBoxGood, rmBoxTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * spacerPlate = new G4LogicalVolume(spacerPlateFinal, Copper,"SpacerPlate");

  return spacerPlate;
}
