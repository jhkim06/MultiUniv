from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = '1 == 1'

# For acceptance correction
cuts['Acceptance'] = 'evt_tag_dielectron_promptfinal == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 1'
#cuts['Acceptance_evenEvent'] = 'pass_kinematic_cut_el_FSRgamma_gen == 1 && evt_tag_dielectron_promptfinal == 1 && (Entry$%2 == 0)'

