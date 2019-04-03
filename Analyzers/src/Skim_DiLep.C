#include "Skim_DiLep.h"

void Skim_DiLep::initializeAnalyzer(){

  initializeAnalyzerTools(); //To use SF

  //=================================
  // Skim Types
  //=================================
   

  if( HasFlag("MuMu")){
    cout<<"[Skim_DiLep::initializeAnalyzer] MuMu Selection"<<endl;
  }
  else if( HasFlag("ElEl")){
    cout<<"[Skim_DiLep::initializeAnalyzer] ElEl Selection"<<endl;
  }
  else if( HasFlag("MuMuOrElEl")){
    cout<<"[Skim_DiLep::initializeAnalyzer] MuMu or ElEl Selection"<<endl;
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
  newtree = fChain->CloneTree(0); // JH : What relation does this outfile have with the fChain(created by SetTreeName)?

  // New Branch
  newtree->Branch("IsMuMu", &IsMuMu,"IsMuMu/I"); // JH : What's the meaning of each arguments?
  newtree->Branch("IsElEl", &IsElEl,"IsElel/I");


  newtree->Branch("PUweight", &PUweight,"PUweight/D");
  newtree->Branch("PUweight_Up", &PUweight_Up,"PUweight_Up/D");
  newtree->Branch("PUweight_Dn", &PUweight_Dn,"PUweight_Dn/D");

  newtree->Branch("trgSF",    &trgSF,   "trgSF/D");
  newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/D");
  newtree->Branch("trgSF_Dn", &trgSF_Dn,"trgSF_Dn/D");

  newtree->Branch("recoSF",    &recoSF,   "recoSF/D");
  newtree->Branch("recoSF_Up", &recoSF_Up,"recoSF_Up/D");
  newtree->Branch("recoSF_Dn", &recoSF_Dn,"recoSF_Dn/D");

  newtree->Branch("IdSF",    &IdSF,   "IdSF/D");
  newtree->Branch("IdSF_Up", &IdSF_Up,"IdSF_Up/D");
  newtree->Branch("IdSF_Dn", &IdSF_Dn,"IdSF_Dn/D");

  newtree->Branch("IsoSF",    &IsoSF,   "IsoSF/D");
  newtree->Branch("IsoSF_Up", &IsoSF_Up,"IsoSF_Up/D");
  newtree->Branch("IsoSF_Dn", &IsoSF_Dn,"IsoSF_Dn/D");

  newtree->Branch("ZPtCor", &ZPtCor,"ZPtCor/D");

  // Kinematic Variables
  //
  newtree->Branch("diLep_Ch", &diLep_Ch,"diLep_Ch/I");
  newtree->Branch("diLep_m", &diLep_m,"diLep_m/D");
  newtree->Branch("diLep_pt", &diLep_pt,"diLep_pt/D");
  newtree->Branch("diLep_eta", &diLep_eta,"diLep_eta/D");

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
      "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
      "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
      "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
    };
      //"HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v", need to evaluate the trig effi 
      //"HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
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

  newtree->SetBranchAddress("IsMuMu",   &IsMuMu);
  newtree->SetBranchAddress("IsElEl",   &IsElEl);

  newtree->SetBranchAddress("PUweight",   &PUweight);
  newtree->SetBranchAddress("PUweight_Up",&PUweight_Up);
  newtree->SetBranchAddress("PUweight_Dn",&PUweight_Dn);

  newtree->SetBranchAddress("trgSF",   &trgSF);
  newtree->SetBranchAddress("trgSF_Up",&trgSF_Up);
  newtree->SetBranchAddress("trgSF_Dn",&trgSF_Dn);

  newtree->SetBranchAddress("recoSF",   &recoSF);
  newtree->SetBranchAddress("recoSF_Up",&recoSF_Up);
  newtree->SetBranchAddress("recoSF_Dn",&recoSF_Dn);

  newtree->SetBranchAddress("IdSF",   &IdSF);
  newtree->SetBranchAddress("IdSF_Up",&IdSF_Up);
  newtree->SetBranchAddress("IdSF_Dn",&IdSF_Dn);

  newtree->SetBranchAddress("IsoSF",   &IsoSF);
  newtree->SetBranchAddress("IsoSF_Up",&IsoSF_Up);
  newtree->SetBranchAddress("IsoSF_Dn",&IsoSF_Dn);

  newtree->SetBranchAddress("ZPtCor",&ZPtCor);
  newtree->SetBranchAddress("diLep_Ch",&diLep_Ch);
  newtree->SetBranchAddress("diLep_m",&diLep_m);
  newtree->SetBranchAddress("diLep_pt",&diLep_pt);
  newtree->SetBranchAddress("diLep_eta",&diLep_eta);

  FillHist("CutFlow",5,1,30,0,30);
  // Filters ====================
  //if( HasFlag("MetFilt"))if(!PassMETFilter()) return;
  FillHist("CutFlow",6,1,30,0,30);


  muons=GetMuons("POGTightWithTightIso",7.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  electrons=GetElectrons("passMediumID",9.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

  IsMuMu = 0;
  IsElEl = 0;
  //=========================
  // DiLepton condition
  //=========================
  if(muons.size() == 2   )if(electrons.size() == 0) IsMuMu = 1;
  if(muons.size() == 0   )if(electrons.size() == 2) IsElEl = 1;
  if(IsMuMu != 1 && IsElEl != 1) return;
  if(HasFlag("MuMu") )if(IsMuMu !=1 ) return;
  if(HasFlag("ElEl") )if(IsElEl !=1 ) return;

  //=======================================
  // Channel dependent cut and ftn set
  //=======================================
    
  LeptonID_SF  = NULL;
  LeptonISO_SF = NULL;
  LeptonReco_SF= NULL;
  PileUpWeight = NULL;

  if(IsMuMu == 1){ // Muon-----------------------------
    if(! evt->PassTrigger(DiMuTrgs) )return;
    leps=MakeLeptonPointerVector(muons);
    Lep0PtCut=20.;
    Lep1PtCut=10.;
    LepEtaCut = 2.4;
    LeptonID_SF =&MCCorrection::MuonID_SF;
    LeptonISO_SF=&MCCorrection::MuonISO_SF;
    // key for private or official SF
    LeptonID_key="NUM_TightID_DEN_genTracks";
    LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";
    trgSF_key0="Lead17_POGTight";  // For 2016 separated period BCDEF, GH 
    trgSF_key1="Tail8_POGTight"; 
  } //---------------------------------------------
  if(IsElEl == 1){ // Electron =======================
    if(! evt->PassTrigger(DiElTrgs) )return;
    leps=MakeLeptonPointerVector(electrons);
    Lep0PtCut=25.;
    Lep1PtCut=15.;
    LepEtaCut = 2.5;
    LeptonID_SF  = &MCCorrection::ElectronID_SF;
    LeptonReco_SF= &MCCorrection::ElectronReco_SF;
    // key for private or official SF
    LeptonID_key    = "MediumID_pt10";
    LeptonID_key_POG= "passMediumID";
    trgSF_key0="LeadEle23_MediumID";
    trgSF_key1="TailEle12_MediumID";
  } //===========================================

  // ================================
  // Kinematic cuts 
  // ================================
  for(int i(0); i < 2; i++){ // two lepton only, pt eta the same to TnP
    if(leps[i]->LeptonFlavour()==Lepton::MUON){
     Aod_pt[i]=((Muon*)leps.at(i))->MiniAODPt();
     Aod_eta[i]=leps.at(i)->Eta();
    }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
     Aod_pt[i]=leps.at(i)->Pt();
     Aod_eta[i]=((Electron*)leps.at(i))->scEta();
     // TODO do we need this gap veto? it is already in Electron.h for id pass ftn
     if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
    }
  }
  if(Aod_pt[0] < Lep0PtCut) return;
  if(Aod_pt[1] < Lep1PtCut) return;
  if(fabs(Aod_eta[0]) > LepEtaCut) return;
  if(fabs(Aod_eta[1]) > LepEtaCut) return;
    
  //==============================
  // Kinematic Variables 
  //==============================

  diLep_Ch = DiLepCh::NA;

  diLep_m  = DEFAULT;
  diLep_pt  = DEFAULT;
  diLep_eta  = DEFAULT;

  if(leps.size() > 1){
    if(leps[0]->LeptonFlavour() == Lepton::MUON)if(leps[1]->LeptonFlavour() == Lepton::MUON){
      if(leps[0]->Charge() == 1) if(leps[1]->Charge() == 1) diLep_Ch = DiLepCh::MuMuPP;
      if(leps[0]->Charge() == -1)if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::MuMuMM;
      if(leps[0]->Charge() == 1) if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::MuMuOS;
      if(leps[0]->Charge() == -1)if(leps[1]->Charge() ==  1)diLep_Ch = DiLepCh::MuMuOS;
    }
    if(leps[0]->LeptonFlavour() == Lepton::ELECTRON)if(leps[1]->LeptonFlavour() == Lepton::ELECTRON){
      if(leps[0]->Charge() == 1) if(leps[1]->Charge() == 1) diLep_Ch = DiLepCh::ElElPP;
      if(leps[0]->Charge() == -1)if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::ElElMM;
      if(leps[0]->Charge() == 1) if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::ElElOS;
      if(leps[0]->Charge() == -1)if(leps[1]->Charge() ==  1)diLep_Ch = DiLepCh::ElElOS;
    }
    diLep    = *leps.at(0) + *leps.at(1);
    diLep_pt = diLep.Pt();
    diLep_eta = diLep.Eta();
    diLep_m  = diLep.M();
  }

  /////////////////PUreweight///////////////////
  PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

  PUweight=1.,PUweight_Up=1.,PUweight_Dn=1.;

  if(!IsDATA){
    PUweight=(mcCorr->*PileUpWeight)(nPileUp,0);
    PUweight_Up=(mcCorr->*PileUpWeight)(nPileUp,1);
    PUweight_Dn=(mcCorr->*PileUpWeight)(nPileUp,-1);
  }
  //==============================
  // SF 
  //==============================


  trgSF    = 1;
  trgSF_Up = 1;
  trgSF_Dn = 1;

  recoSF    = 1;
  recoSF_Up = 1;
  recoSF_Dn = 1;

  IdSF    = 1;
  IdSF_Up = 1;
  IdSF_Dn = 1;

  IsoSF =1;
  IsoSF_Up =1;
  IsoSF_Dn =1;


  if(!IsDATA){
    for( int i(0); i<2 ; i++){
      recoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i],Aod_pt[i],0):1.;
      recoSF_Up *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i],Aod_pt[i],1):1.;
      recoSF_Dn *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i],Aod_pt[i],-1):1.;

      IdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],0):1.;
      IdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],1):1.;
      IdSF_Dn   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],-1):1.;

      IsoSF	*= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],0):1.;
      IsoSF_Up	*= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],1):1.;
      IsoSF_Dn	*= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],-1):1.;

    }
    //cout<<"Skim pt0: "<<leps[0]->Pt()<<endl;
    trgSF      = mcCorr->DiLeptonTrg_SF(trgSF_key0,trgSF_key1,leps,0);
    trgSF_Up   = mcCorr->DiLeptonTrg_SF(trgSF_key0,trgSF_key1,leps,1);
    trgSF_Dn   = mcCorr->DiLeptonTrg_SF(trgSF_key0,trgSF_key1,leps,-1);
  }

  //===============================
  // Gen Info
  // status code: http://home.thep.lu.se/~torbjorn/pythia81html/ParticleProperties.html
  // genParticles status code: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATMCMatchingExercise 
  //===============================

  ZPtCor = 1;
  if(MCSample.Contains("DYJets") || MCSample.Contains("DYJets10to50_MG")){
    Gen genL0, genL1, genFsr, genHardL0, genHardL1;
    vector<Gen> gens = GetGens();
    // Check tau process
    for( int i(0); i<(int) gens.size(); i++){
      if( !gens.at(i).isPrompt()) continue; // not from hadron, muon, or tau
      if( gens.at(i).isHardProcess()){ // from ME
	if( genHardL0.IsEmpty() && (abs(gens.at(i).PID() ) == 11 || abs(gens.at(i).PID())==13||abs(gens.at(i).PID())==15)){
	  genHardL0 = gens.at(i);
        }else if(!genHardL0.IsEmpty() && gens.at(i).PID() == -genHardL0.PID()){
	  genHardL1 = gens.at(i);
	  if(abs( genHardL1.PID()) == 15){
	    //prefix = "tau_";
	    break;
	  }
        }
      }
      if(gens.at(i).Status() == 1){ // entering detector
        if(genL0.IsEmpty() && (abs(gens.at(i).PID())==11 || abs(gens.at(i).PID())==13) ) genL0=gens.at(i);
        else if( !genL0.IsEmpty() && gens.at(i).PID() == -genL0.PID()){
          genL1=gens.at(i);
        }
        else if(gens.at(i).PID()==22){
          genFsr+=gens.at(i); // need track mother, check also fromHardProcessBeforeFSR which is before QCD or QED FSR
        }
      }
    }

    if( abs(genHardL0.PID()) != 15 )if( (IsElEl && (genL1.PID() == 11)) || (IsMuMu && (genL1.PID() == 13)) ){
      genZ = genL0 + genL1 + genFsr;
      ZPtCor = mcCorr->GetZPtWeight(genZ.Pt(),genZ.Rapidity(),abs(genHardL0.PID())==13 ? Lepton::Flavour::MUON : Lepton::Flavour::ELECTRON);
    }
  }


  //baseW = weight_norm_1invpb*ev->MCweight()*ev->GetTriggerLumi("Full");

  // b tag test
  //

  //==== Test btagging code
  //==== add taggers and WP that you want to use in analysis
  std::vector<Jet::Tagger> vtaggers;
  vtaggers.push_back(Jet::DeepCSV);

  std::vector<Jet::WP> v_wps;
  v_wps.push_back(Jet::Medium); 

  //=== list of taggers, WP, setup systematics, use period SFs
  SetupBTagger(vtaggers,v_wps, true, true);

  vector<Jet> this_AllJets = GetAllJets();
  vector<Jet> jets = SelectJets(this_AllJets, "tight", 30., 2.4);

  int n_bjet_deepcsv_m=0;
  int n_bjet_deepcsv_m_noSF=0;

  for(unsigned int ij = 0 ; ij < jets.size(); ij++){
    if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,true,0)) n_bjet_deepcsv_m++; // method for getting btag with SF applied to MC
    if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,false,0)) n_bjet_deepcsv_m_noSF++; // method for getting btag with no SF applied to MC
  }

  //
  //for(int i=0;i<(int)PDFWeights_Scale->size();i++){
  //  cout<<"Scale: "<<i<<" "<<PDFWeights_Scale->at(i)<<endl;
  //}

  //b_trgSF->Fill();
  //b_trgSF_Up->Fill();
  //b_trgSF_Dn->Fill();
  newtree->Fill();


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

