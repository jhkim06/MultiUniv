from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && dilep_mass_rec > 40'

cuts['dipt_cut'] = 'dilep_pt_rec < 100'

cuts['dimu_photon_cut'] = 'photon_n_rec > 0 && dilep_photon_mass_rec > 85 && dilep_photon_mass_rec < 105 && dilep_mass_rec > 30 && dilep_mass_rec < 87'