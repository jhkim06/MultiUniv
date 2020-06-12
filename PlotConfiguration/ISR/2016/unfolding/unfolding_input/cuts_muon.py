from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

supercut = '1==1'

cuts['Detector'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 10. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.' # Need to study how to determine underflow/overflow size

#cuts['Detector_NoLepMomCorr'] = 'evt_tag_dimuon_rec_NoLepMomCorr == 1 && evt_tag_analysisevnt_sel_rec_NoLepMomCorr == 1 && dilep_mass_rec_NoLepMomCorr > 10. && dilep_mass_rec_NoLepMomCorr < 380. && dilep_pt_rec_NoLepMomCorr < 110.' # Need to study how to determine underflow/overflow size

#cuts['Detector_LepMomScaleUp'] = 'evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 && dilep_mass_rec_LepMomScaleUp > 10. && dilep_mass_rec_LepMomScaleUp < 380. && dilep_pt_rec_LepMomScaleUp < 110.'
#cuts['Detector_LepMomScaleDown'] = 'evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 && dilep_mass_rec_LepMomScaleDown > 10. && dilep_mass_rec_LepMomScaleDown < 380. && dilep_pt_rec_LepMomScaleDown < 110.'
#cuts['Detector_LepMomResUp'] = 'evt_tag_dimuon_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 && dilep_mass_rec_LepMomResUp > 10. && dilep_mass_rec_LepMomResUp < 380. && dilep_pt_rec_LepMomResUp < 110.'
#cuts['Detector_LepMomResDown'] = 'evt_tag_dimuon_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResDown == 1 && dilep_mass_rec_LepMomResDown > 10. && dilep_mass_rec_LepMomResDown < 380. && dilep_pt_rec_LepMomResDown < 110.'
#
#cuts['Detector_M_Total'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 40. && dilep_mass_rec_Nominal < 330. && dilep_pt_rec_Nominal < 100.'
#cuts['Detector_M_0'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 40. && dilep_mass_rec_Nominal < 64. && dilep_pt_rec_Nominal < 100.'
#cuts['Detector_M_1'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 64. && dilep_mass_rec_Nominal < 81. && dilep_pt_rec_Nominal < 100.'
#cuts['Detector_M_2'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 81. && dilep_mass_rec_Nominal < 101. && dilep_pt_rec_Nominal < 100.'
#cuts['Detector_M_3'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 101. && dilep_mass_rec_Nominal < 200. && dilep_pt_rec_Nominal < 100.'
#cuts['Detector_M_4'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 200. && dilep_mass_rec_Nominal < 320. && dilep_pt_rec_Nominal < 100.'

