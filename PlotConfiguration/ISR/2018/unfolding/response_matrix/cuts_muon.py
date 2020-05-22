from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
#supercut = 'evt_tag_dimuon_promptfinal == 1 &&  evt_tag_dimuon_promptfinal == 1'
supercut = 'evt_tag_dimuon_promptfinal == 1'

# detector distribution
#cuts['detector_level'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '
cuts['detector_level_DY_Fake'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0 && dilep_mass_rec_Nominal > 10. '

## for closure test
#cuts['detector_level_unfold_split_p2'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && (Entry$%10 > 7) '
#cuts['detector_level_DY_Fake_unfold_split_p2'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0 && (Entry$%10 > 7)'
#cuts['detector_level_unfold_split_p5'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && (Entry$%2 == 0) '
#cuts['detector_level_DY_Fake_unfold_split_p5'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0 && (Entry$%2 == 0)'

#cuts['detector_level_lepMomUp'] = 'evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
#cuts['detector_level_DY_Fake_lepMomUp'] = 'evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 0'
#cuts['detector_level_lepMomDown'] = 'evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '
#cuts['detector_level_DY_Fake_lepMomDown'] = 'evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 0'

# Matrix
cuts['Detector_Dressed_DRp1_Fiducial'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '
cuts['Detector_Dressed_DRp1_FullPhase'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '
cuts['Detector_Dressed_DR4PI_FullPhase'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 ' 

#cuts['fiducial_phase_pre_FSR_dRp1_lepMomUp'] = 'evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
#cuts['fiducial_phase_pre_FSR_dRp1_lepMomDown'] = 'evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '

# for closure test
#cuts['fiducial_phase_pre_FSR_dRp1_unfold_split_p8'] = '(pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1)*(Entry$%10 < 8) && evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1'
#cuts['fiducial_phase_pre_FSR_dRp1_unfold_split_p5'] = '(pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1)*(Entry$%2 == 1) && evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1'
