/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Mon Sep 28 10:43:07 2020
 @File Name: B1ParticleSourceMessenger.hh
 ************************************************************************/

#ifndef B1ParticleSourceMessenger_h
#define B1ParticleSourceMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class B1ParticleSource;

class G4ParticleTable;
class G4UIcommand;
class G4UImessenger;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class B1ParticleSourceMessenger: public G4UImessenger {
    public:
        B1ParticleSourceMessenger(B1ParticleSource* fPtclGun);
        ~B1ParticleSourceMessenger();

        void SetNewValue(G4UIcommand* cmd, G4String newValues);

    private:
        B1ParticleSource* fParticleGun;
        G4ParticleTable* particleTable;

    private:
        G4UIdirectory                *gunDirectory;

        G4UIcmdWithAnInteger         *numberCmd;
        G4UIcmdWithAString           *particleCmd;
        G4UIcmdWithAString           *typeCmd;
        G4UIcmdWithAString           *shapeCmd;
        G4UIcmdWith3VectorAndUnit    *centreCmd;
        G4UIcmdWith3VectorAndUnit    *positionCmd;
        G4UIcmdWith3Vector           *directionCmd;
        G4UIcmdWithADoubleAndUnit    *energyCmd;
        G4UIcmdWithAString           *angtypeCmd;
        G4UIcmdWithADouble           *angLimitCmd;
        G4UIcmdWithAString           *energytypeCmd;
        G4UIcmdWithAnInteger         *verbosityCmd;
        G4UIcmdWithoutParameter      *listCmd;

};


#endif
