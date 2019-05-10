from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['2b'] = 'nbtags==2' #TODO: define variables in CommonTools
cuts['3b'] = 'nbtags>=3'
#cuts['eeOS'] = 'diLep_Ch =='+str(DiLepCh.ElElOS)
#cuts['eeOS_Selective'] = 'diLep_Ch =='+str(DiLepCh.ElElOS) +' && diLep_passSelectiveQ'
#cuts['mmOS'] = 'diLep_Ch =='+str(DiLepCh.MuMuOS)
#cuts['all'] = '1==1'
