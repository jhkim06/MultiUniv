#ifndef Skim_K2_h
#define Skim_K2_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "TKinFitterDriver.h"

class Skim_K2 : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventByJESJER(int em_shift_up_down, int res_shift_up_down, int btag_up_down=0);
  void executeEvent();

  Skim_K2();
  ~Skim_K2();

  TTree *newtree;

  void WriteHist();

private:

  TKinFitterDriver *fitter_driver;
  bool FlagTest;
  int IsMu;
  int IsEl;
  TBranch *b_IsMu;
  TBranch *b_IsEl;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Jet> jets;
  std::vector<Jet> jets_JES_Up;
  std::vector<Jet> jets_JES_Do;
  std::vector<Jet> jets_JER_Up;
  std::vector<Jet> jets_JER_Do;

  Event* evt;

  //dijet mass by signal mass point
  std::vector<TString> mass_points;
  std::vector<TString> JES_JER_syst;
  std::map<TString, std::map<TString, double> > initial_dijet_m;
  std::map<TString, std::map<TString, double> > corrected_dijet_m;
  std::map<TString, std::map<TString, double> > fitted_dijet_m;
  std::map<TString, std::map<TString, double> > best_chi2;
  std::map<TString, std::map<TString, int> > fitter_status;

  //double best_chi2;
  //double best_chi2_JES_Up;
  //double best_chi2_JES_Do;
  //double best_chi2_JER_Up;
  //double best_chi2_JER_Do;
  //int fitter_status;
  //int fitter_status_JES_Up;
  //int fitter_status_JES_Do;
  //int fitter_status_JER_Up;
  //int fitter_status_JER_Do;

  double hadronic_top_M;
  double leptonic_top_M;
  double leptonic_W_M;
  bool IsRealNeuPz;

  double hadronic_top_M_F;
  double leptonic_top_M_F;
  double leptonic_W_M_F;
  double deltaS;

  std::vector<double> hadronic_top_M_vector_success;
  std::vector<double> hadronic_top_M_vector_fail;
  std::vector<double> hadronic_top_b_pt_vector_success;
  std::vector<double> hadronic_top_b_pt_vector_fail;
  std::vector<double> leptonic_top_b_pt_vector_success;
  std::vector<double> leptonic_top_b_pt_vector_fail;
  std::vector<double> wch_up_type_pt_vector_success;
  std::vector<double> wch_up_type_pt_vector_fail;
  std::vector<double> wch_down_type_pt_vector_success;
  std::vector<double> wch_down_type_pt_vector_fail;

  double selected_lepton_pt;
  double selected_lepton_eta;
  double selected_lepton_phi;

  int njets; //number of jets
  int njets_JES_Up;
  int njets_JES_Do;
  int njets_JER_Up;
  int njets_JER_Do;
  int nbtags; //number of b tags
  int nbtags_JES_Up;
  int nbtags_JES_Do;
  int nbtags_JER_Up;
  int nbtags_JER_Do;

  std::vector<double> selected_jet_pt;
  std::vector<double> selected_jet_pt_JES_Up;
  std::vector<double> selected_jet_pt_JES_Do;
  std::vector<double> selected_jet_pt_JER_Up;
  std::vector<double> selected_jet_pt_JER_Do;
  std::vector<double> selected_jet_eta;
  std::vector<double> selected_jet_phi;
  //correct MET by JES/JER variation
  double MET;
  double MET_JES_Up;
  double MET_JES_Do;
  double MET_JER_Up;
  double MET_JER_Do;

  //Mistag
  // here upgrade means upgrade b-tagging status
  bool FlagMistag; // store value of HasFlag("Mistag")
  unsigned int nUpgrade;        // num. of untagged SF>1. jet
  unsigned int nUpgrade_BTag_Up;
  unsigned int nUpgrade_BTag_Do;
  unsigned int nUpgrade_JES_Up; // to be initialized as 0
  unsigned int nUpgrade_JES_Do; // will be calculated at dedicated method
  unsigned int nUpgrade_JER_Up;
  unsigned int nUpgrade_JER_Do;
  unsigned int nUpgraded;       // to be initialized as 0 in clear
  unsigned int nUpgraded_BTag_Up;
  unsigned int nUpgraded_BTag_Do;
  unsigned int nUpgraded_JES_Up;
  unsigned int nUpgraded_JES_Do;
  unsigned int nUpgraded_JER_Up;
  unsigned int nUpgraded_JER_Do;

  std::map<unsigned int,unsigned int> MapIdxUpgrade; // key: n th jets to be upgraded(correspond to nUpgraded), value: jets index to be upgraded
  std::map<unsigned int,unsigned int> MapIdxUpgrade_BTag_Up;
  std::map<unsigned int,unsigned int> MapIdxUpgrade_BTag_Do;
  std::map<unsigned int,unsigned int> MapIdxUpgrade_JES_Up; // ex) MapIdxUpgrade[nUpgraded] = jet_idx
  std::map<unsigned int,unsigned int> MapIdxUpgrade_JES_Do;
  std::map<unsigned int,unsigned int> MapIdxUpgrade_JER_Up;
  std::map<unsigned int,unsigned int> MapIdxUpgrade_JER_Do;

  std::map<unsigned int, double> MapIdxMistagRate;       
  std::map<unsigned int, double> MapIdxMistagRate_BTag_Up;       
  std::map<unsigned int, double> MapIdxMistagRate_BTag_Do;       
  std::map<unsigned int, double> MapIdxMistagRate_JES_Up;
  std::map<unsigned int, double> MapIdxMistagRate_JES_Do;
  std::map<unsigned int, double> MapIdxMistagRate_JER_Up;
  std::map<unsigned int, double> MapIdxMistagRate_JER_Do;

  void calcUpgrade(int em_shift_up_down, int res_shift_up_down, int btag_up_down=0); // estimate n upgrade and mistag sf.

  double MistagRate;        // to be stored in tree
  double MistagRate_BTag_Up;
  double MistagRate_BTag_Do;
  double MistagRate_JES_Up; // 1. will be stored for nUpgrade == 0.
  double MistagRate_JES_Do; // 0. will be stored for nUpgraded >= nUpgrade
  double MistagRate_JER_Up;
  double MistagRate_JER_Do;

  int IsMistag; // 0. for not upgraded event, 1. for upgraded event
  int IsMistag_BTag_Up; // -1 for nUpgraded >= nUpgrade
  int IsMistag_BTag_Do; // to be stored in tree
  int IsMistag_JES_Up; 
  int IsMistag_JES_Do; 
  int IsMistag_JER_Up;
  int IsMistag_JER_Do;

  void Clear();

};



#endif

