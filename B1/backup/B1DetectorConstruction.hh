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
// $Id: B1DetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file B1DetectorConstruction.hh
/// \brief Definition of the B1DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "B1DetectorConstructionMessenger.hh"

class G4VPhysicalVolume;

/// Detector construction class to define materials and geometry.

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        B1DetectorConstruction();
        virtual ~B1DetectorConstruction();

        virtual G4VPhysicalVolume* Construct();
        virtual void ConstructSDandField();

        void DefineMaterials();
        G4VPhysicalVolume* DefineVolumes();


    private:
        B1DetectorConstructionMessenger* fMessenger;
    
    public:
        G4double GetCellSize() { return fCellXYSize; }
        void SetCellXYSize(G4double size) { fCellXYSize = size; }

        G4double GetPmtSize()  { return fPmtSize;  }
        void SetPmtSize(G4double size) { fPmtSize = size; }

        G4ThreeVector GetPmtPos()  { return fPmtPos; }
        void SetPmtPos(G4ThreeVector pos) { fPmtPos = pos; }

        G4double GetRindex()  { return fRindex; }
        void SetRindex(G4double rindex) { fRindex = rindex; }



    private:
        G4bool fCheckOverlaps;
        G4int fNofLayers;

        G4Material* world_mat;
        G4Material* glass_mat;

        G4double        fRindex;
        G4double        fCellXYSize;
        G4double        fPmtSize;
        G4ThreeVector   fPmtPos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

