from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

# for fake estimation
# TL same sign
cuts['detector_level'] = 'is_dimu_tri_passed == 1 && evt_tag_dimuon_rec_Fake == 1 && evt_tag_dielectron_rec_Fake == 0 && evt_tag_analysisevnt_sel_rec_Fake == 1 && dilep_pt_rec_Fake < 100. && dilep_mass_rec_Fake > 40 && evt_tag_oppositecharge_sel_rec_Fake == 0 && evt_tag_TL_rec_Fake == 1 '

