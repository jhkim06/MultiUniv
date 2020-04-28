from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['Detector'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_analysisevnt_sel_rec_Nominal == 1 '
#cuts['detector_level'] = 'evt_tag_dielectron_rec_Nominal == 1 && evt_tag_leptonpt_sel_rec_Nominal == 1 && evt_tag_leptoneta_sel_rec_Nominal == 1 && additional_veto_el_size_Nominal == 0 && additional_veto_mu_size_Nominal == 0 && leadinglep_pt_rec_Nominal > 28. && subleadinglep_pt_rec_Nominal > 17.'

#cuts['detector_level_lepMomUp'] = 'evt_tag_dielectron_rec_LepMomScaleUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleUp == 1 '
#cuts['detector_level_lepMomDown'] = 'evt_tag_dielectron_rec_LepMomScaleDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomScaleDown == 1 '
#cuts['detector_level_lepMomResUp'] = 'evt_tag_dielectron_rec_LepMomResUp == 1 && evt_tag_analysisevnt_sel_rec_LepMomResUp == 1 '
#cuts['detector_level_lepMomResDown'] = 'evt_tag_dielectron_rec_LepMomResDown == 1 && evt_tag_analysisevnt_sel_rec_LepMomResDown == 1 '
