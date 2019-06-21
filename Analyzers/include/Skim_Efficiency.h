#ifndef Skim_Efficiency_h
#define Skim_Efficiency_h

#include "RoccoR.h"
#include "AnalyzerCore.h"
#include "RootHelper.h"

const TString SFs[4] = {"IdSF", "IsoSF", "RecoSF", "TrgSF"};

class Skim_Efficiency : public AnalyzerCore {

public:
  Skim_Efficiency();
  ~Skim_Efficiency();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param, bool isMu = true);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();

private:

  vector<TString> trgSF_key;
  TString LeptonISO_key;
  TString LeptonID_key;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);
  double (MCCorrection::*LeptonTrg_SF)(TString,TString,std::vector<Muon>,int);

  std::map<TString, std::map<TString,std::vector<double>>>  lepSFs;

  std::map<TString, std::map<TString,std::vector<TString>>>  muWPs;
  std::map<TString, std::map<TString,std::vector<TString>>>  eleWPs;

  std::map<TString, std::map<TString,std::vector<TString>>>  muKEYs; // double lepton trigger uses two keys for each leg
  std::map<TString, std::map<TString,std::vector<TString>>>  eleKEYs;

  std::vector<Muon> AllMuons;
  std::vector<Electron> AllElectrons;

};



#endif

