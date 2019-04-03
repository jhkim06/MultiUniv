from CommonPyTools.python.CommonTools import *

# Signal only has the style, the other background has style 3001
# lineWidth 2, this is another option

groupPlot['VV'] = {
    'nameHR' : "VV",
    'isSignal' : 0,
    'color':  458,
    'samples' : ['WW','WZ']
    }


#plot['DYJets10to50_MG'] = {
#    'color': 418,
#    'isSignal' :1,
#    'isData': 0,
#    'style': 4050,
#    'scale':1,
#    'plotName':'DY10to50',
#    }
#
plot['DYJets'] = {
    'color': 400, # Yellow
    'isSignal' :1,
    'isData': 0,
    'style': 4050,
    'plotName':'DY',
    }

plot['WZ_pythia'] = {
    'color': 450,
    'isSignal' :0,
    'isData': 0,
    'plotName':'WZ',
    'scale':1,
    }
plot['WW_pythia'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'plotName':'WW',
    'scale':1,
    }

plot['DoubleEG'] = {
    'color':1,
    'isSignal':0,
    'isData':1,
    'plotName':'DoubleEG',
    'scale':1,
    }

legend['lumi'] = 'L = 41.5/fb'
legend['sqrt'] = '#sqrt{s} = 13 TeV'
