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
  //TBranch *b_trgSF_Do;

  vector<TString> SingleMuTrgs;
  vector<TString> SingleElTrgs;

  TString trgSF_key0, trgSF_QPlus_key0, trgSF_QMinu_key0;
  TString trgSF_key1, trgSF_QPlus_key1, trgSF_QMinu_key1;

  TString LeptonISO_key;

  TString LeptonID_key_POG;
  TString LeptonID_key, LeptonID_QPlus_key, LeptonID_QMinu_key;
  Event* evt;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);
  double (MCCorrection::*PileUpWeight)(int,int);
 
  double PUweight, PUweight_Up, PUweight_Do;

  bool PtEtaPass;
  double Aod_pt[2], Aod_eta[2];
  double Lep0PtCut;
  double Lep1PtCut;
  double LepEtaCut;

  Double_t trgSF, trgSF_Up, trgSF_Do;

  Double_t trgSF_Q, trgSF_Q_Up, trgSF_Q_Do;

  double recoSF, recoSF_Up, recoSF_Do;

  double IdSF, IdSF_Up, IdSF_Do;
  double IdSF_Q, IdSF_Q_Up, IdSF_Q_Do;
  double IsoSF, IsoSF_Up, IsoSF_Do;

  double doubleTmp;
  double pdf_scale_Up, pdf_scale_Do;

  TLorentzVector genZ;
  double ZPtCor; //XXX: is it necessary?

  // diLepton Variables
  //TODO: add singleLepton Variables ??
  /*
  DiLepCh diLep_Ch;
  bool diLep_passSelectiveQ;
  TLorentzVector diLep;
  double diLep_m;
  double diLep_pt;
  double diLep_eta;
  */
};



#endif

