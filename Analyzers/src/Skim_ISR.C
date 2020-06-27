#include "Skim_ISR.h"

void Skim_ISR::initializeAnalyzer()
{

    //=================================
    // Skim Types
    //=================================

    debug_ = false;
    if( HasFlag("ISR_detector_only"))
    {
        save_detector_info = true;
        save_generator_info = false;
    }
    else if (HasFlag("ISR_generator_only"))
    {
        save_detector_info = false;
        save_generator_info = true;
    }
    else if (HasFlag("ISR"))
    {
        save_detector_info = true;
        save_generator_info = true;
    }
    else if(HasFlag("MakeZptCorrNtuple"))
    {
        save_detector_info = true;
        save_generator_info = true;
        make_zptcorr_ntuple = true;
    }
    else
    {
        cout <<"[Skim_ISR::executeEvent] Not ready for this Flags ";
        for(unsigned int i=0; i<Userflags.size(); i++)
        {
            cout <<"  "<< Userflags.at(i);
        }
        cout<<endl;
        exit(EXIT_FAILURE);
    }

    outfile->mkdir("recoTree");
    outfile->cd("recoTree");

    if(make_zptcorr_ntuple)
    {
        newtree = new TTree("SKFlat","SKFlat");
    }
    else
    {
        newtree = fChain->CloneTree(0);
    }

    newtree->Branch("evt_weight_total_gen", &evt_weight_total_gen,"evt_weight_total_gen/D");

    if(save_detector_info)
    {
        newtree->Branch("evt_weight_total_rec",  &evt_weight_total_rec, "evt_weight_total_rec/D");

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
        newtree->Branch("is_met_filter_passed", &is_met_filter_passed,"is_met_filter_passed/O");
        newtree->Branch("is_diel_tri_passed", &is_diel_tri_passed,"is_diel_tri_passed/O");
        newtree->Branch("is_dimu_tri_passed", &is_dimu_tri_passed,"is_dimu_tri_passed/O");
        newtree->Branch("evt_tag_bvetoed_rec", &evt_tag_bvetoed_rec,"evt_tag_bvetoed_rec/O");

        // nominal
        nominal_selection = new Analysis_Variables("Nominal");
        nominal_selection->setBranch(newtree);

        if(!make_zptcorr_ntuple)
        {
            fake_estimation = new Analysis_Variables("Fake");
            lepton_momentum_scale_up = new Analysis_Variables("LepMomScaleUp");
            lepton_momentum_scale_down = new Analysis_Variables("LepMomScaleDown");
            lepton_momentum_res_up = new Analysis_Variables("LepMomResUp");
            lepton_momentum_res_down = new Analysis_Variables("LepMomResDown");
            without_lepton_momentum = new Analysis_Variables("NoLepMomCorr");

            fake_estimation->setBranch(newtree);
            lepton_momentum_scale_up->setBranch(newtree);
            lepton_momentum_scale_down->setBranch(newtree);
            lepton_momentum_res_up->setBranch(newtree);
            lepton_momentum_res_down->setBranch(newtree);
            without_lepton_momentum->setBranch(newtree);
        }
    }

    if(save_generator_info)
    {
        // gen info
        // event categories
        newtree->Branch("evt_tag_dimuon_lhe", &evt_tag_dimuon_lhe,"evt_tag_dimuon_lhe/O");
        newtree->Branch("evt_tag_dielectron_lhe", &evt_tag_dielectron_lhe,"evt_tag_dielectron_lhe/O");

        newtree->Branch("evt_tag_ditau_hardprocess", &evt_tag_ditau_hardprocess,"evt_tag_ditau_hardprocess/O");
        newtree->Branch("evt_tag_dielectron_hardprocess", &evt_tag_dielectron_hardprocess,"evt_tag_dielectron_hardprocess/O");
        newtree->Branch("evt_tag_dimuon_hardprocess", &evt_tag_dimuon_hardprocess,"evt_tag_dimuon_hardprocess/O");

        newtree->Branch("evt_tag_dimuon_promptfinal", &evt_tag_dimuon_promptfinal, "evt_tag_dimuon_promptfinal/O");
        newtree->Branch("evt_tag_dielectron_promptfinal", &evt_tag_dielectron_promptfinal, "evt_tag_dielectron_promptfinal/O");
        newtree->Branch("evt_tag_emu_promptfinal", &evt_tag_emu_promptfinal, "evt_tag_emu_promptfinal/O");

        if(!make_zptcorr_ntuple)
        {
            newtree->Branch("photon_motherID_isPromptFinalState_selected", &photon_motherID_isPromptFinalState_selected);
            newtree->Branch("photon_matchedToLep_isPromptFinalState_selected", &photon_matchedToLep_isPromptFinalState_selected);
            newtree->Branch("photon_dRtoParticle_isPromptFinalState_selected", &photon_dRtoParticle_isPromptFinalState_selected);
            newtree->Branch("photon_dRtoAntiParticle_isPromptFinalState_selected", &photon_dRtoAntiParticle_isPromptFinalState_selected);
        }

        // TODO Add Z pT weight!
        newtree->Branch("zptweight_muon", &zptweight_muon, "zptweight_muon/D");
        newtree->Branch("zptweight_electron", &zptweight_electron, "zptweight_electron/D");

        newtree->Branch("n_photon_notLeptonMother_isPromptFinalState", &n_photon_notLeptonMother_isPromptFinalState, "n_photon_notLeptonMother_isPromptFinalState/I");
        newtree->Branch("n_photon_isPromptFinalState", &n_photon_isPromptFinalState, "n_photon_isPromptFinalState/I");
        newtree->Branch("n_lepton_isPromptFinalState", &n_lepton_isPromptFinalState, "n_lepton_isPromptFinalState/I");
        newtree->Branch("n_isPromptFinalState", &n_isPromptFinalState, "n_isPromptFinalState/I");

        newtree->Branch("dilep_motherID_hardprocess", &dilep_motherID_hardprocess,"dilep_motherID_hardprocess/I");
        newtree->Branch("dilep_motherID_myalgorithm", &dilep_motherID_myalgorithm,"dilep_motherID_myalgorithm/I");

        // LHE
        newtree->Branch("dilep_pt_lhe", &dilep_pt_lhe,"dilep_pt_lhe/D");
        newtree->Branch("dilep_mass_lhe", &dilep_mass_lhe,"dilep_mass_lhe/D");
        //TODO add LHE lepton pt eta
        // flagged as HardProcess
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

        newtree->Branch("dilep_pt_FSRgammaDRp1_gen_ispromptfinal", &dilep_pt_FSRgammaDRp1_gen_ispromptfinal,"dilep_pt_FSRgammaDRp1_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_FSRgammaDRp1_gen_ispromptfinal", &dilep_mass_FSRgammaDRp1_gen_ispromptfinal,"dilep_mass_FSRgammaDRp1_gen_ispromptfinal/D");
        newtree->Branch("dilep_pt_FSRgamma_gen_ispromptfinal", &dilep_pt_FSRgamma_gen_ispromptfinal,"dilep_pt_FSRgamma_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_FSRgamma_gen_ispromptfinal", &dilep_mass_FSRgamma_gen_ispromptfinal,"dilep_mass_FSRgamma_gen_ispromptfinal/D");
        newtree->Branch("dilep_pt_AllFSRgamma_gen_ispromptfinal", &dilep_pt_AllFSRgamma_gen_ispromptfinal,"dilep_pt_AllFSRgamma_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_AllFSRgamma_gen_ispromptfinal", &dilep_mass_AllFSRgamma_gen_ispromptfinal,"dilep_mass_AllFSRgamma_gen_ispromptfinal/D");
        newtree->Branch("dilep_pt_alllepton_FSRgamma_gen_ispromptfinal", &dilep_pt_alllepton_FSRgamma_gen_ispromptfinal,"dilep_pt_alllepton_FSRgamma_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_alllepton_FSRgamma_gen_ispromptfinal", &dilep_mass_alllepton_FSRgamma_gen_ispromptfinal,"dilep_mass_alllepton_FSRgamma_gen_ispromptfinal/D");

        newtree->Branch("pass_kinematic_cut_el_bare_gen", &pass_kinematic_cut_el_bare_gen, "pass_kinematic_cut_el_bare_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_bare_gen", &pass_kinematic_cut_mu_bare_gen, "pass_kinematic_cut_mu_bare_gen/O");
        newtree->Branch("pass_kinematic_cut_el_FSRgammaDRp1_gen", &pass_kinematic_cut_el_FSRgammaDRp1_gen, "pass_kinematic_cut_el_FSRgammaDRp1_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_FSRgammaDRp1_gen", &pass_kinematic_cut_mu_FSRgammaDRp1_gen, "pass_kinematic_cut_mu_FSRgammaDRp1_gen/O");
        newtree->Branch("pass_kinematic_cut_el_FSRgamma_gen", &pass_kinematic_cut_el_FSRgamma_gen, "pass_kinematic_cut_el_FSRgamma_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_FSRgamma_gen", &pass_kinematic_cut_mu_FSRgamma_gen, "pass_kinematic_cut_mu_FSRgamma_gen/O");
        newtree->Branch("pass_kinematic_cut_el_alllepton_FSRgamma_gen", &pass_kinematic_cut_el_alllepton_FSRgamma_gen, "pass_kinematic_cut_el_alllepton_FSRgamma_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_alllepton_FSRgamma_gen", &pass_kinematic_cut_mu_alllepton_FSRgamma_gen, "pass_kinematic_cut_mu_alllepton_FSRgamma_gen/O");
    }

    // clear vector residual
    DiMuTrgs.clear();
    DiElTrgs.clear();

    cout << "[Skim_ISR::initializeAnalyzer] Skim List====================== " << endl;
    if(DataYear==2016)
    {
        SingleMuTrgs = {
          "HLT_IsoMu24_v",
          "HLT_IsoTkMu24_v"
        };
        SingleElTrgs = {
          "HLT_Ele27_WPTight_Gsf_v"
        };

        DiMuTrgs = {
          "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
          "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
          "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
          "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
          "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
          "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",
        };
        DiElTrgs = {
          "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"
        };
    }
    else if(DataYear==2017)
    {
        DiMuTrgs = {
          "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",
        };
        DiElTrgs = {
          "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"
        };
    }
    else if(DataYear==2018)
    {
        DiMuTrgs = {
          "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v",
        };
        DiElTrgs = {
          "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"
        };
    }
    else
    {
        cout<<"[Skim_ISR::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
        exit(EXIT_FAILURE);
    }

    cout << "\t"<<"doubleTrgs to skim = " << endl;
    for(unsigned int i=0; i<DiMuTrgs.size(); i++)
    {
      cout << "\t" << DiMuTrgs.at(i) << endl;
    }
    for(unsigned int i=0; i<DiElTrgs.size(); i++)
    {
      cout << "\t" << DiElTrgs.at(i) << endl;
    }
}

void Skim_ISR::executeEvent()
{

    AllMuons.clear();
    AllElectrons.clear();

    muons.clear();
    electrons.clear();
    leps.clear();
    leptons_postfsr.clear();

    is_met_filter_passed = false;
    is_diel_tri_passed = false;
    is_dimu_tri_passed = false;

    dilep_motherID_hardprocess = -999;
    dilep_motherID_myalgorithm = -999;

    dilep_pt_lhe = -999.;
    dilep_mass_lhe = -999.;

    dilep_pt_FSRgammaDRp1_gen_ispromptfinal = -999.;
    dilep_mass_FSRgammaDRp1_gen_ispromptfinal = -999.;

    dilep_pt_FSRgamma_gen_ispromptfinal = -999.;
    dilep_mass_FSRgamma_gen_ispromptfinal = -999.;

    dilep_pt_AllFSRgamma_gen_ispromptfinal = -999.;
    dilep_mass_AllFSRgamma_gen_ispromptfinal = -999.;

    dilep_pt_alllepton_FSRgamma_gen_ispromptfinal = -999.;
    dilep_mass_alllepton_FSRgamma_gen_ispromptfinal = -999.;

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

    evt_weight_total_gen = 1.;
    evt_weight_total_rec = 1.;
    evt_weight_btag_rec = 1.;

    evt_weight_pureweight = 1.;
    evt_weight_pureweight_up = 1.;
    evt_weight_pureweight_down = 1.;

    evt_weight_l1prefire = 1.;
    evt_weight_l1prefire_up = 1.;
    evt_weight_l1prefire_down = 1.;

    evt_weight_bveto = 1.;
    evt_weight_bveto_up = 1.;
    evt_weight_bveto_down = 1.;

    evt_tag_dielectron_lhe = 0;
    evt_tag_dimuon_lhe = 0;
    evt_tag_ditau_hardprocess = 0;
    evt_tag_dielectron_hardprocess = 0;
    evt_tag_dimuon_hardprocess = 0;
    evt_tag_bvetoed_rec = 0;

    photon_motherID_isPromptFinalState_selected.clear();
    photon_matchedToLep_isPromptFinalState_selected.clear();
    photon_dRtoParticle_isPromptFinalState_selected.clear();
    photon_dRtoAntiParticle_isPromptFinalState_selected.clear();

    evt = new Event;
    *evt = GetEvent();

    FillHist("CutFlow",5,1,30,0,30);

    if(!IsDATA)
    {
        evt_weight_total_gen *= weight_norm_1invpb*evt->GetTriggerLumi("Full");
        evt_weight_total_gen *= evt->MCweight();
    }

    if(!IsDATA)
    {
        gen_particles.clear();
        gen_particles = GetGens();

        lhe_particles.clear();
        lhe_particles = GetLHEs();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    //
    //
    //                          Generator level only for Drell-Yan
    //
    //
    ////////////////////////////////////////////////////////////////////////////////////////

    if((MCSample.Contains("DY") || MCSample.Contains("ZTo")) && save_generator_info )
    {

        evt_tag_dimuon_promptfinal = false;
        evt_tag_dielectron_promptfinal = false;
        evt_tag_emu_promptfinal = false;

        pass_kinematic_cut_el_bare_gen = false;
        pass_kinematic_cut_mu_bare_gen = false;

        pass_kinematic_cut_el_FSRgammaDRp1_gen = false;
        pass_kinematic_cut_mu_FSRgammaDRp1_gen = false;

        pass_kinematic_cut_el_FSRgamma_gen = false;
        pass_kinematic_cut_mu_FSRgamma_gen = false;

        pass_kinematic_cut_el_alllepton_FSRgamma_gen = false;
        pass_kinematic_cut_mu_alllepton_FSRgamma_gen = false;

        gen_lepton_isPromptFinalstate.clear();
        gen_antilepton_isPromptFinalstate.clear();
        gen_photon_isPromptFinalstate.clear();

        n_isPromptFinalState = 0;
        n_photon_notLeptonMother_isPromptFinalState = 0;
        n_photon_isPromptFinalState = 0;
        n_lepton_isPromptFinalState = 0;

        zptweight_muon = 1.;
        zptweight_electron = 1.;

        bool photos_used = false;
        if(MCSample.Contains("PHOTOS"))
        {
            photos_used = true;
        }

        if(debug_)
        {
            cout << "Generator information for " + MCSample << endl;
        }

        // LHE info
        bool tauLHEexist = false;
        LHE temp_particle;
        LHE temp_antiparticle;
        for(int ilhe = 0; ilhe < (int) lhe_particles.size(); ilhe++)
        {
            if((abs(lhe_particles[ilhe].ID())==11||abs(lhe_particles[ilhe].ID())==13))
            {
                if(temp_particle.ID() == 0 && lhe_particles[ilhe].ID() > 0)
                {
                    temp_particle = lhe_particles[ilhe];

                    if(lhe_particles[ilhe].ID() == 11) evt_tag_dielectron_lhe = 1;
                    else evt_tag_dimuon_lhe = 1;
                }
                else if(temp_antiparticle.ID() == 0 && lhe_particles[ilhe].ID() < 0)
                {
                    temp_antiparticle = lhe_particles[ilhe];

                    if(lhe_particles[ilhe].ID() == -11) evt_tag_dielectron_lhe = 1;
                    else evt_tag_dimuon_lhe = 1;
                }
            }

            if(abs(lhe_particles[ilhe].ID())==15)
            {
                tauLHEexist = true;
                break;
            }
        }

        if(!tauLHEexist)
        {
            dilep_pt_lhe   = (temp_particle + temp_antiparticle).Pt();
            dilep_mass_lhe = (temp_particle + temp_antiparticle).M();
        }
        // for LHE particle

        bool gen_lepton_from_hardprocess_found = false;
        int first_lepton_id_found_in_ME = 0;

        gen_particle_index_ME         = -1;
        gen_antiparticle_index_ME     = -1;
        gen_particle_index_status1    = -1;
        gen_antiparticle_index_status1 = -1;

        // Loop over generator particles
        for( unsigned int i = 0; i < gen_particles.size(); i++)
        {
            int current_particle_id = gen_particles.at(i).PID();

            // isPromptFinalState() flagged gen particle
            if(gen_particles.at(i).isPromptFinalState())
            {
                n_isPromptFinalState++;

                // Save electron and muon flagged as isPromptFinalState()
                if(abs(current_particle_id) == 11 || abs(current_particle_id)==13)
                {
                    // Save leptons if their mother are not a proton
                    if(abs(gen_particles.at(gen_particles.at(i).MotherIndex()).PID()) != 2212)
                    {
                        n_lepton_isPromptFinalState++;

                        if(current_particle_id > 0)
                        {
                            gen_lepton_isPromptFinalstate.push_back(gen_particles.at(i));
                        }
                        else
                        {
                            gen_antilepton_isPromptFinalstate.push_back(gen_particles.at(i));
                        }
                    }
                }

                if(abs(current_particle_id) == 22)
                {
                    n_photon_isPromptFinalState++;
                    gen_photon_isPromptFinalstate.push_back(gen_particles.at(i));
                }
            }
            // for isPromptFinalState() flagged gen particles

            // print out gen particle info
            if(debug_)
            {
                if(gen_particles.at(i).Status() == 1 || gen_particles.at(i).isPromptFinalState() == true)
                {
                    std::cout << i << "\033[1;31m pid: " << gen_particles.at(i).PID()
                                   << " mother index: " << gen_particles.at(i).MotherIndex()
                                   << " status: " << gen_particles.at(i).Status()
                                   << " isPrompt: " << gen_particles.at(i).isPrompt()
                                   << " isHardProcess: " << gen_particles.at(i).isHardProcess()
                                   << " isPromptFinalState: " << gen_particles.at(i).isPromptFinalState()
                                   << " Pt: " << gen_particles.at(i).Pt()
                                   << "\033[0m" << std::endl;
                }
                else
                {
                    std::cout << i << " pid: " << gen_particles.at(i).PID() << " mother index: " << gen_particles.at(i).MotherIndex()
                               << " status: " << gen_particles.at(i).Status() << " isPrompt: " << gen_particles.at(i).isPrompt()
                               << " isHardProcess: " << gen_particles.at(i).isHardProcess()
                               << " Pt: " << gen_particles.at(i).Pt()
                               << std::endl;
                }
            }


            // isHardProcess() particles
            if(gen_particles.at(i).isHardProcess())
            {
                // consider only lepton
                if( abs(current_particle_id) == 11 || abs(current_particle_id)==13 || abs(current_particle_id)==15 )
                {

                    // First lepton flagged as HardProcess
                    if(gen_lepton_from_hardprocess_found == false)
                    {
                        // Tau found
                        if(abs(current_particle_id) == 15)
                        {
                            evt_tag_ditau_hardprocess = 1;
                            // No further information needed for tautau case
                            break;
                        }

                        gen_lepton_from_hardprocess_found = true;

                        if(abs(current_particle_id) == 11)// electron
                        {
                            evt_tag_dielectron_hardprocess = 1;
                            first_lepton_id_found_in_ME = current_particle_id;
                        }
                        if(abs(current_particle_id) == 13)// muon
                        {
                            evt_tag_dimuon_hardprocess = 1;
                            first_lepton_id_found_in_ME = current_particle_id;
                        }

                        // Save index
                        // particle
                        if(current_particle_id > 0)
                        {
                            gen_particle_index_ME = i;
                        }
                        else
                        {
                            // antiparticle
                            gen_antiparticle_index_ME = i;
                        }
                    }
                    // Second lepton flagged as HardProcess
                    else
                    {
                        // Found opposite-sign dilepton both flagged as HardProcess
                        if( current_particle_id == -first_lepton_id_found_in_ME )
                        {
                            if(current_particle_id > 0)
                            {
                                gen_particle_index_ME = i;
                            }
                            else
                            {
                                gen_antiparticle_index_ME = i;
                            }

                        }
                    }
                }
            } // For isHardProcess Flag
        }// Gen particle loop

        // Basic check for the selected dilpton pairs
        if(!evt_tag_ditau_hardprocess)
        {

            Gen dilep_isPromptFinalState;
            Gen lep_isPromptFinalState;
            Gen antilep_isPromptFinalState;

            // Fiducial phase space
            double leading_muon_pt = 20.;
            double subleading_muon_pt = 10.;
            double muon_eta = 2.4;

            double leading_electron_pt = 25.;
            double subleading_electron_pt = 15.;
            double electron_eta = 2.5;

            if(debug_)
            {
                cout << "n_isPromptFinalState: " << n_isPromptFinalState << endl;
                cout << "n_lepton_isPromptFinalState: " << n_lepton_isPromptFinalState << endl;
            }

            std::sort(gen_lepton_isPromptFinalstate.begin(), gen_lepton_isPromptFinalstate.end(), PtComparing);
            std::sort(gen_antilepton_isPromptFinalstate.begin(), gen_antilepton_isPromptFinalstate.end(), PtComparing);
            std::sort(gen_photon_isPromptFinalstate.begin(), gen_photon_isPromptFinalstate.end(), PtComparing);

            int DYInitIndex = 0;
            int l1index = 0, l2index = 0;
            const int lepton_size = gen_lepton_isPromptFinalstate.size();
            const int antilepton_size = gen_antilepton_isPromptFinalstate.size();
            bool dilep_set = false;
            bool zvertex_found = false;

            // Loop over all the isPromptFinalState Flag leptons pairs
            for(int il1 = 0; il1 < lepton_size; il1++)
            {
                for(int il2 = 0; il2 < antilepton_size; il2++)
                {

                    int DYInitIndex_ = findDYInitIndex(gen_lepton_isPromptFinalstate.at(il1).getIndex(), gen_antilepton_isPromptFinalstate.at(il2).getIndex(), zvertex_found);
                    //cout << "il1: " << il1 << " il2: " << il2 << endl;
                    //cout << "index1: " << gen_lepton_isPromptFinalstate.at(il1).getIndex() << " index2: " << gen_antilepton_isPromptFinalstate.at(il2).getIndex() << endl;
                    //cout << "zvertex_found: " << zvertex_found << endl;

                    // If dilepton index not set before and findDYInitIndex() return the initial DY index (not -1), then set DYInitIndex and dilepton index
                    // Even dilepton index set already, if there is a Z vertex then replace the previous index with the index giving the Z vertex
                    if((!dilep_set && DYInitIndex_ != -1) || (zvertex_found && DYInitIndex_ != -1))
                    {
                        DYInitIndex = DYInitIndex_;
                        l1index = il1;
                        l2index = il2;
                        dilep_set = true;
                        zvertex_found = false;
                    }
                }
            }

            // There are chances that e, mu pair is seletected...
            if(abs(gen_lepton_isPromptFinalstate.at(l1index).PID()) == abs(gen_antilepton_isPromptFinalstate.at(l2index).PID()))
            {

                if(abs(gen_lepton_isPromptFinalstate.at(l1index).PID()) == 11)
                {
                    evt_tag_dielectron_promptfinal = true;
                }

                if(abs(gen_lepton_isPromptFinalstate.at(l1index).PID()) == 13)
                {
                    evt_tag_dimuon_promptfinal = true;
                }

                dilep_isPromptFinalState += gen_lepton_isPromptFinalstate.at(l1index);
                dilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(l2index);

                gen_particle_index_status1     = gen_lepton_isPromptFinalstate.at(l1index).getIndex();
                gen_antiparticle_index_status1 = gen_antilepton_isPromptFinalstate.at(l2index).getIndex();
                dilep_motherID_myalgorithm = gen_particles.at(DYInitIndex).PID();
                if(debug_) cout << "gen_particle_index_status1: " << gen_particle_index_status1 << endl;
                if(debug_) cout << "gen_antiparticle_index_status1: " << gen_antiparticle_index_status1 << endl;
                if(debug_) cout << "DYInitIndex: " << DYInitIndex << endl;

                // save index between status 1 and the DY initial index
                std::map<int, int> index_map;
                saveIndexToMap(gen_lepton_isPromptFinalstate.at(l1index).getIndex(),     DYInitIndex, index_map);
                saveIndexToMap(gen_antilepton_isPromptFinalstate.at(l2index).getIndex(), DYInitIndex, index_map);

                lep_isPromptFinalState     += gen_lepton_isPromptFinalstate.at(l1index);
                antilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(l2index);
    
                // FIXME pass_kinematic_cut_mu_bare_gen->pass_pt_20_10_eta_2p4_bare_gen
                pass_kinematic_cut_mu_bare_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_muon_pt, subleading_muon_pt, muon_eta);
                pass_kinematic_cut_el_bare_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_electron_pt, subleading_electron_pt, electron_eta);

                if(debug_)
                {
                    cout << "----------------------------------------------------------------------------------------------" << endl;
                    cout << "dilepton pt, mass from the two leading leptons: " << (dilep_isPromptFinalState).Pt() << ", " << (dilep_isPromptFinalState).M() << endl;
                }

                int photon_size = gen_photon_isPromptFinalstate.size();
                Gen photon_less_DRp1;
                Gen photon_less_DRp1_from_lepton;
                Gen photon_less_DRp1_from_antilepton;
                Gen photon_greater_DRp1;
                Gen photon_greater_DRp1_nonLeptonMother;
                Gen photon_greater_DRp1_from_lepton;
                Gen photon_greater_DRp1_from_antilepton;

                // Add photons to the selected leptons
                for(int i = 0; i < photon_size; i++)
                {
                    double dr_lepton_gamma     = gen_lepton_isPromptFinalstate.at(l1index).DeltaR(gen_photon_isPromptFinalstate.at(i));
                    double dr_antilepton_gamma = gen_antilepton_isPromptFinalstate.at(l2index).DeltaR(gen_photon_isPromptFinalstate.at(i));

                    photon_motherID_isPromptFinalState_selected.push_back(gen_particles.at(gen_photon_isPromptFinalstate.at(i).MotherIndex()).PID());
                    photon_dRtoParticle_isPromptFinalState_selected.push_back(dr_lepton_gamma);
                    photon_dRtoAntiParticle_isPromptFinalState_selected.push_back(dr_antilepton_gamma);

                    if(debug_)
                    {
                        if(abs(gen_particles.at(gen_photon_isPromptFinalstate.at(i).MotherIndex()).PID()) < 10)
                        {
                            cout << "PHOTON'S MOTHER is QUARK" << endl;
                        }
                        if(abs(gen_particles.at(gen_photon_isPromptFinalstate.at(i).MotherIndex()).PID()) == 22)
                        {
                            cout << "PHOTON'S MOTHER is PHOTON" << endl;
                            int mother_index = gen_photon_isPromptFinalstate.at(i).MotherIndex();
                            int motherID_of_this_gamma = abs(gen_particles.at(mother_index).PID());
                            while(motherID_of_this_gamma == 22)
                            {
                                cout << "index: " << mother_index << " ID: " << motherID_of_this_gamma << endl;
                                mother_index = gen_particles.at(mother_index).MotherIndex();
                                motherID_of_this_gamma = abs(gen_particles.at(mother_index).PID()); 
                            }
                        }
                    }

                    if(isMatchedToDYIndexMap(gen_photon_isPromptFinalstate.at(i).MotherIndex(), DYInitIndex, index_map))
                        photon_matchedToLep_isPromptFinalState_selected.push_back(true);
                    else
                    {
                        photon_matchedToLep_isPromptFinalState_selected.push_back(false);
                        if(debug_)
                        {
                            for (std::map<int,int>::iterator it=index_map.begin(); it!=index_map.end(); ++it)
                                std::cout << it->first << " => " << it->second << '\n';
                        }
                    }

                    if(dr_lepton_gamma < 0.1 || dr_antilepton_gamma < 0.1)
                    {
                        photon_less_DRp1 += gen_photon_isPromptFinalstate.at(i);

                        if(dr_lepton_gamma < dr_antilepton_gamma)
                        {
                            photon_less_DRp1_from_lepton += gen_photon_isPromptFinalstate.at(i);
                        }
                        else
                        {
                            photon_less_DRp1_from_antilepton += gen_photon_isPromptFinalstate.at(i);
                        }
                    }
                    else
                    {
                        // Require photon from leptons decayed from the initial lepton
                        if(isMatchedToDYIndexMap(gen_photon_isPromptFinalstate.at(i).MotherIndex(), DYInitIndex, index_map))
                        {
                            photon_greater_DRp1 += gen_photon_isPromptFinalstate.at(i);

                            if(dr_lepton_gamma < dr_antilepton_gamma)
                            {
                                photon_greater_DRp1_from_lepton += gen_photon_isPromptFinalstate.at(i);
                            }
                            else
                            {
                                photon_greater_DRp1_from_antilepton += gen_photon_isPromptFinalstate.at(i);
                            }
                        }
                        else
                        {
                            photon_greater_DRp1_nonLeptonMother += gen_photon_isPromptFinalstate.at(i);
                        }
                    }
                }

                dilep_isPromptFinalState += photon_less_DRp1;
                dilep_pt_FSRgammaDRp1_gen_ispromptfinal = dilep_isPromptFinalState.Pt();
                dilep_mass_FSRgammaDRp1_gen_ispromptfinal = dilep_isPromptFinalState.M();
                if(debug_) cout << "FSR photon (DR=0.1) summed pt, mass: " << dilep_pt_FSRgammaDRp1_gen_ispromptfinal << ", " << dilep_mass_FSRgammaDRp1_gen_ispromptfinal << endl;

                // need to add FSR photon to lepton to check kinematic cuts
                lep_isPromptFinalState += photon_less_DRp1_from_lepton;
                antilep_isPromptFinalState += photon_less_DRp1_from_antilepton;
                pass_kinematic_cut_mu_FSRgammaDRp1_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_muon_pt, subleading_muon_pt, muon_eta);
                pass_kinematic_cut_el_FSRgammaDRp1_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_electron_pt, subleading_electron_pt, electron_eta);

                dilep_isPromptFinalState += photon_greater_DRp1;
                dilep_pt_FSRgamma_gen_ispromptfinal = dilep_isPromptFinalState.Pt();
                dilep_mass_FSRgamma_gen_ispromptfinal = dilep_isPromptFinalState.M();

                if(DataYear==2016)
                {
                    zptweight_muon = mcCorr->GetISRZPtWeight(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal, Lepton::MUON);
                    zptweight_electron = mcCorr->GetISRZPtWeight(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal, Lepton::ELECTRON);
                }

                dilep_pt_AllFSRgamma_gen_ispromptfinal = (dilep_isPromptFinalState+photon_greater_DRp1_nonLeptonMother).Pt();
                dilep_mass_AllFSRgamma_gen_ispromptfinal = (dilep_isPromptFinalState+photon_greater_DRp1_nonLeptonMother).M();

                lep_isPromptFinalState += photon_greater_DRp1_from_lepton;
                antilep_isPromptFinalState += photon_greater_DRp1_from_antilepton;
                pass_kinematic_cut_mu_FSRgamma_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_muon_pt, subleading_muon_pt, muon_eta);
                pass_kinematic_cut_el_FSRgamma_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_electron_pt, subleading_electron_pt, electron_eta);
                if(debug_) cout << "FSR photon summed pt, mass: " << dilep_pt_FSRgamma_gen_ispromptfinal << ", " << dilep_mass_FSRgamma_gen_ispromptfinal << endl;
                // need to add FSR photon to lepton to check kinematic cuts

                if(fabs(dilep_mass_gen_prefsr-dilep_mass_FSRgamma_gen_ispromptfinal) > 1e-4)
                {
                    if(debug_) cout << "Hard process dilepton mass and QED FSR corrected mass are different" << endl;
                }

                // Add remaining leptons
                for(int il = 0; il < lepton_size; il++)
                {
                    if(l1index == il) continue;
                    dilep_isPromptFinalState += gen_lepton_isPromptFinalstate.at(il);
                    lep_isPromptFinalState += gen_lepton_isPromptFinalstate.at(il);
                }

                for(int ial = 0; ial < antilepton_size; ial++)
                {
                    if(l2index == ial) continue;
                    dilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(ial);
                    antilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(ial);
                }

                dilep_pt_alllepton_FSRgamma_gen_ispromptfinal = dilep_isPromptFinalState.Pt();
                dilep_mass_alllepton_FSRgamma_gen_ispromptfinal = dilep_isPromptFinalState.M();

                pass_kinematic_cut_mu_alllepton_FSRgamma_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_muon_pt, subleading_muon_pt, muon_eta);
                pass_kinematic_cut_el_alllepton_FSRgamma_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_electron_pt, subleading_electron_pt, electron_eta);

                if(debug_)
                {
                    if(fabs((lep_isPromptFinalState+antilep_isPromptFinalState).Pt()-dilep_pt_alllepton_FSRgamma_gen_ispromptfinal) > 1e-5)
                    {
                        cout << "They must be the same please check!" << endl;
                        cout << "dilep_pt_alllepton_FSRgamma_gen_ispromptfinal: " << dilep_pt_alllepton_FSRgamma_gen_ispromptfinal
                             << " " << (lep_isPromptFinalState+antilep_isPromptFinalState).Pt() << endl;
                    }
                }
            }
            else
            {
                // count this case
                if(debug_) cout << "two leading lepton have different PID please check" << endl;
                evt_tag_emu_promptfinal = true;
            }

            dilep_motherID_hardprocess = gen_particles.at(gen_particles.at(gen_particle_index_ME).MotherIndex()).PID();

            // HardProcess dilelpton
            // FIXME better to change names...
            dilep_pt_gen_prefsr   = (gen_particles.at(gen_particle_index_ME) + gen_particles.at(gen_antiparticle_index_ME)).Pt();
            dilep_mass_gen_prefsr = (gen_particles.at(gen_particle_index_ME) + gen_particles.at(gen_antiparticle_index_ME)).M();
            particle_pt_gen_prefsr = gen_particles.at(gen_particle_index_ME).Pt();
            antiparticle_pt_gen_prefsr = gen_particles.at(gen_antiparticle_index_ME).Pt();
            particle_eta_gen_prefsr = gen_particles.at(gen_particle_index_ME).Eta();
            antiparticle_eta_gen_prefsr = gen_particles.at(gen_antiparticle_index_ME).Eta();
            if(debug_)
            {
                cout << "Dilepton mass: " << dilep_mass_gen_prefsr << endl;
            }


            if(!evt_tag_emu_promptfinal)
            {
                if(debug_)
                {
                if(gen_particles.at(gen_particle_index_ME).PID() != gen_particles.at(gen_particle_index_status1).PID() ||
                    gen_particles.at(gen_antiparticle_index_ME).PID() != gen_particles.at(gen_antiparticle_index_status1).PID())
                {
                    // TODO count the number of this case
                    cout << "dilepton pair not selected properly..." << endl;
                }
                // check dilep mass between hardprocess and my algorithm
                if(fabs(dilep_mass_alllepton_FSRgamma_gen_ispromptfinal-dilep_mass_gen_prefsr) > 1e-4)
                {
                    cout << "CHECK THIS EVENTS!" << endl;
                    cout << "Dilept using hard process different from my algorithm." << endl;
                    cout << "delta: " << fabs(dilep_mass_alllepton_FSRgamma_gen_ispromptfinal-dilep_mass_gen_prefsr) << endl;
                    cout << "dilep_mass_alllepton_FSRgamma_gen_ispromptfinal: " << dilep_mass_alllepton_FSRgamma_gen_ispromptfinal << endl;
                    cout << "dilep_mass_gen_prefsr: " << dilep_mass_gen_prefsr << endl;
                }
                }

                dilep_pt_gen_postfsr   = (gen_particles.at(gen_particle_index_status1) + gen_particles.at(gen_antiparticle_index_status1)).Pt();
                dilep_mass_gen_postfsr = (gen_particles.at(gen_particle_index_status1) + gen_particles.at(gen_antiparticle_index_status1)).M();
                particle_pt_gen_postfsr     = gen_particles.at(gen_particle_index_status1).Pt();
                antiparticle_pt_gen_postfsr     = gen_particles.at(gen_antiparticle_index_status1).Pt();
                particle_eta_gen_postfsr     = gen_particles.at(gen_particle_index_status1).Eta();
                antiparticle_eta_gen_postfsr     = gen_particles.at(gen_antiparticle_index_status1).Eta();

                // save post FSR leptons to check dR matching between gen and rec leptons
                leptons_postfsr.push_back(gen_particles.at(gen_particle_index_status1));
                leptons_postfsr.push_back(gen_particles.at(gen_antiparticle_index_status1));
            }
        }

        if(debug_)
        {
            if(evt_tag_dielectron_hardprocess)
            {
                cout << "DY->ee event..." << endl;
            }
            if(evt_tag_dimuon_hardprocess)
            {
                cout << "DY->mumu event..." << endl;
            }
            if(evt_tag_ditau_hardprocess)
            {
                cout << "DY->tautau event..." << endl;
            }
            // check further info for dielectron and dimuon events
            if(!evt_tag_ditau_hardprocess)
            {
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

        if(!save_detector_info)
        {
            newtree->Fill();

            delete evt;
            return;
        }
    }// generator level

    // reconstruction level
    // PassMETFilter needed for ISR?
    // lets save tag for each selection cut
    /////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                     //
    //                                                                                     //
    //                             Reconstruction level                                    //
    //                                                                                     //
    //                                                                                     //
    /////////////////////////////////////////////////////////////////////////////////////////

    if(PassMETFilter()) is_met_filter_passed = true;

    if(evt->PassTrigger(DiMuTrgs)) is_dimu_tri_passed = true;
    if(evt->PassTrigger(DiElTrgs)) is_diel_tri_passed = true;

    // skip events if triggers not fired when generator info is not needed
    if(!save_generator_info && (is_dimu_tri_passed == 0 && is_diel_tri_passed == 0))
    {
        delete evt;
        return;
    }

    // PU
    PileUpWeight=(DataYear==2017) ? &MCCorrection::GetPileUpWeightBySampleName : &MCCorrection::GetPileUpWeight;

    if(!IsDATA)
    {
      evt_weight_pureweight=(mcCorr->*PileUpWeight)(nPileUp,0);
      evt_weight_pureweight_up=(mcCorr->*PileUpWeight)(nPileUp,1);
      evt_weight_pureweight_down=(mcCorr->*PileUpWeight)(nPileUp,-1);
      evt_weight_total_rec *= evt_weight_pureweight;
    }

    // L1 prefire
    if(!IsDATA)
    {
        if(DataYear<=2017)
        {
            evt_weight_l1prefire = L1PrefireReweight_Central;
            evt_weight_l1prefire_up = L1PrefireReweight_Up;
            evt_weight_l1prefire_down = L1PrefireReweight_Down;
            evt_weight_total_rec *= L1PrefireReweight_Central;
        }
    }

    // b veto to reduce ttbar background
    std::vector<Jet::Tagger> vtaggers;
    vtaggers.push_back(Jet::DeepCSV);

    std::vector<Jet::WP> v_wps;
    v_wps.push_back(Jet::Medium);

    //systematic, run dependent: set true for 2017
    bool systematic_btag = true;
    bool run_dependent_btag = false;

    if(DataYear==2017)
    {
        run_dependent_btag = true;
    }
    SetupBTagger(vtaggers,v_wps, systematic_btag, run_dependent_btag);

    vector<Jet> this_AllJets = GetAllJets();
    vector<Jet> jets = SelectJets(this_AllJets, "tight", 30., 2.4);

    int n_bjet_deepcsv_m=0;
    int n_bjet_deepcsv_m_noSF=0;

    for(unsigned int ij = 0 ; ij < jets.size(); ij++)
    {
      if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,true,0)) n_bjet_deepcsv_m++;       // method for getting btag with SF applied to MC
      if(IsBTagged(jets.at(ij), Jet::DeepCSV, Jet::Medium,false,0)) n_bjet_deepcsv_m_noSF++; // method for getting btag with no SF applied to MC
    }

    if(n_bjet_deepcsv_m_noSF == 0) evt_tag_bvetoed_rec = 1;

    float btag_sf = 1, misbtag_sf = 1.;
    float btag_sf_up = 1, misbtag_sf_up = 1.;
    float btag_sf_down = 1, misbtag_sf_down = 1.;

    BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, 0, btag_sf, misbtag_sf);
    BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, 1, btag_sf_up, misbtag_sf_down);
    BtaggingSFEvtbyEvt(jets, Jet::DeepCSV, Jet::Medium, -1, btag_sf_down, misbtag_sf_down);

    if(!IsDATA)
    {
        evt_weight_total_rec *= (btag_sf * misbtag_sf);
        evt_weight_bveto = (btag_sf * misbtag_sf);
        evt_weight_bveto_up = (btag_sf_up * misbtag_sf_up);
        evt_weight_bveto_down = (btag_sf_down * misbtag_sf_down);
    }
    if(debug_) std::cout <<"misbtag_sf: " << misbtag_sf << " btag_sf : " << btag_sf << " n bjets (noSF): " << n_bjet_deepcsv_m_noSF << " n bjets: " << n_bjet_deepcsv_m << std::endl;

    AllMuons = GetAllMuons();
    AllElectrons = GetAllElectrons();

    clearVariables();
    AnalyzerParameter param;

    nominal_selection->initVariables();
    executeEventFromParameter(param, nominal_selection, false, 0);
    param.Clear();

    if(!make_zptcorr_ntuple)
    {

        //---------------------- for fake estimation
        // set parameters
        // Muon ID
        param.Muon_Tight_ID = "HNTight";
        param.Muon_ID = "HNLoose";
        param.Muon_FR_ID = "HNtypeI_V1";     // ID name in histmap_Muon.txt
        param.Muon_FR_Key = "AwayJetPt40";   // histname
        param.Muon_UsePtCone = true;

        // Electron ID
        param.Electron_Tight_ID = "ISRTight";
        param.Electron_ID = "ISRLoose";
        param.Electron_FR_ID = "HNtypeI_V1";     // ID name in histmap_Electron.txt
        param.Electron_FR_Key = "AwayJetPt40";   // histname
        param.Electron_UsePtCone = true;

        // Jet ID
        param.Jet_ID = "tight";
        param.FatJet_ID = "tight";

        clearVariables();
        fake_estimation->initVariables();
        executeEventFromParameter(param, fake_estimation, true);
        param.Clear();
        //---------------------------------------------------------------//

        // for lepton momentum variation
        clearVariables();
        lepton_momentum_scale_up->initVariables();
        executeEventFromParameter(param, lepton_momentum_scale_up, false, 1);
        param.Clear();

        clearVariables();
        lepton_momentum_scale_down->initVariables();
        executeEventFromParameter(param, lepton_momentum_scale_down, false, 2);
        param.Clear();

        clearVariables();
        lepton_momentum_res_up->initVariables();
        executeEventFromParameter(param, lepton_momentum_res_up, false, 3);
        param.Clear();

        clearVariables();
        lepton_momentum_res_down->initVariables();
        executeEventFromParameter(param, lepton_momentum_res_down, false, 4);
        param.Clear();

        clearVariables();
        without_lepton_momentum->initVariables();
        executeEventFromParameter(param, without_lepton_momentum, false, 0, false);
        param.Clear();
    }
    newtree->Fill();
    delete evt;
}

bool Skim_ISR::PassKinematicCuts(const Gen lep1, const Gen lep2, double leading_pt, double subleading_pt, double eta)
{
    if((lep1.Pt() > leading_pt && lep2.Pt() > subleading_pt) || (lep1.Pt() > subleading_pt && lep2.Pt() > leading_pt))
    {
        if(fabs(lep1.Eta()) < eta && fabs(lep2.Eta()) < eta)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Skim_ISR::clearVariables()
{
    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();
}

void Skim_ISR::executeEventFromParameter(AnalyzerParameter param, Analysis_Variables* p_struct, bool is_fake_estimation, const int scale_res_sys, bool apply_lep_corr)
{

    vector<Muon> this_AllMuons = AllMuons;
    vector<Electron> this_AllElectrons = AllElectrons;

    if(!is_fake_estimation)
    {
        // select analysis leptons
        vector<Muon> muons_         = GetMuons("POGTightWithTightIso", 7., 2.4, apply_lep_corr, false, 0, 0, scale_res_sys);
        vector<Electron> electrons_ = GetElectrons("passMediumID",     9., 2.5, apply_lep_corr, scale_res_sys);

        vector<Muon> veto_muons_         = GetMuons("POGLooseWithLooseIso", 7., 2.4, apply_lep_corr, false, 0, 0, scale_res_sys);
        vector<Electron> veto_electrons_ = GetElectrons("passVetoID",       9., 2.5, apply_lep_corr, scale_res_sys);

        std::sort(muons_.begin(), muons_.end(), PtComparing);
        std::sort(electrons_.begin(), electrons_.end(), PtComparing);

        std::sort(veto_muons_.begin(), veto_muons_.end(), PtComparing);
        std::sort(veto_electrons_.begin(), veto_electrons_.end(), PtComparing);

        if(muons_.size() == 2)
        {
            IsMuMu = 1;

            int veto_mu_size = veto_muons_.size();
            p_struct->additional_veto_mu_size_ = 0;
            for(int i = 0; i < veto_mu_size; i++)
            {
                if(muons_.at(0).getNtupleIndex() != veto_muons_.at(i).getNtupleIndex() &&
                    muons_.at(1).getNtupleIndex() != veto_muons_.at(i).getNtupleIndex())
                    p_struct->additional_veto_mu_size_++;
            }
            p_struct->additional_veto_el_size_ = veto_electrons.size();
        }
        if(electrons_.size() == 2)
        {
            IsElEl = 1;

            int veto_el_size = veto_electrons_.size();
            p_struct->additional_veto_el_size_ = 0;
            for(int i = 0; i < veto_el_size; i++)
            {
                if(electrons_.at(0).getNtupleIndex() != veto_electrons_.at(i).getNtupleIndex() &&
                    electrons_.at(1).getNtupleIndex() != veto_electrons_.at(i).getNtupleIndex())
                    p_struct->additional_veto_el_size_++;
            }
            p_struct->additional_veto_mu_size_ = veto_muons_.size();
        }

        if((IsMuMu && is_dimu_tri_passed) || (IsElEl && is_diel_tri_passed))
        {
            if(IsMuMu == 1)
            {
                leps=MakeLeptonPointerVector(muons_);
                p_struct->evt_tag_dimuon_rec_ = 1;
                Lep0PtCut = 20.;
                Lep1PtCut = 10.;
                LepEtaCut = 2.4;

                LeptonReco_SF = NULL;
                LeptonID_SF   = &MCCorrection::MuonID_SF;
                LeptonISO_SF  = &MCCorrection::MuonISO_SF;
                if(DataYear==2016)
                {
                    idSF_key =  "NUM_TightID_DEN_genTracks";
                    isoSF_key = "NUM_TightRelIso_DEN_TightIDandIPCut";
                    leading_trig_key =    "Lead17_POGTight";
                    subleading_trig_key = "Tail8_POGTight";
                    DZfilter_key = "";
                }
                else if(DataYear==2017)
                {
                    idSF_key =  "NUM_TightID_DEN_genTracks";
                    isoSF_key = "NUM_TightRelIso_DEN_TightIDandIPCut";
                    leading_trig_key = "LeadMu17_POGTight";
                    subleading_trig_key = "TailMu8_POGTight";
                    DZfilter_key = "";
                }
                else if(DataYear==2018)
                {
                    idSF_key =  "NUM_TightID_DEN_genTracks";
                    isoSF_key = "NUM_TightRelIso_DEN_TightIDandIPCut";
                    leading_trig_key =    "LeadMu17_POGTight";
                    subleading_trig_key = "LeadMu8_POGTight";
                    DZfilter_key = "";
                }
                else
                {
                    cout<<endl;
                    exit(EXIT_FAILURE);

                }
            }
            if(IsElEl == 1)
            {
                leps=MakeLeptonPointerVector(electrons_);
                p_struct->evt_tag_dielectron_rec_ = 1;
                Lep0PtCut = 25.;
                Lep1PtCut = 15.;
                LepEtaCut = 2.5;

                LeptonISO_SF  = NULL;
                if(DataYear==2016)
                {
                    LeptonReco_SF = &MCCorrection::ElectronReco_SF;
                    LeptonID_SF   = &MCCorrection::ElectronID_SF;
                    idSF_key = "passMediumID";
                    leading_trig_key =    "LeadEle23_MediumID";
                    subleading_trig_key = "TailEle12_MediumID";
                    DZfilter_key = "DZfilter";
                }
                else if(DataYear==2017)
                {
                    LeptonReco_SF = &MCCorrection::ElectronReco_SF;
                    LeptonID_SF   = &MCCorrection::ElectronID_SF;
                    idSF_key = "passMediumID";
                    leading_trig_key =    "LeadEle23_MediumID";
                    subleading_trig_key = "TailEle12_MediumID";
                    DZfilter_key = "";
                }
                else if(DataYear==2018)
                {
                    LeptonReco_SF = &MCCorrection::ElectronReco_SF;
                    LeptonID_SF   = &MCCorrection::ElectronID_SF;
                    idSF_key = "passMediumID";
                    leading_trig_key =    "TailEle23_MediumID";
                    subleading_trig_key = "TailEle12_MediumID";
                    DZfilter_key = "";

                }
                else
                {
                    cout<<endl;
                    exit(EXIT_FAILURE);
                }
            }

            // lepton pt cut requirement
            if(leps.at(0)->Pt() > Lep0PtCut && leps.at(1)->Pt() > Lep1PtCut)
            {
                p_struct->evt_tag_leptonpt_sel_rec_ = 1;
            }

            // lepton eta cut requirement
            if(leps.at(0)->LeptonFlavour()==Lepton::ELECTRON)
            {

                Electron *el1 = (Electron *)( leps.at(0) );
                Electron *el2 = (Electron *)( leps.at(1) );

                if((fabs(el1->scEta()) < 1.4442 || fabs(el1->scEta()) > 1.566) && (fabs(el2->scEta()) < 1.4442 || fabs(el2->scEta()) > 1.566) &&
                    fabs(el1->scEta()) < LepEtaCut && fabs(el2->scEta()) < LepEtaCut)
                {
                    p_struct->evt_tag_leptoneta_sel_rec_ = 1;
                }

            }
            else
            {
                if(fabs(leps.at(0)->Eta()) < LepEtaCut && fabs(leps.at(1)->Eta()) < LepEtaCut)
                {
                        p_struct->evt_tag_leptoneta_sel_rec_ = 1;
                }
            }

            // opposite charge requirements
            if((leps.at(0)->Charge() + leps.at(1)->Charge()) == 0)
            {
                p_struct->evt_tag_oppositecharge_sel_rec_ = 1;
            }

            p_struct->leadinglep_pt_rec_     = leps.at(0)->Pt();
            p_struct->subleadinglep_pt_rec_  = leps.at(1)->Pt();
            p_struct->leadinglep_eta_rec_    = leps.at(0)->Eta();
            p_struct->subleadinglep_eta_rec_ = leps.at(1)->Eta();
            p_struct->dilep_pt_rec_          = (*(leps.at(0))+*(leps.at(1))).Pt();
            p_struct->dilep_mass_rec_        = (*(leps.at(0))+*(leps.at(1))).M();

            if(p_struct->evt_tag_leptonpt_sel_rec_ && p_struct->evt_tag_leptoneta_sel_rec_ && p_struct->evt_tag_oppositecharge_sel_rec_ && evt_tag_bvetoed_rec)
            {
                p_struct->evt_tag_analysisevnt_sel_rec_ = 1;
            }

            // save lepton SFs
            if(!IsDATA)
            {
                // trigger SF
                if(leading_trig_key != "")
                {
                    p_struct->evt_weight_trigSF_rec_ *=      mcCorr->DiLeptonTrg_SF(leading_trig_key, subleading_trig_key, leps, 0);
                    p_struct->evt_weight_trigSF_up_rec_ *=   mcCorr->DiLeptonTrg_SF(leading_trig_key, subleading_trig_key, leps, 1);
                    p_struct->evt_weight_trigSF_down_rec_ *= mcCorr->DiLeptonTrg_SF(leading_trig_key, subleading_trig_key, leps, -1);
                }
                if(DZfilter_key != "")
                {
                    p_struct->evt_weight_trigSFDZ_rec_ *= mcCorr->ElectronDZfilter_SF(DZfilter_key, leps, nPV, 0);
                    p_struct->evt_weight_trigSFDZ_up_rec_ *= mcCorr->ElectronDZfilter_SF(DZfilter_key, leps, nPV, 1);
                    p_struct->evt_weight_trigSFDZ_down_rec_ *= mcCorr->ElectronDZfilter_SF(DZfilter_key, leps, nPV, -1);
                }

                // reco/id/iso SF
                for( unsigned int i = 0; i< 2; i++)
                {
                    if(p_struct->evt_tag_dimuon_rec_)
                    {
                        // ID SF
                        p_struct->evt_weight_idSF_rec_ *=      LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                        p_struct->evt_weight_idSF_up_rec_ *=   LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  1) : 1.;
                        p_struct->evt_weight_idSF_down_rec_ *= LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  -1) : 1.;

                        // Iso SF
                        p_struct->evt_weight_isoSF_rec_ *=      LeptonISO_SF?(mcCorr->*LeptonISO_SF)(isoSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                        p_struct->evt_weight_isoSF_up_rec_ *=   LeptonISO_SF?(mcCorr->*LeptonISO_SF)(isoSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  1) : 1.;
                        p_struct->evt_weight_isoSF_down_rec_ *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(isoSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  -1) : 1.;
                    }
                    else
                    {
                        // ID SF
                        p_struct->evt_weight_idSF_rec_ *=      LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  0) : 1.;
                        p_struct->evt_weight_idSF_up_rec_ *=   LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  1) : 1.;
                        p_struct->evt_weight_idSF_down_rec_ *= LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  -1) : 1.;

                        p_struct->evt_weight_recoSF_rec_ *=      LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  0) : 1.;
                        p_struct->evt_weight_recoSF_up_rec_ *=   LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  1) : 1.;
                        p_struct->evt_weight_recoSF_down_rec_ *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  -1) : 1.;
                    }
                }
            }
        } // events with two leptons passing ID and trigger requirements
    }
    else
    {
        vector<Muon> muons_         = SelectMuons(this_AllMuons, param.Muon_ID, 10., 2.4);
        vector<Electron> electrons_ = SelectElectrons(this_AllElectrons, param.Electron_ID, 10., 2.5);
        std::sort(muons_.begin(), muons_.end(), PtComparing);
        std::sort(electrons_.begin(), electrons_.end(), PtComparing);

        IsMuMu = 0;
        IsElEl = 0;

        // check how to handel third lepton veto for fake estimation
        if(muons_.size() == 2)     IsMuMu = 1;
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

        if(IsMuMu == 1)
        {

            if(evt->PassTrigger(DiMuTrgs) )
            {
                leps=MakeLeptonPointerVector(muons_);
                p_struct->evt_tag_dimuon_rec_ = 1;
                Lep0PtCut = 20.;
                Lep1PtCut = 10.;
                LepEtaCut = 2.4;

            }
        }

        if(IsElEl == 1)
        {

            if(evt->PassTrigger(DiElTrgs) )
            {
                leps=MakeLeptonPointerVector(electrons_);
                p_struct->evt_tag_dielectron_rec_ = 1;
                Lep0PtCut = 25.;
                Lep1PtCut = 15.;
                LepEtaCut = 2.5;

            }
        }

        if( leps.size() == 2 )
        { // leps have leptons passing ID and trigger passed

            // lepton pt cut requirement
            if(leps.at(0)->Pt() > Lep0PtCut && leps.at(1)->Pt() > Lep1PtCut)
                p_struct->evt_tag_leptonpt_sel_rec_ = 1;

            // lepton eta cut requirement
            if(fabs(leps.at(0)->Eta()) < LepEtaCut && fabs(leps.at(1)->Eta()) < LepEtaCut)
            {

                if(leps.at(0)->LeptonFlavour()==Lepton::ELECTRON)
                {

                    Electron *el1 = (Electron *)( leps.at(0) );
                    Electron *el2 = (Electron *)( leps.at(1) );

                    if((fabs(el1->scEta()) < 1.4442 || fabs(el1->scEta()) > 1.566) && (fabs(el2->scEta()) < 1.4442 || fabs(el2->scEta()) > 1.566) && fabs(el1->scEta()) < LepEtaCut && fabs(el2->scEta()) < LepEtaCut)
                        p_struct->evt_tag_leptoneta_sel_rec_ = 1;

                }
                else
                {
                    p_struct->evt_tag_leptoneta_sel_rec_ = 1;
                }
            }

            // opposite charge requirements
            if((leps.at(0)->Charge() + leps.at(1)->Charge()) == 0)
            {
                p_struct->evt_tag_oppositecharge_sel_rec_ = 1;
            }

            p_struct->leadinglep_pt_rec_ =     leps.at(0)->Pt();
            p_struct->subleadinglep_pt_rec_ =  leps.at(1)->Pt();
            p_struct->leadinglep_eta_rec_ =    leps.at(0)->Eta();
            p_struct->subleadinglep_eta_rec_ = leps.at(1)->Eta();
            p_struct->dilep_pt_rec_ =          (*(leps.at(0))+*(leps.at(1))).Pt();
            p_struct->dilep_mass_rec_ =        (*(leps.at(0))+*(leps.at(1))).M();

            if(p_struct->evt_tag_leptonpt_sel_rec_ && p_struct->evt_tag_leptoneta_sel_rec_ && evt_tag_bvetoed_rec)
                p_struct->evt_tag_analysisevnt_sel_rec_ = 1;

            bool pass_TT_ = false;
            bool pass_TL_ = false;
            bool pass_LL_ = false;
            double weight_TT_ = 1.;
            double weight_TL_ = 1.;
            double weight_LL_ = 1.;

            // TT, LT tag and corresponding fake rate estimation
            fakeEst->GetWeight(leps, param, pass_TT_, pass_TL_, pass_LL_, weight_TT_, weight_TL_, weight_LL_, 0, true);

            p_struct->evt_tag_TT_rec_ = pass_TT_;
            p_struct->evt_tag_TL_rec_ = pass_TL_;
            p_struct->evt_tag_LL_rec_ = pass_LL_;
            p_struct->evt_weight_TT_rec_ = weight_TT_;
            p_struct->evt_weight_TL_rec_ = weight_TL_;
            p_struct->evt_weight_LL_rec_ = weight_LL_;
        }
    }
}

int Skim_ISR::findDYInitIndex(int l1_index, int l2_index, bool &zvertex)
{

    bool leptonVertex = false;
    std::vector<int> l1_index_vector;
    std::vector<int> l2_index_vector;
    std::vector<int> v_intersection(100);
    std::vector<int>::iterator it;

    // Save all ancestor particle index upto the second index, or the first Z index 
    saveIndexToVector(l1_index, 2, l1_index_vector);
    saveIndexToVector(l2_index, 2, l2_index_vector);

    std::sort (l1_index_vector.begin(), l1_index_vector.end());
    std::sort (l2_index_vector.begin(), l2_index_vector.end());

    it=std::set_intersection(l1_index_vector.begin(), l1_index_vector.end(),
                             l2_index_vector.begin(), l2_index_vector.end(), v_intersection.begin());

    v_intersection.resize(it-v_intersection.begin());
    std::sort(v_intersection.begin(), v_intersection.end(), greater <>());

    // Check intersection has lepton vertex... ex) e+->e+, e-, e+
    // If so, return -1
    int vsize = v_intersection.size();

    for(int i = 0; i < vsize; i++)
    {
        if(gen_particles.at(v_intersection.at(i)).PID() == 23) zvertex = true;
        if(abs(gen_particles.at(v_intersection.at(i)).PID()) == 11 || abs(gen_particles.at(v_intersection.at(i)).PID()) == 13)
            leptonVertex = true;
    }

    if(v_intersection.size() == 0)
        return -1;
    else
        if(leptonVertex)
            return -1;
        else
            return v_intersection.at(0);
}

bool Skim_ISR::isMatchedToDYIndexMap(int mother_index, int DYInitIndex, std::map<int,int> &partindex_map)
{

    bool temp = false;

    if(mother_index < DYInitIndex)
        return false;
    else
    {
        if(!MCSample.Contains("PHOTOS"))
        {
            if(partindex_map.find(mother_index) != partindex_map.end() && (abs(gen_particles.at(mother_index).PID()) == 11 || abs(gen_particles.at(mother_index).PID()) == 13))
            {
                return true;
            }
            else
            {
                temp = isMatchedToDYIndexMap(gen_particles.at(mother_index).MotherIndex(), DYInitIndex, partindex_map);
            }
        }
        else
        {
            if(partindex_map.find(mother_index) != partindex_map.end() && (abs(gen_particles.at(mother_index).PID()) == 23))
            {
                return true;
            }
            else
            {
                temp = isMatchedToDYIndexMap(gen_particles.at(mother_index).MotherIndex(), DYInitIndex, partindex_map);
            }

        }
    }
    return temp;
}

                                                 // DY initial index
void Skim_ISR::saveIndexToMap(int current_index, int mother_index, std::map<int,int> &partindex_map)
{

    if(current_index <= mother_index)
    {
       partindex_map.insert(std::make_pair(mother_index, gen_particles.at(mother_index).PID()));
    }
    else
    {
         partindex_map.insert(std::make_pair(current_index, gen_particles.at(current_index).PID()));
         saveIndexToMap(gen_particles.at(current_index).MotherIndex(), mother_index, partindex_map);
    }
}

void Skim_ISR::saveIndexToVector(int current_index, int mother_index, std::vector<int> &partindex_vector)
{

    int next_mother_index = gen_particles.at(current_index).MotherIndex();
    partindex_vector.push_back(current_index);
    if(current_index <= mother_index || gen_particles.at(next_mother_index).PID() == 23)
    {
        if(current_index <= mother_index)
            partindex_vector.push_back(mother_index);
        else
            partindex_vector.push_back(next_mother_index);
    }
    else
    {
        saveIndexToVector(next_mother_index, mother_index, partindex_vector);
    }
}


void Analysis_Variables::initVariables()
{
    evt_tag_analysisevnt_sel_rec_   = false;
    evt_tag_oppositecharge_sel_rec_ = false;
    evt_tag_leptonpt_sel_rec_       = false;
    evt_tag_leptoneta_sel_rec_      = false;
    evt_tag_dielectron_rec_         = false;
    evt_tag_dimuon_rec_             = false;

    additional_veto_mu_size_ = 0;
    additional_veto_el_size_ = 0;

    evt_tag_TT_rec_                 = false;
    evt_tag_TL_rec_                 = false;
    evt_tag_LL_rec_                 = false;
    evt_weight_TT_rec_              = 1.;
    evt_weight_TL_rec_              = 1.;
    evt_weight_LL_rec_              = 1.;

    dilep_pt_rec_                   = -999.;
    dilep_mass_rec_                 = -999.;
    leadinglep_pt_rec_              = -999.;
    subleadinglep_pt_rec_           = -999.;
    leadinglep_eta_rec_             = -999.;
    subleadinglep_eta_rec_          = -999.;

    evt_weight_recoSF_rec_ = 1.,        evt_weight_recoSF_up_rec_ = 1.,         evt_weight_recoSF_down_rec_ = 1.;
    evt_weight_idSF_rec_ = 1.,          evt_weight_idSF_up_rec_ = 1.,           evt_weight_idSF_down_rec_ = 1.;
    evt_weight_isoSF_rec_ = 1.,         evt_weight_isoSF_up_rec_ = 1.,          evt_weight_isoSF_down_rec_ = 1.;
    evt_weight_trigSF_rec_ = 1.,        evt_weight_trigSF_up_rec_ = 1.,         evt_weight_trigSF_down_rec_ = 1.;
    evt_weight_trigSFDZ_rec_ = 1.,      evt_weight_trigSFDZ_up_rec_ = 1.,       evt_weight_trigSFDZ_down_rec_ = 1.;
}

void Analysis_Variables::setBranch(TTree *tree)
{

    tree->Branch(evt_tag_analysisevnt_sel_rec_brname,      &evt_tag_analysisevnt_sel_rec_);
    tree->Branch(evt_tag_oppositecharge_sel_rec_brname,    &evt_tag_oppositecharge_sel_rec_);
    tree->Branch(evt_tag_leptonpt_sel_rec_brname,          &evt_tag_leptonpt_sel_rec_);
    tree->Branch(evt_tag_leptoneta_sel_rec_brname,         &evt_tag_leptoneta_sel_rec_);
    tree->Branch(evt_tag_dielectron_rec_brname,            &evt_tag_dielectron_rec_);
    tree->Branch(evt_tag_dimuon_rec_brname,                &evt_tag_dimuon_rec_);
    tree->Branch(additional_veto_mu_size_brname,           &additional_veto_mu_size_);
    tree->Branch(additional_veto_el_size_brname,           &additional_veto_el_size_);
    tree->Branch(evt_tag_TT_rec_brname,                    &evt_tag_TT_rec_);
    tree->Branch(evt_tag_TL_rec_brname,                    &evt_tag_TL_rec_);
    tree->Branch(evt_tag_LL_rec_brname,                    &evt_tag_LL_rec_);
    tree->Branch(evt_weight_TT_rec_brname,                 &evt_weight_TT_rec_);
    tree->Branch(evt_weight_TL_rec_brname,                 &evt_weight_TL_rec_);
    tree->Branch(evt_weight_LL_rec_brname,                 &evt_weight_LL_rec_);
    tree->Branch(dilep_pt_rec_brname,                      &dilep_pt_rec_);
    tree->Branch(dilep_mass_rec_brname,                    &dilep_mass_rec_);
    tree->Branch(leadinglep_pt_rec_brname,                 &leadinglep_pt_rec_);
    tree->Branch(subleadinglep_pt_rec_brname,              &subleadinglep_pt_rec_);
    tree->Branch(leadinglep_eta_rec_brname,                &leadinglep_eta_rec_);
    tree->Branch(subleadinglep_eta_rec_brname,             &subleadinglep_eta_rec_);

    tree->Branch(evt_weight_recoSF_rec_brname,          &evt_weight_recoSF_rec_);
    tree->Branch(evt_weight_recoSF_up_rec_brname,       &evt_weight_recoSF_up_rec_);
    tree->Branch(evt_weight_recoSF_down_rec_brname,     &evt_weight_recoSF_down_rec_);
    tree->Branch(evt_weight_idSF_rec_brname,            &evt_weight_idSF_rec_);
    tree->Branch(evt_weight_idSF_up_rec_brname,         &evt_weight_idSF_up_rec_);
    tree->Branch(evt_weight_idSF_down_rec_brname,       &evt_weight_idSF_down_rec_);
    tree->Branch(evt_weight_isoSF_rec_brname,           &evt_weight_isoSF_rec_);
    tree->Branch(evt_weight_isoSF_up_rec_brname,        &evt_weight_isoSF_up_rec_);
    tree->Branch(evt_weight_isoSF_down_rec_brname,      &evt_weight_isoSF_down_rec_);
    tree->Branch(evt_weight_trigSF_rec_brname,          &evt_weight_trigSF_rec_);
    tree->Branch(evt_weight_trigSF_up_rec_brname,       &evt_weight_trigSF_up_rec_);
    tree->Branch(evt_weight_trigSF_down_rec_brname,     &evt_weight_trigSF_down_rec_);
    tree->Branch(evt_weight_trigSFDZ_rec_brname,        &evt_weight_trigSFDZ_rec_);
    tree->Branch(evt_weight_trigSFDZ_up_rec_brname,     &evt_weight_trigSFDZ_up_rec_);
    tree->Branch(evt_weight_trigSFDZ_down_rec_brname,   &evt_weight_trigSFDZ_down_rec_);
}

Skim_ISR::Skim_ISR()
{
    save_detector_info = false;
    save_generator_info = false;
    make_zptcorr_ntuple = false;
}

Skim_ISR::~Skim_ISR()
{

}

void Skim_ISR::WriteHist()
{

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

