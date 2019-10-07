#!/usr/bin/env python

import ROOT
from ROOT import TFile, TTree
from PyAnalyzers.python.MLTools import MLTools
from PyAnalyzers.python.TMVATools import TMVATools


file_names = [
  '/data8/DATA/SMP/Run2Legacy_v3/2018/MetFt_L_v2_TTSemiLep_v1_K2_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190412_205511/0000/*.root',
  '/data8/DATA/SMP/Run2Legacy_v3/2018/MetFt_L_v2_TTSemiLep_v1_K2_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190412_205511/0001/*.root'
]



variables = {
  'initial_dijet_m' : {
    'name' : 'initial_dijet_m',
    'type' :  'F'
  },
  'fitted_dijet_m' : {
    'name' : 'fitted_dijet_m',
    'type' : 'F'
  },
}

cuts = {
  'sig' : 'fitted_dijet_m>0 && IsMu==1',
  'bkg' : 'fitted_dijet_m>0 && IsEl==1',
}

options = {
  'factory' : {
    'name' : "TMVAClassification",
    'outfile' : 'out_test.root',
    'options' : ":".join(["!V",
	                  "!Silent",
			  "Color",
			  "DrawProgressBar",
			  "Transformations=I;D;P;G,D",
			  "AnalysisType=Classification"
		         ]),
  },
  'prepareTrees' : ":".join(["SplitMode=Random",
			     "!V",
			     "nTrain_Signal=50000",
			     "nTrain_Background=50000",
             	            ]),
  'bookMethod' : {
     'type' : ROOT.TMVA.Types.kBDT,
     'name' : "BDT",
     'options' : ":".join(["!H",
	                "!V",
			"NTrees=850",
			"nEventsMin=150",
			"MaxDepth=3",
			"BoostType=AdaBoost",
			"AdaBoostBeta=0.5",
			"SeparationType=GiniIndex",
			"nCuts=20",
			"PruneMethod=NoPruning",
		       ]),
   },
}

ml_tools =MLTools()
ml_tools.SetMLTools(TMVATools)
ml_tools.SetTrees('TTLJ_powheg','sig',file_names)
ml_tools.SetTrees('TTLJ_powheg','bkg',file_names)
ml_tools.SetVariables(variables)
ml_tools.SetCuts(cuts)
ml_tools.SetOptions(options)
ml_tools.doTrain('TTLJ_powheg_sig','TTLJ_powheg_bkg')
