from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['2b'] = 'nbtags==2' #TODO: define variables in CommonTools
cuts['3b'] = 'nbtags>=3'
cuts['passTightISO'] = 'passTightISO==1' # non QCD
#cuts['passAntiISO'] = 'passAntiISO==1' # ABCD estimation for QCD
#cuts['passAntiISO_Up'] = 'passAntiISO_Up==1'
#cuts['passAntiISO_Do'] = 'passAntiISO_Do==1'
#cuts['eeOS'] = 'diLep_Ch =='+str(DiLepCh.ElElOS)
#cuts['eeOS_Selective'] = 'diLep_Ch =='+str(DiLepCh.ElElOS) +' && diLep_passSelectiveQ'
#cuts['mmOS'] = 'diLep_Ch =='+str(DiLepCh.MuMuOS)
#cuts['all'] = '1==1'
