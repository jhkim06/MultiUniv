from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['Detector'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 45. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.'
