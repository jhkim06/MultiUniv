#include "Skim_DZfilter.h"

void Skim_DZfilter::initializeAnalyzer(){

  //initializeAnalyzerTools(); 

  //=================================
  // Skim Types
  //=================================

  TString data_prescale = getenv("SKFlat_WD");
  data_prescale += "/data/Run2Legacy_v3/2016/TrigPreScale/triggerData2016"; 
  psProv.setPrescaleProvider(data_prescale.Data());   

  if( HasFlag("MuMu")){
    cout<<"[Skim_DZfilter::initializeAnalyzer] MuMu Selection"<<endl;
  }
  else if( HasFlag("ElEl")){
    cout<<"[Skim_DZfilter::initializeAnalyzer] ElEl Selection"<<endl;
  }
  else if( HasFlag("MuMuOrElEl")){
    cout<<"[Skim_DZfilter::initializeAnalyzer] MuMu or ElEl Selection"<<endl;
  }
  else{
    cout <<"[Skim_DZfilter::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }
  outfile->mkdir("DZfilter");
  outfile->cd("DZfilter");
  newtree = new TTree("fitter_tree","fitter_tree");

  // New Branch
  newtree->Branch("IsMuMu", &IsMuMu,"IsMuMu/I"); 
  newtree->Branch("IsElEl", &IsElEl,"IsElel/I");

  // Kinematic Variables

  newtree->Branch("diLep_Ch", &diLep_Ch,"diLep_Ch/I");
  newtree->Branch("mcTrue", &mcTrue,"mcTrue/I");
  newtree->Branch("nPV", &nPV_,"nPV/I");
  newtree->Branch("hltPS", &hltPS,"hltPS/I");
  newtree->Branch("isNonDZPathPassed", &isNonDZPathPassed,"isNonDZPathPassed/I");
  newtree->Branch("isDZPathPassed", &isDZPathPassed,"isDZPathPassed/I");
  newtree->Branch("isBB", &isBB,"isBB/I");
  newtree->Branch("isBE", &isBB,"isBE/I");
  newtree->Branch("isEE", &isEE,"isEE/I");
  newtree->Branch("eventCategory", &eventCategory,"eventCategory/D");
  newtree->Branch("totWeight", &totWeight,"totWeight/D");
  newtree->Branch("pair_mass", &pair_mass,"pair_mass/D");
  newtree->Branch("diLep_pt", &diLep_pt,"diLep_pt/D");
  newtree->Branch("diLep_eta", &diLep_eta,"diLep_eta/D");
  newtree->Branch("leading_pt", &leading_pt,"leading_pt/D");
  newtree->Branch("subleading_pt", &subleading_pt,"subleading_pt/D");
  newtree->Branch("leading_eta", &leading_eta,"leading_eta/D");
  newtree->Branch("subleading_eta", &subleading_eta,"subleading_eta/D");

  // clear vector residual
  DiMuTrgs.clear();
  DiElTrgs.clear();

  cout << "[Skim_DZfilter::initializeAnalyzer] Skim List====================== " << endl;
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
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",
    };
  }
  else{
    cout<<"[Skim_DZfilter::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
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

void Skim_DZfilter::executeEvent(){

  mcTrue = 0;
  totWeight = 1.;
  nPV_ = 0.;
  hltPS = 1.;
  isNonDZPathPassed = 0;
  isDZPathPassed = 0;
  isBB = 0;
  isBE = 0;
  isEE = 0;
  eventCategory = -999;
  muons.clear();
  electrons.clear();
  leps.clear();

  evt = new Event;
  *evt = GetEvent();

  newtree->SetBranchAddress("IsMuMu",   &IsMuMu);
  newtree->SetBranchAddress("IsElEl",   &IsElEl);

  newtree->SetBranchAddress("mcTrue",   &mcTrue);
  newtree->SetBranchAddress("nPV",   &nPV_);
  newtree->SetBranchAddress("hltPS",   &hltPS);
  newtree->SetBranchAddress("isNonDZPathPassed", &isNonDZPathPassed);
  newtree->SetBranchAddress("isDZPathPassed", &isDZPathPassed);
  newtree->SetBranchAddress("isBB", &isBB);
  newtree->SetBranchAddress("isBE", &isBB);
  newtree->SetBranchAddress("isEE", &isEE);
  newtree->SetBranchAddress("eventCategory", &eventCategory);
  newtree->SetBranchAddress("totWeight",&totWeight);

  newtree->SetBranchAddress("diLep_Ch",&diLep_Ch);
  newtree->SetBranchAddress("pair_mass",&pair_mass);
  newtree->SetBranchAddress("diLep_pt",&diLep_pt);
  newtree->SetBranchAddress("diLep_eta",&diLep_eta);
  newtree->SetBranchAddress("leading_pt",&leading_pt);
  newtree->SetBranchAddress("subleading_pt",&subleading_pt);
  newtree->SetBranchAddress("leading_eta",&leading_eta);
  newtree->SetBranchAddress("subleading_eta",&subleading_eta);

  if(!IsDATA){
    //==== weight_norm_1invpb is set to be event weight normalized to 1 pb-1
    //==== So, you have to multiply trigger luminosity
    //==== you can pass trigger names to ev.GetTriggerLumi(), but if you are using unprescaled trigger, simply pass "Full"

    totWeight *= weight_norm_1invpb*evt->GetTriggerLumi("Full");
    //==== MCweight is +1 or -1. Should be multiplied if you are using e.g., aMC@NLO NLO samples
    totWeight *= evt->MCweight();

    Gen genL0postFSR, genL1postFSR, genHardL0, genHardL1;
    vector<Gen> gens = GetGens();

    for( int i(0); i<(int) gens.size(); i++){

      if( gens.at(i).isHardProcess()){ // from ME

        if( genHardL0.IsEmpty() && (abs(gens.at(i).PID() ) == 11 || abs(gens.at(i).PID())==13 || abs(gens.at(i).PID())==15)){
          genHardL0 = gens.at(i);
        }else if(!genHardL0.IsEmpty() && gens.at(i).PID() == -genHardL0.PID()){
          genHardL1 = gens.at(i);
          if(abs( genHardL1.PID()) == 13) return;
          if(abs( genHardL1.PID()) == 15) return;
        }
      }
      mcTrue = 1; // set mcTrue = 1 for Z to EE events

    }// end of gen loop  
  }


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
    
  PileUpWeight = NULL;

  if(IsElEl == 1){ // Electron =======================
    //if(! evt->PassTrigger(DiElTrgs) )return;

    //if( evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") == 0 && evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") == 1){
    //    cout << "DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") << endl;
    //    cout << "non DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") << endl;
    //    //std::cout <<"l1 ps "<<psProv.l1Prescale("L1_SingleEG26",run,lumi)<<std::endl;
    //    std::cout <<"hlt ps "<<psProv.hltPrescale("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",run,lumi)<<std::endl;
    //}

    //if( evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") == 1 && evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") == 0){
    //    cout << "DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") << endl;
    //    cout << "non DZ filter: " << evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") << endl;
    //    std::cout <<"hlt ps "<<psProv.hltPrescale("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",run,lumi)<<std::endl;
    //}

    leps=MakeLeptonPointerVector(electrons);
    hltPS = psProv.hltPrescale("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",run,lumi);
    isNonDZPathPassed = evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    isDZPathPassed = evt->PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

  } //===========================================

  FillHist("CutFlow",7,1,30,0,30);

  // ================================
  // Kinematic cuts 
  // ================================
  for(int i(0); i < 2; i++){ // two lepton only, pt eta the same to TnP
     Aod_pt[i]=leps.at(i)->Pt();
     Aod_eta[i]=((Electron*)leps.at(i))->scEta();
     // TODO do we need this gap veto? it is already in Electron.h for id pass ftn
     if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
  }

  FillHist("CutFlow",8,1,30,0,30);

  Lep0PtCut = 25.;
  Lep1PtCut = 15.;
  LepEtaCut = 2.5;

  if(Aod_pt[0] < Lep0PtCut) return;
  if(Aod_pt[1] < Lep1PtCut) return;
  if(fabs(Aod_eta[0]) > LepEtaCut) return;
  if(fabs(Aod_eta[1]) > LepEtaCut) return;
    
  FillHist("CutFlow",9,1,30,0,30);
  //==============================
  // Kinematic Variables 
  //==============================

  diLep_Ch = DiLepCh::NA;

  pair_mass  = DEFAULT;
  diLep_pt  = DEFAULT;
  diLep_eta  = DEFAULT;
  leading_pt = DEFAULT;
  subleading_pt = DEFAULT;
  leading_eta = DEFAULT;
  subleading_eta = DEFAULT;

  if(leps.size() > 1){
    if(leps[0]->LeptonFlavour() == Lepton::ELECTRON){
        if(leps[1]->LeptonFlavour() == Lepton::ELECTRON){
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
        pair_mass  = diLep.M();

        //if(IsDATA) nPV_ = nPV;
        //else nPV_ = nPileUp;
        nPV_ = nPV;

        if( fabs(leading_eta) < 2.0 && fabs(subleading_eta) < 2.0){
            isBB = 1; eventCategory = 0.5;
        }
        else if (fabs(leading_eta) < 2.0 && fabs(subleading_eta) > 2.0){
            isBE = 1; eventCategory = 1.5;
        }
        else if (fabs(leading_eta) > 2.0 && fabs(subleading_eta) < 2.0){
            isBE = 1; eventCategory = 1.5;
        }
        else{
            isEE = 1; eventCategory = 2.5;  
        }
    }
  }

  if(diLep_Ch != DiLepCh::ElElOS) return;

  /////////////////PUreweight///////////////////
  if(DataYear!=2018)
    PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;
  else 
    PileUpWeight = NULL; // FIXME update pileup for 2018

  if(!IsDATA){
    if(PileUpWeight!=NULL){
        totWeight *=(mcCorr->*PileUpWeight)(nPileUp,0);
    }
    else{
        totWeight *= 1.;
    }
  }

  newtree->Fill();
    
  delete evt;
}



void Skim_DZfilter::executeEventFromParameter(AnalyzerParameter param){

}

Skim_DZfilter::Skim_DZfilter(){

}

Skim_DZfilter::~Skim_DZfilter(){

}

void Skim_DZfilter::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_DZfilter::initializeAnalyzer
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

