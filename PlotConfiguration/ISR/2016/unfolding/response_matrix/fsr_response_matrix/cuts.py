from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
#supercut = 'evt_tag_dielectron_lhe == 1 &&  evt_tag_dielectron_promptfinal == 1'
supercut = 'evt_tag_dielectron_promptfinal == 1'

cuts['Dressed_DRp1_DY_Fake']                 = 'pass_kinematic_cut_el_FSRgamma_gen == 0 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 '
cuts['Dressed_DRp1_Dressed_DR4PI_Fiducial']  = 'pass_kinematic_cut_el_FSRgamma_gen == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 '
cuts['Acceptance'] = '1'

#cuts['dressed_level_DY_fake_evenEvent']  = 'pass_kinematic_cut_el_FSRgamma_gen == 0 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 && (Entry$%2 == 0)'
#cuts['Dressed_DRp1_Dressed_DR4PI_Fiducial_oddEvent']  = 'pass_kinematic_cut_el_FSRgamma_gen == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 && (Entry$%2 == 1)'
