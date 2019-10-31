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

void GenMatching_CHToCB::SetGens(std::vector<Gen> &all_gen_){
  AllGens = &all_gen_;
  //cout << "GenMatching_CHToCB::SetGens : num gens: " << AllGens->size() << endl;
}

void GenMatching_CHToCB::SetJets(std::vector<Jet> &all_jets_){
  jets = &all_jets_;
  njets = jets->size();
  //cout << "GenMatching_CHToCB::SetJets : num jets: " << njets << endl;
}

bool GenMatching_CHToCB::FindHardProcessParton(){
  extra_radiations.clear();

  //cout <<"GenMatching_CHToCB::FindHardProcessParton : start " << endl;
  for(UInt_t ig=0; ig<AllGens->size(); ig++){

    Int_t mother_idx = AllGens->at(ig).MotherIndex();
    if(mother_idx<0) continue;
    if(abs(AllGens->at(ig).PID()) == 15) continue; // no-tau
    //cout <<"GenMatching_CHToCB::FindHardProcessParton : no tau " << endl;
    if(AllGens->at(mother_idx).PID() == 6 &&
       (AllGens->at(ig).Status() == 23||AllGens->at(ig).Status() == 11) && 
       AllGens->at(ig).PID() == 5 
      ){
         //cout <<"GenMatching_CHToCB::FindHardProcessParton : found top b parton " << endl;
         b_from_top.truth_index = ig;
         b_from_top.matched_parton = AllGens->at(ig);
         b_from_top.parton_flavour = AllGens->at(ig).PID();
       }
    else if(AllGens->at(mother_idx).PID() == -6 &&
            (AllGens->at(ig).Status() == 23||AllGens->at(ig).Status() == 11) && 
            AllGens->at(ig).PID() == -5 
           ){
                //cout <<"GenMatching_CHToCB::FindHardProcessParton : found anti-top b parton " << endl;
                b_from_anti_top.truth_index = ig;
                b_from_anti_top.matched_parton = AllGens->at(ig);
                b_from_anti_top.parton_flavour = AllGens->at(ig).PID();
            }
    else if(abs(AllGens->at(mother_idx).PID()) == 24||abs(AllGens->at(mother_idx).PID()) == 37){
 
             //cout <<"GenMatching_CHToCB::FindHardProcessParton : found W(H+) decay product " << endl;
             if(AllGens->at(ig).Status() == 23||AllGens->at(ig).Status() == 11){
               if(abs(AllGens->at(ig).PID()) == 1 || 
                  abs(AllGens->at(ig).PID()) == 3 ||
                  abs(AllGens->at(ig).PID()) == 5
                 ){
                 //cout <<"GenMatching_CHToCB::FindHardProcessParton : found hadronic W down type jet " << endl;
                 down_type_quark.truth_index = ig;
                 down_type_quark.matched_parton = AllGens->at(ig);
                 down_type_quark.parton_flavour = AllGens->at(ig).PID();
               }
               else if(abs(AllGens->at(ig).PID()) == 4 ||
                       abs(AllGens->at(ig).PID()) == 2
                      ){
                 //cout <<"GenMatching_CHToCB::FindHardProcessParton : found hadronic W c jet " << endl;
                 up_type_quark.truth_index = ig;
                 up_type_quark.matched_parton = AllGens->at(ig);
                 up_type_quark.parton_flavour = AllGens->at(ig).PID();
               }

              if((AllGens->at(ig).Status() == 23||
                  AllGens->at(ig).Status() == 1 ||
                  AllGens->at(ig).Status() == 11) &&
                 (abs(AllGens->at(ig).PID())==11 || abs(AllGens->at(ig).PID())==13)
                ){
                   //cout <<"GenMatching_CHToCB::FindHardProcessParton : found lepton " << endl;
                   if(AllGens->at(ig).PID()>0) negative_lepton_charge =1;
                   else negative_lepton_charge =0;
                 }
              else if(abs(AllGens->at(ig).PID())==12 || abs(AllGens->at(ig).PID())==14){
                  //cout <<"GenMatching_CHToCB::FindHardProcessParton : found neutrino " << endl;
                  neutrino.truth_index = ig;
                  neutrino.matched_parton = AllGens->at(ig);
              }
            }
          }
    else{
      if(AllGens->at(ig).Status() == 23||AllGens->at(ig).Status() == 11){
        matchedPartonJet extra_radiation;
        extra_radiation.truth_index = ig;
        extra_radiation.matched_parton = AllGens->at(ig);
        extra_radiation.parton_flavour = AllGens->at(ig).PID();
        extra_radiations.push_back(extra_radiation);
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
       //cout <<"GenMatching_CHToCB::FindHardProcessParton : unmatched " << endl;
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

  for(std::vector<matchedPartonJet>::iterator it=extra_radiations.begin(); it!=extra_radiations.end(); it++){
    FindMinDeltaRMatching(*it);
  }

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

bool GenMatching_CHToCB::CheckFlavour(){

  if( b_from_top.parton_flavour != b_from_top.jet_parton_flavour ){
    return false;
  }
  if( b_from_anti_top.parton_flavour != b_from_anti_top.jet_parton_flavour ){
    return false;
  }
  if( down_type_quark.parton_flavour != down_type_quark.jet_parton_flavour ){
    return false;
  }
  if( up_type_quark.parton_flavour != up_type_quark.jet_parton_flavour){
    return false;
  }

  return true;
}

bool GenMatching_CHToCB::CheckAmbiguity(){

  std::vector<int> matched_jet_index;

  matched_jet_index.push_back(b_from_top.jet_index);
  matched_jet_index.push_back(b_from_anti_top.jet_index);
  matched_jet_index.push_back(down_type_quark.jet_index);
  matched_jet_index.push_back(up_type_quark.jet_index);
  for(std::vector<matchedPartonJet>::iterator it=extra_radiations.begin(); it!=extra_radiations.end(); it++){
    matched_jet_index.push_back(it->jet_index);
  }
  // check unique matching
  bool noAmbiguity=true;
  for(std::vector<int>::iterator it=matched_jet_index.begin(); it!=matched_jet_index.end(); it++){
    int cur = *it; 
    for(std::vector<int>::iterator it2=std::next(it,1); it2!=matched_jet_index.end(); it2++){
      if(cur==*it2){
        noAmbiguity=false;
        break;
      }
    }
  }
  return noAmbiguity;
}

bool GenMatching_CHToCB::FindMinDeltaRMatching(matchedPartonJet &partonjet){

  bool isfound = false;
  vector<double> deltaR;
  for(int i=0; i<njets; i++){
    deltaR.push_back(AllGens->at(partonjet.truth_index).DeltaR(jets->at(i)));
  }
  vector<double>::iterator min_deltaR = std::min_element(deltaR.begin(),deltaR.end());
  for(int i =0; i<njets; i++){
    if(*min_deltaR>0.4) break;
    if(*min_deltaR != deltaR[i]) continue;
    partonjet.matched_jet = jets->at(i);
    partonjet.jet_index = i;
    partonjet.jet_parton_flavour= jets->at(i).partonFlavour();
    isfound = true;
    break;
  }
  return isfound;

}

const GenMatching_CHToCB::matchedPartonJet *GenMatching_CHToCB::Get_hadronic_top_b_jet(){
  if(negative_lepton_charge==1){
    return &b_from_top;
  }
  else if(negative_lepton_charge==0){
    return &b_from_anti_top;
  }
  return NULL;
}

const GenMatching_CHToCB::matchedPartonJet *GenMatching_CHToCB::Get_leptonic_top_b_jet(){
  if(negative_lepton_charge==1){
    return &b_from_anti_top;
  }
  else if(negative_lepton_charge==0){
    return &b_from_top;
  }
  return NULL;
}

const GenMatching_CHToCB::matchedPartonJet *GenMatching_CHToCB::Get_up_type_jet(){
  return &up_type_quark;
}

const GenMatching_CHToCB::matchedPartonJet *GenMatching_CHToCB::Get_down_type_jet(){
  return &down_type_quark;
}

const GenMatching_CHToCB::matchedPartonJet *GenMatching_CHToCB::Get_neutrino(){
  return &neutrino;
}
