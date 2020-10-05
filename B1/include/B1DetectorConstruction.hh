
// $Id: B1DetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file B1DetectorConstruction.hh
/// \brief Definition of the B1DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "B1DetectorConstructionMessenger.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

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
        //G4LogicalVolume* logicPMT;
        G4bool fCheckOverlaps;

        G4Material* world_mat;
        G4Material* glass_mat;
        G4Material* fPMMA;
        G4Material* fblack;
        G4Material* fmetal;
        G4Material* air;

        G4double        fRindex;
        G4double        fCellXYSize;
        G4double        fPmtSize;
        G4ThreeVector   fPmtPos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

