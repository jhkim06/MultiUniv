from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'evt_tag_dielectron_gen == 1'

# detector distribution
cuts['detector_level'] = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['detector_level_DY_Fake'] = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 0'
cuts['detector_level_lepMomUp'] = 'evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
cuts['detector_level_DY_Fake_lepMomUp'] = 'evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 0'
cuts['detector_level_lepMomDown'] = 'evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '
cuts['detector_level_DY_Fake_lepMomDown'] = 'evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 0'

# matrix
cuts['fiducial_phase_pre_FSR_dRp1'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['fiducial_phase_pre_FSR_dRp1_lepMomUp'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
cuts['fiducial_phase_pre_FSR_dRp1_lepMomDown'] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '

