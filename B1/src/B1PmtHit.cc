/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Fri Sep 25 15:58:10 2020
 @File Name: B1PmtHit.cc
 ************************************************************************/

#include "B1PmtHit.hh"

G4ThreadLocal G4Allocator<B1PmtHit>* B1PmtHitAllocator = 0;

B1PmtHit::B1PmtHit()
    : G4VHit(),
      fTrackID(0.)
{}

B1PmtHit::~B1PmtHit()
{;}


B1PmtHit::B1PmtHit( const B1PmtHit& right)
    : G4VHit()
{
    fTrackID = right.fTrackID;
}


const B1PmtHit& B1PmtHit::operator=(const B1PmtHit& right)
{
    fTrackID = right.fTrackID;

    return *this;
}

G4int B1PmtHit::operator==(const B1PmtHit& right) const
{
    return (  this == &right ) ? 1 : 0;
}
void B1PmtHit::Draw()
{

}

void B1PmtHit::Print()
{
    G4cout << " trackID: " << fTrackID << G4endl;
}





