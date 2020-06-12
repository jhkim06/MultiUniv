#include "Skim_ISRHist.h"

void Skim_ISRHist::initializeAnalyzer()
{
    debug_ = false;
    // Pt
    ptBinningRecElectron= new TUnfoldBinning("Rec_Pt_Ele");
    ptBinningRecMuon= new TUnfoldBinning("Rec_Pt_Mu");
    ptBinningRecElectron->AddAxis("pt",nptBinFine,ptBinFine,false,true);
    ptBinningRecElectron->AddAxis("mass", nmassBinforPt_electron, massBinforPt_electron, true, true);
    ptBinningRecMuon->AddAxis("pt",nptBinFine,ptBinFine,false,true);
    ptBinningRecMuon->AddAxis("mass", nmassBinforPt_muon, massBinforPt_muon, true, true);

    // Mass
    massBinningRec= new TUnfoldBinning("Rec_Mass");
    massBinningRec->AddAxis("mass", nmassBin, massBin, true, true);
    massBinningRec->AddAxis("pt", nptBin_forMass,  ptBin_forMass, false, true);

    //
    //ptBinningRecElectron->CreateHistogram("");

    nominal_selection = new Analysis_HistVariables("Nominal");

    std::cout << "Init Skim_ISRHist " << std::endl;
    // clear vector residual
    DiMuTrgs.clear();
    DiElTrgs.clear();

    cout << "[Skim_ISRHist::initializeAnalyzer] Skim List====================== " << endl;
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
        cout<<"[Skim_ISRHist::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
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

void Skim_ISRHist::executeEvent()
{

    AllMuons.clear();
    AllElectrons.clear();

    muons.clear();
    electrons.clear();
    leps.clear();

    is_met_filter_passed = false;
    is_diel_tri_passed = false;
    is_dimu_tri_passed = false;

    evt_weight_total_rec = 1.;
    evt_weight_btag_rec = 1.;

    evt_weight_pureweight = 1.;
    evt_weight_l1prefire = 1.;
    evt_weight_bveto = 1.;
    evt_tag_bvetoed_rec = 0;
    evt_weight_total_gen = 1.;

    evt = new Event;
    *evt = GetEvent();

    FillHist("CutFlow",5,1,30,0,30);

    if(!IsDATA)
    {
        evt_weight_total_gen *= weight_norm_1invpb*evt->GetTriggerLumi("Full");
        evt_weight_total_gen *= evt->MCweight();

        lhe_particles.clear();
        lhe_particles = GetLHEs();
    }

    if((MCSample.Contains("DY") || MCSample.Contains("ZTo")))
    {
        
        for(int ilhe = 0; ilhe < (int) lhe_particles.size(); ilhe++)
        {
            if(abs(lhe_particles[ilhe].ID())==15)
            {
                delete evt;
                return;
            }
        }
    }
    

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
    if((is_dimu_tri_passed == 0 && is_diel_tri_passed == 0))
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

    delete evt;
}

void Skim_ISRHist::clearVariables()
{
    IsMuMu = 0;
    IsElEl = 0;
    leps.clear();
}

void Skim_ISRHist::executeEventFromParameter(AnalyzerParameter param, Analysis_HistVariables* p_struct, bool is_fake_estimation, const int scale_res_sys)
{

    vector<Muon> this_AllMuons = AllMuons;
    vector<Electron> this_AllElectrons = AllElectrons;

    if(!is_fake_estimation)
    {
        // select analysis leptons
        vector<Muon> muons_         = GetMuons("POGTightWithTightIso", 7., 2.4, true, false, 0, 0, scale_res_sys);
        vector<Electron> electrons_ = GetElectrons("passMediumID",     9., 2.5, true, scale_res_sys);

        vector<Muon> veto_muons_         = GetMuons("POGLooseWithLooseIso", 7., 2.4, true, false, 0, 0, scale_res_sys);
        vector<Electron> veto_electrons_ = GetElectrons("passVetoID",       9., 2.5, true, scale_res_sys);

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


            // Save lepton SFs
            if(!IsDATA)
            {
                // TRIGGER SF
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
                        p_struct->evt_weight_idSF_rec_ *=      LeptonID_SF?(mcCorr->*LeptonID_SF)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.; // TODO
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
            if(p_struct->evt_tag_leptonpt_sel_rec_ && p_struct->evt_tag_leptoneta_sel_rec_ && p_struct->evt_tag_oppositecharge_sel_rec_ && evt_tag_bvetoed_rec && p_struct->evt_tag_dimuon_rec_ && !p_struct->evt_tag_dielectron_rec_)
            {
                p_struct->evt_tag_analysisevnt_sel_rec_ = 1;
                FillHist("DilepMass", p_struct->dilep_mass_rec_, evt_weight_total_gen * evt_weight_total_rec, 500, 0., 500.);

                int binIndex = massBinningRec->GetGlobalBinNumber(p_struct->dilep_mass_rec_, p_struct->dilep_pt_rec_);
                int binIndex_pt = ptBinningRecMuon->GetGlobalBinNumber(p_struct->dilep_pt_rec_, p_struct->dilep_mass_rec_);
                evt_weight_total_rec = evt_weight_total_rec * p_struct->evt_weight_trigSF_rec_ * p_struct->evt_weight_trigSFDZ_rec_;
                if(p_struct->evt_tag_dimuon_rec_)
                {
                    evt_weight_total_rec = evt_weight_total_rec * p_struct->evt_weight_isoSF_rec_;
                }
                else
                {
                    evt_weight_total_rec = evt_weight_total_rec * p_struct->evt_weight_idSF_rec_ * p_struct->evt_weight_recoSF_rec_;
                }

                FillHist("DilepMass_TUnfold", massBinningRec, binIndex, evt_weight_total_gen * evt_weight_total_rec * p_struct->evt_weight_idSF_rec_); // Nominal histogram
                FillHist("DilepPt_TUnfold", ptBinningRecMuon, binIndex_pt, evt_weight_total_gen * evt_weight_total_rec * p_struct->evt_weight_idSF_rec_); // Nominal histogram

                // Make N histograms
                for(int j = 0; j < 500; j++)
                {
                    TString variationPostfix;
                    variationPostfix.Form("%d", j);
                    LeptonID_SF_var = &MCCorrection::MuonID_SF;
                    double evt_weight_idSF_rec_temp = 1.;
                    for(unsigned int i = 0; i< 2; i++)
                    {
                        if(p_struct->evt_tag_dimuon_rec_)
                        {
                            // ID SF
                            evt_weight_idSF_rec_temp *= (mcCorr->*LeptonID_SF_var)(idSF_key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0, variationPostfix); // TODO
                        }
                        else
                        {
                            //
                        }
                    }
                    FillHist("DilepMass_TUnfold_"+variationPostfix, massBinningRec, binIndex, evt_weight_total_gen * evt_weight_total_rec * evt_weight_idSF_rec_temp); // variation
                    FillHist("DilepPt_TUnfold_"+variationPostfix, ptBinningRecMuon, binIndex_pt, evt_weight_total_gen * evt_weight_total_rec * evt_weight_idSF_rec_temp); // variation
                }
            }
        } // events with two leptons passing ID and trigger requirements
    }
}

void Analysis_HistVariables::initVariables()
{
    evt_tag_analysisevnt_sel_rec_   = false;
    evt_tag_oppositecharge_sel_rec_ = false;
    evt_tag_leptonpt_sel_rec_       = false;
    evt_tag_leptoneta_sel_rec_      = false;
    evt_tag_dielectron_rec_         = false;
    evt_tag_dimuon_rec_             = false;

    additional_veto_mu_size_ = 0;
    additional_veto_el_size_ = 0;

    dilep_pt_rec_                   = -999.;
    dilep_mass_rec_                 = -999.;
    leadinglep_pt_rec_              = -999.;
    subleadinglep_pt_rec_           = -999.;
    leadinglep_eta_rec_             = -999.;
    subleadinglep_eta_rec_          = -999.;
    evt_weight_zptcorr_             = 1.;

    evt_weight_recoSF_rec_ = 1.,        evt_weight_recoSF_up_rec_ = 1.,         evt_weight_recoSF_down_rec_ = 1.;
    evt_weight_idSF_rec_ = 1.,          evt_weight_idSF_up_rec_ = 1.,           evt_weight_idSF_down_rec_ = 1.;
    evt_weight_isoSF_rec_ = 1.,         evt_weight_isoSF_up_rec_ = 1.,          evt_weight_isoSF_down_rec_ = 1.;
    evt_weight_trigSF_rec_ = 1.,        evt_weight_trigSF_up_rec_ = 1.,         evt_weight_trigSF_down_rec_ = 1.;
    evt_weight_trigSFDZ_rec_ = 1.,      evt_weight_trigSFDZ_up_rec_ = 1.,       evt_weight_trigSFDZ_down_rec_ = 1.;
}

Skim_ISRHist::Skim_ISRHist()
{
}

Skim_ISRHist::~Skim_ISRHist()
{

}

