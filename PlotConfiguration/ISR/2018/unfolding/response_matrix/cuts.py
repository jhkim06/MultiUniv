from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'evt_tag_dielectron_promptfinal == 1 &&  evt_tag_dielectron_promptfinal == 1'

# detector distribution
cuts['detector_level'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '
cuts['detector_level_DY_Fake'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 0'

# for closure test
#cuts['detector_level_unfold_split_p2'] = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && (Entry$%10 > 7) '
#cuts['detector_level_DY_Fake_unfold_split_p2'] = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 0 && (Entry$%10 > 7)'
#cuts['detector_level_unfold_split_p5'] = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && (Entry$%2 == 0) '
#cuts['detector_level_DY_Fake_unfold_split_p5'] = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 0 && (Entry$%2 == 0)'

## for lepton momentum systematic
#cuts['detector_level_lepMomUp'] = 'evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
#cuts['detector_level_DY_Fake_lepMomUp'] = 'evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 0'
#cuts['detector_level_lepMomDown'] = 'evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '
#cuts['detector_level_DY_Fake_lepMomDown'] = 'evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 0'

# matrix
cuts['Detector_Dressed_DRp1_Fiducial'] = 'pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '
cuts['Detector_Dressed_DRp1_FullPhase'] = 'evt_tag_dielectron_promptfinal == 1 && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '
cuts['Detector_Dressed_DR4PI_FullPhase'] = 'evt_tag_dielectron_promptfinal == 1 && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '

# for closure test
#cuts['fiducial_phase_pre_FSR_dRp1_unfold_split_p8'] = '(pass_kinematic_cut_el_FSRgammaDRp1_gen == 1)*(Entry$%10 < 8) && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1'
#cuts['fiducial_phase_pre_FSR_dRp1_unfold_split_p5'] = '(pass_kinematic_cut_el_FSRgammaDRp1_gen == 1)*(Entry$%2 == 1) && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1'

#cuts['fiducial_phase_pre_FSR_dRp1_lepMomUp'] = 'pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 && evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
#cuts['fiducial_phase_pre_FSR_dRp1_lepMomDown'] = 'pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 && evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '

