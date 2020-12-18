
// $Id: JunoDetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file JunoDetectorConstruction.hh
/// \brief Definition of the JunoDetectorConstruction class

#ifndef JunoDetectorConstruction_h
#define JunoDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

/// Detector construction class to define materials and geometry.

class JunoDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        JunoDetectorConstruction();
        virtual ~JunoDetectorConstruction();

        virtual G4VPhysicalVolume* Construct();
        // virtual void ConstructSDandField();

        void DefineMaterials();
        G4VPhysicalVolume* DefineVolumes();

    private:
        
        G4bool fCheckOverlaps;

        G4Material* air;

    //private:
    //    JunoDetectorConstructionMessenger* fMessenger;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

