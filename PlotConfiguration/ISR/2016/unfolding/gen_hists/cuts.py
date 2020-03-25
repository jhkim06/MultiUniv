from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

# supercut will be applied last in the cuts
supercut = '1'

# dressed level distribution
massCut_low  = ["50.", "65.", "80.", "100.", "200."]
massCut_high = ["65.", "80.", "100.", "200.", "350."]

muon_massCut_low  = ["40.", "60.", "80.", "100.", "200."]
muon_massCut_high = ["60.", "80.", "100.", "200.", "350."]

for i in range(len(massCut_low)):
    cuts['electron_full_phase_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'is_dielectron_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + massCut_low[i] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + massCut_high[i] + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100.'
    cuts['electron_fiducial_phase_post_FSR_dRp1_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + massCut_low[i] + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + massCut_high[i] + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100.'

    cuts['electron_full_phase_split_p2_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'is_dielectron_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + massCut_low[i] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + massCut_high[i] + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100. && (Entry$%10 > 7)'
    cuts['electron_fiducial_phase_post_FSR_dRp1_split_p2_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + massCut_low[i] + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + massCut_high[i] + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100. && (Entry$%10 > 7)'

    cuts['electron_full_phase_split_p5_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'is_dielectron_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + massCut_low[i] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + massCut_high[i] + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100. && (Entry$%2 == 0)'
    cuts['electron_fiducial_phase_post_FSR_dRp1_split_p5_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + massCut_low[i] + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + massCut_high[i] + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100. && (Entry$%2 == 0)'

    # muon
    cuts['muon_full_phase_m' + muon_massCut_low[i] + 'to' + muon_massCut_high[i]] = 'is_dimuon_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + muon_massCut_low[i] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + muon_massCut_high[i] + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100.'
    cuts['muon_fiducial_phase_post_FSR_dRp1_m' + muon_massCut_low[i] + 'to' + muon_massCut_high[i]] = 'evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dimuon_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + muon_massCut_low[i] + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + muon_massCut_high[i] + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100.'

    cuts['muon_full_phase_split_p2_m' + muon_massCut_low[i] + 'to' + muon_massCut_high[i]] = 'is_dimuon_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + muon_massCut_low[i] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + muon_massCut_high[i] + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100. && (Entry$%10 > 7)'
    cuts['muon_fiducial_phase_post_FSR_dRp1_split_p2_m' + muon_massCut_low[i] + 'to' + muon_massCut_high[i]] = 'evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dimuon_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + muon_massCut_low[i] + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + muon_massCut_high[i] + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100. && (Entry$%10 > 7)'

    cuts['muon_full_phase_split_p5_m' + muon_massCut_low[i] + 'to' + muon_massCut_high[i]] = 'is_dimuon_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + muon_massCut_low[i] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + muon_massCut_high[i] + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100. &&  (Entry$%2 == 0)'
    cuts['muon_fiducial_phase_post_FSR_dRp1_split_p5_m' + muon_massCut_low[i] + 'to' + muon_massCut_high[i]] = 'evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dimuon_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + muon_massCut_low[i] + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + muon_massCut_high[i] + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100. && (Entry$%2 == 0)'

