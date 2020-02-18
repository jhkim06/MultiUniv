from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'is_dimuon_gen == 1'

# detector distribution
cuts['detector_level'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['detector_level_DY_Fake'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0'

cuts['detector_level_lepMomUp'] = 'evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
cuts['detector_level_DY_Fake_lepMomUp'] = 'evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0'
cuts['detector_level_lepMomDown'] = 'evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '
cuts['detector_level_DY_Fake_lepMomDown'] = 'evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0'

# matrix
cuts['fiducial_phase_pre_FSR_dRp1'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '

cuts['fiducial_phase_pre_FSR_dRp1_lepMomUp'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
cuts['fiducial_phase_pre_FSR_dRp1_lepMomDown'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '
