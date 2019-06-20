#ifndef TKinFitterDriver_h
#define TKinFitterDriver_h

#include "TString.h"
#include <iostream>
#include <numeric>

#include "TFitConstraintM.h"
#include "TFitParticleEtEtaPhi.h"
#include "TKinFitter.h"
#include "TSCorrection.h"

#include "Jet.h"

using namespace std;

class TKinFitterDriver{

public:

  TKinFitterDriver();
  TKinFitterDriver(int DataYear_);
  ~TKinFitterDriver();

  int DataYear;
  void SetDataYear(int i);

  void SetAllObjects(std::vector<Jet> jet_vector_,
                     std::vector<bool> btag_vector_,
                     TLorentzVector lepton_,
                     TLorentzVector met_);
  void SetHadronicTopBJets(TLorentzVector jet_); // it doesn't check tagging status
  void SetLeptonicTopBJets(TLorentzVector jet_); // it doesn't check tagging status
  void SetWCHUpTypeJets(TLorentzVector jet_); // u/c jet from W(H+)
  void SetWCHDownTypeJets(TLorentzVector jet_); // d/s/b jet from W(H+)
  void SetLepton(TLorentzVector lepton_);
  void SetMET(TLorentzVector met_);
  void SetNeutrino(TLorentzVector met_,int i); // i is related to neu. Pz

  void Fit();
  void FindBestChi2Fit(bool UseLeading4Jets=false);

  int GetStatus();
  double GetChi2();
  double GetFittedDijetMass();
  double GetInitialDijetMass();
  double GetCorrectedDijetMass();

  int GetBestStatus();
  double GetBestChi2();
  double GetBestFittedDijetMass();
  double GetBestInitialDijetMass();
  double GetBestCorrectedDijetMass();

  std::vector<double> GetHadronicTopMassVector(bool IsConverge=true);
  std::vector<double> GetHadronicTopBPtVector(bool IsConverge=true);
  std::vector<double> GetLeptonicTopBPtVector(bool IsConverge=true);
  std::vector<double> GetWCHDownTypePtVector(bool IsConverge=true);
  std::vector<double> GetWCHUpTypePtVector(bool IsConverge=true);

  enum JET_ASSIGNMENT{
    HADRONIC_TOP_B,
    LEPTONIC_TOP_B,
    W_CH_UP_TYPE,
    W_CH_DOWN_TYPE,
    NONE
  };

  struct ResultContatiner{
    ResultContatiner(){}
    ~ResultContatiner(){}
    int status; //fitter status
    double chi2;
    double fitted_dijet_M;
    double initial_dijet_M;
    double corrected_dijet_M;
    double hadronic_top_M;

    double hadronic_top_b_pt;
    double leptonic_top_b_pt;
    double w_ch_up_type_pt;
    double w_ch_down_type_pt;
  };

private:

  void SetJetError(TMatrixD *matrix,  double Et, double Eta, double Phi, TString flavour_key);
  double JetErrorEt(double Et, double Eta, TString flavour_key);
  double JetErrorEta(double Et, double Eta, TString flavour_key);
  double JetErrorPhi(double Et, double Eta, TString flavour_key);
  void SetConstraint();
  void SetFitter();
  void SetCurrentPermutationJets();
  bool Check_BJet_Assignment();
  bool Kinematic_Cut();
  bool NextPermutation(bool UseLeading4Jets=false);

  void Sol_Neutrino_Pz();
  void Resol_Neutrino_Pt();
  double neutrino_pz[2];
  bool IsRealNeuPz;

  TKinFitter *fitter;
  TSCorrection *ts_correction;

  std::vector<TLorentzVector> jet_vector;
  std::vector<bool> btag_vector;
  TLorentzVector METv;
  TLorentzVector recal_METv;

  int njets;
  int nbtags;
  std::vector<TKinFitterDriver::JET_ASSIGNMENT> permutation_vector;

  TLorentzVector hadronic_top_b_jet; // b jet comes from hadronic top 
  TLorentzVector leptonic_top_b_jet; // b jet comes from leptonic top
  TLorentzVector hadronic_w_ch_jet1; // u/c jet comes from W(H+)
  TLorentzVector hadronic_w_ch_jet2; // d/s/b jet comes from W(H+)
  TLorentzVector corr_hadronic_top_b_jet; // applied TS Correction
  TLorentzVector corr_leptonic_top_b_jet; 
  TLorentzVector corr_hadronic_w_ch_jet1;
  TLorentzVector corr_hadronic_w_ch_jet2;
  TLorentzVector lepton; // lepton comes from leptonic W
  TLorentzVector neutrino; // neutrino comes from leptonic W

  TFitParticleEtEtaPhi *fit_hadronic_top_b_jet;
  TFitParticleEtEtaPhi *fit_leptonic_top_b_jet;
  TFitParticleEtEtaPhi *fit_hadronic_w_ch_jet1;
  TFitParticleEtEtaPhi *fit_hadronic_w_ch_jet2;
  TFitParticleEtEtaPhi *fit_lepton;
  TFitParticleEtEtaPhi *fit_neutrino;

  TMatrixD error_hadronic_top_b_jet; 
  TMatrixD error_leptonic_top_b_jet;
  TMatrixD error_hadronic_w_ch_jet1;
  TMatrixD error_hadronic_w_ch_jet2;
  TMatrixD error_lepton;
  TMatrixD error_neutrino;

  TFitConstraintM *constrain_hadronic_top_M;
  TFitConstraintM *constrain_leptonic_top_M;
  TFitConstraintM *constrain_leptonic_W_M;

  TKinFitterDriver::ResultContatiner fit_result;

  std::vector<TKinFitterDriver::ResultContatiner> fit_result_vector;
  std::vector<TKinFitterDriver::ResultContatiner> GetResults();
  static bool Chi2Comparing(const TKinFitterDriver::ResultContatiner& rc1, const TKinFitterDriver::ResultContatiner& rc2){ return (rc1.chi2 < rc2.chi2); }
};

#endif
