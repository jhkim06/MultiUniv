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

  std::map<TString, double>  Mu_IdSF;
  std::map<TString, double>  MuMu_IdSF;
  std::map<TString, double>  Mu_IsoSF;
  std::map<TString, double>  MuMu_IsoSF;
  std::map<TString, double>  Mu_TriggerSF;
  std::map<TString, double>  MuMu_TriggerSF;
  std::map<TString, TString> Mu_IdSF_Iso;
  std::map<TString, TString> Mu_IdSF_Trigger;
  std::map<TString, TString> MuMu_IdSF_Trigger;


  std::map<TString, double>  El_IdSF;
  std::map<TString, TString> El_IdSF_key;
  std::map<TString, double>  El_TriggerSF;
  std::map<TString, TString> El_IdSF_Trigger;
  std::map<TString, double>  El_RecoSF;

  std::map<TString, double>  ElEl_IdSF;
  std::map<TString, double>  ElEl_TriggerSF;
  std::map<TString, TString> ElEl_IdSF_Trigger;
  std::map<TString, double>  ElEl_RecoSF;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;

  TString ElectronID_key;

};



#endif

