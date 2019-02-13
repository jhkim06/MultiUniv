#ifndef SMP_Skim_h
#define SMP_Skim_h

#include "AnalyzerCore.h"

class SMP_Skim : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  SMP_Skim();
  ~SMP_Skim();

  TTree *newtree;

  void WriteHist();

private:
  bool skim_DoubleLepTrg;
  vector<TString> doubleTrgs;

};



#endif

