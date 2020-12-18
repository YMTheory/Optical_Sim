
// $Id: JunoDetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file JunoDetectorConstruction.cc
/// \brief Implementation of the JunoDetectorConstruction class

#include "JunoDetectorConstruction.hh"

#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
//#include "G4UnionSolid.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4GeometryManager.hh"
#include "G4OpticalSurface.hh"
#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


JunoDetectorConstruction::JunoDetectorConstruction()
    : G4VUserDetectorConstruction(),
    fCheckOverlaps(true)
{ 
    //fMessenger = new JunoDetectorConstructionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JunoDetectorConstruction::~JunoDetectorConstruction()
{ ; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



G4VPhysicalVolume* JunoDetectorConstruction::Construct()
{   

    DefineMaterials();

    return DefineVolumes();
}

void JunoDetectorConstruction::DefineMaterials()
{
    
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    air = nist->FindOrBuildMaterial("G4_AIR");
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* JunoDetectorConstruction::DefineVolumes()
{

    //Definition of some constants
    //
    G4double worldLength = 25.*m;
    G4double LSRadius    = 17.7*m;
    G4double waterRadius = 21.*mm;


    //////////////////////////////////////////////////////////////////////////////////////////////

    // Visualization attributes
    G4VisAttributes* lsVisAtt = new G4VisAttributes(G4Colour(0, 1, 1));
    //boxVisAtt->SetForceSolid ();
    G4VisAttributes* waterVisAtt = new G4VisAttributes(G4Colour(1, 0, 1));
    //tubVisAtt->SetForceSolid();
    
    //////////////////////////////////////////////////////////////////////////////////////////////


    // Geometry Construction Part

    //World
    //
    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);
    G4Box* worldS
        = new G4Box("world",                                    //its name
                    worldLength/2,worldLength/2,worldLength/2); //its size
    G4LogicalVolume* worldLV
        = new G4LogicalVolume(
                     worldS,   //its solid
                     //air,      //its material
                     air,
                     "World"); //its name
  
    G4VPhysicalVolume* worldPV
     = new G4PVPlacement(
                     0,               // no rotation
                     G4ThreeVector(), // at (0,0,0)
                     worldLV,         // its logical volume
                     "World",         // its name
                     0,               // its mother  volume
                     false,           // no boolean operations
                     0,               // copy number
                     fCheckOverlaps); // checking overlaps 




    return worldPV;

}


//void JunoDetectorConstruction::ConstructSDandField()
//{
//    G4cout << " ----> Add Sensitive Detector " << G4endl;
//    // Sensitive Detector
//
//    auto pmtSD
//        =  new JunoPmtSD("PmtSD", "PmtHitsCollection", 1); //fNofLayers);
//    G4SDManager::GetSDMpointer()->AddNewDetector(pmtSD);
//    SetSensitiveDetector("logicPmt", pmtSD);
//
//}




