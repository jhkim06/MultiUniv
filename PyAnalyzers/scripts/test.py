#!/usr/bin/env python

import ROOT
from ROOT import TFile, TTree
from PyAnalyzers.python.MLTools import MLTools
from PyAnalyzers.python.TMVATools import TMVATools

from KerasModel import KerasModel

file_names = [
  '/data8/DATA/SMP/Run2Legacy_v3/2018/MetFt_L_v2_TTSemiLep_v1_K2_v1_ABCD_v1_ML_Train_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190412_205511/0000/*.root',
  '/data8/DATA/SMP/Run2Legacy_v3/2018/MetFt_L_v2_TTSemiLep_v1_K2_v1_ABCD_v1_ML_Train_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190412_205511/0001/*.root'
]



variables = {
  'had_top_b_jet_pt' : {
    'name' : 'had_top_b_jet_pt',
    'type' :  'D'
  },
  'lep_top_b_jet_pt' : {
    'name' : 'lep_top_b_jet_pt',
    'type' : 'D'
  },
  'up_type_jet_pt' : {
    'name' : 'up_type_jet_pt',
    'type' : 'D'
  },
  'down_type_jet_pt' : {
    'name' : 'down_type_jet_pt',
    'type' : 'D'
  },
  'dijet_deltaR' : {
    'name' : 'dijet_deltaR',
    'type' : 'D'
  },
  'dijet_deltaEta' : {
    'name' : 'dijet_deltaEta',
    'type' : 'D'
  },
  'dijet_cosThetaTC' : {
    'name' : 'dijet_cosThetaTC',
    'type' : 'D'
  },
  'dijet_cosThetaTB' : {
    'name' : 'dijet_cosThetaTB',
    'type' : 'D'
  },
  'hadronic_top_mass' : {
    'name' : 'hadronic_top_mass',
    'type' : 'D'
  },
  'leptonic_top_mass' : {
    'name' : 'leptonic_top_mass',
    'type' : 'D'
  },
  'W_MT' : {
    'name' : 'W_MT',
    'type' : 'D'
  },
  'tt_MT' : {
    'name' : 'tt_MT',
    'type' : 'D'
  },
}

cuts = {
  'sig' : '',
  'bkg' : '',
}

options = {
  'factory' : {
    'name' : "TMVAClassification",
    'options' : ":".join(["!V",
	                  "!Silent",
			  "Color",
			  "DrawProgressBar",
			  "Transformations=I;D;P;G,D",
			  "AnalysisType=Classification"
		         ]),
    'weight' : "weight",
  },
  'prepareTrees' : ":".join(["SplitMode=Random",
			     "!V",
			     #"nTrain_Signal=50000",
			     #"nTrain_Background=50000",
             	            ]),
  'bookMethod' : [
    {
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
    {
      'type' : ROOT.TMVA.Types.kPyKeras,
      'name' : "PyKeras",
      'options' : ":".join(["H",
	                    "!V",
			    "VarTransform=D,G",
			    "FilenameModel=model.h5",
			    "NumEpochs=10",
			    "BatchSize=100"
		           ]),
    },
  ],
}
IsKeras = False
for option in options['bookMethod']:
  if option['name'] == "PyKeras":
    IsKeras = True
if IsKeras:
  m = KerasModel()
  m.defineModel_3layer(len(variables))
  m.compile()
  m.save("model.h5")
  m.summary()

ml_tools =MLTools()
ml_tools.SetMLTools(TMVATools)
ml_tools.SetTrees('TTLJ_powheg','sig_tree_2b',file_names)
ml_tools.SetTrees('TTLJ_powheg','bkg_tree_all_2b',file_names)
ml_tools.SetVariables(variables)
ml_tools.SetCuts(cuts)
ml_tools.SetOptions(options)
ml_tools.doTrain('TTLJ_powheg_sig_tree_2b','TTLJ_powheg_bkg_tree_all_2b','out_train_2b.root')
