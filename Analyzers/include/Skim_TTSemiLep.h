#ifndef Skim_TTSemiLep_h
#define Skim_TTSemiLep_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "TKinFitterDriver.h"

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

  //TKinFitterDriver* fitter_driver;

  int IsMu;
  int IsEl;
  int passTightID; // for ABCD method
  int passIso; // for ABCD method
  int passAntiIso; // for ABCD method
  int passAntiIso_Up; // for ABCD method
  int passAntiIso_Do; // for ABCD method

  double weight_Prefire;

  //RootHelper rootHelp;
  double DiLepTrg_SF(TString Leg0Key, TString Leg1Key, const vector<Lepton*>& leps, int sys);
  //TBranch *b_trgSF;
  //TBranch *b_trgSF_Up;
  //TBranch *b_trgSF_Do;

  vector<TString> SingleMuTrgs;
  vector<TString> SingleElTrgs;

  double TriggerSafePtCutMu;
  double TriggerSafePtCutEl;

  TString trgSFkeyMu;
  TString trgSFkeyEl;

  TString LeptonISO_key;

  TString LeptonID_key_POG;
  TString LeptonID_key;
  Event* evt;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Gen> gens;
  std::vector<Lepton*> leps;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);
  double (MCCorrection::*PileUpWeight)(int,int);
 
  double PUweight, PUweight_Up, PUweight_Do;

  bool PtEtaPass;
  double Aod_pt[2], Aod_eta[2];
  double Lep0PtCut;
  double LepEtaCut;

  Double_t trgSF, trgSF_Up, trgSF_Do;


  double recoSF, recoSF_Up, recoSF_Do;

  double IdSF, IdSF_Up, IdSF_Do;
  double IsoSF, IsoSF_Up, IsoSF_Do;

  double doubleTmp;
  double pdf_scale_Up, pdf_scale_Do;

  TLorentzVector genZ;

  std::vector<bool> btag_vector_noSF;
  int n_bjet_deepcsv_m_noSF;
  double BTagSF, BTagSF_Up, BTagSF_Do;
  double MisTagSF, MisTagSF_Up, MisTagSF_Do;

  //double TopPtReweight;

  std::vector<Jet::Tagger> vtaggers;
  std::vector<Jet::WP> v_wps;
  vector<Jet> this_AllJets ;
  vector<Jet> jets;
  vector<Jet> jetsLveto;
  float tmp_btagsf;
  std::vector<float> tmp_mistagsf;
  
};



#endif

