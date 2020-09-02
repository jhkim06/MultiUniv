from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

# supercut will be applied last in the cuts
supercut = '1 == 1'

# Nominal
cuts['Detector_DY_Fake'] = 'evt_tag_dielectron_hardprocess == 1 && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 0 && dilep_mass_rec_Nominal > 45. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.'

# Matrix
cuts['Detector_Dressed_DRp1_Fiducial'] = 'evt_tag_dielectron_promptfinal == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 45. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110.'

# Closure test
#cuts['detector_level_DY_Fake_evenEvent'] = 'evt_tag_dielectron_hardprocess == 1 && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 0 && dilep_mass_rec_Nominal > 45. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110. && (Entry$%2 == 0)'

# Matrix
#cuts['Detector_Dressed_DRp1_Fiducial_oddEvent'] = 'evt_tag_dielectron_promptfinal == 1 && pass_kinematic_cut_el_FSRgammaDRp1_gen == 1 && evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 && dilep_mass_rec_Nominal > 45. && dilep_mass_rec_Nominal < 380. && dilep_pt_rec_Nominal < 110. && (Entry$%2 == 1)'

