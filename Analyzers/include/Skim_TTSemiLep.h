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

  double baseW;
  double weight_Prefire;
  double HEMweight;

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

  int nbtags;
  int nbtags_JES_Up;
  int nbtags_JES_Do;
  int nbtags_JER_Up;
  int nbtags_JER_Do;

  int nhf5;
  int nhf5_JES_Up;
  int nhf5_JES_Do;
  int nhf5_JER_Up;
  int nhf5_JER_Do;

  int nhf0;
  int nhf0_JES_Up;
  int nhf0_JES_Do;
  int nhf0_JER_Up;
  int nhf0_JER_Do;

  double BTagSF;
  double BTagSF_JES_Up; // second Up/Do label is jet selection related one.
  double BTagSF_JES_Do;
  double BTagSF_JER_Up;
  double BTagSF_JER_Do;
  double BTagSF_up_lfstats1;
  double BTagSF_down_lfstats1;
  double BTagSF_up_lfstats2;
  double BTagSF_down_lfstats2;
  double BTagSF_up_lf;
  double BTagSF_down_lf;
  double BTagSF_up_hf;
  double BTagSF_down_hf;
  double BTagSF_up_jes;
  double BTagSF_down_jes;
  double BTagSF_up_hfstats1;
  double BTagSF_down_hfstats1;
  double BTagSF_up_hfstats2;
  double BTagSF_down_hfstats2;
  double BTagSF_up_cferr1;
  double BTagSF_down_cferr1;
  double BTagSF_up_cferr2;
  double BTagSF_down_cferr2;

  std::vector<double> BTagSF_vector;
  std::vector<double> BTagSF_vector_JES_Up; // second Up/Do label is jet selection related one.
  std::vector<double> BTagSF_vector_JES_Do;
  std::vector<double> BTagSF_vector_JER_Up;
  std::vector<double> BTagSF_vector_JER_Do;
  std::vector<double> BTagSF_vector_up_lfstats1;
  std::vector<double> BTagSF_vector_down_lfstats1;
  std::vector<double> BTagSF_vector_up_lfstats2;
  std::vector<double> BTagSF_vector_down_lfstats2;
  std::vector<double> BTagSF_vector_up_lf;
  std::vector<double> BTagSF_vector_down_lf;
  std::vector<double> BTagSF_vector_up_hf;
  std::vector<double> BTagSF_vector_down_hf;
  std::vector<double> BTagSF_vector_up_jes;
  std::vector<double> BTagSF_vector_down_jes;
  std::vector<double> BTagSF_vector_up_hfstats1;
  std::vector<double> BTagSF_vector_down_hfstats1;
  std::vector<double> BTagSF_vector_up_hfstats2;
  std::vector<double> BTagSF_vector_down_hfstats2;
  std::vector<double> BTagSF_vector_up_cferr1;
  std::vector<double> BTagSF_vector_down_cferr1;
  std::vector<double> BTagSF_vector_up_cferr2;
  std::vector<double> BTagSF_vector_down_cferr2;

  void InitBTagReshapeNormEstimator();
  void BTagReshapeNormEstimator();
  TString GetBTagBin(const Jet& jet);

  TString BTagNormPath;
  std::map<TString, TH1D*> BTagNormHist;
  TFile* btagNorm_root;

  double BTagNorm;
  double BTagNorm_up_lfstats1;
  double BTagNorm_down_lfstats1;
  double BTagNorm_up_lfstats2;
  double BTagNorm_down_lfstats2;
  double BTagNorm_up_lf;
  double BTagNorm_down_lf;
  double BTagNorm_up_hf;
  double BTagNorm_down_hf;
  double BTagNorm_up_jes;
  double BTagNorm_down_jes;
  double BTagNorm_up_hfstats1;
  double BTagNorm_down_hfstats1;
  double BTagNorm_up_hfstats2;
  double BTagNorm_down_hfstats2;
  double BTagNorm_up_cferr1;
  double BTagNorm_down_cferr1;
  double BTagNorm_up_cferr2;
  double BTagNorm_down_cferr2;

  double TopPtReweight;

  vector<Jet> jets;
  vector<Jet> jets_JES_Up;
  vector<Jet> jets_JES_Do;
  vector<Jet> jets_JER_Up;
  vector<Jet> jets_JER_Do;

  float tmp_btagsf;
  std::vector<float> tmp_mistagsf;
  
};



#endif

