#include "TKinFitterDriver.h"

TKinFitterDriver::TKinFitterDriver(){

}


TKinFitterDriver::TKinFitterDriver(int DataYear_){

  DataYear = DataYear_;

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

  ts_correction = new TSCorrection(DataYear);
  ts_correction->ReadFittedError("fit_error_pythia.txt");
  ts_correction->ReadFittedMean("fit_mean_pythia.txt");

  fit_hadronic_top_b_jet = new TFitParticleEtEtaPhi();
  fit_leptonic_top_b_jet = new TFitParticleEtEtaPhi();
  fit_hadronic_w_ch_jet1 = new TFitParticleEtEtaPhi();
  fit_hadronic_w_ch_jet2 = new TFitParticleEtEtaPhi();
  fit_lepton = new TFitParticleEtEtaPhi();
  fit_neutrino =  new TFitParticleEtEtaPhi();

  constrain_hadronic_top_M = new TFitConstraintM("hadronic_top_mass_constraint", "hadronic_top_mass_constraint", 0, 0, 172.5);
  constrain_leptonic_top_M = new TFitConstraintM("leptonic_top_mass_constraint", "leptonic_top_mass_constraint", 0, 0, 172.5);
  constrain_leptonic_W_M = new TFitConstraintM("leptonic_w_mass_constraint", "leptonic_w_mass_constraint", 0, 0, 80.4);
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
  delete ts_correction;
}


void TKinFitterDriver::SetDataYear(int i){
  DataYear = i;
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
  METv = met_;
  this->SetLepton(lepton_);
  
  //cout <<"TKinFitterDriver::SetAllObjects : " << endl;
}


void TKinFitterDriver::SetHadronicTopBJets(TLorentzVector jet_){
  hadronic_top_b_jet = jet_;
  double Et = hadronic_top_b_jet.Et();
  double Eta = hadronic_top_b_jet.Eta();
  double Phi = hadronic_top_b_jet.Phi();
  this->SetJetError(&error_hadronic_top_b_jet, Et, Eta, Phi, "b");
  corr_hadronic_top_b_jet = ts_correction->GetCorrectedJet("b",hadronic_top_b_jet);
  fit_hadronic_top_b_jet->~TFitParticleEtEtaPhi();
  new(fit_hadronic_top_b_jet) TFitParticleEtEtaPhi("hadronic_top_b_jet",
                                                    "hadronic_top_b_jet",
                                                    &corr_hadronic_top_b_jet,
                                                    &error_hadronic_top_b_jet
                                                   );
  //cout <<"TKinFitterDriver::SetHadronicTopBJets : " << endl;

}


void TKinFitterDriver::SetLeptonicTopBJets(TLorentzVector jet_){
  leptonic_top_b_jet=jet_;
  double Et = leptonic_top_b_jet.Et();
  double Eta = leptonic_top_b_jet.Eta();
  double Phi = leptonic_top_b_jet.Phi();
  this->SetJetError(&error_leptonic_top_b_jet, Et, Eta, Phi, "b");
  corr_leptonic_top_b_jet = ts_correction->GetCorrectedJet("b",leptonic_top_b_jet);
  fit_leptonic_top_b_jet->~TFitParticleEtEtaPhi();
  new(fit_leptonic_top_b_jet) TFitParticleEtEtaPhi("leptonic_top_b_jet",
                                                    "leptonic_top_b_jet",
                                                    &corr_leptonic_top_b_jet,
                                                    &error_leptonic_top_b_jet
                                                   );
  //cout <<"TKinFitterDriver::SetLeptonicTopBJets : " << endl;
}


void TKinFitterDriver::SetWCHUpTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet1=jet_;
  double Et = hadronic_w_ch_jet1.Et();
  double Eta = hadronic_w_ch_jet1.Eta();
  double Phi = hadronic_w_ch_jet1.Phi();
  this->SetJetError(&error_hadronic_w_ch_jet1, Et, Eta, Phi, "udsc");
  corr_hadronic_w_ch_jet1 = ts_correction->GetCorrectedJet("udsc",hadronic_w_ch_jet1);
  fit_hadronic_w_ch_jet1->~TFitParticleEtEtaPhi();
  new(fit_hadronic_w_ch_jet1) TFitParticleEtEtaPhi("hadronic_w_ch_jet1",
                                                    "hadronic_w_ch_jet1",
                                                    &corr_hadronic_w_ch_jet1,
                                                    &error_hadronic_w_ch_jet1
                                                   );
  //cout <<"TKinFitterDriver::SetWCHUpTypeJets : " << endl;
}


void TKinFitterDriver::SetWCHDownTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet2=jet_;
  double Et = hadronic_w_ch_jet2.Et();
  double Eta = hadronic_w_ch_jet2.Eta();
  double Phi = hadronic_w_ch_jet2.Phi();
  TString flav =  nbtags>2 ? "b":"udsc";
  this->SetJetError(&error_hadronic_w_ch_jet2, Et, Eta, Phi, flav);
  corr_hadronic_w_ch_jet2 = ts_correction->GetCorrectedJet(flav, hadronic_w_ch_jet2);
  fit_hadronic_w_ch_jet2->~TFitParticleEtEtaPhi();
  new(fit_hadronic_w_ch_jet2) TFitParticleEtEtaPhi("hadronic_w_ch_jet2",
                                                    "hadronic_w_ch_jet2",
                                                    &corr_hadronic_w_ch_jet2,
                                                    &error_hadronic_w_ch_jet2
                                                   );
  //cout << "TKinFitterDriver::SetWCHDownTypeJets : " << endl;
}


void TKinFitterDriver::SetLepton(TLorentzVector lepton_){
  lepton=lepton_;
  double Et = lepton.Et();
  double Eta = lepton.Eta();
  //this->SetError(&error_lepton, Et, Eta);
  error_lepton(0,0)=TMath::Power(0.03*Et,2);
  error_lepton(1,1)=TMath::Power(0.03*Eta,2);
  error_lepton(2,2)=TMath::Power(0.03*lepton.Phi(),2);
  fit_lepton->~TFitParticleEtEtaPhi();
  new(fit_lepton) TFitParticleEtEtaPhi("lepton",
                                        "lepton",
                                        &lepton,
                                        &error_lepton
                                       );
  //cout << "TKinFitterDriver::SetLepton : " << endl;
}


void TKinFitterDriver::SetMET(TLorentzVector met_){
  METv = met_;
}


void TKinFitterDriver::SetNeutrino(TLorentzVector met_, int i){

  double Pz = neutrino_pz[i];
  neutrino.SetPxPyPzE(met_.Px(),met_.Py(), Pz, TMath::Sqrt(met_.E()*met_.E()+Pz*Pz));
  /*
  TLorentzVector unclustered_energy = -met_;
  unclustered_energy -= hadronic_top_b_jet;
  unclustered_energy -= leptonic_top_b_jet;
  unclustered_energy -= hadronic_w_ch_jet1;
  unclustered_energy -= hadronic_w_ch_jet2;
  unclustered_energy -= lepton;
  unclustered_energy.SetPz(0);
  unclustered_energy.SetE(unclustered_energy.Et());
  */
  this->SetJetError(&error_neutrino,
		    met_.Et(), 0.001, 0.001, "udscb");
  fit_neutrino->~TFitParticleEtEtaPhi();
  new(fit_neutrino) TFitParticleEtEtaPhi("neutrino",
                                          "neutrino",
                                          &neutrino,
                                          &error_neutrino
                                         );
  
  //cout << "TKinFitterDriver::SetNeutrino : " << endl;
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


bool TKinFitterDriver::Kinematic_Cut(){
  TLorentzVector hadronic_top = hadronic_top_b_jet + hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  double hadronic_top_mass = hadronic_top.M();
  return (hadronic_top_mass > 100 && hadronic_top_mass < 240);
}


void TKinFitterDriver::SetConstraint(){
  //TODO: will update to be able to set top-mass
  // reset constrain
  constrain_hadronic_top_M->Clear();
  constrain_hadronic_top_M->addParticles1(fit_hadronic_top_b_jet, fit_hadronic_w_ch_jet1, fit_hadronic_w_ch_jet2);
  constrain_leptonic_top_M->Clear();
  constrain_leptonic_top_M->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino);
  constrain_leptonic_W_M->Clear();
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
  fitter->setMaxNbIter( 50 ); //50 is default
  fitter->setMaxDeltaS( 1e-2 );
  fitter->setMaxF( 1 ); //1e-1 is default
  fitter->setVerbosity(1);
  //cout << "TKinFitterDriver::SetFitter : " << endl;
}


void TKinFitterDriver::Fit(){
  fit_result.status=-1; // -1 means fit not performed
  this->SetConstraint();
  this->SetFitter();
  fit_result.status = fitter->fit();
  // save kinematic variable TODO: will make a method
  TLorentzVector hadronic_top = hadronic_top_b_jet + hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  fit_result.hadronic_top_M = hadronic_top.M();
  fit_result.hadronic_top_b_pt = hadronic_top_b_jet.Pt();
  fit_result.leptonic_top_b_pt = leptonic_top_b_jet.Pt();
  fit_result.w_ch_up_type_pt = hadronic_w_ch_jet1.Pt();
  fit_result.w_ch_down_type_pt = hadronic_w_ch_jet2.Pt();

  fit_result.chi2 = 9999999;
  if(fit_result.status==0){ // 0 means converge
    fit_result.chi2 = fitter->getS(); // save chi2
    const TLorentzVector *fitted_jet1 = fit_hadronic_w_ch_jet1->getCurr4Vec(); // get address of fitted object
    const TLorentzVector *fitted_jet2 = fit_hadronic_w_ch_jet2->getCurr4Vec(); // get address of fitted object
    const TLorentzVector fitted_dijet = (*fitted_jet1) + (*fitted_jet2);
    fit_result.fitted_dijet_M = fitted_dijet.M(); // save dijet mass
    const TLorentzVector *initial_jet1 = fit_hadronic_w_ch_jet1->getIni4Vec(); // get address of fitted object
    const TLorentzVector *initial_jet2 = fit_hadronic_w_ch_jet2->getIni4Vec(); // get address of fitted object
    const TLorentzVector initial_dijet = (*initial_jet1) + (*initial_jet2);
    fit_result.initial_dijet_M = initial_dijet.M(); // save dijet mass
    TLorentzVector corrected_dijet = corr_hadronic_w_ch_jet1 + corr_hadronic_w_ch_jet2;
    fit_result.corrected_dijet_M = corrected_dijet.M(); // save dijet mass
  }
  //cout << "TKinFitterDriver::Fit : " << endl;
}


void TKinFitterDriver::FindBestChi2Fit(bool UseLeading4Jets){
  fit_result_vector.clear();
  fit_result_vector.shrink_to_fit();
  // status -1 : fit not performed
  fit_result.status=-1;
  do{
    if(this->Check_BJet_Assignment() == false) continue;
    this->SetCurrentPermutationJets();
    //if(this->Kinematic_Cut() == false) continue;
      this->Sol_Neutrino_Pz();
      for(int i(0); i<2; i++){
	//if(!IsRealNeuPz && i==1) break;
	if(IsRealNeuPz){
	  this->SetNeutrino(METv, i);
	}
	else if(!IsRealNeuPz && i==0){
	  this->SetNeutrino(recal_METv, i);
	}
        this->Fit();
	fit_result_vector.push_back(fit_result);
      }
    }while(this->NextPermutation(UseLeading4Jets));
  std::sort(fit_result_vector.begin(), fit_result_vector.end(), Chi2Comparing);
}


int TKinFitterDriver::GetStatus(){
  return fit_result.status;
}

double TKinFitterDriver::GetChi2(){
  return fit_result.chi2;
}

double TKinFitterDriver::GetFittedDijetMass(){
  return fit_result.fitted_dijet_M;
}

double TKinFitterDriver::GetInitialDijetMass(){
  return fit_result.initial_dijet_M;
}

double TKinFitterDriver::GetCorrectedDijetMass(){
  return fit_result.corrected_dijet_M;
}

int TKinFitterDriver::GetBestStatus(){
  int out=-1;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).status;
  }
  return out;
}


double TKinFitterDriver::GetBestChi2(){
  double out=-1;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).chi2;
  }
  return out==9999999 ? -1. : out;
}


double TKinFitterDriver::GetBestFittedDijetMass(){
  double out=-1;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).fitted_dijet_M;
  }
  return out;
}


double TKinFitterDriver::GetBestInitialDijetMass(){
  double out=-1;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).initial_dijet_M;
  }
  return out;
}


double TKinFitterDriver::GetBestCorrectedDijetMass(){
  double out=-1;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).corrected_dijet_M;
  }
  return out;
}


std::vector<double> TKinFitterDriver::GetHadronicTopMassVector(bool IsConverge){
  std::vector<double> out_vector;
  for(auto &x : fit_result_vector){
    if(IsConverge==true && x.status==0){
      out_vector.push_back(x.hadronic_top_M);
    }
    else if(IsConverge==false && x.status!=0){
      out_vector.push_back(x.hadronic_top_M);
    }
  }
  return out_vector;
}

std::vector<double> TKinFitterDriver::GetHadronicTopBPtVector(bool IsConverge){
  std::vector<double> out_vector;
  for(auto &x : fit_result_vector){
    if(IsConverge==true && x.status==0){
      out_vector.push_back(x.hadronic_top_b_pt);
    }
    else if(IsConverge==false && x.status!=0){
      out_vector.push_back(x.hadronic_top_b_pt);
    }
  }
  return out_vector;
}
std::vector<double> TKinFitterDriver::GetLeptonicTopBPtVector(bool IsConverge){
  std::vector<double> out_vector;
  for(auto &x : fit_result_vector){
    if(IsConverge==true && x.status==0){
      out_vector.push_back(x.leptonic_top_b_pt);
    }
    else if(IsConverge==false && x.status!=0){
      out_vector.push_back(x.leptonic_top_b_pt);
    }
  }
  return out_vector;
}
std::vector<double> TKinFitterDriver::GetWCHDownTypePtVector(bool IsConverge){
  std::vector<double> out_vector;
  for(auto &x : fit_result_vector){
    if(IsConverge==true && x.status==0){
      out_vector.push_back(x.w_ch_up_type_pt);
    }
    else if(IsConverge==false && x.status!=0){
      out_vector.push_back(x.w_ch_up_type_pt);
    }
  }
  return out_vector;
}
std::vector<double> TKinFitterDriver::GetWCHUpTypePtVector(bool IsConverge){
  std::vector<double> out_vector;
  for(auto &x : fit_result_vector){
    if(IsConverge==true && x.status==0){
      out_vector.push_back(x.w_ch_down_type_pt);
    }
    else if(IsConverge==false && x.status!=0){
      out_vector.push_back(x.w_ch_down_type_pt);
    }
  }
  return out_vector;
}
std::vector<TKinFitterDriver::ResultContatiner> TKinFitterDriver::GetResults(){
  return fit_result_vector;
}


bool TKinFitterDriver::NextPermutation(bool UseLeading4Jets){

  std::vector<TKinFitterDriver::JET_ASSIGNMENT>::iterator begin = permutation_vector.begin();
  std::vector<TKinFitterDriver::JET_ASSIGNMENT>::iterator end;
  if(UseLeading4Jets){
    end = begin+4;
  }
  else{
    end = permutation_vector.end();
  }
  return std::next_permutation(begin,end); //permutation in range of [begin,end)
}


void TKinFitterDriver::SetJetError(TMatrixD *matrix,  double Et, double Eta, double Phi, TString flavour_key){
  (*matrix)(0,0) = TMath::Power(Et*this->JetErrorEt(Et, Eta, flavour_key), 2);
  (*matrix)(1,1) = TMath::Power(Eta*this->JetErrorEta(Et, Eta, flavour_key), 2);
  (*matrix)(2,2) = TMath::Power(Phi*this->JetErrorPhi(Et, Eta, flavour_key), 2);
}


double TKinFitterDriver::JetErrorEt(double Et, double Eta, TString flavour_key){
  return ts_correction->GetFittedError("Et", flavour_key, Et, Eta);
}


double TKinFitterDriver::JetErrorEta(double Et, double Eta, TString flavour_key){
  return ts_correction->GetFittedError("Eta", flavour_key, Et, Eta);
}


double TKinFitterDriver::JetErrorPhi(double Et, double Eta, TString flavour_key){
  return ts_correction->GetFittedError("Phi", flavour_key, Et, Eta);
}


void TKinFitterDriver::Sol_Neutrino_Pz(){
  
  double lepton_mass =  lepton.M();

  double k = 80.4*80.4/2.0 - lepton_mass*lepton_mass/2.0 + lepton.Px()*METv.Px() + lepton.Py()*METv.Py();
  double a = TMath::Power(lepton.Px(), 2.0) + TMath::Power(lepton.Py(), 2.0);
  double b = -2*k*lepton.Pz();                                                           
  double c = TMath::Power(lepton.Pt(), 2.0)*TMath::Power(METv.Pt(), 2.0) - TMath::Power(k, 2.0);

  double determinant = TMath::Power(b, 2.0) - 4*a*c;
  
  //cout << "determinant = " << determinant << endl;
  
  //real soluion
  if(determinant>=0){
    neutrino_pz[0] = (-b + TMath::Sqrt(determinant))/(2*a);                      
    neutrino_pz[1] = (-b - TMath::Sqrt(determinant))/(2*a);                      
    IsRealNeuPz = true;
  }
  else{
    neutrino_pz[0] = -b/(2*a);
    this->Resol_Neutrino_Pt();
    IsRealNeuPz = false;
  }

}


void TKinFitterDriver::Resol_Neutrino_Pt(){

  //cout << "Kinematic_Fitter_MVA::Resol_Neutino_Pt" << endl;
    
  //recal MET
  double lepton_mass = lepton.M();
  double cosine = TMath::Cos(METv.Phi());
  double sine = TMath::Sin(METv.Phi());
  
  double a = lepton.E()*lepton.E() - lepton.Pz()*lepton.Pz() - TMath::Power(lepton.Px()*cosine + lepton.Py()*sine , 2.0);
  double b = (lepton.Px()*cosine + lepton.Py()*sine)*(lepton_mass*lepton_mass - 80.4*80.4);
  double determinant = TMath::Power(lepton_mass*lepton_mass - 80.4*80.4, 2.)*(lepton.E()*lepton.E() - lepton.Pz()*lepton.Pz());
  
  //cout << "a = " << a << endl;
  //cout << "b = " << b << endl;
  //cout << "det = "<< determinant << endl;

  double met_recal[2];
  met_recal[0] = (-b + TMath::Sqrt(determinant))/2./a;
  met_recal[1] = (-b - TMath::Sqrt(determinant))/2./a;
  
  double mass_diff[2];
  TLorentzVector met_recal_vector[2];
  for(Int_t i=0; i<2; i++)
    {
      met_recal_vector[i].SetPxPyPzE(met_recal[i]*cosine, met_recal[i]*sine, 0, met_recal[i]);
      
      TLorentzVector w_lnu;
      w_lnu = lepton + met_recal_vector[i];
      
      double w_lnu_mass = w_lnu.M();
      mass_diff[i] = TMath::Abs(80.4 - w_lnu_mass);
      
      //cout << METv.Pt() << "\t" << met_recal[i] << "\t" << w_lnu.M() << "\t" << mass_diff[i] << endl;
    }
  //cout << endl;
  
  if(mass_diff[0]<mass_diff[1]) recal_METv = met_recal_vector[0];
  else recal_METv = met_recal_vector[1];
  
}
