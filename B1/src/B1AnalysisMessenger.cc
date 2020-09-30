/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Wed Sep 30 09:13:41 2020
 @File Name: B1AnalysisMessenger.cc
 ************************************************************************/

#include "B1AnalysisMessenger.hh"

B1AnalysisMessenger::B1AnalysisMessenger(
        B1AnalysisManager* analysisManager)
    : b1Analysis(analysisManager)
{
    b1AnalysisDir = new G4UIdirectory("/B1/analy/");
    b1AnalysisDir->SetGuidance("analysis control");

    outputFileCmd = new G4UIcmdWithAString("/B1/analy/outputFile", this);
    outputFileCmd->SetGuidance("specify output file name");
    outputFileCmd->SetParameterName("choice", true);
    outputFileCmd->SetDefaultValue("test");
    //outputFileCmd->AvailableForStates(G4State_Idle);

}

B1AnalysisMessenger::~B1AnalysisMessenger()
{
    delete b1AnalysisDir;
    delete outputFileCmd;
}


void B1AnalysisMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
    if ( cmd == outputFileCmd ) {
        b1Analysis->SetOutputFileName( newValue );
    }
    
    else
        G4cout << "Error: Unknown Command !" << G4endl;
}
