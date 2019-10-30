#include "TKinFitterDriver.h"

TKinFitterDriver::TKinFitterDriver(){

}


TKinFitterDriver::TKinFitterDriver(int DataYear_, bool useMLCut_, TString MCSample_){

  DataYear = DataYear_;
  this->SetMLCut(useMLCut_);
  if(useMLCut){
    this->initML();
  }
  MCSample = MCSample_;
  fitter = new TKinFitter("fitter","fitter");

  error_hadronic_top_b_jet.ResizeTo(1,1); 
  error_leptonic_top_b_jet.ResizeTo(1,1);
  error_hadronic_w_ch_jet1.ResizeTo(1,1);
  error_hadronic_w_ch_jet2.ResizeTo(1,1);
  error_lepton.ResizeTo(1,1);
  error_neutrino_pxpy.ResizeTo(2,2);

  error_hadronic_top_b_jet.Zero(); 
  error_leptonic_top_b_jet.Zero();
  error_hadronic_w_ch_jet1.Zero();
  error_hadronic_w_ch_jet2.Zero();
  error_lepton.Zero();
  error_neutrino_pxpy.Zero();

  ts_correction = new TSCorrection(DataYear);
  ts_correction->ReadFittedError("fit_error_pythia.txt");
  ts_correction->ReadFittedMean("fit_mean_pythia.txt");

  fit_hadronic_top_b_jet = new TFitParticlePt();
  fit_leptonic_top_b_jet = new TFitParticlePt();
  fit_hadronic_w_ch_jet1 = new TFitParticlePt();
  fit_hadronic_w_ch_jet2 = new TFitParticlePt();
  fit_extra_jet = new TFitParticlePt();
  fit_lepton = new TFitParticlePt();
  fit_neutrino_pxpy =  new TFitParticlePxPy();
  fit_neutrino_pz =  new TFitParticlePz();

  constrain_hadronic_top_M = new TFitConstraintM("hadronic_top_mass_constraint", "hadronic_top_mass_constraint", 0, 0, 172.5);
  //constrain_hadronic_top_MGaus = new TFitConstraintMGaus("hadronic_top_mass_constraint", "hadronic_top_mass_constraint", 0, 0, 172.5, 1.5);
  constrain_leptonic_top_M = new TFitConstraintM("leptonic_top_mass_constraint", "leptonic_top_mass_constraint", 0, 0, 172.5);
  //constrain_leptonic_top_MGaus = new TFitConstraintMGaus("leptonic_top_mass_constraint", "leptonic_top_mass_constraint", 0, 0, 172.5, 1.5);
  constrain_leptonic_W_M = new TFitConstraintM("leptonic_w_mass_constraint", "leptonic_w_mass_constraint", 0, 0, 80.4);
  //constrain_leptonic_W_MGaus = new TFitConstraintMGaus("leptonic_w_mass_constraint", "leptonic_w_mass_constraint", 0, 0, 80.4, 2.085);
  //cout <<"TKinFitterDriver::TKinFitterDriver : initialized" << endl;
}

void TKinFitterDriver::initML(){
  if(gSystem->Load("libTMVA.so")){
    cout << "TKinFitterDriver::initML,   libTMVA.so is not loaded" << endl;
    exit(EXIT_FAILURE);
  }
  TMVA::Tools::Instance();
  //TMVA::PyMethodBase::PyInitialize();
  tmva_reader = new TMVA::Reader();
  tmva_reader->AddVariable((TString)"leptonic_top_mass",&leptonic_top_mass);
  tmva_reader->AddVariable((TString)"tt_deltaR",&tt_deltaR);
  tmva_reader->AddVariable((TString)"dijet_cosThetaTB",&dijet_cosThetaTB);
  tmva_reader->AddVariable((TString)"dijet_cosThetaTC",&dijet_cosThetaTC);
  tmva_reader->AddVariable((TString)"W_MT",&W_MT);
  tmva_reader->AddVariable((TString)"up_type_jet_pt",&up_type_jet_pt);
  tmva_reader->AddVariable((TString)"had_top_pt",&had_top_pt);
  tmva_reader->AddVariable((TString)"hadronic_top_mass",&hadronic_top_mass);
  tmva_reader->AddVariable((TString)"had_top_b_jet_pt",&had_top_b_jet_pt);
  tmva_reader->AddVariable((TString)"dijet_deltaR",&dijet_deltaR);
  tmva_reader->AddVariable((TString)"lep_top_pt",&lep_top_pt);
  tmva_reader->AddVariable((TString)"tt_MT",&tt_MT);
  tmva_reader->AddVariable((TString)"down_type_jet_pt",&down_type_jet_pt);
  tmva_reader->AddVariable((TString)"lep_top_b_jet_pt",&lep_top_b_jet_pt);
  tmva_reader->AddVariable((TString)"dijet_deltaEta",&dijet_deltaEta);

  TString base_path= getenv("DATA_DIR"); 
  base_path += "/" + TString::Itoa(DataYear,10) + "/TMVAClassification/";
  std::map<TString, TString> methods;
  //TString MCSample_ = MCSample.Contains("CHToCB")?MCSample:"TTLJ_powheg";
  for(TString MCSample_ : {"TTLJ_powheg", "CHToCB_M120"}){
    methods[Form("BDT_%s_4j_2b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"4j","2b");
    methods[Form("BDT_%s_5j_2b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"5j","2b");
    methods[Form("BDT_%s_6j_2b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"6j","2b");
    methods[Form("BDT_%s_4j_3b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"4j","3b");
    methods[Form("BDT_%s_5j_3b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"5j","3b");
    methods[Form("BDT_%s_6j_3b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"6j","3b");
  }
  for(auto &method : methods){
    tmva_reader->BookMVA(method.first,method.second);
  }
}


TKinFitterDriver::~TKinFitterDriver(){
  delete fitter;

  delete fit_hadronic_top_b_jet;
  delete fit_leptonic_top_b_jet;
  delete fit_hadronic_w_ch_jet1;
  delete fit_hadronic_w_ch_jet2;
  delete fit_extra_jet;
  delete fit_lepton;
  delete fit_neutrino_pxpy;
  delete fit_neutrino_pz;

  delete constrain_hadronic_top_M;
  //delete constrain_hadronic_top_MGaus;
  delete constrain_leptonic_top_M;
  //delete constrain_leptonic_top_MGaus;
  delete constrain_leptonic_W_M;
  //delete constrain_leptonic_W_MGaus;
  delete ts_correction;
  if(useMLCut){
    delete tmva_reader;
  }
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
  double Pt = hadronic_top_b_jet.Pt();
  double Eta = hadronic_top_b_jet.Eta();
  double Phi = hadronic_top_b_jet.Phi();
  this->SetJetError(&error_hadronic_top_b_jet, Pt, Eta, Phi, "b");
  corr_hadronic_top_b_jet = ts_correction->GetCorrectedJet("b",hadronic_top_b_jet);
  fit_hadronic_top_b_jet->~TFitParticlePt();
  new(fit_hadronic_top_b_jet) TFitParticlePt("hadronic_top_b_jet",
                                                    "hadronic_top_b_jet",
                                                    &corr_hadronic_top_b_jet,
                                                    &error_hadronic_top_b_jet
                                                   );
  //cout <<"TKinFitterDriver::SetHadronicTopBJets : " << endl;

}


void TKinFitterDriver::SetLeptonicTopBJets(TLorentzVector jet_){
  leptonic_top_b_jet=jet_;
  double Pt = leptonic_top_b_jet.Pt();
  double Eta = leptonic_top_b_jet.Eta();
  double Phi = leptonic_top_b_jet.Phi();
  this->SetJetError(&error_leptonic_top_b_jet, Pt, Eta, Phi, "b");
  corr_leptonic_top_b_jet = ts_correction->GetCorrectedJet("b",leptonic_top_b_jet);
  fit_leptonic_top_b_jet->~TFitParticlePt();
  new(fit_leptonic_top_b_jet) TFitParticlePt("leptonic_top_b_jet",
                                                    "leptonic_top_b_jet",
                                                    &corr_leptonic_top_b_jet,
                                                    &error_leptonic_top_b_jet
                                                   );
  //cout <<"TKinFitterDriver::SetLeptonicTopBJets : " << endl;
}


void TKinFitterDriver::SetWCHUpTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet1=jet_;
  double Pt = hadronic_w_ch_jet1.Pt();
  double Eta = hadronic_w_ch_jet1.Eta();
  double Phi = hadronic_w_ch_jet1.Phi();
  this->SetJetError(&error_hadronic_w_ch_jet1, Pt, Eta, Phi, "udsc");
  corr_hadronic_w_ch_jet1 = ts_correction->GetCorrectedJet("udsc",hadronic_w_ch_jet1);
  fit_hadronic_w_ch_jet1->~TFitParticlePt();
  new(fit_hadronic_w_ch_jet1) TFitParticlePt("hadronic_w_ch_jet1",
                                                    "hadronic_w_ch_jet1",
                                                    &corr_hadronic_w_ch_jet1,
                                                    &error_hadronic_w_ch_jet1
                                                   );
  //cout <<"TKinFitterDriver::SetWCHUpTypeJets : " << endl;
}


void TKinFitterDriver::SetWCHDownTypeJets(TLorentzVector jet_){
  hadronic_w_ch_jet2=jet_;
  double Pt = hadronic_w_ch_jet2.Pt();
  double Eta = hadronic_w_ch_jet2.Eta();
  double Phi = hadronic_w_ch_jet2.Phi();
  TString flav =  nbtags>2 ? "b":"udsc";
  this->SetJetError(&error_hadronic_w_ch_jet2, Pt, Eta, Phi, flav);
  corr_hadronic_w_ch_jet2 = ts_correction->GetCorrectedJet(flav, hadronic_w_ch_jet2);
  fit_hadronic_w_ch_jet2->~TFitParticlePt();
  new(fit_hadronic_w_ch_jet2) TFitParticlePt("hadronic_w_ch_jet2",
                                                    "hadronic_w_ch_jet2",
                                                    &corr_hadronic_w_ch_jet2,
                                                    &error_hadronic_w_ch_jet2
                                                   );
  //cout << "TKinFitterDriver::SetWCHDownTypeJets : " << endl;
}


void TKinFitterDriver::SetLepton(TLorentzVector lepton_){
  lepton=lepton_;
  double Pt = lepton.Pt();
  //double Eta = lepton.Eta();
  //this->SetError(&error_lepton, Pt, Eta);
  error_lepton(0,0)=TMath::Power(0.01*Pt,2);
  //error_lepton(1,1)=TMath::Power(0.03*Eta,2);
  //error_lepton(2,2)=TMath::Power(0.03*lepton.Phi(),2);
  fit_lepton->~TFitParticlePt();
  new(fit_lepton) TFitParticlePt("lepton",
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

  double Pz = neutrino_pz_sol[i];
  neutrino_pxpy.SetPxPyPzE(met_.Px(),met_.Py(), 0., met_.E());
  neutrino_pz.SetPxPyPzE(0., 0., Pz, fabs(Pz));

  double error_neutrino_px=0., error_neutrino_py=0.;
  for(auto &x : jet_vector){
    double Pt = x.Pt();
    double Px = x.Px();
    double Py = x.Py();
    double Eta = x.Eta();
    double error_ts_corr = this->JetErrorPt(Pt, Eta, "udscb");
    error_neutrino_px+=(error_ts_corr*Px)*(error_ts_corr*Px);
    error_neutrino_py+=(error_ts_corr*Py)*(error_ts_corr*Py);
  }
  error_neutrino_pxpy(0,0) = error_neutrino_px;
  error_neutrino_pxpy(1,1) = error_neutrino_py;
  //this->SetUnclError(&error_neutrino_pxpy, met_);
  fit_neutrino_pxpy->~TFitParticlePxPy();
  new(fit_neutrino_pxpy) TFitParticlePxPy("neutrino_pxpy",
                                          "neutrino_pxpy",
                                          &neutrino_pxpy,
                                          &error_neutrino_pxpy
                                         );
  
  fit_neutrino_pz->~TFitParticlePz();
  new(fit_neutrino_pz) TFitParticlePz("neutrino_pz",
		                      "neutrino_pz",
				      &neutrino_pz,
				      NULL
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


void TKinFitterDriver::updatesMLVariables(){

  TLorentzVector h_top = hadronic_top_b_jet + hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  TLorentzVector l_W = leptonic_top_b_jet + lepton; //XXX wrong
  TLorentzVector l_top = l_W + METv;
  TLorentzVector TT = h_top + l_top;

  had_top_b_jet_pt = hadronic_top_b_jet.Pt();   //  1
  lep_top_b_jet_pt = leptonic_top_b_jet.Pt();   //  2
  up_type_jet_pt = hadronic_w_ch_jet1.Pt();     //  3
  down_type_jet_pt = hadronic_w_ch_jet2.Pt();   //  4
  dijet_deltaR = hadronic_w_ch_jet1.DeltaR(hadronic_w_ch_jet2);       //  5
  dijet_deltaEta = fabs(hadronic_w_ch_jet1.Eta() - hadronic_w_ch_jet2.Eta());     //  6
  dijet_cosThetaTC = cos(h_top.Theta()-hadronic_w_ch_jet1.Theta());   //  7 
  dijet_cosThetaTB = cos(h_top.Theta()-hadronic_w_ch_jet2.Theta());   //  8
  hadronic_top_mass = h_top.M();  //  9
  leptonic_top_mass = l_top.M();  // 10
  W_MT = l_W.Mt();               // 11
  tt_MT = TT.Mt();              // 12
  tt_deltaR = h_top.DeltaR(l_top);          // 13
  had_top_pt = h_top.Pt();         // 14
  lep_top_pt = l_top.Pt();         // 15
}


bool TKinFitterDriver::ML_Cut(){
  if(useMLCut==false){
    return true;
  }
  this->updatesMLVariables();
  // XXX: let's hard code this time
  TString method ="BDT_%s";
  method += njets==4?
              "_4j":njets==5?
                "_5j":njets>=6?
	          "_6j":"_NULL";
  method += nbtags==2?
	      "_2b":nbtags>=3?
	        "_3b":"_NULL";
  double MLoutput1 = tmva_reader->EvaluateMVA(Form(method.Data(),"TTLJ_powheg"));
  double MLoutput2 = tmva_reader->EvaluateMVA(Form(method,"CHToCB_M120"));
  //cout << MLoutput << endl;
  double cut1 = 0., cut2 = 0.;
  cut1 = this->GetMLCut("TTLJ_powheg"); //TODO add function to set cut and selecte MVA method
  cut2 = this->GetMLCut("CHToCB_M120"); //TODO add function to set cut and selecte MVA method
  if(MLoutput1>cut1 || MLoutput2>cut2){
    return true;
  }
  else{
    return false;
  }
}

double TKinFitterDriver::GetMLCut(TString sample){
  double out=-999;
  if(sample.Contains("TTLJ_powheg")){
    if(njets==4){
      if(nbtags==2){
        out=-0.0347;
      }
      else if(nbtags>=3){
        out=-0.0998;
      }
    }
    else if(njets==5){
      if(nbtags==2){
        out=-0.08;
      }
      else if(nbtags>=3){
        out=-0.0548;
      }
    }
    else if(njets>=6){
      if(nbtags==2){
        out=-0.0981;
      }
      else if(nbtags>=3){
        out=-0.0967;
      }
    }
  }
  else if(sample.Contains("CHToCB_M120")){
    if(njets==4){
      if(nbtags==2){
        out=-0.4588;
      }
      else if(nbtags>=3){
        out=-0.3195;
      }
    }
    else if(njets==5){
      if(nbtags==2){
        out=-0.1210;
      }
      else if(nbtags>=3){
        out=-0.0725;
      }
    }
    else if(njets>=6){
      if(nbtags==2){
        out=-0.09;
      }
      else if(nbtags>=3){
        out=-0.0518;
      }
    }
  }
  /*else if(sample.Contains("")){
    if(njets==4){
      if(nbtags==2){
        out=;
      }
      else if(nbtags>=3){
        out=;
      }
    }
    else if(njets==5){
      if(nbtags==2){
        out=;
      }
      else if(nbtags>=3){
        out=;
      }
    }
    else if(njets>=6){
      if(nbtags==2){
        out=;
      }
      else if(nbtags>=3){
        out=;
      }
    }
  }*/
  return out;
}


void TKinFitterDriver::SetConstraint(){
  //TODO: will update to be able to set top-mass
  // reset constrain
  constrain_hadronic_top_M->Clear();
  constrain_hadronic_top_M->addParticles1(fit_hadronic_top_b_jet, fit_hadronic_w_ch_jet1, fit_hadronic_w_ch_jet2);
  //constrain_hadronic_top_MGaus->Clear();
  //constrain_hadronic_top_MGaus->addParticles1(fit_hadronic_top_b_jet, fit_hadronic_w_ch_jet1, fit_hadronic_w_ch_jet2);
  constrain_leptonic_top_M->Clear();
  constrain_leptonic_top_M->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino_pxpy, fit_neutrino_pz);
  //constrain_leptonic_top_MGaus->Clear();
  //constrain_leptonic_top_MGaus->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino_pxpy, fit_neutrino_pz);
  constrain_leptonic_W_M->Clear();
  constrain_leptonic_W_M->addParticles1(fit_lepton, fit_neutrino_pxpy, fit_neutrino_pz);
  //constrain_leptonic_W_MGaus->Clear();
  //constrain_leptonic_W_MGaus->addParticles1(fit_lepton, fit_neutrino_pxpy, fit_neutrino_pz);
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
  fitter->addMeasParticle( fit_neutrino_pxpy );
  fitter->addUnmeasParticle( fit_neutrino_pz );
  //fitter->addUnmeasParticle( fit_lepton );
  //fitter->addUnmeasParticle( fit_neutrino_pxpy );
  //add Constraint
  fitter->addConstraint( constrain_hadronic_top_M );
  //fitter->addConstraint( constrain_hadronic_top_MGaus );
  fitter->addConstraint( constrain_leptonic_top_M );
  //fitter->addConstraint( constrain_leptonic_top_MGaus );
  fitter->addConstraint( constrain_leptonic_W_M );
  //fitter->addConstraint( constrain_leptonic_W_MGaus );
  //Set convergence criteria
  fitter->setMaxNbIter( 50 ); //50 is default
  fitter->setMaxDeltaS( 1e-2 );
  fitter->setMaxF( 1e-1 ); //1e-1 is default
  fitter->setVerbosity(1);
  //cout << "TKinFitterDriver::SetFitter : " << endl;
}


void TKinFitterDriver::Fit(){
  this->SetConstraint();
  this->SetFitter();
  this->SaveResults();
}


void TKinFitterDriver::SaveResults(){

  fit_result.status=-1; // -1 means fit not performed
  fit_result.status = fitter->fit();
  // save kinematic variable before fit
  TLorentzVector hadronic_top = hadronic_top_b_jet + hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  TLorentzVector leptonic_W = lepton + neutrino_pxpy + neutrino_pz;
  TLorentzVector leptonic_top = leptonic_top_b_jet + leptonic_W;
  fit_result.hadronic_top_M = hadronic_top.M();
  fit_result.leptonic_top_M = leptonic_top.M();
  fit_result.leptonic_W_M = leptonic_W.M();
  fit_result.IsRealNeuPz = IsRealNeuPz;

  fit_result.hadronic_top_b_pt = hadronic_top_b_jet.Pt();
  fit_result.leptonic_top_b_pt = leptonic_top_b_jet.Pt();
  fit_result.w_ch_up_type_pt = hadronic_w_ch_jet1.Pt();
  fit_result.w_ch_down_type_pt = hadronic_w_ch_jet2.Pt();

  fit_result.chi2 = 9999;
  //if(fit_result.status!=-10){ // -10 means singular matrix
    // save S and F
    fit_result.currS = fitter->getS();
    fit_result.deltaS = fitter->getDeltaS();
    fit_result.hadronic_top_mass_F = constrain_hadronic_top_M->getCurrentValue();
    //fit_result.hadronic_top_mass_F = constrain_hadronic_top_MGaus->getCurrentValue();
    fit_result.leptonic_top_mass_F = constrain_leptonic_top_M->getCurrentValue();
    //fit_result.leptonic_top_mass_F = constrain_leptonic_top_MGaus->getCurrentValue();
    fit_result.leptonic_w_mass_F = constrain_leptonic_W_M->getCurrentValue();
    //fit_result.leptonic_w_mass_F = constrain_leptonic_W_MGaus->getCurrentValue();
    // re-calculate chi2,
    //chi2 term comes from constraint is not accurate
    fit_result.chi2 = this->CalcChi2();

    // calc. dijet mass
    const TLorentzVector *fitted_jet1 = fit_hadronic_w_ch_jet1->getCurr4Vec(); // get address of fitted object
    const TLorentzVector *fitted_jet2 = fit_hadronic_w_ch_jet2->getCurr4Vec(); // get address of fitted object
    const TLorentzVector fitted_dijet = (*fitted_jet1) + (*fitted_jet2);
    fit_result.fitted_dijet_M = fitted_dijet.M(); // save dijet mass
    TLorentzVector initial_dijet = hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
    fit_result.initial_dijet_M = initial_dijet.M(); // save dijet mass
    TLorentzVector corrected_dijet = corr_hadronic_w_ch_jet1 + corr_hadronic_w_ch_jet2;
    fit_result.corrected_dijet_M = corrected_dijet.M(); // save dijet mass
  //}
  //cout << "TKinFitterDriver::Fit : " << endl;

}


double TKinFitterDriver::CalcChi2(){
  double chi2=0;
  // jets
  chi2 += this->CalcEachChi2(fit_hadronic_top_b_jet);
  chi2 += this->CalcEachChi2(fit_leptonic_top_b_jet);
  chi2 += this->CalcEachChi2(fit_hadronic_w_ch_jet1);
  chi2 += this->CalcEachChi2(fit_hadronic_w_ch_jet2);
  //lepton
  chi2 += this->CalcEachChi2(fit_lepton);
  //extra pt
  chi2 += this->CalcEachChi2(fit_neutrino_pxpy);
  // mass constraints
  chi2 += this->CalcEachChi2(constrain_leptonic_W_M, 2.085);
  //chi2 += this->CalcEachChi2(constrain_leptonic_W_MGaus);
  //chi2 += this->CalcEachChi2(constrain_hadronic_top_MGaus);
  chi2 += this->CalcEachChi2(constrain_hadronic_top_M, 1.5);
  //chi2 += this->CalcEachChi2(constrain_leptonic_top_MGaus);
  chi2 += this->CalcEachChi2(constrain_leptonic_top_M, 1.5);
  return chi2;
}


double TKinFitterDriver::CalcEachChi2(TAbsFitParticle* ptr){

  const TMatrixD* iniPar = ptr->getParIni();
  const TMatrixD* currPar = ptr->getParCurr();
  const TMatrixD* covMatrix = ptr->getCovMatrix();
  double S = 0.;

  for(int i(0); i<iniPar->GetNcols(); i++){
    double deltaY = (*iniPar)(i,i) - (*currPar)(i,i);
    S += deltaY*deltaY/(*covMatrix)(i,i);
  }
  return S;
}


double TKinFitterDriver::CalcEachChi2(TFitConstraintM* ptr, double width){
  double S = 0.;
  double deltaY = ptr->getCurrentValue();
  S = (deltaY*deltaY)/(width*width);
  return S;
}


double TKinFitterDriver::CalcEachChi2(TFitConstraintMGaus* ptr){
  return ptr->getChi2();
}


void TKinFitterDriver::FindBestChi2Fit(bool UseLeading4Jets, bool IsHighMassFitter){
  fit_result_vector.clear();
  fit_result_vector.shrink_to_fit();
  // status -1 : fit not performed
  fit_result.status=-1;
  do{
    if(this->Check_BJet_Assignment() == false) continue;
    this->SetCurrentPermutationJets();
    if(this->ML_Cut() == false) continue;
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
  if(IsHighMassFitter){
    std::sort(fit_result_vector.begin(), fit_result_vector.end(), HighMassFitter);
  }
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
  return out==9999 ? -1. : out;
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


double TKinFitterDriver::GetBestHadronicTopMass(){
  double out=-100;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).hadronic_top_M;
  }
  return out;
}


double TKinFitterDriver::GetBestLeptonicTopMass(){
  double out=-100;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).leptonic_top_M;
  }
  return out;
}


double TKinFitterDriver::GetBestLeptonicWMass(){
  double out=-100;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).leptonic_W_M;
  }
  return out;
}


bool TKinFitterDriver::GetBestIsRealNeuPz(){
  bool out=false;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).IsRealNeuPz;
  }
  return out;
}


double TKinFitterDriver::GetBestHadronicTopMassF(){
  double out=-100;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).hadronic_top_mass_F;
  }
  return out;
}


double TKinFitterDriver::GetBestLeptonicTopMassF(){
  double out=-100;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).leptonic_top_mass_F;
  }
  return out;
}


double TKinFitterDriver::GetBestLeptonicWMassF(){
  double out=-100;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).leptonic_w_mass_F;
  }
  return out;
}


double TKinFitterDriver::GetBestDeltaS(){
  double out=-100;
  if(fit_result_vector.size()>0){
    out =fit_result_vector.at(0).deltaS;
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


void TKinFitterDriver::SetJetError(TMatrixD *matrix,  double Pt, double Eta, double Phi, TString flavour_key){
  (*matrix)(0,0) = TMath::Power(Pt*this->JetErrorPt(Pt, Eta, flavour_key), 2);
  //(*matrix)(1,1) = TMath::Power(Eta*this->JetErrorEta(Et, Eta, flavour_key), 2);
  //(*matrix)(2,2) = TMath::Power(Phi*this->JetErrorPhi(Et, Eta, flavour_key), 2);
}


void TKinFitterDriver::SetUnclError(TMatrixD *matrix, TLorentzVector &met){
  TLorentzVector extra_pt(0.,0.,0.,0.);
  extra_pt -= met;
  extra_pt -= lepton;
  extra_pt -= hadronic_top_b_jet;
  extra_pt -= leptonic_top_b_jet;
  extra_pt -= hadronic_w_ch_jet1;
  extra_pt -= hadronic_w_ch_jet2;

  double Pt = extra_pt.Pt();
  double Eta = 0.;
  double error_Pt = Pt*this->JetErrorPt(Pt, Eta, "udscb");
  //(*matrix)(0,0) = error_Pt*error_Pt;
  //(*matrix)(1,1) = error_Pt*error_Pt;
  (*matrix)(0,0) = error_Pt*error_Pt;
  (*matrix)(1,1) = error_Pt*error_Pt;
}


double TKinFitterDriver::JetErrorPt(double Pt, double Eta, TString flavour_key){
  return ts_correction->GetFittedError("Pt", flavour_key, Pt, Eta);
}


double TKinFitterDriver::JetErrorEta(double Pt, double Eta, TString flavour_key){
  return ts_correction->GetFittedError("Eta", flavour_key, Pt, Eta);
}


double TKinFitterDriver::JetErrorPhi(double Pt, double Eta, TString flavour_key){
  return ts_correction->GetFittedError("Phi", flavour_key, Pt, Eta);
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
    neutrino_pz_sol[0] = (-b + TMath::Sqrt(determinant))/(2*a);                      
    neutrino_pz_sol[1] = (-b - TMath::Sqrt(determinant))/(2*a);                      
    IsRealNeuPz = true;
  }
  else{
    neutrino_pz_sol[0] = -b/(2*a);
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


bool TKinFitterDriver::Chi2Comparing(const TKinFitterDriver::ResultContatiner& rc1, const TKinFitterDriver::ResultContatiner& rc2){
  return (rc1.chi2 < rc2.chi2);
}


bool TKinFitterDriver::HighMassFitter(const TKinFitterDriver::ResultContatiner& rc1, const TKinFitterDriver::ResultContatiner& rc2){
  bool out; 
  out=(rc1.chi2 < rc2.chi2) ||
      (
       (rc1.chi2 == rc2.chi2) &&
       (rc1.hadronic_top_b_pt < rc1.w_ch_down_type_pt) &&
       (rc2.hadronic_top_b_pt >= rc2.w_ch_down_type_pt)
      );
  return out;
}
