#ifndef MCCorrection_h
#define MCCorrection_h

#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

#include "Lepton.h"
#include "Muon.h"
#include "Electron.h"
#include "Photon.h"
#include "Jet.h"
#include "Gen.h"

class MCCorrection{

public:

  MCCorrection();
  ~MCCorrection();

  void ReadHistograms();

  TString MCSample;
  void SetMCSample(TString s);

  int DataYear;
  void SetDataYear(int i);

  bool IgnoreNoHist;

  double MuonID_SF(TString ID, double eta, double pt, int sys=0);
  double MuonIDISO_RD_SF(TString ID, double eta, double pt, int sys=0);
  double MuonIDISO_SF(TString ID, double eta, double pt, int sys=0);
  double MuonISO_SF(TString ID, double eta, double pt, int sys=0);
  double MuonTrigger_Eff(TString ID, TString trig, int DataOrMC, double eta, double pt, int sys=0);
  double MuonTrigger_SF(TString ID, TString trig, std::vector<Muon> muons, int sys=0);
  std::map< TString, TH2F* > map_hist_Muon;
  std::map< TString, TString > map_VarOrder_Muon;

  double ElectronReco_SF(double sceta, double pt, int sys=0);
  double ElectronID_SF(TString ID, double sceta, double pt, int sys=0);
  std::map< TString, TH2F* > map_hist_Electron;
  std::map< TString, TString > map_VarOrder_Electron;
  std::map< TString, TGraphAsymmErrors* > map_graph_Electron;

  std::map< TString, TH2F* > map_hist_prefire;
  double GetPrefireWeight(std::vector<Photon> photons, std::vector<Jet> jets, int sys);

  std::map< TString, TH1D* > map_hist_pileup;
  double GetPileUpWeightBySampleName(int N_vtx, int syst);
  double GetPileUpWeight(int N_vtx, int syst);

  std::map< TString, TH2D* > map_hist_ZpT;
  double GetZPtWeight(double zpt,double zrap,Lepton::Flavour flavour, TString sample="DYJets");

  //TH2D *hzpt_muon,*hzpt_electron,*hzpt_norm_muon,*hzpt_norm_electron;

  double DiLeptonTrg_SF(TString IdKey0,TString IdKey1,const vector<Lepton*>& leps,int sys);

  TString _EtaPtOrder;

  double GetTopPtReweight(const std::vector<Gen> &gens);
  double GetTopPtReweight(const std::vector<double> *gen_pt_, const std::vector<int> *gen_PID_, const std::vector<int> *gen_status_);

};

#endif
