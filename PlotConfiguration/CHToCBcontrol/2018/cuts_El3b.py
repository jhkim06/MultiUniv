from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = 'passTightID==1'
supercut += ' && selected_lepton_pt>0'
supercut += ' && njets>0'

cuts['El3b'] = 'nbtags>=2 && IsEl==1 && MET>20'
cuts['El3bnoMETcut'] = 'nbtags>=2 && IsEl==1'

#cuts['El3b_KF'] = 'nbtags>=2 && IsEl==1 && fitter_status==0'
