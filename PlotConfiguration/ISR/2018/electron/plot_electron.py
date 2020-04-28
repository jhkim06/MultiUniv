from CommonPyTools.python.CommonTools import *
from ROOT import kMagenta, kAzure, kTeal, kOrange, kPink, kBlack, kOrange

# Signal only has the style, the other background has style 3001
# lineWidth 2, this is another option
# style 0 : noFillColor
# no nameHR --> using sample keyname intead

#groupPlot['Fake'] = {
#    'nameHR': "Fake",
#    'isSignal' :0,
#    'color':  kBlack,
#    'samples' : ['Fake']
#    }

#groupPlot['WJet'] = {
#    'nameHR' : "WJet",
#    'isSignal' : 0,
#    'color':  kMagenta,
#    'style': 4050,
#    'samples' : ['WJets_MG']
#    }

groupPlot['TT'] = {
    'nameHR' : "t#bar{t}",
    'isSignal' : 0,
    'style': 4050,
    'color':  kAzure+1,
    'lineColor':kAzure-9,
    'samples' : ['TTLL_powheg']
    }

groupPlot['VV'] = {
    'nameHR' : "VV",
    'isSignal' : 0,
    'style': 4050,
    'color':  kTeal+1,
    'lineColor':kTeal-9,
    'samples' : ['WW_pythia','WZ_pythia','ZZ_pythia']
    }

groupPlot['DYtoTauTau'] = {
    'nameHR' : "DY\\rightarrow\\tau\\tau",
    'isSignal' :0,
    'color': kOrange+1,
    'lineColor':kOrange-9,
    'style': 4050,
    'lineWidth':1,
    'samples' : ['DYJetsToTauTau','DYJets10to50ToTauTau']
    }

# kOrange 800
groupPlot['DY'] = {
    'nameHR' : "DY\\rightarrow ee",
    'isSignal' :0,
    'color': kPink+1,
    'style': 4050,
    'lineColor':kPink-9,
    'lineWidth':1,
    'samples' : ['DYJetsToEE','DYJets10to50ToEE']
    }

plot['DYJets10to50ToEE'] = {
    'color': 418,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    'scale':1,
    }

plot['DYJetsToEE'] = {
    'color': kPink,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    }

plot['DYJets10to50ToTauTau'] = {
    'color': 418,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    'scale':1,
    }

plot['DYJetsToTauTau'] = {
    'color': kPink,
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

#plot['Fake'] = {
#    'color': kBlack,
#    'isSignal' :0,
#    'isData': 0,
#    'scale':1,
#    }

plot['EGamma'] = {
    'nameHR' : "Data",
    'color':kBlack,
    'isSignal':0,
    'isData':1,
    'scale':1,
    }

#plot['DoubleMuonQCDFakeRate'] = {
#    'nameHR' : "DoubleMuonQCDFakeRate",
#    'color':kRed,
#    'isSignal':0,
#    'isData':0,
#    'scale':1,
#    }

legend['lumi'] = '59.7 fb^{-1}'
# extraText default is Preliminary
#legend['extraText'] = 'Preliminary'
# iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV)
# For instance: 
#               iPeriod = 3 means: 7 TeV + 8 TeV
#               iPeriod = 0 means: free form (uses lumi_sqrtS)
legend['iPeriod'] = 4
legend['iPos'] = 0
