/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Tue Sep 29 16:07:32 2020
 @File Name: B1AnalysisManager.hh
 ************************************************************************/

#ifndef B1AnalysisManager_h
#define B1AnalysisManager_h 1

class B1AnalysisManager  {
    
    public:

        //B1AnalysisManager();
        virtual ~B1AnalysisManager();

        void book();

        void finish();
        
        //method to call to create an instance of this class
        static B1AnalysisManager* getInstance();
        
        void SetOutputFileName(G4String);

        void analysePhotonNumber(G4int number);
        void analyseEventID(G4int evtid);
        void analyseAddNtupleRow();

    private:
        B1AnalysisManager();

        G4String outputFileName;

        static B1AnalysisManager* instance;
};

#endif
