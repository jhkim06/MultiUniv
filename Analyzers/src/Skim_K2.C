#include "Skim_K2.h"

void Skim_K2::initializeAnalyzer(){

  initializeAnalyzerTools(); //To use SF

  //=================================
  // Skim Types
  //=================================
   

  if( HasFlag("K2")){
    cout<<"[Skim_K2::initializeAnalyzer] TTSemiLepMu Selection"<<endl;
  }
  else{
    cout <<"[Skim_K2::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }
  
  if( HasFlag("Test") ){
    IsTest = true;
    cout<<"[Skim_K2::initializeAnalyzer] Test, do not run systematic"<<endl;
  }
  outfile->mkdir("recoTree");
  outfile->cd("recoTree");

  // Existing Branch
  fChain->SetBranchAddress("IsMu",&IsMu, &b_IsMu);
  fChain->SetBranchAddress("IsEl",&IsEl, &b_IsEl);

  // disable branch
  if(fChain->GetEntries()>0){
    newtree = fChain->CloneTree(0); // JH : What relation does this outfile have with the fChain(created by SetTreeName)?
    newtree->SetBranchStatus("fatjet*",0);
    newtree->SetBranchStatus("photon*",0);
  }
  else{
    newtree = fChain->CloneTree(-1); // JH : What relation does this outfile have with the fChain(created by SetTreeName)?
  }
  // New Branch
  //--------
  // To make branch for dijet mass, best_chi2, fitter_status
  // for various mass(..., M090, M100, ...) and syst(JES/JER)
  //--------
  mass_points = {"M","M090","M100","M110","M120","M130","M140","M150"};
  JES_JER_syst = {"","JESUp","JESDown","JERUp","JERDown"};
  // start nested loop
  for(auto mass : mass_points){
    TString dijet_branch_name_base = TString::Format("_dijet_%s",mass.Data());
    TString chi2_branch_name_base = TString::Format("best_chi2_%s",mass.Data());
    TString status_branch_name_base = TString::Format("fitter_status_%s",mass.Data());
    for(auto syst : JES_JER_syst){
      TString dijet_branch_name_base_syst = dijet_branch_name_base;
      TString chi2_branch_name_base_syst = chi2_branch_name_base;
      TString status_branch_name_base_syst = status_branch_name_base;
      if(syst != ""){
        dijet_branch_name_base_syst = dijet_branch_name_base_syst + "_" + syst;
        chi2_branch_name_base_syst   = chi2_branch_name_base_syst + "_" + syst;
        status_branch_name_base_syst = status_branch_name_base_syst + "_" + syst;
      }
      //cout << "Branch Name: " << dijet_branch_name_base_syst  << endl;
      //cout << "Branch Name: " << chi2_branch_name_base_syst   << endl;
      //cout << "Branch Name: " << status_branch_name_base_syst << endl;
      TString dijet_branch_name_initial_dijet_m   = "initial" + dijet_branch_name_base_syst;
      TString dijet_branch_name_corrected_dijet_m = "corrected" + dijet_branch_name_base_syst;
      TString dijet_branch_name_fitted_dijet_m    = "fitted" + dijet_branch_name_base_syst;
      newtree->Branch(dijet_branch_name_initial_dijet_m, &(initial_dijet_m[syst][mass]), dijet_branch_name_initial_dijet_m + "/D");
      newtree->Branch(dijet_branch_name_corrected_dijet_m, &(corrected_dijet_m[syst][mass]), dijet_branch_name_corrected_dijet_m + "/D");
      newtree->Branch(dijet_branch_name_fitted_dijet_m, &(fitted_dijet_m[syst][mass]), dijet_branch_name_fitted_dijet_m + "/D");

      newtree->Branch(chi2_branch_name_base_syst, &(best_chi2[syst][mass]), chi2_branch_name_base_syst + "/D");
      newtree->Branch(status_branch_name_base_syst, &(fitter_status[syst][mass]), status_branch_name_base_syst + "/I");
    }
  }
  // end of nested loop
  //--------

  newtree->Branch("hadronic_top_M", &hadronic_top_M, "hadronic_top_M/D");
  newtree->Branch("leptonic_top_M", &leptonic_top_M,"leptonic_top_M/D");
  newtree->Branch("leptonic_W_M", &leptonic_W_M,"leptonic_W_M/D");
  newtree->Branch("IsRealNeuPz",&IsRealNeuPz,"IsRealNeuPz/B");
  newtree->Branch("hadronic_top_M_F", &hadronic_top_M_F, "hadronic_top_M_F/D");
  newtree->Branch("leptonic_top_M_F", &leptonic_top_M_F,"leptonic_top_M_F/D");
  newtree->Branch("leptonic_W_M_F", &leptonic_W_M_F,"leptonic_W_M_F/D");
  newtree->Branch("deltaS", &deltaS,"deltaS/D");

  newtree->Branch("hadronic_top_M_vector_success", "vector<double>" ,&hadronic_top_M_vector_success);
  newtree->Branch("hadronic_top_M_vector_fail", "vector<double>" ,&hadronic_top_M_vector_fail);
  newtree->Branch("hadronic_top_b_pt_vector_success", "vector<double>" ,&hadronic_top_b_pt_vector_success);
  newtree->Branch("hadronic_top_b_pt_vector_fail", "vector<double>" ,&hadronic_top_b_pt_vector_fail);
  newtree->Branch("leptonic_top_b_pt_vector_success", "vector<double>" ,&leptonic_top_b_pt_vector_success);
  newtree->Branch("leptonic_top_b_pt_vector_fail", "vector<double>" ,&leptonic_top_b_pt_vector_fail);
  newtree->Branch("wch_up_type_pt_vector_success", "vector<double>" ,&wch_up_type_pt_vector_success);
  newtree->Branch("wch_up_type_pt_vector_fail", "vector<double>" ,&wch_up_type_pt_vector_fail);
  newtree->Branch("wch_down_type_pt_vector_success", "vector<double>" ,&wch_down_type_pt_vector_success);
  newtree->Branch("wch_down_type_pt_vector_fail", "vector<double>" ,&wch_down_type_pt_vector_fail);
  newtree->Branch("selected_lepton_pt", &selected_lepton_pt, "selected_lepton_pt/D");
  newtree->Branch("selected_lepton_eta", &selected_lepton_eta, "selected_lepton_eta/D");
  newtree->Branch("selected_lepton_phi", &selected_lepton_phi, "selected_lepton_phi/D");

  newtree->Branch("njets", &njets,"njets/I");
  newtree->Branch("njets_JES_Up", &njets_JES_Up,"njets_JES_Up/I");
  newtree->Branch("njets_JES_Do", &njets_JES_Do,"njets_JES_Do/I");
  newtree->Branch("njets_JER_Up", &njets_JER_Up,"njets_JER_Up/I");
  newtree->Branch("njets_JER_Do", &njets_JER_Do,"njets_JER_Do/I");

  newtree->Branch("nbtags", &nbtags,"nbtags/I");
  newtree->Branch("nbtags_JES_Up", &nbtags_JES_Up,"nbtags_JES_Up/I");
  newtree->Branch("nbtags_JES_Do", &nbtags_JES_Do,"nbtags_JES_Do/I");
  newtree->Branch("nbtags_JER_Up", &nbtags_JER_Up,"nbtags_JER_Up/I");
  newtree->Branch("nbtags_JER_Do", &nbtags_JER_Do,"nbtags_JER_Do/I");

  newtree->Branch("selected_jet_pt", "vector<double>" ,&selected_jet_pt);
  newtree->Branch("selected_jet_pt_JES_Up", "vector<double>" ,&selected_jet_pt_JES_Up);
  newtree->Branch("selected_jet_pt_JES_Do", "vector<double>" ,&selected_jet_pt_JES_Do);
  newtree->Branch("selected_jet_pt_JER_Up", "vector<double>" ,&selected_jet_pt_JER_Up);
  newtree->Branch("selected_jet_pt_JER_Do", "vector<double>" ,&selected_jet_pt_JER_Do);

  newtree->Branch("selected_jet_eta", "vector<double>" ,&selected_jet_eta);
  newtree->Branch("selected_jet_phi", "vector<double>" ,&selected_jet_phi);

  newtree->Branch("MET", &MET, "MET/D");
  newtree->Branch("MET_JES_Up", &MET_JES_Up, "MET_JES_Up/D");
  newtree->Branch("MET_JES_Do", &MET_JES_Do, "MET_JES_Do/D");
  newtree->Branch("MET_JER_Up", &MET_JER_Up, "MET_JER_Up/D");
  newtree->Branch("MET_JER_Do", &MET_JER_Do, "MET_JER_Do/D");
  // setup btagger
  std::vector<Jet::Tagger> taggers = {Jet::DeepCSV};
  std::vector<Jet::WP> wps ={Jet::Medium};

  SetupBTagger(taggers, wps, true, true);

  fitter_driver = new TKinFitterDriver(DataYear,true,MCSample); // true means use ML cut
}


void Skim_K2::executeEvent(){

  this->Clear();

  //diLep_passSelectiveQ = false;

  evt = new Event;
  *evt = GetEvent();

  //get muons
  muons=GetMuons("POGLooseWithLooseIso",15.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  //get electrons
  electrons=GetElectrons("passVetoID",15.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

  this->executeEventByJESJER(0,0);
  if(!IsData && !IsTest ){
    this->executeEventByJESJER(1,0);
    this->executeEventByJESJER(-1,0);
    this->executeEventByJESJER(0,1);
    this->executeEventByJESJER(0,-1);
  }
  newtree->Fill();
  delete evt;
}


void Skim_K2::executeEventByJESJER(int em_shift_up_down, int res_shift_up_down){

  //set pointers
  double *p_MET;
  std::map<TString, double> *p_best_chi2, *p_initial_dijet_m, *p_corrected_dijet_m, *p_fitted_dijet_m;
  int *p_njets, *p_nbtags;
  std::map<TString, int> *p_fitter_status;
  std::vector<double> *p_selected_jet_pt;
  TString syst_string = "NULL";
  if(em_shift_up_down==0 && res_shift_up_down==0){
    syst_string = "";
    p_selected_jet_pt = &selected_jet_pt;
    p_njets = &njets;
    p_nbtags = &nbtags;
    p_MET = &MET;
  }
  else if(em_shift_up_down==1 && res_shift_up_down==0){
    syst_string = "JESUp";
    p_selected_jet_pt = &selected_jet_pt_JES_Up;
    p_njets = &njets_JES_Up;
    p_nbtags = &nbtags_JES_Up;
    p_MET = &MET_JES_Up;
  }
  else if(em_shift_up_down==-1 && res_shift_up_down==0){
    syst_string = "JESDown";
    p_selected_jet_pt = &selected_jet_pt_JES_Do;
    p_njets = &njets_JES_Do;
    p_nbtags = &nbtags_JES_Do;
    p_MET = &MET_JES_Do;
  }
  else if(em_shift_up_down==0 && res_shift_up_down==1){
    syst_string = "JERUp";
    p_selected_jet_pt = &selected_jet_pt_JER_Up;
    p_njets = &njets_JER_Up;
    p_nbtags = &nbtags_JER_Up;
    p_MET = &MET_JER_Up;
  }
  else if(em_shift_up_down==0 && res_shift_up_down==-1){
    syst_string = "JERDown";
    p_selected_jet_pt = &selected_jet_pt_JER_Do;
    p_njets = &njets_JER_Do;
    p_nbtags = &nbtags_JER_Do;
    p_MET = &MET_JER_Do;
  }
  else{
    cout <<"[Skim_K2::executeEventByJESJER] not supported option" << endl;
    exit(EXIT_FAILURE);
  }

  // assign dijet_m
  if(syst_string != "NULL"){
    p_initial_dijet_m = &(initial_dijet_m[syst_string]);
    p_corrected_dijet_m = &(corrected_dijet_m[syst_string]);
    p_fitted_dijet_m = &(fitted_dijet_m[syst_string]);
    p_best_chi2 = &(best_chi2[syst_string]);
    p_fitter_status = &(fitter_status[syst_string]);
  }
  else{
    cout <<"[Skim_K2::executeEventByJESJER] syst_string is NULL" << endl;
    exit(EXIT_FAILURE);
  }


  // get jets
  vector<Jet> jets = GetJets("tight", 30., 2.4, em_shift_up_down, res_shift_up_down); 
  jets = JetsVetoLeptonInside(jets, electrons, muons);
  std::sort(jets.begin(), jets.end(), PtComparing);
  if(jets.size()<4){
    return;
  }

  // set btag vector
  std::vector<bool> btag_vector_noSF;
  int nbtags_=0;
  for(unsigned int ij = 0 ; ij < jets.size(); ij++){
    if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,false,0)){
      btag_vector_noSF.push_back(true);
      nbtags_ += 1;
    }
    else{
      btag_vector_noSF.push_back(false);
    }
  }
  if(jets.size()!=btag_vector_noSF.size()){
    cout <<"[Skim_K2::executeEventByJETJER] check jet vector size" << endl;
    exit(EXIT_FAILURE);
  }
  *p_nbtags = nbtags_;
  if(*p_nbtags<2){
    return;
  }
    ///////////////////////////////////////////////////////////
   // !!!!!!!!!!!!!!!!!! execute fitter !!!!!!!!!!!!!!!!!!! //
  ///////////////////////////////////////////////////////////
  TLorentzVector lepton(0.,0.,0.,0.);
  Particle METv = evt->GetMETVector();
  //correct MET by JES/JER 
  if(em_shift_up_down!=0 || res_shift_up_down!=0){
    vector<Jet> jets_nominal = GetJets("tight", 30., 2.4); 
    jets_nominal = JetsVetoLeptonInside(jets_nominal, electrons, muons);
    METv = UpdateMET(METv, jets_nominal, jets);
  }
  // set lepton
  if(IsMu){
    lepton = muons.at(0);
    METv = UpdateMET(METv, muons);
  }
  else if(IsEl){
    lepton = electrons.at(0);
  }

  // set fitter
  fitter_driver->SetAllObjects(jets, 
                               btag_vector_noSF,
                               lepton,
                               (TLorentzVector)METv
                              );
  // find best chi2
  fitter_driver->FindBestChi2Fit(false); // true means use only leading four jets

  //std::vector<TKinFitterDriver::ResultContatiner> fit_result_vector = fitter_driver->GetResults();

  for(auto mass : mass_points){
    TString sample_label = mass=="M"?"CHToCB_M120":"CHToCB_"+mass;
    (*p_initial_dijet_m)[mass] = fitter_driver->GetBestInitialDijetMass(sample_label);
    (*p_corrected_dijet_m)[mass] = fitter_driver->GetBestCorrectedDijetMass(sample_label);
    (*p_fitted_dijet_m)[mass] = fitter_driver->GetBestFittedDijetMass(sample_label);

    (*p_best_chi2)[mass] = fitter_driver->GetBestChi2(sample_label);
    (*p_fitter_status)[mass] = fitter_driver->GetBestStatus(sample_label);
  }

  // nominal only
  if(em_shift_up_down==0 && res_shift_up_down==0){
    hadronic_top_M = fitter_driver->GetBestHadronicTopMass();
    leptonic_top_M = fitter_driver->GetBestLeptonicTopMass();
    leptonic_W_M = fitter_driver->GetBestLeptonicWMass();
    IsRealNeuPz = fitter_driver->GetBestIsRealNeuPz();
    hadronic_top_M_F = fitter_driver->GetBestHadronicTopMassF();
    leptonic_top_M_F = fitter_driver->GetBestLeptonicTopMassF();
    leptonic_W_M_F = fitter_driver->GetBestLeptonicWMassF();
    deltaS = fitter_driver->GetBestDeltaS();
    hadronic_top_M_vector_success = fitter_driver->GetHadronicTopMassVector(true);
    hadronic_top_M_vector_fail = fitter_driver->GetHadronicTopMassVector(false);
    hadronic_top_b_pt_vector_success = fitter_driver->GetHadronicTopBPtVector(true);
    hadronic_top_b_pt_vector_fail = fitter_driver->GetHadronicTopBPtVector(false);
    leptonic_top_b_pt_vector_success = fitter_driver->GetLeptonicTopBPtVector(true);
    leptonic_top_b_pt_vector_fail = fitter_driver->GetLeptonicTopBPtVector(false);
    wch_up_type_pt_vector_success = fitter_driver->GetWCHUpTypePtVector(true);
    wch_up_type_pt_vector_fail = fitter_driver->GetWCHUpTypePtVector(false);
    wch_down_type_pt_vector_success = fitter_driver->GetWCHDownTypePtVector(true);
    wch_down_type_pt_vector_fail = fitter_driver->GetWCHDownTypePtVector(false);

    selected_lepton_pt  = lepton.Pt();
    selected_lepton_eta = lepton.Eta();
    selected_lepton_phi = lepton.Phi();
    for(auto& x : jets){
      selected_jet_eta.push_back(x.Eta());
      selected_jet_phi.push_back(x.Phi());
    }
  }
    
  *p_njets= jets.size();
  *p_MET = METv.E();
  for(auto& x : jets){
    p_selected_jet_pt->push_back(x.Pt());
  }

}


Skim_K2::Skim_K2(){
  IsTest = false;
}


Skim_K2::~Skim_K2(){
  delete fitter_driver;
}


void Skim_K2::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_K2::initializeAnalyzer
  newtree->AutoSave();
  //newtree->Write();
  outfile->cd();
  for(std::map< TString, TH1D* >::iterator mapit = maphist_TH1D.begin(); mapit!=maphist_TH1D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
  }
  for(std::map< TString, TH2D* >::iterator mapit = maphist_TH2D.begin(); mapit!=maphist_TH2D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
  }

  outfile->cd();
  for(std::map< TString, std::map<TString, TH1D*> >::iterator mapit=JSmaphist_TH1D.begin(); mapit!=JSmaphist_TH1D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH1D* > this_maphist = mapit->second;


    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH1D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }

  for(std::map< TString, std::map<TString, TH2D*> >::iterator mapit=JSmaphist_TH2D.begin(); mapit!=JSmaphist_TH2D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH2D* > this_maphist = mapit->second;

    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH2D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }

}

void Skim_K2::Clear(){

  muons.clear();
  electrons.clear();
  hadronic_top_M_vector_success.clear();
  hadronic_top_M_vector_success.shrink_to_fit();
  hadronic_top_M_vector_fail.clear();
  hadronic_top_M_vector_fail.shrink_to_fit();
  hadronic_top_b_pt_vector_success.clear();
  hadronic_top_b_pt_vector_success.shrink_to_fit();
  hadronic_top_b_pt_vector_fail.clear();
  hadronic_top_b_pt_vector_fail.shrink_to_fit();
  leptonic_top_b_pt_vector_success.clear();
  leptonic_top_b_pt_vector_success.shrink_to_fit();
  leptonic_top_b_pt_vector_fail.clear();
  leptonic_top_b_pt_vector_fail.shrink_to_fit();
  wch_up_type_pt_vector_success.clear();
  wch_up_type_pt_vector_success.shrink_to_fit();
  wch_up_type_pt_vector_fail.clear();
  wch_up_type_pt_vector_fail.shrink_to_fit();
  wch_down_type_pt_vector_success.clear();
  wch_down_type_pt_vector_success.shrink_to_fit();
  wch_down_type_pt_vector_fail.clear();
  wch_down_type_pt_vector_fail.shrink_to_fit();
  selected_jet_pt.clear();
  selected_jet_pt_JES_Up.clear();
  selected_jet_pt_JES_Do.clear();
  selected_jet_pt_JER_Up.clear();
  selected_jet_pt_JER_Do.clear();
  selected_jet_eta.clear();
  selected_jet_phi.clear();

  //----------
  // clear dijet mass
  for(auto* map : {&initial_dijet_m, &corrected_dijet_m, &fitted_dijet_m}){
    for(auto& value1 : *map){
      for(auto& value2 : value1.second){
        value2.second = -1;
      }
    }
  }
  for(auto& value1 : best_chi2){
    for(auto& value2 : value1.second){
      value2.second = -10;
    }
  }
  for(auto& value1 : fitter_status){
    for(auto& value2 : value1.second){
      value2.second = -2;
    }
  }
  //----------

  selected_lepton_pt=-1;
  selected_lepton_eta=-1;
  selected_lepton_phi=-1;

  njets=-1; //number of jets
  njets_JES_Up=-1;
  njets_JES_Do=-1;
  njets_JER_Up=-1;
  njets_JER_Do=-1;

  nbtags=-1; //number of jets
  nbtags_JES_Up=-1;
  nbtags_JES_Do=-1;
  nbtags_JER_Up=-1;
  nbtags_JER_Do=-1;

  MET=-1;
  MET_JES_Up=-1;
  MET_JES_Do=-1;
  MET_JER_Up=-1;
  MET_JER_Do=-1;

}
