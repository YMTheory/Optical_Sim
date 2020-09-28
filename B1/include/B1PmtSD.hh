/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Fri Sep 25 15:48:19 2020
 @File Name: B1TrackerSD.hh
 ************************************************************************/

#ifndef B1PmtSD_h
#define B1PmtSD_h 1

#include "G4VSensitiveDetector.hh"
#include "B1PmtHit.hh"

class G4Step;
class G4HCofThisEvent;

class B1PmtSD : public G4VSensitiveDetector
{
    public:
        B1PmtSD(const G4String& name,
                const G4String& hitsCollectionName,
                G4int nofPmts);
        virtual ~B1PmtSD();

        // methods from base class
        virtual void   Initialize  (G4HCofThisEvent* hitCollection);
        virtual G4bool ProcessHits (G4Step* step, G4TouchableHistory* history);
        virtual void   EndOfEvent  (G4HCofThisEvent* hitCollection);

    private:
        B1PmtHitsCollection* fHitsCollection;
        G4int fNofPmts;

};

#endif
