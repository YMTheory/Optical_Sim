/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Mon Sep 28 18:40:39 2020
 @File Name: B1TrackingAction.hh
 ************************************************************************/

#ifndef B1TrackingAction_h
#define B1TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class B1TrackingAction : public G4UserTrackingAction {

    public:
        B1TrackingAction   ();
        ~B1TrackingAction  ();

        void PreUserTrackingAction  (const G4Track* track);
        void PostUserTrackingAction (const G4Track*);
};

#endif
