from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = '1 == 1'

#
cuts['Detector_DY_Fake'] = 'evt_tag_dimuon_hardprocess == 1 && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 0 && dilep_mass_rec_Nominal > 35. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.'
#
# Matrix
cuts['Detector_Dressed_DRp1_Fiducial'] = 'evt_tag_dimuon_promptfinal == 1 && pass_kinematic_cut_mu_FSRgammaDRp1_gen == 1 && evt_tag_dimuon_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 35. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.'

