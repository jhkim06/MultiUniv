from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

supercut = '1==1'

LOW_MASS_CUTS = ['40', '60', '80', '100', '200']
HIGH_MASS_CUTS = ['60', '80', '100', '200', '350']

cuts['electron_LHE'] = 'evt_tag_dielectron_lhe'
cuts['muon_LHE'] = 'evt_tag_dimuon_lhe'

cuts['electron_HardProcess'] = 'evt_tag_dielectron_hardprocess'
cuts['muon_HardProcess'] = 'evt_tag_dimuon_hardprocess'

cuts['electron_PromptFinal'] = 'evt_tag_dielectron_promptfinal'
cuts['muon_PromptFinal'] = 'evt_tag_dimuon_promptfinal'

cuts['electron_Acceptance_PromptFinal'] = 'evt_tag_dielectron_promptfinal && pass_kinematic_cut_el_FSRgammaDRp1_gen'
cuts['muon_Acceptance_PromptFinal'] = 'evt_tag_dimuon_promptfinal && pass_kinematic_cut_mu_FSRgammaDRp1_gen'

cuts['electron_Acceptance_Efficiency_PromptFinal'] = 'evt_tag_dielectron_promptfinal && pass_kinematic_cut_el_FSRgammaDRp1_gen && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1'
cuts['muon_Acceptance_Efficiency_PromptFinal'] = 'evt_tag_dimuon_promptfinal && pass_kinematic_cut_mu_FSRgammaDRp1_gen && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1'

cuts['electron_rec_selection'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_dielectron_lhe'
cuts['muon_rec_selection'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_muon_lhe'

for icut in range(len(LOW_MASS_CUTS)):

    LHEMassCut = 'dilep_mass_lhe > ' + LOW_MASS_CUTS[icut] + ' && dilep_mass_lhe < ' + HIGH_MASS_CUTS[icut]
    HardProcessMassCut = 'dilep_mass_gen_prefsr > ' + LOW_MASS_CUTS[icut] + ' && dilep_mass_gen_prefsr < ' + HIGH_MASS_CUTS[icut]
    BareMassCut = 'dilep_mass_gen_postfsr > ' + LOW_MASS_CUTS[icut] + ' && dilep_mass_gen_postfsr < ' + HIGH_MASS_CUTS[icut]
    DressedDRp1MassCut = 'dilep_mass_FSRgammaDRp1_gen_ispromptfinal > ' + LOW_MASS_CUTS[icut] + ' && dilep_mass_FSRgammaDRp1_gen_ispromptfinal < ' + HIGH_MASS_CUTS[icut]
    Dressed4PIMassCut = 'dilep_mass_FSRgamma_gen_ispromptfinal > ' + LOW_MASS_CUTS[icut] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + HIGH_MASS_CUTS[icut]

    cuts['electron_LHE_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_lhe && ' + LHEMassCut
    cuts['muon_LHE_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_muon_lhe && ' + LHEMassCut

    cuts['electron_HardProcess_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_hardprocess && ' + HardProcessMassCut
    cuts['muon_HardProcess_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_hardprocess && ' + HardProcessMassCut

    cuts['electron_PromptFinal_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + BareMassCut
    cuts['muon_PromptFinal_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + BareMassCut

    cuts['electron_PromptFinal_NoFSR_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + BareMassCut + ' && n_photon_isPromptFinalState == 0'
    cuts['muon_PromptFinal_NoFSR_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + BareMassCut + ' && n_photon_isPromptFinalState == 0'

    cuts['electron_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + DressedDRp1MassCut
    cuts['muon_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + DressedDRp1MassCut

    cuts['electron_Pt100Cut_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + DressedDRp1MassCut + ' && dilep_pt_FSRgammaDRp1_gen_ispromptfinal < 100'
    cuts['muon_Pt100Cut_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + DressedDRp1MassCut + ' && dilep_pt_FSRgammaDRp1_gen_ispromptfinal < 100'

    cuts['electron_Pt30Cut_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + DressedDRp1MassCut + ' && dilep_pt_FSRgammaDRp1_gen_ispromptfinal < 30'
    cuts['muon_Pt30Cut_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + DressedDRp1MassCut + ' && dilep_pt_FSRgammaDRp1_gen_ispromptfinal < 30'

    cuts['electron_Pt30to100_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + DressedDRp1MassCut + ' && dilep_pt_FSRgammaDRp1_gen_ispromptfinal > 30 && dilep_pt_FSRgammaDRp1_gen_ispromptfinal < 100'
    cuts['muon_Pt30to100_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + DressedDRp1MassCut + ' && dilep_pt_FSRgammaDRp1_gen_ispromptfinal > 30 && dilep_pt_FSRgammaDRp1_gen_ispromptfinal < 100'

    cuts['electron_Acceptance_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + DressedDRp1MassCut + ' && pass_kinematic_cut_el_FSRgammaDRp1_gen'
    cuts['muon_Acceptance_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + DressedDRp1MassCut + ' && pass_kinematic_cut_mu_FSRgammaDRp1_gen'

    cuts['electron_Acceptance_Efficiency_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + DressedDRp1MassCut + ' && pass_kinematic_cut_el_FSRgammaDRp1_gen && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1'
    cuts['muon_Acceptance_Efficiency_PromptFinalDRp1_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + DressedDRp1MassCut + ' && pass_kinematic_cut_mu_FSRgammaDRp1_gen && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1'

    cuts['electron_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + Dressed4PIMassCut
    cuts['muon_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + Dressed4PIMassCut

    cuts['electron_Pt100Cut_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + Dressed4PIMassCut + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
    cuts['muon_Pt100Cut_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + Dressed4PIMassCut + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100'

    cuts['electron_Pt30Cut_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + Dressed4PIMassCut + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 30'
    cuts['muon_Pt30Cut_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + Dressed4PIMassCut + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 30'

    cuts['electron_Pt30to100_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dielectron_promptfinal && ' + Dressed4PIMassCut + ' && dilep_pt_FSRgamma_gen_ispromptfinal > 30 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
    cuts['muon_Pt30to100_PromptFinal4PI_m' + LOW_MASS_CUTS[icut] + "to" + HIGH_MASS_CUTS[icut]] = 'evt_tag_dimuon_promptfinal && ' + Dressed4PIMassCut + ' && dilep_pt_FSRgamma_gen_ispromptfinal > 30 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'

cuts['electron_PromptFinal_flagged_m10to500'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500'
cuts['muon_PromptFinal_flagged_m10to500'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500'

cuts['electron_PromptFinal_flagged_m10to500_PID1'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 1'
cuts['muon_PromptFinal_flagged_m10to500_PID1'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 1'

cuts['electron_PromptFinal_flagged_m10to500_PID2'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 2'
cuts['muon_PromptFinal_flagged_m10to500_PID2'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 2'

cuts['electron_PromptFinal_flagged_m10to500_PID3'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 3'
cuts['muon_PromptFinal_flagged_m10to500_PID3'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 3'

cuts['electron_PromptFinal_flagged_m10to500_PID4'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 4'
cuts['muon_PromptFinal_flagged_m10to500_PID4'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 4'

cuts['electron_PromptFinal_flagged_m10to500_PID5'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 5'
cuts['muon_PromptFinal_flagged_m10to500_PID5'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 5'

cuts['electron_PromptFinal_flagged_m10to500_PID21'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 21'
cuts['muon_PromptFinal_flagged_m10to500_PID21'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 21'

cuts['electron_PromptFinal_flagged_m10to500_PID23'] = 'evt_tag_dielectron_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 23'
cuts['muon_PromptFinal_flagged_m10to500_PID23'] = 'evt_tag_dimuon_promptfinal && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500 && abs(dilep_motherID_myalgorithm) == 23'

cuts['electron_PromptFinal_flagged_m10to500_LessdRp1'] = 'evt_tag_dielectron_promptfinal && (photon_dRtoParticle_isPromptFinalState_selected < 0.1 || photon_dRtoAntiParticle_isPromptFinalState_selected < 0.1) && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500'
cuts['electron_PromptFinal_flagged_m10to500_LargerdRp1'] = 'evt_tag_dielectron_promptfinal && !(photon_dRtoParticle_isPromptFinalState_selected < 0.1 || photon_dRtoAntiParticle_isPromptFinalState_selected < 0.1) && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500'

cuts['muon_PromptFinal_flagged_m10to500_LessdRp1'] = 'evt_tag_dimuon_promptfinal && (photon_dRtoParticle_isPromptFinalState_selected < 0.1 || photon_dRtoAntiParticle_isPromptFinalState_selected < 0.1) && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500'
cuts['muon_PromptFinal_flagged_m10to500_LargerdRp1'] = 'evt_tag_dimuon_promptfinal && !(photon_dRtoParticle_isPromptFinalState_selected < 0.1 || photon_dRtoAntiParticle_isPromptFinalState_selected < 0.1) && dilep_mass_FSRgamma_gen_ispromptfinal > 10 && dilep_mass_FSRgamma_gen_ispromptfinal < 500'

