//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1DetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "B1PmtSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
    fNofLayers(1)
{ 
    fCellSize = 10.*mm;
    fPmtSize  = 3.*cm;
    fPmtPos   = G4ThreeVector(0, 0, 0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::DefineMaterials()
{
  // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    world_mat = nist->FindOrBuildMaterial("G4_AIR");
    
    G4int nEntries = 2;
    G4String name;
    G4double density;
    G4int compNum;
    glass_mat = new G4Material(name="glass_mat", density=2.23*g/cm3, compNum=2);
    G4MaterialPropertiesTable* glass_mpt = new G4MaterialPropertiesTable();
    G4double glass_PhotonEnergy[nEntries] = {2.884*eV, 3.024*eV};
    G4double glass_RIndex[nEntries] = {1.0, 1.0};
    glass_mpt->AddProperty("RINDEX", glass_PhotonEnergy, glass_RIndex, nEntries);
    glass_mat->SetMaterialPropertiesTable(glass_mpt);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::DefineVolumes()
{  
  
  // World
  //
  G4double world_sizeXY = 2.0*m;
  G4double world_sizeZ  = 2.0*m;
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       //overlaps checking
                     

  // design of cuvette
  //
  G4double outcell_sizeXY = 10.*mm; //6.25*mm;
  G4double outcell_sizeZ  = 22.5*mm;
  G4Box* solidOutCell = 
      new G4Box("solidOutCell", outcell_sizeXY, outcell_sizeXY, outcell_sizeZ);
  G4LogicalVolume* logicOutCell = 
      new G4LogicalVolume(solidOutCell,
                          glass_mat,
                          "logicOutCell");
  G4VPhysicalVolume* phyOutCell = 
      new G4PVPlacement(0, 
                        G4ThreeVector(0, 0, 0),
                        logicOutCell,
                        "phyOutCell",
                        logicWorld,
                        false,
                        0,
                        fCheckOverlaps);

    // design of PMT
    //
    G4double pi = 3.14159265;
    G4double pmt_Radius = 3.0*cm;
    G4double pmt_Length = 20.0*cm;
    G4Tubs* solidPmt = new G4Tubs("solidPmt", 0, pmt_Radius, pmt_Length/2, 0, 2*pi);
    G4LogicalVolume* logicPmt = 
        new G4LogicalVolume( solidPmt,
                             world_mat,
                             "logicPmt");
    G4RotationMatrix* Rot = new G4RotationMatrix();
    Rot->rotateY(pi/2*rad);

    G4VPhysicalVolume* physPmt = 
        new G4PVPlacement(Rot,
                          G4ThreeVector(410*mm, 0., 0.),
                          //G4ThreeVector(424.75*mm, 0., 0.),
                          logicPmt,
                          "physPmt",
                          logicWorld,
                          false,
                          0,
                          fCheckOverlaps);

    // Visualization attributes
    G4VisAttributes* boxVisAtt = new G4VisAttributes(G4Colour(0, 1, 1));
    boxVisAtt->SetForceSolid ();
    G4VisAttributes* tubVisAtt = new G4VisAttributes(G4Colour(1, 0, 1));
    tubVisAtt->SetForceSolid();
    logicOutCell   -> SetVisAttributes(boxVisAtt);
    logicPmt       -> SetVisAttributes(tubVisAtt);


  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
   DefineMaterials();
   
   return DefineVolumes();
}


void B1DetectorConstruction::ConstructSDandField()
{
    G4cout << " ----> Add Sensitive Detector " << G4endl;
    // Sensitive Detector

    auto pmtSD
      =  new B1PmtSD("PmtSD", "PmtHitsCollection", fNofLayers);
    G4SDManager::GetSDMpointer()->AddNewDetector(pmtSD);
    SetSensitiveDetector("logicPmt", pmtSD);

}



