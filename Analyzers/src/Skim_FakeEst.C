#include "Skim_FakeEst.h"

void Skim_FakeEst::initializeAnalyzer(){

  initializeAnalyzerTools(); //To use SF

  //=================================
  // Skim Types
  //=================================
   
  debug_ = true;

  if( HasFlag("MuMu")){
    cout<<"[Skim_FakeEst::initializeAnalyzer] MuMu Selection"<<endl;
  }
  else if( HasFlag("ElEl")){
    cout<<"[Skim_FakeEst::initializeAnalyzer] ElEl Selection"<<endl;
  }
  else if( HasFlag("MuMuOrElEl")){
    cout<<"[Skim_FakeEst::initializeAnalyzer] MuMu or ElEl Selection"<<endl;
  }
  else{
    cout <<"[Skim_FakeEst::executeEvent] Not ready for this Flags ";
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
  newtree->Branch("isfiducialPostFSR",&isfiducialPostFSR);
  newtree->Branch("isfiducialPreFSR",&isfiducialPreFSR);
  newtree->Branch("DYtautau",&DYtautau);
  newtree->Branch("isBveto",&isBveto);
  newtree->Branch("isOS",&isOS);
  newtree->Branch("lepIso",&lepIso);

  newtree->Branch("AlphaS",&AlphaS);
  newtree->Branch("Scale",&Scale);

  //b_trgSF = newtree->Branch("trgSF", &trgSF,"trgSF/F");
  //b_trgSF_Up = newtree->Branch("trgSF_Up", &trgSF_Up,"trgSF_Up/F");
  //b_trgSF_Dn = newtree->Branch("trgSF_Dn", &trgSF_Dn,"trgSF_Dn/F");

  // clear vector residual
  DiMuTrgs.clear();
  DiElTrgs.clear();

  cout << "[Skim_FakeEst::initializeAnalyzer] Skim List====================== " << endl;
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
    cout<<"[Skim_FakeEst::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
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

void Skim_FakeEst::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  ptRec.clear();
  mRec.clear();
  ptPreFSR.clear();
  mPreFSR.clear();
  ptPostFSR.clear();
  mPostFSR.clear();

  AlphaS.clear();
  Scale.clear();

  particleFSR.clear();
  anparticleFSR.clear();

  weightGen = 1.;
  weightRec = 1.;
  bTagReweight = 1.;

  ispassRec = 0;
  isfiducialPostFSR = 0;
  isfiducialPreFSR = 0;
  DYtautau = 0;
  isBveto = 0;
  isOS = false;
  lepIso.clear();

  isdielectron = 0;
  isdimuon = 0;

  evt = new Event;
  *evt = GetEvent();

  newtree->SetBranchAddress("IsMuMu",   &IsMuMu);
  newtree->SetBranchAddress("IsElEl",   &IsElEl);

  FillHist("CutFlow",5,1,30,0,30);

  if(!IsDATA){
    //==== weight_norm_1invpb is set to be event weight normalized to 1 pb-1
    //==== So, you have to multiply trigger luminosity
    //==== you can pass trigger names to ev.GetTriggerLumi(), but if you are using unprescaled trigger, simply pass "Full"
    
    weightGen *= weight_norm_1invpb*evt->GetTriggerLumi("Full");
    
    //==== MCweight is +1 or -1. Should be multiplied if you are using e.g., aMC@NLO NLO samples
    weightGen *= evt->MCweight();
    
  }

  ZPtCor = 1;

  if(MCSample.Contains("DYJets") || MCSample.Contains("DYJets10to50_MG")){
    Gen genL0Fsr, genL1Fsr, genL0postFSR, genL1postFSR, genHardL0, genHardL1;
    TLorentzVector genZ, genL0preFSR, genL1preFSR;
    vector<Gen> gens = GetGens();
    vector<Gen> gphotons;

    // Check tau process
    if(debug_) std::cout << "gen loop start..........." << std::endl;
    for( int i(0); i<(int) gens.size(); i++){

      if( !gens.at(i).isPrompt()) continue; // not from hadron, muon, or tau

      if( gens.at(i).isHardProcess()){ // from ME

        if( genHardL0.IsEmpty() && (abs(gens.at(i).PID() ) == 11 || abs(gens.at(i).PID())==13 || abs(gens.at(i).PID())==15)){
          genHardL0 = gens.at(i);
          if(debug_) std::cout << "genHardL0 ID: " << gens.at(i).PID() << " index: " << i << " pt: " << gens.at(i).Pt() << std::endl;
        }else if(!genHardL0.IsEmpty() && gens.at(i).PID() == -genHardL0.PID()){
          genHardL1 = gens.at(i);
          if(debug_) std::cout << "genHardL1 ID: " << gens.at(i).PID() << " index: " << i << " pt: " << gens.at(i).Pt() << std::endl;
          if(abs( genHardL1.PID()) == 11) isdielectron = 1;
          if(abs( genHardL1.PID()) == 13) isdimuon = 1;
          if(abs( genHardL1.PID()) == 15){
            DYtautau = 1;
            //prefix = "tau_";
            break;
          }
        }
      }
    }
  }


  // Filters ====================
  if(PassMETFilter()){ 

     Aod_eta[0] = -999.;
     Aod_eta[1] = -999.;

     FillHist("CutFlow",6,1,30,0,30);

     // Lepton ID
     muons=GetMuons("POGTight",7.,2.4); // Tight ID without isolation
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


        if(IsMuMu && leps.size() == 2){ // leps have leptons passing ID and trigger matching
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

	  if( Aod_pt[0] > Lep0PtCut && Aod_pt[1] > Lep1PtCut && fabs(Aod_eta[0]) < LepEtaCut && fabs(Aod_eta[1]) < LepEtaCut && (*(leps.at(0))+*(leps.at(1))).Pt() < 100){
             // 
             ispassRec=1;
	     Double_t dimass_temp = (*(leps.at(0))+*(leps.at(1))).M(); 
	     Double_t dipt_temp = (*(leps.at(0))+*(leps.at(1))).Pt(); 

             PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

             PUweight=1.;

             if(!IsDATA){
               PUweight=(mcCorr->*PileUpWeight)(nPileUp,0);
               weightRec *= PUweight;
             }

             trgSF    = 1;
             recoSF    = 1;
             IdSF    = 1;

             if(!IsDATA){
               for( int i(0); i<2 ; i++){
                 recoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i],Aod_pt[i],0):1.;
                 IdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],0):1.;
               }
               //cout<<"Skim pt0: "<<leps[0]->Pt()<<endl;
               trgSF      = mcCorr->DiLeptonTrg_SF(trgSF_key0,trgSF_key1,leps,0);

               weightRec *= recoSF;
               weightRec *= IdSF;
               weightRec *= trgSF;
             }


	     if(leps.at(0)->Charge() != leps.at(1)->Charge()) isOS = true; 

	     lepIso.push_back(leps.at(0)->RelIso()); 
	     lepIso.push_back(leps.at(1)->RelIso()); 

	     Double_t iso_abcd = 0.2;
             const int nmassbin=5;
             double massbin[nmassbin+1]={50,65,80,100,200,350};

	     TString prefix = "";
             if(DYtautau && (MCSample.Contains("DYJets") || MCSample.Contains("DYJets10to50_MG"))) prefix = "tautau"; 

	     // just to show
	     if( (fabs(leps.at(0)->RelIso()) < iso_abcd && fabs(leps.at(1)->RelIso()) < iso_abcd)  || (fabs(leps.at(0)->RelIso()) > iso_abcd && fabs(leps.at(1)->RelIso()) > iso_abcd)){
               FillHist(prefix+"ABCD", leps.at(0)->RelIso(), isOS ? 1.5 : 0.5, weightGen*weightRec, 100, 0., 1., 2, 0., 2.);  
	       FillHist(prefix+"ABCD", leps.at(1)->RelIso(), isOS ? 1.5 : 0.5, weightGen*weightRec, 100, 0., 1., 2, 0., 2.);  
               if(fabs(leps.at(0)->RelIso()) < iso_abcd && fabs(leps.at(1)->RelIso()) < iso_abcd && !isOS){
                 FillHist(prefix+"SS_Isolated_dimass",    dimass_temp, weightGen*weightRec, 100, 0., 500.); 
                 if(dimass_temp>50 && dimass_temp<65)   FillHist(prefix+"SS_Isolated_dipt_mass5065",    dipt_temp, weightGen*weightRec, 20, 0., 100.); 
                 if(dimass_temp>65 && dimass_temp<80)   FillHist(prefix+"SS_Isolated_dipt_mass6580",    dipt_temp, weightGen*weightRec, 20, 0., 100.); 
                 if(dimass_temp>80 && dimass_temp<100)  FillHist(prefix+"SS_Isolated_dipt_mass80100",    dipt_temp, weightGen*weightRec, 20, 0., 100.); 
                 if(dimass_temp>100 && dimass_temp<200) FillHist(prefix+"SS_Isolated_dipt_mass100200",    dipt_temp, weightGen*weightRec, 20, 0., 100.); 
                 if(dimass_temp>200 && dimass_temp<350) FillHist(prefix+"SS_Isolated_dipt_mass200350",    dipt_temp, weightGen*weightRec, 20, 0., 100.); 
               }
               if(fabs(leps.at(0)->RelIso()) > iso_abcd && fabs(leps.at(1)->RelIso()) > iso_abcd && !isOS) FillHist(prefix+"SS_NonIsolated_dimass", dimass_temp, weightGen*weightRec, 500, 0., 500.); 
               if(fabs(leps.at(0)->RelIso()) > iso_abcd && fabs(leps.at(1)->RelIso()) > iso_abcd && isOS)  FillHist(prefix+"OS_NonIsolated_dimass", dimass_temp, weightGen*weightRec, 500, 0., 500.); 
             }
	     else{
               FillHist(prefix+"ABCD_", leps.at(0)->RelIso(), isOS ? 1.5 : 0.5, weightGen*weightRec, 100, 0., 1., 2, 0., 2.);  
	       FillHist(prefix+"ABCD_", leps.at(1)->RelIso(), isOS ? 1.5 : 0.5, weightGen*weightRec, 100, 0., 1., 2, 0., 2.);  
             }

	     // scan isolation variable 
             for(int iso_scan = 0; iso_scan < 20; iso_scan++){
	        Double_t iso_abcd_scan = (35 * 0.01) - (iso_scan) * 0.01;
		TString iso_;
	        iso_.Form("0p%d", 35 - iso_scan);

                if( (fabs(leps.at(0)->RelIso()) > 0.15 && fabs(leps.at(1)->RelIso()) > 0.15)){ 

                  // for mass distribution
	          // left region: closer region to signal
                  if( (fabs(leps.at(0)->RelIso()) < iso_abcd_scan && fabs(leps.at(1)->RelIso()) < iso_abcd_scan) ){
                    if(!isOS) FillHist(prefix+"SS_dimass_iso"+iso_+"_left", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                    if(!isOS) FillHist(prefix+"SS_dimass_iso"+iso_+"_left", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                    if(isOS)  FillHist(prefix+"OS_dimass_iso"+iso_+"_left", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                  }
		  // transition region
                  if( (fabs(leps.at(0)->RelIso()) < iso_abcd_scan + 0.015 && fabs(leps.at(0)->RelIso()) > iso_abcd_scan - 0.015) && (fabs(leps.at(1)->RelIso()) < iso_abcd_scan + 0.015 && fabs(leps.at(1)->RelIso()) > iso_abcd_scan - 0.015)){
                    if(!isOS) FillHist(prefix+"SS_dimass_iso"+iso_+"_transfer", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                    if(!isOS) FillHist(prefix+"SS_dimass_iso"+iso_+"_transfer", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                    if(isOS)  FillHist(prefix+"OS_dimass_iso"+iso_+"_transfer", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                  } 

                  if( (fabs(leps.at(0)->RelIso()) > iso_abcd_scan && fabs(leps.at(1)->RelIso()) > iso_abcd_scan) ){
                    if(!isOS) FillHist(prefix+"SS_dimass_iso"+iso_+"_right", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                    if(!isOS) FillHist(prefix+"SS_dimass_iso"+iso_+"_right", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                    if(isOS)  FillHist(prefix+"OS_dimass_iso"+iso_+"_right", dimass_temp, weightGen*weightRec, 100, 0., 500.);
                  } 

		  // for pt distribution
	          for(int imass = 0; imass < nmassbin; imass++){
		      TString mass_low;
	              mass_low.Form("%d", (int)massbin[imass]);
		      TString mass_high;
	              mass_high.Form("%d", (int)massbin[imass+1]);

                     if(dimass_temp > massbin[imass] && dimass_temp < massbin[imass+1]){
                       if( (fabs(leps.at(0)->RelIso()) < iso_abcd_scan && fabs(leps.at(1)->RelIso()) < iso_abcd_scan) ){
                         if(!isOS) FillHist(prefix+"SS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_left", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                         if(!isOS) FillHist(prefix+"SS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_left", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                         if(isOS)  FillHist(prefix+"OS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_left", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                       } 
                       // transition region
                       if( (fabs(leps.at(0)->RelIso()) < iso_abcd_scan + 0.015 && fabs(leps.at(0)->RelIso()) > iso_abcd_scan - 0.015) && (fabs(leps.at(1)->RelIso()) < iso_abcd_scan + 0.015 && fabs(leps.at(1)->RelIso()) > iso_abcd_scan - 0.015)){
                         if(!isOS) FillHist(prefix+"SS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_transfer", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                         if(!isOS) FillHist(prefix+"SS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_transfer", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                         if(isOS)  FillHist(prefix+"OS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_transfer", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                       }

                       if( (fabs(leps.at(0)->RelIso()) > iso_abcd_scan && fabs(leps.at(1)->RelIso()) > iso_abcd_scan) ){
                         if(!isOS) FillHist(prefix+"SS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_right", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                         if(!isOS) FillHist(prefix+"SS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_right", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                         if(isOS)  FillHist(prefix+"OS_dipt_m"+mass_low+mass_high+"_iso"+iso_+"_right", dipt_temp, weightGen*weightRec, 20, 0., 100.);
                       }
                     }
                  }// mass bin loop

	        }// non isolated two leptons: Region C and D
	     }// iso variable loop

             ptRec.push_back(leps.at(0)->Pt());
             ptRec.push_back(leps.at(1)->Pt());
             ptRec.push_back( (*(leps.at(0))+*(leps.at(1))).Pt() );

             mRec.push_back(leps.at(0)->M());
             mRec.push_back(leps.at(1)->M());
             mRec.push_back( (*(leps.at(0))+*(leps.at(1))).M() );
 
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
             if(debug_) std::cout <<"misbtag_sf: " << misbtag_sf << " btag_sf : " << btag_sf << " n bjets (noSF): " << n_bjet_deepcsv_m_noSF << " n bjets: " << n_bjet_deepcsv_m << std::endl;

          } // kinematic cuts on leptons and opposite charge
        } // passing dilepton trigger, how about trigger matching?
     } // two leptons passing ID
  } // pass METfilter 

  newtree->Fill();
}

int Skim_FakeEst::findInitialMoterIndex(int motherIndex, int currentIndex, vector<Gen> &gens){

  int initIndex = -1;
  // stop if reach the initial protons
  if( gens.at(currentIndex).PID() == 2212 && gens.at(currentIndex).MotherIndex() == -1){
    if(debug_) std::cout << " initial proton... " << std::endl;
    return -1;
  }
  // stop if mother ID and current ID is different 
  else if(gens.at(motherIndex).PID() != gens.at(currentIndex).PID()){
          return currentIndex;
  }
  else{
       if(debug_) std::cout << " mother index: " << motherIndex << " ID: " << gens.at(motherIndex).PID() <<  " cuurent index: " << currentIndex << " current ID: " << gens.at(currentIndex).PID() << " current isPrompt : " << gens.at(currentIndex).isPrompt() << std::endl; 
       if(debug_) std::cout << "############### call again ######################" << std::endl; 
       initIndex = findInitialMoterIndex(gens.at(motherIndex).MotherIndex(), motherIndex, gens);
  }

  return initIndex;
}


void Skim_FakeEst::selectDilepton(vector<Gen> &gens, std::map<int,int> &parIndex, std::map<int,int> &aparIndex, vector<int> &gparticleIndex, vector<int> &gaparticleIndex){

    TLorentzVector initialDilep;
    std::map<int, int>::iterator it = parIndex.begin();
    while(it != parIndex.end())
    {
        TLorentzVector tempDilep;
        if(debug_) std::cout << "particle initial:" << it->first << " particle final: " << it->second << std::endl;

        std::map<int, int>::iterator it_ = aparIndex.begin();
        while(it_ != aparIndex.end()){
              if( gens.at(it->first).MotherIndex() == gens.at(it_->first).MotherIndex()){ // check if the mother of the initial dielectron match 
                 if(debug_) std::cout << "anti Particle initial:" << it_->first << " anti particle final: " << it_->second << std::endl;

                 if(initialDilep.Eta() == 0 && initialDilep.Pt() == 0 && initialDilep.M() == 0){ // check if this is the first time to set the initialDilep
                   initialDilep = (gens.at(it->first)+gens.at(it_->first));
                   if(debug_) std::cout << "initial dilep mass: " << (gens.at(it->first)+gens.at(it_->first)).M() << std::endl;
                   if(debug_) std::cout << "final dilep mass: " << (gens.at(it->second)+gens.at(it_->second)).M() << std::endl;
		   gparticleIndex.push_back(it->first);
		   gparticleIndex.push_back(it->second);

		   gaparticleIndex.push_back(it_->first);
		   gaparticleIndex.push_back(it_->second);
 
                 }
                 else{
                     tempDilep = (gens.at(it->first)+gens.at(it_->first));
                     if(tempDilep.M() > initialDilep.M() ){
                        initialDilep = tempDilep;
                        if(debug_) std::cout << "more than one dilep, mass: " << (gens.at(it->first)+gens.at(it_->first)).M() << std::endl;
                        if(debug_) std::cout << "final dilep mass: " << (gens.at(it->second)+gens.at(it_->second)).M() << std::endl;

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

void Skim_FakeEst::saveMotherIndexMap(vector<Gen> &gens, int currentIndex, int motherIndex, std::map<int,int> &partindexmap){

    if(currentIndex==motherIndex){
       partindexmap.insert(std::make_pair(currentIndex, gens.at(currentIndex).PID()));
    }
    else{
         partindexmap.insert(std::make_pair(currentIndex, gens.at(currentIndex).PID()));
         saveMotherIndexMap(gens, gens.at(currentIndex).MotherIndex(), motherIndex, partindexmap);
    }
}

void Skim_FakeEst::executeEventFromParameter(AnalyzerParameter param){

}

Skim_FakeEst::Skim_FakeEst(){

}

Skim_FakeEst::~Skim_FakeEst(){

}

void Skim_FakeEst::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_FakeEst::initializeAnalyzer
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

