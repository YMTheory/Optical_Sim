/*************************************************************************
  @Author: MiaoYu ---> miaoyu@ihep.ac.cn
  @Created Time : Fri Sep 25 15:53:38 2020
  @File Name: B1PmtHit.hh
 ************************************************************************/

#ifndef B1PmtHit_h
#define B1PmtHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class B1PmtHit : public G4VHit
{
    public:
        B1PmtHit();
        B1PmtHit(const B1PmtHit&);
        virtual ~B1PmtHit();

        // operators
        const B1PmtHit& operator=(const B1PmtHit&);
        G4int operator==(const B1PmtHit&) const;

        inline void* operator new    (size_t);
        inline void operator  delete (void*);

        // methods from base class
        virtual void Draw();
        virtual void Print();

        // Set methods
        void SetTrackID(G4int trackId) { fTrackID = trackId; }

        // Get methods
        G4int  GetTrackID() const;

    private:
        G4double fTrackID;

};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<B1PmtHit> B1PmtHitsCollection;

extern G4ThreadLocal G4Allocator<B1PmtHit>* B1PmtHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* B1PmtHit::operator new(size_t)
{
  if(!B1PmtHitAllocator)
      B1PmtHitAllocator = new G4Allocator<B1PmtHit>;
  return (void *) B1PmtHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void B1PmtHit::operator delete(void *hit)
{
  B1PmtHitAllocator->FreeSingle((B1PmtHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4int B1PmtHit::GetTrackID() const {
    return fTrackID;
}



#endif
