
// $Id: B1DetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "B1DetectorConstructionMessenger.hh"
#include "B1PmtSD.hh"

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


B1DetectorConstruction::B1DetectorConstruction()
    : G4VUserDetectorConstruction(),
    fCheckOverlaps(true),fblack(NULL),fmetal(NULL), air(NULL)
{ 
    fRindex       = 1.5;
    fCellXYSize   = 10.*mm;
    fPmtSize      = 30.*mm;
    fPmtPos       = G4ThreeVector(500.*mm, 0, 0);
    fAptMode      = 0;  // 0 for all, 1 for one by one
    fAptNumber    = 0;
    fAptSize      = {};
    fAptPos       = {};
    fAptShape     = {};
    fAptRot       = {};

    fMessenger = new B1DetectorConstructionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



G4VPhysicalVolume* B1DetectorConstruction::Construct()
{   

    DefineMaterials();

    return DefineVolumes();
}

void B1DetectorConstruction::DefineMaterials()
{
    G4String name;
    G4double density;
    G4int compNum;


    fmetal = new G4Material(name="metal",density=3.76*g/cm3,compNum=3);
    G4MaterialPropertiesTable* metal_MPT = new G4MaterialPropertiesTable;

    const G4int nEntries = 2;

    G4double PhotonEnergy[nEntries] =
    {2.884*eV, 3.024*eV};
    G4double Reflection[nEntries] =
    {0.5,0.5};
    metal_MPT->AddProperty("Reflection",    PhotonEnergy, Reflection,nEntries);
    fmetal -> SetMaterialPropertiesTable(metal_MPT);

    fblack = new G4Material(name="black",density=1*g/cm3,compNum=3);
    G4MaterialPropertiesTable* black_MPT = new G4MaterialPropertiesTable;
    black_MPT -> AddConstProperty("theAbsorption", 1.0);
    fblack -> SetMaterialPropertiesTable(black_MPT);

    //
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    air = nist->FindOrBuildMaterial("G4_AIR");
    G4MaterialPropertiesTable* air_mpt = new G4MaterialPropertiesTable();
    air_mpt -> AddConstProperty("RINDEX", 1.0);
    air -> SetMaterialPropertiesTable(air_mpt);


    fPMMA = new G4Material(name="PMMA",density=2.23*g/cm3,compNum=2);
    G4double RefractiveIndex1[nEntries] = {fRindex, fRindex}; //{ 1.50,1.50};
    G4MaterialPropertiesTable* PMMA_MPT = new G4MaterialPropertiesTable();
    PMMA_MPT->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex1,nEntries);
    fPMMA->SetMaterialPropertiesTable(PMMA_MPT);

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* B1DetectorConstruction::CellConstruction()
{
    
    G4Box* solidCell  =
        new G4Box("box",fCellXYSize, fCellXYSize, 22.5*mm);
    //G4Box* box  =
    //    new G4Box("box",6.26*mm,6.26*mm,22.5*mm);

    G4ThreeVector zTrans(0,0,1.3*mm);
    //G4SubtractionSolid* subtraction =
    //    new G4SubtractionSolid("Box0-Box1", box0, box1,0,zTrans);
    G4LogicalVolume* logicCell =                         
        new G4LogicalVolume(
                solidCell,
                fPMMA,             
                "logicCell");        

    return logicCell;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* B1DetectorConstruction::PmtConstruction()
{
    G4double PmtRadius = fPmtSize;  // pmt radius
    G4double PmtLength = 20.*cm;
    G4ThreeVector pos = fPmtPos;
    G4Tubs* solidPmt = new G4Tubs("PMT",0, PmtRadius, PmtLength/2., 0, 2*pi);
    G4LogicalVolume* logicPmt = 
        new G4LogicalVolume(
                solidPmt,
                air,  // material
                "logicPmt");

    return logicPmt;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* B1DetectorConstruction::RoundAptConstruction(G4double in_radius, G4double out_radius)
{
    G4double apt_length = 1.5*mm;
    G4Tubs* solidApt = new G4Tubs("solidApt", in_radius, out_radius, apt_length/2., 0, 2*pi);
    G4LogicalVolume* logicApt = 
            new G4LogicalVolume(
                    solidApt,
                    fblack,
                    "logicApt"
                );

    return logicApt;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* B1DetectorConstruction::SquareAptConstruction(G4double xy, G4double out_radius, G4double ang)
{
    G4double z = 1.5*mm;
    G4Tubs* solidAptOut = new G4Tubs("solidAptOut", 0, out_radius, z, 0, 2*pi);
    G4Box*  solidApt    = new G4Box("solidApt", xy, xy, z);
    G4RotationMatrix* rot = new G4RotationMatrix();
    G4cout << "\n";
    G4cout << " ======> Config One Aperture <======= " << G4endl;
    G4cout << "Aperture Shape: Squar" << G4endl;
    G4cout << "Aperture Size : " << xy << G4endl;
    G4cout << "Aperture Rotation Angle: " << ang * deg << G4endl;
    G4cout << "\n";
    rot->rotateZ(ang);
    G4SubtractionSolid* subApt = 
        new G4SubtractionSolid("subApt",solidAptOut, solidApt, rot, G4ThreeVector());
    G4LogicalVolume* logicApt = 
            new G4LogicalVolume(
                    subApt,
                    fblack,
                    "logicApt"
                );

    return logicApt;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetAptSize(G4double* size)
{
    fAptSize.clear();
    for( int iapt=0; iapt<fAptNumber; iapt++) {
        fAptSize.push_back(size[iapt]);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetAptPos(G4double* pos)
{
    fAptPos.clear();
    for( int iapt=0; iapt<fAptNumber; iapt++) {
        fAptPos.push_back(pos[iapt]);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetAptShape(G4int* shape)
{
    fAptShape.clear();
    for(int iapt=0; iapt<fAptNumber; iapt++) {
        fAptShape.push_back(shape[iapt]);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void B1DetectorConstruction::SetAptConfigMode(G4int mode)
{
    fAptMode =  mode;  // 0 for all, 1 for one by one
}

void B1DetectorConstruction::ClearAptConfig()
{
    fAptShape.clear();
    fAptSize.clear();
    fAptPos.clear();
    fAptRot.clear();
}

void B1DetectorConstruction::SetOneAptShape(G4int shape)
{
    fAptShape.push_back(shape);
}

void B1DetectorConstruction::SetOneAptSize(G4double size)
{
    fAptSize.push_back(size);
}

void B1DetectorConstruction::SetOneAptPos(G4double pos)
{
    fAptPos.push_back(pos);
}

void B1DetectorConstruction::SetOneAptRot(G4double ang)
{
    fAptRot.push_back(ang);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::DefineVolumes()
{

    G4NistManager* man = G4NistManager::Instance();
    G4Material* air = man -> FindOrBuildMaterial("G4_AIR");
    
     const G4int nEntries = 2;

  G4double PhotonEnergy[nEntries] =
    {2.884*eV, 3.024*eV};
//
// Water
//	      
  G4double RefractiveIndex1[nEntries] =
            { 1.00,1.00};

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
  myMPT1->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex1,nEntries);
//    myMPT1 -> AddConstProperty("RINDEX", 1.50);

  air->SetMaterialPropertiesTable(myMPT1);
    //Definition of some constants
    //
    G4double worldLength = 1.8*m;
    G4double tubeIRadius = 11.45*mm;
    G4double tubeORadius = 15.25*mm;

    G4RotationMatrix* xRot = new G4RotationMatrix;
    xRot->rotateX(pi/2.*rad);
    G4RotationMatrix* yRot = new G4RotationMatrix;
    yRot->rotateY(pi/2.*rad);


    //////////////////////////////////////////////////////////////////////////////////////////////
    // optical surface definition
    // black - air
    G4OpticalSurface* OpticalAirBlack = new G4OpticalSurface("AirBlackface");
    OpticalAirBlack -> SetModel(unified);
    OpticalAirBlack -> SetType(dielectric_dielectric);
    OpticalAirBlack -> SetFinish(polishedfrontpainted);
    G4MaterialPropertiesTable* AirBlackMPT = new G4MaterialPropertiesTable();
    //AirBlackMPT->AddConstProperty("REFLECTIVITY",0.);
    //AirBlackMPT->AddConstProperty("theAbsorption",1.);
    OpticalAirBlack->SetMaterialPropertiesTable(AirBlackMPT);

    // air - glass
    G4OpticalSurface* OpticalAirPMMA = new G4OpticalSurface("AirCuvetteface");
    OpticalAirPMMA -> SetModel(unified);
    OpticalAirPMMA -> SetType(dielectric_dielectric);
    OpticalAirPMMA -> SetFinish(ground);
    G4MaterialPropertiesTable* AirCuvetteMPT = new G4MaterialPropertiesTable();
    // AirCuvetteMPT->AddConstProperty("RINDEX",1.5);
    OpticalAirPMMA->SetMaterialPropertiesTable(AirCuvetteMPT);


    // air - air
    G4OpticalSurface* OpticalAirAir = new G4OpticalSurface("AirAirface");
    OpticalAirAir -> SetModel(unified);
    OpticalAirAir -> SetType(dielectric_dielectric);
    OpticalAirAir -> SetFinish(ground);
    G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();
    OpticalAirPMMA->SetMaterialPropertiesTable(myST1);

    //////////////////////////////////////////////////////////////////////////////////////////////

    // Visualization attributes
    G4VisAttributes* boxVisAtt = new G4VisAttributes(G4Colour(0, 1, 1));
    boxVisAtt->SetForceSolid ();
    G4VisAttributes* tubVisAtt = new G4VisAttributes(G4Colour(1, 0, 1));
    tubVisAtt->SetForceSolid();
    G4VisAttributes* aptVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 1));
    aptVisAtt->SetForceSolid();

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


    //design of cuvette
    //

    G4LogicalVolume* logicCell = CellConstruction();
    G4VPhysicalVolume* physCell = 
        new G4PVPlacement(0,                       
                G4ThreeVector(0, 0, 0), 
                logicCell,                
                "physCell",              
                worldLV,              
                false,                   
                0,                       
                fCheckOverlaps);  
    //new G4LogicalBorderSurface("Air/PMMA Surface0",worldPV, physCell, OpticalAirPMMA); // optical surface
    logicCell   ->  SetVisAttributes(boxVisAtt);  // set visualization


    // design of aperture:
    
    if(fAptMode == 0) {   // set all apt in one time
        G4double vec_aptsize[3] = {2*mm, 2.5*mm, 2*mm};
        G4double vec_aptpos[3]  = {15.25*mm, 87.6*mm, 229.7*mm};
        SetAptSize(vec_aptsize);
        SetAptPos(vec_aptpos);
    }

    const int apt_num = fAptNumber;
    G4double aptOutRadius = 30*mm;  // out radius for aperture
    G4LogicalVolume* vec_logicApt[apt_num] ;
    G4PVPlacement*   vec_physApt[apt_num];

    G4cout << " ++++++++++++++++++++++++++++++++> Total " << fAptNumber << " aptertures has been added !" << G4endl;
    for(int iapt=0; iapt<fAptNumber; iapt++) {
        if ( fAptShape[iapt] == 0 ) {
            vec_logicApt[iapt] = RoundAptConstruction(fAptSize[iapt], aptOutRadius);
            G4cout << " ======> Adding " << iapt << " Round Aperture with size " << fAptSize[iapt] << " at " << fAptPos[iapt] << G4endl;
        }

        else if ( fAptShape[iapt] == 1 ) {
            vec_logicApt[iapt] = SquareAptConstruction(fAptSize[iapt], aptOutRadius, fAptRot[iapt]);
            G4cout << " ======> Adding " << iapt << " square Aperture with size " << fAptSize[iapt] << " at " << fAptPos[iapt] << G4endl;
        }

        else {
            G4cout << "Wrong Aperture Shape " << fAptShape[iapt] << G4endl;
            continue;
        }

        vec_physApt[iapt]  = new G4PVPlacement(yRot,
                                G4ThreeVector(fAptPos[iapt], 0, 0),
                                vec_logicApt[iapt],
                                "physApt",
                                worldLV,
                                false,
                                0,
                                fCheckOverlaps
                                );
    
        //new G4LogicalBorderSurface("Air/Black Surface0", worldPV, vec_physApt[iapt], OpticalAirBlack); // optical surface
        //vec_logicApt[iapt] -> SetVisAttributes(aptVisAtt);

    }    
   
    // ooooooooooOOOOOOOOOOOOOOOOOOOOoooooooooo //
    // deign of PMT

    G4ThreeVector pos = fPmtPos;
    G4LogicalVolume* logicPmt = PmtConstruction();
    G4VPhysicalVolume* physPmt = 
        new G4PVPlacement(yRot,
                //G4ThreeVector(424.75*mm,0., 0.),
                pos,
                logicPmt,
                "physPmt",
                worldLV,
                false,
                0,
                fCheckOverlaps);

    logicPmt    ->  SetVisAttributes(tubVisAtt);




    // design of scattering path

    //design of apertures

    //first one

    //G4Box* apt0 = 
    //    new G4Box("apt0",1*mm,2*mm,2*mm);

    //G4Tubs* tub0 = 
    //    new G4Tubs("tub0",0,tubeIRadius-0.01*mm,1*mm,0,2*pi);

    //G4SubtractionSolid* subapt0 = 
    //    new G4SubtractionSolid("tub0-apt0",tub0,apt0,xRot,G4ThreeVector());
    //G4LogicalVolume* logicapt0 = 
    //    new G4LogicalVolume(subapt0,
    //            fblack,
    //            "logicapt0");
    /*
       G4VPhysicalVolume* physapt0 = 
       new G4PVPlacement(xRot,
       G4ThreeVector(0,15.25*mm,0),
       logicapt0,
       "physapt0",
       worldLV,
       false,
       0,
       fCheckOverlaps);
       */

    //second one 

    //G4Box* apt1 = 
    //    new G4Box("apt1",1*mm,2.5*mm,2.5*mm);

    //G4Tubs* tub1 = 
    //    new G4Tubs("tub1",0,tubeIRadius-0.01*mm,1*mm,0,2*pi);

    //G4SubtractionSolid* subapt1 = 
    //    new G4SubtractionSolid("tub1-apt1",tub1,apt1,xRot,G4ThreeVector());
    //G4LogicalVolume* logicapt1 = 
    //    new G4LogicalVolume(subapt1,
    //            fblack,
    //            "logicapt1");
    /*  G4VPhysicalVolume* physapt1 = 
        new G4PVPlacement(xRot,
        G4ThreeVector(0,87.60*mm,0),
        logicapt1,
        "physapt1",
        worldLV,
        false,
        0,
        fCheckOverlaps);

*/
    //third one

    //G4Box* apt2 = 
    //    new G4Box("apt2",1*mm,2*mm,2*mm);

    //G4Tubs* tub2 = 
    //    new G4Tubs("tub2",0,tubeIRadius-0.01*mm,1*mm,0,2*pi);

    //G4SubtractionSolid* subapt2 = 
    //    new G4SubtractionSolid("tub2-apt2",tub2,apt2,xRot,G4ThreeVector());
    //G4LogicalVolume* logicapt2 = 
    //    new G4LogicalVolume(subapt2,
    //            fblack,
    //            "logicapt2");
    /* G4VPhysicalVolume* physapt2 = 
       new G4PVPlacement(xRot,
       G4ThreeVector(0,229.7*mm,0),
       logicapt2,
       "physapt2",
       worldLV,
       false,
       0,
       fCheckOverlaps);
       */

    // design of Lens Tube

    //G4Tubs* lenstube = 
    //    new G4Tubs("lenstube",tubeIRadius,tubeORadius,150*mm,0,2*pi);
    //G4LogicalVolume* logiclenstube = 
    //    new G4LogicalVolume(lenstube,
    //            fmetal,
    //            "logiclenstube");
    //G4VPhysicalVolume* physlenstube0 = 
    //  new G4PVPlacement(xRot,
    //                G4ThreeVector(0,174.75*mm,0),
    //                logiclenstube,
    //                "physlenstube",
    //                worldLV,
    //                false,
    //                0,
    //                fCheckOverlaps);



    /*design of cuvette sheft

      G4Box* sheft = 
      new G4Box("sheft",22.0*mm,24.75*mm,21*mm);
      G4ThreeVector zTans(0,0,8.5*mm);

      G4Tubs* path0 = 
      new G4Tubs("path0",0*mm,3*mm,7.875*mm,0,2*pi);

      G4Tubs* path1 = 
      new G4Tubs("path1",0,3*mm,1.375*mm,0,2*pi);

      G4Tubs* path2 = 
      new G4Tubs("path2",0,3*mm,7.375*mm,0,2*pi);
      G4SubtractionSolid* subsheft0 = 
      new G4SubtractionSolid("sheft-cuvette",sheft,box,0,zTans);
    //        new G4SubtractionSolid("test",sheft,path0,yRot,G4ThreeVector(0,0,0));    */

    /*  G4SubtractionSolid* subsheft1 = 
        new G4SubtractionSolid("subsheft0-path0",subsheft0,path0,yRot,G4ThreeVector(-14.125*mm,0,0));
        G4SubtractionSolid* subsheft2 = 
        new G4SubtractionSolid("subsheft1-tub2",subsheft1,tub2,yRot,G4ThreeVector(22*mm,0,0));
        G4SubtractionSolid* subsheft3 = 
        new G4SubtractionSolid("subsheft2-tub2",subsheft2,tub2,xRot,G4ThreeVector(0,-24.75*mm,0)); 
        G4SubtractionSolid* subsheft4 = 
        new G4SubtractionSolid("subsheft3-path1",subsheft3,path1,xRot,G4ThreeVector(0,15.5*mm,0));
        G4LogicalVolume* logicsheft = 
        new G4LogicalVolume(subsheft0,
    //                        sheft,
    fmetal,
    "logicsheft");

    G4VPhysicalVolume* physheft =
    new G4PVPlacement(0,
    G4ThreeVector(),
    logicsheft,
    "physsheft",
    worldLV,
    false,
    0,
    fCheckOverlaps);

    G4LogicalVolume* logicpath0 = 
    new G4LogicalVolume(path0,air,"logicpath0");

    G4LogicalVolume* logicpath1 = 
    new G4LogicalVolume(path1,air,"logicpath1");

    G4LogicalVolume* logicpath2 = 
    new G4LogicalVolume(path2,air,"logicpath2");

    G4LogicalVolume* logicbox = 
    new G4LogicalVolume(sheft,air,"logicbox");

    G4VPhysicalVolume* phypath0 =
    new G4PVPlacement(yRot,
    G4ThreeVector(-14.125*mm,0,0),    //start from here!!!
    logicpath0,
    "physpath0",
    worldLV,
    false,
    0,
    fCheckOverlaps);

    G4VPhysicalVolume* phypath1 =
    new G4PVPlacement(xRot,
    G4ThreeVector(0,23.375*mm,0),    //start from here!!!
    logicpath1,
    "physpath1",
    worldLV,
    false,
    0,
    fCheckOverlaps);

    G4VPhysicalVolume* phypath2 =
    new G4PVPlacement(xRot,
    G4ThreeVector(0,13.625*mm,0),    //start from here!!!
    logicpath2,
    "physpath2",
    worldLV,
    false,
    0,
    fCheckOverlaps);

*/


    /*
       G4VPhysicalVolume* phybox =
       new G4PVPlacement(0,
       G4ThreeVector(0,0,0),    //start from here!!!
       logicbox,
       "physbox",
       worldLV,
       false,
       0,
       fCheckOverlaps);
       */
    // design of incoming path

    //G4Tubs* lenstube1 = 
    //    new G4Tubs("lenstube1",tubeIRadius,tubeORadius,130*mm,0,2*pi);
    //G4LogicalVolume* logiclenstube1 = 
    //    new G4LogicalVolume(lenstube1,
    //            fmetal,
    //            "logiclenstube1");

    /*  G4VPhysicalVolume* physlenstube1 = 
        new G4PVPlacement(yRot,
        G4ThreeVector(-152*mm,0,0),
        logiclenstube1,
        "physlenstube1",
        worldLV,
        false,
        0,
        fCheckOverlaps);


        G4Tubs* apt3 = 
        new G4Tubs("apt3",0,0.5*mm,1*mm,0,2*pi);

        G4Tubs* tub3 = 
        new G4Tubs("tub3",0,tubeIRadius-0.01*mm,1*mm,0,2*pi);

        G4SubtractionSolid* subapt3 = 
        new G4SubtractionSolid("tub3-apt2",tub3,apt3,0,G4ThreeVector());
        G4LogicalVolume* logicapt3 = 
        new G4LogicalVolume(subapt3,
        fblack,
        "logicapt3");
        G4VPhysicalVolume* physapt3 = 
        new G4PVPlacement(yRot,
        G4ThreeVector(-100*mm,0,0),
        logicapt3,
        "physapt3",
        worldLV,
        false,
        0,
        fCheckOverlaps);
        */
    //design of end closure

    /*  G4Tubs* closure0 = new G4Tubs("closure0",0,tubeIRadius-0.01*mm,1*mm,0,2*pi);
        G4LogicalVolume* logiclosure0 =
        new G4LogicalVolume(closure0,
        fblack,
        "logiclosure0");
        G4VPhysicalVolume* physclosure0 = 
        new G4PVPlacement(xRot,
        G4ThreeVector(0,-24.75*mm,0),
        logiclosure0,
        "physclosure0",
        worldLV,
        false,
        0,
        fCheckOverlaps);

        G4Tubs* closure1 = new G4Tubs("closure1",0,tubeIRadius-0.01*mm,1*mm,0,2*pi);
        G4LogicalVolume* logiclosure1 =
        new G4LogicalVolume(closure1,
        fblack,
        "logiclosure1");
        G4VPhysicalVolume* physclosure1 = 
        new G4PVPlacement(yRot,
        G4ThreeVector(22*mm,0,0),
        logiclosure1,
        "physclosure1",
        worldLV,
        false,
        0,
        fCheckOverlaps);

*/

    //design of optical properties

    //G4OpticalSurface* OpticalAirMetal = new G4OpticalSurface("AirMetalface");
    //OpticalAirMetal -> SetModel(unified);
    //OpticalAirMetal -> SetType(dielectric_metal);
    //OpticalAirMetal -> SetFinish(groundfrontpainted);

    //G4MaterialPropertiesTable* AirMetalMPT = new G4MaterialPropertiesTable();
    ////    AirMetalMPT->AddConstProperty("theREFLECTIVITY",0.1);
    //OpticalAirMetal->SetMaterialPropertiesTable(AirMetalMPT);


    //  new G4LogicalBorderSurface("Air/Metal Surface0",worldPV,physlenstube0,OpticalAirMetal);
    //  new G4LogicalBorderSurface("Air/Metal Surface1",worldPV,physlenstube1,OpticalAirMetal);
    //  new G4LogicalBorderSurface("Air/Metal Surface2",worldPV,physheft,OpticalAirMetal);



    return worldPV;

}


void B1DetectorConstruction::ConstructSDandField()
{
    G4cout << " ----> Add Sensitive Detector " << G4endl;
    // Sensitive Detector

    auto pmtSD
        =  new B1PmtSD("PmtSD", "PmtHitsCollection", 1); //fNofLayers);
    G4SDManager::GetSDMpointer()->AddNewDetector(pmtSD);
    SetSensitiveDetector("logicPmt", pmtSD);

}




