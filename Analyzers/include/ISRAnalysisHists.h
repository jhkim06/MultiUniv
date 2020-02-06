#ifndef ISRAnalysisHists_h
#define ISRAnalysisHists_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class ISRAnalysisHists : public AnalyzerCore {

public:

    void initializeAnalyzer();
    void executeEvent();

    ISRAnalysisHists();
    ~ISRAnalysisHists();

    TTree *newtree;

    void WriteHist();

private:

    Event* evt;

};

#endif

