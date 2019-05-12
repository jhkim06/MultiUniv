from CommonPyTools.python.CommonTools import *
from ROOT import kMagenta, kBlue, kCyan, kOrange, kYellow, kBlack, kRed

# Signal only has the style, the other background has style 3001
# lineWidth 2, this is another option
# style 0 : noFillColor
# no nameHR --> using sample keyname intead

groupPlot['WJet'] = {
    'nameHR' : "WJet",
    'isSignal' : 0,
    'color':  kMagenta,
    'samples' : ['WJets_MG']
    }

groupPlot['TT'] = {
    'nameHR' : "TT",
    'isSignal' : 0,
    'color':  kBlue,
    'samples' : ['TTLL_powheg']
    }

groupPlot['VV'] = {
    'nameHR' : "VV",
    'isSignal' : 0,
    'color':  kCyan,
    'samples' : ['WW_pythia','WZ_pythia','ZZ_pythia']
    }

# kOrange 800
groupPlot['DY'] = {
    'nameHR' : "DY",
    'isSignal' :0,
    'color': kOrange-2, 
    'style': 4050,
    'lineColor':807,
    'lineWidth':1,
    'samples' : ['DYJets']
    }

groupPlot['QCD'] = {
    'nameHR' : "QCD",
    'isSignal' :0,
    'color': kYellow, #color is not defined yet
    'style': 4050,
    'lineColor':807,
    'lineWidth':1,
    'samples' : ['SingleMuon_QCD','TTLL_powheg_QCD','WJets_MG_QCD','DYJets_QCD','WW_pythia_QCD','WZ_pythia_QCD','ZZ_pythia_QCD']
    }



#plot['DYJets10to50_MG'] = {
#    'color': 418,
#    'isSignal' :1,
#    'isData': 0,
#    'style': 4050,
#    'scale':1,
#    }
#
plot['DYJets'] = {
    'color': kYellow,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    }

plot['WZ_pythia'] = {
    'color': 450,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }
plot['WW_pythia'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }
plot['TTLL_powheg'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }
plot['WJets_MG'] = {
    'color': 550, #FIXME: same color with TTLL_powheg
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleMuon'] = {
    'nameHR' : "SingleMuon",
    'color':kBlack,
    'isSignal':0,
    'isData':1,
    'scale':1,
    }
"""
plot['SingleElectron'] = {
    'nameHR' : "SingleElectron",
    'color':kBlack,
    'isSignal':0,
    'isData':1,
    'scale':1,
    }
"""
legend['lumi'] = 'L = 41.5/fb'
legend['sqrt'] = '#sqrt{s} = 13 TeV'
# extraText default is Preliminary
#legend['extraText'] = 'Preliminary'
# iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV)
# For instance: 
#               iPeriod = 3 means: 7 TeV + 8 TeV
#               iPeriod = 0 means: free form (uses lumi_sqrtS)
legend['iPeriod'] = 0
legend['iPos'] = 0
