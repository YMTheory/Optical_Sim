/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Mon Sep 28 10:48:06 2020
 @File Name: B1ParticleSourceMessenger.cc
 ************************************************************************/

#include "B1ParticleSourceMessenger.hh"
#include "B1ParticleSource.hh"

#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"
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
(B1ParticleSource* fPtclGun) 
    : fParticleGun(fPtclGun)
{
    gunDirectory = new G4UIdirectory("/B1/gun/");
    gunDirectory->SetGuidance("Particle Source control commands");

    listCmd = new G4UIcmdWithoutParameter("/B1/gun/List",this);
    listCmd->SetGuidance("List available particles");
    listCmd->SetGuidance("Invoke G4ParticleTable");

    // particle definition
    particleCmd = new G4UIcmdWithAString("/B1/gun/particle", this);
    particleCmd->SetGuidance("Set particle to be generated.");
    particleCmd->SetGuidance(" (opticalphoton is default)");
    particleCmd->SetGuidance(" (ion can be specified for shooting ions)");
    particleCmd->SetParameterName("particleName",true);
    particleCmd->SetDefaultValue("opticalphoton");
    particleCmd->SetCandidates("opticalphoton");
   
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
    
    // angular distribution
    angtypeCmd = new G4UIcmdWithAString("/B1/gun/angtype", this);
    angtypeCmd->SetGuidance("Sets angular source distribution type");
    angtypeCmd->SetGuidance("Possible variables are: iso direction");
    angtypeCmd->SetParameterName("AngDis",true,true);
    angtypeCmd->SetDefaultValue("iso");
    angtypeCmd->SetCandidates("iso HalfSphere direction");


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

    // energy distribution
    energytypeCmd = new G4UIcmdWithAString("/B1/gun/energytype", this);
    energytypeCmd->SetGuidance("Sets energy distribution type");
    energytypeCmd->SetGuidance("Possible variables are: Mono");
    energytypeCmd->SetParameterName("EnergyDis",true,true);
    energytypeCmd->SetDefaultValue("Mono");
    energytypeCmd->SetCandidates("Mono");

    
    // verbosity
    verbosityCmd = new G4UIcmdWithAnInteger("/B1/gun/verbose",this);
    verbosityCmd->SetGuidance("Set Verbose level for gun");
    verbosityCmd->SetGuidance(" 0 : Silent");
    verbosityCmd->SetGuidance(" 1 : Limited information");
    verbosityCmd->SetGuidance(" 2 : Detailed information");
    verbosityCmd->SetParameterName("level",false);
    verbosityCmd->SetRange("level>=0 && level <=2");

}

B1ParticleSourceMessenger::~B1ParticleSourceMessenger()
{
    delete listCmd;
    delete typeCmd;
    delete shapeCmd;
    delete centreCmd;
    delete energytypeCmd;
    delete particleCmd;
    delete positionCmd;
    delete directionCmd;
    delete energyCmd;
    delete angtypeCmd;

    delete gunDirectory;
}

void B1ParticleSourceMessenger::SetNewValue
(G4UIcommand* cmd, G4String newValues) {
    
    
    if ( cmd == typeCmd )
        fParticleGun->SetPosDisType(newValues);

    else if ( cmd == shapeCmd )
        fParticleGun->SetPosDisShape(newValues);

    else if ( cmd == centreCmd ) 
        fParticleGun->SetCentreCoords( centreCmd->GetNew3VectorValue(newValues) );

    else if ( cmd == energytypeCmd )
        fParticleGun->SetEnergyDisType(newValues);

    else if ( cmd == particleCmd ) {
        G4ParticleDefinition *pd = particleTable->FindParticle(newValues);
        if( pd != NULL )
            fParticleGun->SetParticleDefinition(pd);
    }

    else if ( cmd == angtypeCmd ) {
        fParticleGun->SetAngDistType(newValues);
    }

    else if ( cmd == listCmd )
        particleTable->DumpTable();

    else if ( cmd == directionCmd ) {
        fParticleGun->SetAngDistType("direction");
        fParticleGun->SetParticleMomentumDirection
            (directionCmd->GetNew3VectorValue(newValues));
    }

    else if ( cmd == energyCmd ) {
        fParticleGun->SetEnergyDisType("Mono");
        fParticleGun->SetMonoEnergy(energyCmd->GetNewDoubleValue(newValues));
    }

    else if ( cmd == positionCmd ) {
        fParticleGun->SetPosDisType("Point");
        fParticleGun->SetCentreCoords(positionCmd->GetNew3VectorValue(newValues));
    }

    else if ( cmd == verbosityCmd )
        fParticleGun->SetVerbosity(verbosityCmd->GetNewIntValue(newValues));

    else
        G4cout << "Error: Unknow Command" << G4endl;
        
}
