#ifndef Skim_K2_h
#define Skim_K2_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"
#include "TKinFitterDriver.h"

class Skim_K2 : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_K2();
  ~Skim_K2();

  TTree *newtree;

  void WriteHist();

private:

  TKinFitterDriver *fitter_driver;

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
  double corrected_dijet_m;
  double fitted_dijet_m;
  double best_chi2;

  double selected_lepton_pt;
  double selected_lepton_eta;
  double selected_lepton_phi;

  int njets; //number of jets
  std::vector<double> selected_jet_pt;
  std::vector<double> selected_jet_eta;
  std::vector<double> selected_jet_phi;
 
};



#endif

