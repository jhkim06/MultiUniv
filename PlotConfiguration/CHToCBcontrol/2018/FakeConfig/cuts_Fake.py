from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

#supercut = 'passIso==1 && passTightID==1 && MET>20'
supercut = 'passTightID==1'

cuts['Mu2b_A'] = 'nbtags==2 && IsMu==1 && passIso==1 && MET<20'
cuts['Mu2b_B'] = 'nbtags==2 && IsMu==1 && passAntiIso==1 && MET<20'
#cuts['Mu2b_B_Up'] = 'nbtags==2 && IsMu==1 && passAntiIso_Up==1 && MET<20'
#cuts['Mu2b_C_Up'] = 'nbtags==2 && IsMu==1 && passAntiIso_Up==1 && MET>20'
#cuts['Mu2b_B_Do'] = 'nbtags==2 && IsMu==1 && passAntiIso_Do==1 && MET<20'
#cuts['Mu2b_C_Do'] = 'nbtags==2 && IsMu==1 && passAntiIso_Do==1 && MET>20'

cuts['Mu3b_A'] = 'nbtags>=3 && IsMu==1 && passIso==1 && MET<20'
cuts['Mu3b_B'] = 'nbtags>=3 && IsMu==1 && passAntiIso==1 && MET<20'
#cuts['Mu3b_B_Up'] = 'nbtags>=3 && IsMu==1 && passAntiIso_Up==1 && MET<20'
#cuts['Mu3b_C_Up'] = 'nbtags>=3 && IsMu==1 && passAntiIso_Up==1 && MET>20'
#cuts['Mu3b_B_Do'] = 'nbtags>=3 && IsMu==1 && passAntiIso_Do==1 && MET<20'
#cuts['Mu3b_C_Do'] = 'nbtags>=3 && IsMu==1 && passAntiIso_Do==1 && MET>20'

cuts['El2b_A'] = 'nbtags==2 && IsEl==1 && passIso==1 && MET<20'
cuts['El2b_B'] = 'nbtags==2 && IsEl==1 && passAntiIso_Up==1 && MET<20'
#cuts['El2b_B_Up'] = 'nbtags==2 && IsEl==1 && passAntiIso_Up==1 && MET<20'
#cuts['El2b_C_Up'] = 'nbtags==2 && IsEl==1 && passAntiIso_Up==1 && MET>20'
#cuts['El2b_B_Do'] = 'nbtags==2 && IsEl==1 && passAntiIso_Do==1 && MET<20'
#cuts['El2b_C_Do'] = 'nbtags==2 && IsEl==1 && passAntiIso_Do==1 && MET>20'

cuts['El3b_A'] = 'nbtags>=3 && IsEl==1 && passIso==1 && MET<20'
cuts['El3b_B'] = 'nbtags>=3 && IsEl==1 && passAntiIso==1 && MET<20'
#cuts['El3b_B_Up'] = 'nbtags>=3 && IsEl==1 && passAntiIso_Up==1 && MET<20'
#cuts['El3b_C_Up'] = 'nbtags>=3 && IsEl==1 && passAntiIso_Up==1 && MET>20'
#cuts['El3b_B_Do'] = 'nbtags>=3 && IsEl==1 && passAntiIso_Do==1 && MET<20'
#cuts['El3b_C_Do'] = 'nbtags>=3 && IsEl==1 && passAntiIso_Do==1 && MET>20'

