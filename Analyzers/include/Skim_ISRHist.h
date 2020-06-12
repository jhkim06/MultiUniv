#ifndef Skim_ISRHist_h
#define Skim_ISRHist_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "TUnfoldBinning.h"

const int nptBinFine=17;
const double ptBinFine[nptBinFine+1]={0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.};

const int nptBinCoarse=9;
const double ptBinCoarse[nptBinCoarse+1]={0., 4., 8., 12., 18., 28., 40., 55., 75., 100.};

const int nmassBinforPt_electron = 5;
const int nmassBinforPt_muon = 5;
const Double_t massBinforPt_muon[nmassBinforPt_muon+1] = {40, 64, 81, 101, 200, 320};
const Double_t massBinforPt_electron[nmassBinforPt_electron+1] = {50, 64, 81, 101, 200, 320};

const int nptBin_forMass = 1;
const Double_t ptBin_forMass[nptBin_forMass+1] = {0,100};

const int nmassBin = 34;
const Double_t massBin[nmassBin+1] = {15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320};

struct Analysis_HistVariables
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

    double dilep_pt_rec_;
    double dilep_mass_rec_;
    double dilep_photon_mass_rec_;
    double leadinglep_pt_rec_;
    double subleadinglep_pt_rec_;
    double leadinglep_eta_rec_;
    double subleadinglep_eta_rec_;
    double leadingphoton_lep_dr_rec_;
    double evt_weight_zptcorr_;

    double evt_weight_recoSF_rec_, evt_weight_recoSF_up_rec_, evt_weight_recoSF_down_rec_;
    double evt_weight_idSF_rec_,   evt_weight_idSF_up_rec_,   evt_weight_idSF_down_rec_;
    double evt_weight_isoSF_rec_,  evt_weight_isoSF_up_rec_,  evt_weight_isoSF_down_rec_;
    double evt_weight_trigSF_rec_, evt_weight_trigSF_up_rec_, evt_weight_trigSF_down_rec_;
    double evt_weight_trigSFDZ_rec_, evt_weight_trigSFDZ_up_rec_, evt_weight_trigSFDZ_down_rec_;

    Analysis_HistVariables(TString prefix_ = "Fake"): prefix(prefix_)
    {
        evt_tag_analysisevnt_sel_rec_   = false;
        evt_tag_oppositecharge_sel_rec_ = false;
        evt_tag_leptonpt_sel_rec_       = false;
        evt_tag_leptoneta_sel_rec_      = false;
        evt_tag_dielectron_rec_         = false;
        evt_tag_dimuon_rec_             = false;

        additional_veto_mu_size_ = 0;
        additional_veto_el_size_ = 0;

        evt_weight_zptcorr_             = 1.;
        dilep_pt_rec_                   = -999.;
        dilep_mass_rec_                 = -999.;
        leadinglep_pt_rec_              = -999.;
        subleadinglep_pt_rec_           = -999.;
        leadinglep_eta_rec_             = -999.;
        subleadinglep_eta_rec_          = -999.;

        evt_weight_recoSF_rec_ = 1.,   evt_weight_recoSF_up_rec_ = 1.,   evt_weight_recoSF_down_rec_ = 1.;
        evt_weight_idSF_rec_ = 1.,     evt_weight_idSF_up_rec_ = 1.,     evt_weight_idSF_down_rec_ = 1.;
        evt_weight_isoSF_rec_ = 1.,    evt_weight_isoSF_up_rec_ = 1.,    evt_weight_isoSF_down_rec_ = 1.;
        evt_weight_trigSF_rec_ = 1.,   evt_weight_trigSF_up_rec_ = 1.,   evt_weight_trigSF_down_rec_ = 1.;
        evt_weight_trigSFDZ_rec_ = 1., evt_weight_trigSFDZ_up_rec_ = 1., evt_weight_trigSFDZ_down_rec_ = 1.;
    }

    void initVariables();

};

class Skim_ISRHist : public AnalyzerCore {

public:

    void initializeAnalyzer();
    void executeEventFromParameter(AnalyzerParameter param, Analysis_HistVariables * p_struct, bool fake_estimation = false, const int scale_res_sys = 0);
    void executeEvent();

    void clearVariables();

    Skim_ISRHist();
    ~Skim_ISRHist();

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
    double (MCCorrection::*LeptonID_SF_var)(TString,double,double,int, TString);
    double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
    double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
    double (MCCorrection::*LeptonReco_SF)(double,double,int);

    double (MCCorrection::*PileUpWeight)(int,int);

    TString leading_trig_key, subleading_trig_key;
    TString DZfilter_key;
    TString idSF_key;
    TString isoSF_key;

    vector<Muon> AllMuons;
    vector<Electron> AllElectrons;

    std::vector<LHE>      lhe_particles; 
    std::vector<Muon>     muons;
    std::vector<Electron> electrons;
    std::vector<Muon>     veto_muons;
    std::vector<Electron> veto_electrons;
    std::vector<Lepton*>  leps;

    // isPromptFinalstate gen particles
    bool evt_tag_dimuon_promptfinal;
    bool evt_tag_dielectron_promptfinal;
    bool evt_tag_emu_promptfinal;

    double Lep0PtCut;
    double Lep1PtCut;
    double LepEtaCut;

    bool is_met_filter_passed;
    bool is_diel_tri_passed;
    bool is_dimu_tri_passed;

    Analysis_HistVariables* nominal_selection;

    double evt_weight_total_gen;
    double evt_weight_total_rec;
    double evt_weight_btag_rec;

    double evt_weight_pureweight, evt_weight_pureweight_up, evt_weight_pureweight_down;
    double evt_weight_l1prefire,  evt_weight_l1prefire_up,  evt_weight_l1prefire_down;
    double evt_weight_bveto,      evt_weight_bveto_up,      evt_weight_bveto_down;

    bool evt_tag_bvetoed_rec;

    TUnfoldBinning* ptBinningRecElectron = NULL;
    TUnfoldBinning* ptBinningRecMuon = NULL;
    TUnfoldBinning* massBinningRec = NULL;

};

#endif

