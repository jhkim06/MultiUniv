from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = '1 == 1'

#
cuts['detector_level_DY_Fake'] = 'evt_tag_dimuon_hardprocess == 1 && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0 && dilep_mass_rec_Nominal > 35. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.'
#
# Matrix
cuts['Detector_Dressed_DRp1_Fiducial'] = 'evt_tag_dimuon_promptfinal == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 35. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.'

#
#cuts['detector_level_DY_Fake_NoLepMomCorr'] = 'evt_tag_dimuon_rec_NoLepMomCorr == 1 && evt_tag_analysisevnt_sel_rec_NoLepMomCorr == 1 && pass_kinematic_cut_mu_FSRgamma_gen == 0 && dilep_mass_rec_NoLepMomCorr > 35. && dilep_mass_rec_NoLepMomCorr < 380. && dilep_pt_rec_NoLepMomCorr < 110.'
#
## Matrix
#cuts['Detector_Dressed_DRp1_Fiducial_NoLepMomCorr'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_NoLepMomCorr == 1 && evt_tag_analysisevnt_sel_rec_NoLepMomCorr == 1 && dilep_mass_rec_NoLepMomCorr < 380. && dilep_pt_rec_NoLepMomCorr < 110.'
#cuts['Detector_Dressed_DRp1_FullPhase_NoLepMomCorr'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_NoLepMomCorr == 1 && evt_tag_analysisevnt_sel_rec_NoLepMomCorr == 1 && dilep_mass_rec_NoLepMomCorr < 380. && dilep_pt_rec_NoLepMomCorr < 110.'
#cuts['Detector_Dressed_DR4PI_FullPhase_NoLepMomCorr'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_NoLepMomCorr == 1 && evt_tag_analysisevnt_sel_rec_NoLepMomCorr == 1 && dilep_mass_rec_NoLepMomCorr < 380. && dilep_pt_rec_NoLepMomCorr < 110.'
#cuts['Detector_Dressed_DR4PI_Fiducial_NoLepMomCorr'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && evt_tag_dimuon_rec_NoLepMomCorr == 1 && evt_tag_analysisevnt_sel_rec_NoLepMomCorr == 1 && dilep_mass_rec_NoLepMomCorr > 35. && dilep_mass_rec_NoLepMomCorr < 380. && dilep_pt_rec_NoLepMomCorr < 110.'

# For lepton momentum systematic
#cuts['detector_level_DY_Fake_LepMomScaleUp'] = 'evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && pass_kinematic_cut_mu_FSRgamma_gen == 0 && dilep_mass_rec_LepMomScaleUp > 35. && dilep_mass_rec_LepMomScaleUp < 380. && dilep_pt_rec_LepMomScaleUp < 110.'
#cuts['detector_level_DY_Fake_LepMomScaleDown'] = 'evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && pass_kinematic_cut_mu_FSRgamma_gen == 0 && dilep_mass_rec_LepMomScaleDown > 35. && dilep_mass_rec_LepMomScaleDown < 380. && dilep_pt_rec_LepMomScaleDown < 110.'
#cuts['detector_level_DY_Fake_LepMomResUp'] = 'evt_tag_dimuon_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 && pass_kinematic_cut_mu_FSRgamma_gen == 0 && dilep_mass_rec_LepMomResUp > 35. && dilep_mass_rec_LepMomResUp < 380. && dilep_pt_rec_LepMomResUp < 110.'
#cuts['detector_level_DY_Fake_LepMomResDown'] = 'evt_tag_dimuon_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResDown == 1 && pass_kinematic_cut_mu_FSRgamma_gen == 0 && dilep_mass_rec_LepMomResDown > 35. && dilep_mass_rec_LepMomResDown < 380. && dilep_pt_rec_LepMomResDown < 110.'
#
#cuts['Detector_Dressed_DRp1_Fiducial_LepMomScaleUp'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && dilep_mass_rec_LepMomScaleUp < 380. && dilep_pt_rec_LepMomScaleUp < 110.'
#cuts['Detector_Dressed_DRp1_FullPhase_LepMomScaleUp'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && dilep_mass_rec_LepMomScaleUp < 380. && dilep_pt_rec_LepMomScaleUp < 110.'
#cuts['Detector_Dressed_DR4PI_FullPhase_LepMomScaleUp'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && dilep_mass_rec_LepMomScaleUp < 380. && dilep_pt_rec_LepMomScaleUp < 110.'
#cuts['Detector_Dressed_DR4PI_Fiducial_LepMomScaleUp'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && dilep_mass_rec_LepMomScaleUp > 35. && dilep_mass_rec_LepMomScaleUp < 380. && dilep_pt_rec_LepMomScaleUp < 110.'
#
#cuts['Detector_Dressed_DRp1_Fiducial_LepMomScaleDown'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && dilep_mass_rec_LepMomScaleDown < 380. && dilep_pt_rec_LepMomScaleDown < 110.'
#cuts['Detector_Dressed_DRp1_FullPhase_LepMomScaleDown'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && dilep_mass_rec_LepMomScaleDown < 380. && dilep_pt_rec_LepMomScaleDown < 110.'
#cuts['Detector_Dressed_DR4PI_FullPhase_LepMomScaleDown'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && dilep_mass_rec_LepMomScaleDown < 380. && dilep_pt_rec_LepMomScaleDown < 110.'
#cuts['Detector_Dressed_DR4PI_Fiducial_LepMomScaleDown'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && dilep_mass_rec_LepMomScaleDown > 35. && dilep_mass_rec_LepMomScaleDown < 380. && dilep_pt_rec_LepMomScaleDown < 110.'
#
#cuts['Detector_Dressed_DRp1_Fiducial_LepMomResUp'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 && dilep_mass_rec_LepMomResUp < 380. && dilep_pt_rec_LepMomResUp < 110.'
#cuts['Detector_Dressed_DRp1_FullPhase_LepMomResUp'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 && dilep_mass_rec_LepMomResUp < 380. && dilep_pt_rec_LepMomResUp < 110.'
#cuts['Detector_Dressed_DR4PI_FullPhase_LepMomResUp'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 && dilep_mass_rec_LepMomResUp < 380. && dilep_pt_rec_LepMomResUp < 110.'
#cuts['Detector_Dressed_DR4PI_Fiducial_LepMomResUp'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && evt_tag_dimuon_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 && dilep_mass_rec_LepMomResUp > 35. && dilep_mass_rec_LepMomResUp < 380. && dilep_pt_rec_LepMomResUp < 110.'
#
#cuts['Detector_Dressed_DRp1_Fiducial_LepMomResDown'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResDown == 1 && dilep_mass_rec_LepMomResDown < 380. && dilep_pt_rec_LepMomResDown < 110.'
#cuts['Detector_Dressed_DRp1_FullPhase_LepMomResDown'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResDown == 1 && dilep_mass_rec_LepMomResDown < 380. && dilep_pt_rec_LepMomResDown < 110.'
#cuts['Detector_Dressed_DR4PI_FullPhase_LepMomResDown'] = 'evt_tag_dimuon_promptfinal == 1 && evt_tag_dimuon_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResDown == 1 && dilep_mass_rec_LepMomResDown < 380. && dilep_pt_rec_LepMomResDown < 110.'
#cuts['Detector_Dressed_DR4PI_Fiducial_LepMomResDown'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && evt_tag_dimuon_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResDown == 1 && dilep_mass_rec_LepMomResDown > 35. && dilep_mass_rec_LepMomResDown < 380. && dilep_pt_rec_LepMomResDown < 110.'

# for closure test
#cuts['detector_level_unfold_split_p2'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && (Entry$%10 > 7) '
#cuts['detector_level_DY_Fake_unfold_split_p2'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0 && (Entry$%10 > 7)'
#cuts['detector_level_unfold_split_p5'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && (Entry$%2 == 0) '
#cuts['detector_level_DY_Fake_unfold_split_p5'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0 && (Entry$%2 == 0)'

# for closure test
#cuts['fiducial_phase_pre_FSR_dRp1_unfold_split_p8'] = '(pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1)*(Entry$%10 < 8) && evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1'
#cuts['fiducial_phase_pre_FSR_dRp1_unfold_split_p5'] = '(pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1)*(Entry$%2 == 1) && evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1'

#cuts['fiducial_phase_pre_FSR_dRp1_LepMomScaleUp'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
#cuts['fiducial_phase_pre_FSR_dRp1_LepMomScaleDown'] = 'pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '

