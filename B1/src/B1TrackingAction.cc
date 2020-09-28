/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Mon Sep 28 18:43:11 2020
 @File Name: B1TrackingAction.cc
 ************************************************************************/

#include "B1TrackingAction.hh"

#include "G4Track.hh"

B1TrackingAction::B1TrackingAction()
    : G4UserTrackingAction()
{}

B1TrackingAction::~B1TrackingAction()
{}

void B1TrackingAction::PreUserTrackingAction( const G4Track* track )
{
    G4cout << "Particle ID: " << track->GetTrackID() << G4endl;
}

void B1TrackingAction::PostUserTrackingAction ( const G4Track* ) 
{;}
