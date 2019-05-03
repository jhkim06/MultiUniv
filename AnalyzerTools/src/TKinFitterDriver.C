#include "TKinFitterDriver.h"

TKinFitterDriver::TKinFitterDriver(){

  fitter = new TKinFitter("fitter","fitter");

  error_hadronic_top_b_jet = error_hadronic_top_b_jet(3,3); 
  error_leptonic_top_b_jet = error_leptonic_top_b_jet(3,3);
  error_hadronic_w_ch_jet1 = error_hadronic_w_ch_jet1(3,3);
  error_hadronic_w_ch_jet2 = error_hadronic_w_ch_jet2(3,3);
  error_lepton = error_lepton(3,3);
  error_neutrino = error_neutrino(3,3);

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

}


TKinFitterDriver::~TKinFitterDriver(){

  delete fitter;
  this->Clear();
}


void TKinFitterDriver::Clear(){

  delete fit_hadronic_top_b_jet; 
  delete fit_leptonic_top_b_jet;
  delete fit_hadronic_w_ch_jet1;
  delete fit_hadronic_w_ch_jet2;
  delete fit_lepton;
  delete fit_neutrino;

  delete constrain_hadronic_top_M;
  delete constrain_leptonic_top_M;
  delete constrain_leptonic_W_M;

  fit_hadronic_top_b_jet = NULL; 
  fit_leptonic_top_b_jet = NULL;
  fit_hadronic_w_ch_jet1 = NULL;
  fit_hadronic_w_ch_jet2 = NULL;
  fit_lepton = NULL;
  fit_neutrino = NULL;

  constrain_hadronic_top_M = NULL;
  constrain_leptonic_top_M = NULL;
  constrain_leptonic_W_M = NULL;

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


void TKinFitterDriver::SetHadronicBJets(TLorentzVector jet_){
  hadronic_top_b_jet = jet_;
  double Et = hadronic_top_b_jet.Et();
  double Eta = hadronic_top_b_jet.Eta();
  this->SetError(&error_hadronic_top_b_jet, Et, Eta);
  fit_hadronic_top_b_jet = new TFitParticleEtEtaPhi("hadronic_top_b_jet",
                                                    "hadronic_top_b_jet",
                                                    &hadronic_top_b_jet,
                                                    &error_hadronic_top_b_jet
                                                   );
}


void TKinFitterDriver::SetLeptonicBJets(TLorentzVector jet_){
  leptonic_top_b_jet=jet_;
  double Et = leptonic_top_b_jet.Et();
  double Eta = leptonic_top_b_jet.Eta();
  this->SetError(&error_leptonic_top_b_jet, Et, Eta);
  fit_leptonic_top_b_jet = new TFitParticleEtEtaPhi("leptonic_top_b_jet",
                                                    "leptonic_top_b_jet",
                                                    &leptonic_top_b_jet,
                                                    &error_leptonic_top_b_jet
                                                   );
}


void TKinFitterDriver::SetWCHUpTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet1=jet_;
  double Et = hadronic_w_ch_jet1.Et();
  double Eta = hadronic_w_ch_jet1.Eta();
  this->SetError(&error_hadronic_w_ch_jet1, Et, Eta);
  fit_hadronic_w_ch_jet1 = new TFitParticleEtEtaPhi("hadronic_w_ch_jet1",
                                                    "hadronic_w_ch_jet1",
                                                    &hadronic_w_ch_jet1,
                                                    &error_hadronic_w_ch_jet1
                                                   );
}


void TKinFitterDriver::SetWCHDownTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet2=jet_;
  double Et = hadronic_w_ch_jet2.Et();
  double Eta = hadronic_w_ch_jet2.Eta();
  this->SetError(&error_hadronic_w_ch_jet2, Et, Eta);
  fit_hadronic_w_ch_jet2 = new TFitParticleEtEtaPhi("hadronic_w_ch_jet2",
                                                    "hadronic_w_ch_jet2",
                                                    &hadronic_w_ch_jet2,
                                                    &error_hadronic_w_ch_jet2
                                                   );
}


void TKinFitterDriver::SetLepton(TLorentzVector lepton_){
  lepton=lepton_;
  fit_lepton = new TFitParticleEtEtaPhi("lepton",
                                        "lepton",
                                        &lepton,
                                        &error_lepton
                                       );
}


void TKinFitterDriver::SetMET(TLorentzVector met_){
  neutrino=met_; //TODO: will update this with Pz sol.
  fit_neutrino = new TFitParticleEtEtaPhi("neutrino",
                                          "neutrino",
                                          &neutrino,
                                          &error_neutrino
                                         );
}


void TKinFitterDriver::SetConstraint(){
  //TODO: will update to be able to set top-mass
  constrain_hadronic_top_M = new TFitConstraintM("hadronic_top_mass_constraint", "hadronic_top_mass_constraint", 0, 0, 172.5);
  constrain_leptonic_top_M = new TFitConstraintM("leptonic_top_mass_constraint", "leptonic_top_mass_constraint", 0, 0, 172.5);
  constrain_leptonic_W_M = new TFitConstraintM("leptonic_w_mass_constraint", "leptonic_w_mass_constraint", 0, 0, 80.4);
  // reset constrain
  constrain_hadronic_top_M->addParticles1(fit_hadronic_top_b_jet, fit_hadronic_w_ch_jet1, fit_hadronic_w_ch_jet2);
  constrain_leptonic_top_M->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino);
  constrain_leptonic_W_M->addParticles1(fit_lepton, fit_neutrino);
}


void TKinFitterDriver::SetFitter(){
  //add MeasParticles to vary Et,Eta,Phi
  fitter->addMeasParticle( fit_hadronic_top_b_jet );
  fitter->addMeasParticle( fit_leptonic_top_b_jet );
  fitter->addMeasParticle( fit_hadronic_w_ch_jet1 );
  fitter->addMeasParticle( fit_hadronic_w_ch_jet2 );
  //add UnmeasParticles not to vary Et,Eta,Phi
  fitter->addUnmeasParticle( fit_lepton );
  fitter->addUnmeasParticle( fit_neutrino );
  //add Constraint
  fitter->addConstraint( constrain_hadronic_top_M );
  fitter->addConstraint( constrain_leptonic_top_M );
  fitter->addConstraint( constrain_leptonic_W_M );
  //Set convergence criteria
  fitter->setMaxNbIter( 30 );
  fitter->setMaxDeltaS( 1e-2 );
  fitter->setMaxF( 1e-1 );
  fitter->setVerbosity(0);
}


void TKinFitterDriver::Fit(){
  this->Clear();
  status=-1; // -1 means fit not performed
  this->SetConstraint();
  this->SetFitter();
  status = fitter->fit();
  if(status==0){ // 0 means converge
    chi2 = fitter->getS(); // save chi2
    TLorentzVector *fitted_jet1, *fitted_jet2;
    TLorentzVector dijet;
    fitted_jet1 = fit_hadronic_w_ch_jet1->getCurr4Vec(); // get address of fitted object
    fitted_jet2 = fit_hadronic_w_ch_jet2->getCurr4Vec(); // get address of fitted object
    dijet = (*fitted_jet1) + (*fitted_jet2);
    dijet_M = dijet.M(); // save dijet mass
  }
}


void TKinFitterDriver::FindBestChi2Fit(){
  this->Clear();
  best_chi2 = 99999999999; // init. with large number
  bool isUpdated = false;
  status=-1;
  do{
    this->Fit();
    if(status==0 && chi2 < best_chi2){
      best_chi2 = chi2;
      best_dijet_M = dijet_M;
      isUpdated=true;
    }
  }while(this->NextPermutation());
  status = isUpdated ? 0 : status; //0 means converge
}


double TKinFitterDriver::GetStatus(){
  return status;
}


double TKinFitterDriver::GetChi2(){
  return chi2;
}


double TKinFitterDriver::GetFittedDijetMass(){
  return dijet_M;
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
  return std::next_permutation(begin,end); //permutation in range of [begin,end)
}


void TKinFitterDriver::SetError(TMatrixD *matrix,  double Et, double Eta){
  (*matrix)(0,0) = this->ErrEt(Et,Eta);
  (*matrix)(1,1) = this->ErrEta(Et,Eta);
  (*matrix)(2,2) = this->ErrPhi(Et,Eta);
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
  return InvPerr2;
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
