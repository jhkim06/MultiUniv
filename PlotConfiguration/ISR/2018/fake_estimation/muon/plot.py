from CommonPyTools.python.CommonTools import *
from ROOT import kMagenta, kBlue, kCyan, kOrange, kYellow, kBlack, kRed

# Signal only has the style, the other background has style 3001
# lineWidth 2, this is another option
# style 0 : noFillColor
# no nameHR --> using sample keyname intead

#groupPlot['QCD'] = {
#    'nameHR' : "QCD",
#    'isSignal' : 0,
#    'color':  kBlack,
#    'samples' : ['DoubleMuonQCDFakeRate']
#    }

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

groupPlot['DYtoTauTau'] = {
    'nameHR' : "DYtoTauTau",
    'isSignal' :0,
    'color': kRed,
    'style': 4050,
    'lineColor':807,
    'lineWidth':1,
    'samples' : ['DYJetsToTauTau','DYJets10to50ToTauTau']
    }

# kOrange 800

#groupPlot['DY'] = {
#    'nameHR' : "DY",
#    'isSignal' :0,
#    'color': kOrange-2,
#    'style': 4050,
#    'lineColor':807,
#    'lineWidth':1,
#    'samples' : ['DYJets','DYJets10to50']
#    }

groupPlot['DY'] = {
    'nameHR' : "DY",
    'isSignal' :0,
    'color': kOrange-2, 
    'style': 4050,
    'lineColor':807,
    'lineWidth':1,
    'samples' : ['DYJetsToMuMu','DYJets10to50ToMuMu']
    }

#plot['DYJets10to50'] = {
#    'color': 418,
#    'isSignal' :1,
#    'isData': 0,
#    'style': 4050,
#    'scale':1,
#    }
#
#plot['DYJets'] = {
#    'color': kYellow,
#    'isSignal' :0,
#    'isData': 0,
#    'style': 4050,
#    }


plot['DYJets10to50ToMuMu'] = {
    'color': 418,
    'isSignal' :1,
    'isData': 0,
    'style': 4050,
    'scale':1,
    }

plot['DYJetsToMuMu'] = {
    'color': kYellow,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    }

plot['DYJets10to50ToTauTau'] = {
    'color': 418,
    'isSignal' :1,
    'isData': 0,
    'style': 4050,
    'scale':1,
    }

plot['DYJetsToTauTau'] = {
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

plot['DoubleMuon'] = {
    'nameHR' : "DoubleMuon",
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

legend['lumi'] = '35.9 fb^{-1}'
# extraText default is Preliminary
#legend['extraText'] = 'Preliminary'
# iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV)
# For instance: 
#               iPeriod = 3 means: 7 TeV + 8 TeV
#               iPeriod = 0 means: free form (uses lumi_sqrtS)
legend['iPeriod'] = 4
legend['iPos'] = 0
