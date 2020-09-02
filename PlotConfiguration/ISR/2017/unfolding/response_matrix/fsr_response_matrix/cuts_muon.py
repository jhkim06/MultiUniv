from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'evt_tag_dimuon_promptfinal == 1'

# matrix
cuts['dressed_level_DY_fake']  = 'pass_kinematic_cut_mu_FSRgamma_gen == 0 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 '
cuts['Dressed_DRp1_Dressed_DR4PI_Fiducial'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1'
cuts['Acceptance'] = '1'

