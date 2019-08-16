from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['eventSel'] = 'diLep_Ch =='+str(DiLepCh.MuMuOS) + ' && leading_pt > 20 && subleading_pt > 10 && abs(leading_eta) < 2.4 && abs(subleading_eta) < 2.4 && diLep_m > 60 && diLep_m < 120 '
#cuts['eeOS_Selective'] = 'diLep_Ch =='+str(DiLepCh.ElElOS) +' && diLep_passSelectiveQ'
#cuts['mmOS'] = 'diLep_Ch =='+str(DiLepCh.MuMuOS)
#cuts['all'] = '1==1'
