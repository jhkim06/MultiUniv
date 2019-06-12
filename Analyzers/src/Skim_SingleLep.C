#include "Skim_SingleLep.h"

void Skim_SingleLep::initializeAnalyzer(){

  //initializeAnalyzerTools(); //defined at AnalyzerCor and executed at the run script 

  //=================================
  // Skim Types
  //=================================
   

  if( HasFlag("SingleLep")){
    cout<<"[Skim_SingleLep::initializeAnalyzer] SingleLep Selection"<<endl;
  }

  /*
  else if( HasFlag("MuOrEl")){
    cout<<"[Skim_SingleLep::initializeAnalyzer] Mu or El Selection"<<endl;
  }
  */
  else{
    cout <<"[Skim_SingleLep::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0); // JH : What relation does this outfile have with the fChain(created by SetTreeName)?

  // New Branch
  newtree->Branch("IsMu", &IsMu,"IsMu/I"); // JH : What's the meaning of each arguments?
  newtree->Branch("IsEl", &IsEl,"IsEl/I");
  newtree->Branch("passTightID", &passTightID,"passTightID/I");
  newtree->Branch("passIso", &passIso,"passIso/I");
  newtree->Branch("passAntiIso", &passAntiIso,"passAntiIso/I");
  newtree->Branch("passAntiIso_Up", &passAntiIso_Up,"passAntiIso_Up/I");
  newtree->Branch("passAntiIso_Do", &passAntiIso_Do,"passAntiIso_Do/I");

  // clear vector residual
  SingleMuTrgs.clear();
  SingleElTrgs.clear();


  cout << "[Skim_SingleLep::initializeAnalyzer] Skim List====================== " << endl;
  if(DataYear==2016){
    SingleMuTrgs = {
      "HLT_IsoMu24_v"
    };
    SingleElTrgs = {
      "HLT_Ele27_WPTight_Gsf_v"
    };
    Mu0PtCut=26;
    Mu0EtaCut=2.4;
    El0PtCut=30;
    El0EtaCut=2.5;
  }
  else if(DataYear==2017){
    SingleMuTrgs = {
      "HLT_IsoMu27_v"
    };
    SingleElTrgs = {
      "HLT_Ele35_WPTight_Gsf_v"
    };
    Mu0PtCut=29;
    Mu0EtaCut=2.4;
    El0PtCut=38;
    El0EtaCut=2.5;
  }
  else{
    cout<<"[Skim_SingleLep::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
    exit(EXIT_FAILURE);
  }

  cout << "\t"<<"doubleTrgs to skim = " << endl;
  for(unsigned int i=0; i<SingleMuTrgs.size(); i++){
    cout << "\t" << SingleMuTrgs.at(i) << endl;
  }
  for(unsigned int i=0; i<SingleElTrgs.size(); i++){
    cout << "\t" << SingleElTrgs.at(i) << endl;
  }

}

void Skim_SingleLep::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  evt = new Event;
  *evt = GetEvent();

  newtree->SetBranchAddress("IsMu",   &IsMu);
  newtree->SetBranchAddress("IsEl",   &IsEl);

  newtree->SetBranchAddress("passTightID",   &passTightID);
  newtree->SetBranchAddress("passIso",   &passIso);
  newtree->SetBranchAddress("passAntiIso",   &passAntiIso);
  newtree->SetBranchAddress("passAntiIso_Up",   &passAntiIso_Up);
  newtree->SetBranchAddress("passAntiIso_Do",   &passAntiIso_Do);

  // Filters ====================
  //if( HasFlag("MetFilt"))if(!PassMETFilter()) return;

  muons=GetMuons("POGLooseWithLooseIso",15.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  electrons=GetElectrons("passVetoID",15.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

  IsMu = 0;
  IsEl = 0;
  //=========================
  // SingleLepton condition
  //=========================
  if(muons.size() == 1 && electrons.size() == 0){
    IsMu = 1;
  }
  if(muons.size() == 0 && electrons.size() == 1){
    IsEl = 1;
  }
  if(IsMu != 1 && IsEl != 1) return;
  FillHist("CutFlow",3,1,30,0,30);
  //=========================
  // check ID and isolation condition
  //=========================
  if(IsMu){
    passTightID=muons.at(0).isPOGTight();
    passIso=muons.at(0).isPOGTightIso();
    passAntiIso=muons.at(0).isAntiIso(0);
    passAntiIso_Up=muons.at(0).isAntiIso(1);
    passAntiIso_Do=muons.at(0).isAntiIso(-1);
  }
  else if(IsEl){
    passTightID=electrons.at(0).Pass_CutBasedTightNoIso();
    passIso=electrons.at(0).isCutBasedTightIso();
    passAntiIso=electrons.at(0).isAntiIso("Tight",0);
    passAntiIso_Up=electrons.at(0).isAntiIso("Tight",1);
    passAntiIso_Do=electrons.at(0).isAntiIso("Tight",-1);
  }

  if(IsMu == 1){ // Muon-----------------------------
    if(! evt->PassTrigger(SingleMuTrgs) )return;
    leps=MakeLeptonPointerVector(muons);
    Lep0PtCut=Mu0PtCut;
    LepEtaCut = Mu0EtaCut;
  } //---------------------------------------------
  if(IsEl == 1){ // Electron =======================
    if(! evt->PassTrigger(SingleElTrgs) )return;
    //if(electrons[0].SelectiveQ() )if(electrons[1].SelectiveQ())  diLep_passSelectiveQ = true;
    leps=MakeLeptonPointerVector(electrons);
    Lep0PtCut=El0PtCut;
    LepEtaCut = El0EtaCut;
  } //===========================================
  FillHist("CutFlow",4,1,30,0,30);

  // ================================
  // Kinematic cuts 
  // ================================
  for(int i(0); i < 1; i++){ // one lepton only, pt eta the same to TnP
    if(leps[i]->LeptonFlavour()==Lepton::MUON){
     Aod_pt[i]=((Muon*)leps.at(i))->MiniAODPt();
     Aod_eta[i]=leps.at(i)->Eta();
    }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
     Aod_pt[i]=leps.at(i)->Pt();
     Aod_eta[i]=((Electron*)leps.at(i))->scEta();
     if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
    }
  }
  if(Aod_pt[0] < Lep0PtCut) return;
  if(fabs(Aod_eta[0]) > LepEtaCut) return;
  FillHist("CutFlow",5,1,30,0,30);

  newtree->Fill();


}



void Skim_SingleLep::executeEventFromParameter(AnalyzerParameter param){

}

Skim_SingleLep::Skim_SingleLep(){

}

Skim_SingleLep::~Skim_SingleLep(){
 //delete fitter_driver;
}

void Skim_SingleLep::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_SingleLep::initializeAnalyzer
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

