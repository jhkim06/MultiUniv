#ifndef ISR_UnfoldInput_h
#define ISR_UnfoldInput_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class ISR_UnfoldInput : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  ISR_UnfoldInput();
  ~ISR_UnfoldInput();

  TTree *newtree;

  void WriteHist();

private:


  int IsMuMu;
  int IsElEl;

  //RootHelper rootHelp;
  double DiLepTrg_SF(TString Leg0Key, TString Leg1Key, const vector<Lepton*>& leps, int sys);
  //TBranch *b_trgSF;
  //TBranch *b_trgSF_Up;
  //TBranch *b_trgSF_Dn;

  vector<TString> DiMuTrgs;
  vector<TString> DiElTrgs;

  TString trgSF_key0, trgSF_key1;
  TString LeptonID_key,LeptonID_key_POG,LeptonISO_key;
  Event* evt;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);
  double (MCCorrection::*PileUpWeight)(int,int);
 
  double PUweight, PUweight_Up, PUweight_Dn;

  bool PtEtaPass;
  double Aod_pt[2], Aod_eta[2];
  double Lep0PtCut;
  double Lep1PtCut;
  double LepEtaCut;

  Double_t trgSF;
  Double_t trgSF_Up;
  Double_t trgSF_Dn;

  double recoSF;
  double recoSF_Up;
  double recoSF_Dn;

  double IdSF, IdSF_Up, IdSF_Dn;
  double IsoSF, IsoSF_Up, IsoSF_Dn;

  // TString prefix;
  double ZPtCor;

  // tree variables used in CatAnalyzer as a first trial
  std::vector<Double_t> ptRec,mRec;
  std::vector<Double_t> ptPreFSR,mPreFSR;
  Double_t weightGen, weightRec;
  Int_t ispassRec,isfiducialPreFSR,DYtautau,isBveto;
  Int_t isdielectron, isdimuon;

};



#endif

