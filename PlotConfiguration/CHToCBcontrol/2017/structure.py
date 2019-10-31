from CommonPyTools.python.CommonTools import *

# keys here must match keys in plot.py  
# a key is one component of final distribution, no overlap between sample in groupPlot and plot list

structure['TT'] = {
    'isSignal'   : 0,
    'isData'     : 0,
    }

structure['WJets_MG'] = {
    'isSignal'   : 0,
    'isData'     : 0,
    }


#--------------------    
# DATA driven QCD
#--------------------
'''
structure['SingleElectron_FakeEl'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    }

structure['SingleMuon_FakeMu'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    }
'''
#--------------------    
# DATA
#--------------------    
structure['SingleElectron'] = {
    'isSignal'   : 0,
    'isData'     : 1,
    }

structure['SingleMuon'] = {
    'isSignal'   : 0,
    'isData'     : 1,
    }
#--------------------    
# Signal
#--------------------  
# isSignal: all signals not grid(1), alternative(2), signal grids(3)
structure['CHToCB_M090'] = {
    'isSignal'   : 1,
    'isData'     : 0,
    }
structure['CHToCB_M120'] = {
    'isSignal'   : 1,
    'isData'     : 0,
    }
structure['CHToCB_M140'] = {
    'isSignal'   : 1,
    'isData'     : 0,
    }
