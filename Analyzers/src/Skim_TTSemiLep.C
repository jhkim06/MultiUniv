#include "Skim_TTSemiLep.h"

void Skim_TTSemiLep::initializeAnalyzer(){

  //initializeAnalyzerTools(); //defined at AnalyzerCor and executed at the run script 

  //=================================
  // Skim Types
  //=================================
   

  if( HasFlag("TTSemiLep")){
    cout<<"[Skim_TTSemiLep::initializeAnalyzer] TTSemiLepMu Selection"<<endl;
  }

  /*
  else if( HasFlag("MuOrEl")){
    cout<<"[Skim_TTSemiLep::initializeAnalyzer] Mu or El Selection"<<endl;
  }
  */
  else{
    cout <<"[Skim_TTSemiLep::executeEvent] Not ready for this Flags ";
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

  //XXX: Do I need ZPtCor?
  newtree->Branch("ZPtCor", &ZPtCor,"ZPtCor/D");

  // Kinematic Variables
  //TODO: will add something?
  /*
  newtree->Branch("diLep_Ch", &diLep_Ch,"diLep_Ch/I");
  newtree->Branch("diLep_passSelectiveQ", &diLep_passSelectiveQ,"diLep_passSelectiveQ/O");
  newtree->Branch("diLep_m", &diLep_m,"diLep_m/D");
  newtree->Branch("diLep_pt", &diLep_pt,"diLep_pt/D");
  newtree->Branch("diLep_eta", &diLep_eta,"diLep_eta/D");
  */
  //b_trgSF = newtree->Branch("trgSF", &trgSF,"trgSF/F");
  //b_trgSF_Up = newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/F");
  //b_trgSF_Do = newtree->Branch("trgSF_Do", &trgSF_Do,"trgSF_Do/F");
  /*
  newtree->Branch("initial_dijet_m", &initial_dijet_m,"initial_dijet_m/D");
  newtree->Branch("fitted_dijet_m", &fitted_dijet_m,"fitted_dijet_m/D");
  newtree->Branch("best_chi2", &best_chi2,"best_chi2/D");
  */
  newtree->Branch("btag_vector_noSF","vector<bool>",&btag_vector_noSF);
  newtree->Branch("n_bjet_deepcsv_m_noSF", &n_bjet_deepcsv_m_noSF,"n_bjet_deepcsv_m_noSF/I");
  newtree->Branch("BTagSF", &BTagSF,"BTagSF/D");
  newtree->Branch("BTagSF_Up", &BTagSF_Up,"BTagSF_Up/D");
  newtree->Branch("BTagSF_Do", &BTagSF_Do,"BTagSF_Do/D");
  newtree->Branch("MisTagSF", &MisTagSF,"MisTagSF/D");
  newtree->Branch("MisTagSF_Up", &MisTagSF_Up,"MisTagSF_Up/D");
  newtree->Branch("MisTagSF_Do", &MisTagSF_Do,"MisTagSF_Do/D");

  //newtree->Branch("TopPtReweight_Up", &TopPtReweight_Up,"TopPtReweight_Up/D");
  //newtree->Branch("TopPtReweight_Do", &TopPtReweight_Do,"TopPtReweight_Do/D");

  // clear vector residual
  SingleMuTrgs.clear();
  SingleElTrgs.clear();


  cout << "[Skim_TTSemiLep::initializeAnalyzer] Skim List====================== " << endl;
  if(DataYear==2016){
    SingleMuTrgs = {
      "HLT_IsoMu24_v"
    };
    SingleElTrgs = {
      "HLT_Ele27_WPTight_Gsf_v"
    };
  }
  else if(DataYear==2017){
    SingleMuTrgs = {
      "HLT_IsoMu27_v"
    };
    SingleElTrgs = {
      "HLT_Ele35_WPTight_Gsf_v"
    };
  }
  else{
    cout<<"[Skim_TTSemiLep::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
    exit(EXIT_FAILURE);
  }

  cout << "\t"<<"doubleTrgs to skim = " << endl;
  for(unsigned int i=0; i<SingleMuTrgs.size(); i++){
    cout << "\t" << SingleMuTrgs.at(i) << endl;
  }
  for(unsigned int i=0; i<SingleElTrgs.size(); i++){
    cout << "\t" << SingleElTrgs.at(i) << endl;
  }
  // setup btagger
  std::vector<Jet::Tagger> taggers = {Jet::DeepCSV};
  std::vector<Jet::WP> wps ={Jet::Medium};

  SetupBTagger(taggers, wps, true, true);

  //fitter_driver = new TKinFitterDriver(DataYear); 
}

void Skim_TTSemiLep::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();
  btag_vector_noSF.clear();
  vtaggers.clear();
  v_wps.clear();
  this_AllJets.clear();
  jets.clear();
  jetsLveto.clear();

  muons.shrink_to_fit();
  electrons.shrink_to_fit();
  leps.shrink_to_fit();
  btag_vector_noSF.shrink_to_fit();
  vtaggers.shrink_to_fit();
  v_wps.shrink_to_fit();
  this_AllJets.shrink_to_fit();
  jets.shrink_to_fit();
  jetsLveto.shrink_to_fit();

  tmp_btagsf=1., tmp_mistagsf=1.;
  n_bjet_deepcsv_m_noSF=0;
  IsMu = 0; IsEl = 0;
  PUweight=1.,PUweight_Up=1.,PUweight_Do=1.;
  trgSF    = 1; trgSF_Up   = 1; trgSF_Do   = 1;
  trgSF_Q  = 1; trgSF_Q_Up = 1; trgSF_Q_Do = 1;

  recoSF   = 1; recoSF_Up  = 1; recoSF_Do = 1;

  IdSF    = 1; IdSF_Up   = 1; IdSF_Do   = 1;
  IdSF_Q  = 1; IdSF_Q_Up = 1; IdSF_Q_Do = 1;

  IsoSF =1; IsoSF_Up =1; IsoSF_Do =1;
  
  pdf_scale_Up = 1; pdf_scale_Do = 1;
  

  //diLep_passSelectiveQ = false;

  evt = new Event;
  *evt = GetEvent();

  newtree->SetBranchAddress("IsMu",   &IsMu);
  newtree->SetBranchAddress("IsEl",   &IsEl);

  newtree->SetBranchAddress("passTightID",   &passTightID);
  newtree->SetBranchAddress("passIso",   &passIso);
  newtree->SetBranchAddress("passAntiIso",   &passAntiIso);
  newtree->SetBranchAddress("passAntiIso_Up",   &passAntiIso_Up);
  newtree->SetBranchAddress("passAntiIso_Do",   &passAntiIso_Do);

  newtree->SetBranchAddress("PUweight",   &PUweight);
  newtree->SetBranchAddress("PUweight_Up",&PUweight_Up);
  newtree->SetBranchAddress("PUweight_Do",&PUweight_Do);

  newtree->SetBranchAddress("trgSF",   &trgSF);
  newtree->SetBranchAddress("trgSF_Up",&trgSF_Up);
  newtree->SetBranchAddress("trgSF_Do",&trgSF_Do);

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

  newtree->SetBranchAddress("ZPtCor",&ZPtCor);
  //newtree->SetBranchAddress("diLep_Ch",&diLep_Ch);
  //newtree->SetBranchAddress("diLep_passSelectiveQ",&diLep_passSelectiveQ);
  //newtree->SetBranchAddress("diLep_m",&diLep_m);
  //newtree->SetBranchAddress("diLep_pt",&diLep_pt);
  //newtree->SetBranchAddress("diLep_eta",&diLep_eta);
  /*
  newtree->SetBranchAddress("initial_dijet_m",&initial_dijet_m);
  newtree->SetBranchAddress("fitted_dijet_m",&fitted_dijet_m);
  newtree->SetBranchAddress("best_chi2",&best_chi2);
  */
  newtree->SetBranchAddress("n_bjet_deepcsv_m_noSF",&n_bjet_deepcsv_m_noSF);
  newtree->SetBranchAddress("BTagSF", &BTagSF);
  newtree->SetBranchAddress("BTagSF_Up", &BTagSF_Up);
  newtree->SetBranchAddress("BTagSF_Do", &BTagSF_Do);
  newtree->SetBranchAddress("MisTagSF", &MisTagSF);
  newtree->SetBranchAddress("MisTagSF_Up", &MisTagSF_Up);
  newtree->SetBranchAddress("MisTagSF_Do", &MisTagSF_Do);

  //newtree->Branch("TopPtReweight_Up", &TopPtReweight_Up);
  //newtree->Branch("TopPtReweight_Do", &TopPtReweight_Do);

  FillHist("CutFlow",5,1,30,0,30);
  // Filters ====================
  //if( HasFlag("MetFilt"))if(!PassMETFilter()) return;

  //FIXME: fix lepton ID later
  muons=GetMuons("POGLooseWithLooseIso",15.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  electrons=GetElectrons("passVetoID",15.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

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
  //if(HasFlag("TTSemiLepMu") )if(IsMu !=1 ) return;
  //if(HasFlag("TTSemiLepEl") )if(IsEl !=1 ) return;
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
  FillHist("CutFlow",6,1,30,0,30);
  //=======================================
  // Channel dependent cut and ftn set
  //=======================================
    
  LeptonID_SF  = NULL;
  LeptonISO_SF = NULL;
  LeptonReco_SF= NULL;
  PileUpWeight = NULL;

  if(IsMu == 1){ // Muon-----------------------------
    if(! evt->PassTrigger(SingleMuTrgs) )return;
    leps=MakeLeptonPointerVector(muons);
    Lep0PtCut=29.; //FIXME: set by year
    LepEtaCut = 2.4;
    LeptonID_SF =&MCCorrection::MuonID_SF;
    LeptonISO_SF=&MCCorrection::MuonISO_SF;
    // key for private or official SF
    LeptonID_key="NUM_TightID_DEN_genTracks";
    LeptonID_QPlus_key="NUM_TightID_DEN_genTracks";
    LeptonID_QMinu_key="NUM_TightID_DEN_genTracks";

    LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";

    trgSF_key0="Lead17_POGTight";  // For 2016 separated period BCDEF, GH 
    trgSF_QPlus_key0="Lead17_POGTight";  // For 2016 separated period BCDEF, GH 
    trgSF_QMinu_key0="Lead17_POGTight";  // For 2016 separated period BCDEF, GH 

    trgSF_key1="Tail8_POGTight"; //FIXME: function for single lep trigger
    trgSF_QPlus_key1="Tail8_POGTight"; 
    trgSF_QMinu_key1="Tail8_POGTight"; 

  } //---------------------------------------------
  if(IsEl == 1){ // Electron =======================
    if(! evt->PassTrigger(SingleElTrgs) )return;
    //if(electrons[0].SelectiveQ() )if(electrons[1].SelectiveQ())  diLep_passSelectiveQ = true;
    leps=MakeLeptonPointerVector(electrons);
    Lep0PtCut=38.; //FIXME: set by year
    LepEtaCut = 2.5;
    LeptonID_SF  = &MCCorrection::ElectronID_SF;
    LeptonReco_SF= &MCCorrection::ElectronReco_SF;
    // key for private or official SF
    LeptonID_key_POG= "passMediumID"; //FIXME: H+ ->cb use Tight electron
    LeptonID_key    = "MediumID_pt10";
    LeptonID_QPlus_key    = "MediumID_QPlus_pt10";
    LeptonID_QMinu_key    = "MediumID_QMinus_pt10";

    trgSF_key0="LeadEle23_MediumID";
    trgSF_QPlus_key0="Selective_LeadEle23_MediumID_QPlus";
    trgSF_QMinu_key0="Selective_LeadEle23_MediumID_QMinus";

    trgSF_key1="TailEle12_MediumID";  //FIXME: function for single lepton trigger
    trgSF_QPlus_key1="Selective_TailEle12_MediumID_QPlus";
    trgSF_QMinu_key1="Selective_TailEle12_MediumID_QMinus";


  } //===========================================
  FillHist("CutFlow",7,1,30,0,30);

  // ================================
  // Kinematic cuts 
  // ================================
  for(int i(0); i < 1; i++){ // one lepton only, pt eta the same to TnP
    if(leps[i]->LeptonFlavour()==Lepton::MUON){
     Aod_pt[i]=((Muon*)leps.at(i))->MiniAODPt();
     Aod_eta[i]=leps.at(i)->Eta();
     //double haah = mcCorr->MuonTrigger_SF("POGTight","IsoMu27",muons,0);
     //haah = mcCorr->MuonTrigger_SF("POGTight","IsoMu27",muons,1);
     //haah = mcCorr->MuonTrigger_SF("POGTight","IsoMu27",muons,-1);
    }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
     Aod_pt[i]=leps.at(i)->Pt();
     Aod_eta[i]=((Electron*)leps.at(i))->scEta();
     // TODO do we need this gap veto? it is already in Electron.h for id pass ftn
     if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
    }
  }
  FillHist("CutFlow",8,1,30,0,30);
  if(Aod_pt[0] < Lep0PtCut) return;
  if(fabs(Aod_eta[0]) > LepEtaCut) return;
    
  FillHist("CutFlow",9,1,30,0,30);
  //==============================
  // Kinematic Variables 
  //==============================
  //TODO: add variables ??
  /////////////////PUreweight///////////////////
  PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

  if(!IsDATA){
    PUweight=(mcCorr->*PileUpWeight)(nPileUp,0);
    PUweight_Up=(mcCorr->*PileUpWeight)(nPileUp,1);
    PUweight_Do=(mcCorr->*PileUpWeight)(nPileUp,-1);
  }
  //==============================
  // SF 
  //==============================


  if(!IsDATA){
    for( int i(0); i<1 ; i++){

      recoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  0) : 1.;
      recoSF_Up *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  1) : 1.;
      recoSF_Do *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i], -1) : 1.;

      IdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i],  0) : 1.;
      IdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i],  1) : 1.;
      IdSF_Do   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i], -1) : 1.;

      IsoSF	*= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i],  0) : 1.;
      IsoSF_Up	*= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i],  1) : 1.;
      IsoSF_Do	*= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i], -1) : 1.;

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
	cout<<"Skim_TTSemiLep: leps charage strange: "<<leps[i]->Charge()<<endl;
        exit(EXIT_FAILURE);
      }
    }
    /*
    //FIXME: trgSF for SingleLep
    //cout<<"Skim pt0: "<<leps[0]->Pt()<<endl;
    trgSF      = mcCorr->DiLeptonTrg_SF(trgSF_key0, trgSF_key1, leps,  0);
    trgSF_Up   = mcCorr->DiLeptonTrg_SF(trgSF_key0, trgSF_key1, leps,  1);
    trgSF_Do   = mcCorr->DiLeptonTrg_SF(trgSF_key0, trgSF_key1, leps, -1);

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
      cout<<"Skim_TTSemiLep: two charge combination is strange."<<endl;
      exit(EXIT_FAILURE);
    }

    if(DataYear==2016 || DataYear == 2017 || DataYear == 2018){
      for( int i(0); i< (int) PDFWeights_Scale->size(); i++){
	if( i == 5 || i == 7 ) continue;

	doubleTmp = PDFWeights_Scale->at(i);
	//cout<<" scale "<<i<<" "<<PDFWeights_Scale->at(i)<<endl;
	if( doubleTmp > pdf_scale_Up) pdf_scale_Up = doubleTmp;
	if( doubleTmp < pdf_scale_Do) pdf_scale_Do = doubleTmp;
      }
      //cout<<"scale up and do: "<<pdf_scaleUp<<" "<<pdf_scaleDo<<endl;
    }
    */
  }
  //===============================
  // Gen Info
  // status code: http://home.thep.lu.se/~torbjorn/pythia81html/ParticleProperties.html
  // genParticles status code: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATMCMatchingExercise 
  //===============================
/*
  //XXX: Do I need this?
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

    if( abs(genHardL0.PID()) != 15 )if( (IsEl && (genL1.PID() == 11)) || (IsMu && (genL1.PID() == 13)) ){
      genZ = genL0 + genL1 + genFsr;
      ZPtCor = mcCorr->GetZPtWeight(genZ.Pt(),genZ.Rapidity(),abs(genHardL0.PID())==13 ? Lepton::Flavour::MUON : Lepton::Flavour::ELECTRON);
    }
  }


  //baseW = weight_norm_1invpb*ev->MCweight()*ev->GetTriggerLumi("Full");

  // b tag test
  //
*/
  //==== Test btagging code
  //==== add taggers and WP that you want to use in analysis
  vtaggers.push_back(Jet::DeepCSV);
  v_wps.push_back(Jet::Medium); 

  //=== list of taggers, WP, setup systematics, use period SFs
  SetupBTagger(vtaggers,v_wps, true, true);

  this_AllJets = GetAllJets();
  jets = SelectJets(this_AllJets, "tight", 30., 2.4);
  jetsLveto = JetsVetoLeptonInside(jets, electrons, muons);
  std::sort(jetsLveto.begin(), jetsLveto.end(), PtComparing);
  if(jetsLveto.size()<4) return;
  FillHist("CutFlow",10,1,30,0,30);


  for(unsigned int ij = 0 ; ij < jetsLveto.size(); ij++){
    if(IsBTagged(jetsLveto.at(ij), Jet::DeepCSV, Jet::Medium,false,0)){
      n_bjet_deepcsv_m_noSF++; // method for getting btag with no SF applied to MC
      btag_vector_noSF.push_back(true);
    }
    else{
      btag_vector_noSF.push_back(false);
    }
  }
  //require more than 2b tagged jetLvetos
  if(n_bjet_deepcsv_m_noSF < 2) return;
  FillHist("CutFlow",11,1,30,0,30);

  BtaggingSFEvtbyEvt(jetsLveto, Jet::DeepCSV, Jet::Medium, 0, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  BTagSF = tmp_btagsf;
  MisTagSF = tmp_mistagsf;
  BtaggingSFEvtbyEvt(jetsLveto, Jet::DeepCSV, Jet::Medium, 1, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  BTagSF_Up = tmp_btagsf;
  MisTagSF_Up = tmp_mistagsf;
  BtaggingSFEvtbyEvt(jetsLveto, Jet::DeepCSV, Jet::Medium, -1, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  BTagSF_Do = tmp_btagsf;
  MisTagSF_Do = tmp_mistagsf;
  //
  //for(int i=0;i<(int)PDFWeights_Scale->size();i++){
  //  cout<<"Scale: "<<i<<" "<<PDFWeights_Scale->at(i)<<endl;
  //}

  //b_trgSF->Fill();
  //b_trgSF_Up->Fill();
  //b_trgSF_Do->Fill();
  if(jetsLveto.size()!=btag_vector_noSF.size()){
    cout <<"[Skim_TTSemiLep::executeEvent] check jet vector size" << endl;
    exit(EXIT_FAILURE);
  }

  //std::vector<Gen> gens = GetGens();
  //TopPtReweight_Up = mcCorr->GetTopPtReweight(gens);
  //TopPtReweight_Do = 1.;
    ///////////////////////////////////////////////////////////
   // !!!!!!!!!!!!!!!!!! execute fitter !!!!!!!!!!!!!!!!!!! //
  ///////////////////////////////////////////////////////////
  /*
  if(IsMu){
    fitter_driver->SetAllObjects(jetsLveto, 
                                 btag_vector_noSF,
                                 (TLorentzVector)muons.at(0),
                                 (TLorentzVector)evt->GetMETVector()
                                );
  }
  else if(IsEl){
    fitter_driver->SetAllObjects(jetsLveto,
                                 btag_vector_noSF,
                                 (TLorentzVector)electrons.at(0),
                                 (TLorentzVector)evt->GetMETVector()
                                );
  }
  fitter_driver->FindBestChi2Fit(false);
  if(fitter_driver->GetStatus()!=0) return; //0 means fit converge
  FillHist("CutFlow",12,1,30,0,30);

  initial_dijet_m = fitter_driver->GetBestInitialDijetMass();
  fitted_dijet_m = fitter_driver->GetBestFittedDijetMass();
  best_chi2 = fitter_driver->GetChi2();
  */
  newtree->Fill();


}



void Skim_TTSemiLep::executeEventFromParameter(AnalyzerParameter param){

}

Skim_TTSemiLep::Skim_TTSemiLep(){

}

Skim_TTSemiLep::~Skim_TTSemiLep(){
 //delete fitter_driver;
}

void Skim_TTSemiLep::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_TTSemiLep::initializeAnalyzer
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

