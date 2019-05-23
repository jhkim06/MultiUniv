#ifndef Skim_Corr_h
#define Skim_Corr_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "DIY.h"

class Skim_Corr : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_Corr();
  ~Skim_Corr();

  TTree *newtree;

  void WriteHist();

private:


  int IsMuMu;
  int IsElEl;
  int passIso; // for ABCD method, MuMu pass isolation requirement
  int passAntiIso; // for ABCD method, MuMu pass anti-isolation requirement
  int passAntiIso_Up; // for ABCD method
  int passAntiIso_Do; // for ABCD method

  //RootHelper rootHelp;
  double DiLepTrg_SF(TString Leg0Key, TString Leg1Key, const vector<Lepton*>& leps, int sys);
  //TBranch *b_trgSF;
  //TBranch *b_trgSF_Up;
  //TBranch *b_trgSF_Do;

  vector<TString> DiMuTrgs;
  vector<TString> DiElTrgs;

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
  double pdf_error_Up, pdf_error_Do;

  TLorentzVector genZ;
  double ZPtCor;

  // diLepton Variables
  DiLepCh diLep_Ch;
  bool diLep_passSelectiveQ;
  TLorentzVector diLep;
  double diLep_m;
  double diLep_pt;
  double diLep_eta;
  int num_veto_mu;
  int num_tight_mu;
  int num_veto_el;
  int num_medi_el;
};



#endif

