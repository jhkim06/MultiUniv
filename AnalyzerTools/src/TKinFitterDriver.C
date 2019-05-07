#include "TKinFitterDriver.h"

TKinFitterDriver::TKinFitterDriver(){

  fitter = new TKinFitter("fitter","fitter");

  error_hadronic_top_b_jet.ResizeTo(3,3); 
  error_leptonic_top_b_jet.ResizeTo(3,3);
  error_hadronic_w_ch_jet1.ResizeTo(3,3);
  error_hadronic_w_ch_jet2.ResizeTo(3,3);
  error_lepton.ResizeTo(3,3);
  error_neutrino.ResizeTo(3,3);

  error_hadronic_top_b_jet.Zero(); 
  error_leptonic_top_b_jet.Zero();
  error_hadronic_w_ch_jet1.Zero();
  error_hadronic_w_ch_jet2.Zero();
  error_lepton.Zero();
  error_neutrino.Zero();

  fit_hadronic_top_b_jet = NULL; 
  fit_leptonic_top_b_jet = NULL;
  fit_hadronic_w_ch_jet1 = NULL;
  fit_hadronic_w_ch_jet2 = NULL;
  fit_lepton = NULL;
  fit_neutrino = NULL;

  constrain_hadronic_top_M = NULL;
  constrain_leptonic_top_M = NULL;
  constrain_leptonic_W_M = NULL;

  //cout <<"TKinFitterDriver::TKinFitterDriver : initialized" << endl;
}


TKinFitterDriver::~TKinFitterDriver(){

  delete fitter;
  delete fit_hadronic_top_b_jet; 
  delete fit_leptonic_top_b_jet;
  delete fit_hadronic_w_ch_jet1;
  delete fit_hadronic_w_ch_jet2;
  delete fit_lepton;
  delete fit_neutrino;

  delete constrain_hadronic_top_M;
  delete constrain_leptonic_top_M;
  delete constrain_leptonic_W_M;

}


void TKinFitterDriver::SetAllObjects(std::vector<Jet> jet_vector_,
                                     std::vector<bool> btag_vector_,
                                     TLorentzVector lepton_,
                                     TLorentzVector met_){

  //cout << "jet vector size " << jet_vector_.size() << endl; 
  //cout << "btag vector size " << btag_vector_.size() << endl; 
  jet_vector.clear();
  for(UInt_t i=0; i<jet_vector_.size(); i++){
    jet_vector.push_back((TLorentzVector)jet_vector_.at(i));
  }
  btag_vector.clear();
  for(UInt_t i=0; i<btag_vector_.size(); i++){
    btag_vector.push_back(btag_vector_.at(i));
  }
  njets = jet_vector.size();
  nbtags = std::accumulate(btag_vector.begin(), btag_vector.end(),0);

  permutation_vector.clear();
  for(int i(0); i<njets; i++){
    if(i==0) permutation_vector.push_back( HADRONIC_TOP_B );
    else if(i==1) permutation_vector.push_back( LEPTONIC_TOP_B );
    else if(i==2) permutation_vector.push_back( W_CH_UP_TYPE );
    else if(i==3) permutation_vector.push_back( W_CH_DOWN_TYPE );
    else permutation_vector.push_back( NONE );
    
  } 
 
  this->SetLepton(lepton_);
  this->SetMET(met_); 
  
  //cout <<"TKinFitterDriver::SetAllObjects : " << endl;
}


void TKinFitterDriver::SetHadronicTopBJets(TLorentzVector jet_){
  hadronic_top_b_jet = jet_;
  double Et = hadronic_top_b_jet.Et();
  double Eta = hadronic_top_b_jet.Eta();
  this->SetError(&error_hadronic_top_b_jet, Et, Eta);

  if(!fit_hadronic_top_b_jet) delete fit_hadronic_top_b_jet;
  fit_hadronic_top_b_jet = new TFitParticleEtEtaPhi("hadronic_top_b_jet",
                                                    "hadronic_top_b_jet",
                                                    &hadronic_top_b_jet,
                                                    &error_hadronic_top_b_jet
                                                   );
  //cout <<"TKinFitterDriver::SetHadronicTopBJets : " << endl;

}


void TKinFitterDriver::SetLeptonicTopBJets(TLorentzVector jet_){
  leptonic_top_b_jet=jet_;
  double Et = leptonic_top_b_jet.Et();
  double Eta = leptonic_top_b_jet.Eta();
  this->SetError(&error_leptonic_top_b_jet, Et, Eta);

  if(!fit_leptonic_top_b_jet) delete fit_leptonic_top_b_jet;
  fit_leptonic_top_b_jet = new TFitParticleEtEtaPhi("leptonic_top_b_jet",
                                                    "leptonic_top_b_jet",
                                                    &leptonic_top_b_jet,
                                                    &error_leptonic_top_b_jet
                                                   );
  //cout <<"TKinFitterDriver::SetLeptonicTopBJets : " << endl;
}


void TKinFitterDriver::SetWCHUpTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet1=jet_;
  double Et = hadronic_w_ch_jet1.Et();
  double Eta = hadronic_w_ch_jet1.Eta();
  this->SetError(&error_hadronic_w_ch_jet1, Et, Eta);

  if(!fit_hadronic_w_ch_jet1) delete fit_hadronic_w_ch_jet1;
  fit_hadronic_w_ch_jet1 = new TFitParticleEtEtaPhi("hadronic_w_ch_jet1",
                                                    "hadronic_w_ch_jet1",
                                                    &hadronic_w_ch_jet1,
                                                    &error_hadronic_w_ch_jet1
                                                   );
  //cout <<"TKinFitterDriver::SetWCHUpTypeJets : " << endl;
}


void TKinFitterDriver::SetWCHDownTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet2=jet_;
  double Et = hadronic_w_ch_jet2.Et();
  double Eta = hadronic_w_ch_jet2.Eta();
  this->SetError(&error_hadronic_w_ch_jet2, Et, Eta);
  if(!fit_hadronic_w_ch_jet2) delete fit_hadronic_w_ch_jet2;
  fit_hadronic_w_ch_jet2 = new TFitParticleEtEtaPhi("hadronic_w_ch_jet2",
                                                    "hadronic_w_ch_jet2",
                                                    &hadronic_w_ch_jet2,
                                                    &error_hadronic_w_ch_jet2
                                                   );
  //cout << "TKinFitterDriver::SetWCHDownTypeJets : " << endl;
}


void TKinFitterDriver::SetLepton(TLorentzVector lepton_){
  lepton=lepton_;
  double Et = lepton.Et();
  double Eta = lepton.Eta();
  //this->SetError(&error_lepton, Et, Eta);
  error_lepton(0,0)=0.01;
  error_lepton(1,1)=0.01;
  error_lepton(2,2)=0.01;
  if(!fit_lepton) delete fit_lepton;
  fit_lepton = new TFitParticleEtEtaPhi("lepton",
                                        "lepton",
                                        &lepton,
                                        &error_lepton
                                       );
  //cout << "TKinFitterDriver::SetLepton : " << endl;
}


void TKinFitterDriver::SetMET(TLorentzVector met_){
  neutrino=met_; //TODO: will update this with Pz sol.
  double Et = neutrino.Et();
  double Eta = neutrino.Eta();
  //this->SetError(&error_neutrino, Et, Eta);
  error_neutrino(0,0)=0.01;
  error_neutrino(1,1)=0.01;
  error_neutrino(2,2)=0.01;
  if(!fit_neutrino) delete fit_neutrino;
  fit_neutrino = new TFitParticleEtEtaPhi("neutrino",
                                          "neutrino",
                                          &neutrino,
                                          &error_neutrino
                                         );
  
  //cout << "TKinFitterDriver::SetMET : " << endl;
}


void TKinFitterDriver::SetCurrentPermutationJets(){

  int k=-1,l=-1,m=-1,n=-1; // jet index
  for(UInt_t i=0; i<permutation_vector.size(); i++){
    JET_ASSIGNMENT jet_assignment_idx = permutation_vector.at(i);
    if( jet_assignment_idx == HADRONIC_TOP_B ) k=i;
    else if( jet_assignment_idx == LEPTONIC_TOP_B ) l=i;
    else if( jet_assignment_idx == W_CH_UP_TYPE ) m=i;
    else if( jet_assignment_idx == W_CH_DOWN_TYPE ) n=i;
  }
  //cout << k << l << m << n << endl;
  this->SetHadronicTopBJets( jet_vector.at(k) );
  this->SetLeptonicTopBJets( jet_vector.at(l) );
  this->SetWCHUpTypeJets( jet_vector.at(m) );
  this->SetWCHDownTypeJets( jet_vector.at(n) );

}


bool TKinFitterDriver::Check_BJet_Assignment(){

  int nbtags_in_four_jets=0;
  for(UInt_t i=0; i<permutation_vector.size(); i++){
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

  //cout << "TKinFitterDriver::Check_BJet_Assignment : " << endl; 
  return true_bjet_assignment;
}


void TKinFitterDriver::SetConstraint(){
  //TODO: will update to be able to set top-mass
  if(!constrain_hadronic_top_M) delete constrain_hadronic_top_M;
  if(!constrain_leptonic_top_M) delete constrain_leptonic_top_M;
  if(!constrain_leptonic_W_M) delete constrain_leptonic_W_M;
  constrain_hadronic_top_M = new TFitConstraintM("hadronic_top_mass_constraint", "hadronic_top_mass_constraint", 0, 0, 172.5);
  constrain_leptonic_top_M = new TFitConstraintM("leptonic_top_mass_constraint", "leptonic_top_mass_constraint", 0, 0, 172.5);
  constrain_leptonic_W_M = new TFitConstraintM("leptonic_w_mass_constraint", "leptonic_w_mass_constraint", 0, 0, 80.4);
  // reset constrain
  constrain_hadronic_top_M->addParticles1(fit_hadronic_top_b_jet, fit_hadronic_w_ch_jet1, fit_hadronic_w_ch_jet2);
  constrain_leptonic_top_M->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino);
  constrain_leptonic_W_M->addParticles1(fit_lepton, fit_neutrino);
}


void TKinFitterDriver::SetFitter(){
  fitter->reset();
  //add MeasParticles to vary Et,Eta,Phi
  fitter->addMeasParticle( fit_hadronic_top_b_jet );
  fitter->addMeasParticle( fit_leptonic_top_b_jet );
  fitter->addMeasParticle( fit_hadronic_w_ch_jet1 );
  fitter->addMeasParticle( fit_hadronic_w_ch_jet2 );
  //add UnmeasParticles not to vary Et,Eta,Phi
  // TODO: currently, fitter dose not fit MET.
  // To fit MET, it is required to know uncertainty of MET
  // Also, Px, Py should be constrained
  fitter->addMeasParticle( fit_lepton );
  fitter->addMeasParticle( fit_neutrino );
  //fitter->addUnmeasParticle( fit_lepton );
  //fitter->addUnmeasParticle( fit_neutrino );
  //add Constraint
  fitter->addConstraint( constrain_hadronic_top_M );
  fitter->addConstraint( constrain_leptonic_top_M );
  fitter->addConstraint( constrain_leptonic_W_M );
  //Set convergence criteria
  fitter->setMaxNbIter( 30 );
  fitter->setMaxDeltaS( 1e-2 );
  fitter->setMaxF( 1e-1 );
  fitter->setVerbosity(1);
  //cout << "TKinFitterDriver::SetFitter : " << endl;
}


void TKinFitterDriver::Fit(){
  status=-1; // -1 means fit not performed
  this->SetConstraint();
  this->SetFitter();
  status = fitter->fit();
  if(status==0){ // 0 means converge
    chi2 = fitter->getS(); // save chi2
    const TLorentzVector *fitted_jet1 = fit_hadronic_w_ch_jet1->getCurr4Vec(); // get address of fitted object
    const TLorentzVector *fitted_jet2 = fit_hadronic_w_ch_jet2->getCurr4Vec(); // get address of fitted object
    const TLorentzVector fitted_dijet = (*fitted_jet1) + (*fitted_jet2);
    fitted_dijet_M = fitted_dijet.M(); // save dijet mass
    const TLorentzVector *initial_jet1 = fit_hadronic_w_ch_jet1->getIni4Vec(); // get address of fitted object
    const TLorentzVector *initial_jet2 = fit_hadronic_w_ch_jet2->getIni4Vec(); // get address of fitted object
    const TLorentzVector initial_dijet = (*initial_jet1) + (*initial_jet2);
    initial_dijet_M = initial_dijet.M(); // save dijet mass
  }
  //cout << "TKinFitterDriver::Fit : " << endl;
}


void TKinFitterDriver::FindBestChi2Fit(bool UseLeading4Jets){
  best_chi2 = 99999999999; // init. with large number
  bool isUpdated = false;
  status=-1;
  do{
    if(this->Check_BJet_Assignment() == false) continue;
    this->SetCurrentPermutationJets();
    this->Fit();
    if(status==0 && chi2 < best_chi2){
      best_chi2 = chi2;
      best_fitted_dijet_M = fitted_dijet_M;
      best_initial_dijet_M = initial_dijet_M;
      isUpdated=true;
    }
  }while(this->NextPermutation(UseLeading4Jets));
  status = isUpdated ? 0 : status; //0 means converge
}


int TKinFitterDriver::GetStatus(){
  return status;
}


double TKinFitterDriver::GetChi2(){
  return chi2;
}


double TKinFitterDriver::GetFittedDijetMass(){
  return fitted_dijet_M;
}


double TKinFitterDriver::GetInitialDijetMass(){
  return initial_dijet_M;
}


double TKinFitterDriver::GetBestFittedDijetMass(){
  return best_fitted_dijet_M;
}


double TKinFitterDriver::GetBestInitialDijetMass(){
  return best_initial_dijet_M;
}



bool TKinFitterDriver::NextPermutation(bool UseLeading4Jets){

  std::vector<TKinFitterDriver::JET_ASSIGNMENT>::iterator begin = permutation_vector.begin();
  std::vector<TKinFitterDriver::JET_ASSIGNMENT>::iterator end;
  if(UseLeading4Jets){
    end = begin+4;
  }
  else{
    end = permutation_vector.begin();
  }
  return std::next_permutation(begin,end); //permutation in range of [begin,end)
}


void TKinFitterDriver::SetError(TMatrixD *matrix,  double Et, double Eta){
  (*matrix)(0,0) = this->ErrEt(Et, Eta);
  (*matrix)(1,1) = this->ErrEt(Et, Eta);
  (*matrix)(2,2) = this->ErrEt(Et, Eta);

}


double TKinFitterDriver::ErrEt(double Et, double Eta){
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 5.6;
    b = 1.25;
    c = 0.033;
  }
  else{
    a = 4.8;
    b = 0.89;
    c = 0.043;
  }
  InvPerr2 = (a * a) + (b * b) * Et + (c * c) * Et * Et;
  //return InvPerr2;
  return 20;
}


double TKinFitterDriver::ErrEta(double Et, double Eta){
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 1.215;
    b = 0.037;
    c = 7.941 * 0.0001;
  }
  else{
    a = 1.773;
    b = 0.034;
    c = 3.56 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}


double TKinFitterDriver::ErrPhi(double Et, double Eta){
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 6.65;
    b = 0.04;
    c = 8.49 * 0.00001;
  } 
  else{ 
    a = 2.908;
    b = 0.021;
    c = 2.59 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}
