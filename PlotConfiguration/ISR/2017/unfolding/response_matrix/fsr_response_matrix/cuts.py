from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'evt_tag_dielectron_gen == 1'

cuts['full_phase'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_fiducial_post_fsr == 1 '

