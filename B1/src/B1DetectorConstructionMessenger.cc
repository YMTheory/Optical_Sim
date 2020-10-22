/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Tue Sep 29 15:09:34 2020
 @File Name: B1DetectorConstructionMessenger.cc
 ************************************************************************/

#include "B1DetectorConstructionMessenger.hh"
#include "B1DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"

B1DetectorConstructionMessenger::
B1DetectorConstructionMessenger( B1DetectorConstruction* mpga )
    :fTarget(mpga) {

    fDirectory = new G4UIdirectory("/B1/det/");
    fDirectory->SetGuidance("detector setup commands");

    fCellXYSizeCmd = new G4UIcmdWithADoubleAndUnit("/B1/det/setCellXYSize", this);
    fCellXYSizeCmd->SetGuidance("Set cell xy size");
    fCellXYSizeCmd->SetParameterName("CellXYSize", true, true);
    fCellXYSizeCmd->SetDefaultValue(10);
    fCellXYSizeCmd->SetDefaultUnit("mm");

    fPmtSizeCmd = new G4UIcmdWithADoubleAndUnit("/B1/det/setPmtSize", this);
    fPmtSizeCmd->SetGuidance("Set pmt radius");
    fPmtSizeCmd->SetParameterName("PmtSize", true, true);
    fPmtSizeCmd->SetDefaultValue(30);
    fPmtSizeCmd->SetDefaultUnit("mm");

    fPmtPosCmd = new G4UIcmdWith3VectorAndUnit("/B1/det/setPmtPos", this);
    fPmtPosCmd->SetGuidance("Set pmt position");
    fPmtPosCmd->SetParameterName("X", "Y", "Z", true, true);
    fPmtPosCmd->SetDefaultValue(G4ThreeVector(400, 0, 0));
    fPmtPosCmd->SetDefaultUnit("mm");

    fRindexCmd = new G4UIcmdWithADouble("/B1/det/setRindex", this);
    fRindexCmd->SetGuidance("Set glass rindex");
    fRindexCmd->SetParameterName("Rindex", true, true);
    fRindexCmd->SetDefaultValue(1.5);

    fAptModeCmd = new G4UIcmdWithAnInteger("/B1/det/setAptMode", this);
    fAptModeCmd->SetGuidance("Set aperture config mode");
    fAptModeCmd->SetDefaultValue(0);

    fNAptCmd = new G4UIcmdWithAnInteger("/B1/det/setNApt", this);
    fNAptCmd->SetGuidance("Set Aperture number");
    fNAptCmd->SetDefaultValue(1);

    fAptShapeCmd = new G4UIcmdWithAnInteger("/B1/det/setAptShape", this);
    fAptShapeCmd->SetGuidance("Set one aperture shape");
    fAptShapeCmd->SetDefaultValue(0);  // 0 for round, 1 for square
    
    fAptSizeCmd = new G4UIcmdWithADoubleAndUnit("/B1/det/setAptSize", this);
    fAptSizeCmd->SetGuidance("Set one aperture size");
    fAptSizeCmd->SetDefaultValue(2);
    fAptSizeCmd->SetDefaultUnit("mm");

    fAptPosCmd = new G4UIcmdWithADoubleAndUnit("/B1/det/setAptPos", this);
    fAptPosCmd->SetGuidance("Set one aperture position");
    fAptPosCmd->SetDefaultValue(100);
    fAptPosCmd->SetDefaultUnit("mm");

    fAptRotCmd = new G4UIcmdWithADoubleAndUnit("/B1/det/setAptRot", this);
    fAptRotCmd->SetGuidance("Set one aperture rotation");
    fAptRotCmd->SetDefaultValue(0);
    fAptRotCmd->SetDefaultUnit("deg");
}   

B1DetectorConstructionMessenger::
~B1DetectorConstructionMessenger() {
    delete fCellXYSizeCmd;
    delete fPmtSizeCmd;
    delete fPmtPosCmd;
    delete fRindexCmd;
    delete fAptModeCmd;
    delete fNAptCmd;
    delete fAptShapeCmd;
    delete fAptSizeCmd;
    delete fAptPosCmd;
    delete fAptRotCmd;
}


void B1DetectorConstructionMessenger::SetNewValue(
        G4UIcommand* cmd, G4String newValue) {

    if ( cmd == fCellXYSizeCmd ) {
        fTarget->SetCellXYSize( fCellXYSizeCmd->GetNewDoubleValue(newValue) );
    }

    else if ( cmd == fPmtSizeCmd ) {
        fTarget->SetPmtSize( fPmtSizeCmd->GetNewDoubleValue(newValue) );
    }

    else if ( cmd == fPmtPosCmd ) {
        fTarget->SetPmtPos( fPmtPosCmd->GetNew3VectorValue(newValue) );
    }
    
    else if ( cmd == fRindexCmd ) {
        fTarget->SetRindex( fRindexCmd->GetNewDoubleValue(newValue));
    }

    else if ( cmd == fNAptCmd ) {
        fTarget->SetAptNumber( fNAptCmd->GetNewIntValue(newValue) );
    }

    else if ( cmd == fAptModeCmd ) {
        fTarget->SetAptConfigMode( fAptModeCmd->GetNewIntValue(newValue) );
    }

    else if ( cmd == fAptShapeCmd ) {
        fTarget->SetOneAptShape( fAptShapeCmd->GetNewIntValue(newValue) );
    }

    else if ( cmd == fAptSizeCmd ) {
        fTarget->SetOneAptSize( fAptSizeCmd->GetNewDoubleValue(newValue) );
    }

    else if ( cmd == fAptPosCmd ) {
        fTarget->SetOneAptPos( fAptPosCmd->GetNewDoubleValue(newValue) );
    }

    else if ( cmd == fAptRotCmd ) {
        fTarget->SetOneAptRot( fAptRotCmd->GetNewDoubleValue(newValue) );
    }

    else 
        G4cout << "Error: Unknown Command " << G4endl;

}


G4String B1DetectorConstructionMessenger::GetCurrentValue(G4UIcommand* cmd)
{
    ;
}
