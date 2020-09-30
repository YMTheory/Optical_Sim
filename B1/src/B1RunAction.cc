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
// $Id: B1RunAction.cc 99560 2016-09-27 07:03:29Z gcosmo $
//
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1Analysis.hh"
#include "B1AnalysisManager.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction()
: G4UserRunAction()
{
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);
    B1AnalysisManager* analysis = B1AnalysisManager::getInstance();
    
    // Create analysis manager
    //auto analysisManager = G4AnalysisManager::Instance();
    //G4cout << "Using " << analysisManager->GetType() << G4endl;

    //analysisManager->SetVerboseLevel(1);
    //analysisManager->SetNtupleMerging(true);

    //// Book ntuples:
    //analysisManager->CreateNtuple("B1", "Hits Info in SD");
    //analysisManager->CreateNtupleIColumn("TrackID");
    //analysisManager->CreateNtupleIColumn("nPhoton");
    //analysisManager->FinishNtuple();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{
    //delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{
    G4cout << "Begin of One Run" << G4endl;

    //auto analysisManager = G4AnalysisManager::Instance();
    //// Open an output file
    //G4String fileName = "B1";
    //analysisManager->OpenFile(fileName);

    B1AnalysisManager* analysis = B1AnalysisManager::getInstance();
    analysis->book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* )
{
    auto analysisManager = G4AnalysisManager::Instance();
    // save ntuples
    analysisManager->Write();
    analysisManager->CloseFile();
    B1AnalysisManager* analysis = B1AnalysisManager::getInstance();
    analysis->finish();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

