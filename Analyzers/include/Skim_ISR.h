#ifndef Skim_ISR_h
#define Skim_ISR_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

// dimu variables for FSR photon study
struct Dimu_variables {
    TString muon_id;

    bool evt_tag_analysisevnt_sel_rec_;
    double dimu_pt_rec_;
    double dimu_mass_rec_;
    double dimu_photon_mass_rec_;
    double leadingmuon_pt_rec_;
    double subleadingmuon_pt_rec_;
    double leadingmuon_eta_rec_;
    double subleadingmuon_eta_rec_;
    double leadingphoton_muon_dr_rec_;

    TString  evt_tag_analysisevnt_sel_rec_brname;
    TString  dimu_pt_rec_brname;
    TString  dimu_mass_rec_brname;
    TString  dimu_photon_mass_rec_brname;
    TString  leadingmuon_pt_rec_brname;
    TString  subleadingmuon_pt_rec_brname;
    TString  leadingmuon_eta_rec_brname;
    TString  subleadingmuon_eta_rec_brname;
    TString  leadingphoton_muon_dr_rec_brname;

    Dimu_variables(TString muon_id_="POGTightWithTightIso"): muon_id(muon_id_)
    {
        evt_tag_analysisevnt_sel_rec_ = false;
        dimu_pt_rec_                = -999.;
        dimu_mass_rec_              = -999.;
        dimu_photon_mass_rec_       = -999.;
        leadingmuon_pt_rec_         = -999.;
        subleadingmuon_pt_rec_      = -999.;
        leadingmuon_eta_rec_        = -999.;
        subleadingmuon_eta_rec_     = -999.;
        leadingphoton_muon_dr_rec_  = -999.;

        evt_tag_analysisevnt_sel_rec_brname = "evt_tag_analysisevnt_sel_rec_" + muon_id;
        dimu_pt_rec_brname                 = "dimu_pt_rec_" + muon_id;
        dimu_mass_rec_brname               = "dimu_mass_rec_" + muon_id;
        dimu_photon_mass_rec_brname        = "dimu_photon_mass_rec_" + muon_id;
        leadingmuon_pt_rec_brname          = "leadingmuon_pt_rec_" + muon_id;
        subleadingmuon_pt_rec_brname       = "subleadingmuon_pt_rec_" + muon_id;
        leadingmuon_eta_rec_brname         = "leadingmuon_eta_rec_" + muon_id;
        subleadingmuon_eta_rec_brname      = "subleadingmuon_eta_rec_" + muon_id;
        leadingphoton_muon_dr_rec_brname   = "leadingphoton_muon_dr_rec_" + muon_id;
    }

    void setBranch(TTree *tree);
    void resetVariables();
    void setVariables(bool pass_sel, double dimu_pt, double dimu_mass, double dimu_gamma_mass, double lead_muon_pt, double sublead_muon_pt, double lead_muon_eta, double sublead_muon_eta, double dr_muon_gamma);
};

struct ISR_LeptonIDVariation {
    TString muon_id;
    TString electron_id;
    TString id_sel_name;

    bool evt_tag_analysisevnt_sel_rec_;
    bool evt_tag_dielectron_rec_;
    bool evt_tag_dimuon_rec_;
    double dilep_pt_rec_;
    double dilep_mass_rec_;
    double dilep_photon_mass_rec_;
    double leadinglep_pt_rec_;
    double subleadinglep_pt_rec_;
    double leadinglep_eta_rec_;
    double subleadinglep_eta_rec_;
    double leadingphoton_lep_dr_rec_;

    TString evt_tag_analysisevnt_sel_rec_brname;
    TString evt_tag_dielectron_rec_brname;
    TString evt_tag_dimuon_rec_brname;
    TString dilep_pt_rec_brname;
    TString dilep_mass_rec_brname;
    TString leadinglep_pt_rec_brname;
    TString subleadinglep_pt_rec_brname;
    TString leadinglep_eta_rec_brname;
    TString subleadinglep_eta_rec_brname;

    ISR_LeptonIDVariation(TString muon_id_="POGTightWithTightIso", TString electron_id_ = "passMediumID", TString id_sel_name_ = "Fake"): muon_id(muon_id_), electron_id(electron_id_), id_sel_name(id_sel_name_) 
    {
        evt_tag_analysisevnt_sel_rec_ = false;
        evt_tag_dielectron_rec_ = false;
        evt_tag_dimuon_rec_ = false;
        dilep_pt_rec_                = -999.;
        dilep_mass_rec_              = -999.;
        leadinglep_pt_rec_         = -999.;
        subleadinglep_pt_rec_      = -999.;
        leadinglep_eta_rec_        = -999.;
        subleadinglep_eta_rec_     = -999.;

        evt_tag_analysisevnt_sel_rec_brname = "evt_tag_analysisevnt_sel_rec_" + id_sel_name;
        evt_tag_dielectron_rec_brname = "evt_tag_dielectron_rec_" + id_sel_name;
        evt_tag_dimuon_rec_brname = "evt_tag_dimuon_rec_" + id_sel_name;
        dilep_pt_rec_brname                 = "dilep_pt_rec_" + id_sel_name;
        dilep_mass_rec_brname               = "dilep_mass_rec_" + id_sel_name;
        leadinglep_pt_rec_brname          = "leadinglep_pt_rec_" + id_sel_name;
        subleadinglep_pt_rec_brname       = "subleadinglep_pt_rec_" + id_sel_name;
        leadinglep_eta_rec_brname         = "leadinglep_eta_rec_" + id_sel_name;
        subleadinglep_eta_rec_brname      = "subleadinglep_eta_rec_" + id_sel_name;
    }

    void setBranch(TTree *tree);
    void resetVariables();
    void setVariables(bool pass_sel, bool pass_dielectron, bool pass_dimuon, double dilep_pt, double dilep_mass, double lead_lep_pt, double sublead_lep_pt, double lead_lep_eta, double sublead_lep_eta);
};

class Skim_ISR : public AnalyzerCore {

public:

    void initializeAnalyzer();
    void executeEventFromParameter(AnalyzerParameter param, bool temp_FSR_study = true);
    void executeEvent();
    
    int findInitialMoterIndex(int mother_index, int current_index, bool same_flavor=true);
    void saveIndexToMap(int current_index, int mother_index, std::map<int,int> &partindex_map);
    void clearVariables();

    Skim_ISR();
    ~Skim_ISR();

    TTree *newtree;

    void WriteHist();

private:

    bool debug_;

    int IsMuMu;
    int IsElEl;

    vector<TString> DiMuTrgs;
    vector<TString> DiElTrgs;

    Event* evt;

    bool save_detector_info;
    bool save_generator_info;

    vector<Muon> AllMuons;
    vector<Electron> AllElectrons;

    std::vector<Gen>      gen_particles;
    std::vector<Gen>      gen_photons;
    std::vector<Muon>     muons;
    std::vector<Electron> electrons;
    std::vector<Photon>   photons;
    std::vector<Lepton*>  leps;

    std::vector<Gen> leptons_postfsr;

    bool gen_rec_evt_matched;
    vector<Double_t> gen_rec_lepton_dR;

    Gen gen_particle_ME, gen_antiparticle_ME;
    Gen gen_particle_status1, gen_antiparticle_status1;
    int gen_particle_index_ME, gen_antiparticle_index_ME;
    int gen_particle_index_status1, gen_antiparticle_index_status1;

    double (MCCorrection::*PileUpWeight)(int,int);

    double Lep0PtCut;
    double Lep1PtCut;
    double LepEtaCut;

    int mother_id_of_prefsr_dilep;

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

    std::vector<Double_t> dilep_pt_gen_dressed_drX;
    std::vector<Double_t> dilep_mass_gen_dressed_drX;
    std::vector<Double_t> drX_gen_dressed;

    std::vector<Double_t> dilep_pt_gen_lepton_matched_dressed_drX;
    std::vector<Double_t> dilep_mass_gen_lepton_matched_dressed_drX;
    std::vector<Double_t> drX_gen_lepton_matched_dressed;

    std::vector<Double_t> photons_et_gen;
    std::vector<Int_t> photons_mother_id_gen;
    std::vector<Double_t> photons_closest_dr_to_leptons_gen;
    std::vector<Double_t> lepton_matched_photons_closest_dr_to_leptons_gen;

    std::vector<Bool_t> dielectron_tnp;
    std::vector<Bool_t> dimuon_tnp;
    std::vector<Double_t>  pair_mass_tnp;
    std::vector<Double_t>  evt_weight_tnp;
    std::vector<Double_t>  probe_pt_tnp;
    std::vector<Double_t>  probe_eta_tnp;
    std::vector<Bool_t>    probe_tight_tag_tnp;

    double dilep_pt_rec;
    double dilep_mass_rec;
    double dilep_photon_mass_rec;
    double leadinglep_pt_rec;
    double subleadinglep_pt_rec;
    double leadinglep_eta_rec;
    double subleadinglep_eta_rec;
    double leadingphoton_pt_rec;
    double leadingphoton_eta_rec;
    double leadingphoton_lepton_dr_rec;
    int photon_n_rec;

    double leadingmuon_reliso_rec;
    double subleadingmuon_reliso_rec;

    std::map<TString, Dimu_variables*> Dimu_map;
    ISR_LeptonIDVariation* fake_estimation;

    double evt_weight_fake;
    double evt_weight_total_gen;
    double evt_weight_total_rec;
    double evt_weight_btag_rec;

    double evt_weight_pureweight, evt_weight_pureweight_up, evt_weight_pureweight_down;
    double evt_weight_l1prefire, evt_weight_l1prefire_up, evt_weight_l1prefire_down;
    double evt_weight_bveto, evt_weight_bveto_up, evt_weight_bveto_down;

    bool evt_tag_leptonpt_sel_rec;
    bool evt_tag_leptoneta_sel_rec;
    bool evt_tag_oppositecharge_sel_rec;
    bool evt_tag_analysisevnt_sel_rec;

    int  photon_n_gen;
    int  lepton_matched_photon_n_gen;
    std::vector<double>  lepton_matched_photon_et_gen_drX;
    bool evt_tag_dielectron_fiducial_post_fsr;
    bool evt_tag_dimuon_fiducial_post_fsr;

    std::vector<bool> evt_tag_dielectron_fiducial_lepton_matched_dressed_drX;
    std::vector<bool> evt_tag_dimuon_fiducial_lepton_matched_dressed_drX;

    bool evt_tag_ditau_gen;
    bool evt_tag_dielectron_gen;
    bool evt_tag_dimuon_gen;
    bool evt_tag_dielectron_rec;
    bool evt_tag_dimuon_rec;
    bool evt_tag_bvetoed_rec;

};

#endif

