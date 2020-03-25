from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

# supercut will be applied last in the cuts
supercut = '1'

#cuts['electron_full_phase_mass_HardProcess'] = 'evt_tag_dielectron_gen == 1'
#cuts['muon_full_phase_mass_HardProcess']     = 'evt_tag_dimuon_gen == 1'
#cuts['electron_full_phase_mass_mySelection'] = 'is_dielectron_gen == 1'
#cuts['muon_full_phase_mass_mySelection']     = 'is_dimuon_gen == 1'

for i in range(20, 320, 20):
    #cuts['electron_full_phase_m' + str(i) + 'to' + str(i+10)] = 'is_dielectron_gen == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > ' + str(i) + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + str(i+10) + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100.'
    cuts['muon_full_phase_m' + str(i) + 'to' + str(i+20)] = '(is_dimuon_gen == 1 || is_dielectron_gen == 1) && dilep_mass_FSRgamma_gen_ispromptfinal > ' + str(i) + ' && dilep_mass_FSRgamma_gen_ispromptfinal < ' + str(i+20) + ' && dilep_pt_FSRgamma_gen_ispromptfinal < 100.'

   #cuts['electron_fiducial_phase_post_FSR_dRp1_m' + str(i) + 'to' + str(i+10)] = 'evt_tag_dielectron_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dielectron_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + str(i) + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + str(i+10) + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100.'
   #cuts['muon_fiducial_phase_post_FSR_dRp1_m' + str(i) + 'to' + str(i+10)] = 'evt_tag_dimuon_fiducial_lepton_matched_dressed_drX[0] == 1 && evt_tag_dimuon_gen == 1 && dilep_mass_gen_lepton_matched_dressed_drX[0] > ' + str(i) + ' && dilep_mass_gen_lepton_matched_dressed_drX[0] < ' + str(i+10) + ' && dilep_pt_gen_lepton_matched_dressed_drX[0] < 100.'

