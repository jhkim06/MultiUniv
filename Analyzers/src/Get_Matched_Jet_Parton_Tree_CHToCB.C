#include "Get_Matched_Jet_Parton_Tree_CHToCB.h"

void Get_Matched_Jet_Parton_Tree_CHToCB::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //=================================
  // setup TFile, TTree
  //=================================
  outfile->SetCompressionLevel(1);
  newtree = new TTree("TSCorr_tree","TSCorr_tree");
  //=================================
  // set pointers
  //=================================
  //out obj. reco
  b_jet_from_top = new TLorentzVector(1.,1.,1.,1.);
  b_jet_from_anti_top = new TLorentzVector(1.,1.,1.,1.);
  down_type_jet_from_w_ch = new TLorentzVector(1.,1.,1.,1.);
  up_type_jet_from_w_ch = new TLorentzVector(1.,1.,1.,1.);
  lepton = new TLorentzVector(1.,1.,1.,1.);
  METv = new TLorentzVector(1.,1.,1.,1.);
  //out obj. truth
  b_parton_from_top = new TLorentzVector(1.,1.,1.,1.);
  b_parton_from_anti_top = new TLorentzVector(1.,1.,1.,1.);
  down_type_parton_from_w_ch = new TLorentzVector(1.,1.,1.,1.);
  up_type_parton_from_w_ch = new TLorentzVector(1.,1.,1.,1.);
  neutrino = new TLorentzVector(1.,1.,1.,1.);  

  //=================================
  // New Branch
  //=================================
  //out obj. reco
  newtree->Branch("b_jet_from_top","TLorentzVector",&b_jet_from_top);
  newtree->Branch("b_jet_from_anti_top","TLorentzVector",&b_jet_from_anti_top);
  newtree->Branch("down_type_jet_from_w_ch","TLorentzVector",&down_type_jet_from_w_ch);
  newtree->Branch("up_type_jet_from_w_ch","TLorentzVector",&up_type_jet_from_w_ch);
  newtree->Branch("lepton","TLorentzVector",&lepton);
  newtree->Branch("METv","TLorentzVector",&METv);
  //out obj. truth
  newtree->Branch("b_parton_from_top","TLorentzVector",&b_parton_from_top);
  newtree->Branch("b_parton_from_anti_top","TLorentzVector",&b_parton_from_anti_top);
  newtree->Branch("down_type_parton_from_w_ch","TLorentzVector",&down_type_parton_from_w_ch);
  newtree->Branch("up_type_parton_from_w_ch","TLorentzVector",&up_type_parton_from_w_ch);
  newtree->Branch("neutrino","TLorentzVector",&neutrino);

  gen_matcher = new GenMatching_CHToCB();
}

void Get_Matched_Jet_Parton_Tree_CHToCB::executeEvent(){

  muons.clear();
  electrons.clear();

  FillHist("CutFlow",0,1,30,0,30);

  // Filters ====================
  if(!PassMETFilter()) return;
  FillHist("CutFlow",1,1,30,0,30);

  // select obj, XXX: slopy this time
  muons=GetMuons("POGTight",30.,2.4);
  TString ElectronID = "passTightID";
  electrons=GetElectrons(ElectronID,30.,2.5);
  if(muons.size()+electrons.size() !=1) return; // 1 tight lepton

  TLorentzVector reco_lepton;
  if(muons.size()==1) reco_lepton = muons.at(0);
  else if(electrons.size()==1) reco_lepton = electrons.at(0);
  FillHist("CutFlow",2,1,30,0,30);
  //TODO: will add extra lepton veto

  evt = new Event;
  *evt = GetEvent();
  TLorentzVector MET_vector = evt->GetMETVector();
  if(MET_vector.Et()<20) return;
  FillHist("CutFlow",3,1,30,0,30);

  vector<Jet> this_AllJets = GetAllJets();
  vector<Gen> this_AllGens = GetGens();
  vector<Jet> jets = SelectJets(this_AllJets, "tight", 30., 2.4);
  std::sort(jets.begin(), jets.end(), PtComparing);
  if(jets.size()<4) return;
  FillHist("CutFlow",4,1,30,0,30);

  gen_matcher->SetGens(this_AllGens);
  gen_matcher->SetJets(jets);
  if(!gen_matcher->FindHardProcessParton()) return; // find parton from hard process
  FillHist("CutFlow",5,1,30,0,30);

  if(!gen_matcher->MatchJets()) return; // match parton-jet min-delta R
  FillHist("CutFlow",6,1,30,0,30);

  *b_jet_from_top = gen_matcher->Get_hadronic_top_b_jet();
  *b_jet_from_anti_top = gen_matcher->Get_leptonic_top_b_jet();
  *down_type_jet_from_w_ch = gen_matcher->Get_down_type_jet();
  *up_type_jet_from_w_ch = gen_matcher->Get_up_type_jet();
  *lepton = reco_lepton;
  *METv = MET_vector;

  //out obj. truth
  *b_parton_from_top = gen_matcher->Get_hadronic_top_b_parton();
  *b_parton_from_anti_top = gen_matcher->Get_leptonic_top_b_parton();
  *down_type_parton_from_w_ch = gen_matcher->Get_down_type_parton();
  *up_type_parton_from_w_ch = gen_matcher->Get_up_type_parton();
  *neutrino = gen_matcher->Get_neutrino();

  newtree->Fill();

  return;

}


void Get_Matched_Jet_Parton_Tree_CHToCB::executeEventFromParameter(AnalyzerParameter param){

}

Get_Matched_Jet_Parton_Tree_CHToCB::Get_Matched_Jet_Parton_Tree_CHToCB(){

}

Get_Matched_Jet_Parton_Tree_CHToCB::~Get_Matched_Jet_Parton_Tree_CHToCB(){
  delete newtree;
  //out obj. reco
  delete b_jet_from_top;
  delete b_jet_from_anti_top;
  delete down_type_jet_from_w_ch;
  delete up_type_jet_from_w_ch;
  delete lepton;
  delete METv;

  //out obj. truth
  delete b_parton_from_top;
  delete b_parton_from_anti_top;
  delete down_type_parton_from_w_ch;
  delete up_type_parton_from_w_ch;
  delete neutrino;

  delete gen_matcher;
}

void Get_Matched_Jet_Parton_Tree_CHToCB::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Get_Matched_Jet_Parton_Tree_CHToCB::initializeAnalyzer
  //newtree->AutoSave();
  newtree->Write();
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

