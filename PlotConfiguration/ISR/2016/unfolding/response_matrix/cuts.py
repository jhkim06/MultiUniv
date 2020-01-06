from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'evt_tag_dielectron_gen == 1'

#cuts['full_phase'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
#
#cuts['fiducial_phase_pre_FSR_dRp1'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
#cuts['fiducial_phase_pre_FSR_dR10'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[9] == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
#cuts['fiducial_phase_post_FSR'] = 'evt_tag_dielectron_fiducial_post_fsr == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '

# to check sumw2 after unfolding

massCut_low  = ["50.", "65.", "80.", "100.", "200."]
massCut_high = ["65.", "80.", "100.", "200.", "350."]

for i in range(len(massCut_low)):
    cuts['fiducial_phase_pre_FSR_dRp1_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + massCut_low[i] + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + massCut_high[i] + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100.'

