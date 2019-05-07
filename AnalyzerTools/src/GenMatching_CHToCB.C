#include "GenMatching_CHToCB.h"

GenMatching_CHToCB::GenMatching_CHToCB(){

  b_from_top.truth_index = -99999;
  b_from_anti_top.truth_index = -99999;
  down_type_quark.truth_index = -99999;
  up_type_quark.truth_index = -99999;
  neutrino.truth_index = -99999;
}

GenMatching_CHToCB::~GenMatching_CHToCB(){
}

void GenMatching_CHToCB::SetGens(std::vector<Gen> all_gen_){
  AllGens = all_gen_;
}

void GenMatching_CHToCB::SetJets(std::vector<Jet> all_jets_){
  jets = all_jets_;
  njets = jets.size();
}

bool GenMatching_CHToCB::FindHardProcessParton(){

  for(UInt_t ig=0; ig<AllGens.size(); ig++){

    Int_t mother_idx = AllGens.at(ig).MotherIndex();
    if(mother_idx<0) continue;
    if(abs(AllGens.at(ig).PID()) == 15) continue; // no-tau

    if(AllGens.at(mother_idx).PID() == 6 &&
       (AllGens.at(ig).Status() == 23||AllGens.at(ig).Status() == 11) && 
       AllGens.at(ig).PID() == 5 
      ){
         b_from_top.truth_index = ig;
         b_from_top.matched_parton = AllGens.at(ig);
       }
    else if(AllGens.at(mother_idx).PID() == -6 &&
            (AllGens.at(ig).Status() == 23||AllGens.at(ig).Status() == 11) && 
            AllGens.at(ig).PID() == -5 
           ){
                b_from_anti_top.truth_index = ig;
                b_from_anti_top.matched_parton = AllGens.at(ig);
            }
    else if(abs(AllGens.at(mother_idx).PID()) == 24||abs(AllGens.at(mother_idx).PID()) == 37){
 
             if(AllGens.at(ig).Status() == 23||AllGens.at(ig).Status() == 11){
               if(abs(AllGens.at(ig).PID())%2!=0){
                 down_type_quark.truth_index = ig;
                 down_type_quark.matched_parton = AllGens.at(ig);
               }
               else if(abs(AllGens.at(ig).PID()) == 4){
                 up_type_quark.truth_index = ig;
                 up_type_quark.matched_parton = AllGens.at(ig);
               }
               else if(abs(AllGens.at(ig).PID()) == 2){
                 up_type_quark.truth_index = ig;
                 up_type_quark.matched_parton = AllGens.at(ig);
               }
              if((AllGens.at(ig).Status() == 23||
                  AllGens.at(ig).Status() == 1 ||
                  AllGens.at(ig).Status() == 11) &&
                 (abs(AllGens.at(ig).PID())==11 || abs(AllGens.at(ig).PID())==13)
                ){
                   if(AllGens.at(ig).PID()>0) negative_lepton_charge =1;
                   else negative_lepton_charge =0;
                 }
              else if(abs(AllGens.at(ig).PID())==12 || abs(AllGens.at(ig).PID())==14){
                  neutrino.matched_parton = AllGens.at(ig);
              }
            }
          }
  } //end of for

  if(b_from_top.truth_index<0 ||
     b_from_anti_top.truth_index<0 ||
     down_type_quark.truth_index<0 ||
     up_type_quark.truth_index<0 ||
     neutrino.truth_index<0 ||
     negative_lepton_charge == -1
    ){
       return false;
     }
  else{
    return true;
  }
}

bool GenMatching_CHToCB::MatchJets(){
  bool is_top_found = false, is_anti_top_found = false;
  bool is_down_type_quark_found = false, is_up_type_quark_found = false;
  // parton-jet matching

  is_top_found = FindMinDeltaRMatching(b_from_top);
  is_anti_top_found = FindMinDeltaRMatching(b_from_anti_top);
  is_down_type_quark_found =FindMinDeltaRMatching(down_type_quark);
  is_up_type_quark_found = FindMinDeltaRMatching(up_type_quark);

  if(is_top_found==false ||
     is_anti_top_found==false ||
     is_down_type_quark_found==false ||
     is_up_type_quark_found==false
    ){
       return false;
     }
  else{
    return true;
  }

}

bool GenMatching_CHToCB::FindMinDeltaRMatching(matchedPartonJet &partonjet){

  bool isfound = false;
  vector<double> deltaR;
  for(int i=0; i<njets; i++){
    deltaR.push_back(AllGens.at(partonjet.truth_index).DeltaR(jets.at(i)));
  }
  vector<double>::iterator min_deltaR = std::min_element(deltaR.begin(),deltaR.end());
  for(int i =0; i<njets; i++){
    if(*min_deltaR>0.4) break;
    if(*min_deltaR != deltaR[i]) continue;
    partonjet.matched_jet = jets[i];
    isfound = true;
    break;
  }
  return isfound;

}

TLorentzVector GenMatching_CHToCB::Get_hadronic_top_b_jet(){
  if(negative_lepton_charge==1){
    return b_from_top.matched_jet;
  }
  else if(negative_lepton_charge==0){
    return b_from_anti_top.matched_jet;
  }
  return TLorentzVector();
}

TLorentzVector GenMatching_CHToCB::Get_leptonic_top_b_jet(){
  if(negative_lepton_charge==1){
    return b_from_anti_top.matched_jet;
  }
  else if(negative_lepton_charge==0){
    return b_from_top.matched_jet;
  }
  return TLorentzVector();
}

TLorentzVector GenMatching_CHToCB::Get_up_type_jet(){
  return up_type_quark.matched_jet;
}

TLorentzVector GenMatching_CHToCB::Get_down_type_jet(){
  return down_type_quark.matched_jet;
}

TLorentzVector GenMatching_CHToCB::Get_neutrino(){
  return neutrino.matched_parton;
}
