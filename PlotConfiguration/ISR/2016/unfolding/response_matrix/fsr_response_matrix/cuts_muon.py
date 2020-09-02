from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = 'evt_tag_dimuon_promptfinal == 1 '

# matrix
cuts['Dressed_DRp1_DY_Fake']                = 'pass_kinematic_cut_mu_FSRgamma_gen == 0 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 '
cuts['Dressed_DRp1_Dressed_DR4PI_Fiducial'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1'
cuts['Acceptance'] = '1'

#cuts['dressed_level_DY_fake_evenEvent']  = 'pass_kinematic_cut_mu_FSRgamma_gen == 0 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && (Entry$%2 == 0)'
#cuts['Dressed_DRp1_Dressed_DR4PI_Fiducial_oddEvent'] = 'pass_kinematic_cut_mu_FSRgamma_gen == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && (Entry$%2 == 1)'

#cuts['full_phase_dRp1_split_p8'] = '(is_dimuon_gen == 1)*(Entry$%10 < 8) && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1'
#cuts['full_phase_dRp1_split_p5'] = '(is_dimuon_gen == 1)*(Entry$%2 == 1) && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1'

#massCut_low  = ["40.", "60.", "80.", "100.", "200."]
#massCut_high = ["60.", "80.", "100.", "200.", "350."]

# full phase distribution
#for i in range(len(massCut_low)):
#    cuts['full_phase_m' + massCut_low[i] + 'to' + massCut_high[i]] = 'is_dimuon_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + massCut_low[i] + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + massCut_high[i] + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100.'
