#ifndef Skim_TTSemiLep_h
#define Skim_TTSemiLep_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"

class Skim_TTSemiLep : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_TTSemiLep();
  ~Skim_TTSemiLep();

  TTree *newtree;

  void WriteHist();

private:


  int IsMu;
  int IsEl;

  //RootHelper rootHelp;
  double DiLepTrg_SF(TString Leg0Key, TString Leg1Key, const vector<Lepton*>& leps, int sys);
  //TBranch *b_trgSF;
  //TBranch *b_trgSF_Up;
  //TBranch *b_trgSF_Dn;

  vector<TString> SingleMuTrgs;
  vector<TString> SingleElTrgs;

  TString trgSF_key0;
  TString LeptonID_key,LeptonID_key_POG,LeptonISO_key;
  Event* evt;

  std::vector<Muon> muons;
  std::vector<Muon> muons_loose;
  std::vector<Electron> electrons;
  std::vector<Electron> electrons_loose;
  std::vector<Lepton*> leps;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);
  double (MCCorrection::*PileUpWeight)(int,int);
 
  double PUweight, PUweight_Up, PUweight_Dn;

  bool PtEtaPass;
  double Aod_pt[2], Aod_eta[2];
  double Lep0PtCut;
  double LepEtaCut;

  Double_t trgSF;
  Double_t trgSF_Up;
  Double_t trgSF_Dn;

  double recoSF;
  double recoSF_Up;
  double recoSF_Dn;

  double IdSF, IdSF_Up, IdSF_Dn;
  double IsoSF, IsoSF_Up, IsoSF_Dn;

  TLorentzVector genZ;
  double ZPtCor;

  // diLepton Variables
  DiLepCh diLep_Ch;
  TLorentzVector diLep;
  double diLep_m;
  double diLep_pt;
  double diLep_eta;

};



#endif

