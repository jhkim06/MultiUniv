#include "Skim_ISR.h"

void Skim_ISR::initializeAnalyzer(){
    
    //=================================
    // Skim Types
    //=================================
     
    debug_ = false;
    if( HasFlag("ISR")){
      cout<<"[Skim_ISR::initializeAnalyzer] "<<endl;
    }
    else{
      cout <<"[Skim_ISR::executeEvent] Not ready for this Flags ";
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
    // branches below include which might be better to be handled in varialbe skim later
    newtree->Branch("dilep_pt_rec", &dilep_pt_rec,"dilep_pt_rec/D");
    newtree->Branch("dilep_mass_rec", &dilep_mass_rec,"dilep_mass_rec/D");
    newtree->Branch("leadinglep_pt_rec", &leadinglep_pt_rec,"leadinglep_pt_rec/D");
    newtree->Branch("subleadinglep_pt_rec", &subleadinglep_pt_rec,"subleadinglep_pt_rec/D");
    newtree->Branch("leadinglep_eta_rec", &leadinglep_eta_rec,"leadinglep_eta_rec/D");
    newtree->Branch("subleadinglep_eta_rec", &subleadinglep_eta_rec,"subleadinglep_eta_rec/D");

    // branches for photon for FSR study but seems "slimmedPhotons" has Et > 10 GeV cut
    // so need to use PFPhotons which is not available in the current SKFlat 
    newtree->Branch("dilep_photon_mass_rec", &dilep_photon_mass_rec,"dilep_photon_mass_rec/D");
    newtree->Branch("photon_n_rec", &photon_n_rec,"photon_n_rec/I");
    newtree->Branch("leadingphoton_pt_rec", &leadingphoton_pt_rec,"leadingphoton_pt_rec/D");
    newtree->Branch("leadingphoton_eta_rec", &leadingphoton_eta_rec,"leadingphoton_eta_rec/D");
    newtree->Branch("leadingphoton_lepton_dr_rec", &leadingphoton_lepton_dr_rec,"leadingphoton_lepton_dr_rec/D");

    newtree->Branch("evt_weight_total_gen", &evt_weight_total_gen,"evt_weight_total_gen/D");
    newtree->Branch("evt_weight_total_rec", &evt_weight_total_rec,"evt_weight_total_rec/D");

    // branches for analysis selection tags
    // tags at reconstruction level
    newtree->Branch("evt_tag_dielectron_rec", &evt_tag_dielectron_rec,"evt_tag_dielectron_rec/O");
    newtree->Branch("evt_tag_dimuon_rec", &evt_tag_dimuon_rec,"evt_tag_dimuon_rec/O");
    newtree->Branch("evt_tag_leptonpt_sel_rec", &evt_tag_leptonpt_sel_rec,"evt_tag_leptonpt_sel_rec/O");
    newtree->Branch("evt_tag_leptoneta_sel_rec", &evt_tag_leptoneta_sel_rec,"evt_tag_leptoneta_sel_rec/O");
    newtree->Branch("evt_tag_oppositecharge_sel_rec", &evt_tag_oppositecharge_sel_rec,"evt_tag_oppositecharge_sel_rec/O");
    newtree->Branch("evt_tag_analysisevnt_sel_rec", &evt_tag_analysisevnt_sel_rec,"evt_tag_analysisevnt_sel_rec/O");

    newtree->Branch("evt_tag_ditau_gen", &evt_tag_ditau_gen,"evt_tag_ditau_gen/O");
    newtree->Branch("evt_tag_dielectron_gen", &evt_tag_dielectron_gen,"evt_tag_dielectron_gen/O");
    newtree->Branch("evt_tag_dimuon_gen", &evt_tag_dimuon_gen,"evt_tag_dimuon_gen/O");


    newtree->Branch("evt_tag_bvetoed_rec", &evt_tag_bvetoed_rec,"evt_tag_bvetoed_rec/O");

    // clear vector residual
    DiMuTrgs.clear();
    DiElTrgs.clear();

    cout << "[Skim_ISR::initializeAnalyzer] Skim List====================== " << endl;
    if(DataYear==2016){
        
        DiMuTrgs = {
          "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
          "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
          "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v", // need to estimate the trg eff
          "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
          "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
          "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", // need to estimate the trg eff
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
    else if(DataYear==2018){
        DiMuTrgs = {
          "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v",
        };
        DiElTrgs = {
          "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"
        };
    }
    else{
        cout<<"[Skim_ISR::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
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

void Skim_ISR::executeEvent(){
        
    muons.clear();
    electrons.clear();
    photons.clear();
    leps.clear();

    dilep_pt_rec = -999.;
    dilep_mass_rec = -999.;
    dilep_photon_mass_rec = -999.;
    leadinglep_pt_rec = -999.;
    subleadinglep_pt_rec = -999.;
    leadinglep_eta_rec = -999.;
    subleadinglep_eta_rec = -999.;

    photon_n_rec = 0;
    leadingphoton_pt_rec = -999.;
    leadingphoton_eta_rec = -999.;
    leadingphoton_lepton_dr_rec = -999.;

    evt_weight_total_gen = 1.;
    evt_weight_total_rec = 1.;
    evt_weight_btag_rec = 1.;
  
    evt_tag_leptonpt_sel_rec = 0;
    evt_tag_leptoneta_sel_rec = 0;
    evt_tag_oppositecharge_sel_rec = 0;
    evt_tag_analysisevnt_sel_rec = 0;

    evt_tag_ditau_gen = 0;
    evt_tag_dielectron_gen = 0;
    evt_tag_dimuon_gen = 0;
    evt_tag_dielectron_rec = 0;
    evt_tag_dimuon_rec = 0;
    evt_tag_bvetoed_rec = 0;
  
    evt = new Event;
    *evt = GetEvent();
  
    FillHist("CutFlow",5,1,30,0,30);

    if(!IsDATA){
        
        evt_weight_total_gen *= weight_norm_1invpb*evt->GetTriggerLumi("Full");
        evt_weight_total_gen *= evt->MCweight();
    }

    ///////////////////////////////////// generator level, only for Drell-Yan MC
    if(MCSample.Contains("DYJets")){
        if(debug_) cout << "Generator information for " + MCSample << endl;
        gen_particles.clear();
        gen_photons.clear();

        gen_particles = GetGens();

        bool gen_lepton_from_hardprocess_found = false;
        int first_lepton_id_found_in_ME = 0;
        gen_particle_index_ME         = -1;
        gen_antiparticle_index_ME     = -1;
        gen_particle_index_status1    = -1;
        gen_antiparticle_index_status1 = -1;

        // loop over generator particles
        for( unsigned int i = 0; i < gen_particles.size(); i++){

            if(debug_){
                if(gen_particles.at(i).Status() == 1)
                    std::cout << i << "\033[1;31m pid: " << gen_particles.at(i).PID() << " mother index: " << gen_particles.at(i).MotherIndex() 
                              << " status: " << gen_particles.at(i).Status() << " isPrompt: " << gen_particles.at(i).isPrompt() << " isHardProcess: " << gen_particles.at(i).isHardProcess() << "\033[0m" << std::endl;

                else std::cout << i << " pid: " << gen_particles.at(i).PID() << " mother index: " << gen_particles.at(i).MotherIndex() 
                               << " status: " << gen_particles.at(i).Status() << " isPrompt: " << gen_particles.at(i).isPrompt() << " isHardProcess: " << gen_particles.at(i).isHardProcess() << std::endl;
            }
            int current_particle_id = gen_particles.at(i).PID();
            // particles associated matrix element (ME)
            if(gen_particles.at(i).isHardProcess()){ 
                if( (abs(current_particle_id) == 11 || abs(current_particle_id)==13 || abs(current_particle_id)==15 )){
                    // first lepton from ME
                    if(gen_lepton_from_hardprocess_found == false){
                        if(abs(current_particle_id) == 15){
                            evt_tag_ditau_gen = 1;  
                            // no further information needed for tautau case
                            break;
                        }

                        gen_lepton_from_hardprocess_found = true;
                        if(abs(current_particle_id) == 11){ 
                            evt_tag_dielectron_gen = 1;    
                            first_lepton_id_found_in_ME = current_particle_id;
                        }
                        if(abs(current_particle_id) == 13){ 
                            evt_tag_dimuon_gen = 1;    
                            first_lepton_id_found_in_ME = current_particle_id;
                        }

                        // save index
                        if(current_particle_id > 0){
                            gen_particle_index_ME = i;
                            gen_particle_ME = gen_particles.at(i);
                        }
                        else{
                            gen_antiparticle_index_ME = i;
                            gen_antiparticle_ME = gen_particles.at(i);
                        }

                    }
                    // second lepton from ME
                    else{ 
                        if( current_particle_id == -first_lepton_id_found_in_ME ){

                            if(current_particle_id > 0){
                                gen_particle_index_ME = i;
                                gen_particle_ME = gen_particles.at(i);
                            }
                            else{               
                                gen_antiparticle_index_ME = i;
                                gen_antiparticle_ME = gen_particles.at(i);
                            }

                        }// found OS dilepton from ME
                    }
                }// electron, muon, tau in ME
            }// ME 

            // collect status 1 particles with their mother index
            if(gen_particles.at(i).Status() == 1){
                int id_found_in_ME = 0; 

                // photon
                if(current_particle_id==22){
                    gen_photons.push_back(gen_particles.at(i));
                }

                if( abs(current_particle_id) == 11 || abs(current_particle_id)==13 ){
                    if(evt_tag_dielectron_gen){
                        id_found_in_ME = 11;
                    }
                    if(evt_tag_dimuon_gen){
                        id_found_in_ME = 13;
                    }
                 
                    // lepton not found yet in ME, so just skip current particle...   
                    // since no chance that current status 1 particle from leptons from ME
                    // but there should be no such case 
                    if(id_found_in_ME == 0) continue;                    

                    // find the initial index of the lepton (status 1 and prompt)
                    // do this since there are cases
                    // not from hardprocess leptons and stil status 1 
                    int initial_index = findInitialMoterIndex( gen_particles.at(i).MotherIndex(), i);
                    if(current_particle_id==id_found_in_ME && initial_index == gen_particle_index_ME){
                        gen_particle_status1 = gen_particles.at(i);
                        gen_particle_index_status1 = i;
                    }
                    if(current_particle_id==-id_found_in_ME && initial_index == gen_antiparticle_index_ME){
                        gen_antiparticle_status1 = gen_particles.at(i);
                        gen_antiparticle_index_status1 = i;
                    }
                }

            }// status 1 particles

        }// gen particle loop

        // basic check for the selected dilpton pairs
        if(!evt_tag_ditau_gen){
            if( gen_particles.at(gen_particle_index_ME).PID() != gen_particles.at(gen_particle_index_status1).PID() || gen_particles.at(gen_antiparticle_index_ME).PID() != gen_particles.at(gen_antiparticle_index_status1).PID()){
                cout << "dilepton pair not selected properly..." << endl; 
                exit(EXIT_FAILURE);
            }
        }
        if(debug_){
            if(evt_tag_dielectron_gen){
                cout << "DY->ee event..." << endl;
            }
            if(evt_tag_dimuon_gen){
                cout << "DY->mumu event..." << endl;
            }
            if(evt_tag_ditau_gen){
                cout << "DY->tautau event..." << endl;
            }
            // check further info for dielectron and dimuon events 
            if(!evt_tag_ditau_gen){
                cout << "Leptons from hardprocess" << endl;
                cout << "Lepton 1: " << endl;
                cout << "ID: " << gen_particles.at(gen_particle_index_ME).PID() << " index: " << gen_particle_index_ME << endl; 
                cout << "Lepton 2: " << endl;
                cout << "ID: " << gen_particles.at(gen_antiparticle_index_ME).PID() << " index: " << gen_antiparticle_index_ME << endl; 

                cout << endl;
                cout << "\033[1;31mStatus 1 leptons\033[0m" << endl;
                cout << "status 1 particles..." << endl; 
                cout << "particle index: " << gen_particle_index_status1 << " anti-particle index: " << gen_antiparticle_index_status1 << endl;;
            }
        }
    }/////////////////////////////////////////////////////////////////// generator level

    // reconstruction level
    if(PassMETFilter()){ 

        FillHist("CutFlow",6,1,30,0,30);
        
        // Lepton ID
        muons = GetMuons("POGTightWithTightIso", 7., 2.4);
        electrons = GetElectrons("passMediumID", 9., 2.5);
        photons = GetPhotons("passMediumID", 0.5, 2.5, true); // last boolean is for checkPixelSeed
        std::sort(muons.begin(), muons.end(), PtComparing); 
        std::sort(electrons.begin(), electrons.end(), PtComparing);
        std::sort(photons.begin(), photons.end(), PtComparing);

        IsMuMu = 0;
        IsElEl = 0;

        //if(muons.size() == 2) if(electrons.size() == 0) IsMuMu = 1;
        //if(muons.size() == 0) if(electrons.size() == 2) IsElEl = 1;

        if(muons.size() == 2) IsMuMu = 1;
        if(electrons.size() == 2) IsElEl = 1;
         
        if(IsMuMu || IsElEl){
            if(IsMuMu == 1){ 
                
                if(evt->PassTrigger(DiMuTrgs) ){
                      leps=MakeLeptonPointerVector(muons);
                      evt_tag_dimuon_rec = 1;
                      Lep0PtCut = 20.;
                      Lep1PtCut = 10.;
                      LepEtaCut = 2.4;
                }
            } 
            if(IsElEl == 1){ 
                if(evt->PassTrigger(DiElTrgs) ){
                    leps=MakeLeptonPointerVector(electrons);
                    evt_tag_dielectron_rec = 1;
                    Lep0PtCut = 25.;
                    Lep1PtCut = 15.;
                    LepEtaCut = 2.5;
                }
            } 

            if( leps.size() == 2 ){ // leps have leptons passing ID and trigger passed

                // lepton pt cut requirement
                if(leps.at(0)->Pt() > Lep0PtCut && leps.at(1)->Pt() > Lep1PtCut) evt_tag_leptonpt_sel_rec = 1;

                // lepton eta cut requirement
                if(fabs(leps.at(0)->Eta()) < LepEtaCut && fabs(leps.at(1)->Eta()) < LepEtaCut){ 
                    if(IsMuMu == 1){
                            evt_tag_leptoneta_sel_rec = 1;
                    }
                    if(IsElEl == 1){
                        if((fabs(leps.at(0)->Eta()) < 1.4442 || fabs(leps.at(0)->Eta()) > 1.566) && (fabs(leps.at(1)->Eta()) < 1.4442 || fabs(leps.at(1)->Eta()) > 1.566)) 
                            evt_tag_leptoneta_sel_rec = 1;
                    }
                }
                
                // opposite charge requirements
                if((leps.at(0)->Charge() + leps.at(1)->Charge()) == 0) evt_tag_oppositecharge_sel_rec = 1;

                if(evt_tag_leptonpt_sel_rec && evt_tag_leptoneta_sel_rec && evt_tag_leptoneta_sel_rec && evt_tag_oppositecharge_sel_rec) evt_tag_analysisevnt_sel_rec = 1;

                leadinglep_pt_rec = leps.at(0)->Pt();
                subleadinglep_pt_rec = leps.at(1)->Pt();
                leadinglep_eta_rec = leps.at(0)->Eta();
                subleadinglep_eta_rec = leps.at(1)->Eta();
                dilep_pt_rec = (*(leps.at(0))+*(leps.at(1))).Pt();
                dilep_mass_rec = (*(leps.at(0))+*(leps.at(1))).M();

                // check if there are photons passing required ID
                int photon_size = photons.size();
                bool leading_photon_found = false;
                for(int iphoton = 0; iphoton < photon_size; iphoton++){
                    photon_n_rec++;

                    if(leading_photon_found == false){
                        leading_photon_found = true;
                        dilep_photon_mass_rec = ( *(leps.at(0)) + *(leps.at(1)) + photons.at(iphoton)).M();
                        leadingphoton_pt_rec = photons.at(iphoton).Pt();
                        leadingphoton_eta_rec = photons.at(iphoton).Eta();

                        double dr_leadinglep = leps.at(0)->DeltaR(photons.at(iphoton));
                        double dr_subleadinglep = leps.at(1)->DeltaR(photons.at(iphoton));
                        // save closest deltaR between lepton and photon
                        leadingphoton_lepton_dr_rec = dr_leadinglep > dr_subleadinglep ? dr_subleadinglep : dr_leadinglep;  
                    }
                }

                PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

                PUweight=1.,PUweight_Up=1.,PUweight_Dn=1.;

                if(!IsDATA){
                  PUweight=(mcCorr->*PileUpWeight)(nPileUp,0);
                  PUweight_Up=(mcCorr->*PileUpWeight)(nPileUp,1);
                  PUweight_Dn=(mcCorr->*PileUpWeight)(nPileUp,-1);
                  evt_weight_total_rec *= PUweight;
                }

                L1Prefire =1, L1Prefire_Up =1, L1Prefire_Dn =1;

                if(!IsDATA){
                  if(DataYear<=2017){
                    evt_weight_total_rec *= L1PrefireReweight_Central;
                    L1Prefire = L1PrefireReweight_Central;
                    L1Prefire_Up = L1PrefireReweight_Up;
                    L1Prefire_Dn = L1PrefireReweight_Down;
                  }
                }

                // b tag 
                std::vector<Jet::Tagger> vtaggers;
                vtaggers.push_back(Jet::DeepCSV);

                std::vector<Jet::WP> v_wps;
                v_wps.push_back(Jet::Medium); 

                SetupBTagger(vtaggers,v_wps, true, false);

                vector<Jet> this_AllJets = GetAllJets();
                vector<Jet> jets = SelectJets(this_AllJets, "tight", 30., 2.4);

                int n_bjet_deepcsv_m=0;
                int n_bjet_deepcsv_m_noSF=0;

                for(unsigned int ij = 0 ; ij < jets.size(); ij++){
                  if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,true,0)) n_bjet_deepcsv_m++; // method for getting btag with SF applied to MC
                  if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,false,0)) n_bjet_deepcsv_m_noSF++; // method for getting btag with no SF applied to MC
                }

                 if(n_bjet_deepcsv_m_noSF == 0) evt_tag_bvetoed_rec = 1;

                 float btag_sf = 1, misbtag_sf = 1.;
                 BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, 0, btag_sf, misbtag_sf);
                 if(!IsDATA) evt_weight_total_rec = btag_sf * misbtag_sf;
                 if(debug_) std::cout <<"misbtag_sf: " << misbtag_sf << " btag_sf : " << btag_sf << " n bjets (noSF): " << n_bjet_deepcsv_m_noSF << " n bjets: " << n_bjet_deepcsv_m << std::endl;

            } // passing dilepton trigger (dont need trigger matching?)
        } // two leptons passing ID
    } // pass METfilter 

  newtree->Fill();

  delete evt;
}

void Skim_ISR::executeEventFromParameter(AnalyzerParameter param){

}

int Skim_ISR::findInitialMoterIndex(int mother_index, int current_index, bool same_flavor){
    
    int init_index = -1;
    // stop if reached te initial protons
    if( fabs(gen_particles.at(current_index).PID()) == 2212 && gen_particles.at(current_index).MotherIndex() == -1){
      return -1;
    }
    // stop if mother ID and current ID is different 
    else if((gen_particles.at(mother_index).PID() != gen_particles.at(current_index).PID()) && same_flavor){
            return current_index;
    }
    else{
        // call again
        init_index = findInitialMoterIndex(gen_particles.at(mother_index).MotherIndex(), mother_index);
    }

    return init_index;
}

Skim_ISR::Skim_ISR(){

}

Skim_ISR::~Skim_ISR(){

}

void Skim_ISR::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_ISR::initializeAnalyzer
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

