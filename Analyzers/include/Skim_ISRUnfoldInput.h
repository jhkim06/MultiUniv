#ifndef Skim_ISRUnfoldInput_h
#define Skim_ISRUnfoldInput_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class Skim_ISRUnfoldInput : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_ISRUnfoldInput();
  ~Skim_ISRUnfoldInput();

  TTree *newtree;

  void WriteHist();

  int findInitialMoterIndex(int motherIndex, int currentIndex, vector<Gen> &gens, bool onlySamePtl = true); 
  void selectDilepton(vector<Gen> &gens, std::map<int,int> &parIndex, std::map<int,int> &aparIndex, vector<int> &gparticleIndex, vector<int> &gaparticleIndex);
  void saveMotherIndexMap(vector<Gen> &gens, int currentIndex, int motherIndex, std::map<int,int> &partindexmap);

private:

  bool debug_;

  int IsMuMu;
  int IsElEl;

  //RootHelper rootHelp;
  double DiLepTrg_SF(TString Leg0Key, TString Leg1Key, const vector<Lepton*>& leps, int sys);

  vector<TString> DiMuTrgs;
  vector<TString> DiElTrgs;

  TString trgSF_key0, trgSF_key1;
  TString LeptonID_key,LeptonID_key_POG,LeptonISO_key;
  Event* evt;

  std::vector<Muon> muons;
  std::vector<Muon> muons_momentumUp;
  std::vector<Muon> muons_momentumDown;

  std::vector<Electron> electrons;
  std::vector<Electron> electrons_momentumUp;
  std::vector<Electron> electrons_momentumDown;
  std::vector<Electron> electrons_momentumResUp;
  std::vector<Electron> electrons_momentumResDown;

  std::vector<Lepton*> leps;
  std::vector<Lepton*> leps_momentumUp;
  std::vector<Lepton*> leps_momentumDown;

  std::vector<Lepton*> leps_momentumResUp;
  std::vector<Lepton*> leps_momentumResDown;

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
  std::vector<Double_t> AlphaS;
  std::vector<Double_t> Scale;
  std::vector<Double_t> PDFerror;
  std::vector<Double_t> ptRec,mRec;
  std::vector<Double_t> ptRec_momentumUp,mRec_momentumUp;
  std::vector<Double_t> ptRec_momentumDown,mRec_momentumDown;
  std::vector<Double_t> ptRec_momentumResUp,mRec_momentumResUp;
  std::vector<Double_t> ptRec_momentumResDown,mRec_momentumResDown;
  std::vector<Double_t> ptPreFSR,mPreFSR;
  std::vector<Double_t> ptPostFSR,mPostFSR;
  std::vector<TLorentzVector> particleFSR, anparticleFSR;

  TLorentzVector particlePostFSR, anparticlePostFSR;
  Double_t weightGen, weightRec, bTagReweight;
  Double_t L1Prefire, L1Prefire_Up, L1Prefire_Dn;
  Int_t ispassRec,isfiducialPostFSR,isfiducialPreFSR,DYtautau,isBveto;
  Int_t isdielectron, isdimuon;

};



#endif

