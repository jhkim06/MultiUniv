#ifndef Skim_DZfilter_h
#define Skim_DZfilter_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "PrescaleProvider.h"

class Skim_DZfilter : public AnalyzerCore {

public:

  PrescaleProvider psProv;
  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_DZfilter();
  ~Skim_DZfilter();

  TTree *newtree;

  void WriteHist();

private:

  int IsMuMu;
  int IsElEl;

  //RootHelper rootHelp;

  vector<TString> DiMuTrgs;
  vector<TString> DiElTrgs;

  Event* evt;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;

  double (MCCorrection::*PileUpWeight)(int,int);
 
  double totWeight;

  double Aod_pt[2], Aod_eta[2];
  double Lep0PtCut;
  double Lep1PtCut;
  double LepEtaCut;

  // diLepton Variables
  DiLepCh diLep_Ch;
  TLorentzVector diLep;
  double pair_mass;
  double diLep_pt;
  double diLep_eta;
  double leading_pt;
  double subleading_pt;
  double leading_eta;
  double subleading_eta;
  int mcTrue;
  int nPV_;
  int hltPS;
  int isNonDZPathPassed;
  int isDZPathPassed;
  int isBB, isBE, isEE;
  double eventCategory;
};



#endif

