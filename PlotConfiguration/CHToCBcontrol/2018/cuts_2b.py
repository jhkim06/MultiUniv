from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = 'passTightID==1'
supercut += ' && selected_lepton_pt>0'
supercut += ' && njets>0'

cuts['Mu'] = 'IsMu==1 && MET>20'
cuts['El'] = 'IsEl==1 && MET>20'

cuts['Mu2b'] = 'nbtags==2 && IsMu==1 && MET>20'
cuts['El2b'] = 'nbtags==2 && IsEl==1 && MET>20'

cuts['Mu2bnoMETcut'] = 'nbtags==2 && IsMu==1'
cuts['El2bnoMETcut'] = 'nbtags==2 && IsEl==1'

#cuts['Mu2b_KF'] = 'nbtags==2 && IsMu==1 && fitter_status==0'
#cuts['El2b_KF'] = 'nbtags==2 && IsEl==1 && fitter_status==0'
