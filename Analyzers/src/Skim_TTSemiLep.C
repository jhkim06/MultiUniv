#include "Skim_TTSemiLep.h"

void Skim_TTSemiLep::initializeAnalyzer(){

  //initializeAnalyzerTools(); //defined at AnalyzerCor and executed at the run script 

  //=================================
  // Skim Types
  //=================================
   

  if( HasFlag("TTSemiLep")){
    cout<<"[Skim_TTSemiLep::initializeAnalyzer] TTSemiLepMu Selection"<<endl;
  }
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
  TBranch* b_baseW =(TBranch*) newtree->GetListOfBranches()->FindObject("baseW");
  if(b_baseW) {
    //
  }
  else{
    newtree->Branch("baseW", &baseW,"baseW/D");
  }

  // New Branch
  newtree->Branch("IsMu", &IsMu,"IsMu/I"); // JH : What's the meaning of each arguments?
  newtree->Branch("IsEl", &IsEl,"IsEl/I");
  newtree->Branch("weight_Prefire", &weight_Prefire,"weight_Prefire/D");
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

  newtree->Branch("recoSF",    &recoSF,   "recoSF/D");
  newtree->Branch("recoSF_Up", &recoSF_Up,"recoSF_Up/D");
  newtree->Branch("recoSF_Do", &recoSF_Do,"recoSF_Do/D");

  newtree->Branch("IdSF",    &IdSF,   "IdSF/D");
  newtree->Branch("IdSF_Up", &IdSF_Up,"IdSF_Up/D");
  newtree->Branch("IdSF_Do", &IdSF_Do,"IdSF_Do/D");

  newtree->Branch("IsoSF",    &IsoSF,   "IsoSF/D");
  newtree->Branch("IsoSF_Up", &IsoSF_Up,"IsoSF_Up/D");
  newtree->Branch("IsoSF_Do", &IsoSF_Do,"IsoSF_Do/D");

  newtree->Branch("pdf_scale_Up", &pdf_scale_Up,"pdf_scale_Up/D");
  newtree->Branch("pdf_scale_Do", &pdf_scale_Do,"pdf_scale_Do/D");

  newtree->Branch("BTagSF", &BTagSF,"BTagSF/D");
  newtree->Branch("BTagSF_JES_Up", &BTagSF_JES_Up,"BTagSF_JES_Up/D");
  newtree->Branch("BTagSF_JES_Do", &BTagSF_JES_Do,"BTagSF_JES_Do/D");
  newtree->Branch("BTagSF_JER_Up", &BTagSF_JER_Up,"BTagSF_JER_Up/D");
  newtree->Branch("BTagSF_JER_Do", &BTagSF_JER_Do,"BTagSF_JER_Do/D");
  newtree->Branch("BTagSF_up_lfstats1", &BTagSF_up_lfstats1,"BTagSF_up_lfstats1/D");
  newtree->Branch("BTagSF_down_lfstats1", &BTagSF_down_lfstats1,"BTagSF_down_lfstats1/D");
  newtree->Branch("BTagSF_up_lfstats2", &BTagSF_up_lfstats2,"BTagSF_up_lfstats2/D");
  newtree->Branch("BTagSF_down_lfstats2", &BTagSF_down_lfstats2,"BTagSF_down_lfstats2/D");
  newtree->Branch("BTagSF_up_hf", &BTagSF_up_hf,"BTagSF_up_hf/D");
  newtree->Branch("BTagSF_down_hf", &BTagSF_down_hf,"BTagSF_down_hf/D");
  newtree->Branch("BTagSF_up_lf", &BTagSF_up_lf,"BTagSF_up_lf/D");
  newtree->Branch("BTagSF_down_lf", &BTagSF_down_lf,"BTagSF_down_lf/D");
  newtree->Branch("BTagSF_up_jes", &BTagSF_up_jes,"BTagSF_up_jes/D");
  newtree->Branch("BTagSF_down_jes", &BTagSF_down_jes,"BTagSF_down_jes/D");
  newtree->Branch("BTagSF_up_hfstats1", &BTagSF_up_hfstats1,"BTagSF_up_hfstats1/D");
  newtree->Branch("BTagSF_down_hfstats1", &BTagSF_down_hfstats1,"BTagSF_down_hfstats1/D");
  newtree->Branch("BTagSF_up_hfstats2", &BTagSF_up_hfstats2,"BTagSF_up_hfstats2/D");
  newtree->Branch("BTagSF_down_hfstats2", &BTagSF_down_hfstats2,"BTagSF_down_hfstats2/D");
  newtree->Branch("BTagSF_up_cferr1", &BTagSF_up_cferr1,"BTagSF_up_cferr1/D");
  newtree->Branch("BTagSF_down_cferr1", &BTagSF_down_cferr1,"BTagSF_down_cferr1/D");
  newtree->Branch("BTagSF_up_cferr2", &BTagSF_up_cferr2,"BTagSF_up_cferr2/D");
  newtree->Branch("BTagSF_down_cferr2", &BTagSF_down_cferr2,"BTagSF_down_cferr2/D");

  newtree->Branch("nhf5", &nhf5,"nhf5/I");
  newtree->Branch("nhf5_JES_Up", &nhf5_JES_Up,"nhf5_JES_Up/I");
  newtree->Branch("nhf5_JES_Do", &nhf5_JES_Do,"nhf5_JES_Do/I");
  newtree->Branch("nhf5_JER_Up", &nhf5_JER_Up,"nhf5_JER_Up/I");
  newtree->Branch("nhf5_JER_Do", &nhf5_JER_Do,"nhf5_JER_Do/I");

  newtree->Branch("nhf0", &nhf0,"nhf0/I");
  newtree->Branch("nhf0_JES_Up", &nhf0_JES_Up,"nhf0_JES_Up/I");
  newtree->Branch("nhf0_JES_Do", &nhf0_JES_Do,"nhf0_JES_Do/I");
  newtree->Branch("nhf0_JER_Up", &nhf0_JER_Up,"nhf0_JER_Up/I");
  newtree->Branch("nhf0_JER_Do", &nhf0_JER_Do,"nhf0_JER_Do/I");

  newtree->Branch("BTagNorm", &BTagNorm, "BTagNorm/D");
  newtree->Branch("BTagNorm_up_lfstats1",   &BTagNorm_up_lfstats1,   "BTagNorm_up_lfstats1/D");
  newtree->Branch("BTagNorm_down_lfstats1", &BTagNorm_down_lfstats1, "BTagNorm_down_lfstats1/D");
  newtree->Branch("BTagNorm_up_lfstats2",   &BTagNorm_up_lfstats2,   "BTagNorm_up_lfstats2/D");
  newtree->Branch("BTagNorm_down_lfstats2", &BTagNorm_down_lfstats2, "BTagNorm_down_lfstats2/D");
  newtree->Branch("BTagNorm_up_lf",         &BTagNorm_up_lf,         "BTagNorm_up_lf/D");
  newtree->Branch("BTagNorm_down_lf",       &BTagNorm_down_lf,       "BTagNorm_down_lf/D");
  newtree->Branch("BTagNorm_up_hf",         &BTagNorm_up_hf,         "BTagNorm_up_hf/D");
  newtree->Branch("BTagNorm_down_hf",       &BTagNorm_down_hf,       "BTagNorm_down_hf/D");
  newtree->Branch("BTagNorm_up_jes",        &BTagNorm_up_jes,        "BTagNorm_up_jes/D");
  newtree->Branch("BTagNorm_down_jes",      &BTagNorm_down_jes,      "BTagNorm_down_jes/D");
  newtree->Branch("BTagNorm_up_hfstats1",   &BTagNorm_up_hfstats1,   "BTagNorm_up_hfstats1/D");
  newtree->Branch("BTagNorm_down_hfstats1", &BTagNorm_down_hfstats1, "BTagNorm_down_hfstats1/D");
  newtree->Branch("BTagNorm_up_hfstats2",   &BTagNorm_up_hfstats2,   "BTagNorm_up_hfstats2/D");
  newtree->Branch("BTagNorm_down_hfstats2", &BTagNorm_down_hfstats2, "BTagNorm_down_hfstats2/D");
  newtree->Branch("BTagNorm_up_cferr1",     &BTagNorm_up_cferr1,     "BTagNorm_up_cferr1/D");
  newtree->Branch("BTagNorm_down_cferr1",   &BTagNorm_down_cferr1,   "BTagNorm_down_cferr1/D");
  newtree->Branch("BTagNorm_up_cferr2",     &BTagNorm_up_cferr2,     "BTagNorm_up_cferr2/D");
  newtree->Branch("BTagNorm_down_cferr2",   &BTagNorm_down_cferr2,   "BTagNorm_down_cferr2/D");

  newtree->Branch("TopPtReweight", &TopPtReweight,"TopPtReweight/D");
  if(DataYear==2018 && !IsDATA){
    newtree->Branch("HEMweight", &HEMweight,"HEMweight/D");
  }

  // clear vector residual
  SingleMuTrgs.clear();
  SingleElTrgs.clear();


  cout << "[Skim_TTSemiLep::initializeAnalyzer] Skim List====================== " << endl;
  if(DataYear==2016){
    SingleMuTrgs = {
      "HLT_IsoMu24_v",
      "HLT_IsoTkMu24_v"
    };
    trgSFkeyMu = "IsoMu24";
    trgSFkeyEl = "";
    TriggerSafePtCutMu=26.;
    SingleElTrgs = {
      "HLT_Ele27_WPTight_Gsf_v"
    };
    TriggerSafePtCutEl=30.;
  }
  else if(DataYear==2017){
    SingleMuTrgs = {
      "HLT_IsoMu27_v"
    };
    trgSFkeyMu = "IsoMu27";
    trgSFkeyEl = "Ele35_WPTight";
    TriggerSafePtCutMu=30.;
    SingleElTrgs = {
      "HLT_Ele35_WPTight_Gsf_v"
    };
    TriggerSafePtCutEl=37.;
  }
  else if(DataYear==2018){
    SingleMuTrgs = {
      "HLT_IsoMu24_v"
    };
    trgSFkeyMu = "IsoMu24";
    trgSFkeyEl = "";
    TriggerSafePtCutMu=26.;
    SingleElTrgs = {
      "HLT_Ele32_WPTight_Gsf_v"
    };
    TriggerSafePtCutEl=35.;
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
  //std::vector<Jet::WP> wps ={Jet::Medium};
  //SetupBTagger(taggers, wps, true, DataYear==2017?true:false);
  std::vector<Jet::WP> wps ={Jet::Reshaping};
  SetupBTagger(taggers, wps, true, false); // call syst. no period dependent
  //TODO: Get btagging sf.

  // load btag reshape norm.
  this->InitBTagReshapeNormEstimator();
}

void Skim_TTSemiLep::executeEvent(){

  muons.clear();
  electrons.clear();
  gens.clear();
  leps.clear();
  jets.clear();
  jets_JES_Up.clear();
  jets_JES_Do.clear();
  jets_JER_Up.clear();
  jets_JER_Do.clear();

  muons.shrink_to_fit();
  electrons.shrink_to_fit();
  gens.shrink_to_fit();
  leps.shrink_to_fit();

  nbtags=0;
  nbtags_JES_Up=0;
  nbtags_JES_Do=0;
  nbtags_JER_Up=0;
  nbtags_JER_Do=0;

  nhf5=0;
  nhf5_JES_Up=0;
  nhf5_JES_Do=0;
  nhf5_JER_Up=0;
  nhf5_JER_Do=0;
  
  nhf0=0;
  nhf0_JES_Up=0;
  nhf0_JES_Do=0;
  nhf0_JER_Up=0;
  nhf0_JER_Do=0;

  BTagSF_vector.clear();
  BTagSF_vector_JES_Up.clear();
  BTagSF_vector_JES_Do.clear();
  BTagSF_vector_JER_Up.clear();
  BTagSF_vector_JER_Do.clear();
  BTagSF_vector_up_lfstats1.clear();
  BTagSF_vector_down_lfstats1.clear();
  BTagSF_vector_up_lfstats2.clear();
  BTagSF_vector_down_lfstats2.clear();
  BTagSF_vector_up_lf.clear();
  BTagSF_vector_down_lf.clear();
  BTagSF_vector_up_hf.clear();
  BTagSF_vector_down_hf.clear();
  BTagSF_vector_up_jes.clear();
  BTagSF_vector_down_jes.clear();
  BTagSF_vector_up_hfstats1.clear();
  BTagSF_vector_down_hfstats1.clear();
  BTagSF_vector_up_hfstats2.clear();
  BTagSF_vector_down_hfstats2.clear();
  BTagSF_vector_up_cferr1.clear();
  BTagSF_vector_down_cferr1.clear();
  BTagSF_vector_up_cferr2.clear();
  BTagSF_vector_down_cferr2.clear();

  tmp_btagsf=1.;
  tmp_mistagsf.clear();
  tmp_mistagsf.shrink_to_fit();

  IsMu = 0; IsEl = 0;
  PUweight=1.,PUweight_Up=1.,PUweight_Do=1.;
  trgSF    = 1; trgSF_Up   = 1; trgSF_Do   = 1;

  recoSF   = 1; recoSF_Up  = 1; recoSF_Do = 1;

  IdSF    = 1; IdSF_Up   = 1; IdSF_Do   = 1;

  IsoSF =1; IsoSF_Up =1; IsoSF_Do =1;
  
  pdf_scale_Up = 1; pdf_scale_Do = 1;
  

  //diLep_passSelectiveQ = false;

  evt = new Event;
  *evt = GetEvent();


  // Filters ====================
  FillHist("CutFlow",0,1,30,0,30);
  if( HasFlag("MetFt"))if(!PassMETFilter()) return;
  FillHist("CutFlow",1,1,30,0,30);


  FillHist("CutFlow",5,1,30,0,30);

  muons=GetMuons("POGLooseWithLooseIso",15.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  electrons=GetElectrons("passVetoID",15.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing);

  weight_Prefire = GetPrefireWeight(0);

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
    Lep0PtCut = TriggerSafePtCutMu;
    LepEtaCut = 2.4;
    LeptonID_SF =&MCCorrection::MuonID_SF;
    LeptonISO_SF=&MCCorrection::MuonISO_SF;
    // key for private or official SF
    LeptonID_key="NUM_TightID_DEN_genTracks";

    LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";



  } //---------------------------------------------
  if(IsEl == 1){ // Electron =======================
    if(! evt->PassTrigger(SingleElTrgs) )return;
    //if(electrons[0].SelectiveQ() )if(electrons[1].SelectiveQ())  diLep_passSelectiveQ = true;
    leps=MakeLeptonPointerVector(electrons);
    Lep0PtCut = TriggerSafePtCutEl;
    LepEtaCut = 2.5;
    LeptonID_SF  = &MCCorrection::ElectronID_SF;
    LeptonReco_SF= &MCCorrection::ElectronReco_SF;
    // key for private or official SF
    LeptonID_key    = "passTightID";




  } //===========================================

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
  if(Aod_pt[0] < Lep0PtCut) return;
  if(fabs(Aod_eta[0]) > LepEtaCut) return;
    
  FillHist("CutFlow",7,1,30,0,30);
  std::vector<Jet> this_AllJets = GetAllJets();
  //HEM veto
  HEMweight = IsHEMJets(this_AllJets,1000);
  if(HEMweight==0.){
    return;
  }

  jets = GetJets("tight", 30., 2.4, 0, 0);
  jets = JetsVetoLeptonInside(jets, electrons, muons);
  std::sort(jets.begin(), jets.end(), PtComparing);
  if(!IsData){
    jets_JES_Up = GetJets("tight", 30., 2.4, 1,0);
    jets_JES_Do = GetJets("tight", 30., 2.4, -1, 0);
    jets_JER_Up = GetJets("tight", 30., 2.4, 0, 1);
    jets_JER_Do = GetJets("tight", 30., 2.4, 0, -1);
    jets_JES_Up = JetsVetoLeptonInside(jets_JES_Up, electrons, muons);
    jets_JES_Do = JetsVetoLeptonInside(jets_JES_Do, electrons, muons);
    jets_JER_Up = JetsVetoLeptonInside(jets_JER_Up, electrons, muons);
    jets_JER_Do = JetsVetoLeptonInside(jets_JER_Do, electrons, muons);
    std::sort(jets_JES_Up.begin(), jets_JES_Up.end(), PtComparing);
    std::sort(jets_JES_Do.begin(), jets_JES_Do.end(), PtComparing);
    std::sort(jets_JER_Up.begin(), jets_JER_Up.end(), PtComparing);
    std::sort(jets_JER_Do.begin(), jets_JER_Do.end(), PtComparing);
  }

  if(IsData){
    if(jets.size()<4) return;
  }
  else{
    if(
       jets.size() <4 &&
       jets_JES_Up.size() <4 &&    
       jets_JES_Do.size() <4 &&
       jets_JER_Up.size() <4 &&
       jets_JER_Do.size() <4
      ) return;
  }
  FillHist("CutFlow",8,1,30,0,30);

  if(IsData){
    for(unsigned int ij = 0 ; ij < jets.size(); ij++){ if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Reshaping,false,0)) nbtags++; }
  }
  else{
    for(unsigned int ij = 0 ; ij < jets.size(); ij++){ if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Reshaping,false,0)) nbtags++; }
    for(unsigned int ij = 0 ; ij < jets_JES_Up.size(); ij++){ if(IsBTagged(jets_JES_Up.at(ij), Jet::DeepCSV, Jet::Reshaping,false,0)) nbtags_JES_Up++; }
    for(unsigned int ij = 0 ; ij < jets_JES_Do.size(); ij++){ if(IsBTagged(jets_JES_Do.at(ij), Jet::DeepCSV, Jet::Reshaping,false,0)) nbtags_JES_Do++; }
    for(unsigned int ij = 0 ; ij < jets_JER_Up.size(); ij++){ if(IsBTagged(jets_JER_Up.at(ij), Jet::DeepCSV, Jet::Reshaping,false,0)) nbtags_JER_Up++; }
    for(unsigned int ij = 0 ; ij < jets_JER_Do.size(); ij++){ if(IsBTagged(jets_JER_Do.at(ij), Jet::DeepCSV, Jet::Reshaping,false,0)) nbtags_JER_Do++; }
  }
  //
  //TODO: will be calculated by JES/JER variabtion
  //BtaggingSFEvtbyEvt(jetsLveto_pt30cut, Jet::DeepCSV, Jet::Medium, 0, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  //BTagSF = tmp_btagsf;
  //MisTagSF =0;
  //for(auto &x : tmp_mistagsf){
  //  MisTagSF += x;
  //}
  //BtaggingSFEvtbyEvt(jetsLveto_pt30cut, Jet::DeepCSV, Jet::Medium, 1, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  //BTagSF_Up = tmp_btagsf;
  //MisTagSF_Up = 0;
  //for(auto &x : tmp_mistagsf){
  //  MisTagSF_Up += x;
  //}
  //BtaggingSFEvtbyEvt(jetsLveto_pt30cut, Jet::DeepCSV, Jet::Medium, -1, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  //BTagSF_Do = tmp_btagsf;
  //MisTagSF_Do = 0;
  //for(auto &x : tmp_mistagsf){
  //  MisTagSF_Do += x;
  //}
  //
  if(!IsData){
    BTagSF               = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  0, BTagSF_vector              );
    BTagSF_JES_Up        = BtaggingSFReshape(jets_JES_Up, Jet::DeepCSV, Jet::Reshaping,  0, BTagSF_vector_JES_Up       );
    BTagSF_JES_Do        = BtaggingSFReshape(jets_JES_Do, Jet::DeepCSV, Jet::Reshaping,  0, BTagSF_vector_JES_Do       );
    BTagSF_JER_Up        = BtaggingSFReshape(jets_JER_Up, Jet::DeepCSV, Jet::Reshaping,  0, BTagSF_vector_JER_Up       );
    BTagSF_JER_Do        = BtaggingSFReshape(jets_JER_Do, Jet::DeepCSV, Jet::Reshaping,  0, BTagSF_vector_JER_Do       );
    BTagSF_up_lfstats1   = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  1, BTagSF_vector_up_lfstats1  );
    BTagSF_down_lfstats1 = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -1, BTagSF_vector_down_lfstats1);
    BTagSF_up_lfstats2   = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  2, BTagSF_vector_up_lfstats2  );
    BTagSF_down_lfstats2 = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -2, BTagSF_vector_down_lfstats2);
    BTagSF_up_hf         = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  3, BTagSF_vector_up_hf        );
    BTagSF_down_hf       = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -3, BTagSF_vector_down_hf      );
    BTagSF_up_lf         = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  4, BTagSF_vector_up_lf        );
    BTagSF_down_lf       = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -4, BTagSF_vector_down_lf      );

    BTagSF_up_jes        = BtaggingSFReshape(jets_JES_Up, Jet::DeepCSV, Jet::Reshaping,  5, BTagSF_vector_up_jes       );
    BTagSF_down_jes      = BtaggingSFReshape(jets_JES_Do, Jet::DeepCSV, Jet::Reshaping, -5, BTagSF_vector_down_jes     );
    BTagSF_up_hfstats1   = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  6, BTagSF_vector_up_hfstats1  );
    BTagSF_down_hfstats1 = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -6, BTagSF_vector_down_hfstats1);
    BTagSF_up_hfstats2   = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  7, BTagSF_vector_up_hfstats2  );
    BTagSF_down_hfstats2 = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -7, BTagSF_vector_down_hfstats2);
    BTagSF_up_cferr1     = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  8, BTagSF_vector_up_cferr1    );
    BTagSF_down_cferr1   = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -8, BTagSF_vector_down_cferr1  );
    BTagSF_up_cferr2     = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping,  9, BTagSF_vector_up_cferr2    );
    BTagSF_down_cferr2   = BtaggingSFReshape(jets,        Jet::DeepCSV, Jet::Reshaping, -9, BTagSF_vector_down_cferr2  );
  }


  /////////////////PUreweight///////////////////
  PileUpWeight= &MCCorrection::GetPileUpWeight;
  if(DataYear==2017 &&
     ( MCSample=="TTLJ_powheg_hdamp_Do" ||
       MCSample=="TTLJ_powheg_mass_Up" ||
       MCSample=="TT_herwig"
     )
    ){
    PileUpWeight = &MCCorrection::GetPileUpWeightBySampleName;
  }
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

      trgSF *= IsMu?mcCorr->MuonTrigger_SF("POGTight", trgSFkeyMu, muons, 0) :
	            DataYear==2017?mcCorr->ElectronTrigger_SF("passTightID",trgSFkeyEl,electrons,0):1.;
      trgSF_Up *=IsMu?mcCorr->MuonTrigger_SF("POGTight", trgSFkeyMu, muons, 1) :
	            DataYear==2017?mcCorr->ElectronTrigger_SF("passTightID",trgSFkeyEl,electrons,1):1.;
      trgSF_Do *= IsMu?mcCorr->MuonTrigger_SF("POGTight", trgSFkeyMu, muons, -1) :
	            DataYear==2017?mcCorr->ElectronTrigger_SF("passTightID",trgSFkeyEl,electrons,-1):1.;

    }
  }

  //gens = GetGens();
  //BHGetGens(gens);
  //TopPtReweight = mcCorr->GetTopPtReweight(gens);
  TopPtReweight = mcCorr->GetTopPtReweight(gen_pt, gen_PID, gen_status);

  if(!IsData){

    double sumW_before_BTagSF;
    sumW_before_BTagSF = weight_norm_1invpb*evt->MCweight()*evt->GetTriggerLumi("Full");
    sumW_before_BTagSF *= PUweight*IdSF*IsoSF*recoSF*trgSF*TopPtReweight;
    sumW_before_BTagSF *= DataYear<2018?L1PrefireReweight_Central:1.;
    sumW_before_BTagSF *= DataYear==2018?HEMweight:1.;

    // count number of hf==5
    for(auto& jet: jets){ nhf5 += jet.hadronFlavour()==5?1:0; nhf0 += jet.hadronFlavour()==0?1:0; }
    for(auto& jet: jets_JES_Up){ nhf5_JES_Up += jet.hadronFlavour()==5?1:0; nhf0_JES_Up += jet.hadronFlavour()==0?1:0; }
    for(auto& jet: jets_JES_Do){ nhf5_JES_Do += jet.hadronFlavour()==5?1:0; nhf0_JES_Do += jet.hadronFlavour()==0?1:0; }
    for(auto& jet: jets_JER_Up){ nhf5_JER_Up += jet.hadronFlavour()==5?1:0; nhf0_JER_Up += jet.hadronFlavour()==0?1:0; }
    for(auto& jet: jets_JER_Do){ nhf5_JER_Do += jet.hadronFlavour()==5?1:0; nhf0_JER_Do += jet.hadronFlavour()==0?1:0; }

    //std::map<TString, std::vector<double>*> MapBTagSyst;
    //MapBTagSyst[""]              = &BTagSF_vector;
    //MapBTagSyst["up_lfstats1"]   = &BTagSF_vector_up_lfstats1;
    //MapBTagSyst["down_lfstats1"] = &BTagSF_vector_down_lfstats1;
    //MapBTagSyst["up_lfstats2"]   = &BTagSF_vector_up_lfstats2;
    //MapBTagSyst["down_lfstats2"] = &BTagSF_vector_down_lfstats2;
    //MapBTagSyst["up_lf"]         = &BTagSF_vector_up_lf;       
    //MapBTagSyst["down_lf"]       = &BTagSF_vector_down_lf;     
    //MapBTagSyst["up_hf"]         = &BTagSF_vector_up_hf;       
    //MapBTagSyst["down_hf"]       = &BTagSF_vector_down_hf;     
    //MapBTagSyst["up_jes"]        = &BTagSF_vector_up_jes;      
    //MapBTagSyst["down_jes"]      = &BTagSF_vector_down_jes;    
    //MapBTagSyst["up_hfstats1"]   = &BTagSF_vector_up_hfstats1; 
    //MapBTagSyst["down_hfstats1"] = &BTagSF_vector_down_hfstats1;
    //MapBTagSyst["up_hfstats2"]   = &BTagSF_vector_up_hfstats2; 
    //MapBTagSyst["down_hfstats2"] = &BTagSF_vector_down_hfstats2;
    //MapBTagSyst["up_cferr1"]     = &BTagSF_vector_up_cferr1;   
    //MapBTagSyst["down_cferr1"]   = &BTagSF_vector_down_cferr1; 
    //MapBTagSyst["up_cferr2"]     = &BTagSF_vector_up_cferr2;   
    //MapBTagSyst["down_cferr2"]   = &BTagSF_vector_down_cferr2; 

    //for(auto &BTagSyst : MapBTagSyst ){
    //  if(BTagSyst.first=="down_jes" && jets_JES_Do.size()>=4){
    //    for(unsigned int i=0; i<jets_JES_Do.size(); i++){
    //      TString histName = this->GetBTagBin(jets_JES_Do.at(i));
    //      histName += BTagSyst.first==""?"":"_"+BTagSyst.first;
    //      FillHist(histName, 0, sumW_before_BTagSF,2,0,2);
    //      FillHist(histName, 1, sumW_before_BTagSF*BTagSyst.second->at(i),2,0,2);
    //    }
    //  }
    //  else if(BTagSyst.first=="up_jes" && jets_JES_Up.size()>=4){
    //    for(unsigned int i=0; i<jets_JES_Up.size(); i++){
    //      TString histName = this->GetBTagBin(jets_JES_Up.at(i));
    //      histName += BTagSyst.first==""?"":"_"+BTagSyst.first;
    //      FillHist(histName, 0, sumW_before_BTagSF,2,0,2);
    //      FillHist(histName, 1, sumW_before_BTagSF*BTagSyst.second->at(i),2,0,2);
    //    }
    //  }
    //  else if(BTagSyst.first!="up_jes" && BTagSyst.first!="down_jes" && jets.size()>=4){
    //    for(unsigned int i=0; i<jets.size(); i++){
    //      TString histName = this->GetBTagBin(jets.at(i));
    //      histName += BTagSyst.first==""?"":"_"+BTagSyst.first;
    //      FillHist(histName, 0, sumW_before_BTagSF,2,0,2);
    //      FillHist(histName, 1, sumW_before_BTagSF*BTagSyst.second->at(i),2,0,2);
    //    }
    //  }
    //}
    //debug
    //cout << "lets print out btag sfs and csv" << endl;
    //for(unsigned int i=0; i<jets.size(); i++){
    //  double sf = BTagSF_vector.at(i);
    //  double csv = jets.at(i).GetTaggerResult(Jet::DeepCSV);
    //  double pt = jets.at(i).Pt();
    //  double eta = jets.at(i).Eta();
    //  if(jets.at(i).hadronFlavour()==5)
    //    cout << "idx: " << i <<"\tpt: " << pt << "\teta: " << eta <<"\tsf: " << sf << "\t\t" << "csv: " << csv << endl;	    
    //}
    //cout << BTagSF << endl;
    this->BTagReshapeNormEstimator();
    
  }

  //fill baseW
  if(IsDATA){
    baseW = 1;
  }else{
    baseW = weight_norm_1invpb*evt->MCweight()*evt->GetTriggerLumi("Full");
  }


  newtree->Fill();

  //require more than 2b tagged jetLvetos
  if(IsData){
    if(nbtags < 2) return;
  }
  else{
    if(nbtags < 2 &&
       nbtags_JES_Up < 2 &&  
       nbtags_JES_Do < 2 &&  
       nbtags_JER_Up < 2 &&  
       nbtags_JER_Do < 2 
      ) return;
  }
  FillHist("CutFlow",9,1,30,0,30);



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


void Skim_TTSemiLep::InitBTagReshapeNormEstimator(){
  //////
  BTagNormPath = getenv("DATA_DIR");
  BTagNormPath = BTagNormPath+"/"+TString::Itoa(DataYear,10)+"/BTagReshapeNorm/";
  //
  btagNorm_root = new TFile(BTagNormPath+"BTag_Reshape_Norm.root","READ");
  //
  TIter next(btagNorm_root->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
    TString className = key->GetClassName();
    TClass *cl = gROOT->GetClass(className);
    if(!cl->InheritsFrom("TH1D")) continue;
    TH1D* th1d = (TH1D*)key->ReadObj();
    TString histName = th1d->GetName();
    if(!histName.Contains("flav")) continue;
    BTagNormHist[histName] = th1d;
    cout << histName << endl;
  }

}


void Skim_TTSemiLep::BTagReshapeNormEstimator(){

  std::map<TString, double*> MapBTagSyst;
  MapBTagSyst[""]              = &BTagNorm;              
  MapBTagSyst["up_lfstats1"]   = &BTagNorm_up_lfstats1;   
  MapBTagSyst["down_lfstats1"] = &BTagNorm_down_lfstats1; 
  MapBTagSyst["up_lfstats2"]   = &BTagNorm_up_lfstats2;   
  MapBTagSyst["down_lfstats2"] = &BTagNorm_down_lfstats2; 
  MapBTagSyst["up_lf"]         = &BTagNorm_up_lf;         
  MapBTagSyst["down_lf"]       = &BTagNorm_down_lf;       
  MapBTagSyst["up_hf"]         = &BTagNorm_up_hf;         
  MapBTagSyst["down_hf"]       = &BTagNorm_down_hf;       
  MapBTagSyst["up_jes"]        = &BTagNorm_up_jes;        
  MapBTagSyst["down_jes"]      = &BTagNorm_down_jes;      
  MapBTagSyst["up_hfstats1"]   = &BTagNorm_up_hfstats1;   
  MapBTagSyst["down_hfstats1"] = &BTagNorm_down_hfstats1; 
  MapBTagSyst["up_hfstats2"]   = &BTagNorm_up_hfstats2;   
  MapBTagSyst["down_hfstats2"] = &BTagNorm_down_hfstats2; 
  MapBTagSyst["up_cferr1"]     = &BTagNorm_up_cferr1;     
  MapBTagSyst["down_cferr1"]   = &BTagNorm_down_cferr1;   
  MapBTagSyst["up_cferr2"]     = &BTagNorm_up_cferr2;     
  MapBTagSyst["down_cferr2"]   = &BTagNorm_down_cferr2;   
  //
  for(auto &BTagSyst : MapBTagSyst ){
    *(BTagSyst.second) = 1.;
    std::vector<Jet> *p_jets;
    if(BTagSyst.first=="down_jes" && jets_JES_Do.size()>=4){
      p_jets = &jets_JES_Do;
    }
    else if(BTagSyst.first=="up_jes" && jets_JES_Up.size()>=4){
      p_jets = &jets_JES_Up;
    }
    else if(BTagSyst.first!="up_jes" && BTagSyst.first!="down_jes" && jets.size()>=4){
      p_jets = &jets;
    }
    else{
      p_jets = NULL;
    }
    //
    if(p_jets){
      //debug
      //if(p_jets==&jets){
      //  cout << "lets print btag Norm"<< endl;
      //}
      for(unsigned int i=0; i<p_jets->size(); i++){
        TString histName = this->GetBTagBin(p_jets->at(i));
        histName += BTagSyst.first==""?"":"_"+BTagSyst.first;
        double sumW_before_btagSF = BTagNormHist[histName]->GetBinContent(1);
        double sumW_after_btagSF  = BTagNormHist[histName]->GetBinContent(2);
        double tmp_Norm = sumW_before_btagSF/sumW_after_btagSF;
        *(BTagSyst.second) *= tmp_Norm;
	//debug
        //if(p_jets==&jets && BTagSyst.first=="" && jets.at(i).hadronFlavour()==5){
	//  cout << "idx: " << i <<"\tnorm: " << tmp_Norm << endl;
        //}
      }
      //if(p_jets==&jets && BTagSyst.first=="")
      //  cout << *(BTagSyst.second) << endl;
    }
  }
  //

}


TString Skim_TTSemiLep::GetBTagBin(const Jet& jet){
  int    had_flav = jet.hadronFlavour();
  double jet_pt   = jet.Pt();
  double jet_absEta  = fabs(jet.Eta());

  TString out;
  if(had_flav==4){
    out="flav4";
    //
    if(jet_pt>20 && jet_pt<=30){
      out+="_pt20to30";
    }
    else if(jet_pt>30 && jet_pt<=50){
      out+="_pt30to50";
    }
    else if(jet_pt>50 && jet_pt<=70){
      out+="_pt50to70";
    }
    else if(jet_pt>70 && jet_pt<=100){
      out+="_pt70to100";
    }
    else{
      out+="_pt100toInf";
    }
  }
  else if(had_flav==5){
    out="flav5";
    //
    if(jet_pt>20 && jet_pt<=30){
      out+="_pt20to30";
    }
    else if(jet_pt>30 && jet_pt<=50){
      out+="_pt30to50";
    }
    else if(jet_pt>50 && jet_pt<=70){
      out+="_pt50to70";
    }
    else if(jet_pt>70 && jet_pt<=100){
      out+="_pt70to100";
    }
    else{
      out+="_pt100toInf";
    }
  }
  else if(had_flav==0){
    out="flav0";
    //
    if(jet_pt>20 && jet_pt<=30){
      out+="_pt20to30";
    }
    else if(jet_pt>30 && jet_pt<=40){
      out+="_pt30to40";
    }
    else if(jet_pt>40 && jet_pt<=60){
      out+="_pt40to60";
    }
    else{
      out+="_pt60toInf";
    }
    //
    if(jet_absEta<0.8){
      out+="_absEta0to0p8";
    }
    else if(jet_absEta<1.6){
      out+="_absEta0p8to1p6";
    }
    else{
      out+="_absEta1p6to";
    }
  }

  return out;

}
