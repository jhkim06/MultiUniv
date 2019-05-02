#include "TKinFitterDriver.h"

TKinFitterDriver::TKinFitterDriver(){
  fitter = new TKinFitter("fitter","fitter");
}


TKinFitterDriver::~TKinFitterDriver(){
  delete fitter;
}


void TKinFitterDriver::SetAllObjects(std::vector<TLorentzVector> jet_vector_,
                                     std::vector<bool> btag_vector_,
                                     TLorentzVector lepton_,
                                     TLorentzVector met_){

  jet_vector = jet_vector_;
  btag_vector = btag_vector_;
  lepton = lepton_;
  neutrino = met_; //TODO: will update this part

  njets = jet_vector.size();
  nbtags = std::accumulate(btag_vector.begin(), btag_vector.end(),0);

  for(int i(0); i<njets; i++){
    if(i<4){
      permutation_vector.push_back(i);
    }
    else{
      permutation_vector.push_back(4);
    }
  } 
  
}

bool TKinFitterDriver::NextPermutation(bool UseLeading4Jets){

  std::vector<int>::iterator begin = permutation_vector.begin();
  std::vector<int>::iterator end;
  if(UseLeading4Jets){
    end = begin+4;
  }
  else{
    end = permutation_vector.begin();
  }
  return std::next_permutation(begin,end);
}


void TKinFitterDriver::Fit(){
  do{

  }while(this->NextPermutation());
}

