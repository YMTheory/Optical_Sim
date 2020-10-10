/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Tue Sep 29 14:10:10 2020
 @File Name: B1DetectorConstructionMessenger.hh
 ************************************************************************/

#ifndef B1DetectorConstructionMessenger_h
#define B1DetectorConstructionMessenger_h 1

class B1DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

#include "G4UImessenger.hh"
#include "globals.hh"

class B1DetectorConstructionMessenger : public G4UImessenger
{
    public:
        B1DetectorConstructionMessenger( B1DetectorConstruction* mpga );
        ~B1DetectorConstructionMessenger();


        virtual void SetNewValue( G4UIcommand *cmd, G4String newValues );
        virtual G4String GetCurrentValue( G4UIcommand* cmd );

    private:
        B1DetectorConstruction*         fTarget;

        G4UIdirectory*                  fDirectory;

        G4UIcmdWithADoubleAndUnit*      fCellXYSizeCmd;
        G4UIcmdWithADoubleAndUnit*      fPmtSizeCmd;
        G4UIcmdWith3VectorAndUnit*      fPmtPosCmd;
        G4UIcmdWithADouble*             fRindexCmd;

        // aperture configuration
        G4UIcmdWithAnInteger*           fNAptCmd;
};

#endif
