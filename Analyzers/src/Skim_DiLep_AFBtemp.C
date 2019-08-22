#include "Skim_DiLep_AFBtemp.h"

void Skim_DiLep_AFBtemp::initializeAnalyzer(){

  //initializeAnalyzerTools(); //To use SF, executed by root macro

  //=================================
  // Skim Types
  //=================================

  TString data_prescale = getenv("SKFlat_WD");
  data_prescale += "/data/Run2Legacy_v3/2016/TrigPreScale/triggerData2016"; 
  //psProv.setPrescaleProvider("/home/jhkim/MultiUniv/data/Run2Legacy_v3/2016/TrigPreScale/triggerData2016");   
  psProv.setPrescaleProvider(data_prescale.Data());   

  if( HasFlag("MuMu")){
    cout<<"[Skim_DiLep_AFBtemp::initializeAnalyzer] MuMu Selection"<<endl;
  }
  else if( HasFlag("ElEl")){
    cout<<"[Skim_DiLep_AFBtemp::initializeAnalyzer] ElEl Selection"<<endl;
  }
  else if( HasFlag("MuMuOrElEl")){
    cout<<"[Skim_DiLep_AFBtemp::initializeAnalyzer] MuMu or ElEl Selection"<<endl;
  }
  else{
    cout <<"[Skim_DiLep_AFBtemp::executeEvent] Not ready for this Flags ";
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
  newtree->Branch("IsMuMu", &IsMuMu,"IsMuMu/I"); // JH : What's the meaning of each arguments?
  newtree->Branch("IsElEl", &IsElEl,"IsElel/I");
  newtree->Branch("passIso", &passIso,"passIso/I");
  newtree->Branch("passAntiIso", &passAntiIso,"passAntiIso/I");
  newtree->Branch("passAntiIso_Up", &passAntiIso_Up,"passAntiIso_Up/I");
  newtree->Branch("passAntiIso_Do", &passAntiIso_Do,"passAntiIso_Do/I");

  newtree->Branch("PUweight", &PUweight,"PUweight/D");
  newtree->Branch("PUweight_Up", &PUweight_Up,"PUweight_Up/D");
  newtree->Branch("PUweight_Do", &PUweight_Do,"PUweight_Do/D");

  newtree->Branch("trgSF",    &trgSF,   "trgSF/D");
  newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/D");
  newtree->Branch("trgSF_Do", &trgSF_Do,"trgSF_Do/D");
  newtree->Branch("trgSF_Q",    &trgSF_Q,   "trgSF_Q/D");
  newtree->Branch("trgSF_Q_Up", &trgSF_Q_Up,"trgSF_Q_Up/D");
  newtree->Branch("trgSF_Q_Do", &trgSF_Q_Do,"trgSF_Q_Do/D");

  newtree->Branch("recoSF",    &recoSF,   "recoSF/D");
  newtree->Branch("recoSF_Up", &recoSF_Up,"recoSF_Up/D");
  newtree->Branch("recoSF_Do", &recoSF_Do,"recoSF_Do/D");

  newtree->Branch("IdSF",    &IdSF,   "IdSF/D");
  newtree->Branch("IdSF_Up", &IdSF_Up,"IdSF_Up/D");
  newtree->Branch("IdSF_Do", &IdSF_Do,"IdSF_Do/D");

  newtree->Branch("IdSF_Q",    &IdSF_Q,   "IdSF_Q/D");
  newtree->Branch("IdSF_Q_Up", &IdSF_Q_Up,"IdSF_Q_Up/D");
  newtree->Branch("IdSF_Q_Do", &IdSF_Q_Do,"IdSF_Q_Do/D");

  newtree->Branch("IsoSF",    &IsoSF,   "IsoSF/D");
  newtree->Branch("IsoSF_Up", &IsoSF_Up,"IsoSF_Up/D");
  newtree->Branch("IsoSF_Do", &IsoSF_Do,"IsoSF_Do/D");

  newtree->Branch("pdf_scale_Up", &pdf_scale_Up,"pdf_scale_Up/D");
  newtree->Branch("pdf_scale_Do", &pdf_scale_Do,"pdf_scale_Do/D");


  newtree->Branch("ZPtCor", &ZPtCor,"ZPtCor/D");

  // Kinematic Variables
  //
  newtree->Branch("diLep_Ch", &diLep_Ch,"diLep_Ch/I");
  newtree->Branch("diLep_passSelectiveQ", &diLep_passSelectiveQ,"diLep_passSelectiveQ/O");
  newtree->Branch("diLep_m", &diLep_m,"diLep_m/D");
  newtree->Branch("diLep_pt", &diLep_pt,"diLep_pt/D");
  newtree->Branch("diLep_eta", &diLep_eta,"diLep_eta/D");
  newtree->Branch("leading_pt", &leading_pt,"leading_pt/D");
  newtree->Branch("subleading_pt", &subleading_pt,"subleading_pt/D");
  newtree->Branch("leading_eta", &leading_eta,"leading_eta/D");
  newtree->Branch("subleading_eta", &subleading_eta,"subleading_eta/D");
  newtree->Branch("num_veto_mu", &num_veto_mu,"num_veto_mu/I");

  // clear vector residual
  DiMuTrgs.clear();
  DiElTrgs.clear();


  cout << "[Skim_DiLep_AFBtemp::initializeAnalyzer] Skim List====================== " << endl;
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
  else if(DataYear==2018){
    DiMuTrgs = {
      "HLT_IsoMu24_v",
    };
  }
  else{
    cout<<"[Skim_DiLep_AFBtemp::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
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

void Skim_DiLep_AFBtemp::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  diLep_passSelectiveQ = false;

  evt = new Event;
  *evt = GetEvent();

  newtree->SetBranchAddress("IsMuMu",   &IsMuMu);
  newtree->SetBranchAddress("IsElEl",   &IsElEl);
  newtree->SetBranchAddress("passIso",   &passIso);
  newtree->SetBranchAddress("passAntiIso",   &passAntiIso);
  newtree->SetBranchAddress("passAntiIso_Up",   &passAntiIso_Up);
  newtree->SetBranchAddress("passAntiIso_Do",   &passAntiIso_Do);

  newtree->SetBranchAddress("PUweight",   &PUweight);
  newtree->SetBranchAddress("PUweight_Up",&PUweight_Up);
  newtree->SetBranchAddress("PUweight_Do",&PUweight_Do);

  newtree->SetBranchAddress("trgSF_Q",   &trgSF_Q);
  newtree->SetBranchAddress("trgSF_Q_Up",&trgSF_Q_Up);
  newtree->SetBranchAddress("trgSF_Q_Do",&trgSF_Q_Do);

  newtree->SetBranchAddress("recoSF",   &recoSF);
  newtree->SetBranchAddress("recoSF_Up",&recoSF_Up);
  newtree->SetBranchAddress("recoSF_Do",&recoSF_Do);

  newtree->SetBranchAddress("IdSF",   &IdSF);
  newtree->SetBranchAddress("IdSF_Up",&IdSF_Up);
  newtree->SetBranchAddress("IdSF_Do",&IdSF_Do);

  newtree->SetBranchAddress("IdSF_Q",   &IdSF_Q);
  newtree->SetBranchAddress("IdSF_Q_Up",&IdSF_Q_Up);
  newtree->SetBranchAddress("IdSF_Q_Do",&IdSF_Q_Do);

  newtree->SetBranchAddress("IsoSF",   &IsoSF);
  newtree->SetBranchAddress("IsoSF_Up",&IsoSF_Up);
  newtree->SetBranchAddress("IsoSF_Do",&IsoSF_Do);

  newtree->SetBranchAddress("pdf_scale_Up",&pdf_scale_Up);
  newtree->SetBranchAddress("pdf_scale_Do",&pdf_scale_Do);

  newtree->SetBranchAddress("diLep_Ch",&diLep_Ch);
  newtree->SetBranchAddress("diLep_passSelectiveQ",&diLep_passSelectiveQ);
  newtree->SetBranchAddress("diLep_m",&diLep_m);
  newtree->SetBranchAddress("diLep_pt",&diLep_pt);
  newtree->SetBranchAddress("diLep_eta",&diLep_eta);
  newtree->SetBranchAddress("leading_pt",&leading_pt);
  newtree->SetBranchAddress("subleading_pt",&subleading_pt);
  newtree->SetBranchAddress("leading_eta",&leading_eta);
  newtree->SetBranchAddress("subleading_eta",&subleading_eta);
  newtree->SetBranchAddress("num_veto_mu",&num_veto_mu);

  FillHist("CutFlow",5,1,30,0,30);
  // Filters ====================
  //if( HasFlag("MetFilt"))if(!PassMETFilter()) return;

  muons=GetMuons("POGMediumWithLooseTrkIso",10.,2.4); //without isolation cut
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h, no RC
  electrons=GetElectrons("passMediumID",9.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

  IsMuMu = 0;
  IsElEl = 0;

  //=========================
  // DiLepton condition
  //=========================
  if(muons.size() == 2  && electrons.size() == 0){
    IsMuMu = 1;
  }
  if(muons.size() == 0 && electrons.size() == 2){
    IsElEl = 1;
  }
  if(IsMuMu != 1 && IsElEl != 1) return;
  if(HasFlag("MuMu") )if(IsMuMu !=1 ) return;
  if(HasFlag("ElEl") )if(IsElEl !=1 ) return;

  FillHist("CutFlow",6,1,30,0,30);
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
    if(DataYear==2016) LeptonID_SF =&MCCorrection::MuonIDISO_RD_SF;
    else LeptonID_SF =&MCCorrection::MuonIDISO_SF;

    // key for private or official SF
    LeptonID_QPlus_key="MediumID_trkIso_QPlus";
    LeptonID_QMinu_key="MediumID_trkIso_QMinus";

    trgSF_QPlus_key0="LeadMu17_MediumID_trkIso_QPlus";  // For 2016 separated period BCDEF, GH 
    trgSF_QMinu_key0="LeadMu17_MediumID_trkIso_QMinus";  // For 2016 separated period BCDEF, GH 

    trgSF_key1="Tail8_POGTight"; 
    trgSF_QPlus_key1="TailMu8_MediumID_trkIso_QPlus"; 
    trgSF_QMinu_key1="TailMu8_MediumID_trkIso_QMinus"; 

  } //---------------------------------------------
  if(IsElEl == 1){ // Electron =======================
    //if(! evt->PassTrigger(DiElTrgs) )return;

    //if( evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") == 0 && evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") == 1){
    //    cout << "DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") << endl;
    //    cout << "non DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") << endl;
    //    //std::cout <<"l1 ps "<<psProv.l1Prescale("L1_SingleEG26",run,lumi)<<std::endl;
    //    std::cout <<"hlt ps "<<psProv.hltPrescale("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",run,lumi)<<std::endl;
    //}

    if( evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") == 1 && evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") == 0){
        //cout << "DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") << endl;
        //cout << "non DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") << endl;
        //std::cout <<"l1 ps "<<psProv.l1Prescale("L1_SingleEG26",run,lumi)<<std::endl;
        //std::cout <<"hlt ps "<<psProv.hltPrescale("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",run,lumi)<<std::endl;
    }

    //if(electrons[0].SelectiveQ() )if(electrons[1].SelectiveQ())  diLep_passSelectiveQ = true;
    //leps=MakeLeptonPointerVector(electrons);
    //Lep0PtCut=25.;
    //Lep1PtCut=15.;
    //LepEtaCut = 2.5;
    //LeptonID_SF  = &MCCorrection::ElectronID_SF;
    //LeptonReco_SF= &MCCorrection::ElectronReco_SF;
    //// key for private or official SF
    //LeptonID_key_POG= "passMediumID";
    //LeptonID_key    = "MediumID_pt10";
    //LeptonID_QPlus_key    = "Selective_MediumID_QPlus_pt10"; // currently only selective charge dependent SFs exist for 2016
    //LeptonID_QMinu_key    = "Selective_MediumID_QMinus_pt10";

    //trgSF_QPlus_key0="Selective_LeadEle23_MediumID_QPlus";
    //trgSF_QMinu_key0="Selective_LeadEle23_MediumID_QMinus";

    //trgSF_key1="TailEle12_MediumID";
    //trgSF_QPlus_key1="Selective_TailEle12_MediumID_QPlus";
    //trgSF_QMinu_key1="Selective_TailEle12_MediumID_QMinus";


  } //===========================================
  FillHist("CutFlow",7,1,30,0,30);

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
  FillHist("CutFlow",8,1,30,0,30);
  if(Aod_pt[0] < Lep0PtCut) return;
  if(Aod_pt[1] < Lep1PtCut) return;
  if(fabs(Aod_eta[0]) > LepEtaCut) return;
  if(fabs(Aod_eta[1]) > LepEtaCut) return;
    
  FillHist("CutFlow",9,1,30,0,30);
  //==============================
  // Kinematic Variables 
  //==============================

  diLep_Ch = DiLepCh::NA;

  diLep_m  = DEFAULT;
  diLep_pt  = DEFAULT;
  diLep_eta  = DEFAULT;
  leading_pt = DEFAULT;
  subleading_pt = DEFAULT;
  leading_eta = DEFAULT;
  subleading_eta = DEFAULT;

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
    leading_pt = (*leps.at(0)).Pt();
    subleading_pt = (*leps.at(1)).Pt();
    leading_eta = (*leps.at(0)).Eta();
    subleading_eta = (*leps.at(1)).Eta();
    diLep_m  = diLep.M();
  }

  /////////////////PUreweight///////////////////
  if(DataYear!=2018)
    PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;
  else 
    PileUpWeight = NULL; // FIXME update pileup for 2018

  PUweight=1.,PUweight_Up=1.,PUweight_Do=1.;

  if(!IsDATA){
    if(PileUpWeight!=NULL){
        PUweight=(mcCorr->*PileUpWeight)(nPileUp,0);
        PUweight_Up=(mcCorr->*PileUpWeight)(nPileUp,1);
        PUweight_Do=(mcCorr->*PileUpWeight)(nPileUp,-1);
    }
    else{
        PUweight= 1.;
        PUweight_Up= 1.;
        PUweight_Do= 1.;
    }
  }

  //==============================
  // SF 
  //==============================

  trgSF    = 1; trgSF_Up   = 1; trgSF_Do   = 1;
  trgSF_Q  = 1; trgSF_Q_Up = 1; trgSF_Q_Do = 1;

  recoSF   = 1; recoSF_Up  = 1; recoSF_Do = 1;

  IdSF    = 1; IdSF_Up   = 1; IdSF_Do   = 1;
  IdSF_Q  = 1; IdSF_Q_Up = 1; IdSF_Q_Do = 1;

  IsoSF =1; IsoSF_Up =1; IsoSF_Do =1;
  
  pdf_scale_Up = 1; pdf_scale_Do = 1;

  if(!IsDATA){
    for( int i(0); i<2 ; i++){

      if(leps[i]->Charge() == 1){
        IdSF_Q      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_QPlus_key, Aod_eta[i], Aod_pt[i],  0) : 1.;
        IdSF_Q_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_QPlus_key, Aod_eta[i], Aod_pt[i],  1) : 1.;
        IdSF_Q_Do   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_QPlus_key, Aod_eta[i], Aod_pt[i], -1) : 1.;
      }
      else if(leps[i]->Charge() == -1){
        IdSF_Q      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_QMinu_key, Aod_eta[i], Aod_pt[i],  0) : 1.;
        IdSF_Q_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_QMinu_key, Aod_eta[i], Aod_pt[i],  1) : 1.;
        IdSF_Q_Do   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_QMinu_key, Aod_eta[i], Aod_pt[i], -1) : 1.;
      }else{
        cout<<"Skim_DiLep_AFBtemp: leps charage strange: "<<leps[i]->Charge()<<endl;
        exit(EXIT_FAILURE);
      }
    }

    if( leps[0]->Charge() == 1 && leps[1]->Charge() == 1  ){
      trgSF_Q      = mcCorr->DiLeptonTrg_SF(trgSF_QPlus_key0, trgSF_QPlus_key1, leps,  0);
      trgSF_Q_Up   = mcCorr->DiLeptonTrg_SF(trgSF_QPlus_key0, trgSF_QPlus_key1, leps,  1);
      trgSF_Q_Do   = mcCorr->DiLeptonTrg_SF(trgSF_QPlus_key0, trgSF_QPlus_key1, leps, -1);
    }
    else if( leps[0]->Charge() == 1 && leps[1]->Charge() == -1 ){
      trgSF_Q      = mcCorr->DiLeptonTrg_SF(trgSF_QPlus_key0, trgSF_QMinu_key1, leps,  0);
      trgSF_Q_Up   = mcCorr->DiLeptonTrg_SF(trgSF_QPlus_key0, trgSF_QMinu_key1, leps,  1);
      trgSF_Q_Do   = mcCorr->DiLeptonTrg_SF(trgSF_QPlus_key0, trgSF_QMinu_key1, leps, -1);
    }
    else if( leps[0]->Charge() == -1 && leps[1]->Charge() == 1 ){
      trgSF_Q      = mcCorr->DiLeptonTrg_SF(trgSF_QMinu_key0, trgSF_QPlus_key1, leps,  0);
      trgSF_Q_Up   = mcCorr->DiLeptonTrg_SF(trgSF_QMinu_key0, trgSF_QPlus_key1, leps,  1);
      trgSF_Q_Do   = mcCorr->DiLeptonTrg_SF(trgSF_QMinu_key0, trgSF_QPlus_key1, leps, -1);
    }
    else if( leps[0]->Charge() == -1 && leps[1]->Charge() == -1 ){
      trgSF_Q      = mcCorr->DiLeptonTrg_SF(trgSF_QMinu_key0, trgSF_QMinu_key1, leps,  0);
      trgSF_Q_Up   = mcCorr->DiLeptonTrg_SF(trgSF_QMinu_key0, trgSF_QMinu_key1, leps,  1);
      trgSF_Q_Do   = mcCorr->DiLeptonTrg_SF(trgSF_QMinu_key0, trgSF_QMinu_key1, leps, -1);
    }else {
      cout<<"Skim_DiLep_AFBtemp: two charge combination is strange."<<endl;
      exit(EXIT_FAILURE);
    }
  }

  newtree->Fill();
    
  delete evt;
}



void Skim_DiLep_AFBtemp::executeEventFromParameter(AnalyzerParameter param){

}

Skim_DiLep_AFBtemp::Skim_DiLep_AFBtemp(){

}

Skim_DiLep_AFBtemp::~Skim_DiLep_AFBtemp(){

}

void Skim_DiLep_AFBtemp::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_DiLep_AFBtemp::initializeAnalyzer
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

