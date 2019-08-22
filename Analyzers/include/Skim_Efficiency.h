#ifndef Skim_Efficiency_h
#define Skim_Efficiency_h

#include "RoccoR.h"
#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "LeptonSFs.h"

class Skim_Efficiency : public AnalyzerCore {

public:
  Skim_Efficiency();
  ~Skim_Efficiency();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param, unsigned int ithWP, bool isMu = true);
  void executeEvent();

  Event* evt;
  TTree *newtree;

  void WriteHist();

private:

  vector<LeptonSFs*> muonWPs;
  vector<LeptonSFs*> electronWPs;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);
  double (MCCorrection::*LeptonTrg_SF)(TString,TString,std::vector<Muon>,int);

};

#endif

