/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Wed Sep 30 09:09:07 2020
 @File Name: B1AnalysisMessenger.hh
 ************************************************************************/

#ifndef B1AnalysisMessenger_h
#define B1AnalysisMessenger_h 1

#include "globals.hh"
#include "B1AnalysisManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"

class B1AnalysisManager;

class B1AnalysisMessenger : public G4UImessenger
{

    public:
        B1AnalysisMessenger(B1AnalysisManager*);
        ~B1AnalysisMessenger();
            
        void SetNewValue(G4UIcommand*, G4String);

    private:
        // pointer to B1AnalysisManager
        B1AnalysisManager* b1Analysis;
        G4UIdirectory* b1AnalysisDir;
        G4UIcmdWithAString* outputFileCmd;

};
#endif
