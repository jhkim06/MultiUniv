from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = 'evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1'

cuts['dipt_cut'] = 'dilep_pt_rec < 100'

cuts['no_cut'] = '1'
