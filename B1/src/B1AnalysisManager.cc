/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Tue Sep 29 16:11:41 2020
 @File Name: B1AnalysisManager.cc
 ************************************************************************/

#include "g4root.hh"

#include "B1AnalysisManager.hh"

B1AnalysisManager* B1AnalysisManager::instance = 0;

B1AnalysisManager::B1AnalysisManager()
    : outputFileName("opt_sim")
{
    G4AnalysisManager::Instance();

    // creating the messenger
    analysisMessenger = new B1AnalysisMessenger(this);

    G4cout << " +++++ B1AnalysisManager created" << G4endl;
}

B1AnalysisManager::~B1AnalysisManager()
{
    delete instance;
    instance = 0;

    delete G4AnalysisManager::Instance();
}

void B1AnalysisManager::book()
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    //Open an output file
    man->OpenFile(outputFileName);
    man->SetVerboseLevel(1);
    man->SetFirstHistoId(1);
    man->SetFirstNtupleId(1);

    G4cout << "Open output file: " << outputFileName << G4endl;
    man->CreateNtuple("photon", "Hits Info on SD");
    man->CreateNtupleIColumn("EventID");
    man->CreateNtupleIColumn("nPhoton");
    man->CreateNtupleIColumn("nInitPhoton");
    man->CreateNtupleDColumn("InitPosY");
    man->FinishNtuple();
    G4cout << "Created ntuple for photon counting" << G4endl;
}

void B1AnalysisManager::finish()
{
    G4cout << "Going to save ntuples" << G4endl;
    // Save histograms
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}

B1AnalysisManager* B1AnalysisManager::getInstance()
{
    if (instance==0) { instance = new B1AnalysisManager(); }
    return instance;
}


void B1AnalysisManager::SetOutputFileName(G4String newName)
{
  
  outputFileName = newName;
}

void B1AnalysisManager::analyseEventID( G4int evtid )
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn( 0, evtid );
}


void B1AnalysisManager::analysePhotonNumber(G4int number)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn( 1, number );
}

void B1AnalysisManager::analyseInitPhotonNumber(G4int number)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn( 2, number );
}


void B1AnalysisManager::analyseAddNtupleRow()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->AddNtupleRow();
}

