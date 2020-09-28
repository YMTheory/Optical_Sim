/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Fri Sep 25 16:13:44 2020
 @File Name: B1PmtSD.cc
 ************************************************************************/

#include "B1PmtSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

B1PmtSD::B1PmtSD( const G4String& name, 
                  const G4String& hitsCollectionName,
                  G4int nofPmts)
    : G4VSensitiveDetector(name),
    fHitsCollection(NULL),
    fNofPmts(nofPmts)
{
    collectionName.insert(hitsCollectionName);
}

B1PmtSD::~B1PmtSD()
{;}


void B1PmtSD::Initialize(G4HCofThisEvent* hce)
{
    // Create hits collection
    fHitsCollection
        = new B1PmtHitsCollection( SensitiveDetectorName, collectionName[0]);
    
    // Add this collection in hce
    G4int hcID 
        = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection( hcID, fHitsCollection );

    // Create hits
    for( G4int i=0; i<fNofPmts+1; i++ )  {
        fHitsCollection->insert(new B1PmtHit());
    }
}

G4bool B1PmtSD::ProcessHits( G4Step* aStep, G4TouchableHistory*)
{
    
    G4cout << "SD Hit Info : " << aStep->GetTrack()->GetTrackID() << G4endl;

    G4double edep = aStep->GetTotalEnergyDeposit();
    G4double stepLength = aStep->GetStepLength();
    if(edep == 0. && stepLength == 0. ) return false;

    auto touchable = (aStep->GetPreStepPoint()->GetTouchable());

    // Get pmt id
    auto pmtNumber = touchable->GetReplicaNumber(1);

    auto hit = (*fHitsCollection)[pmtNumber];
    if ( ! hit ) {
        G4ExceptionDescription msg;
        msg << "Cannot access hit " << pmtNumber; 
        G4Exception("B4cCalorimeterSD::ProcessHits()",
                "MyCode0004", FatalException, msg);
    }         


    return true;
}



void B1PmtSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>1 ) { 
     G4int nofHits = fHitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits 
            << " hits in the tracker chambers: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}
