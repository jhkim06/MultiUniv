#include "Skim_DiLep.h"

void Skim_DiLep::initializeAnalyzer(){

  initializeAnalyzerTools(); //To use SF

  //=================================
  // Skim Types
  //=================================
   
  IsMuMu = false;
  IsElEl = false;

  if( HasFlag("MuMu")){
    IsMuMu = true;
    cout<<"[Skim_DiLep::initializeAnalyzer] Same  Flavor Selection"<<endl;
  }
  else
  if( HasFlag("ElEl")){
    IsElEl = true;
  }
  else{
    cout <<"[Skim_DiLep::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  // New Branch
  newtree->Branch("trgSF", &trgSF,"trgSF/D");
  newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/D");
  newtree->Branch("trgSF_Dn", &trgSF_Dn,"trgSF_Dn/D");
  //b_trgSF = newtree->Branch("trgSF", &trgSF,"trgSF/F");
  //b_trgSF_Up = newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/F");
  //b_trgSF_Dn = newtree->Branch("trgSF_Dn", &trgSF_Dn,"trgSF_Dn/F");



  // clear vector residual
  DiMuTrgs.clear();
  DiElTrgs.clear();


  cout << "[Skim_DiLep::initializeAnalyzer] Skim List====================== " << endl;
  if(DataYear==2016){
    DiMuTrgs = {
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
      "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
      "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
    };
    DiElTrgs = {
      "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"
    };
  }
  else if(DataYear==2017){
    DiMuTrgs = {
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",
    };
    DiElTrgs = {
      "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"
    };
  }
  else{
    cout<<"[Skim_DiLep::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
    exit(EXIT_FAILURE);
  }

  cout << "\t"<<"doubleTrgs to skim = " << endl;
  for(unsigned int i=0; i<DiMuTrgs.size(); i++){
    cout << "\t" << DiMuTrgs.at(i) << endl;
  }
  for(unsigned int i=0; i<DiElTrgs.size(); i++){
    cout << "\t" << DiElTrgs.at(i) << endl;
  }

}

void Skim_DiLep::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  evt = new Event;
  *evt = GetEvent();

  newtree->SetBranchAddress("trgSF",&trgSF);
  newtree->SetBranchAddress("trgSF_Up",&trgSF_Up);
  newtree->SetBranchAddress("trgSF_Dn",&trgSF_Dn);

  FillHist("CutFlow",5,1,30,0,30);
  // Filters ====================
  //if( HasFlag("MetFilt"))if(!PassMETFilter()) return;
  FillHist("CutFlow",6,1,30,0,30);


  muons=GetMuons("POGTightWithTightIso",7.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  electrons=GetElectrons("passMediumID",9.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

  LeptonID_SF=NULL;
  LeptonISO_SF=NULL;
  LeptonReco_SF=NULL;
  PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

  // dilepton condition
  if(IsMuMu){ // Muon-----------------------------
    if(electrons.size() > 0) return;
    if(muons.size() != 2   ) return;
    if(! evt->PassTrigger(DiMuTrgs) )return;
    leps=MakeLeptonPointerVector(muons);
    Lep0PtCut=20.;
    Lep1PtCut=10.;
    LeptonID_SF=&MCCorrection::MuonID_SF;
    LeptonISO_SF=&MCCorrection::MuonISO_SF;
    LeptonID_key="NUM_TightID_DEN_genTracks";
    LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";
    trgSF_key0="Leg17_POGTight";
    trgSF_key1="Leg8_POGTight";
  } //---------------------------------------------
  if(IsElEl){ // Electron =======================
    if(electrons.size() != 0) return;
    if(muons.size() > 0   ) return;
    if(! evt->PassTrigger(DiElTrgs) )return;
    leps=MakeLeptonPointerVector(electrons);
    Lep0PtCut=25.;
    Lep1PtCut=15.;
    LeptonID_SF=&MCCorrection::ElectronID_SF;
    LeptonReco_SF=&MCCorrection::ElectronReco_SF;
    LeptonID_key="passMediumID_pt10";
    LeptonID_key_POG="passMediumID";
    trgSF_key0="LeadEle23_MediumID";
    trgSF_key1="TailEle12_MediumID";
  } //===========================================

  // SF =========================
  /////////////////PUreweight///////////////////
  PUweight=1.,PUweight_Up=1.,PUweight_Dn=1.;
  if(!IsDATA){
    PUweight=(mcCorr->*PileUpWeight)(nPileUp,0);
    PUweight_Up=(mcCorr->*PileUpWeight)(nPileUp,1);
    PUweight_Dn=(mcCorr->*PileUpWeight)(nPileUp,-1);
  }


  //if( ChName.Contains("DoubleMuon")){

  //  Lep0PtCut = 20;
  //  Lep1PtCut = 10;
  //  EtaCut=2.4;

  //  trgSF_Leg0Key = "Leg17_POGTight"; // As writtern at histmaps.txt
  //  trgSF_Leg1Key = "Leg8_POGTight";

  //  leps=MakeLeptonPointerVector(muons);


  //}
  //if( ChName.Contains("DoubleElectron")){

  //  Lep0PtCut=25.;
  //  Lep1PtCut=15.;
  //  EtaCut=2.5;

  //  trgSF_Leg0Key="LeadEle23_MediumID";
  //  trgSF_Leg1Key="TailEle12_MediumID";

  //  leps=MakeLeptonPointerVector(electrons);


  //}




  trgSF=1;
  trgSF_Up=1;
  trgSF_Dn=1;

  recoSF=1;
  recoSF_Up=1;
  recoSF_Dn=1;

  //Double Lepton condition
  if(leps.size() >= 2){
    PtEtaPass = true;
    if(leps.at(0)->Pt()<Lep0PtCut||leps.at(1)->Pt()<Lep1PtCut) PtEtaPass = false;
    if(fabs(leps.at(0)->Eta())>EtaCut||fabs(leps.at(1)->Eta()>EtaCut))PtEtaPass =  false;

    if(!IsDATA)if(PtEtaPass){
      trgSF      = DiLepTrg_SF(trgSF_key0,trgSF_key1,leps,0);
      trgSF_Up   = DiLepTrg_SF(trgSF_key0,trgSF_key1,leps,1);
      trgSF_Dn   = DiLepTrg_SF(trgSF_key0,trgSF_key1,leps,-1);
    }
  }




    //baseW = weight_norm_1invpb*ev->MCweight()*ev->GetTriggerLumi("Full");


  //b_trgSF->Fill();
  //b_trgSF_Up->Fill();
  //b_trgSF_Dn->Fill();
  newtree->Fill();


}
double Skim_DiLep::DiLepTrg_SF(TString Leg0Key, TString Leg1Key, const vector<Lepton*>& leps, int sys){
  if(IsDATA) return 1;
  if(leps.size()<2){
  //if(leps.size()!=2)
    //cout<<"[Skim_DiLep::DiLepTrg_SF] only dilepton algorithm"<<endl;
    return 1;
  }
  map<TString,TH2F*>* map_hist_Lepton=NULL;
  if(leps[0]->LeptonFlavour()==Lepton::MUON){
    map_hist_Lepton=&mcCorr->map_hist_Muon;
  }else if(leps[0]->LeptonFlavour()==Lepton::ELECTRON){
    map_hist_Lepton=&mcCorr->map_hist_Electron;
  }else{
    cout <<"[Skim_DiLep::DiLepTrg_SF] Not ready"<<endl;
    exit(EXIT_FAILURE);
  }    
      
  TH2F* this_hist[2]={NULL,NULL};
  double triggerSF=1.;
  this_hist[0]=(*map_hist_Lepton)["Trigger_SF_"+Leg0Key];
  this_hist[1]=(*map_hist_Lepton)["Trigger_SF_"+Leg1Key];
  if(!this_hist[0]||!this_hist[1]){
    cout << "[Skim_DiLep::DiLepTrg_SF] No "<<Leg0Key<<" or "<<Leg1Key<<" at data/ID/../histmap.txt"<<endl;
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<2;i++){
    double this_pt,this_eta;
    if(leps[i]->LeptonFlavour()==Lepton::MUON){
      this_pt=((Muon*)leps.at(i))->MiniAODPt();
      this_eta=leps.at(i)->Eta();
    }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
      this_pt=leps.at(i)->Pt();
      this_eta=((Electron*)leps.at(i))->scEta();
    }else{
      cout << "[Skim_DiLep::DiLepTrg_SF] It is not lepton"<<endl;
      exit(EXIT_FAILURE);
    }
    /*
    double ptmin=this_hist[i]->GetYaxis()->GetXmin();
    double ptmax=this_hist[i]->GetYaxis()->GetXmax();
    double etamin=this_hist[i]->GetXaxis()->GetXmin();
    double etamax=this_hist[i]->GetXaxis()->GetXmax();    
    if(this_pt<ptmin) this_pt=ptmin+0.001;
    if(this_pt>ptmax) this_pt=ptmax-0.001;
    if(etamin>=0) this_eta=fabs(this_eta);
    if(this_eta<etamin) this_eta=etamin+0.001;
    if(this_eta>etamax) this_eta=etamax-0.001;
    triggerSF*=this_hist[i]->GetBinContent(this_hist[i]->FindBin(this_eta,this_pt))+sys*this_hist[i]->GetBinError(this_hist[i]->FindBin(this_eta,this_pt));
    */
    triggerSF *= RootHelper::GetBinContentUser(this_hist[i],this_eta,this_pt,sys);
    //triggerSF *= rootHelp.GetBinContentUser(this_hist[i],this_eta,this_pt,sys);
  }
  return triggerSF;
}


void Skim_DiLep::executeEventFromParameter(AnalyzerParameter param){

}

Skim_DiLep::Skim_DiLep(){

}

Skim_DiLep::~Skim_DiLep(){

}

void Skim_DiLep::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_DiLep::initializeAnalyzer
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

