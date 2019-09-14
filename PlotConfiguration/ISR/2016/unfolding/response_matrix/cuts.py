from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

#cuts['full_phase'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
cuts['full_phase'] = 'evt_tag_dimuon_gen == 1 && evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '

#cuts['fiducial_phase_pre_FSR'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
#cuts['fiducial_phase_post_FSR'] = 'evt_tag_dielectron_gen == 1 && evt_tag_dielectron_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 '
