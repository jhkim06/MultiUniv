#include "Skim_ISR.h"

void Skim_ISR::initializeAnalyzer(){
    
    //=================================
    // Skim Types
    //=================================
     
    debug_ = false;
    if( HasFlag("ISR_detector_only")){
        save_detector_info = true;
        save_generator_info = false;
    }
    else if (HasFlag("ISR_generator_only")){
        save_detector_info = false;
        save_generator_info = true;
    }
    else if (HasFlag("ISR")){
        save_detector_info = true;
        save_generator_info = true;
    }
    // add options: only generator level
    //
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

    newtree->Branch("evt_weight_total_gen", &evt_weight_total_gen,"evt_weight_total_gen/D");

    if(save_detector_info){
        // New Branch
        // branches below include which might be better to be handled in varialbe skim later
        newtree->Branch("dilep_pt_rec", &dilep_pt_rec,"dilep_pt_rec/D");
        newtree->Branch("dilep_mass_rec", &dilep_mass_rec,"dilep_mass_rec/D");
        newtree->Branch("leadinglep_pt_rec", &leadinglep_pt_rec,"leadinglep_pt_rec/D");
        newtree->Branch("subleadinglep_pt_rec", &subleadinglep_pt_rec,"subleadinglep_pt_rec/D");
        newtree->Branch("leadinglep_eta_rec", &leadinglep_eta_rec,"leadinglep_eta_rec/D");
        newtree->Branch("subleadinglep_eta_rec", &subleadinglep_eta_rec,"subleadinglep_eta_rec/D");
        newtree->Branch("leadingmuon_reliso_rec", &leadingmuon_reliso_rec,"leadingmuon_reliso_rec/D");
        newtree->Branch("subleadingmuon_reliso_rec", &subleadingmuon_reliso_rec,"subleadingmuon_reliso_rec/D");

        // branches for photon for FSR study but seems "slimmedPhotons" has Et > 10 GeV cut
        // so need to use PFPhotons which is not available in the current SKFlat 
        newtree->Branch("dilep_photon_mass_rec", &dilep_photon_mass_rec,"dilep_photon_mass_rec/D");
        newtree->Branch("photon_n_rec", &photon_n_rec,"photon_n_rec/I");
        newtree->Branch("leadingphoton_pt_rec", &leadingphoton_pt_rec,"leadingphoton_pt_rec/D");
        newtree->Branch("leadingphoton_eta_rec", &leadingphoton_eta_rec,"leadingphoton_eta_rec/D");
        newtree->Branch("leadingphoton_lepton_dr_rec", &leadingphoton_lepton_dr_rec,"leadingphoton_lepton_dr_rec/D");

        newtree->Branch("evt_weight_total_rec", &evt_weight_total_rec,"evt_weight_total_rec/D");
        newtree->Branch("evt_weight_fake", &evt_weight_fake,"evt_weight_fake/D");

        newtree->Branch("evt_weight_pureweight", &evt_weight_pureweight,"evt_weight_pureweight/D");
        newtree->Branch("evt_weight_pureweight_up", &evt_weight_pureweight_up,"evt_weight_pureweight_up/D");
        newtree->Branch("evt_weight_pureweight_down", &evt_weight_pureweight_down,"evt_weight_pureweight_down/D");
        newtree->Branch("evt_weight_l1prefire", &evt_weight_l1prefire,"evt_weight_l1prefire/D");
        newtree->Branch("evt_weight_l1prefire_up", &evt_weight_l1prefire_up,"evt_weight_l1prefire_up/D");
        newtree->Branch("evt_weight_l1prefire_down", &evt_weight_l1prefire_down, "evt_weight_l1prefire_down/D");
        newtree->Branch("evt_weight_bveto", &evt_weight_bveto,"evt_weight_bveto/D");
        newtree->Branch("evt_weight_bveto_up", &evt_weight_bveto_up,"evt_weight_bveto_up/D");
        newtree->Branch("evt_weight_bveto_down", &evt_weight_bveto_down,"evt_weight_bveto_down/D");

        // branches for analysis selection tags
        // tags at reconstruction level
        newtree->Branch("evt_tag_dielectron_rec", &evt_tag_dielectron_rec,"evt_tag_dielectron_rec/O");
        newtree->Branch("evt_tag_dimuon_rec", &evt_tag_dimuon_rec,"evt_tag_dimuon_rec/O");
        newtree->Branch("evt_tag_leptonpt_sel_rec", &evt_tag_leptonpt_sel_rec,"evt_tag_leptonpt_sel_rec/O");
        newtree->Branch("evt_tag_leptoneta_sel_rec", &evt_tag_leptoneta_sel_rec,"evt_tag_leptoneta_sel_rec/O");
        newtree->Branch("evt_tag_oppositecharge_sel_rec", &evt_tag_oppositecharge_sel_rec,"evt_tag_oppositecharge_sel_rec/O");
        newtree->Branch("evt_tag_analysisevnt_sel_rec", &evt_tag_analysisevnt_sel_rec,"evt_tag_analysisevnt_sel_rec/O");

        newtree->Branch("evt_tag_bvetoed_rec", &evt_tag_bvetoed_rec,"evt_tag_bvetoed_rec/O");

        newtree->Branch("gen_rec_evt_matched", &gen_rec_evt_matched,"gen_rec_evt_matched/O");
        newtree->Branch("gen_rec_lepton_dR", &gen_rec_lepton_dR);

        // temporary tree to study QED FSR at detector level
        Dimu_map["POGTight"] = new Dimu_variables("POGTight");
        Dimu_map["POGTight"]->setBranch(newtree);

        Dimu_map["POGTightWithRelIsoNoPH"] = new Dimu_variables("POGTightWithRelIsoNoPH");
        Dimu_map["POGTightWithRelIsoNoPH"]->setBranch(newtree);

        Dimu_map["POGTightWithRelIsoNoPHCH"] = new Dimu_variables("POGTightWithRelIsoNoPHCH");
        Dimu_map["POGTightWithRelIsoNoPHCH"]->setBranch(newtree);

        fake_estimation = new ISR_LeptonIDVariation("HNLoose", "ISRLoose", "Fake");
        fake_estimation->setBranch(newtree);
    }


    if(save_generator_info){
        // gen info
        newtree->Branch("evt_tag_ditau_gen", &evt_tag_ditau_gen,"evt_tag_ditau_gen/O");
        newtree->Branch("evt_tag_dielectron_gen", &evt_tag_dielectron_gen,"evt_tag_dielectron_gen/O");
        newtree->Branch("evt_tag_dimuon_gen", &evt_tag_dimuon_gen,"evt_tag_dimuon_gen/O");

        newtree->Branch("photon_n_gen", &photon_n_gen,"photon_n_gen/I");
        newtree->Branch("lepton_matched_photon_n_gen", &lepton_matched_photon_n_gen,"lepton_matched_photon_n_gen/I");
        newtree->Branch("lepton_matched_photon_et_gen_drX", &lepton_matched_photon_et_gen_drX);
        newtree->Branch("evt_tag_dielectron_fiducial_post_fsr", &evt_tag_dielectron_fiducial_post_fsr,"evt_tag_dielectron_fiducial_post_fsr/O");
        newtree->Branch("evt_tag_dimuon_fiducial_post_fsr", &evt_tag_dimuon_fiducial_post_fsr,"evt_tag_dimuon_fiducial_post_fsr/O");

        newtree->Branch("evt_tag_dielectron_fiducial_lepton_matched_dressed_drX", &evt_tag_dielectron_fiducial_lepton_matched_dressed_drX);
        newtree->Branch("evt_tag_dimuon_fiducial_lepton_matched_dressed_drX", &evt_tag_dimuon_fiducial_lepton_matched_dressed_drX);

        newtree->Branch("mother_id_of_prefsr_dilep", &mother_id_of_prefsr_dilep,"mother_id_of_prefsr_dilep/I");
        newtree->Branch("dilep_pt_gen_prefsr", &dilep_pt_gen_prefsr,"dilep_pt_gen_prefsr/D");
        newtree->Branch("dilep_mass_gen_prefsr", &dilep_mass_gen_prefsr,"dilep_mass_gen_prefsr/D");
        newtree->Branch("particle_pt_gen_prefsr", &particle_pt_gen_prefsr,"particle_pt_gen_prefsr/D");
        newtree->Branch("antiparticle_pt_gen_prefsr", &antiparticle_pt_gen_prefsr,"antiparticle_pt_gen_prefsr/D");
        newtree->Branch("particle_eta_gen_prefsr", &particle_eta_gen_prefsr,"particle_eta_gen_prefsr/D");
        newtree->Branch("antiparticle_eta_gen_prefsr", &antiparticle_eta_gen_prefsr,"antiparticle_eta_gen_prefsr/D");

        newtree->Branch("dilep_pt_gen_postfsr", &dilep_pt_gen_postfsr,"dilep_pt_gen_postfsr/D");
        newtree->Branch("dilep_mass_gen_postfsr", &dilep_mass_gen_postfsr,"dilep_mass_gen_postfsr/D");
        newtree->Branch("particle_pt_gen_postfsr", &particle_pt_gen_postfsr,"particle_pt_gen_postfsr/D");
        newtree->Branch("antiparticle_pt_gen_postfsr", &antiparticle_pt_gen_postfsr,"antiparticle_pt_gen_postfsr/D");
        newtree->Branch("particle_eta_gen_postfsr", &particle_eta_gen_postfsr,"particle_eta_gen_postfsr/D");
        newtree->Branch("antiparticle_eta_gen_postfsr", &antiparticle_eta_gen_postfsr,"antiparticle_eta_gen_postfsr/D");

        newtree->Branch("dilep_pt_gen_dressed_drX",&dilep_pt_gen_dressed_drX);
        newtree->Branch("dilep_mass_gen_dressed_drX",&dilep_mass_gen_dressed_drX);
        newtree->Branch("drX_gen_dressed",&drX_gen_dressed);
        newtree->Branch("dilep_pt_gen_lepton_matched_dressed_drX",&dilep_pt_gen_lepton_matched_dressed_drX);
        newtree->Branch("dilep_mass_gen_lepton_matched_dressed_drX",&dilep_mass_gen_lepton_matched_dressed_drX);
        newtree->Branch("drX_gen_lepton_matched_dressed",&drX_gen_lepton_matched_dressed); // actually redundant

        newtree->Branch("photons_et_gen",&photons_et_gen);
        newtree->Branch("photons_mother_id_gen",&photons_mother_id_gen);
        newtree->Branch("photons_closest_dr_to_leptons_gen",&photons_closest_dr_to_leptons_gen);
        newtree->Branch("lepton_matched_photons_closest_dr_to_leptons_gen",&lepton_matched_photons_closest_dr_to_leptons_gen);
    }

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

    AllMuons.clear();        
    AllElectrons.clear();        
    muons.clear();
    electrons.clear();
    photons.clear();
    leps.clear();
    leptons_postfsr.clear();

    gen_rec_lepton_dR.clear();
    gen_rec_evt_matched = false;

    dilep_pt_rec          = -999.;
    dilep_mass_rec        = -999.;
    dilep_photon_mass_rec = -999.;
    leadinglep_pt_rec     = -999.;
    subleadinglep_pt_rec  = -999.;
    leadinglep_eta_rec    = -999.;
    subleadinglep_eta_rec = -999.;
    leadingmuon_reliso_rec = -999.;
    subleadingmuon_reliso_rec = -999.;

    mother_id_of_prefsr_dilep = -999;

    dilep_pt_gen_prefsr   = -999.;
    dilep_mass_gen_prefsr = -999.;
    particle_pt_gen_prefsr     = -999.;
    antiparticle_pt_gen_prefsr     = -999.;
    particle_eta_gen_prefsr     = -999.;
    antiparticle_eta_gen_prefsr     = -999.;

    dilep_pt_gen_postfsr   = -999.;
    dilep_mass_gen_postfsr = -999.;
    particle_pt_gen_postfsr     = -999.;
    antiparticle_pt_gen_postfsr     = -999.;
    particle_eta_gen_postfsr     = -999.;
    antiparticle_eta_gen_postfsr     = -999.;

    dilep_pt_gen_dressed_drX.clear();
    dilep_mass_gen_dressed_drX.clear();
    drX_gen_dressed.clear();

    dilep_pt_gen_lepton_matched_dressed_drX.clear();
    dilep_mass_gen_lepton_matched_dressed_drX.clear();
    drX_gen_lepton_matched_dressed.clear();

    photons_et_gen.clear();
    photons_mother_id_gen.clear();
    photons_closest_dr_to_leptons_gen.clear();
    lepton_matched_photons_closest_dr_to_leptons_gen.clear();

    photon_n_rec = 0;
    leadingphoton_pt_rec = -999.;
    leadingphoton_eta_rec = -999.;
    leadingphoton_lepton_dr_rec = -999.;

    evt_weight_total_gen = 1.;
    evt_weight_total_rec = 1.;
    evt_weight_btag_rec = 1.;

    evt_weight_fake = 1.;

    evt_weight_pureweight = 1.;
    evt_weight_pureweight_up = 1.;
    evt_weight_pureweight_down = 1.;

    evt_weight_l1prefire = 1.;
    evt_weight_l1prefire_up = 1.;
    evt_weight_l1prefire_down = 1.;
    
    evt_weight_bveto = 1.;
    evt_weight_bveto_up = 1.;
    evt_weight_bveto_down = 1.;
  
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

    evt_tag_dielectron_fiducial_post_fsr = false;
    evt_tag_dimuon_fiducial_post_fsr = false;
    photon_n_gen = 0;
    lepton_matched_photon_n_gen = 0;

    lepton_matched_photon_et_gen_drX.clear();
    evt_tag_dielectron_fiducial_lepton_matched_dressed_drX.clear();
    evt_tag_dimuon_fiducial_lepton_matched_dressed_drX.clear();
  
    evt = new Event;
    *evt = GetEvent();
  
    FillHist("CutFlow",5,1,30,0,30);

    if(!IsDATA){
        evt_weight_total_gen *= weight_norm_1invpb*evt->GetTriggerLumi("Full");
        evt_weight_total_gen *= evt->MCweight();
    }

    ///////////////////////////////////// generator level, only for Drell-Yan MC
    if(MCSample.Contains("DY") && save_generator_info ){
        bool photos_used = false;
        if(MCSample.Contains("PHOTOS")) photos_used = true;
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

            mother_id_of_prefsr_dilep = gen_particles.at(gen_particles.at(gen_particle_index_ME).MotherIndex()).PID();
            
            dilep_pt_gen_prefsr   = (gen_particles.at(gen_particle_index_ME) + gen_particles.at(gen_antiparticle_index_ME)).Pt();
            dilep_mass_gen_prefsr = (gen_particles.at(gen_particle_index_ME) + gen_particles.at(gen_antiparticle_index_ME)).M();
            particle_pt_gen_prefsr     = gen_particles.at(gen_particle_index_ME).Pt();
            antiparticle_pt_gen_prefsr     = gen_particles.at(gen_antiparticle_index_ME).Pt();
            particle_eta_gen_prefsr     = gen_particles.at(gen_particle_index_ME).Eta();
            antiparticle_eta_gen_prefsr     = gen_particles.at(gen_antiparticle_index_ME).Eta();

            dilep_pt_gen_postfsr   = (gen_particles.at(gen_particle_index_status1) + gen_particles.at(gen_antiparticle_index_status1)).Pt();
            dilep_mass_gen_postfsr = (gen_particles.at(gen_particle_index_status1) + gen_particles.at(gen_antiparticle_index_status1)).M();
            particle_pt_gen_postfsr     = gen_particles.at(gen_particle_index_status1).Pt();
            antiparticle_pt_gen_postfsr     = gen_particles.at(gen_antiparticle_index_status1).Pt();
            particle_eta_gen_postfsr     = gen_particles.at(gen_particle_index_status1).Eta();
            antiparticle_eta_gen_postfsr     = gen_particles.at(gen_antiparticle_index_status1).Eta();

            // save pre FSR leptons to check dR matching between gen and rec leptons
            leptons_postfsr.push_back(gen_particles.at(gen_particle_index_status1));
            leptons_postfsr.push_back(gen_particles.at(gen_antiparticle_index_status1));

            if( evt_tag_dielectron_gen == 1 && ((particle_pt_gen_postfsr > 25. && antiparticle_pt_gen_postfsr > 15.) || (particle_pt_gen_postfsr > 15. && antiparticle_pt_gen_postfsr > 25.)) && fabs(particle_eta_gen_postfsr) < 2.5 && fabs(antiparticle_eta_gen_postfsr) < 2.5 )
                evt_tag_dielectron_fiducial_post_fsr = true;
            else evt_tag_dielectron_fiducial_post_fsr = false;

            if( evt_tag_dimuon_gen == 1 && ((particle_pt_gen_postfsr > 20. && antiparticle_pt_gen_postfsr > 10.) || (particle_pt_gen_postfsr > 10. && antiparticle_pt_gen_postfsr > 20.)) && fabs(particle_eta_gen_postfsr) < 2.4 && fabs(antiparticle_eta_gen_postfsr) < 2.4 )
                evt_tag_dimuon_fiducial_post_fsr = true;
            else evt_tag_dimuon_fiducial_post_fsr = false;


            // dilepton from dressed leptons for dR = X
            TLorentzVector dilepton_p4_status1 = gen_particles.at(gen_particle_index_status1) + gen_particles.at(gen_antiparticle_index_status1);
            std::map<Double_t, TLorentzVector> dilepton_gamma_p4_drX = {{0.1, dilepton_p4_status1},{0.2, dilepton_p4_status1}, {0.3, dilepton_p4_status1},
                                                                        {0.5, dilepton_p4_status1},{0.7, dilepton_p4_status1}, {1., dilepton_p4_status1},
                                                                        {2., dilepton_p4_status1}, {3., dilepton_p4_status1}, {5., dilepton_p4_status1}, {10, dilepton_p4_status1}}; 

            std::map<Double_t, TLorentzVector> dilepton_lepton_matched_gamma_p4_drX = {{0.1, dilepton_p4_status1},{0.2, dilepton_p4_status1}, {0.3, dilepton_p4_status1},
                                                                                       {0.5, dilepton_p4_status1},{0.7, dilepton_p4_status1}, {1., dilepton_p4_status1},
                                                                                       {2., dilepton_p4_status1}, {3., dilepton_p4_status1}, {5., dilepton_p4_status1}, {10, dilepton_p4_status1}};


            // dressed lepton for dR = X
            TLorentzVector particle_p4_status1 = gen_particles.at(gen_particle_index_status1);
            TLorentzVector antiparticle_p4_status1 = gen_particles.at(gen_antiparticle_index_status1);

            std::map<Double_t, TLorentzVector> particle_lepton_matched_gamma_p4_drX = {{0.1, particle_p4_status1},{0.2, particle_p4_status1}, {0.3, particle_p4_status1},
                                                                                       {0.5, particle_p4_status1},{0.7, particle_p4_status1}, {1., particle_p4_status1},
                                                                                       {2., particle_p4_status1}, {3., particle_p4_status1}, {5., particle_p4_status1}, {10, particle_p4_status1}};

            std::map<Double_t, TLorentzVector> antiparticle_lepton_matched_gamma_p4_drX = {{0.1, antiparticle_p4_status1},{0.2, antiparticle_p4_status1}, {0.3, antiparticle_p4_status1},
                                                                                       {0.5, antiparticle_p4_status1},{0.7, antiparticle_p4_status1}, {1., antiparticle_p4_status1},
                                                                                       {2., antiparticle_p4_status1}, {3., antiparticle_p4_status1}, {5., antiparticle_p4_status1}, {10, antiparticle_p4_status1}};

            // added photons
            TLorentzVector photon_sum_p4;
            std::map<Double_t, TLorentzVector> photon_p4_drX = {{0.1, photon_sum_p4},{0.2, photon_sum_p4}, {0.3, photon_sum_p4},
                                                                                       {0.5, photon_sum_p4},{0.7, photon_sum_p4}, {1., photon_sum_p4},
                                                                                       {2., photon_sum_p4}, {3., photon_sum_p4}, {5., photon_sum_p4}, {10, photon_sum_p4}};

            // save index between status 1 and the initial ME lepton
            std::map<int, int> index_map;
            saveIndexToMap(gen_particle_index_status1,     gen_particle_index_ME,     index_map);
            saveIndexToMap(gen_antiparticle_index_status1, gen_antiparticle_index_ME, index_map);

            // status 1 photons
            //
            unsigned int size_gen_photons = gen_photons.size();
            photon_n_gen = size_gen_photons;
            for(unsigned int iph = 0; iph < size_gen_photons; iph++){

                photons_et_gen.push_back(gen_photons.at(iph).Pt());
                photons_mother_id_gen.push_back( gen_particles.at(gen_photons.at(iph).MotherIndex()).PID() );
 
                // find the closest delta R between photon and lepton and save it               
                Double_t dr_gamma_particle = gen_photons.at(iph).DeltaR( gen_particles.at(gen_particle_index_status1) ); 
                Double_t dr_gamma_antiparticle = gen_photons.at(iph).DeltaR( gen_particles.at(gen_antiparticle_index_status1) );
                Double_t dr_temp;

                bool matched_to_particle = false;
                if(dr_gamma_particle > dr_gamma_antiparticle){
                    photons_closest_dr_to_leptons_gen.push_back(dr_gamma_antiparticle);
                    dr_temp = dr_gamma_antiparticle;
                }
                else{
                    photons_closest_dr_to_leptons_gen.push_back(dr_gamma_particle);
                    dr_temp = dr_gamma_particle;
                    matched_to_particle = true; 
                }

                if(!photos_used){
                    if( index_map.find(gen_photons.at(iph).MotherIndex()) != index_map.end() ){
                        lepton_matched_photon_n_gen++;
                        lepton_matched_photons_closest_dr_to_leptons_gen.push_back(dr_temp);
                    }
                }
                else{
                    if( gen_particles.at(gen_photons.at(iph).MotherIndex()).PID() == 23 ){
                        lepton_matched_photon_n_gen++;
                        lepton_matched_photons_closest_dr_to_leptons_gen.push_back(dr_temp);
                    }
                }

                // 
                TLorentzVector photon_temp = gen_photons.at(iph);
                for(std::map<Double_t, TLorentzVector>::iterator mapit = dilepton_gamma_p4_drX.begin(); mapit!=dilepton_gamma_p4_drX.end(); mapit++){
                    if(dr_temp < mapit->first){
                        mapit->second += photon_temp; 

                        // only for photons sharing the same index with decaying lepton
                        // this is the current way to correct FSR in ISR analysis without delta R cut
                        if(!photos_used){
                            if( index_map.find(gen_photons.at(iph).MotherIndex()) != index_map.end() ){
                                dilepton_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                photon_p4_drX[mapit->first] += photon_temp;

                                if(matched_to_particle){
                                    particle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                                else{
                                    antiparticle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                            }
                        }
                        else{

                            if( gen_particles.at(gen_photons.at(iph).MotherIndex()).PID() == 23 ){
                                dilepton_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                photon_p4_drX[mapit->first] += photon_temp;

                                if(matched_to_particle){
                                    particle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                                else{
                                    antiparticle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                            }
                        }// for PHOTOS
                    }
                    else continue;
                }// loop for dilepton_gamma_p4_drX
            }// loop over status 1 photons

            for(std::map<Double_t, TLorentzVector>::iterator mapit = dilepton_gamma_p4_drX.begin(); mapit!=dilepton_gamma_p4_drX.end(); mapit++){
                dilep_pt_gen_dressed_drX.push_back((mapit->second).Pt());
                dilep_mass_gen_dressed_drX.push_back((mapit->second).M());
                drX_gen_dressed.push_back(mapit->first);
            }// loop for dilepton_gamma_p4_drX

            for(std::map<Double_t, TLorentzVector>::iterator mapit = dilepton_lepton_matched_gamma_p4_drX.begin(); mapit!=dilepton_lepton_matched_gamma_p4_drX.end(); mapit++){
                dilep_pt_gen_lepton_matched_dressed_drX.push_back((mapit->second).Pt());
                dilep_mass_gen_lepton_matched_dressed_drX.push_back((mapit->second).M());
                drX_gen_lepton_matched_dressed.push_back(mapit->first);
            }// loop for dilepton_lepton_matched_gamma_p4_drX


            std::map<Double_t, TLorentzVector>::iterator mapit_particle = particle_lepton_matched_gamma_p4_drX.begin();
            std::map<Double_t, TLorentzVector>::iterator mapit_antiparticle = antiparticle_lepton_matched_gamma_p4_drX.begin();

            for( ; mapit_particle!=particle_lepton_matched_gamma_p4_drX.end(); mapit_particle++, mapit_antiparticle++){
                if( (((mapit_particle->second).Pt() > 25. && (mapit_antiparticle->second).Pt() > 15) || ((mapit_particle->second).Pt() > 15. && (mapit_antiparticle->second).Pt() > 25))  &&  fabs((mapit_particle->second).Eta()) < 2.5 && fabs((mapit_antiparticle->second).Eta()) < 2.5 ){
                    evt_tag_dielectron_fiducial_lepton_matched_dressed_drX.push_back(true);
                }
                else evt_tag_dielectron_fiducial_lepton_matched_dressed_drX.push_back(false); 

                if( (((mapit_particle->second).Pt() > 20. && (mapit_antiparticle->second).Pt() > 10) || ((mapit_particle->second).Pt() > 10. && (mapit_antiparticle->second).Pt() > 20))  &&  fabs((mapit_particle->second).Eta()) < 2.4 && fabs((mapit_antiparticle->second).Eta()) < 2.4 ){
                    evt_tag_dimuon_fiducial_lepton_matched_dressed_drX.push_back(true);
                }
                else evt_tag_dimuon_fiducial_lepton_matched_dressed_drX.push_back(false); 
            }// loop for particle_lepton_matched_gamma_p4_drX and antiparticle_lepton_matched_gamma_p4_drXX

            for(std::map<Double_t, TLorentzVector>::iterator mapit = photon_p4_drX.begin(); mapit!=photon_p4_drX.end(); mapit++){
                lepton_matched_photon_et_gen_drX.push_back((mapit->second).Pt());
            }// loop for dilepton_lepton_matched_gamma_p4_drX


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
    if(PassMETFilter() && save_detector_info){ 

        // TODO need to rearange...
        //if( !evt->PassTrigger(DiMuTrgs) ){
        //    delete evt;
        //    return;
        //}

        FillHist("CutFlow",6,1,30,0,30);

        ///////////////////////////////////////////////////////////////////////////// basic event weight
        PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

        if(!IsDATA){
          evt_weight_pureweight=(mcCorr->*PileUpWeight)(nPileUp,0);
          evt_weight_pureweight_up=(mcCorr->*PileUpWeight)(nPileUp,1);
          evt_weight_pureweight_down=(mcCorr->*PileUpWeight)(nPileUp,-1);
          evt_weight_total_rec *= evt_weight_pureweight;
        }


        if(!IsDATA){
          if(DataYear<=2017){
            evt_weight_l1prefire = L1PrefireReweight_Central;
            evt_weight_l1prefire_up = L1PrefireReweight_Up;
            evt_weight_l1prefire_down = L1PrefireReweight_Down;
            evt_weight_total_rec *= L1PrefireReweight_Central;
          }
        }

        // b tag 
        std::vector<Jet::Tagger> vtaggers;
        vtaggers.push_back(Jet::DeepCSV);

        std::vector<Jet::WP> v_wps;
        v_wps.push_back(Jet::Medium);

                                //systematic, run dependent: set true for 2017
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
        float btag_sf_up = 1, misbtag_sf_up = 1.;
        float btag_sf_down = 1, misbtag_sf_down = 1.;

        BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, 0, btag_sf, misbtag_sf);
        BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, 1, btag_sf_up, misbtag_sf_down);
        BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, -1, btag_sf_down, misbtag_sf_down);

        if(!IsDATA){
            evt_weight_total_rec *= (btag_sf * misbtag_sf);
            evt_weight_bveto = (btag_sf * misbtag_sf);
            evt_weight_bveto_up = (btag_sf_up * misbtag_sf_up);
            evt_weight_bveto_down = (btag_sf_down * misbtag_sf_down);
        }
        if(debug_) std::cout <<"misbtag_sf: " << misbtag_sf << " btag_sf : " << btag_sf << " n bjets (noSF): " << n_bjet_deepcsv_m_noSF << " n bjets: " << n_bjet_deepcsv_m << std::endl;
        ///////////////////////////////////////////////////////////////////////////// 
        //

        // for quick study for FSR with various Muon isolation definition
        AllMuons = GetAllMuons();
        AllElectrons = GetAllElectrons();

        // Lepton ID
        muons = GetMuons("POGTightWithTightIso", 7., 2.4);
        electrons = GetElectrons("passMediumID", 9., 2.5);
        photons = GetPhotons("passMediumID", 0.5, 2.5, true); // last boolean is for checkPixelSeed
        std::sort(muons.begin(), muons.end(), PtComparing); 
        std::sort(electrons.begin(), electrons.end(), PtComparing);
        std::sort(photons.begin(), photons.end(), PtComparing);

        AnalyzerParameter param;
        param.Muon_ID = "POGTight";
        Dimu_map["POGTight"]->resetVariables();
        executeEventFromParameter(param);
        param.Clear();
        clearVariables();

        param.Muon_ID = "POGTightWithRelIsoNoPH";
        Dimu_map["POGTightWithRelIsoNoPH"]->resetVariables();
        executeEventFromParameter(param);
        param.Clear();
        clearVariables();

        param.Muon_ID = "POGTightWithRelIsoNoPHCH";
        Dimu_map["POGTightWithRelIsoNoPHCH"]->resetVariables();
        executeEventFromParameter(param);
        param.Clear();
        clearVariables();

        // get fake weight
        // Muon ID
        param.Muon_Tight_ID = "HNTight";
        param.Muon_ID = "HNLoose";
        param.Muon_FR_ID = "HNtypeI_V1";     // ID name in histmap_Muon.txt
        param.Muon_FR_Key = "AwayJetPt40"; // histname
        param.Muon_UsePtCone = true;

        // Electron Id
        param.Electron_Tight_ID = "ISRTight";
        param.Electron_ID = "ISRLoose";
        param.Electron_FR_ID = "HNtypeI_V1";     // ID name in histmap_Electron.txt
        param.Electron_FR_Key = "AwayJetPt40"; // histname
        
        param.Electron_UsePtCone = true;

        // Jet ID
        param.Jet_ID = "tight";
        param.FatJet_ID = "tight";

        //if(IsDATA){
        //    fake_estimation->resetVariables();
        //    executeEventFromParameter(param, false);
        //    param.Clear();
        //    clearVariables();
        //}

        IsMuMu = 0;
        IsElEl = 0;

        //if(muons.size() == 2) if(electrons.size() == 0) IsMuMu = 1;
        //if(muons.size() == 0) if(electrons.size() == 2) IsElEl = 1;

        if(muons.size() == 2) IsMuMu = 1;
        if(electrons.size() == 2) IsElEl = 1;
        if(debug_) cout << "muon size: " << muons.size() << " electron size: " << electrons.size() << endl; 
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

                if(debug_) cout << "check trigger ..." << endl;
                if(evt->PassTrigger(DiElTrgs) ){
                    if(debug_) cout << "dielectron trigger passed! " << endl;
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

                leadinglep_pt_rec =     leps.at(0)->Pt();
                subleadinglep_pt_rec =  leps.at(1)->Pt();
                leadinglep_eta_rec =    leps.at(0)->Eta();
                subleadinglep_eta_rec = leps.at(1)->Eta();
                dilep_pt_rec =   (*(leps.at(0))+*(leps.at(1))).Pt();
                dilep_mass_rec = (*(leps.at(0))+*(leps.at(1))).M();
                leadingmuon_reliso_rec = leps.at(0)->RelIso();
                subleadingmuon_reliso_rec = leps.at(0)->RelIso();

                double dR_for_gen_rec_matching = 0.1;
                unsigned int n_matched_lepton = 0;
                for(unsigned int gen_size = 0; gen_size < leptons_postfsr.size(); gen_size++){
                    double temp_dr1 = leps.at(0)->DeltaR(leptons_postfsr.at(gen_size));
                    double temp_dr2 = leps.at(1)->DeltaR(leptons_postfsr.at(gen_size));

                    if( temp_dr1 < dR_for_gen_rec_matching ) n_matched_lepton++;
                    if( temp_dr2 < dR_for_gen_rec_matching ) n_matched_lepton++;

                    temp_dr1 < temp_dr2 ? gen_rec_lepton_dR.push_back(temp_dr1) : gen_rec_lepton_dR.push_back(temp_dr2);

                    // don't care charge flip, just count matched leptons to gen leptons 
                    if(n_matched_lepton == 2 && gen_size == 1)
                        gen_rec_evt_matched = true;
                } 

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

                if(evt_tag_leptonpt_sel_rec && evt_tag_leptoneta_sel_rec && evt_tag_oppositecharge_sel_rec && evt_tag_bvetoed_rec) 
                    evt_tag_analysisevnt_sel_rec = 1;

                if(debug_) cout << "evt_tag_analysisevnt_sel_rec: " << evt_tag_analysisevnt_sel_rec << endl;

                //if(!save_generator_info && (evt_tag_dimuon_rec == 0 && evt_tag_dielectron_rec == 0)) return;

            } // passing dilepton trigger (dont need trigger matching?)
        } // two leptons passing ID
    } // pass METfilter 
    
    newtree->Fill();

    delete evt;
}

void Skim_ISR::clearVariables(){

    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();
    evt_tag_dimuon_rec = 0;
    evt_tag_dielectron_rec = 0;
    evt_tag_leptonpt_sel_rec = 0;
    evt_tag_leptoneta_sel_rec = 0;
    evt_tag_oppositecharge_sel_rec = 0;
    evt_tag_analysisevnt_sel_rec = 0;

    dilep_pt_rec          = -999.;
    dilep_mass_rec        = -999.;
    dilep_photon_mass_rec = -999.;
    leadinglep_pt_rec     = -999.;
    subleadinglep_pt_rec  = -999.;
    leadinglep_eta_rec    = -999.;
    subleadinglep_eta_rec = -999.;

    photon_n_rec = 0;
    leadingphoton_pt_rec = -999.;
    leadingphoton_eta_rec = -999.;
    leadingphoton_lepton_dr_rec = -999.;
}

void Skim_ISR::executeEventFromParameter(AnalyzerParameter param, bool temp_FSR_study){
        
    vector<Muon> this_AllMuons = AllMuons;
    vector<Electron> this_AllElectrons = AllElectrons;

    if(temp_FSR_study){
        vector<Muon> muons_ = SelectMuons(this_AllMuons, param.Muon_ID, 7., 2.4);
        std::sort(muons_.begin(), muons_.end(), PtComparing); 

        IsMuMu = 0;

        if(muons_.size() == 2) IsMuMu = 1;
         
        if(IsMuMu == 1){ 
                
          if(evt->PassTrigger(DiMuTrgs) ){
              leps=MakeLeptonPointerVector(muons_);
              evt_tag_dimuon_rec = 1;
              Lep0PtCut = 20.;
              Lep1PtCut = 10.;
              LepEtaCut = 2.4;
           }
        } 

        if( leps.size() == 2 ){ // leps have leptons passing ID and trigger passed

            // lepton pt cut requirement
            if(leps.at(0)->Pt() > Lep0PtCut && leps.at(1)->Pt() > Lep1PtCut) evt_tag_leptonpt_sel_rec = 1;

            // lepton eta cut requirement
            if(fabs(leps.at(0)->Eta()) < LepEtaCut && fabs(leps.at(1)->Eta()) < LepEtaCut){ 
                        evt_tag_leptoneta_sel_rec = 1;
            }
            
            // opposite charge requirements
            if((leps.at(0)->Charge() + leps.at(1)->Charge()) == 0) evt_tag_oppositecharge_sel_rec = 1;


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
            if(evt_tag_leptonpt_sel_rec && evt_tag_leptoneta_sel_rec && evt_tag_oppositecharge_sel_rec && evt_tag_bvetoed_rec)
                evt_tag_analysisevnt_sel_rec = 1;

            Dimu_map[param.Muon_ID]->setVariables(evt_tag_analysisevnt_sel_rec, dilep_pt_rec, dilep_mass_rec, dilep_photon_mass_rec, leadinglep_pt_rec, subleadinglep_pt_rec, leadinglep_eta_rec, subleadinglep_eta_rec, leadingphoton_lepton_dr_rec); 
        }
    }
    else{

        vector<Muon> muons_ = SelectMuons(this_AllMuons, param.Muon_ID, 10., 2.4);
        vector<Electron> electrons_ = SelectElectrons(this_AllElectrons, param.Electron_ID, 10., 2.5);
        std::sort(muons_.begin(), muons_.end(), PtComparing);
        std::sort(electrons_.begin(), electrons_.end(), PtComparing);

        IsMuMu = 0;
        IsElEl = 0;

        if(muons_.size() == 2) IsMuMu = 1;
        if(electrons_.size() == 2) IsElEl = 1;

        // Set tight_iso cut & calculate pTcone
        double mu_tight_iso = 0.15;
        double el_tight_iso = 0.;

        // Set pTcone

        for(unsigned int i=0; i<muons_.size(); i++){
          double this_ptcone = muons_.at(i).CalcPtCone(muons_.at(i).RelIso(), mu_tight_iso);
          muons_.at(i).SetPtCone(this_ptcone);
        }
         
        for(unsigned int i=0; i<electrons_.size(); i++){
          el_tight_iso = 0.0287+0.506/electrons_.at(i).UncorrPt();
          if(fabs(electrons_.at(i).scEta()) > 1.479) el_tight_iso = 0.0445+0.963/electrons_.at(i).UncorrPt();
          double this_ptcone = electrons_.at(i).CalcPtCone(electrons_.at(i).RelIso(), el_tight_iso);
          electrons_.at(i).SetPtCone(this_ptcone);
        }

        if(IsMuMu == 1){

          if(evt->PassTrigger(DiMuTrgs) ){
              leps=MakeLeptonPointerVector(muons_);
              evt_tag_dimuon_rec = 1;
              Lep0PtCut = 20.;
              Lep1PtCut = 10.;
              LepEtaCut = 2.4;
           }
        }

        if(IsElEl == 1){
    
            if(evt->PassTrigger(DiElTrgs) ){
                leps=MakeLeptonPointerVector(electrons_);
                evt_tag_dielectron_rec = 1;
                Lep0PtCut = 25.;
                Lep1PtCut = 15.;
                LepEtaCut = 2.5;
            }
        }


        if( leps.size() == 2 ){ // leps have leptons passing ID and trigger passed

            // lepton pt cut requirement
            if(leps.at(0)->Pt() > Lep0PtCut && leps.at(1)->Pt() > Lep1PtCut)
                evt_tag_leptonpt_sel_rec = 1;

            // lepton eta cut requirement
            if(fabs(leps.at(0)->Eta()) < LepEtaCut && fabs(leps.at(1)->Eta()) < LepEtaCut){
                if(IsMuMu == 1)
                    evt_tag_leptoneta_sel_rec = 1;
                if(IsElEl == 1){
                    if((fabs(leps.at(0)->Eta()) < 1.4442 || fabs(leps.at(0)->Eta()) > 1.566) && (fabs(leps.at(1)->Eta()) < 1.4442 || fabs(leps.at(1)->Eta()) > 1.566))
                        evt_tag_leptoneta_sel_rec = 1;
                }
            }

            // opposite charge requirements
            if((leps.at(0)->Charge() + leps.at(1)->Charge()) == 0)
                evt_tag_oppositecharge_sel_rec = 1;

            leadinglep_pt_rec = leps.at(0)->Pt();
            subleadinglep_pt_rec = leps.at(1)->Pt();
            leadinglep_eta_rec = leps.at(0)->Eta();
            subleadinglep_eta_rec = leps.at(1)->Eta();
            dilep_pt_rec = (*(leps.at(0))+*(leps.at(1))).Pt();
            dilep_mass_rec = (*(leps.at(0))+*(leps.at(1))).M();

            if(evt_tag_leptonpt_sel_rec && evt_tag_leptoneta_sel_rec && evt_tag_oppositecharge_sel_rec && evt_tag_bvetoed_rec)
                evt_tag_analysisevnt_sel_rec = 1;

            evt_weight_fake = fakeEst->GetWeight(leps, param, 0, false);
            fake_estimation->setVariables(evt_tag_analysisevnt_sel_rec, evt_tag_dielectron_rec, evt_tag_dimuon_rec, dilep_pt_rec, dilep_mass_rec, leadinglep_pt_rec, subleadinglep_pt_rec, leadinglep_eta_rec, subleadinglep_eta_rec);
        }

    }
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

void Skim_ISR::saveIndexToMap(int current_index, int mother_index, std::map<int,int> &partindex_map){

    if(current_index==mother_index){
       partindex_map.insert(std::make_pair(current_index, gen_particles.at(current_index).PID()));
    }
    else{
         partindex_map.insert(std::make_pair(current_index, gen_particles.at(current_index).PID()));
         saveIndexToMap(gen_particles.at(current_index).MotherIndex(), mother_index, partindex_map);
    }
}

void ISR_LeptonIDVariation::resetVariables(){
     
    evt_tag_analysisevnt_sel_rec_ = false;
    evt_tag_dielectron_rec_       = false;
    evt_tag_dimuon_rec_           = false;
    dilep_pt_rec_                 = -999.;
    dilep_mass_rec_               = -999.;
    leadinglep_pt_rec_            = -999.;
    subleadinglep_pt_rec_         = -999.;
    leadinglep_eta_rec_           = -999.;
    subleadinglep_eta_rec_        = -999.;
}

void ISR_LeptonIDVariation::setBranch(TTree *tree){ 

    tree->Branch(evt_tag_analysisevnt_sel_rec_brname,   &evt_tag_analysisevnt_sel_rec_);
    tree->Branch(evt_tag_dielectron_rec_brname,   &evt_tag_dielectron_rec_);
    tree->Branch(evt_tag_dimuon_rec_brname,   &evt_tag_dimuon_rec_);
    tree->Branch(dilep_pt_rec_brname,   &dilep_pt_rec_);
    tree->Branch(dilep_mass_rec_brname,   &dilep_mass_rec_);
    tree->Branch(leadinglep_pt_rec_brname,   &leadinglep_pt_rec_);
    tree->Branch(subleadinglep_pt_rec_brname,   &subleadinglep_pt_rec_);
    tree->Branch(leadinglep_eta_rec_brname,   &leadinglep_eta_rec_);
    tree->Branch(subleadinglep_eta_rec_brname,   &subleadinglep_eta_rec_);
}

void ISR_LeptonIDVariation::setVariables(bool pass_sel, bool pass_dielectron, bool pass_dimuon, double dilep_pt, double dilep_mass, double lead_lep_pt, double sublead_lep_pt, double lead_lep_eta, double sublead_lep_eta){

    evt_tag_analysisevnt_sel_rec_ = pass_sel;
    evt_tag_dielectron_rec_ = pass_dielectron;
    evt_tag_dimuon_rec_ = pass_dimuon;
    dilep_pt_rec_ = dilep_pt;
    dilep_mass_rec_ = dilep_mass;
    leadinglep_pt_rec_ = lead_lep_pt;
    subleadinglep_pt_rec_ = sublead_lep_pt;
    leadinglep_eta_rec_ = lead_lep_eta;
    subleadinglep_eta_rec_ = sublead_lep_eta;
}

void Dimu_variables::resetVariables(){

    evt_tag_analysisevnt_sel_rec_ = false;
    dimu_pt_rec_                = -999.;
    dimu_mass_rec_              = -999.;
    dimu_photon_mass_rec_       = -999.;
    leadingmuon_pt_rec_         = -999.;
    subleadingmuon_pt_rec_      = -999.;
    leadingmuon_eta_rec_        = -999.;
    subleadingmuon_eta_rec_     = -999.;
    leadingphoton_muon_dr_rec_  = -999.;
}

void Dimu_variables::setBranch(TTree *tree){
    tree->Branch(evt_tag_analysisevnt_sel_rec_brname,   &evt_tag_analysisevnt_sel_rec_);
    tree->Branch(dimu_pt_rec_brname,                    &dimu_pt_rec_);
    tree->Branch(dimu_mass_rec_brname,                  &dimu_mass_rec_);
    tree->Branch(dimu_photon_mass_rec_brname,           &dimu_photon_mass_rec_);
    tree->Branch(leadingmuon_pt_rec_brname,             &leadingmuon_pt_rec_);
    tree->Branch(subleadingmuon_pt_rec_brname,          &subleadingmuon_pt_rec_);
    tree->Branch(leadingmuon_eta_rec_brname,            &leadingmuon_eta_rec_);
    tree->Branch(subleadingmuon_eta_rec_brname,         &subleadingmuon_eta_rec_);
    tree->Branch(leadingphoton_muon_dr_rec_brname,      &leadingphoton_muon_dr_rec_);
}

void Dimu_variables::setVariables(bool pass_sel, double dimu_pt, double dimu_mass, double dimu_gamma_mass, double lead_muon_pt, double sublead_muon_pt, double lead_muon_eta, double sublead_muon_eta, double dr_muon_gamma){
    evt_tag_analysisevnt_sel_rec_ = pass_sel;
    dimu_pt_rec_                = dimu_pt;
    dimu_mass_rec_              = dimu_mass;
    dimu_photon_mass_rec_       = dimu_gamma_mass;
    leadingmuon_pt_rec_         = lead_muon_pt;
    subleadingmuon_pt_rec_      = sublead_muon_pt;
    leadingmuon_eta_rec_        = lead_muon_eta;
    subleadingmuon_eta_rec_     = sublead_muon_eta;
    leadingphoton_muon_dr_rec_  = dr_muon_gamma;
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

