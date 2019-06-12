#ifndef Skim_SingleLep_h
#define Skim_SingleLep_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "TKinFitterDriver.h"

class Skim_SingleLep : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_SingleLep();
  ~Skim_SingleLep();

  TTree *newtree;

  void WriteHist();

private:

  //TKinFitterDriver* fitter_driver;

  Event *evt;

  int IsMu;
  int IsEl;
  int passTightID; // for ABCD method
  int passIso; // for ABCD method
  int passAntiIso; // for ABCD method
  int passAntiIso_Up; // for ABCD method
  int passAntiIso_Do; // for ABCD method

  vector<TString> SingleMuTrgs;
  vector<TString> SingleElTrgs;
  double Mu0PtCut;
  double Mu0EtaCut;
  double El0PtCut;
  double El0EtaCut;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;

  bool PtEtaPass;
  double Aod_pt[2], Aod_eta[2];
  double Lep0PtCut;
  double LepEtaCut;

};



#endif

