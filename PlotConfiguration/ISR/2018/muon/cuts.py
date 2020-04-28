from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

# make seperate directory for each cut key
# want to check before/after correction
#       case 1: apply different weight but using the same cut
#       case 2: apply different weight using diffeent cut

# for fake estimation
#cuts['detector_level'] = 'evt_tag_dimuon_rec_Fake == 1 && evt_tag_analysisevnt_sel_rec_Fake == 1 && dilep_pt_rec_Fake < 100. && dilep_mass_rec_Fake > 40 && evt_tag_oppositecharge_sel_rec_Fake == 1 && evt_tag_LL_rec_Fake == 1 '

cuts['detector_level'] = 'is_dimu_tri_passed && evt_tag_dimuon_rec && evt_tag_bvetoed_rec && additional_veto_el_size == 0 && additional_veto_mu_size == 0 && evt_tag_leptoneta_sel_rec && evt_tag_leptonpt_sel_rec && evt_tag_oppositecharge_sel_rec && dilep_pt_rec < 100. && dilep_mass_rec > 40 && dilep_mass_rec < 350'

cuts['detector_level_m80to100'] = 'is_dimu_tri_passed && evt_tag_dimuon_rec && evt_tag_bvetoed_rec && additional_veto_el_size == 0 && additional_veto_mu_size == 0 && evt_tag_leptoneta_sel_rec && evt_tag_leptonpt_sel_rec && evt_tag_oppositecharge_sel_rec && dilep_pt_rec < 100. && dilep_mass_rec > 80 && dilep_mass_rec < 100'

cuts['detector_level_m80to100_pt25cut'] = 'is_dimu_tri_passed && evt_tag_dimuon_rec && evt_tag_bvetoed_rec && additional_veto_el_size == 0 && additional_veto_mu_size == 0 && evt_tag_leptoneta_sel_rec && evt_tag_leptonpt_sel_rec && evt_tag_oppositecharge_sel_rec && dilep_pt_rec < 100. && dilep_mass_rec > 80 && dilep_mass_rec < 100 && leadinglep_pt_rec > 25 && subleadinglep_pt_rec > 25'
