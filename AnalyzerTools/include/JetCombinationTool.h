#ifndef JetCombinationTool_h
#define JetCombinationTool_h

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

class JetCombinationTool{

public:

  JetCombinationTool();	
  ~JetCombinationTool();

  enum JET_ASSIGNMENT{
    HADRONIC_TOP_B,
    LEPTONIC_TOP_B,
    W_CH_UP_TYPE,
    W_CH_DOWN_TYPE,
    NONE
  };

  void SetBtagVector(const std::vector<bool> &btag_vector_);
  void SetNJets(const int &njets_){ njets = njets_; }
  void InitPermutationVector();

  bool NextPermutation(bool UseLeading4Jets=false);
  const std::vector<JetCombinationTool::JET_ASSIGNMENT>& GetPermutationVector();
  void FindJetIndex();
  int Get_hadronic_top_b_jet_index(){ return had_top_b_jet_idx; };
  int Get_leptonic_top_b_jet_index(){ return lep_top_b_jet_idx; };
  int Get_up_type_jet_index(){ return up_type_jet_idx; };
  int Get_down_type_jet_index(){ return down_type_jet_idx; };

  bool Check_BJet_Assignment();

private:

  unsigned int njets;
  unsigned int nbtags;
  std::vector<bool> btag_vector;
  std::vector<JetCombinationTool::JET_ASSIGNMENT> permutation_vector;
  

  int had_top_b_jet_idx;
  int lep_top_b_jet_idx;
  int up_type_jet_idx;
  int down_type_jet_idx;

};

#endif
