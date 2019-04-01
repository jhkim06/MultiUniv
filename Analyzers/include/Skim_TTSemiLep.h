#ifndef Skim_TTSemiLep_h
#define Skim_TTSemiLep_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class Skim_TTSemiLep : public AnalyzerCore {

public:
  Skim_TTSemiLep();
  ~Skim_TTSemiLep();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();

private:


  bool   Is_baseW;
  double baseW;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
 


};



#endif

