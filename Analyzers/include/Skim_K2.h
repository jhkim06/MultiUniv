#ifndef Skim_K2_h
#define Skim_K2_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "TKinFitterDriver.h"

class Skim_K2 : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventByJESJER(int em_shift_up_down, int res_shift_up_down);
  void executeEvent();

  Skim_K2();
  ~Skim_K2();

  TTree *newtree;

  void WriteHist();

private:

  TKinFitterDriver *fitter_driver;
  bool IsTest;
  int IsMu;
  int IsEl;
  std::vector<bool>* btag_vector_noSF;
  TBranch *b_IsMu;
  TBranch *b_IsEl;
  TBranch *b_btag_vector_noSF;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;

  Event* evt;

  double initial_dijet_m;
  double initial_dijet_m_JES_Up;
  double initial_dijet_m_JES_Do;
  double initial_dijet_m_JER_Up;
  double initial_dijet_m_JER_Do;
  double corrected_dijet_m;
  double corrected_dijet_m_JES_Up;
  double corrected_dijet_m_JES_Do;
  double corrected_dijet_m_JER_Up;
  double corrected_dijet_m_JER_Do;
  double fitted_dijet_m;
  double fitted_dijet_m_JES_Up;
  double fitted_dijet_m_JES_Do;
  double fitted_dijet_m_JER_Up;
  double fitted_dijet_m_JER_Do;
  double best_chi2;
  double best_chi2_JES_Up;
  double best_chi2_JES_Do;
  double best_chi2_JER_Up;
  double best_chi2_JER_Do;
  int fitter_status;
  int fitter_status_JES_Up;
  int fitter_status_JES_Do;
  int fitter_status_JER_Up;
  int fitter_status_JER_Do;

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

  void Clear();
};



#endif

