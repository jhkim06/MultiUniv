from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['detector_level'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
