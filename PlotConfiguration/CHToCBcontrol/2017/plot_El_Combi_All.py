from CommonPyTools.python.CommonTools import *
from ROOT import kMagenta, kBlue, kCyan, kOrange, kYellow, kBlack, kRed, kViolet

# Signal only has the style, the other background has style 3001
# lineWidth 2, this is another option
# style 0 : noFillColor
# no nameHR --> using sample keyname intead

groupPlot['tt'] = {
    'nameHR' : "tt",
    'isSignal' : 0,
    'color':  kRed,
    'samples' : ['TTLL_powheg','TTLJ_powheg']
    #'samples' : ['TTLL_powheg','TTLJ_powheg','ttbb']
    #'samples' : ['TTLL_powheg','TTLJ_powheg','TTJJ_powheg']
    }

groupPlot['nontt'] = {
    'nameHR' : "nontt",
    'isSignal' : 0,
    'color':  kMagenta,
    #'samples' : ['SingleTop_sch_Lep','SingleTop_tch_top_Incl','SingleTop_tch_antitop_Incl','SingleTop_tW_top_NoFullyHad','SingleTop_tW_antitop_NoFullyHad','WJets_MG','DYJets', 'DYJets10to50_MG','WW_pythia','WZ_pythia','ZZ_pythia','ttW','ttZ','ttHTobb']
    'samples' : ['SingleTop_sch_Lep','SingleTop_tch_top_Incl','SingleTop_tch_antitop_Incl','SingleTop_tW_top_NoFullyHad','SingleTop_tW_antitop_NoFullyHad','WJets_MG','DYJets', 'DYJets10to50_MG','WW_pythia','WZ_pythia','ZZ_pythia','ttW','ttZ']
    }

#groupPlot['QCD'] = {
#    'nameHR' : "QCD",
#    'isSignal' :0,
#    'color': kCyan, #color is not defined yet
#    'samples' : [ "%s_QCD"%(ele) for ele in groupPlot['tt']['samples'] + groupPlot['nontt']['samples']+["SingleElectron"] ],
#    'suppressNegative' : True,
#    }

#
#groupPlot['ttbb'] = {
#    'nameHR' : "ttbb",
#    'isSignal' : 0,
#    'color':  kRed+2,
#    'samples' : ['ttbb']
#    }
#

#groupPlot['VJ'] = {
#    'nameHR' : "VJ",
#    'isSignal' : 0,
#    'color':  kOrange,
#    'samples' : ['WJets_MG']
#    #'samples' : ['WJets_MG','DYJets','DYJets10to50_MG']
#    }
#
#groupPlot['VV'] = {
#    'nameHR' : "VV",
#    'isSignal' : 0,
#    'color':  kCyan,
#    'samples' : ['WW_pythia','WZ_pythia','ZZ_pythia']
#    }
#
#groupPlot['TTX'] = {
#    'nameHR' : "TTX",
#    'isSignal' : 0,
#    'color':  kYellow,
#    'samples' : ['ttW','ttZ','ttH_bb']
#    }
#
#
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

#plot['TTJJ_powheg'] = {
#    'color': 550,
#    'isSignal' :0,
#    'isData': 0,
#    'scale':1,
#    }
#
#plot['ttbb'] = {
#    'color': 550,
#    'isSignal' :0,
#    'isData': 0,
#    'scale':1,
#    }

plot['SingleTop_sch_Lep'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tch_top_Incl'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tch_antitop_Incl'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tW_top_NoFullyHad'] = {
    'color': kMagenta,
    'isSignal' :0,
    'isData': 0,
    'scale':1,
    }

plot['SingleTop_tW_antitop_NoFullyHad'] = {
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

#plot['ttHTobb'] = {
#    'color': kYellow,
#    'isSignal' :0,
#    'isData': 0,
#    'scale':1,
#    }

#plot['SingleMuon'] = {
#    'nameHR' : "SingleMuon",
#    'color':kBlack,
#    'isSignal':0,
#    'isData':1,
#    'scale':1,
#    }
#
plot['SingleElectron'] = {
    'nameHR' : "SingleElectron",
    'color':kBlack,
    'isSignal':0,
    'isData':1,
    'scale':1,
    }
#
##plot_QCD = {}
##for key, val in plot.iteritems():
##  key_QCD = "%s_QCD"%(key)
##  plot_QCD[key_QCD] = val.copy()
##  plot_QCD[key_QCD]['isData'] = 0
##plot.update(plot_QCD)



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
