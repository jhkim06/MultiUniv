from CommonPyTools.python.CommonTools import *
from ROOT import kMagenta, kBlue, kCyan, kOrange, kYellow, kBlack, kRed, kViolet

# Signal only has the style, the other background has style 3001
# lineWidth 2, this is another option
# style 0 : noFillColor
# no nameHR --> using sample keyname intead

groupPlot['TT'] = {
    'nameHR' : "TT",
    'isSignal' : 0,
    'color':  kRed,
    'samples' : ['TTLL_powheg','TTLJ_powheg','TTJJ_powheg']
    }

groupPlot['ttbb'] = {
    'nameHR' : "ttbb",
    'isSignal' : 0,
    'color':  kRed+2,
    'samples' : ['ttbb']
    }

groupPlot['ST'] = {
    'nameHR' : "ST",
    'isSignal' : 0,
    'color':  kMagenta,
    'samples' : ['SingleTop_sch_top','SingleTop_tch_top','SingleTop_tch_antitop','SingleTop_tW_top','SingleTop_tW_antitop']
    }

groupPlot['VJ'] = {
    'nameHR' : "VJ",
    'isSignal' : 0,
    'color':  kOrange,
    'samples' : ['WJets_MG','DYJets','DYJets10to50_MG']
    }

groupPlot['VV'] = {
    'nameHR' : "VV",
    'isSignal' : 0,
    'color':  kCyan,
    'samples' : ['WW_pythia','WZ_pythia','ZZ_pythia']
    }

groupPlot['TTX'] = {
    'nameHR' : "TTX",
    'isSignal' : 0,
    'color':  kYellow,
    'samples' : ['ttW','ttZ','ttH_bb']
    }

'''
groupPlot['QCD'] = {
    'nameHR' : "QCD",
    'isSignal' :0,
    'color': kYellow, #color is not defined yet
    'style': 4050,
    'lineColor':807,
    'lineWidth':1,
    'samples' : ['SingleMuon_QCD','SingleElectron_QCD','TTLL_powheg_QCD','WJets_MG_QCD','DYJets_QCD','WW_pythia_QCD','WZ_pythia_QCD','ZZ_pythia_QCD']
    }
'''

plot['DYJets'] = {
    'color': kYellow,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    }

plot['DYJets10to50_MG'] = {
    'color': 418,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    }

plot['WJets_MG'] = {
    'color': kYellow,
    'isSignal' :0,
    'isData': 0,
    'style': 4050,
    }

plot['TTLL_powheg'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['TTLJ_powheg'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['TTJJ_powheg'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['ttbb'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_sch_top'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tch_top'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tch_antitop'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tW_top'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tW_antitop'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
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
plot['ZZ_pythia'] = {
    'color': 550,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['ttW'] = {
    'color': kYellow,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['ttZ'] = {
    'color': kYellow,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['ttH_bb'] = {
    'color': kYellow,
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

plot['SingleElectron'] = {
    'nameHR' : "SingleElectron",
    'color':kBlack,
    'isSignal':0,
    'isData':1,
    'scale':1,
    }

legend['lumi'] = 'L = 41.5/fb'
legend['sqrt'] = '#sqrt{s} = 13 TeV'
# extraText default is Preliminary
legend['extraText'] = 'in progress'
# iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV)
# For instance: 
#               iPeriod = 3 means: 7 TeV + 8 TeV
#               iPeriod = 0 means: free form (uses lumi_sqrtS)
legend['iPeriod'] = 0
legend['iPos'] = 0
