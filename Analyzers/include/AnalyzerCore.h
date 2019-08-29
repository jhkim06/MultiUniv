#ifndef AnalyzerCore_h
#define AnalyzerCore_h

#include "TLorentzVector.h"
#include "TString.h"
#include "TMath.h"
#include "TProfile.h"
#include <sstream>      

#include "SKFlatNtuple.h"
#include "Event.h"
#include "Particle.h"
#include "Gen.h"
#include "Lepton.h"
#include "Muon.h"
#include "Electron.h"
#include "Photon.h"
#include "Jet.h"
#include "FatJet.h"

#include "AnalyzerParameter.h"
#include "MCCorrection.h"
#include "FakeBackgroundEstimator.h"
#include "CFBackgroundEstimator.h"
#include "BTagSFUtil.h"
#include "PDFReweight.h"
#include "RocCorrUtil.h"

#define M_Z 91.1876
#define M_W 80.379

class AnalyzerCore: public SKFlatNtuple {

public:

  AnalyzerCore();
  ~AnalyzerCore();

  virtual void initializeAnalyzer(){

  };

  virtual void executeEvent(){

  };

  //==================
  //==== Get objects
  //==================

  //==== When GetAllMuons, we apply Rochester correciton
  //==== Then, Pt orderding can be changed
  //==== So, in the analysis code, do e.g.,
  // vector<Muon> muons = GetMuons(~~~);
  // std::sort(muons.begin(), muons.end(), PtComparing);
  //==== ** Recommend you to do the same for other objects (Electron, Jet, FatJet, ...) **
  inline static bool PtComparing(const Particle& p1, const Particle& p2){ return (p1.Pt() > p2.Pt()); }
  inline static bool PtComparingPtr(Particle* p1, Particle* p2){ return (p1->Pt() > p2->Pt()); }

  Event GetEvent();


  std::vector<Electron> GetAllElectrons(bool apply_reg_correction = true);
  std::vector<Electron> GetElectrons(TString id, double ptmin, double fetamax, bool apply_reg_correction = true);

  std::vector<Muon> GetAllMuons(bool apply_roc = true, bool update_roc = false, int s = 0, int m = 0);
  std::vector<Muon> GetMuons(TString id, double ptmin, double fetamax, bool apply_roc = true, bool update_roc = false, int s = 0, int m = 0);

  std::vector<Photon> GetAllPhotons();
  std::vector<Photon> GetPhotons(TString id, double ptmin, double fetamax, bool checkPixelSeed = false);

  //==== If TightIso is set, it calculate ptcone
  //==== If UseMini is true, Lepton::RelIso() returns MiniRelIso
  std::vector<Lepton *> MakeLeptonPointerVector(std::vector<Muon>& muons, double TightIso=-999, bool UseMini=false);
  std::vector<Lepton *> MakeLeptonPointerVector(std::vector<Electron>& electrons, double TightIso=-999, bool UseMini=false);

  std::vector<Jet> GetAllJets();
  std::vector<Jet> GetJets(TString id, double ptmin, double fetamax);
  std::vector<Jet> GetJets(TString id, double ptmin, double fetamax, int en_up_down, int res_up_down);

  std::vector<FatJet> GetAllFatJets();
  std::vector<FatJet> GetFatJets(TString id, double ptmin, double fetamax);

  std::vector<Gen> GetGens();
  void BHGetGens(std::vector<Gen>& out);

  //===================================================
  //==== Get objects METHOD 2
  //==== Get AllObject in the begining, and apply cut
  //==================================================+

  std::vector<Electron> SelectElectrons(std::vector<Electron> electrons, TString id, double ptmin, double fetamax);

  std::vector<Muon> UseTunePMuon(std::vector<Muon> muons);
  std::vector<Muon> SelectMuons(std::vector<Muon> muons, TString id, double ptmin, double fetamax);

  std::vector<Jet> SelectJets(const std::vector<Jet> &jets, TString id, double ptmin, double fetamax);

  std::vector<FatJet> SelectFatJets(std::vector<FatJet> jets, TString id, double ptmin, double fetamax);

  //==================
  //==== Systematics
  //==================

  std::vector<Electron> ScaleElectrons(std::vector<Electron> electrons, int sys);
  std::vector<Electron> SmearElectrons(std::vector<Electron> electrons, int sys);

  std::vector<Muon> ScaleMuons(std::vector<Muon> muons, int sys);

  std::vector<Jet> ScaleJets(std::vector<Jet> jets, int sys);
  std::vector<Jet> SmearJets(std::vector<Jet> jets, int sys);

  std::vector<FatJet> ScaleFatJets(std::vector<FatJet> jets, int sys);
  std::vector<FatJet> SmearFatJets(std::vector<FatJet> jets, int sys);
  std::vector<FatJet> ScaleSDMassFatJets(std::vector<FatJet> jets, int sys);
  std::vector<FatJet> SmearSDMassFatJets(std::vector<FatJet> jets, int sys);

  //====================
  //==== Event Filters
  //====================

  bool PassMETFilter();

  //============
  //==== Tools
  //============

  //===== Estimators

  MCCorrection *mcCorr;
  FakeBackgroundEstimator *fakeEst;
  CFBackgroundEstimator *cfEst;
  void initializeAnalyzerTools();

  //==== Prefire
  double GetPrefireWeight(int sys);

  //==== PU Reweight
  double GetPileUpWeight(int N_vtx, int syst);


  //==== Btag setup
  void SetupBTagger(std::vector<Jet::Tagger> taggers, std::vector<Jet::WP> wps, bool setup_systematics, bool period_dependant);
  
  //==== Is Btagged (using SF)
  bool IsBTagged(Jet j, Jet::Tagger tagger, Jet::WP WP, bool applySF, int systematic );

  //==== EvtByEvt Btagging
  void BtaggingSFEvtbyEvt(std::vector<Jet> &jets, Jet::Tagger tagger, Jet::WP WP, int systematic, float &btag_sf, float &mistag_sf);
  void BtaggingSFEvtbyEvt(std::vector<Jet> &jets, Jet::Tagger tagger, Jet::WP WP, int systematic, float &btag_sf, std::vector<float> &mistag_sf);
 
  //==== Using new PDF set
  PDFReweight *pdfReweight;
  double GetPDFWeight(LHAPDF::PDF* pdf_);
  //==== NewCentral/ProdCentral
  double GetPDFReweight();
  //==== NewErrorSet/ProdCentral
  double GetPDFReweight(int member);

  //================
  //==== Functions
  //================

  bool IsOnZ(double m, double width);
  double MT(TLorentzVector a, TLorentzVector b);
  double MT2(TLorentzVector a, TLorentzVector b, Particle METv, double METgap);
  double projectedMET(TLorentzVector a, TLorentzVector b, Particle METv);
  bool HasFlag(TString flag);
  std::vector<Muon> MuonWithoutGap(std::vector<Muon> muons);
  std::vector<Muon> MuonPromptOnly(std::vector<Muon> muons, std::vector<Gen> gens);
  std::vector<Muon> MuonUsePtCone(std::vector<Muon> muons);
  Muon MuonUsePtCone(Muon muon);
  Particle UpdateMET(const Particle &METv, const std::vector<Muon> &muons);
  Particle UpdateMET(const Particle &METv, const std::vector<Jet> &jets_nominal, const std::vector<Jet> &jets_corrected);
  std::vector<Muon> MuonApplyPtCut(std::vector<Muon> muons, double ptcut);
  std::vector<Electron> ElectronPromptOnly(std::vector<Electron> electrons, std::vector<Gen> gens);
  std::vector<Electron> ElectronUsePtCone(std::vector<Electron> electrons);
  Electron ElectronUsePtCone(Electron electron);
  std::vector<Electron> ElectronApplyPtCut(std::vector<Electron> electrons, double ptcut);
  std::vector<Jet> JetsAwayFromFatJet(std::vector<Jet> jets, std::vector<FatJet> fatjets, double mindr=1.0);
  std::vector<Jet> JetsVetoLeptonInside(const std::vector<Jet> &jets, const std::vector<Electron> &els, const std::vector<Muon> &mus);
  std::vector<Jet> JetsAwayFromPhoton(std::vector<Jet> jets, std::vector<Photon> photons, double mindr);
  Particle AddFatJetAndLepton(FatJet fatjet, Lepton lep);

  //==== GenMatching

  void PrintGen(std::vector<Gen> gens);
  Gen GetGenMatchedLepton(Lepton lep, std::vector<Gen> gens);
  Gen GetGenMatchedPhoton(Lepton lep, std::vector<Gen> gens);
  vector<int> TrackGenSelfHistory(Gen me, std::vector<Gen> gens);
  bool IsFromHadron(Gen me, std::vector<Gen> gens);
  int GetLeptonType(Lepton lep, std::vector<Gen> gens);
  int GetGenPhotonType(Gen genph, std::vector<Gen> gens);
  bool IsSignalPID(int pid);


  //==== Plotting

  std::map< TString, TH1D* > maphist_TH1D;
  std::map< TString, TH2D* > maphist_TH2D;

  TH1D* GetHist1D(TString histname);
  TH2D* GetHist2D(TString histname);

  void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  void FillHist(TString histname, double value, double weight, int n_bin, double *xbins);
  void FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double x_min, double x_max,
                int n_biny, double y_min, double y_max);
  void FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double *xbins,
                int n_biny, double *ybins);

  //==== JSFillHist : 1D
  std::map< TString, std::map<TString, TH1D*> > JSmaphist_TH1D;
  TH1D* JSGetHist1D(TString suffix, TString histname);
  void JSFillHist(TString suffix, TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  //==== JSFillHist : 2D
  std::map< TString, std::map<TString, TH2D*> > JSmaphist_TH2D;
  TH2D* JSGetHist2D(TString suffix, TString histname);
  void JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double x_min, double x_max,
                  int n_biny, double y_min, double y_max);
  void JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double *xbins,
                  int n_biny, double *ybins);

  //==== BHFillProfile
  std::map< TString, std::map<TString, TProfile*> > BHmapprofile;
  TProfile* BHGetProfile(TString suffix, TString profilename);
  void BHFillProfile(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx=60, double x_min=0., double x_max=300.,
                  double y_min=-0.5, double y_max=0.5);



  virtual void WriteHist();

  //==== Quick Plotters
  void FillLeptonPlots(std::vector<Lepton *> leps, TString this_region, double weight);
  void FillJetPlots(std::vector<Jet> jets, std::vector<FatJet> fatjets, TString this_region, double weight);

  //==== Output rootfile

  TFile *outfile;
  void SetOutfilePath(TString outname);

  std::map<TString,BTagSFUtil*> MapBTagSF;

private:
  RocCorrUtil* RocUtil; 
  





};



#endif

