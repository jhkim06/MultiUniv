#include "Skim_ISR.h"

void Skim_ISR::initializeAnalyzer(){
    
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

    if(save_detector_info)
    {

        // New Branch
        // branches below include which might be better to be handled in varialbe skim later
        newtree->Branch("additional_veto_mu_size", &additional_veto_mu_size,"additional_veto_mu_size/I");
        newtree->Branch("additional_veto_el_size", &additional_veto_el_size,"additional_veto_el_size/I");
        newtree->Branch("el1_ntuple_index", &el1_ntuple_index,"el1_ntuple_index/I");
        newtree->Branch("el2_ntuple_index", &el2_ntuple_index,"el2_ntuple_index/I");
        newtree->Branch("mu1_ntuple_index", &mu1_ntuple_index,"mu1_ntuple_index/I");
        newtree->Branch("mu2_ntuple_index", &mu2_ntuple_index,"mu2_ntuple_index/I");
        newtree->Branch("dilep_pt_rec", &dilep_pt_rec,"dilep_pt_rec/D");
        newtree->Branch("dilep_mass_rec", &dilep_mass_rec,"dilep_mass_rec/D");
        newtree->Branch("leadinglep_pt_rec", &leadinglep_pt_rec,"leadinglep_pt_rec/D");
        newtree->Branch("subleadinglep_pt_rec", &subleadinglep_pt_rec,"subleadinglep_pt_rec/D");
        newtree->Branch("leadinglep_eta_rec", &leadinglep_eta_rec,"leadinglep_eta_rec/D");
        newtree->Branch("subleadinglep_eta_rec", &subleadinglep_eta_rec,"subleadinglep_eta_rec/D");
        newtree->Branch("leadinglep_iso_rec", &leadinglep_iso_rec,"leadinglep_iso_rec/D");
        newtree->Branch("subleadinglep_iso_rec", &subleadinglep_iso_rec,"subleadinglep_iso_rec/D");

        newtree->Branch("evt_weight_total_rec",  &evt_weight_total_rec, "evt_weight_total_rec/D");
        newtree->Branch("evt_weight_recoSF_up_rec", &evt_weight_recoSF_up_rec,"evt_weight_recoSF_up_rec/D");
        newtree->Branch("evt_weight_recoSF_down_rec", &evt_weight_recoSF_down_rec,"evt_weight_recoSF_down_rec/D");
        newtree->Branch("evt_weight_recoSF_rec", &evt_weight_recoSF_rec,"evt_weight_recoSF_rec/D");
        newtree->Branch("evt_weight_recoSF_up_rec", &evt_weight_recoSF_up_rec,"evt_weight_recoSF_up_rec/D");
        newtree->Branch("evt_weight_recoSF_down_rec", &evt_weight_recoSF_down_rec,"evt_weight_recoSF_down_rec/D");
        newtree->Branch("evt_weight_idSF_rec",   &evt_weight_idSF_rec,  "evt_weight_idSF_rec/D");
        newtree->Branch("evt_weight_idSF_up_rec",   &evt_weight_idSF_up_rec,  "evt_weight_idSF_up_rec/D");
        newtree->Branch("evt_weight_idSF_down_rec",   &evt_weight_idSF_down_rec,  "evt_weight_idSF_down_rec/D");
        newtree->Branch("evt_weight_isoSF_rec",  &evt_weight_isoSF_rec, "evt_weight_isoSF_rec/D");
        newtree->Branch("evt_weight_isoSF_up_rec",  &evt_weight_isoSF_up_rec, "evt_weight_isoSF_up_rec/D");
        newtree->Branch("evt_weight_isoSF_down_rec",  &evt_weight_isoSF_down_rec, "evt_weight_isoSF_down_rec/D");
        newtree->Branch("evt_weight_trigSF_rec", &evt_weight_trigSF_rec,"evt_weight_trigSF_rec/D");
        newtree->Branch("evt_weight_trigSF_up_rec", &evt_weight_trigSF_up_rec,"evt_weight_trigSF_up_rec/D");
        newtree->Branch("evt_weight_trigSF_down_rec", &evt_weight_trigSF_down_rec,"evt_weight_trigSF_down_rec/D");
        newtree->Branch("evt_weight_trigSFDZ_rec", &evt_weight_trigSFDZ_rec,"evt_weight_trigSFDZ_rec/D");
        newtree->Branch("evt_weight_trigSFDZ_up_rec", &evt_weight_trigSFDZ_up_rec,"evt_weight_trigSFDZ_up_rec/D");
        newtree->Branch("evt_weight_trigSFDZ_down_rec", &evt_weight_trigSFDZ_down_rec,"evt_weight_trigSFDZ_down_rec/D");

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
        newtree->Branch("evt_tag_dielectron_rec", &evt_tag_dielectron_rec,"evt_tag_dielectron_rec/O");
        newtree->Branch("evt_tag_dimuon_rec", &evt_tag_dimuon_rec,"evt_tag_dimuon_rec/O");
        newtree->Branch("evt_tag_leptonpt_sel_rec", &evt_tag_leptonpt_sel_rec,"evt_tag_leptonpt_sel_rec/O");
        newtree->Branch("evt_tag_leptoneta_sel_rec", &evt_tag_leptoneta_sel_rec,"evt_tag_leptoneta_sel_rec/O");
        newtree->Branch("evt_tag_oppositecharge_sel_rec", &evt_tag_oppositecharge_sel_rec,"evt_tag_oppositecharge_sel_rec/O");
        newtree->Branch("evt_tag_analysisevnt_sel_rec", &evt_tag_analysisevnt_sel_rec,"evt_tag_analysisevnt_sel_rec/O");
        newtree->Branch("evt_tag_bvetoed_rec", &evt_tag_bvetoed_rec,"evt_tag_bvetoed_rec/O");

        fake_estimation = new Analysis_SelVariation("Fake");
        fake_estimation->setBranch(newtree);

        lepton_momentum_scale_up = new Analysis_SelVariation("LepMomScaleUp");
        lepton_momentum_scale_down = new Analysis_SelVariation("LepMomScaleDown");

        lepton_momentum_res_up = new Analysis_SelVariation("LepMomResUp");
        lepton_momentum_res_down = new Analysis_SelVariation("LepMomResDown");

        lepton_momentum_scale_up->setBranch(newtree);
        lepton_momentum_scale_down->setBranch(newtree);

        lepton_momentum_res_up->setBranch(newtree);
        lepton_momentum_res_down->setBranch(newtree);
    }

    if(save_generator_info)
    {
        // gen info
        newtree->Branch("evt_tag_dimuon_lhe", &evt_tag_dimuon_lhe,"evt_tag_dimuon_lhe/O");
        newtree->Branch("evt_tag_dielectron_lhe", &evt_tag_dielectron_lhe,"evt_tag_dielectron_lhe/O");

        newtree->Branch("evt_tag_ditau_gen", &evt_tag_ditau_gen,"evt_tag_ditau_gen/O");
        newtree->Branch("evt_tag_dielectron_gen", &evt_tag_dielectron_gen,"evt_tag_dielectron_gen/O");
        newtree->Branch("evt_tag_dimuon_gen", &evt_tag_dimuon_gen,"evt_tag_dimuon_gen/O");

        newtree->Branch("n_lepton_isPromptFinalState", &n_lepton_isPromptFinalState, "n_lepton_isPromptFinalState/I");
        newtree->Branch("n_isPromptFinalState", &n_isPromptFinalState, "n_isPromptFinalState/I");
        newtree->Branch("n_lepton_isGammaMother_isPromptFinalState", &n_lepton_isGammaMother_isPromptFinalState, "n_lepton_isGammaMother_isPromptFinalState/I");

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

        newtree->Branch("dilep_pt_lhe", &dilep_pt_lhe,"dilep_pt_lhe/D");
        newtree->Branch("dilep_mass_lhe", &dilep_mass_lhe,"dilep_mass_lhe/D");

        newtree->Branch("dilep_pt_bare_gen_ispromptfinal", &dilep_pt_bare_gen_ispromptfinal,"dilep_pt_bare_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_bare_gen_ispromptfinal", &dilep_mass_bare_gen_ispromptfinal,"dilep_mass_bare_gen_ispromptfinal/D");

        newtree->Branch("dilep_pt_FSRgammaDRp1_gen_ispromptfinal", &dilep_pt_FSRgammaDRp1_gen_ispromptfinal,"dilep_pt_FSRgammaDRp1_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_FSRgammaDRp1_gen_ispromptfinal", &dilep_mass_FSRgammaDRp1_gen_ispromptfinal,"dilep_mass_FSRgammaDRp1_gen_ispromptfinal/D");

        newtree->Branch("dilep_pt_FSRgamma_gen_ispromptfinal", &dilep_pt_FSRgamma_gen_ispromptfinal,"dilep_pt_FSRgamma_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_FSRgamma_gen_ispromptfinal", &dilep_mass_FSRgamma_gen_ispromptfinal,"dilep_mass_FSRgamma_gen_ispromptfinal/D");

        newtree->Branch("dilep_pt_alllepton_FSRgamma_gen_ispromptfinal", &dilep_pt_alllepton_FSRgamma_gen_ispromptfinal,"dilep_pt_alllepton_FSRgamma_gen_ispromptfinal/D");
        newtree->Branch("dilep_mass_alllepton_FSRgamma_gen_ispromptfinal", &dilep_mass_alllepton_FSRgamma_gen_ispromptfinal,"dilep_mass_alllepton_FSRgamma_gen_ispromptfinal/D");

        newtree->Branch("is_dimuon_gen", &is_dimuon_gen, "is_dimuon_gen/O");
        newtree->Branch("is_dielectron_gen", &is_dielectron_gen, "is_dielectron_gen/O");
        newtree->Branch("is_emu_gen", &is_emu_gen, "is_emu_gen/O");

        newtree->Branch("pass_kinematic_cut_el_bare_gen", &pass_kinematic_cut_el_bare_gen, "pass_kinematic_cut_el_bare_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_bare_gen", &pass_kinematic_cut_mu_bare_gen, "pass_kinematic_cut_mu_bare_gen/O");

        newtree->Branch("pass_kinematic_cut_el_FSRgammaDRp1_gen", &pass_kinematic_cut_el_FSRgammaDRp1_gen, "pass_kinematic_cut_el_FSRgammaDRp1_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_FSRgammaDRp1_gen", &pass_kinematic_cut_mu_FSRgammaDRp1_gen, "pass_kinematic_cut_mu_FSRgammaDRp1_gen/O");

        newtree->Branch("pass_kinematic_cut_el_FSRgamma_gen", &pass_kinematic_cut_el_FSRgamma_gen, "pass_kinematic_cut_el_FSRgamma_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_FSRgamma_gen", &pass_kinematic_cut_mu_FSRgamma_gen, "pass_kinematic_cut_mu_FSRgamma_gen/O");

        newtree->Branch("pass_kinematic_cut_el_alllepton_FSRgamma_gen", &pass_kinematic_cut_el_alllepton_FSRgamma_gen, "pass_kinematic_cut_el_alllepton_FSRgamma_gen/O");
        newtree->Branch("pass_kinematic_cut_mu_alllepton_FSRgamma_gen", &pass_kinematic_cut_mu_alllepton_FSRgamma_gen, "pass_kinematic_cut_mu_alllepton_FSRgamma_gen/O");

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

    is_met_filter_passed = false;
    is_diel_tri_passed = false;
    is_dimu_tri_passed = false;

    additional_veto_el_size = 0;
    additional_veto_mu_size = 0;

    el1_ntuple_index = -1;
    el2_ntuple_index = -1;
    mu1_ntuple_index = -1;
    mu2_ntuple_index = -1;

    dilep_pt_rec          = -999.;
    dilep_mass_rec        = -999.;
    leadinglep_pt_rec     = -999.;
    subleadinglep_pt_rec  = -999.;
    leadinglep_iso_rec     = -999.;
    subleadinglep_iso_rec  = -999.;
    leadinglep_eta_rec    = -999.;
    subleadinglep_eta_rec = -999.;

    mother_id_of_prefsr_dilep = -999;

    dilep_pt_lhe = -999.;
    dilep_mass_lhe = -999.;

    dilep_pt_bare_gen_ispromptfinal = -999.;
    dilep_mass_bare_gen_ispromptfinal = -999.;

    dilep_pt_FSRgammaDRp1_gen_ispromptfinal = -999.;
    dilep_mass_FSRgammaDRp1_gen_ispromptfinal = -999.;

    dilep_pt_FSRgamma_gen_ispromptfinal = -999.;
    dilep_mass_FSRgamma_gen_ispromptfinal = -999.;

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

    evt_weight_total_gen = 1.;
    evt_weight_total_rec = 1.;
    evt_weight_btag_rec = 1.;

    evt_weight_recoSF_rec = 1., evt_weight_recoSF_up_rec = 1., evt_weight_recoSF_down_rec = 1.;
    evt_weight_idSF_rec = 1.,   evt_weight_idSF_up_rec = 1.,   evt_weight_idSF_down_rec = 1.;
    evt_weight_isoSF_rec = 1.,  evt_weight_isoSF_up_rec = 1.,  evt_weight_isoSF_down_rec = 1.;
    evt_weight_trigSF_rec = 1., evt_weight_trigSF_up_rec = 1., evt_weight_trigSF_down_rec = 1.;
    evt_weight_trigSFDZ_rec = 1., evt_weight_trigSFDZ_up_rec = 1., evt_weight_trigSFDZ_down_rec = 1.;

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

    evt_tag_dielectron_lhe = 0;
    evt_tag_dimuon_lhe = 0;
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

    if(!IsDATA){
        gen_particles.clear();
        gen_particles = GetGens();

        lhe_particles.clear();
        lhe_particles = GetLHEs();
    }

    ///////////////////////////////////////////////////////////////////////////////////////// 
    //
    //
    // Generator level only for Drell-Yan
    //
    //
    ////////////////////////////////////////////////////////////////////////////////////////
    if((MCSample.Contains("DY") || MCSample.Contains("ZTo")) && save_generator_info )
    {
        
        is_dimuon_gen = false;
        is_dielectron_gen = false;
        is_emu_gen = false;
  
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

        Gen summed_lepton_photon_isPromptFinalState;
        n_isPromptFinalState = 0;
        n_lepton_isPromptFinalState = 0;
        n_lepton_isGammaMother_isPromptFinalState = 0;

        bool photos_used = false;
        if(MCSample.Contains("PHOTOS"))
        {
            photos_used = true;
        }
        if(debug_)
        {
            cout << "Generator information for " + MCSample << endl;
        }

        gen_photons.clear();

        bool gen_lepton_from_hardprocess_found = false;
        int first_lepton_id_found_in_ME = 0;

        gen_particle_index_ME         = -1;
        gen_antiparticle_index_ME     = -1;
        gen_particle_index_status1    = -1;
        gen_antiparticle_index_status1 = -1;

        // loop over generator particles
        for( unsigned int i = 0; i < gen_particles.size(); i++)
        {
            int current_particle_id = gen_particles.at(i).PID();

            // isPromptFinalState() flagged gen particle
            if(gen_particles.at(i).isPromptFinalState())
            {
                n_isPromptFinalState++;

                // save electron and muon flagged as isPromptFinalState()
                if(abs(current_particle_id) == 11 || abs(current_particle_id)==13)
                {
                    n_lepton_isPromptFinalState++;
                    summed_lepton_photon_isPromptFinalState += gen_particles.at(i);

                    if(current_particle_id > 0)
                    {
                        gen_lepton_isPromptFinalstate.push_back(gen_particles.at(i));
                    }
                    else
                    {
                        gen_antilepton_isPromptFinalstate.push_back(gen_particles.at(i));
                    }

                    if(gen_particles.at(i).MotherIndex() > 0)
                    {
                        // count number of leptons from gen photon
                        if(gen_particles.at(gen_particles.at(i).MotherIndex()).PID() == 22)
                        {
                            n_lepton_isGammaMother_isPromptFinalState++;
                            if(abs(current_particle_id) == 13)
                            {
                                if(debug_) cout << "gamma* to mu+ mu- case here!" << endl;
                            }
                        }
                    }
                    // save lepton and anti-lepton into each seperate vector
                    // and use the lepton with the highest pt
                }

                if(abs(current_particle_id) == 22)
                {

                    gen_photon_isPromptFinalstate.push_back(gen_particles.at(i));

                    if(gen_particles.at(i).MotherIndex() > 0)
                    {
                        if(abs(gen_particles.at(gen_particles.at(i).MotherIndex()).PID()) == 11 || abs(gen_particles.at(gen_particles.at(i).MotherIndex()).PID()) == 13)
                        {
                            summed_lepton_photon_isPromptFinalState += gen_particles.at(i);
                        }
                        else
                        {
                            if(debug_) cout << "isPromptFinalState gamma not from lepton..." << endl;
                        }
                    }
                }
            }

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

            // particles associated matrix element (ME)
            if(gen_particles.at(i).isHardProcess())
            {
                // consider only lepton
                if( abs(current_particle_id) == 11 || abs(current_particle_id)==13 || abs(current_particle_id)==15 )
                {
                    
                    // first lepton from ME
                    if(gen_lepton_from_hardprocess_found == false)
                    {
                        // tau found
                        if(abs(current_particle_id) == 15)
                        {
                            evt_tag_ditau_gen = 1;
                            // no further information needed for tautau case
                            break;
                        }

                        gen_lepton_from_hardprocess_found = true;

                        if(abs(current_particle_id) == 11)
                        {
                            evt_tag_dielectron_gen = 1;
                            first_lepton_id_found_in_ME = current_particle_id;
                        }
                        if(abs(current_particle_id) == 13)      
                        {
                            evt_tag_dimuon_gen = 1;
                            first_lepton_id_found_in_ME = current_particle_id;
                        }

                        // save index
                        // particle
                        if(current_particle_id > 0){
                            gen_particle_index_ME = i;
                            gen_particle_ME = gen_particles.at(i);
                        }
                        else{
                            // antiparticle
                            gen_antiparticle_index_ME = i;
                            gen_antiparticle_ME = gen_particles.at(i);
                        }

                    }
                    else
                    {
                        // first lepton already found, and now second lepton from ME
                        if( current_particle_id == -first_lepton_id_found_in_ME )
                        {

                            if(current_particle_id > 0)
                            {
                                gen_particle_index_ME = i;
                                gen_particle_ME = gen_particles.at(i);
                            }
                            else
                            {
                                gen_antiparticle_index_ME = i;
                                gen_antiparticle_ME = gen_particles.at(i);
                            }

                        }// found OS dilepton from ME
                    }
                }// electron, muon, tau in ME
            }// ME

            // collect status 1 particles with their mother index
            if(gen_particles.at(i).Status() == 1)
            {
                int id_found_in_ME = 0;

                // save all status 1 photons
                if(current_particle_id==22)
                {
                    gen_photons.push_back(gen_particles.at(i));
                }

                if( abs(current_particle_id) == 11 || abs(current_particle_id)==13 )
                {
                    if(evt_tag_dielectron_gen)
                    {
                        id_found_in_ME = 11;
                    }
                    else if(evt_tag_dimuon_gen)
                    {
                        id_found_in_ME = 13;
                    }
                    else
                    {
                        // lepton not found yet in ME, so just skip current particle...
                        // since no chance that current status 1 particle from leptons from ME
                        // but there should be no such case
                        continue;
                    }

                    // find the initial index of the current lepton (status 1 and prompt)
                    // do this since there are cases
                    // not from hardprocess leptons and stil status 1
                    // basically the same with the firstCopy()
                    int initial_index = findInitialMoterIndex( gen_particles.at(i).MotherIndex(), i);
                    if(current_particle_id==id_found_in_ME && initial_index == gen_particle_index_ME)
                    {
                        gen_particle_status1 = gen_particles.at(i);
                        gen_particle_index_status1 = i;
                    }
                    if(current_particle_id==-id_found_in_ME && initial_index == gen_antiparticle_index_ME)
                    {
                        gen_antiparticle_status1 = gen_particles.at(i);
                        gen_antiparticle_index_status1 = i;
                    }
                }

            }// status 1 particles
        }// gen particle loop

        // basic check for the selected dilpton pairs
        if(!evt_tag_ditau_gen)
        {

            Gen dilep_isPromptFinalState;
            Gen lep_isPromptFinalState;
            Gen antilep_isPromptFinalState;

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
                cout << "n_lepton_isGammaMother_isPromptFinalState: " << n_lepton_isGammaMother_isPromptFinalState << endl;
            }

            if(gen_particles.at(gen_particle_index_ME).PID() != gen_particles.at(gen_particle_index_status1).PID() || gen_particles.at(gen_antiparticle_index_ME).PID() != gen_particles.at(gen_antiparticle_index_status1).PID())
            {
                cout << "dilepton pair not selected properly..." << endl;
                exit(EXIT_FAILURE);
            }

            // save following info into output variables
            mother_id_of_prefsr_dilep = gen_particles.at(gen_particles.at(gen_particle_index_ME).MotherIndex()).PID();

            dilep_pt_gen_prefsr   = (gen_particles.at(gen_particle_index_ME) + gen_particles.at(gen_antiparticle_index_ME)).Pt();
            dilep_mass_gen_prefsr = (gen_particles.at(gen_particle_index_ME) + gen_particles.at(gen_antiparticle_index_ME)).M();
            particle_pt_gen_prefsr = gen_particles.at(gen_particle_index_ME).Pt();
            antiparticle_pt_gen_prefsr = gen_particles.at(gen_antiparticle_index_ME).Pt();
            particle_eta_gen_prefsr = gen_particles.at(gen_particle_index_ME).Eta();
            antiparticle_eta_gen_prefsr = gen_particles.at(gen_antiparticle_index_ME).Eta();

            dilep_pt_gen_postfsr   = (gen_particles.at(gen_particle_index_status1) + gen_particles.at(gen_antiparticle_index_status1)).Pt();
            dilep_mass_gen_postfsr = (gen_particles.at(gen_particle_index_status1) + gen_particles.at(gen_antiparticle_index_status1)).M();
            particle_pt_gen_postfsr     = gen_particles.at(gen_particle_index_status1).Pt();
            antiparticle_pt_gen_postfsr     = gen_particles.at(gen_antiparticle_index_status1).Pt();
            particle_eta_gen_postfsr     = gen_particles.at(gen_particle_index_status1).Eta();
            antiparticle_eta_gen_postfsr     = gen_particles.at(gen_antiparticle_index_status1).Eta();

            std::sort(gen_lepton_isPromptFinalstate.begin(), gen_lepton_isPromptFinalstate.end(), PtComparing);
            std::sort(gen_antilepton_isPromptFinalstate.begin(), gen_antilepton_isPromptFinalstate.end(), PtComparing);
            std::sort(gen_photon_isPromptFinalstate.begin(), gen_photon_isPromptFinalstate.end(), PtComparing);

            // check PID of two LEADING leptons are the same to ensure they are from Drell-Yan process
            // Note: mu+mu- and mu-->mu-, e-, e+ with decayed e- has the largest pt. then leading lepton pair can be mu+ e-
            if(abs(gen_lepton_isPromptFinalstate.at(0).PID()) == abs(gen_antilepton_isPromptFinalstate.at(0).PID()))
            {

                if(abs(gen_lepton_isPromptFinalstate.at(0).PID()) == 11)
                {
                    is_dielectron_gen = true;
                }

                if(abs(gen_lepton_isPromptFinalstate.at(0).PID()) == 13)
                {
                    is_dimuon_gen = true;
                }

                dilep_isPromptFinalState += gen_lepton_isPromptFinalstate.at(0);
                dilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(0);
                dilep_pt_bare_gen_ispromptfinal = (dilep_isPromptFinalState).Pt();
                dilep_mass_bare_gen_ispromptfinal = (dilep_isPromptFinalState).M();

                int particle_index = findInitialMoterIndex(gen_lepton_isPromptFinalstate.at(0).MotherIndex(), gen_lepton_isPromptFinalstate.at(0).getIndex());
                int antiparticle_index = findInitialMoterIndex(gen_antilepton_isPromptFinalstate.at(0).MotherIndex(), gen_antilepton_isPromptFinalstate.at(0).getIndex());
                // cout << "particle_index: " << particle_index << endl;
                // cout << "antiparticle_index: " << antiparticle_index << endl;
                // if  PID(particle_index) != initial_PID then the selected lepton is the initial lepton

                // save index between status 1 and the initial ME lepton
                std::map<int, int> index_map;
                saveIndexToMap(gen_lepton_isPromptFinalstate.at(0).getIndex(),     particle_index,     index_map);
                saveIndexToMap(gen_antilepton_isPromptFinalstate.at(0).getIndex(), antiparticle_index, index_map);

                lep_isPromptFinalState += gen_lepton_isPromptFinalstate.at(0);
                antilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(0);

                pass_kinematic_cut_mu_bare_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_muon_pt, subleading_muon_pt, muon_eta);
                pass_kinematic_cut_el_bare_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_electron_pt, subleading_electron_pt, electron_eta);

                if(debug_)
                {
                    cout << "Hardprocess pt, mass: " << dilep_pt_gen_prefsr << ", " << dilep_mass_gen_prefsr << endl;
                    cout << "----------------------------------------------------------------------------------------------" << endl;
                    cout << "dilepton pt, mass from the two leading leptons: " << dilep_pt_bare_gen_ispromptfinal << ", " << dilep_mass_bare_gen_ispromptfinal << endl;
                }

                //dilep_pt_allgamma_gen_ispromptfinal;
                //dilep_mass_allgamma_gen_ispromptfinal;

                int photon_size = gen_photon_isPromptFinalstate.size();
                Gen photon_less_DRp1;
                Gen photon_less_DRp1_from_lepton;
                Gen photon_less_DRp1_from_antilepton;
                Gen photon_greater_DRp1;
                Gen photon_greater_DRp1_from_lepton;
                Gen photon_greater_DRp1_from_antilepton;
                Gen photon_from_nonlepton;

                // Add photons to the selected leptons
                for(int i = 0; i < photon_size; i++)
                {
                    if(gen_photon_isPromptFinalstate.at(i).MotherIndex() > 0)
                    {
                        // photons only from the same lepton ID of the selected post FSR lepton
                        if((abs(gen_particles.at(gen_photon_isPromptFinalstate.at(i).MotherIndex()).PID()) == 11 && is_dielectron_gen)
                            || (abs(gen_particles.at(gen_photon_isPromptFinalstate.at(i).MotherIndex()).PID()) == 13 && is_dimuon_gen))
                        {
                            double dr_lepton_gamma =     gen_lepton_isPromptFinalstate.at(0).DeltaR(gen_photon_isPromptFinalstate.at(i));
                            double dr_antilepton_gamma = gen_antilepton_isPromptFinalstate.at(0).DeltaR(gen_photon_isPromptFinalstate.at(i));

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
                                // require photon from leptons decayed from the initial lepton 
                                if(index_map.find(gen_photon_isPromptFinalstate.at(i).MotherIndex()) != index_map.end())
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
                            }
                        }
                        else
                        {
                            photon_from_nonlepton+=gen_photon_isPromptFinalstate.at(i);
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

                lep_isPromptFinalState += photon_greater_DRp1_from_lepton;
                antilep_isPromptFinalState += photon_greater_DRp1_from_antilepton;
                pass_kinematic_cut_mu_FSRgamma_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_muon_pt, subleading_muon_pt, muon_eta);
                pass_kinematic_cut_el_FSRgamma_gen = PassKinematicCuts(lep_isPromptFinalState, antilep_isPromptFinalState, leading_electron_pt, subleading_electron_pt, electron_eta);
                if(debug_) cout << "FSR photon summed pt, mass: " << dilep_pt_FSRgamma_gen_ispromptfinal << ", " << dilep_mass_FSRgamma_gen_ispromptfinal << endl;
                // need to add FSR photon to lepton to check kinematic cuts

                if(fabs(dilep_mass_gen_prefsr-dilep_mass_FSRgamma_gen_ispromptfinal) > 1e-5)
                {
                    if(debug_) cout << "Hard process dilepton mass and QED FSR corrected mass are different" << endl;
                }

                int lepton_size = gen_lepton_isPromptFinalstate.size();
                int antilepton_size = gen_antilepton_isPromptFinalstate.size();

                // leading lepton already added to dilep_isPromptFinalState
                for(int il = 1; il < lepton_size; il++)
                {
                    dilep_isPromptFinalState += gen_lepton_isPromptFinalstate.at(il);
                    lep_isPromptFinalState += gen_lepton_isPromptFinalstate.at(il);
                }

                // leading lepton already added to dilep_isPromptFinalState
                for(int ial = 1; ial < antilepton_size; ial++)
                {
                    dilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(ial);
                    antilep_isPromptFinalState += gen_antilepton_isPromptFinalstate.at(ial);
                }

                dilep_pt_alllepton_FSRgamma_gen_ispromptfinal = dilep_isPromptFinalState.Pt();
                dilep_mass_alllepton_FSRgamma_gen_ispromptfinal = dilep_isPromptFinalState.M();
                if(debug_) cout << "Add all remaining leptons pt, mass: " << dilep_pt_alllepton_FSRgamma_gen_ispromptfinal << ", " << dilep_mass_alllepton_FSRgamma_gen_ispromptfinal << endl;

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
            else{
                // count this case
                if(debug_) cout << "two leading lepton have different PID please check" << endl;
                is_emu_gen = true;
            }


            // save pre FSR leptons to check dR matching between gen and rec leptons
            leptons_postfsr.push_back(gen_particles.at(gen_particle_index_status1));
            leptons_postfsr.push_back(gen_particles.at(gen_antiparticle_index_status1));

            if( evt_tag_dielectron_gen == 1 && ((particle_pt_gen_postfsr > 25. && antiparticle_pt_gen_postfsr > 15.) || (particle_pt_gen_postfsr > 15. && antiparticle_pt_gen_postfsr > 25.)) && fabs(particle_eta_gen_postfsr) < 2.5 && fabs(antiparticle_eta_gen_postfsr) < 2.5 )
            {
                evt_tag_dielectron_fiducial_post_fsr = true;
            }
            else
            {
                evt_tag_dielectron_fiducial_post_fsr = false;
            }

            if( evt_tag_dimuon_gen == 1 && ((particle_pt_gen_postfsr > 20. && antiparticle_pt_gen_postfsr > 10.) || (particle_pt_gen_postfsr > 10. && antiparticle_pt_gen_postfsr > 20.)) && fabs(particle_eta_gen_postfsr) < 2.4 && fabs(antiparticle_eta_gen_postfsr) < 2.4 )
            {
                evt_tag_dimuon_fiducial_post_fsr = true;
            }
            else
            {
                evt_tag_dimuon_fiducial_post_fsr = false;
            }

            // Dilepton from dressed leptons for dR = X
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
            unsigned int size_gen_photons = gen_photons.size();
            photon_n_gen = size_gen_photons;
            for(unsigned int iph = 0; iph < size_gen_photons; iph++)
            {

                photons_et_gen.push_back(gen_photons.at(iph).Pt());
                photons_mother_id_gen.push_back( gen_particles.at(gen_photons.at(iph).MotherIndex()).PID() );

                // find the closest delta R between photon and lepton and save it
                Double_t dr_gamma_particle = gen_photons.at(iph).DeltaR( gen_particles.at(gen_particle_index_status1) );
                Double_t dr_gamma_antiparticle = gen_photons.at(iph).DeltaR( gen_particles.at(gen_antiparticle_index_status1) );
                Double_t dr_temp;

                bool matched_to_particle = false;
                if(dr_gamma_particle > dr_gamma_antiparticle)
                {
                    photons_closest_dr_to_leptons_gen.push_back(dr_gamma_antiparticle);
                    dr_temp = dr_gamma_antiparticle;
                }
                else
                {
                    photons_closest_dr_to_leptons_gen.push_back(dr_gamma_particle);
                    dr_temp = dr_gamma_particle;
                    matched_to_particle = true;
                }

                if(!photos_used)
                {
                    // check if the current photon's mother is ME leptons or decaying leptons from them
                    if( index_map.find(gen_photons.at(iph).MotherIndex()) != index_map.end() )
                    {
                        lepton_matched_photon_n_gen++;
                        lepton_matched_photons_closest_dr_to_leptons_gen.push_back(dr_temp);
                    }
                }
                else
                {
                    // PHOTOS
                    if( gen_particles.at(gen_photons.at(iph).MotherIndex()).PID() == 23 )
                    {
                        lepton_matched_photon_n_gen++;
                        lepton_matched_photons_closest_dr_to_leptons_gen.push_back(dr_temp);
                    }
                }

                TLorentzVector photon_temp = gen_photons.at(iph);
                for(std::map<Double_t, TLorentzVector>::iterator mapit = dilepton_gamma_p4_drX.begin(); mapit!=dilepton_gamma_p4_drX.end(); mapit++)
                {
                    if(dr_temp < mapit->first){
                        // without requirement that the photon mother is decaying lepton from ME
                        mapit->second += photon_temp;

                        // only for photons sharing the same index with decaying lepton
                        // this is the current way to correct FSR in ISR analysis
                        if(!photos_used)
                        {
                            if( index_map.find(gen_photons.at(iph).MotherIndex()) != index_map.end() )
                            {
                                dilepton_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                photon_p4_drX[mapit->first] += photon_temp;

                                if(matched_to_particle)
                                {
                                    particle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                                else
                                {
                                    antiparticle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                            }
                        }
                        else
                        {

                            if( gen_particles.at(gen_photons.at(iph).MotherIndex()).PID() == 23 )
                            {
                                dilepton_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                photon_p4_drX[mapit->first] += photon_temp;

                                if(matched_to_particle)
                                {
                                    particle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                                else
                                {
                                    antiparticle_lepton_matched_gamma_p4_drX[mapit->first] += photon_temp;
                                }
                            }
                        }// for PHOTOS
                    }
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

            for( ; mapit_particle!=particle_lepton_matched_gamma_p4_drX.end(); mapit_particle++, mapit_antiparticle++)
            {
                if( (((mapit_particle->second).Pt() > 25. && (mapit_antiparticle->second).Pt() > 15) || ((mapit_particle->second).Pt() > 15. && (mapit_antiparticle->second).Pt() > 25))  &&  fabs((mapit_particle->second).Eta()) < 2.5 && fabs((mapit_antiparticle->second).Eta()) < 2.5 )
                {
                    evt_tag_dielectron_fiducial_lepton_matched_dressed_drX.push_back(true);
                }
                else
                {
                    evt_tag_dielectron_fiducial_lepton_matched_dressed_drX.push_back(false);
                }

                if( (((mapit_particle->second).Pt() > 20. && (mapit_antiparticle->second).Pt() > 10) || ((mapit_particle->second).Pt() > 10. && (mapit_antiparticle->second).Pt() > 20))  &&  fabs((mapit_particle->second).Eta()) < 2.4 && fabs((mapit_antiparticle->second).Eta()) < 2.4 )
                {
                    evt_tag_dimuon_fiducial_lepton_matched_dressed_drX.push_back(true);
                }
                else
                {
                    evt_tag_dimuon_fiducial_lepton_matched_dressed_drX.push_back(false);
                }
            }// loop for particle_lepton_matched_gamma_p4_drX and antiparticle_lepton_matched_gamma_p4_drXX

            for(std::map<Double_t, TLorentzVector>::iterator mapit = photon_p4_drX.begin(); mapit!=photon_p4_drX.end(); mapit++)
            {
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

                if(fabs(dilep_pt_gen_lepton_matched_dressed_drX[9]-dilep_pt_FSRgamma_gen_ispromptfinal) > 1e-5)
                {
                    if(debug_) cout << "CHECK THIS EVENTS" << endl;
                    cout << "dilep_pt_gen_lepton_matched_dressed_drX[9]: " << dilep_pt_gen_lepton_matched_dressed_drX[9] << endl;
                    cout << "dilep_pt_FSRgamma_gen_ispromptfinal: " << dilep_pt_FSRgamma_gen_ispromptfinal << endl;

                    cout << "dilep_mass_gen_lepton_matched_dressed_drX[9]: " << dilep_mass_gen_lepton_matched_dressed_drX[9] << endl;
                    cout << "dilep_mass_FSRgamma_gen_ispromptfinal: " << dilep_mass_FSRgamma_gen_ispromptfinal << endl;
                }
            }
        }

        if(!save_detector_info){
            newtree->Fill();

            delete evt;
            return;
        }
    }// generator level

    // reconstruction level
    // PassMETFilter needed for ISR?
    // lets save tag for each selection cut

    if(PassMETFilter()) is_met_filter_passed = true;

    if(evt->PassTrigger(DiMuTrgs)) is_dimu_tri_passed = true;
    if(evt->PassTrigger(DiElTrgs)) is_diel_tri_passed = true;

    // skip events if triggers not fired
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

    // b tag
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
    /////////////////////////////////////////////////////////////////////////////

    AllMuons = GetAllMuons();
    AllElectrons = GetAllElectrons();

    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();

    AnalyzerParameter param;
    // get fake weight
    // Muon ID
    param.Muon_Tight_ID = "HNTight";
    param.Muon_ID = "HNLoose";
    param.Muon_FR_ID = "HNtypeI_V1";     // ID name in histmap_Muon.txt
    param.Muon_FR_Key = "AwayJetPt40";   // histname
    param.Muon_UsePtCone = true;

    // Electron Id
    param.Electron_Tight_ID = "ISRTight";
    param.Electron_ID = "ISRLoose";
    param.Electron_FR_ID = "HNtypeI_V1";     // ID name in histmap_Electron.txt
    param.Electron_FR_Key = "AwayJetPt40";   // histname
    param.Electron_UsePtCone = true;

    // Jet ID
    param.Jet_ID = "tight";
    param.FatJet_ID = "tight";

    //if(IsDATA){
    fake_estimation->resetVariables();
    executeEventFromParameter(param, fake_estimation, true);
    param.Clear();
    clearVariables();
    //}

    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();

    // for lepton momentum variation
    lepton_momentum_scale_up->resetVariables();
    executeEventFromParameter(param, lepton_momentum_scale_up, false, 1);

    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();
    clearVariables();

    lepton_momentum_scale_down->resetVariables();
    executeEventFromParameter(param, lepton_momentum_scale_down, false, 2);

    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();
    clearVariables();

    lepton_momentum_res_up->resetVariables();
    executeEventFromParameter(param, lepton_momentum_res_up, false, 3);

    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();
    clearVariables();

    lepton_momentum_res_down->resetVariables();
    executeEventFromParameter(param, lepton_momentum_res_down, false, 4);

    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();
    clearVariables();

    // select analysis leptons
    muons =     SelectMuons(AllMuons,         "POGTightWithTightIso", 7., 2.4);
    electrons = SelectElectrons(AllElectrons, "passMediumID",         9., 2.5);

    veto_muons =     SelectMuons(AllMuons,         "POGLooseWithLooseIso", 7., 2.4);
    veto_electrons = SelectElectrons(AllElectrons, "passVetoID",           9., 2.5);
    photons = GetPhotons("passMediumID", 0.5, 2.5, true); // last boolean is for checkPixelSeed

    std::sort(muons.begin(), muons.end(), PtComparing);
    std::sort(electrons.begin(), electrons.end(), PtComparing);

    std::sort(veto_muons.begin(), veto_muons.end(), PtComparing);
    std::sort(veto_electrons.begin(), veto_electrons.end(), PtComparing);
    std::sort(photons.begin(), photons.end(), PtComparing);

    if(muons.size() == 2)
    {
        IsMuMu = 1;
        mu1_ntuple_index = muons.at(0).getNtupleIndex();
        mu2_ntuple_index = muons.at(1).getNtupleIndex();

        int veto_mu_size = veto_muons.size();
        additional_veto_mu_size = 0;
        for(int i = 0; i < veto_mu_size; i++)
        {
            if(muons.at(0).getNtupleIndex() != veto_muons.at(i).getNtupleIndex() && muons.at(1).getNtupleIndex() != veto_muons.at(i).getNtupleIndex())
                additional_veto_mu_size++;
        }
        additional_veto_el_size = veto_electrons.size();
    }
    if(electrons.size() == 2)
    {
        IsElEl = 1;
        el1_ntuple_index = electrons.at(0).getNtupleIndex();
        el2_ntuple_index = electrons.at(1).getNtupleIndex();

        int veto_el_size = veto_electrons.size();
        additional_veto_el_size = 0;
        for(int i = 0; i < veto_el_size; i++)
        {
            if(electrons.at(0).getNtupleIndex() != veto_electrons.at(i).getNtupleIndex() && electrons.at(1).getNtupleIndex() != veto_electrons.at(i).getNtupleIndex())
                additional_veto_el_size++;
        }
        additional_veto_mu_size = veto_muons.size();
    }

    if((IsMuMu && is_dimu_tri_passed) || (IsElEl && is_diel_tri_passed))
    {

        if(IsMuMu == 1)
        {

            leps=MakeLeptonPointerVector(muons);
            evt_tag_dimuon_rec = 1;
            // set kinematic cuts
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

            leps=MakeLeptonPointerVector(electrons);
            evt_tag_dielectron_rec = 1;
            // set kinematic cuts
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
            else{
                cout<<endl;
                exit(EXIT_FAILURE);
            }
        }

        // lepton pt cut requirement
        if(leps.at(0)->Pt() > Lep0PtCut && leps.at(1)->Pt() > Lep1PtCut)
        {
            evt_tag_leptonpt_sel_rec = 1;
        }

        // lepton eta cut requirement
        if(leps.at(0)->LeptonFlavour()==Lepton::ELECTRON)
        {

            Electron *el1 = (Electron *)( leps.at(0) );
            Electron *el2 = (Electron *)( leps.at(1) );

            if((fabs(el1->scEta()) < 1.4442 || fabs(el1->scEta()) > 1.566) && (fabs(el2->scEta()) < 1.4442 || fabs(el2->scEta()) > 1.566) && fabs(el1->scEta()) < LepEtaCut && fabs(el2->scEta()) < LepEtaCut)
            {
                evt_tag_leptoneta_sel_rec = 1;
            }

        }
        else
        {
            if(fabs(leps.at(0)->Eta()) < LepEtaCut && fabs(leps.at(1)->Eta()) < LepEtaCut)
            {
                    evt_tag_leptoneta_sel_rec = 1;
            }
        }

        // opposite charge requirements
        if((leps.at(0)->Charge() + leps.at(1)->Charge()) == 0){
            evt_tag_oppositecharge_sel_rec = 1;
        }

        leadinglep_pt_rec =     leps.at(0)->Pt();
        subleadinglep_pt_rec =  leps.at(1)->Pt();
        leadinglep_eta_rec =    leps.at(0)->Eta();
        subleadinglep_eta_rec = leps.at(1)->Eta();
        leadinglep_iso_rec =    leps.at(0)->RelIso();
        subleadinglep_iso_rec = leps.at(1)->RelIso();
        dilep_pt_rec =   (*(leps.at(0))+*(leps.at(1))).Pt();
        dilep_mass_rec = (*(leps.at(0))+*(leps.at(1))).M();

        // lepton SF
        if(!IsDATA)
        {
            // trigger SF
            if(leading_trig_key != "")
            {
                evt_weight_trigSF_rec *=      mcCorr->DiLeptonTrg_SF(leading_trig_key, subleading_trig_key, leps, 0);
                evt_weight_trigSF_up_rec *=   mcCorr->DiLeptonTrg_SF(leading_trig_key, subleading_trig_key, leps, 1);
                evt_weight_trigSF_down_rec *= mcCorr->DiLeptonTrg_SF(leading_trig_key, subleading_trig_key, leps, -1);
            }

            if(DZfilter_key != "")
            {
                evt_weight_trigSFDZ_rec *= mcCorr->ElectronDZfilter_SF(DZfilter_key, leps, nPV, 0); 
                evt_weight_trigSFDZ_up_rec *= mcCorr->ElectronDZfilter_SF(DZfilter_key, leps, nPV, 1); 
                evt_weight_trigSFDZ_down_rec *= mcCorr->ElectronDZfilter_SF(DZfilter_key, leps, nPV, -1); 
            }

            // reco/id/iso SF
            for( unsigned int i = 0; i< 2; i++)
            {
                if(evt_tag_dimuon_rec)
                {

                    // ID SF
                    evt_weight_idSF_rec *=      LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                    evt_weight_idSF_up_rec *=   LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  1) : 1.;
                    evt_weight_idSF_down_rec *= LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  -1) : 1.;

                    // Iso SF
                    evt_weight_isoSF_rec *=      LeptonISO_SF?(mcCorr->*LeptonISO_SF)(isoSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                    evt_weight_isoSF_up_rec *=   LeptonISO_SF?(mcCorr->*LeptonISO_SF)(isoSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  1) : 1.;
                    evt_weight_isoSF_down_rec *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(isoSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  -1) : 1.;
                }
                else
                {

                    // ID SF
                    evt_weight_idSF_rec *=      LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  0) : 1.;
                    evt_weight_idSF_up_rec *=   LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  1) : 1.;
                    evt_weight_idSF_down_rec *= LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  -1) : 1.;

                    evt_weight_recoSF_rec *=      LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  0) : 1.;
                    evt_weight_recoSF_up_rec *=   LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  1) : 1.;
                    evt_weight_recoSF_down_rec *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  -1) : 1.;
                }
            }
        }

        if(evt_tag_leptonpt_sel_rec && evt_tag_leptoneta_sel_rec && evt_tag_oppositecharge_sel_rec && evt_tag_bvetoed_rec)
        {
            evt_tag_analysisevnt_sel_rec = 1;
        }

        if(debug_)
        {
            cout << "evt_tag_analysisevnt_sel_rec: " << evt_tag_analysisevnt_sel_rec << endl;
        }

    } // events with two leptons passing ID and trigger requirements

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
}

void Skim_ISR::executeEventFromParameter(AnalyzerParameter param, Analysis_SelVariation* p_struct, bool is_fake_estimation, const int scale_res_sys)
{

    vector<Muon> this_AllMuons = AllMuons;
    vector<Electron> this_AllElectrons = AllElectrons;

    if(!is_fake_estimation)
    {

        // select analysis leptons
        // add option to choose lepton momentum correction
        vector<Muon> muons_         = GetMuons("POGTightWithTightIso", 10., 2.4, true, false, 0, 0, scale_res_sys);
        vector<Electron> electrons_ = GetElectrons("passMediumID",     9., 2.5, false, scale_res_sys);

        vector<Muon> veto_muons_         = GetMuons("POGLooseWithLooseIso", 10., 2.4, true, false, 0, 0, scale_res_sys);
        vector<Electron> veto_electrons_ = GetElectrons("passVetoID",       9., 2.5, false, scale_res_sys);

        std::sort(muons_.begin(), muons_.end(), PtComparing);
        std::sort(electrons_.begin(), electrons_.end(), PtComparing);

        std::sort(veto_muons_.begin(), veto_muons_.end(), PtComparing);
        std::sort(veto_electrons_.begin(), veto_electrons_.end(), PtComparing);

        if(muons_.size() == 2)
        {
            IsMuMu = 1;
            p_struct->mu1_ntuple_index_ = muons_.at(0).getNtupleIndex();
            p_struct->mu2_ntuple_index_ = muons_.at(1).getNtupleIndex();

            int veto_mu_size = veto_muons_.size();
            p_struct->additional_veto_mu_size_ = 0;
            for(int i = 0; i < veto_mu_size; i++){
                if(muons_.at(0).getNtupleIndex() != veto_muons_.at(i).getNtupleIndex() && muons_.at(1).getNtupleIndex() != veto_muons_.at(i).getNtupleIndex())
                    p_struct->additional_veto_mu_size_++;
            }
            p_struct->additional_veto_el_size_ = veto_electrons.size();
        }
        if(electrons_.size() == 2)
        {
            IsElEl = 1;
            p_struct->el1_ntuple_index_ = electrons_.at(0).getNtupleIndex();
            p_struct->el2_ntuple_index_ = electrons_.at(1).getNtupleIndex();

            int veto_el_size = veto_electrons_.size();
            p_struct->additional_veto_el_size_ = 0;
            for(int i = 0; i < veto_el_size; i++){
                if(electrons_.at(0).getNtupleIndex() != veto_electrons_.at(i).getNtupleIndex() && electrons_.at(1).getNtupleIndex() != veto_electrons_.at(i).getNtupleIndex())
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
                if(DataYear==2016){
                    idSF_key =  "NUM_TightID_DEN_genTracks";
                    isoSF_key = "NUM_TightRelIso_DEN_TightIDandIPCut";
                    leading_trig_key =    "Lead17_POGTight";
                    subleading_trig_key = "Tail8_POGTight";
                }
                else if(DataYear==2017){
                    idSF_key =  "NUM_TightID_DEN_genTracks";
                    isoSF_key = "NUM_TightRelIso_DEN_TightIDandIPCut";
                    leading_trig_key = "LeadMu17_POGTight";
                    subleading_trig_key = "TailMu8_POGTight";
                }
                else if(DataYear==2018){
                    idSF_key =  "NUM_TightID_DEN_genTracks";
                    isoSF_key = "NUM_TightRelIso_DEN_TightIDandIPCut";
                    leading_trig_key =    "LeadMu17_POGTight";
                    subleading_trig_key = "LeadMu8_POGTight";

                }
                else{
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
                if(DataYear==2016){
                    LeptonReco_SF = &MCCorrection::ElectronReco_SF;
                    LeptonID_SF   = &MCCorrection::ElectronID_SF;
                    idSF_key = "passMediumID";
                    leading_trig_key =    "LeadEle23_MediumID";
                    subleading_trig_key = "TailEle12_MediumID";
                }
                else if(DataYear==2017){
                    LeptonReco_SF = &MCCorrection::ElectronReco_SF;
                    LeptonID_SF   = &MCCorrection::ElectronID_SF;
                    idSF_key = "passMediumID";
                    leading_trig_key =    "LeadEle23_MediumID";
                    subleading_trig_key = "TailEle12_MediumID";
                }
                else if(DataYear==2018){
                    LeptonReco_SF = &MCCorrection::ElectronReco_SF;
                    LeptonID_SF   = &MCCorrection::ElectronID_SF;
                    idSF_key = "passMediumID";
                    leading_trig_key =    "TailEle23_MediumID";
                    subleading_trig_key = "TailEle12_MediumID";

                }
                else{
                    cout<<endl;
                    exit(EXIT_FAILURE);
                }

            }

            // lepton pt cut requirement
            if(leps.at(0)->Pt() > Lep0PtCut && leps.at(1)->Pt() > Lep1PtCut)
                p_struct->evt_tag_leptonpt_sel_rec_ = 1;

            // lepton eta cut requirement
            if(leps.at(0)->LeptonFlavour()==Lepton::ELECTRON){

                Electron *el1 = (Electron *)( leps.at(0) );
                Electron *el2 = (Electron *)( leps.at(1) );

                if((fabs(el1->scEta()) < 1.4442 || fabs(el1->scEta()) > 1.566) && (fabs(el2->scEta()) < 1.4442 || fabs(el2->scEta()) > 1.566) && fabs(el1->scEta()) < LepEtaCut && fabs(el2->scEta()) < LepEtaCut)
                    p_struct->evt_tag_leptoneta_sel_rec_ = 1;

            }
            else{
                if(fabs(leps.at(0)->Eta()) < LepEtaCut && fabs(leps.at(1)->Eta()) < LepEtaCut){
                        p_struct->evt_tag_leptoneta_sel_rec_ = 1;
                }
            }

            // opposite charge requirements
            if((leps.at(0)->Charge() + leps.at(1)->Charge()) == 0)
                p_struct->evt_tag_oppositecharge_sel_rec_ = 1;

            p_struct->leadinglep_pt_rec_ =     leps.at(0)->Pt();
            p_struct->subleadinglep_pt_rec_ =  leps.at(1)->Pt();
            p_struct->leadinglep_eta_rec_ =    leps.at(0)->Eta();
            p_struct->subleadinglep_eta_rec_ = leps.at(1)->Eta();
            p_struct->dilep_pt_rec_ =   (*(leps.at(0))+*(leps.at(1))).Pt();
            p_struct->dilep_mass_rec_ = (*(leps.at(0))+*(leps.at(1))).M();

            if(p_struct->evt_tag_leptonpt_sel_rec_ && p_struct->evt_tag_leptoneta_sel_rec_ && p_struct->evt_tag_oppositecharge_sel_rec_ && evt_tag_bvetoed_rec)
                p_struct->evt_tag_analysisevnt_sel_rec_ = 1;

            // lepton SF

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
                    if(evt_tag_dimuon_rec)
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

        if(IsMuMu == 1){

            if(evt->PassTrigger(DiMuTrgs) ){
                leps=MakeLeptonPointerVector(muons_);
                p_struct->evt_tag_dimuon_rec_ = 1;
                Lep0PtCut = 20.;
                Lep1PtCut = 10.;
                LepEtaCut = 2.4;

            }
        }

        if(IsElEl == 1){

            if(evt->PassTrigger(DiElTrgs) ){
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

            // save in tree
            //fake_estimation->setVariables(evt_tag_analysisevnt_sel_rec, evt_tag_oppositecharge_sel_rec, evt_tag_dielectron_rec, evt_tag_dimuon_rec, pass_TT_, pass_TL_, pass_LL_, weight_TT_, weight_TL_, weight_LL_, dilep_pt_rec, dilep_mass_rec, leadinglep_pt_rec, subleadinglep_pt_rec, leadinglep_eta_rec, subleadinglep_eta_rec);
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

int Skim_ISR::getInitialMoterIndex(int mother_index, int initial_PID)
{

    int init_index = -1;
    // stop if reached te initial protons
    if(mother_index == -1)
    {
      return -1;
    }
    else if ((gen_particles.at(gen_particles.at(mother_index).MotherIndex()).PID() != gen_particles.at(mother_index).PID()) 
            || (initial_PID != gen_particles.at(mother_index).PID()))
    {
        return mother_index;
    }
    else
    {
        // call again
        init_index = getInitialMoterIndex(gen_particles.at(mother_index).MotherIndex(), initial_PID);
    }

    return init_index;
}

void Skim_ISR::saveIndexToMap(int current_index, int mother_index, std::map<int,int> &partindex_map){

    if(current_index==mother_index)
    {
       partindex_map.insert(std::make_pair(current_index, gen_particles.at(current_index).PID()));
    }
    else
    {
         partindex_map.insert(std::make_pair(current_index, gen_particles.at(current_index).PID()));
         saveIndexToMap(gen_particles.at(current_index).MotherIndex(), mother_index, partindex_map);
    }
}


void Analysis_SelVariation::resetVariables(){

    evt_tag_analysisevnt_sel_rec_   = false;
    evt_tag_oppositecharge_sel_rec_ = false;
    evt_tag_leptonpt_sel_rec_       = false;
    evt_tag_leptoneta_sel_rec_      = false;
    evt_tag_dielectron_rec_         = false;
    evt_tag_dimuon_rec_             = false;

    additional_veto_mu_size_ = 0;
    additional_veto_el_size_ = 0;
    el1_ntuple_index_ = -1;
    el2_ntuple_index_ = -1;
    mu1_ntuple_index_ = -1;
    mu2_ntuple_index_ = -1;

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

    evt_weight_recoSF_rec_ = 1., evt_weight_recoSF_up_rec_ = 1., evt_weight_recoSF_down_rec_ = 1.;
    evt_weight_idSF_rec_ = 1.,   evt_weight_idSF_up_rec_ = 1.,   evt_weight_idSF_down_rec_ = 1.;
    evt_weight_isoSF_rec_ = 1.,  evt_weight_isoSF_up_rec_ = 1.,  evt_weight_isoSF_down_rec_ = 1.;
    evt_weight_trigSF_rec_ = 1., evt_weight_trigSF_up_rec_ = 1., evt_weight_trigSF_down_rec_ = 1.;
    evt_weight_trigSFDZ_rec_ = 1., evt_weight_trigSFDZ_up_rec_ = 1., evt_weight_trigSFDZ_down_rec_ = 1.;

}

void Analysis_SelVariation::setBranch(TTree *tree){

    tree->Branch(evt_tag_analysisevnt_sel_rec_brname,      &evt_tag_analysisevnt_sel_rec_);
    tree->Branch(evt_tag_oppositecharge_sel_rec_brname,    &evt_tag_oppositecharge_sel_rec_);
    tree->Branch(evt_tag_leptonpt_sel_rec_brname,          &evt_tag_leptonpt_sel_rec_);
    tree->Branch(evt_tag_leptoneta_sel_rec_brname,         &evt_tag_leptoneta_sel_rec_);
    tree->Branch(evt_tag_dielectron_rec_brname,            &evt_tag_dielectron_rec_);
    tree->Branch(evt_tag_dimuon_rec_brname,                &evt_tag_dimuon_rec_);
    tree->Branch(additional_veto_mu_size_brname,           &additional_veto_mu_size_);
    tree->Branch(additional_veto_el_size_brname,           &additional_veto_el_size_);
    tree->Branch(el1_ntuple_index_brname,                  &el1_ntuple_index_);
    tree->Branch(el2_ntuple_index_brname,                  &el2_ntuple_index_);
    tree->Branch(mu1_ntuple_index_brname,                  &mu1_ntuple_index_);
    tree->Branch(mu2_ntuple_index_brname,                  &mu2_ntuple_index_);
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

    tree->Branch(evt_weight_recoSF_rec_brname, &evt_weight_recoSF_rec_);
    tree->Branch(evt_weight_recoSF_up_rec_brname, &evt_weight_recoSF_up_rec_);
    tree->Branch(evt_weight_recoSF_down_rec_brname, &evt_weight_recoSF_down_rec_);
    tree->Branch(evt_weight_idSF_rec_brname, &evt_weight_idSF_rec_);
    tree->Branch(evt_weight_idSF_up_rec_brname, &evt_weight_idSF_up_rec_);
    tree->Branch(evt_weight_idSF_down_rec_brname, &evt_weight_idSF_down_rec_);
    tree->Branch(evt_weight_isoSF_rec_brname, &evt_weight_isoSF_rec_);
    tree->Branch(evt_weight_isoSF_up_rec_brname, &evt_weight_isoSF_up_rec_);
    tree->Branch(evt_weight_isoSF_down_rec_brname, &evt_weight_isoSF_down_rec_);
    tree->Branch(evt_weight_trigSF_rec_brname, &evt_weight_trigSF_rec_);
    tree->Branch(evt_weight_trigSF_up_rec_brname, &evt_weight_trigSF_up_rec_);
    tree->Branch(evt_weight_trigSF_down_rec_brname, &evt_weight_trigSF_down_rec_);
    tree->Branch(evt_weight_trigSFDZ_rec_brname, &evt_weight_trigSFDZ_rec_);
    tree->Branch(evt_weight_trigSFDZ_up_rec_brname, &evt_weight_trigSFDZ_up_rec_);
    tree->Branch(evt_weight_trigSFDZ_down_rec_brname, &evt_weight_trigSFDZ_down_rec_);
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

