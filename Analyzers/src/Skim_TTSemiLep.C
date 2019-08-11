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

  newtree->Branch("n_bjet_deepcsv_m_noSF", &n_bjet_deepcsv_m_noSF,"n_bjet_deepcsv_m_noSF/I");
  newtree->Branch("BTagSF", &BTagSF,"BTagSF/D");
  newtree->Branch("BTagSF_Up", &BTagSF_Up,"BTagSF_Up/D");
  newtree->Branch("BTagSF_Do", &BTagSF_Do,"BTagSF_Do/D");
  newtree->Branch("MisTagSF", &MisTagSF,"MisTagSF/D");
  newtree->Branch("MisTagSF_Up", &MisTagSF_Up,"MisTagSF_Up/D");
  newtree->Branch("MisTagSF_Do", &MisTagSF_Do,"MisTagSF_Do/D");

  newtree->Branch("TopPtReweight", &TopPtReweight,"TopPtReweight/D");

  // clear vector residual
  SingleMuTrgs.clear();
  SingleElTrgs.clear();


  cout << "[Skim_TTSemiLep::initializeAnalyzer] Skim List====================== " << endl;
  if(DataYear==2016){
    SingleMuTrgs = {
      "HLT_IsoMu24_v"
    };
    trgSFkeyMu = "IsoMu24";
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
  std::vector<Jet::WP> wps ={Jet::Medium};

  SetupBTagger(taggers, wps, true, DataYear==2017?true:false);

}

void Skim_TTSemiLep::executeEvent(){

  muons.clear();
  electrons.clear();
  gens.clear();
  leps.clear();
  this_AllJets.clear();
  jets.clear();
  jetsLveto.clear();

  muons.shrink_to_fit();
  electrons.shrink_to_fit();
  gens.shrink_to_fit();
  leps.shrink_to_fit();
  this_AllJets.shrink_to_fit();
  jets.shrink_to_fit();
  jetsLveto.shrink_to_fit();

  tmp_btagsf=1.;
  tmp_mistagsf.clear();
  tmp_mistagsf.shrink_to_fit();

  n_bjet_deepcsv_m_noSF=0;
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
  this_AllJets = GetAllJets();
  jets = SelectJets(this_AllJets, "tight", 20., 2.4);
  jetsLveto = JetsVetoLeptonInside(jets, electrons, muons);
  std::sort(jetsLveto.begin(), jetsLveto.end(), PtComparing);
  if(jetsLveto.size()<4) return;
  FillHist("CutFlow",8,1,30,0,30);


  for(unsigned int ij = 0 ; ij < jetsLveto.size(); ij++){
    if(IsBTagged(jetsLveto.at(ij), Jet::DeepCSV, Jet::Medium,false,0)){
      n_bjet_deepcsv_m_noSF++; // method for getting btag with no SF applied to MC
    }
    else{
    }
  }
  //require more than 2b tagged jetLvetos
  if(n_bjet_deepcsv_m_noSF < 2) return;
  FillHist("CutFlow",9,1,30,0,30);


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

      trgSF *= IsMu?mcCorr->MuonTrigger_SF("POGTight", trgSFkeyMu, muons, 0) : 1.;
      trgSF_Up *=IsMu?mcCorr->MuonTrigger_SF("POGTight", trgSFkeyMu, muons, 1) : 1.;
      trgSF_Do *= IsMu?mcCorr->MuonTrigger_SF("POGTight", trgSFkeyMu, muons, -1) : 1.;

    }
  }

  BtaggingSFEvtbyEvt(jetsLveto, Jet::DeepCSV, Jet::Medium, 0, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  BTagSF = tmp_btagsf;
  MisTagSF =0;
  for(auto &x : tmp_mistagsf){
    MisTagSF += x;
  }
  BtaggingSFEvtbyEvt(jetsLveto, Jet::DeepCSV, Jet::Medium, 1, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  BTagSF_Up = tmp_btagsf;
  MisTagSF_Up = 0;
  for(auto &x : tmp_mistagsf){
    MisTagSF_Up += x;
  }
  BtaggingSFEvtbyEvt(jetsLveto, Jet::DeepCSV, Jet::Medium, -1, tmp_btagsf, tmp_mistagsf); //@AnalyzerCore
  BTagSF_Do = tmp_btagsf;
  MisTagSF_Do = 0;
  for(auto &x : tmp_mistagsf){
    MisTagSF_Do += x;
  }



  //gens = GetGens();
  //BHGetGens(gens);
  //TopPtReweight = mcCorr->GetTopPtReweight(gens);
  TopPtReweight = mcCorr->GetTopPtReweight(gen_pt, gen_PID, gen_status);
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

