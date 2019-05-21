#ifndef Module_Efficiency_h
#define Module_Efficiency_h

#include "RoccoR.h"
#include "AnalyzerCore.h"
#include "RootHelper.h"

class Module_Efficiency : public AnalyzerCore {

public:
  Module_Efficiency();
  ~Module_Efficiency();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();

private:

  std::vector<Lepton*> leps;
  vector<double> Aod_pt, Aod_eta; //TODO lets use vector later

  //
  int IsMu, IsEl, IsElMu;

  //
  double L_recoSF, L_recoSF_Up, L_recoSF_Do; 
  double LL_recoSF, LL_recoSF_Up, LL_recoSF_Do; 

  double L_IdSF, L_IdSF_Up, L_IdSF_Do; 
  double LL_IdSF, LL_IdSF_Up, LL_IdSF_Do; 

  double L_IsoSF, L_IsoSF_Up, L_IsoSF_Do; 
  double LL_IsoSF, LL_IsoSF_Up, LL_IsoSF_Do; 

  //
  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);

  std::vector<Muon> muons;
  std::vector<Electron> electrons;

  TString LeptonID_key;
  TString LeptonISO_key;
  TString trgSF_key0, trgSF_key1;

};



#endif

