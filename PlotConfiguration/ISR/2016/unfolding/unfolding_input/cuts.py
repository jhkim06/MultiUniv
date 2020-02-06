from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['detector_level'] = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['detector_level_lepMomUp'] = 'evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
cuts['detector_level_lepMomDown'] = 'evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '
cuts['detector_level_lepMomResUp'] = 'evt_tag_dielectron_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 '
cuts['detector_level_lepMomResDown'] = 'evt_tag_dielectron_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUpDown == 1 '
