from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['Mu2b'] = 'nbtags==2 && singleLep_Ch =='+str(SingleLepCh.Mu)
cuts['Mu3b'] = 'nbtags>=3 && singleLep_Ch =='+str(SingleLepCh.Mu)
cuts['El2b'] = 'nbtags==2 && singleLep_Ch =='+str(SingleLepCh.El)
cuts['El3b'] = 'nbtags>=3 && singleLep_Ch =='+str(SingleLepCh.El)
