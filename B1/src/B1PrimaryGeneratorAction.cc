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
// $Id: B1PrimaryGeneratorAction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

#include "B1PrimaryGeneratorAction.hh"
#include "B1ParticleSource.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include <cmath>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
    fParticleGun      = new G4ParticleGun();
    fParticleSource   = new B1ParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //this function is called at the begining of ecah event
    //

    // In order to avoid dependence of PrimaryGeneratorAction
    // on DetectorConstruction class we get Envelope volume
    // from G4LogicalVolumeStore.

    
    //G4cout << "Genarate Primary Particles ..." << G4endl; 

    /*
    // Generate more than one particle each time
    NumberOfParticlesToBeGenerated = 10000;
    fParticleGun = new G4ParticleGun(NumberOfParticlesToBeGenerated);

    const G4double pi = 3.141592653;

    // particle definition
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName="opticalphoton");

    for( G4int iP = 0; iP<NumberOfParticlesToBeGenerated; iP++ ) {

        // set particle type
        fParticleGun->SetParticleDefinition(particle);

        // set optical photon energy/wavelength
        fParticleGun->SetParticleEnergy(2*eV);

        // set momentum direction
        G4double mom_x, mom_y, mom_z, mom_theta, mom_phi;
        while(1)  {
            mom_theta = G4UniformRand() * pi;
            mom_phi   = G4UniformRand() * pi * 2;
            mom_x     = sin(mom_theta) * cos(mom_phi);
            if ( mom_x >0 ) break;
        }
        mom_y  =  sin(mom_theta) * sin(mom_phi);
        mom_z  =  cos(mom_theta);

        fParticleGun->SetParticleMomentumDirection( G4ThreeVector(mom_x, mom_y, mom_z));

        fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));

        fParticleGun->GeneratePrimaryVertex( anEvent );
    }
    */ 

    //fParticleGun->GeneratePrimaryVertex(anEvent);
    fParticleSource -> GeneratePrimaryVertex(anEvent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

