/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Mon Sep 28 10:48:06 2020
 @File Name: B1ParticleSourceMessenger.cc
 ************************************************************************/

#include "B1ParticleSourceMessenger.hh"
#include "B1ParticleSource.hh"

#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

B1ParticleSourceMessenger::B1ParticleSourceMessenger
(B1ParticleSource* fPtclGun) : fParticleGun(fPtclGun)
{
    gunDirectory = new G4UIdirectory("/B1/gun");
    gunDirectory->SetGuidance("Particle Source control commands");

    listCmd = new G4UIcmdWithoutParameter("/B1/gun/List",this);
    listCmd->SetGuidance("List available particles");
    listCmd->SetGuidance("Invoke G4ParticleTable");

    // particle definition
    particleCmd = new G4UIcmdWithAString("/B1/gun/particle", this);
    particleCmd->SetGuidance("Set particle to be generated.");
    particleCmd->SetGuidance(" (geantino is default)");
    particleCmd->SetGuidance(" (ion can be specified for shooting ions)");
    particleCmd->SetParameterName("particleName",true);
    particleCmd->SetDefaultValue("geantino");
    G4String candidateList; 
    G4int nPtcl = particleTable->entries();
    for(G4int i=0;i<nPtcl;i++)
    {
        candidateList += particleTable->GetParticleName(i);
        candidateList += " ";
    }
    candidateList += "ion ";
    particleCmd->SetCandidates(candidateList);

    // particle direction
    directionCmd = new G4UIcmdWith3Vector("/B1/gun/direction", this);
    directionCmd->SetGuidance("Set momentum direction.");
    directionCmd->SetGuidance("Direction needs not to be a unit vector.");
    directionCmd->SetParameterName("Px","Py","Pz",true,true); 
    directionCmd->SetRange("Px != 0 || Py != 0 || Pz != 0");

    // particles energy
    energyCmd = new G4UIcmdWithADoubleAndUnit("/B1/gun/energy",this);
    energyCmd->SetGuidance("Set kinetic energy.");
    energyCmd->SetParameterName("Energy",true,true);
    energyCmd->SetDefaultUnit("eV");
    //energyCmd->SetUnitCategory("Energy");
    //energyCmd->SetUnitCandidates("eV keV MeV GeV TeV");

    positionCmd = new G4UIcmdWith3VectorAndUnit("/B1/gun/position",this);
    positionCmd->SetGuidance("Set starting position of the particle.");
    positionCmd->SetParameterName("X","Y","Z",true,true);
    positionCmd->SetDefaultUnit("cm");
    //positionCmd->SetUnitCategory("Length");
    //positionCmd->SetUnitCandidates("microm mm cm m km");

    // source position distribution type
    typeCmd = new G4UIcmdWithAString("/B1/gun/type", this);
    typeCmd->SetGuidance("Sets source distribution type.");
    typeCmd->SetGuidance("Only Point Implemented");
    typeCmd->SetParameterName("DisType", true, true);
    typeCmd->SetDefaultValue("Point");
    typeCmd->SetCandidates("Point");

    // source shape
    shapeCmd = new G4UIcmdWithAString("/B1/gun/shape", this);
    shapeCmd->SetGuidance("Sets source shape type");
    shapeCmd->SetParameterName("Shape", true, true);
    shapeCmd->SetDefaultValue("NULL");
    shapeCmd->SetCandidates("Sphere");

    // centre coordinates
    centreCmd = new G4UIcmdWith3VectorAndUnit("/B1/gun/center", this);
    centreCmd->SetGuidance("Set centre coordinates of source.");
    centreCmd->SetParameterName("X","Y","Z",true,true);
    centreCmd->SetDefaultUnit("cm");
    centreCmd->SetUnitCandidates("nm um mm cm m km");
}

B1ParticleSourceMessenger::~B1ParticleSourceMessenger()
{;}

void B1ParticleSourceMessenger::SetNewValue
    (G4UIcommand* cmd, G4String newValues) {
    
    //if ( cmd == typeCmd )
    //    fParticleGun->SetPosDisType(newValues);
}
