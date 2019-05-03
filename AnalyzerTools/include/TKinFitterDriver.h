#ifndef TKinFitterDriver_h
#define TKinFitterDriver_h

#include "TString.h"
#include <iostream>
#include <numeric>

#include "TFitConstraintM.h"
#include "TFitParticleEtEtaPhi.h"
#include "TKinFitter.h"

using namespace std;

class TKinFitterDriver{

public:

  TKinFitterDriver();
  ~TKinFitterDriver();

  void SetAllObjects(std::vector<TLorentzVector> jet_vector_,
                     std::vector<bool> btag_vector_,
                     TLorentzVector lepton_,
                     TLorentzVector met_);
  void SetHadronicBJets(TLorentzVector jet_); // it doesn't check tagging status
  void SetLeptonicBJets(TLorentzVector jet_); // it doesn't check tagging status
  void SetWCHUpTypeJets(TLorentzVector jet_); // u/c jet from W(H+)
  void SetWCHDownTypeJets(TLorentzVector jet_); // d/s/b jet from W(H+)
  void SetLepton(TLorentzVector lepton_);
  void SetMET(TLorentzVector met_);
  void Fit();
  void FindBestChi2Fit();
  bool GetStatus();
  double GetChi2();
  double GetFittedDijetMass();

private:

  void Clear(); // clear objects except 'fitter'
  void SetError(TMatrixD *matrix,  double Et, double Eta);
  double ErrEt(double Et, double Eta); // hard coding parameter this time
  double ErrEta(double Et, double Eta); // hard coding parameter this time
  double ErrPhi(double Et, double Eta); // hard coding parameter this time
  void SetConstraint();
  void SetFitter();
  bool NextPermutation(bool UseLeading4Jets=false);

  TKinFitter *fitter;

  std::vector<TLorentzVector> jet_vector;
  std::vector<bool> btag_vector;

  int njets;
  int nbtags;
  int status; //fitter status
  std::vector<int> permutation_vector;

  TLorentzVector hadronic_top_b_jet; // b jet comes from hadronic top 
  TLorentzVector leptonic_top_b_jet; // b jet comes from leptonic top
  TLorentzVector hadronic_w_ch_jet1; // u/c jet comes from W(H+)
  TLorentzVector hadronic_w_ch_jet2; // d/s/b jet comes from W(H+)
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

  double chi2;
  double dijet_M;
  double best_chi2;
  double best_dijet_M;

};

#endif
