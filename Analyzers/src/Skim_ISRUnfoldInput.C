#include "Skim_ISRUnfoldInput.h"

void Skim_ISRUnfoldInput::initializeAnalyzer(){

  initializeAnalyzerTools(); //To use SF

  //=================================
  // Skim Types
  //=================================
   

  if( HasFlag("MuMu")){
    cout<<"[Skim_ISRUnfoldInput::initializeAnalyzer] MuMu Selection"<<endl;
  }
  else if( HasFlag("ElEl")){
    cout<<"[Skim_ISRUnfoldInput::initializeAnalyzer] ElEl Selection"<<endl;
  }
  else if( HasFlag("MuMuOrElEl")){
    cout<<"[Skim_ISRUnfoldInput::initializeAnalyzer] MuMu or ElEl Selection"<<endl;
  }
  else{
    cout <<"[Skim_ISRUnfoldInput::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }

  //outfile->mkdir("Tree");
  //outfile->cd("Tree");
  //newtree = fChain->CloneTree(0); // TODO add option to save or not save the previous tree
  outfile->cd();
  newtree = new TTree("tree","tree");

  // New Branch
  newtree->Branch("IsMuMu", &IsMuMu,"IsMuMu/I");
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

  newtree->Branch("isdielectron",&isdielectron);
  newtree->Branch("isdimuon",&isdimuon);
  newtree->Branch("ptRec",&ptRec);
  newtree->Branch("mRec",&mRec);
  newtree->Branch("ptPreFSR",&ptPreFSR);
  newtree->Branch("mPreFSR",&mPreFSR);
  newtree->Branch("ptPostFSR",&ptPostFSR);
  newtree->Branch("mPostFSR",&mPostFSR);
  newtree->Branch("particleFSR",&particleFSR);
  newtree->Branch("anparticleFSR",&anparticleFSR);
  newtree->Branch("weightGen",&weightGen);
  newtree->Branch("weightRec",&weightRec);
  newtree->Branch("bTagReweight",&bTagReweight);
  newtree->Branch("ispassRec",&ispassRec);
  newtree->Branch("isfiducialPreFSR",&isfiducialPreFSR);
  newtree->Branch("DYtautau",&DYtautau);
  newtree->Branch("isBveto",&isBveto);

  //b_trgSF = newtree->Branch("trgSF", &trgSF,"trgSF/F");
  //b_trgSF_Up = newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/F");
  //b_trgSF_Dn = newtree->Branch("trgSF_Dn", &trgSF_Dn,"trgSF_Dn/F");

  // clear vector residual
  DiMuTrgs.clear();
  DiElTrgs.clear();

  cout << "[Skim_ISRUnfoldInput::initializeAnalyzer] Skim List====================== " << endl;
  if(DataYear==2016){
    DiMuTrgs = {
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
      "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
      "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v", // need to estimate the trg eff.
      "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
      "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
      "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", // need to estimate the trg eff.
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
    cout<<"[Skim_ISRUnfoldInput::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
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

void Skim_ISRUnfoldInput::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  ptRec.clear();
  mRec.clear();
  ptPreFSR.clear();
  mPreFSR.clear();
  ptPostFSR.clear();
  mPostFSR.clear();

  particleFSR.clear();
  anparticleFSR.clear();

  weightGen = 1.;
  weightRec = 1.;
  bTagReweight = 1.;

  ispassRec = 0;
  isfiducialPreFSR = 0;
  DYtautau = 0;
  isBveto = 0;

  isdielectron = 0;
  isdimuon = 0;

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

  FillHist("CutFlow",5,1,30,0,30);

  if(!IsDATA){
    //==== weight_norm_1invpb is set to be event weight normalized to 1 pb-1
    //==== So, you have to multiply trigger luminosity
    //==== you can pass trigger names to ev.GetTriggerLumi(), but if you are using unprescaled trigger, simply pass "Full"

    weightGen *= weight_norm_1invpb*evt->GetTriggerLumi("Full");

    //==== MCweight is +1 or -1. Should be multiplied if you are using e.g., aMC@NLO NLO samples
    weightGen *= evt->MCweight();
  }

  //===============================
  // Gen Info
  // status code: http://home.thep.lu.se/~torbjorn/pythia81html/ParticleProperties.html
  // genParticles status code: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATMCMatchingExercise 
  //===============================

  ZPtCor = 1;
  std::map<int, int> eleIndex;
  std::map<int, int> posIndex;
  std::map<int, int> muIndex;
  std::map<int, int> antimuIndex;

  if(MCSample.Contains("DYJets") || MCSample.Contains("DYJets10to50_MG")){
    Gen genL0Fsr, genL1Fsr, genL0postFSR, genL1postFSR, genHardL0, genHardL1;
    TLorentzVector genZ, genL0preFSR, genL1preFSR;
    vector<Gen> gens = GetGens();
    vector<Gen> gphotons;

    // Check tau process
    std::cout << "gen loop start..........." << std::endl;
    for( int i(0); i<(int) gens.size(); i++){

      if( !gens.at(i).isPrompt()) continue; // not from hadron, muon, or tau

      if( gens.at(i).isHardProcess()){ // from ME

        if( genHardL0.IsEmpty() && (abs(gens.at(i).PID() ) == 11 || abs(gens.at(i).PID())==13 || abs(gens.at(i).PID())==15)){
          genHardL0 = gens.at(i);
        }else if(!genHardL0.IsEmpty() && gens.at(i).PID() == -genHardL0.PID()){
          genHardL1 = gens.at(i);
          if(abs( genHardL1.PID()) == 11) isdielectron = 1;    
          if(abs( genHardL1.PID()) == 13) isdimuon = 1;    
          if(abs( genHardL1.PID()) == 15){
 	    DYtautau = 1;  
            //prefix = "tau_";
            break;
          }
        }
      }   

      // search from the status 1 leptons 
      if(gens.at(i).Status() == 1){ // entering detector

        if( (abs(gens.at(i).PID())==11 || abs(gens.at(i).PID())==13) ){
		std::cout << i << " pid: " << gens.at(i).PID() << " mother index: " << gens.at(i).MotherIndex() << " fromHardProcessFinalState: " << gens.at(i).fromHardProcessFinalState() << " isPrompt: " << gens.at(i).isPrompt() << " isPromptFinalState(): " << gens.at(i).isPromptFinalState() << std::endl;

                int initIndex = findInitialMoterIndex( gens.at(i).MotherIndex(), i, gens); // find the initial index of the lepton (status 1 and prompt)
                std::cout << " initial index: " << initIndex << " initial ID: " << gens.at(initIndex).PID() << " status: " << gens.at(initIndex).Status() << std::endl;
                if( gens.at(i).PID() == 11 )  eleIndex.insert(std::make_pair(initIndex, i));
                if( gens.at(i).PID() == -11 ) posIndex.insert(std::make_pair(initIndex, i));
                if( gens.at(i).PID() == 13 )  muIndex.insert(std::make_pair(initIndex, i));
                if( gens.at(i).PID() == -13 ) antimuIndex.insert(std::make_pair(initIndex, i));
        } 

        else if(gens.at(i).PID()==22){
                gphotons.push_back(gens.at(i));
        }
      }// status 1   
    }// end of gen loop   

    std::cout << "gen loop end..........." << std::endl;

    if( DYtautau == 0 ){
      vector<int> electronindex, positronindex;
      vector<int> muonindex, antimuonindex;
      vector<int> partindex, anpartindex;

      selectDilepton(gens, eleIndex, posIndex, electronindex, positronindex);
      selectDilepton(gens, muIndex, antimuIndex, muonindex, antimuonindex);

      if( electronindex.size() > 0 && muonindex.size() > 0 ){ // both electron and muon pair exist, select a pair with larger mass
         if( (gens.at(electronindex.at(0))+gens.at(positronindex.at(0))).M() > (gens.at(muonindex.at(0))+gens.at(antimuonindex.at(0))).M() ){
            partindex.push_back(electronindex.at(0));
            partindex.push_back(electronindex.at(1));

            anpartindex.push_back(positronindex.at(0));
            anpartindex.push_back(positronindex.at(1));
         }
         else{
            partindex.push_back(muonindex.at(0));
            partindex.push_back(muonindex.at(1));

            anpartindex.push_back(antimuonindex.at(0));
            anpartindex.push_back(antimuonindex.at(1));
         }
      }
      else if ( electronindex.size() > 0 && muonindex.size() == 0 ){ // only electron pair
              partindex.push_back(electronindex.at(0));
              partindex.push_back(electronindex.at(1));

              anpartindex.push_back(positronindex.at(0));
              anpartindex.push_back(positronindex.at(1));
      }
      else if ( electronindex.size() == 0 && muonindex.size() > 0 ){ // only muon pair
              partindex.push_back(muonindex.at(0));
              partindex.push_back(muonindex.at(1));

              anpartindex.push_back(antimuonindex.at(0));
              anpartindex.push_back(antimuonindex.at(1));
      }

      std::cout << "check selectDilepton, electronindex size: " << electronindex.size() << " positronindex size: " << positronindex.size() << std::endl;
      std::cout << "check selectDilepton, muonindex size: " << muonindex.size() << " antimuonindex size: " << antimuonindex.size() << std::endl;
      if( electronindex.size() > 0 ){
         std::cout << "ele first index: " << electronindex.at(0) << " second index: " << electronindex.at(1) << std::endl;
         std::cout << "pos first index: " << positronindex.at(0) << " second index: " << positronindex.at(1) << std::endl;
      }

      if( muonindex.size() > 0 ){
         std::cout << "mu first index: " << muonindex.at(0) << " second index: " << muonindex.at(1) << std::endl;
         std::cout << "an-mu first index: " << antimuonindex.at(0) << " second index: " << antimuonindex.at(1) << std::endl;
      }

      std::cout << "selected lepton pair, first index particle : " << partindex.at(0) << " second index : " << partindex.at(1) << std::endl;

      // store index from initial to final lepton
      std::map<int, int> partindexmap;
      saveMotherIndexMap(gens, partindex.at(1), partindex.at(0), partindexmap);
      saveMotherIndexMap(gens, anpartindex.at(1), anpartindex.at(0), partindexmap);

      std::map<int, int>::iterator it = partindexmap.begin();
      while(it != partindexmap.end()){
            std::cout << "check saveMotherIndexMap, index : " << it->first << " ID: " << it->second << std::endl; 
            it++;
      }

      for(unsigned int i = 0; i < gphotons.size(); i++){
         std::cout << i << " th photon, mother index: " << gphotons.at(i).MotherIndex() << " mother ID: " << gens.at(gphotons.at(i).MotherIndex()).PID() << " pt: " << gphotons.at(i).Pt() << std::endl;

         if( partindexmap.find(gphotons.at(i).MotherIndex()) != partindexmap.end() ){
           std::cout << "found mother lepton, lepton index: " << partindexmap.find(gphotons.at(i).MotherIndex())->first << " ID: " << partindexmap.find(gphotons.at(i).MotherIndex())->second << std::endl;
           if(partindexmap.find(gphotons.at(i).MotherIndex())->second > 0){
              genL0Fsr += gphotons.at(i);
              particleFSR.push_back(gphotons.at(i));
           }
           else{
               genL1Fsr += gphotons.at(i);
               anparticleFSR.push_back(gphotons.at(i));
           }
         }
      }

      // Gen genL0preFSR, genL1preFSR, genL0Fsr, genL1Fsr, genL0postFSR, genL1postFSR, genHardL0, genHardL1;
      //
      genL0postFSR = gens.at(partindex.at(1));
      genL1postFSR = gens.at(anpartindex.at(1));

      std::cout << "dilep mass pos fsr: " << (genL0postFSR+genL1postFSR).M() << std::endl;
      genL0preFSR = genL0postFSR + genL0Fsr;
      genL1preFSR = genL1postFSR + genL1Fsr;
      std::cout << "dilep mass pre fsr: " << (genL0preFSR+genL1preFSR).M() << std::endl;

      genZ = genL0preFSR + genL1preFSR;
      ZPtCor = mcCorr->GetZPtWeight(genZ.Pt(),genZ.Rapidity(),abs(genHardL0.PID())==13 ? Lepton::Flavour::MUON : Lepton::Flavour::ELECTRON);

      if ( abs(gens.at(partindex.at(1)).PID()) == 11 ) 
          if( ((genL0preFSR.Pt() > 25. && genL1preFSR.Pt() > 15.) || (genL0preFSR.Pt() > 15. && genL1preFSR.Pt() > 25.)) && fabs(genL0preFSR.Eta()) < 2.5 && fabs(genL1preFSR.Eta()) < 2.5 ) isfiducialPreFSR = 1;  
      if ( abs(gens.at(partindex.at(1)).PID() == 13) ) 
          if( ((genL0preFSR.Pt() > 20. && genL1preFSR.Pt() > 10.) || (genL0preFSR.Pt() > 10. && genL1preFSR.Pt() > 20.)) && fabs(genL0preFSR.Eta()) < 2.4 && fabs(genL1preFSR.Eta()) < 2.4 ) isfiducialPreFSR = 1;  

      // status 1 leptons + all photons
      ptPreFSR.push_back(genL0preFSR.Pt());
      ptPreFSR.push_back(genL1preFSR.Pt());
      ptPreFSR.push_back((genZ).Pt());

      mPreFSR.push_back(genL0preFSR.M());
      mPreFSR.push_back(genL1preFSR.M());
      mPreFSR.push_back((genZ).M());

      // post fsr leptons
      ptPostFSR.push_back(genL0postFSR.Pt());
      ptPostFSR.push_back(genL1postFSR.Pt());
      ptPostFSR.push_back((genL0postFSR+genL1postFSR).Pt());

      mPostFSR.push_back(genL0postFSR.M());
      mPostFSR.push_back(genL1postFSR.M());
      mPostFSR.push_back((genL0postFSR+genL1postFSR).M());

    }// not DY to tautau event
  }// only for DY MC

  // Filters ====================
  if(PassMETFilter()){ 

     Aod_eta[0] = -999.;
     Aod_eta[1] = -999.;

     FillHist("CutFlow",6,1,30,0,30);

     // Lepton ID
     muons=GetMuons("POGTightWithTightIso",7.,2.4);
     std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
     electrons=GetElectrons("passMediumID",9.,2.5);
     std::sort(electrons.begin(),electrons.end(),PtComparing);

     IsMuMu = 0;
     IsElEl = 0;
     //=========================
     // DiLepton condition
     //=========================
     if(muons.size() == 2) if(electrons.size() == 0) IsMuMu = 1;
     if(muons.size() == 0) if(electrons.size() == 2) IsElEl = 1;


     if( IsMuMu || IsElEl){
        //=======================================
        // Channel dependent cut and ftn set
        //=======================================
          
        LeptonID_SF  = NULL;
        LeptonISO_SF = NULL;
        LeptonReco_SF= NULL;
        PileUpWeight = NULL;

        if(IsMuMu == 1){ // Muon-----------------------------
          if(evt->PassTrigger(DiMuTrgs) ){
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
          }
        } //---------------------------------------------
        if(IsElEl == 1){ // Electron =======================
          if(evt->PassTrigger(DiElTrgs) ){
             leps=MakeLeptonPointerVector(electrons);
             Lep0PtCut = 25.;
             Lep1PtCut = 15.;
             LepEtaCut = 2.5;
             LeptonID_SF  = &MCCorrection::ElectronID_SF;
             LeptonReco_SF= &MCCorrection::ElectronReco_SF;
             // key for private or official SF
             LeptonID_key     = "MediumID_pt10";
             LeptonID_key_POG = "passMediumID";
             trgSF_key0 = "LeadEle23_MediumID";
             trgSF_key1 = "TailEle12_MediumID";
          }
        } //===========================================


        if( leps.size() == 2 ){ // leps have leptons passing ID and trigger matching
          // ================================
          // Kinematic cuts 
          // ================================
          for(int i(0); i < 2; i++){ // two lepton only, pt eta the same to TnP
            if(leps[i]->LeptonFlavour()==Lepton::MUON){
               Aod_pt[i]=((Muon*)leps.at(i))->MiniAODPt();
               Aod_eta[i]=leps.at(i)->Eta();
            }
	    else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
                    if(fabs(leps.at(i)->Eta())>1.4442&&fabs(leps.at(i)->Eta())<1.566) continue;
                    Aod_pt[i]=leps.at(i)->Pt();
                    Aod_eta[i]=((Electron*)leps.at(i))->scEta();
            }
          }

	  if( Aod_pt[0] > Lep0PtCut && Aod_pt[1] > Lep1PtCut && fabs(Aod_eta[0]) < LepEtaCut && fabs(Aod_eta[1]) < LepEtaCut && (leps.at(0)->Charge() + leps.at(1)->Charge()) == 0 ){
             // 
             ispassRec=1;

             ptRec.push_back(leps.at(0)->Pt());
             ptRec.push_back(leps.at(1)->Pt());
             ptRec.push_back( (*(leps.at(0))+*(leps.at(1))).Pt() );

             mRec.push_back(leps.at(0)->M());
             mRec.push_back(leps.at(1)->M());
             mRec.push_back( (*(leps.at(0))+*(leps.at(1))).M() );
 
             /////////////////PUreweight///////////////////
             PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

             PUweight=1.,PUweight_Up=1.,PUweight_Dn=1.;

             if(!IsDATA){
               PUweight=(mcCorr->*PileUpWeight)(nPileUp,0);
               PUweight_Up=(mcCorr->*PileUpWeight)(nPileUp,1);
               PUweight_Dn=(mcCorr->*PileUpWeight)(nPileUp,-1);
               weightRec *= PUweight;
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

               weightRec *= recoSF;
               weightRec *= IdSF;
               weightRec *= trgSF;
             }

             // b tag test
             //
             //==== Test btagging code
             //==== add taggers and WP that you want to use in analysis
             std::vector<Jet::Tagger> vtaggers;
             vtaggers.push_back(Jet::DeepCSV);

             std::vector<Jet::WP> v_wps;
             v_wps.push_back(Jet::Medium); 

             //=== list of taggers, WP, setup systematics, use period SFs
             SetupBTagger(vtaggers,v_wps, true, false);

             vector<Jet> this_AllJets = GetAllJets();
             vector<Jet> jets = SelectJets(this_AllJets, "tight", 30., 2.4);

             int n_bjet_deepcsv_m=0;
             int n_bjet_deepcsv_m_noSF=0;

             for(unsigned int ij = 0 ; ij < jets.size(); ij++){
               if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,true,0)) n_bjet_deepcsv_m++; // method for getting btag with SF applied to MC
               if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,false,0)) n_bjet_deepcsv_m_noSF++; // method for getting btag with no SF applied to MC
             }

             if(n_bjet_deepcsv_m_noSF == 0) isBveto = 1;

             float btag_sf = 1, misbtag_sf = 1.;
             BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, 0, btag_sf, misbtag_sf);
             if(!IsDATA) bTagReweight = btag_sf * misbtag_sf;
             //std::cout <<"misbtag_sf: " << misbtag_sf << " btag_sf : " << btag_sf << " n bjets (noSF): " << n_bjet_deepcsv_m_noSF << " n bjets: " << n_bjet_deepcsv_m << std::endl;

          } // kinematic cuts on leptons and opposite charge
        } // passing dilepton trigger, how about trigger matching?
     } // two leptons passing ID
  } // pass METfilter 

  newtree->Fill();
}

int Skim_ISRUnfoldInput::findInitialMoterIndex(int motherIndex, int currentIndex, vector<Gen> &gens){

  int initIndex = -1;
  // stop if reach the initial protons
  if( gens.at(currentIndex).PID() == 2212 && gens.at(currentIndex).MotherIndex() == -1){
    std::cout << " initial proton... " << std::endl;
    return -1;
  }
  // stop if mother ID and current ID is different 
  else if(gens.at(motherIndex).PID() != gens.at(currentIndex).PID()){
          return currentIndex;
  }
  else{
       std::cout << " mother index: " << motherIndex << " ID: " << gens.at(motherIndex).PID() <<  " cuurent index: " << currentIndex << " current ID: " << gens.at(currentIndex).PID() << " current isPrompt : " << gens.at(currentIndex).isPrompt() << std::endl; 
       std::cout << "############### call again ######################" << std::endl; 
       initIndex = findInitialMoterIndex(gens.at(motherIndex).MotherIndex(), motherIndex, gens);
  }

  return initIndex;
}


void Skim_ISRUnfoldInput::selectDilepton(vector<Gen> &gens, std::map<int,int> &parIndex, std::map<int,int> &aparIndex, vector<int> &gparticleIndex, vector<int> &gaparticleIndex){

    TLorentzVector initialDilep;
    std::map<int, int>::iterator it = parIndex.begin();
    while(it != parIndex.end())
    {
        TLorentzVector tempDilep;
        std::cout << "particle initial:" << it->first << " particle final: " << it->second << std::endl;

        std::map<int, int>::iterator it_ = aparIndex.begin();
        while(it_ != aparIndex.end()){
              if( gens.at(it->first).MotherIndex() == gens.at(it_->first).MotherIndex()){ // check if the mother of the initial dielectron match 
                 std::cout << "anti Particle initial:" << it_->first << " anti particle final: " << it_->second << std::endl;

                 if(initialDilep.Eta() == 0 && initialDilep.Pt() == 0 && initialDilep.M() == 0){ // check if this is the first time to set the initialDilep
                   initialDilep = (gens.at(it->first)+gens.at(it_->first));
                   std::cout << "initial dilep mass: " << (gens.at(it->first)+gens.at(it_->first)).M() << std::endl;
                   std::cout << "final dilep mass: " << (gens.at(it->second)+gens.at(it_->second)).M() << std::endl;
		   gparticleIndex.push_back(it->first);
		   gparticleIndex.push_back(it->second);

		   gaparticleIndex.push_back(it_->first);
		   gaparticleIndex.push_back(it_->second);
 
                 }
                 else{
                     tempDilep = (gens.at(it->first)+gens.at(it_->first));
                     if(tempDilep.M() > initialDilep.M() ){
                        initialDilep = tempDilep;
                        std::cout << "more than one dilep, mass: " << (gens.at(it->first)+gens.at(it_->first)).M() << std::endl;
                        std::cout << "final dilep mass: " << (gens.at(it->second)+gens.at(it_->second)).M() << std::endl;

                        // replace index with the larger dilepton masa
		        gparticleIndex[0] = it->first;
		        gparticleIndex[1] = it->second;

		        gaparticleIndex[0] = it_->first;
		        gaparticleIndex[1] = it_->second;
                     }
                 }// to save the dielectron pair with largest mass
              }
              it_++;
        }
        it++;
    }

}

void Skim_ISRUnfoldInput::saveMotherIndexMap(vector<Gen> &gens, int currentIndex, int motherIndex, std::map<int,int> &partindexmap){

    if(currentIndex==motherIndex){
       partindexmap.insert(std::make_pair(currentIndex, gens.at(currentIndex).PID()));
    }
    else{
         partindexmap.insert(std::make_pair(currentIndex, gens.at(currentIndex).PID()));
         saveMotherIndexMap(gens, gens.at(currentIndex).MotherIndex(), motherIndex, partindexmap);
    }
}

void Skim_ISRUnfoldInput::executeEventFromParameter(AnalyzerParameter param){

}

Skim_ISRUnfoldInput::Skim_ISRUnfoldInput(){

}

Skim_ISRUnfoldInput::~Skim_ISRUnfoldInput(){

}

void Skim_ISRUnfoldInput::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_ISRUnfoldInput::initializeAnalyzer
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

