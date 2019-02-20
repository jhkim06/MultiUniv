#ifndef Skim_K1_h
#define Skim_K1_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class Skim_K1 : public AnalyzerCore {

public:
  Skim_K1();
  ~Skim_K1();

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

