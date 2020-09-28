/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Fri Sep 25 13:34:37 2020
 @File Name: B1PhysicsList.hh
 ************************************************************************/

#ifndef B1PhysicsList_h
#define B1PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;

class B1PhysicsList : public G4VModularPhysicsList
{
    public:
        B1PhysicsList();
        virtual ~B1PhysicsList();

    public:
        virtual void SetCuts();

        virtual void ConstructParticle();
        virtual void ConstructProcess();

        void ConstructOpticalProcess();
};

#endif
