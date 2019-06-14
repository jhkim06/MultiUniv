from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['eventSel'] = 'ispassRec == 1 && IsElEl == 1'
#cuts['eeOS_Selective'] = 'diLep_Ch =='+str(DiLepCh.ElElOS) +' && diLep_passSelectiveQ'
#cuts['mmOS'] = 'diLep_Ch =='+str(DiLepCh.MuMuOS)
#cuts['all'] = '1==1'
