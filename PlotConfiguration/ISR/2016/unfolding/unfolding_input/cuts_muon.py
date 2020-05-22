from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['Detector'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 10.' # Need to study how to determine underflow/overflow size
#cuts['detector_level_lepMomUp'] = 'evt_tag_dimuon_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
#cuts['detector_level_lepMomDown'] = 'evt_tag_dimuon_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '

cuts['Detector_M_Total'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 15. && dilep_mass_rec_Nominal < 1000. && dilep_pt_rec_Nominal < 100.' 
cuts['Detector_M_1'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 15. && dilep_mass_rec_Nominal < 40. && dilep_pt_rec_Nominal < 100.' 
cuts['Detector_M_2'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 40. && dilep_mass_rec_Nominal < 60. && dilep_pt_rec_Nominal < 100.' 
cuts['Detector_M_3'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 60. && dilep_mass_rec_Nominal < 81. && dilep_pt_rec_Nominal < 100.' 
cuts['Detector_M_4'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 81. && dilep_mass_rec_Nominal < 101. && dilep_pt_rec_Nominal < 100.' 
cuts['Detector_M_5'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 101. && dilep_mass_rec_Nominal < 200. && dilep_pt_rec_Nominal < 100.' 
cuts['Detector_M_6'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 200. && dilep_mass_rec_Nominal < 320. && dilep_pt_rec_Nominal < 100.' 
cuts['Detector_M_7'] = 'evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 320. && dilep_mass_rec_Nominal < 1000. && dilep_pt_rec_Nominal < 100.' 

