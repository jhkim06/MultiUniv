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

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0); // JH : What relation does this outfile have with the fChain(created by SetTreeName)?

  // Existing Branch
  fChain->SetBranchAddress("IsMu",&IsMu, &b_IsMu);
  fChain->SetBranchAddress("IsEl",&IsEl, &b_IsEl);

  // disable branch
  if(fChain->GetEntries()>0){
    newtree->SetBranchStatus("fatjet*",0);
    newtree->SetBranchStatus("photon*",0);
  }

  // New Branch
  newtree->Branch("initial_dijet_m", &initial_dijet_m,"initial_dijet_m/D");
  newtree->Branch("corrected_dijet_m", &corrected_dijet_m,"corrected_dijet_m/D");
  newtree->Branch("fitted_dijet_m", &fitted_dijet_m,"fitted_dijet_m/D");
  newtree->Branch("best_chi2", &best_chi2,"best_chi2/D");
  newtree->Branch("fitter_status", &fitter_status,"fitter_status/I");

  newtree->Branch("selected_lepton_pt", &selected_lepton_pt, "selected_lepton_pt/D");
  newtree->Branch("selected_lepton_eta", &selected_lepton_eta, "selected_lepton_eta/D");
  newtree->Branch("selected_lepton_phi", &selected_lepton_phi, "selected_lepton_phi/D");

  newtree->Branch("njets", &njets,"njets/I");
  newtree->Branch("selected_jet_pt", "vector<double>" ,&selected_jet_pt);

  newtree->Branch("selected_jet_eta", "vector<double>" ,&selected_jet_eta);
  newtree->Branch("selected_jet_phi", "vector<double>" ,&selected_jet_phi);

  // setup btagger
  std::vector<Jet::Tagger> taggers = {Jet::DeepCSV};
  std::vector<Jet::WP> wps ={Jet::Medium};

  SetupBTagger(taggers, wps, true, true);

  fitter_driver = new TKinFitterDriver(DataYear); 
}

void Skim_K2::executeEvent(){

  muons.clear();
  electrons.clear();

  selected_jet_pt.clear();
  selected_jet_eta.clear();
  selected_jet_phi.clear();
  //diLep_passSelectiveQ = false;

  evt = new Event;
  *evt = GetEvent();

  muons=GetMuons("POGLooseWithLooseIso",15.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  electrons=GetElectrons("passVetoID",15.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

  vector<Jet> this_AllJets = GetAllJets();
  vector<Jet> jets = SelectJets(this_AllJets, "tight", 30., 2.4);
  jets = JetsVetoLeptonInside(jets, electrons, muons);
  std::sort(jets.begin(), jets.end(), PtComparing);
  if(jets.size()<4) return;

  std::vector<bool> btag_vector_noSF;
  for(unsigned int ij = 0 ; ij < jets.size(); ij++){
    if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,false,0)){
      btag_vector_noSF.push_back(true);
    }
    else{
      btag_vector_noSF.push_back(false);
    }
  }
  if(jets.size()!=btag_vector_noSF.size()){
    cout <<"[Skim_K2::executeEvent] check jet vector size" << endl;
    exit(EXIT_FAILURE);
  }
  
    ///////////////////////////////////////////////////////////
   // !!!!!!!!!!!!!!!!!! execute fitter !!!!!!!!!!!!!!!!!!! //
  ///////////////////////////////////////////////////////////
  if(IsMu){
    fitter_driver->SetAllObjects(jets, 
                                 btag_vector_noSF,
                                 (TLorentzVector)muons.at(0),
                                 (TLorentzVector)evt->GetMETVector()
                                );
  }
  else if(IsEl){
    fitter_driver->SetAllObjects(jets,
                                 btag_vector_noSF,
                                 (TLorentzVector)electrons.at(0),
                                 (TLorentzVector)evt->GetMETVector()
                                );
  }
  fitter_driver->FindBestChi2Fit(false); // true means use only leading four jets
  fitter_status = fitter_driver->GetStatus();
  if(fitter_status==0){ //0 means fit converge
    initial_dijet_m = fitter_driver->GetBestInitialDijetMass();
    corrected_dijet_m = fitter_driver->GetBestCorrectedDijetMass();
    fitted_dijet_m = fitter_driver->GetBestFittedDijetMass();
    best_chi2 = fitter_driver->GetChi2();
  }
  else{
    initial_dijet_m = -1;
    corrected_dijet_m = -1;
    fitted_dijet_m = -1;
    best_chi2 = -1;
  }

  ///////////////////////////////////////////////
  // add Kinematic Variables
  ///////////////////////////////////////////////

  if(IsMu){
    selected_lepton_pt = muons.at(0).Pt();
    selected_lepton_eta = muons.at(0).Eta();
    selected_lepton_phi = muons.at(0).Phi();
  }
  else if(IsEl){
    selected_lepton_pt = electrons.at(0).Pt();
    selected_lepton_eta = electrons.at(0).Eta();
    selected_lepton_phi = electrons.at(0).Phi();
  }
  njets= jets.size();
  for(auto& x : jets){
    selected_jet_pt.push_back(x.Pt());
    selected_jet_eta.push_back(x.Eta());
    selected_jet_phi.push_back(x.Phi());
  }

  newtree->Fill();

}



void Skim_K2::executeEventFromParameter(AnalyzerParameter param){

}

Skim_K2::Skim_K2(){

}

Skim_K2::~Skim_K2(){
 //delete fitter_driver;
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

