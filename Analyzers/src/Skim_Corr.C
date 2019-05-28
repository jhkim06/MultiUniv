#include "Skim_Corr.h"


void Skim_Corr::initializeAnalyzer(){

  //initializeAnalyzerTools(); //To use SF, executed by root macro before Loop()

  //=================================
  // Skim Types
  //=================================
   

  if( HasFlag("Corr")){
    cout<<"[Skim_Corr::initializeAnalyzer] Correction"<<endl;
  }
  else{
    cout <<"[Skim_Corr::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }

  TString data_roc = getenv("ROC_DIR");
  if(DataYear == 2016){
    data_roc+="/V3/RoccoR2016.txt";
  }
  else if(DataYear == 2017){
    data_roc+="/V3/RoccoR2017.txt";
  }
  else if(DataYear == 2018){
    data_roc+="/V3/RoccoR2018.txt";
  }
  else{
       cout << DataYear << " is not provided by ROC" << endl;
       exit(EXIT_FAILURE); 
  }

  RocUtil = new RocCorrUtil(data_roc);
  //RocUtil.init(data_roc.Data());


  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);
  //newtree = fChain->CloneTree(0);

  // New Branch

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

  newtree->Branch("ZPtCor", &ZPtCor,"ZPtCor/D");

  newtree->Branch("muon_roch_sf_old",     &muon_roch_sf_old);
  newtree->Branch("muon_roch_sf_err_old", &muon_roch_sf_err_old);
  newtree->Branch("muon_roch_sf_err",     &muon_roch_sf_err);

  // Kinematic Variables
  //

  //b_trgSF = newtree->Branch("trgSF", &trgSF,"trgSF/F");
  //b_trgSF_Up = newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/F");
  //b_trgSF_Do = newtree->Branch("trgSF_Do", &trgSF_Do,"trgSF_Do/F");



  // clear vector residual
  DiMuTrgs.clear();
  DiElTrgs.clear();


  cout << "[Skim_Corr::initializeAnalyzer] Skim List====================== " << endl;
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
    cout<<"[Skim_Corr::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
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

void Skim_Corr::executeEvent(){

  evt = new Event;
  *evt = GetEvent();

  muons.clear();
  electrons.clear();
  gens.clear();
  muon_roch_sf_old.clear();
  muon_roch_sf_err.clear();
  muon_roch_sf_err_old.clear();

  // buffer or memory downsizing
  muons.shrink_to_fit();
  electrons.shrink_to_fit();
  gens.shrink_to_fit();
  muon_roch_sf_old.shrink_to_fit();
  muon_roch_sf_err.shrink_to_fit();
  muon_roch_sf_err_old.shrink_to_fit();

  gens = GetGens();

  /////////////////PUreweight///////////////////

  PUweight=1.,PUweight_Up=1.,PUweight_Do=1.;

  PUweight    = GetPileUpWeight(nPileUp,0);
  PUweight_Up = GetPileUpWeight(nPileUp,1);
  PUweight_Do = GetPileUpWeight(nPileUp,-1);

  // Lepton Ordering (do we need this?)
  //vector< pair<size_t, doubleIter> > order(electron_Energy->size());
  //size_t idx(0);
  //for( doubleIter it = electron_Energy->begin(); it != electron_Energy->end(); ++it,++idx){
  //  order[idx] = make_pair(idx, it);
  //  cout<<idx<<" eleE("<<*it<<") ";
  //}
  //cout<<endl;
  //idx = 0;
  //sort(order.begin(), order.end(), DIY::orderingD() );
  //for( doubleIter it = electron_Energy->begin(); it != electron_Energy->end(); ++it,++idx){
  //  cout<<"new "<<order[idx].first<<" "<<*order[idx].second;
  //}
  //cout<<endl;


  // Rochester correction
  cout<<"event: "<<event<<endl;
  for(size_t i(0); i <muon_pt->size(); i++){
    Muon mu;
    mu.SetPtEtaPhiM(muon_pt->at(i), muon_eta->at(i), muon_phi->at(i), muon_mass->at(i));
    mu.SetCharge(muon_charge->at(i));
    mu.SetTrackerLayersWithMeasurement(muon_trackerLayers->at(i));
    //                set 0 default, nmemeber 1 means 0 for input
    RocUtil->CalcScaleAndError(mu, 0, 0, event, gens, IsDATA);
    oldSf = muon_roch_sf->at(i);
    oldSf_Err = muon_roch_sf_up->at(i) - muon_roch_sf->at(i);
    newSf = mu.MomentumScale();
    newSf_Err = mu.MomentumScaleError();

    cout<<"old rc: "<<oldSf<<" + "<<oldSf_Err<<endl;
    cout<<"new rc: "<<newSf<<" + "<<newSf_Err<<endl;
    muon_roch_sf->at(i) = newSf;
    muon_roch_sf_err.push_back(newSf_Err);
    muon_roch_sf_up->at(i) = newSf + newSf_Err;
    muon_roch_sf_old.push_back(oldSf);
    muon_roch_sf_err_old.push_back(oldSf_Err);
  }
  




  //===============================
  // Gen Info
  // status code: http://home.thep.lu.se/~torbjorn/pythia81html/ParticleProperties.html
  // genParticles status code: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATMCMatchingExercise 
  //===============================

  ZPtCor = 1;
  if(MCSample.Contains("DYJets") || MCSample.Contains("DYJets10to50_MG")){
    Gen genL0, genL1, genFsr, genHardL0, genHardL1;
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
    if( abs(genHardL0.PID()) != 15 )if( (genL1.PID() == 11) || (genL1.PID() == 13) ){
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
  //b_trgSF_Do->Fill();
  newtree->Fill();


}



void Skim_Corr::executeEventFromParameter(AnalyzerParameter param){

}

Skim_Corr::Skim_Corr(){

}

Skim_Corr::~Skim_Corr(){

}

void Skim_Corr::WriteHist(){


  //Delete unnecessary trees
  //newtree->SetBranchStatus("muon_roch_sf_up", 0); only works before clone
  //TBranch *sfUp = newtree->GetBranch("muon_roch_sf_up");
  //newtree->GetListOfBranches()->Remove(sfUp); // segment violation at saving time to files
  //TLeaf *LsfUp = newtree->GetLeaf("muon_roch_sf_up");
  //newtree->GetListOfLeaves()->Remove(LsfUp);// compile error
  

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_Corr::initializeAnalyzer
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

