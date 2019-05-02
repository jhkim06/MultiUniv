#ifndef TKinFitterDriver_h
#define TKinFitterDriver_h

#include "TString.h"
#include <iostream>

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
  void SetHadronicBJets(TLorentzVector jet);
  void SetLeptonicBJets(TLorentzVector jet);
  void SetWCHUpTypeJets(TLorentzVector jet); // u/c jet from W(H+)
  void SetWCHDownTypeJets(TLorentzVector jet); // d/s/b jet from W(H+)
  void SetLepton(TLorentzVector lepton_);
  void SetMET(TLorentzVector met_);
  void Fit();
  double GetChi2();
  double GetFittedDijetMass();
  void FindBestChi2();

private:

  bool NextPermutation(bool UseLeading4Jets=false);
  TKinFitter* fitter;
  std::vector<TLorentzVector> jet_vector;
  std::vector<bool> btag_vector;
  TLorentzVector lepton; // lepton comes from leptonic W
  TLorentzVector neutrino; // neutrino comes from leptonic W

  int njets;
  int nbtags;
  std::vector<int> permutation_vector;

  TLorentzVector hadronic_top_b_jet; // b jet comes from hadronic top 
  TLorentzVector leptonic_top_b_jet; // b jet comes from leptonic top
  TLorentzVector hadronic_w_ch_jet1; // u/c jet comes from W(H+)
  TLorentzVector hadronic_w_ch_jet2; // d/s/b jet comes from W(H+)

  double chi2;
};

#endif
