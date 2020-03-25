from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['LHE_EE_m40to350'] = 'evt_tag_dielectron_gen && dilep_mass_gen_prefsr > 40 && dilep_mass_gen_prefsr < 350 && dilep_pt_gen_prefsr < 100'

cuts['LHE_EE_m40to60'] = 'evt_tag_dielectron_gen && dilep_mass_gen_prefsr > 40 && dilep_mass_gen_prefsr < 60 && dilep_pt_gen_prefsr < 100'
cuts['LHE_EE_m60to80'] = 'evt_tag_dielectron_gen && dilep_mass_gen_prefsr > 60 && dilep_mass_gen_prefsr < 80 && dilep_pt_gen_prefsr < 100'
cuts['LHE_EE_m80to100'] = 'evt_tag_dielectron_gen && dilep_mass_gen_prefsr > 80 && dilep_mass_gen_prefsr < 100 && dilep_pt_gen_prefsr < 100'
cuts['LHE_EE_m100to200'] = 'evt_tag_dielectron_gen && dilep_mass_gen_prefsr > 100 && dilep_mass_gen_prefsr < 200 && dilep_pt_gen_prefsr < 100'
cuts['LHE_EE_m200to350'] = 'evt_tag_dielectron_gen && dilep_mass_gen_prefsr > 200 && dilep_mass_gen_prefsr < 350 && dilep_pt_gen_prefsr < 100'

cuts['LHE_MM_m40to350'] = 'evt_tag_dimuon_gen && dilep_mass_gen_prefsr > 40 && dilep_mass_gen_prefsr < 350 && dilep_pt_gen_prefsr < 100'

cuts['LHE_MM_m40to60'] = 'evt_tag_dimuon_gen && dilep_mass_gen_prefsr > 40 && dilep_mass_gen_prefsr < 60 && dilep_pt_gen_prefsr < 100'
cuts['LHE_MM_m60to80'] = 'evt_tag_dimuon_gen && dilep_mass_gen_prefsr > 60 && dilep_mass_gen_prefsr < 80 && dilep_pt_gen_prefsr < 100'
cuts['LHE_MM_m80to100'] = 'evt_tag_dimuon_gen && dilep_mass_gen_prefsr > 80 && dilep_mass_gen_prefsr < 100 && dilep_pt_gen_prefsr < 100'
cuts['LHE_MM_m100to200'] = 'evt_tag_dimuon_gen && dilep_mass_gen_prefsr > 100 && dilep_mass_gen_prefsr < 200 && dilep_pt_gen_prefsr < 100'
cuts['LHE_MM_m200to350'] = 'evt_tag_dimuon_gen && dilep_mass_gen_prefsr > 200 && dilep_mass_gen_prefsr < 350 && dilep_pt_gen_prefsr < 100'

