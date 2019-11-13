#include "JetCombinationTool.h"


JetCombinationTool::JetCombinationTool(){
}


JetCombinationTool::~JetCombinationTool(){
}


void JetCombinationTool::SetBtagVector(const std::vector<bool> &btag_vector_){
  btag_vector.clear();
  btag_vector = btag_vector_;
  njets = btag_vector.size();
  nbtags = std::accumulate(btag_vector.begin(),btag_vector.end(),0);
}


void JetCombinationTool::InitPermutationVector(){
  permutation_vector.clear();
  if(njets<4){
    std::cout << "njets is less than 4, abort"<< std::endl;
    exit(1);
  }
  for(unsigned int i=0; i<njets; i++){
    if(i==0) permutation_vector.push_back( HADRONIC_TOP_B );
    else if(i==1) permutation_vector.push_back( LEPTONIC_TOP_B );
    else if(i==2) permutation_vector.push_back( W_CH_UP_TYPE );
    else if(i==3) permutation_vector.push_back( W_CH_DOWN_TYPE );
    else permutation_vector.push_back( NONE );
  }
}


const std::vector<JetCombinationTool::JET_ASSIGNMENT>& JetCombinationTool::GetPermutationVector(){
  return permutation_vector;
}

void JetCombinationTool::FindJetIndex(){
  int n_found = 0;
  for(unsigned int i=0; i<permutation_vector.size(); i++){
    if(permutation_vector.at(i) == HADRONIC_TOP_B){
      had_top_b_jet_idx = i;
      n_found++;
    }
    else if(permutation_vector.at(i) == LEPTONIC_TOP_B){
      lep_top_b_jet_idx = i;
      n_found++;
    }
    else if(permutation_vector.at(i) == W_CH_UP_TYPE){
      up_type_jet_idx = i;
      n_found++;
    }
    else if(permutation_vector.at(i) == W_CH_DOWN_TYPE){
      down_type_jet_idx = i;
      n_found++;
    }
    if(n_found==4){
      break;
    }
  }

  return;
}


bool JetCombinationTool::NextPermutation(bool UseLeading4Jets){

  std::vector<JetCombinationTool::JET_ASSIGNMENT>::iterator begin = permutation_vector.begin();
  std::vector<JetCombinationTool::JET_ASSIGNMENT>::iterator end;
  if(UseLeading4Jets){
    end = begin+4;
  }
  else{
    end = permutation_vector.end();
  }
  return std::next_permutation(begin,end); //permutation in range of [begin,end)
}

bool JetCombinationTool::Check_BJet_Assignment(){

  int nbtags_in_four_jets=0;
  for(unsigned int i=0; i<permutation_vector.size(); i++){
    JET_ASSIGNMENT jet_assignment_idx = permutation_vector.at(i);
    bool IsBTagged = btag_vector.at(i);
    if(nbtags>=2){
      if( jet_assignment_idx == HADRONIC_TOP_B && IsBTagged ) nbtags_in_four_jets+=1;
      else if( jet_assignment_idx == LEPTONIC_TOP_B && IsBTagged ) nbtags_in_four_jets+=1;
    }
    if(nbtags>=3){
      if( jet_assignment_idx == W_CH_DOWN_TYPE && IsBTagged ) nbtags_in_four_jets+=1;
    }
  }

  bool true_bjet_assignment=false;
  if(nbtags==2 && nbtags_in_four_jets==2) true_bjet_assignment=true;
  else if(nbtags>=3 && nbtags_in_four_jets>=3) true_bjet_assignment=true;

  //cout << "JetCombinationTool::Check_BJet_Assignment : " << endl; 
  return true_bjet_assignment;
}


