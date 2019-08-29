from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = '1==1'

cuts['eventSel'] = 'isdielectron == 1 && IsElEl == 1 && ispassRec == 1 && isBveto == 1 && ptRec[0] > 25. && ptRec[1] > 15. && ptRec[2] < 100. '
