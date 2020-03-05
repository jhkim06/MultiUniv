#ifndef Skim_ISR_h
#define Skim_ISR_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

struct Analysis_SelVariation 
{

    TString prefix;

    bool evt_tag_analysisevnt_sel_rec_;
    bool evt_tag_oppositecharge_sel_rec_;
    bool evt_tag_leptonpt_sel_rec_;
    bool evt_tag_leptoneta_sel_rec_;
    bool evt_tag_dielectron_rec_;
    bool evt_tag_dimuon_rec_;

    int additional_veto_mu_size_;
    int additional_veto_el_size_;

    int el1_ntuple_index_;
    int el2_ntuple_index_;

    int mu1_ntuple_index_;
    int mu2_ntuple_index_;

    double dilep_pt_rec_;
    double dilep_mass_rec_;
    double dilep_photon_mass_rec_;
    double leadinglep_pt_rec_;
    double subleadinglep_pt_rec_;
    double leadinglep_eta_rec_;
    double subleadinglep_eta_rec_;
    double leadingphoton_lep_dr_rec_;

    double evt_weight_recoSF_rec_, evt_weight_recoSF_up_rec_, evt_weight_recoSF_down_rec_;
    double evt_weight_idSF_rec_,   evt_weight_idSF_up_rec_,   evt_weight_idSF_down_rec_;
    double evt_weight_isoSF_rec_,  evt_weight_isoSF_up_rec_,  evt_weight_isoSF_down_rec_;
    double evt_weight_trigSF_rec_, evt_weight_trigSF_up_rec_, evt_weight_trigSF_down_rec_;
    double evt_weight_trigSFDZ_rec_, evt_weight_trigSFDZ_up_rec_, evt_weight_trigSFDZ_down_rec_;

    // fake weight
    bool evt_tag_TT_rec_;
    bool evt_tag_TL_rec_;
    bool evt_tag_LL_rec_;
    double evt_weight_TT_rec_;
    double evt_weight_TL_rec_;
    double evt_weight_LL_rec_;

    TString evt_tag_analysisevnt_sel_rec_brname;
    TString evt_tag_oppositecharge_sel_rec_brname;
    TString evt_tag_leptonpt_sel_rec_brname;
    TString evt_tag_leptoneta_sel_rec_brname;
    TString evt_tag_dielectron_rec_brname;
    TString evt_tag_dimuon_rec_brname;

    TString additional_veto_mu_size_brname;
    TString additional_veto_el_size_brname;
    TString el1_ntuple_index_brname;
    TString el2_ntuple_index_brname;
    TString mu1_ntuple_index_brname;
    TString mu2_ntuple_index_brname;

    TString dilep_pt_rec_brname;
    TString dilep_mass_rec_brname;
    TString leadinglep_pt_rec_brname;
    TString subleadinglep_pt_rec_brname;
    TString leadinglep_eta_rec_brname;
    TString subleadinglep_eta_rec_brname;

    TString evt_weight_recoSF_rec_brname, evt_weight_recoSF_up_rec_brname, evt_weight_recoSF_down_rec_brname;
    TString evt_weight_idSF_rec_brname,   evt_weight_idSF_up_rec_brname,   evt_weight_idSF_down_rec_brname;
    TString evt_weight_isoSF_rec_brname,  evt_weight_isoSF_up_rec_brname,  evt_weight_isoSF_down_rec_brname;
    TString evt_weight_trigSF_rec_brname, evt_weight_trigSF_up_rec_brname, evt_weight_trigSF_down_rec_brname;
    TString evt_weight_trigSFDZ_rec_brname, evt_weight_trigSFDZ_up_rec_brname, evt_weight_trigSFDZ_down_rec_brname;

    // branch names for fake
    TString evt_tag_TT_rec_brname;
    TString evt_tag_TL_rec_brname;
    TString evt_tag_LL_rec_brname;
    TString evt_weight_TT_rec_brname;
    TString evt_weight_TL_rec_brname;
    TString evt_weight_LL_rec_brname;

    Analysis_SelVariation(TString prefix_ = "Fake"): prefix(prefix_) 
    {
        evt_tag_analysisevnt_sel_rec_   = false;
        evt_tag_oppositecharge_sel_rec_ = false;
        evt_tag_leptonpt_sel_rec_      = false;
        evt_tag_leptoneta_sel_rec_      = false;
        evt_tag_dielectron_rec_         = false;
        evt_tag_dimuon_rec_             = false;

        additional_veto_mu_size_ = 0;
        additional_veto_el_size_ = 0;
        el1_ntuple_index_ = -1;
        el2_ntuple_index_ = -1;
        mu1_ntuple_index_ = -1;
        mu2_ntuple_index_ = -1;

        dilep_pt_rec_                   = -999.;
        dilep_mass_rec_                 = -999.;
        leadinglep_pt_rec_              = -999.;
        subleadinglep_pt_rec_           = -999.;
        leadinglep_eta_rec_             = -999.;
        subleadinglep_eta_rec_          = -999.;

        evt_tag_TT_rec_           = false;
        evt_tag_TL_rec_           = false;
        evt_tag_LL_rec_           = false;
        evt_weight_TT_rec_           = 1.;
        evt_weight_TL_rec_           = 1.;
        evt_weight_LL_rec_           = 1.;

        evt_weight_recoSF_rec_ = 1., evt_weight_recoSF_up_rec_ = 1., evt_weight_recoSF_down_rec_ = 1.;
        evt_weight_idSF_rec_ = 1.,   evt_weight_idSF_up_rec_ = 1.,   evt_weight_idSF_down_rec_ = 1.;
        evt_weight_isoSF_rec_ = 1.,  evt_weight_isoSF_up_rec_ = 1.,  evt_weight_isoSF_down_rec_ = 1.;
        evt_weight_trigSF_rec_ = 1., evt_weight_trigSF_up_rec_ = 1., evt_weight_trigSF_down_rec_ = 1.;
        evt_weight_trigSFDZ_rec_ = 1., evt_weight_trigSFDZ_up_rec_ = 1., evt_weight_trigSFDZ_down_rec_ = 1.;

        // initialize branch names
        evt_tag_analysisevnt_sel_rec_brname   = "evt_tag_analysisevnt_sel_rec_" + prefix;
        evt_tag_oppositecharge_sel_rec_brname = "evt_tag_oppositecharge_sel_rec_" + prefix;
        evt_tag_leptonpt_sel_rec_brname = "evt_tag_leptonpt_sel_rec_" + prefix;
        evt_tag_leptoneta_sel_rec_brname = "evt_tag_leptoneta_sel_rec_" + prefix;
        evt_tag_dielectron_rec_brname         = "evt_tag_dielectron_rec_" + prefix;
        evt_tag_dimuon_rec_brname             = "evt_tag_dimuon_rec_" + prefix;

        additional_veto_mu_size_brname = "additional_veto_mu_size_" + prefix;
        additional_veto_el_size_brname = "additional_veto_el_size_" + prefix;;
        el1_ntuple_index_brname        = "el1_ntuple_index_" + prefix;
        el2_ntuple_index_brname        = "el2_ntuple_index_" + prefix;
        mu1_ntuple_index_brname        = "mu1_ntuple_index_" + prefix;
        mu2_ntuple_index_brname        = "mu2_ntuple_index_" + prefix;

        dilep_pt_rec_brname                 = "dilep_pt_rec_" + prefix;
        dilep_mass_rec_brname               = "dilep_mass_rec_" + prefix;
        leadinglep_pt_rec_brname            = "leadinglep_pt_rec_" + prefix;
        subleadinglep_pt_rec_brname         = "subleadinglep_pt_rec_" + prefix;
        leadinglep_eta_rec_brname           = "leadinglep_eta_rec_" + prefix;
        subleadinglep_eta_rec_brname        = "subleadinglep_eta_rec_" + prefix;

        evt_tag_TT_rec_brname               = "evt_tag_TT_rec_" + prefix;
        evt_tag_TL_rec_brname               = "evt_tag_TL_rec_" + prefix;
        evt_tag_LL_rec_brname               = "evt_tag_LL_rec_" + prefix;
        evt_weight_TT_rec_brname            = "evt_weight_TT_rec_" + prefix;
        evt_weight_TL_rec_brname            = "evt_weight_TL_rec_" + prefix;
        evt_weight_LL_rec_brname            = "evt_weight_LL_rec_" + prefix;

        evt_weight_recoSF_rec_brname = "evt_weight_recoSF_rec_" + prefix;
        evt_weight_recoSF_up_rec_brname = "evt_weight_recoSF_up_rec_" + prefix;
        evt_weight_recoSF_down_rec_brname = "evt_weight_recoSF_down_rec_" + prefix;
        evt_weight_idSF_rec_brname = "evt_weight_idSF_rec_" + prefix;
        evt_weight_idSF_up_rec_brname = "evt_weight_idSF_up_rec_" + prefix;
        evt_weight_idSF_down_rec_brname = "evt_weight_idSF_down_rec_" + prefix;
        evt_weight_isoSF_rec_brname = "evt_weight_isoSF_rec_" + prefix;
        evt_weight_isoSF_up_rec_brname = "evt_weight_isoSF_up_rec_" + prefix;
        evt_weight_isoSF_down_rec_brname = "evt_weight_isoSF_down_rec_" + prefix;
        evt_weight_trigSF_rec_brname = "evt_weight_trigSF_rec_" + prefix;
        evt_weight_trigSF_up_rec_brname = "evt_weight_trigSF_up_rec_" + prefix;
        evt_weight_trigSF_down_rec_brname = "evt_weight_trigSF_down_rec_" + prefix;
        evt_weight_trigSFDZ_rec_brname = "evt_weight_trigSFDZ_rec_" + prefix;
        evt_weight_trigSFDZ_up_rec_brname = "evt_weight_trigSFDZ_up_rec_" + prefix;
        evt_weight_trigSFDZ_down_rec_brname = "evt_weight_trigSFDZ_down_rec_" + prefix;
    }

    void setBranch(TTree *tree);
    void resetVariables();

};

class Skim_ISR : public AnalyzerCore {

public:

    void initializeAnalyzer();
    void executeEventFromParameter(AnalyzerParameter param, Analysis_SelVariation * p_struct, bool fake_estimation = false, const int scale_res_sys = 0);
    void executeEvent();
    
    int findInitialMoterIndex(int mother_index, int current_index, bool same_flavor=true);
    int findDYInitIndex(int l1_index, int l2_index);
    void saveIndexToMap(int current_index, int mother_index, std::map<int,int> &partindex_map);
    void saveIndexToVector(int current_index, int mother_index, std::vector<int> &partindex_vector);
    bool isMatchedToDYIndexMap(int mother_index, int DYInitIndex, std::map<int,int> &partindex_map);  
    bool PassKinematicCuts(const Gen lep1, const Gen lep2, double leading_pt, double subleading_pt, double eta);
    void clearVariables();

    double FR_template(double pT, double eta);

    Skim_ISR();
    ~Skim_ISR();

    TTree *newtree;

    void WriteHist();

private:

    bool debug_;

    Event* evt;

    int IsMuMu;
    int IsElEl;

    vector<TString> DiMuTrgs;
    vector<TString> DiElTrgs;
    vector<TString> SingleMuTrgs;
    vector<TString> SingleElTrgs;

    // function pointer for Lepton SF
    double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
    double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
    double (MCCorrection::*LeptonReco_SF)(double,double,int);

    double (MCCorrection::*PileUpWeight)(int,int);

    TString leading_trig_key, subleading_trig_key;
    TString DZfilter_key;
    TString idSF_key;
    TString isoSF_key;

    bool save_detector_info;
    bool save_generator_info;

    vector<Muon> AllMuons;
    vector<Electron> AllElectrons;

    std::vector<Gen>      gen_particles;
    std::vector<LHE>      lhe_particles;
    std::vector<Muon>     muons;
    std::vector<Electron> electrons;
    std::vector<Muon>     veto_muons;
    std::vector<Electron> veto_electrons;
    std::vector<Photon>   photons;
    std::vector<Lepton*>  leps;

    // isPromptFinalstate gen particles
    std::vector<Gen> gen_lepton_isPromptFinalstate;
    std::vector<Gen> gen_antilepton_isPromptFinalstate;
    std::vector<Gen> gen_photon_isPromptFinalstate;
    std::vector<Gen> leptons_postfsr;

    bool evt_tag_dimuon_promptfinal;
    bool evt_tag_dielectron_promptfinal;
    bool evt_tag_emu_promptfinal;

    bool pass_kinematic_cut_el_bare_gen;
    bool pass_kinematic_cut_mu_bare_gen;

    bool pass_kinematic_cut_el_FSRgammaDRp1_gen;
    bool pass_kinematic_cut_mu_FSRgammaDRp1_gen;

    bool pass_kinematic_cut_el_FSRgamma_gen;
    bool pass_kinematic_cut_mu_FSRgamma_gen;

    bool pass_kinematic_cut_el_alllepton_FSRgamma_gen;
    bool pass_kinematic_cut_mu_alllepton_FSRgamma_gen;

    double dilep_pt_bare_gen_ispromptfinal;
    double dilep_mass_bare_gen_ispromptfinal;

    double dilep_pt_FSRgammaDRp1_gen_ispromptfinal;
    double dilep_mass_FSRgammaDRp1_gen_ispromptfinal;

    double dilep_pt_FSRgamma_gen_ispromptfinal;
    double dilep_mass_FSRgamma_gen_ispromptfinal;

    double dilep_pt_alllepton_FSRgamma_gen_ispromptfinal;
    double dilep_mass_alllepton_FSRgamma_gen_ispromptfinal;

    LHE lhe_particle, lhe_antiparticle;
    int gen_particle_index_ME, gen_antiparticle_index_ME;
    int gen_particle_index_status1, gen_antiparticle_index_status1;

    double Lep0PtCut;
    double Lep1PtCut;
    double LepEtaCut;

    bool is_met_filter_passed;
    bool is_diel_tri_passed;
    bool is_dimu_tri_passed;

    int additional_veto_mu_size;
    int additional_veto_el_size;

    int el1_ntuple_index;
    int el2_ntuple_index;

    int mu1_ntuple_index;
    int mu2_ntuple_index;

    double dilep_pt_rec;
    double dilep_mass_rec;
    double dilep_photon_mass_rec;
    double leadinglep_pt_rec;
    double subleadinglep_pt_rec;
    double leadinglep_iso_rec;
    double subleadinglep_iso_rec;
    double leadinglep_eta_rec;
    double subleadinglep_eta_rec;

    bool evt_tag_leptonpt_sel_rec;
    bool evt_tag_leptoneta_sel_rec;
    bool evt_tag_oppositecharge_sel_rec;
    bool evt_tag_analysisevnt_sel_rec;

    Analysis_SelVariation* fake_estimation;
    Analysis_SelVariation* lepton_momentum_scale_up;
    Analysis_SelVariation* lepton_momentum_scale_down;
    Analysis_SelVariation* lepton_momentum_res_up;
    Analysis_SelVariation* lepton_momentum_res_down;

    double evt_weight_total_gen;
    double evt_weight_total_rec;
    double evt_weight_btag_rec;

    double evt_weight_pureweight, evt_weight_pureweight_up, evt_weight_pureweight_down;
    double evt_weight_l1prefire,  evt_weight_l1prefire_up,  evt_weight_l1prefire_down;
    double evt_weight_bveto,      evt_weight_bveto_up,      evt_weight_bveto_down;

    double evt_weight_recoSF_rec, evt_weight_recoSF_up_rec, evt_weight_recoSF_down_rec;
    double evt_weight_idSF_rec,   evt_weight_idSF_up_rec,   evt_weight_idSF_down_rec;
    double evt_weight_isoSF_rec,  evt_weight_isoSF_up_rec,  evt_weight_isoSF_down_rec;
    double evt_weight_trigSF_rec, evt_weight_trigSF_up_rec, evt_weight_trigSF_down_rec;
    double evt_weight_trigSFDZ_rec, evt_weight_trigSFDZ_up_rec, evt_weight_trigSFDZ_down_rec;

    // gen level variables
    int dilep_motherID_hardprocess;
    int dilep_motherID_myalgorithm;
    int n_lepton_isPromptFinalState;
    int n_photon_notLeptonMother_isPromptFinalState;
    int n_photon_isPromptFinalState;
    int n_lepton_isGammaMother_isPromptFinalState;
    int n_isPromptFinalState;
    std::vector<Int_t> photon_motherID_isPromptFinalState; 
    std::vector<Int_t> photon_motherID_isPromptFinalState_selected; 
    std::vector<Bool_t> photon_matchedToLep_isPromptFinalState_selected; 
    std::vector<Double_t> photon_dRtoParticle_isPromptFinalState_selected; 
    std::vector<Double_t> photon_dRtoAntiParticle_isPromptFinalState_selected; 

    double dilep_pt_lhe   ;
    double dilep_mass_lhe ;
    double dilep_pt_gen_prefsr   ;
    double dilep_mass_gen_prefsr ;
    double particle_pt_gen_prefsr ;
    double antiparticle_pt_gen_prefsr;
    double particle_eta_gen_prefsr   ;
    double antiparticle_eta_gen_prefsr;

    double dilep_pt_gen_postfsr   ;
    double dilep_mass_gen_postfsr ;
    double particle_pt_gen_postfsr  ;
    double antiparticle_pt_gen_postfsr ;
    double particle_eta_gen_postfsr   ;
    double antiparticle_eta_gen_postfsr;

    std::vector<Double_t> photons_closest_dr_to_leptons_gen;
    std::vector<Double_t> lepton_matched_photons_closest_dr_to_leptons_gen;

    int  photon_n_gen;
    int  lepton_matched_photon_n_gen;
    bool evt_tag_dielectron_fiducial_post_fsr;
    bool evt_tag_dimuon_fiducial_post_fsr;

    bool evt_tag_dielectron_lhe;
    bool evt_tag_dimuon_lhe;
    bool evt_tag_ditau_hardprocess;
    bool evt_tag_dielectron_hardprocess;
    bool evt_tag_dimuon_hardprocess;
    bool evt_tag_dielectron_rec;
    bool evt_tag_dimuon_rec;
    bool evt_tag_bvetoed_rec;

};

#endif

