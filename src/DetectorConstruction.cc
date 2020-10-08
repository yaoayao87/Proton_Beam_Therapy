#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"
//#include "PhysicalConstants.hh"


//****************************************************************************//

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//****************************************************************************//

DetectorConstruction::~DetectorConstruction()
{ }

//****************************************************************************//

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  //
  // Construction of Cylindrical World Volume
  //

  G4double density     = 1.e-25*g/cm3;    //from PhysicalConstants.h
  G4double pressure    = 3.e-18*pascal;
  G4double temperature = 2.73*kelvin;
  G4double z;
  G4double a;
  new G4Material("Galactic", z=1., a=1.008*g/mole, density,
                                kStateGas,temperature,pressure);
  G4Material* World_mat = nist->FindOrBuildMaterial("Galactic");

  G4String  nameWorld = "World";
  G4double  in_radius_World = 0*mm;
  G4double  out_radius_World = 300*mm;
  G4double  length_World = 2000*mm;
  G4double  starting_angle_World = 0;
  G4double  segment_angle_World = 360*degree;


  G4Tubs* solidWorld =
    new G4Tubs(nameWorld, in_radius_World, out_radius_World, 0.5*length_World, starting_angle_World, segment_angle_World);

  G4LogicalVolume* logicalWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        World_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physicalWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicalWorld,          //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Construction of Cylindrical Target
  //

  G4Material* Target_mat = nist->FindOrBuildMaterial("G4_WATER");

  G4String  nameTarget = "Target";
  G4double  in_radius_Target = 0*mm;
  G4double  out_radius_Target = 200*mm;
  G4double  length_Target = 800*mm;
  G4double  starting_angle_Target = 0;
  G4double  segment_angle_Target = 360*degree;


  G4Tubs* solidTarget =
    new G4Tubs(nameTarget, in_radius_Target, out_radius_Target, 0.5*length_Target, starting_angle_Target, segment_angle_Target);

  G4LogicalVolume* logicalTarget =
    new G4LogicalVolume(solidTarget,          //its solid
                        Target_mat,           //its material
                        "Target");            //its name

  G4VPhysicalVolume* physicalTarget =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0, 0, 400*mm),       //at (0,0,0)
                      logicalTarget,         //its logical volume
                      "Target",              //its name
                      logicalWorld,          //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  a = 207.2 *g/mole;
  density = 11.35 *g/cm3;
  new G4Material("Lead", z=82., a, density);
  G4Material* Grater_mat = nist->FindOrBuildMaterial("Lead");

  G4String  nameGrater = "Grater";
  G4double  in_radius_Grater = 1.5*mm;
  G4double  out_radius_Grater = 200*mm;
  G4double  length_Grater = 200*mm;
  G4double  starting_angle_Grater = 0;
  G4double  segment_angle_Grater = 360*degree;


  G4Tubs* solidGrater =
    new G4Tubs(nameGrater, in_radius_Grater, out_radius_Grater, 0.5*length_Grater, starting_angle_Grater, segment_angle_Grater);

  G4LogicalVolume* logicalGrater =
    new G4LogicalVolume(solidGrater,          //its solid
                        Grater_mat,           //its material
                        "Grater");            //its name

  G4VPhysicalVolume* physicalGrater =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,-500*mm),       //at (0,0,0)
                      logicalGrater,         //its logical volume
                      "Grater",              //its name
                      logicalWorld,          //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  // Set Target as scoring volume
  fScoringVolume = logicalTarget;

  //always return the physical World
  return physicalWorld;
}

//****************************************************************************//
