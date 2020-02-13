from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = 'passTightID==1 && njets>=4 && MET>20'

cuts['Mu2b'] = 'nbtags==2 && IsMu==1'
cuts['Mu3b'] = 'nbtags>=3 && IsMu==1'

