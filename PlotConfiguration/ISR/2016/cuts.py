from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['detector_level'] = 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && dilep_pt_rec < 100. && dilep_mass_rec > 40'
cuts['detector_level_noBveto'] = 'evt_tag_dimuon_rec == 1 && evt_tag_leptonpt_sel_rec == 1&& evt_tag_leptoneta_sel_rec == 1 && evt_tag_oppositecharge_sel_rec == 1  && dilep_pt_rec < 100. && dilep_mass_rec > 40'

#cuts['dimu_photon_cut'] = 'photon_n_rec > 0 && dilep_photon_mass_rec > 85 && dilep_photon_mass_rec < 105 && dilep_mass_rec > 30 && dilep_mass_rec < 87'
