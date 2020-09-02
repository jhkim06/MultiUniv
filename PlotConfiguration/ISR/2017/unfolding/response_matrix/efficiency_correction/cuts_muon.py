from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = '1 == 1'

# For acceptance correction
cuts['Acceptance'] = ' evt_tag_dimuon_promptfinal == 1 '

