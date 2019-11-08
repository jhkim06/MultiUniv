from CommonPyTools.python.CommonTools import *

# keys here must match keys in plot.py  
# a key is one component of final distribution, no overlap between sample in groupPlot and plot list

structure['tt'] = {
    'isSignal'   : 0,
    'isData'     : 0,
    }

structure['nontt'] = {
    'isSignal'   : 0,
    'isData'     : 0,
    }



#--------------------    
# DATA driven QCD
#--------------------
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
structure['ttCH'] = {
    'isSignal'   : 1,
    'isData'     : 0,
    }
