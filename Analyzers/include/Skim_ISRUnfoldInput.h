#ifndef Skim_ISRUnfoldInput_h
#define Skim_ISRUnfoldInput_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

#include "TUnfoldBinning.h"

const int nmassBins_fine_muon = 58;
const int nmassBins_wide_muon = 29;
const Double_t massBins_fine_muon[nmassBins_fine_muon+1] =     {40,42.5,45,47.5,50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350};
const Double_t massBins_wide_muon[nmassBins_wide_muon+1] =     {40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350};

const int nmassBins_fine_electron = 54;
const int nmassBins_wide_electron = 27;
const Double_t massBins_fine_electron[nmassBins_fine_electron+1] = {50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350};
const Double_t massBins_wide_electron[nmassBins_wide_electron+1] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350};

const int nmassBins_forPt = 5;
const Double_t massBins_forPt_muon[nmassBins_forPt+1] =     {40,60,80,100,200,350};
const Double_t massBins_forPt_electron[nmassBins_forPt+1] = {50,65,80,100,200,350};

const int nptbin_fine=17;
const double ptbin_fine[nptbin_fine+1]={0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.};
const int nptbin_wide=9;
const double ptbin_wide[nptbin_wide+1]={0., 4., 8., 12., 18., 28., 40., 55., 80., 100.};

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

  // binning definition for pt
  TUnfoldBinning* ptBinningRec;
  TUnfoldBinning* ptBinningGen;

  // binning definition for mass
  TUnfoldBinning* massBinningRec;
  TUnfoldBinning* massBinningGen;

  // tunfolding binning index
  Int_t diptBinIndex_Rec, dimassBinIndex_Rec;
  Int_t diptBinIndex_Gen, dimassBinIndex_Gen;

  //
  TLorentzVector particlePostFSR, anparticlePostFSR;
  Double_t weightGen, weightRec, bTagReweight;
  Double_t L1Prefire, L1Prefire_Up, L1Prefire_Dn;
  Int_t ispassRec,isfiducialPostFSR,isfiducialPreFSR,DYtautau,isBveto;
  Int_t isdielectron, isdimuon;

};



#endif

