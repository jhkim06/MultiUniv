from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['detector_level'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 50. && dilep_mass_rec_Nominal < 350.'
cuts['detector_level_m50to65'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 50. && dilep_mass_rec_Nominal < 65.'
cuts['detector_level_m65to80'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 65. && dilep_mass_rec_Nominal < 80.'
cuts['detector_level_m80to100'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 80. && dilep_mass_rec_Nominal < 100.'
cuts['detector_level_m100to200'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 100. && dilep_mass_rec_Nominal < 200.'
cuts['detector_level_m200to350'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 200. && dilep_mass_rec_Nominal < 350.'


