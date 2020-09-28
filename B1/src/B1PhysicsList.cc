/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Fri Sep 25 13:36:45 2020
 @File Name: B1PhysicsList.cc
 ************************************************************************/

#include "B1PhysicsList.hh"

#include "G4OpticalPhysics.hh"
#include "G4SystemOfUnits.hh"

// particles
#include "G4OpticalPhoton.hh"
#include "G4ProcessManager.hh"

B1PhysicsList::B1PhysicsList() : G4VModularPhysicsList()
{
    defaultCutValue = 1.0*mm;

}

B1PhysicsList::~B1PhysicsList() {}

void B1PhysicsList::SetCuts() {
    SetCutsWithDefault();
}


void B1PhysicsList::ConstructParticle()
{
    G4OpticalPhoton::OpticalPhotonDefinition();
}

void B1PhysicsList::ConstructProcess()
{
    AddTransportation();
    ConstructOpticalProcess();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"

void B1PhysicsList::ConstructOpticalProcess()
{
    G4OpAbsorption* theAbsProcess     = new G4OpAbsorption();
    G4OpRayleigh* theRayProcess       = new G4OpRayleigh();
    G4OpBoundaryProcess* theBdProcess = new G4OpBoundaryProcess();
    auto particleIterator=GetParticleIterator();
    particleIterator->reset();
    while( (*particleIterator)() ){
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        if (theAbsProcess->IsApplicable(*particle)) {
            pmanager -> AddProcess(theAbsProcess);
        }
        if(theRayProcess->IsApplicable(*particle)) {
            pmanager -> AddProcess(theRayProcess);
        }
        if(theBdProcess->IsApplicable(*particle)) {
            pmanager -> AddProcess(theBdProcess);
        }
    }
}
