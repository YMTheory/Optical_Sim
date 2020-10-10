
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

        void SetAptNumber(G4int number) { fAptNumber = number; } 
        void SetAptSize(G4double *size);
        void SetAptPos(G4double* pos);
        void SetAptShape(G4int* shape); // 0 for round, 1 for square

    private:
        G4LogicalVolume* CellConstruction();
        G4LogicalVolume* TubeConstruction();
        G4LogicalVolume* RoundAptConstruction(G4double, G4double);
        G4LogicalVolume* SquareAptConstruction(G4double, G4double);
        G4LogicalVolume* PmtConstruction();

    private:
        //G4LogicalVolume* logicPMT;
        G4bool fCheckOverlaps;

        G4Material* fPMMA;
        G4Material* fblack;
        G4Material* fmetal;
        G4Material* air;

        G4double              fRindex;
        G4double              fCellXYSize;
        G4double              fPmtSize;
        G4ThreeVector         fPmtPos;

        G4int                 fAptNumber;
        std::vector<G4double> fAptSize;
        std::vector<G4double> fAptPos;
        std::vector<G4int>    fAptShape;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

