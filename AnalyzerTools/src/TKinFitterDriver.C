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
  //error_neutrino_pt.ResizeTo(1,1);
  error_neutrino_etphi.ResizeTo(2,2);
  //error_neutrino_pxpy.ResizeTo(2,2);
  //error_neutrino_pt.ResizeTo(1,1);
  //error_neutrino_pz.ResizeTo(1,1);

  error_hadronic_top_b_jet.Zero(); 
  error_leptonic_top_b_jet.Zero();
  error_hadronic_w_ch_jet1.Zero();
  error_hadronic_w_ch_jet2.Zero();
  error_lepton.Zero();
  //error_neutrino_pt.Zero();
  error_neutrino_etphi.Zero();
  //error_neutrino_pxpy.Zero();
  //error_neutrino_pz.Zero();

  ts_correction = new TSCorrection(DataYear);
  ts_correction->ReadFittedError("fit_error_pythia.txt");
  ts_correction->ReadFittedMean("fit_mean_pythia.txt");

  fit_hadronic_top_b_jet = new TFitParticlePt();
  fit_leptonic_top_b_jet = new TFitParticlePt();
  fit_hadronic_w_ch_jet1 = new TFitParticlePt();
  fit_hadronic_w_ch_jet2 = new TFitParticlePt();
  fit_extra_jet = new TFitParticlePt();
  fit_lepton = new TFitParticlePt();
  //fit_neutrino_pt =  new TFitParticlePt();
  fit_neutrino_etphi =  new TFitParticleEtPhi();
  //fit_neutrino_pxpy =  new TFitParticlePxPy();
  //fit_neutrino_pz =  new TFitParticlePz();

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
  tmva_reader->AddVariable((TString)"dijet_deltaR",&dijet_deltaR);
  tmva_reader->AddVariable((TString)"had_w_ch_deltaR",&had_w_ch_deltaR);

  tmva_reader->AddVariable((TString)"had_top_b_jet_csv",&had_top_b_jet_csv);
  tmva_reader->AddVariable((TString)"lep_top_b_jet_csv",&lep_top_b_jet_csv);
  tmva_reader->AddVariable((TString)"up_type_jet_csv",  &up_type_jet_csv);
  tmva_reader->AddVariable((TString)"down_type_jet_csv",&down_type_jet_csv);

  tmva_reader->AddVariable((TString)"hadronic_top_mass",&hadronic_top_mass);
  tmva_reader->AddVariable((TString)"hadronic_top_mass_flipped1",&hadronic_top_mass_flipped1);
  tmva_reader->AddVariable((TString)"hadronic_top_mass_flipped2",&hadronic_top_mass_flipped2);
  tmva_reader->AddVariable((TString)"tt_deltaPhi",&tt_deltaPhi);
  tmva_reader->AddVariable((TString)"tt_deltaPhi_flipped1",&tt_deltaPhi_flipped1);
  tmva_reader->AddVariable((TString)"tt_deltaPhi_flipped2",&tt_deltaPhi_flipped2);
  tmva_reader->AddVariable((TString)"Mbl",&Mbl);
  tmva_reader->AddVariable((TString)"Mbl_flipped1",&Mbl_flipped1);
  tmva_reader->AddVariable((TString)"Mbl_flipped2",&Mbl_flipped2);

  TString base_path= getenv("DATA_DIR"); 
  base_path += "/" + TString::Itoa(DataYear,10) + "/TMVAClassification/";
  std::map<TString, TString> methods;
  //TString MCSample_ = MCSample.Contains("CHToCB")?MCSample:"TTLJ_powheg";
  for(TString MCSample_ : {"TTLJ_powheg", "CHToCB_M090to110", "CHToCB_M120to150"}){
    methods[Form("BDT_%s_4j5j_2b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"4j5j","2b");
    methods[Form("BDT_%s_6j_2b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"6j","2b");
    methods[Form("BDT_%s_4j5j_3b",MCSample_.Data())] = Form("%s/weights_%s_%s_%s/TMVAClassification_BDT.weights.xml",base_path.Data(),MCSample_.Data(),"4j5j","3b");
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
  //delete fit_neutrino_pxpy;
  //delete fit_neutrino_pt;
  delete fit_neutrino_etphi;
  //delete fit_neutrino_pz;

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
    jet_vector.push_back(jet_vector_.at(i));
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


void TKinFitterDriver::SetMETShift(double met_shift_, double met_phi_shift_){
  MET_shift = met_shift_;
  MET_phi_shift = met_phi_shift_;
}


void TKinFitterDriver::SetNeutrino(TLorentzVector met_, double met_shift_, double met_phi_shift_, int i){

  double Pz = neutrino_pz_sol[i];

  neutrino_etphi.SetPxPyPzE(met_.Pz(),met_.Py(), Pz, TMath::Sqrt(met_.E()*met_.E()+Pz*Pz));
  error_neutrino_etphi(0,0) = TMath::Power(met_.E()-met_shift_, 2);
  error_neutrino_etphi(1,1) = TMath::Power(met_.Phi()-met_phi_shift_, 2);
  fit_neutrino_etphi->~TFitParticleEtPhi();
  new(fit_neutrino_etphi) TFitParticleEtPhi("neutrino_etphi",
		                            "neutrino_etphi",
				            &neutrino_etphi,
				            &error_neutrino_etphi
		                           );

  //neutrino_pxpy.SetPxPyPzE(met_.Px(),met_.Py(), 0., met_.E());
  //neutrino_pz.SetPxPyPzE(0., 0., Pz, fabs(Pz));

  //double error_neutrino_px=0., error_neutrino_py=0.;
  //for(auto &x : jet_vector){
  //  double Pt = x.Pt();
  //  double Px = x.Px();
  //  double Py = x.Py();
  //  double Eta = x.Eta();
  //  double error_ts_corr = this->JetErrorPt(Pt, Eta, "udscb");
  //  error_neutrino_px+=(error_ts_corr*Px)*(error_ts_corr*Px);
  //  error_neutrino_py+=(error_ts_corr*Py)*(error_ts_corr*Py);
  //}
  //error_neutrino_pxpy(0,0) = error_neutrino_px;
  //error_neutrino_pxpy(1,1) = error_neutrino_py;
  //this->SetUnclError(&error_neutrino_pxpy, met_);
  //fit_neutrino_pxpy->~TFitParticlePxPy();
  //new(fit_neutrino_pxpy) TFitParticlePxPy("neutrino_pxpy",
  //                                        "neutrino_pxpy",
  //                                        &neutrino_pxpy,
  //                                        &error_neutrino_pxpy
  //                                       );
  //
  //fit_neutrino_pz->~TFitParticlePz();
  //double MET = METv.Pt();
  //double lep_pt = lepton.Pt();
  //double cos = TMath::Cos(METv.Phi()-lepton.Phi());
  //double abs_sin = fabs(TMath::Sin(METv.Phi()-lepton.Phi()));
  //error_neutrino_pz(0,0) = TMath::Power(Pz*0.2, 2);

  //new(fit_neutrino_pz) TFitParticlePz("neutrino_pz",
  //      	                      "neutrino_pz",
  //      			      &neutrino_pz,
  //      			      &error_neutrino_pz
  //      			      );
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
  this->SetHadronicTopBJets( (TLorentzVector)jet_vector.at(k) );
  this->SetLeptonicTopBJets( (TLorentzVector)jet_vector.at(l) );
  this->SetWCHUpTypeJets( (TLorentzVector)jet_vector.at(m) );
  this->SetWCHDownTypeJets( (TLorentzVector)jet_vector.at(n) );
  
  //csv variables
  had_top_b_jet_csv = jet_vector.at(k).GetTaggerResult(Jet::DeepCSV);
  lep_top_b_jet_csv = jet_vector.at(l).GetTaggerResult(Jet::DeepCSV);
  up_type_jet_csv   = jet_vector.at(m).GetTaggerResult(Jet::DeepCSV);
  down_type_jet_csv = jet_vector.at(n).GetTaggerResult(Jet::DeepCSV); 


}


bool TKinFitterDriver::Check_BJet_Assignment(){

  int nbtags_in_four_jets=0;
  bool found_up_type=false, found_down_type=false;
  double up_type_csv = -999, down_type_csv = -999;
  for(UInt_t i=0; i<permutation_vector.size(); i++){
    JET_ASSIGNMENT jet_assignment_idx = permutation_vector.at(i);

    if( jet_assignment_idx == W_CH_UP_TYPE ){
      found_up_type = true;
      up_type_csv   = jet_vector.at(jet_assignment_idx).GetTaggerResult(Jet::DeepCSV);
    }
    else if( jet_assignment_idx == W_CH_DOWN_TYPE ){
      found_down_type = true;
      down_type_csv   = jet_vector.at(jet_assignment_idx).GetTaggerResult(Jet::DeepCSV);
    }

    if(found_up_type==true && found_down_type==true){
      if(up_type_csv > down_type_csv){
        break;
      }
    }

    bool IsBTagged = btag_vector.at(i);
    if(nbtags>=2){
      if( jet_assignment_idx == HADRONIC_TOP_B && IsBTagged ) nbtags_in_four_jets+=1;
      else if( jet_assignment_idx == LEPTONIC_TOP_B && IsBTagged ) nbtags_in_four_jets+=1;
    }
    //if(nbtags>=3){
    //  if( jet_assignment_idx == W_CH_DOWN_TYPE && IsBTagged ){
	//if(i>=4){
          // b tagged jet should be inside leading 4 jets
          //break;
        //}
        //else{
    //	  nbtags_in_four_jets+=1;
	//}
      //}
    //}
  }

  bool true_bjet_assignment=false;
  if(up_type_csv > down_type_csv) true_bjet_assignment=false;
  else if(nbtags==2 && nbtags_in_four_jets==2) true_bjet_assignment=true;
  //if(nbtags==2 && nbtags_in_four_jets==2) true_bjet_assignment=true;
  else if(nbtags>=3 && nbtags_in_four_jets>=2) true_bjet_assignment=true;

  //cout << "TKinFitterDriver::Check_BJet_Assignment : " << endl; 
  return true_bjet_assignment;
}


bool TKinFitterDriver::Kinematic_Cut(){
  TLorentzVector hadronic_top = hadronic_top_b_jet + hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  TLorentzVector hadronic_top_flipped = leptonic_top_b_jet + hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  TLorentzVector hadronic_top_flipped2 = hadronic_top_b_jet + hadronic_w_ch_jet1 + leptonic_top_b_jet;
  TLorentzVector bl = leptonic_top_b_jet + lepton;
  //TLorentzVector cb = hadronic_w_ch_jet1 + hadronic_top_b_jet;
  TLorentzVector bb = hadronic_w_ch_jet2 + hadronic_top_b_jet;
  double hadronic_top_mass = hadronic_top.M();
  double hadronic_top_mass_flipped = hadronic_top_flipped.M();
  double Mbl = bl.M();
  //double Mcb = cb.M();
  double Mbb = bb.M();
  double deltaPhilhb = fabs(lepton.Phi() - hadronic_top_b_jet.Phi());
  //double deltaEtabb1 = fabs(hadronic_top_b_jet.Eta()-leptonic_top_b_jet.Eta());
  //double deltaEtabb2 = fabs(hadronic_w_ch_jet2.Eta()-leptonic_top_b_jet.Eta());
  //double dijet_deltaR = hadronic_w_ch_jet1.DeltaR(hadronic_w_ch_jet2);
  //return (hadronic_top_mass > 100 && hadronic_top_mass < 240) && ( Mbl < 152.6 ) && ( Mcb < 152.6) && (Mbb < 152.6)  && ( dijet_deltaR < 2.5 );
  return (hadronic_top_mass > 100 && hadronic_top_mass < 240) && ( Mbl < 152.6 ) && ( Mbb < 152.6 ) && deltaPhilhb>2.;
  //return (hadronic_top_mass > 100 && hadronic_top_mass < 240) && ( Mbl < 152.6 );
}

bool TKinFitterDriver::ThirdBTaggingCut(){
  bool out = false;
  if(nbtags<3){
    out = true;
  }
  else{
    //auto it_up = std::find(permutation_vector.begin(),permutation_vector.end(),W_CH_UP_TYPE);
    auto it_down = std::find(permutation_vector.begin(),permutation_vector.end(),W_CH_DOWN_TYPE);
    //int idx_up = std::distance(permutation_vector.begin(),it_up);
    int idx_down = std::distance(permutation_vector.begin(),it_down);
    //bool IsBTagged_up = btag_vector.at(idx_up);
    bool IsBTagged_down = btag_vector.at(idx_down);
    if(
        IsBTagged_down == true
      ){
        out = true;
      }
  }
  return out;
}
bool TKinFitterDriver::GoodnessCut(){
  
  bool out=true;
  auto pull1 = fit_hadronic_top_b_jet->getPull();
  auto pull2 = fit_leptonic_top_b_jet->getPull();
  auto pull3 = fit_hadronic_w_ch_jet1->getPull();
  auto pull4 = fit_hadronic_w_ch_jet2->getPull();
  for(auto &x : {pull1,pull2,pull3,pull4}){
    if(fabs((*x)(0,0))>3){
      out = false;
      break;
    }
  }
  return out;
}

bool TKinFitterDriver::AngularCorr(){

  bool out=true;
  TLorentzVector had_w_ch = hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  TLorentzVector h_top = hadronic_top_b_jet + had_w_ch;
  //
  TLorentzVector tmp_h_top;
  tmp_h_top.SetPtEtaPhiM(h_top.Pt(), h_top.Eta(), h_top.Phi(), h_top.M());
  double h_top_gamma = tmp_h_top.Gamma();
  double h_top_beta = tmp_h_top.Beta();
  double E_star = (172.5*172.5-80.4*80.4)/(2*172.5);
  double theta_star = h_top.Theta() - (hadronic_top_b_jet-h_top).Theta();
  double E = E_star*h_top_gamma*(1+h_top_beta*TMath::Cos(theta_star));
  //TLorentzVector cb1 = hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  //TLorentzVector cb2 = hadronic_w_ch_jet1 + hadronic_top_b_jet;
  TLorentzVector bb = hadronic_w_ch_jet2 + hadronic_top_b_jet;
  //double Mcb1 = cb1.M();
  //double Mcb2 = cb2.M();
  double Mbb = bb.M();
  //double dijet_deltaR = had_w_ch.DeltaR(hadronic_top_b_jet);
  if( 
      //E < hadronic_top_b_jet.Pt() && E > hadronic_w_ch_jet2.Pt() ||
      Mbb > 152.6
      //fabs(had_w_ch.Eta()) < fabs(hadronic_top_b_jet.Eta())
    ){
    out=false;
  }
  //debug
  //cout << "nbtags:  " << nbtags << "\t\t " << deltaR1 << "\t\t" << deltaR2 << "\t\t" << fit_result.fitted_dijet_M << endl;
  return out;
}

void TKinFitterDriver::updatesMLVariables(){

  TLorentzVector had_w_ch = hadronic_w_ch_jet1 + hadronic_w_ch_jet2;
  TLorentzVector h_top = hadronic_top_b_jet + had_w_ch;
  TLorentzVector h_top_flipped1 = leptonic_top_b_jet + had_w_ch;
  TLorentzVector h_top_flipped2 = hadronic_w_ch_jet2 + had_w_ch;
  TLorentzVector l_W = METv + lepton;
  TLorentzVector bl = lepton + leptonic_top_b_jet;
  TLorentzVector bl_flipped1 = lepton + hadronic_top_b_jet;
  TLorentzVector bl_flipped2 = lepton + hadronic_w_ch_jet2;
  TLorentzVector l_top = l_W + leptonic_top_b_jet;
  TLorentzVector l_top_flipped1 = l_W + hadronic_top_b_jet;
  TLorentzVector l_top_flipped2 = l_W + hadronic_w_ch_jet2;

  dijet_deltaR = hadronic_w_ch_jet1.DeltaR(hadronic_w_ch_jet2);
  had_w_ch_deltaR = had_w_ch.DeltaR(hadronic_top_b_jet);

  //csv variables updated in SetCurrentPermutationJets();

  hadronic_top_mass = h_top.M();
  hadronic_top_mass_flipped1 = h_top_flipped1.M();
  hadronic_top_mass_flipped2 = h_top_flipped2.M();
  Mbl = bl.M();
  Mbl_flipped1 = bl_flipped1.M();
  Mbl_flipped2 = bl_flipped2.M();
  tt_deltaPhi = fabs(h_top.Phi() - l_top.Phi());
  tt_deltaPhi_flipped1 = fabs(h_top_flipped1.Phi() - l_top_flipped1.Phi());
  tt_deltaPhi_flipped2 = fabs(h_top_flipped2.Phi() - l_top_flipped2.Phi());

}


bool TKinFitterDriver::ML_Cut(TString mass_){
  if(useMLCut==false){
    return true;
  }
  this->updatesMLVariables();
  // XXX: let's hard code this time
  TString method ="BDT_%s";
  method += njets==4?
              "_4j5j":njets==5?
                "_4j5j":njets>=6?
	          "_6j":"_NULL";
  method += nbtags==2?
	      "_2b":nbtags>=3?
	        "_3b":"_NULL";
  double MLoutput1 = tmva_reader->EvaluateMVA(Form(method.Data(),"TTLJ_powheg"));
  double MLoutput2 = tmva_reader->EvaluateMVA(Form(method.Data(),mass_.Data()));
  //cout << MLoutput << endl;
  double cut1 = 0., cut2 = 0.;
  cut1 = this->GetMLCut("TTLJ_powheg");
  cut2 = this->GetMLCut(mass_);
  if( (MLoutput1>cut1) ||
      (MLoutput2>cut2)
    ){
    return true;
  }
  else{
    return false;
  }
}

double TKinFitterDriver::GetMLCut(TString sample){
  double out=-999;
  if(sample.Contains("TTLJ_powheg")){
    if(njets==4 || njets==5 ){
      if(nbtags==2){
        out=0.5068280354158298;
      }
      else if(nbtags>=3){
        out=0.2376547026255436;
      }
    }
    else if(njets>=6){
      if(nbtags==2){
        out=0.47901386820577924;
      }
      else if(nbtags>=3){
        out=0.306995535434061;
      }
    }
  }
  else if(sample.Contains("CHToCB_M090to110")){
    if(njets==4 || njets==5){
      if(nbtags==2){
        out=-0.4239895236926861;
      }
      else if(nbtags>=3){
        out=-0.033261172868134445;
      }
    }
    else if(njets>=6){
      if(nbtags==2){
        out=-0.38815070034907145;
      }
      else if(nbtags>=3){
        out=0.01624176652433411;
      }
    }
  }
  else if(sample.Contains("CHToCB_M120to150")){
    if(njets==4 || njets==5){
      if(nbtags==2){
        out=-0.8674999772068501;
      }
      else if(nbtags>=3){
        out=-0.5315194527877283;
      }
    }
    else if(njets>=6){
      if(nbtags==2){
        out=-0.7287129222635327;
      }
      else if(nbtags>=3){
        out=-0.39152847563149457;
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
  //constrain_leptonic_top_M->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino_pxpy, fit_neutrino_pz);
  //constrain_leptonic_top_M->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino_pt);
  constrain_leptonic_top_M->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino_etphi);
  //constrain_leptonic_top_MGaus->Clear();
  //constrain_leptonic_top_MGaus->addParticles1(fit_leptonic_top_b_jet, fit_lepton, fit_neutrino_pxpy, fit_neutrino_pz);
  constrain_leptonic_W_M->Clear();
  //constrain_leptonic_W_M->addParticles1(fit_lepton, fit_neutrino_pt);
  constrain_leptonic_W_M->addParticles1(fit_lepton, fit_neutrino_etphi);
  //constrain_leptonic_W_M->addParticles1(fit_lepton, fit_neutrino_pxpy, fit_neutrino_pz);
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
  //fitter->addMeasParticle( fit_neutrino_pt );
  fitter->addMeasParticle( fit_neutrino_etphi );
  //fitter->addMeasParticle( fit_neutrino_pxpy );
  //fitter->addMeasParticle( fit_neutrino_pz );
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
  //TLorentzVector leptonic_W = lepton + neutrino_pxpy + neutrino_pz;
  TLorentzVector leptonic_W = lepton + neutrino_etphi;
  TLorentzVector leptonic_top = leptonic_top_b_jet + leptonic_W;
  fit_result.hadronic_top_M = hadronic_top.M();
  fit_result.hadronic_top_pt = hadronic_top.Pt();
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

    //
    fit_result.fitted_hadronic_top_b_jet = fit_hadronic_top_b_jet->getCurr4Vec();
    fit_result.fitted_leptonic_top_b_jet = fit_leptonic_top_b_jet->getCurr4Vec();
    fit_result.fitted_hadronic_w_ch_jet1 = fit_hadronic_w_ch_jet1->getCurr4Vec();
    fit_result.fitted_hadronic_w_ch_jet2 = fit_hadronic_w_ch_jet2->getCurr4Vec();

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

    fit_result.passMLcut["CHToCB_M090to110"] = this->ML_Cut("CHToCB_M090to110");
    fit_result.passMLcut["CHToCB_M120to150"] = this->ML_Cut("CHToCB_M120to150");
    fit_result.passThirdBTaggingCut = this->ThirdBTaggingCut();
    fit_result.passGoodnessCut = this->GoodnessCut();
    fit_result.passAngularCorr = this->AngularCorr();

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
  //chi2 += this->CalcEachChi2(fit_neutrino_pt);
  chi2 += this->CalcEachChi2(fit_neutrino_etphi);
  //chi2 += this->CalcEachChi2(fit_neutrino_pz);
  //chi2 += this->CalcEachChi2(fit_neutrino_pxpy);
  // mass constraints
  chi2 += this->CalcEachChi2(constrain_leptonic_W_M, 2.141);
  //chi2 += this->CalcEachChi2(constrain_leptonic_W_MGaus);
  //chi2 += this->CalcEachChi2(constrain_hadronic_top_MGaus);
  chi2 += this->CalcEachChi2(constrain_hadronic_top_M, 1.31);
  //chi2 += this->CalcEachChi2(constrain_leptonic_top_MGaus);
  chi2 += this->CalcEachChi2(constrain_leptonic_top_M, 1.31);
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


void TKinFitterDriver::FindBestChi2Fit(bool UseLeading5Jets, bool IsHighMassFitter){
  fit_result_vector.clear();
  fit_result_vector.shrink_to_fit();
  // status -1 : fit not performed
  fit_result.status=-1;
  do{
    if(this->Check_BJet_Assignment() == false) continue;
    this->SetCurrentPermutationJets();
    //XXX will be removed, results from ML_Cut() should be stored
    //if(this->ML_Cut() == false) continue;
    if(this->Kinematic_Cut() == false) continue;
    //if(this->ThirdBTaggingCut() == false) continue;
      this->Sol_Neutrino_Pz();
      for(int i(0); i<2; i++){
	//if(!IsRealNeuPz && i==1) break;
	if(IsRealNeuPz){
	  this->SetNeutrino(METv, MET_shift, MET_phi_shift, i);
	}
	else if(!IsRealNeuPz && i==0){
	  this->SetNeutrino(METv, MET_shift, MET_phi_shift, i); // not use recalc MET
	  //this->SetNeutrino(recal_METv, i);
	}
        this->Fit();
	fit_result_vector.push_back(fit_result);
      }
    }while(this->NextPermutation(UseLeading5Jets));
  std::sort(fit_result_vector.begin(), fit_result_vector.end(), Chi2Comparing);
  std::sort(fit_result_vector.begin(), fit_result_vector.end(), HadTopPtComparing);
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


double TKinFitterDriver::GetBestChi2Variables(TString varName, TString mass_, bool highMassFitter){

  std::vector<ResultContainer*> tmp_fit_result_vector;
  //
  for(auto &x : fit_result_vector){
    if(x.passThirdBTaggingCut==true &&
       x.passAngularCorr==true &&
       x.passMLcut[mass_]==true
      ){
      tmp_fit_result_vector.push_back(&x);
    }
  }
  
  double out=-1;
  int out_idx=0;
  bool zeroVectorSize=false;
  if(tmp_fit_result_vector.size()==0){
    zeroVectorSize=true;
  }
  else if(tmp_fit_result_vector.size()==1){
    //pass out_idx==0
  }
  else if(tmp_fit_result_vector.size()>1){
    if(nbtags>=3){
      double chi2_0 = tmp_fit_result_vector[0]->chi2;
      double chi2_1 = tmp_fit_result_vector[1]->chi2;
      double w_ch_b_pt_0 = tmp_fit_result_vector[0]->w_ch_down_type_pt;
      double w_ch_b_pt_1 = tmp_fit_result_vector[1]->w_ch_down_type_pt;
      double top_b_pt_0 = tmp_fit_result_vector[0]->hadronic_top_b_pt;
      double top_b_pt_1 = tmp_fit_result_vector[1]->hadronic_top_b_pt; 

      if(highMassFitter){
       if(chi2_0==chi2_1  && w_ch_b_pt_0 < top_b_pt_0 && w_ch_b_pt_1 >= top_b_pt_1 ){
       //if(chi2_0==chi2_1  && Pt_0 >= E_0 && Pt_1 < E_1 ){
          out_idx = 1;
        }
        else{
          //pass out_idx==0
        }
      }
      else{
        if(chi2_0==chi2_1  && w_ch_b_pt_0 >= top_b_pt_0 && w_ch_b_pt_1 < top_b_pt_1 ){
        //if(chi2_0==chi2_1  && Pt_0 < E_0 && Pt_1 >= E_1 ){
          out_idx = 1;
        }
        else{
          //pass out_idx==0
        }
      }
    }
    else{
      //pass out_idx==0
    }
  }

  if(zeroVectorSize==false){
    if(varName=="status"){
      out = tmp_fit_result_vector.at(out_idx)->status;
    }
    else if(varName=="chi2"){
      out = tmp_fit_result_vector.at(out_idx)->chi2;
    }
    else if(varName=="fitted_dijet_M"){
      out = tmp_fit_result_vector.at(out_idx)->fitted_dijet_M;
    }
    else if(varName=="initial_dijet_M"){
      out = tmp_fit_result_vector.at(out_idx)->initial_dijet_M;
    }
    else if(varName=="corrected_dijet_M"){
      out = tmp_fit_result_vector.at(out_idx)->corrected_dijet_M;
    }
    //else if(varName==""){
    //  out = tmp_fit_result_vector.at(out_idx)->;
    //}
    //else if(varName==""){
    //  out = tmp_fit_result_vector.at(out_idx)->;
    //}
  }
  else{
    //pass out==-1
  }
  return out;

}



int TKinFitterDriver::GetBestStatus(TString mass_){
  return (int)GetBestChi2Variables("status",mass_,mass_=="CHToCB_M120to150"?true:false);
}


double TKinFitterDriver::GetBestChi2(TString mass_){
  return GetBestChi2Variables("chi2",mass_,mass_=="CHToCB_M120to150"?true:false);
}


double TKinFitterDriver::GetBestFittedDijetMass(TString mass_){
  return GetBestChi2Variables("fitted_dijet_M",mass_,mass_=="CHToCB_M120to150"?true:false);
}


double TKinFitterDriver::GetBestInitialDijetMass(TString mass_){
  return GetBestChi2Variables("initial_dijet_M",mass_,mass_=="CHToCB_M120to150"?true:false);
}


double TKinFitterDriver::GetBestCorrectedDijetMass(TString mass_){
  return GetBestChi2Variables("corrected_dijet_M",mass_,mass_=="CHToCB_M120to150"?true:false);
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


std::vector<TKinFitterDriver::ResultContainer> TKinFitterDriver::GetResults(){
  return fit_result_vector;
}


bool TKinFitterDriver::NextPermutation(bool UseLeading5Jets){

  std::vector<TKinFitterDriver::JET_ASSIGNMENT>::iterator begin = permutation_vector.begin();
  std::vector<TKinFitterDriver::JET_ASSIGNMENT>::iterator end;
  if(UseLeading5Jets && njets>5){
    end = begin+5;
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


bool TKinFitterDriver::Chi2Comparing(const TKinFitterDriver::ResultContainer& rc1, const TKinFitterDriver::ResultContainer& rc2){
  return (rc1.chi2 < rc2.chi2);
}

bool TKinFitterDriver::HadTopPtComparing(const TKinFitterDriver::ResultContainer& rc1, const TKinFitterDriver::ResultContainer& rc2){
  return (rc1.hadronic_top_pt > rc2.hadronic_top_pt);
}

bool TKinFitterDriver::HighMassFitter(const TKinFitterDriver::ResultContainer& rc1, const TKinFitterDriver::ResultContainer& rc2){
  bool out; 
  out=(rc1.chi2 < rc2.chi2) ||
      (
       (rc1.chi2 == rc2.chi2) &&
       (rc1.fitted_hadronic_top_b_jet->Pt() < rc1.fitted_hadronic_w_ch_jet2->Pt()) &&
       (rc1.fitted_hadronic_top_b_jet->Pt() >= rc1.fitted_hadronic_w_ch_jet2->Pt())
      );
  return out;
}
