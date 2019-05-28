#ifndef Skim_K2_h
#define Skim_K2_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "TKinFitterDriver.h"

class Skim_K2 : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_K2();
  ~Skim_K2();

  TTree *newtree;

  void WriteHist();

private:

  TKinFitterDriver *fitter_driver;

  int IsMu;
  int IsEl;
  TBranch *b_IsMu;
  TBranch *b_IsEl;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;

  Event* evt;

  double initial_dijet_m;
  double corrected_dijet_m;
  double fitted_dijet_m;
  double best_chi2;
 
};



#endif

