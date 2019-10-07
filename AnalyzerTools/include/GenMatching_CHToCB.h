#ifndef GenMatching_CHToCB_h
#define GenMatching_CHToCB_h

#include <map>
#include <vector>

#include "TString.h"

#include "Lepton.h"
#include "Muon.h"
#include "Electron.h"
#include "Jet.h"
#include "Gen.h"

class GenMatching_CHToCB{

public:

  GenMatching_CHToCB();
  ~GenMatching_CHToCB();

  struct matchedPartonJet{
    matchedPartonJet(){}
    ~matchedPartonJet(){}
    Int_t truth_index;
    Int_t jet_index;
    Int_t parton_flavour;
    Int_t jet_parton_flavour;
    TLorentzVector matched_parton;
    TLorentzVector matched_jet;
  };

  //TString MCSample;
  //void SetMCSample(TString s);
  void SetGens(std::vector<Gen> &all_gen_);
  void SetJets(std::vector<Jet> &all_jets_);
  //=== 4 parton matched : return true
  //=== if not, return false
  bool FindHardProcessParton();
  bool MatchJets();
  bool CheckFlavour();
  bool CheckAmbiguity();

  const GenMatching_CHToCB::matchedPartonJet *Get_hadronic_top_b_jet();
  const GenMatching_CHToCB::matchedPartonJet *Get_leptonic_top_b_jet();
  const GenMatching_CHToCB::matchedPartonJet *Get_down_type_jet();
  const GenMatching_CHToCB::matchedPartonJet *Get_up_type_jet();
  const GenMatching_CHToCB::matchedPartonJet *Get_neutrino();
private:

  bool FindMinDeltaRMatching(matchedPartonJet &partonjet);

  std::vector<Gen> *AllGens;
  std::vector<Jet> *jets;
  Int_t njets;

  matchedPartonJet b_from_top;
  matchedPartonJet b_from_anti_top;
  matchedPartonJet down_type_quark;
  matchedPartonJet up_type_quark;
  matchedPartonJet neutrino;
  Int_t negative_lepton_charge;

  std::vector<matchedPartonJet> extra_radiations;

};

#endif
