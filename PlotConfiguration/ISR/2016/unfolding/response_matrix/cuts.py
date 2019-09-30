from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'evt_tag_dielectron_gen == 1'

#cuts['full_phase'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['full_phase'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '

#cuts['fiducial_phase_pre_FSR'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['fiducial_phase_pre_FSR_dRp1'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '

#cuts['fiducial_phase_pre_FSR'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['fiducial_phase_pre_FSR_dRp7'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[4] == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '

#cuts['fiducial_phase_pre_FSR'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['fiducial_phase_pre_FSR_dR10'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[9] == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '

#cuts['fiducial_phase_post_FSR'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['fiducial_phase_post_FSR'] = 'evt_tag_dielectron_fiducial_post_fsr == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
