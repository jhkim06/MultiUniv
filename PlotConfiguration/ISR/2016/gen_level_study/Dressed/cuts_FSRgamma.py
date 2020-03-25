from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['FSRgamma_EE_m40to350'] = 'pass_kinematic_cut_el_FSRgamma_gen && evt_tag_dielectron_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 50 && dilep_mass_FSRgamma_gen_ispromptfinal < 350 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'

cuts['FSRgamma_EE_m40to60'] = 'pass_kinematic_cut_el_FSRgamma_gen && evt_tag_dielectron_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 50 && dilep_mass_FSRgamma_gen_ispromptfinal < 65 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_EE_m60to80'] = 'pass_kinematic_cut_el_FSRgamma_gen && evt_tag_dielectron_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 65 && dilep_mass_FSRgamma_gen_ispromptfinal < 80 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_EE_m80to100'] = 'pass_kinematic_cut_el_FSRgamma_gen && evt_tag_dielectron_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 80 && dilep_mass_FSRgamma_gen_ispromptfinal < 100 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_EE_m100to200'] = 'pass_kinematic_cut_el_FSRgamma_gen && evt_tag_dielectron_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 100 && dilep_mass_FSRgamma_gen_ispromptfinal < 200 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_EE_m200to350'] = 'pass_kinematic_cut_el_FSRgamma_gen && evt_tag_dielectron_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 200 && dilep_mass_FSRgamma_gen_ispromptfinal < 350 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'

cuts['FSRgamma_MM_m40to350'] = 'pass_kinematic_cut_mu_FSRgamma_gen && evt_tag_dimuon_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 40 && dilep_mass_FSRgamma_gen_ispromptfinal < 350 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_MM_m40to60'] = 'pass_kinematic_cut_mu_FSRgamma_gen && evt_tag_dimuon_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 40 && dilep_mass_FSRgamma_gen_ispromptfinal < 60 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_MM_m60to80'] = 'pass_kinematic_cut_mu_FSRgamma_gen && evt_tag_dimuon_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 60 && dilep_mass_FSRgamma_gen_ispromptfinal < 80 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_MM_m80to100'] = 'pass_kinematic_cut_mu_FSRgamma_gen && evt_tag_dimuon_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 80 && dilep_mass_FSRgamma_gen_ispromptfinal < 100 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_MM_m100to200'] = 'pass_kinematic_cut_mu_FSRgamma_gen && evt_tag_dimuon_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 100 && dilep_mass_FSRgamma_gen_ispromptfinal < 200 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'
cuts['FSRgamma_MM_m200to350'] = 'pass_kinematic_cut_mu_FSRgamma_gen && evt_tag_dimuon_gen && dilep_mass_FSRgamma_gen_ispromptfinal > 200 && dilep_mass_FSRgamma_gen_ispromptfinal < 350 && dilep_pt_FSRgamma_gen_ispromptfinal < 100'

