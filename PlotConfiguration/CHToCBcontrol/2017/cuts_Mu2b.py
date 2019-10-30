from CommonPyTools.python.CommonTools import *
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include') 
from Definitions import *

supercut = 'passIso==1 && passTightID==1 && pfMET_Type1_pt>20 && selected_lepton_pt>0'

cuts['Mu2b'] = 'n_bjet_deepcsv_m_noSF==2 && IsMu==1'
