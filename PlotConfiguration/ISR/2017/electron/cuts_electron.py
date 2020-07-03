from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['detector_level'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 50. && dilep_mass_rec_Nominal < 320.'
cuts['detector_level_m50to64'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 50. && dilep_mass_rec_Nominal < 64.'
cuts['detector_level_m64to81'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 64. && dilep_mass_rec_Nominal < 81.'
cuts['detector_level_m81to101'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 81. && dilep_mass_rec_Nominal < 101.'
cuts['detector_level_m101to200'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 101. && dilep_mass_rec_Nominal < 200.'
cuts['detector_level_m200to320'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 200. && dilep_mass_rec_Nominal < 320.'
cuts['detector_level_m101to320'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_pt_rec_Nominal < 100. && dilep_mass_rec_Nominal > 101. && dilep_mass_rec_Nominal < 320.'


