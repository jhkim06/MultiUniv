#!/usr/bin/env python

import os

import ROOT
from ROOT import TFile, TTree
from PyAnalyzers.python.MLTools import MLTools
from PyAnalyzers.python.TMVATools import TMVATools

from KerasModel import KerasModel

file_names = {
  ('2016','TTLJ_powheg') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2016/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/190423_001758/0000/*.root',
    '/data8/DATA/SMP/Run2Legacy_v3/2016/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/190423_001758/0001/*.root',
  ],
  ('2018','TTLJ_powheg') :
  [ 
    '/data8/DATA/SMP/Run2Legacy_v3/2018/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190412_205511/0000/*.root',
    '/data8/DATA/SMP/Run2Legacy_v3/2018/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190412_205511/0001/*.root',
  ],
  ('2017','TTLJ_powheg') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190417_161108/0000/*.root'
  ],
  ('2017','CHToCB_M090') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/ChargedHiggsToCB_M090_TuneCP5_PSweights_13TeV-madgraph-pythia8/190812_092207/0000/*.root'
  ],
  ('2017','CHToCB_M100') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/ChargedHiggsToCB_M100_TuneCP5_PSweights_13TeV-madgraph-pythia8/190812_092431/0000/*.root'
  ],
  ('2017','CHToCB_M110') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/ChargedHiggsToCB_M110_TuneCP5_PSweights_13TeV-madgraph-pythia8/190812_092541/0000/*.root'
  ],
  ('2017','CHToCB_M120') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/ChargedHiggsToCB_M120_TuneCP5_PSweights_13TeV-madgraph-pythia8/190812_092653/0000/*.root'
  ],
  ('2017','CHToCB_M130') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/ChargedHiggsToCB_M130_TuneCP5_PSweights_13TeV-madgraph-pythia8/190812_092800/0000/*.root'
  ],
  ('2017','CHToCB_M140') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/ChargedHiggsToCB_M140_TuneCP5_PSweights_13TeV-madgraph-pythia8/190812_092909/0000/*.root'
  ],
  ('2017','CHToCB_M150') :
  [
    '/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1_ML_Train_v1/ChargedHiggsToCB_M150_TuneCP5_PSweights_13TeV-madgraph-pythia8/190812_093018/0000/*.root'
  ],
}


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
  'tt_deltaR' : {
    'name' : 'tt_deltaR',
    'type' : 'D'
  },
  'had_top_pt' : {
    'name' : 'had_top_pt',
    'type' : 'D'
  },
  'lep_top_pt' : {
    'name' : 'lep_top_pt',
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
  'prepareTrees' : ":".join(["SplitMode=Block",
			     "!V",
			     #"nTrain_Signal=55000",
			     #"nTrain_Background=1400000",
			     #"nTest_Signal=55000",
			     #"nTest_Background=1400000",
             	            ]),
  'bookMethod' : [
     {
      'type' : ROOT.TMVA.Types.kPyKeras,
      'name' : "NN",
      'options' : ":".join(["H",
	                    "!V",
			    "VarTransform=D,G",
			    "FilenameModel=model.h5",
			    "NumEpochs=10",
			    "BatchSize=100",
		           ]),
    },

    {
      'type' : ROOT.TMVA.Types.kBDT,
      'name' : "BDT",
      'options' : ":".join(["!H",
	                    "!V",
	           	    "NTrees=850",
			    #"nEventsMin=150",
			    "MaxDepth=2",
			    "BoostType=AdaBoost",
			    "AdaBoostBeta=0.5",
			    "SeparationType=GiniIndex",
			    "nCuts=20",
			    "PruneMethod=NoPruning",
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

train_years = [
  #'2016',
  '2017',
  #'2018'
]
train_samples = [
	#'TTLJ_powheg',
        #'CHToCB_M090',
        #'CHToCB_M100',
	#'CHToCB_M110',
	'CHToCB_M120',
	#'CHToCB_M130',
	#'CHToCB_M140',
	#'CHToCB_M150'
]

for train_year in train_years:
  for train_sample in train_samples:

    ml_tools.SetTrees(train_sample,'sig_tree_4j_2b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'sig_tree_5j_2b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'sig_tree_6j_2b',file_names[train_year, train_sample])

    ml_tools.SetTrees(train_sample,'sig_tree_4j_3b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'sig_tree_5j_3b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'sig_tree_6j_3b',file_names[train_year, train_sample])

    ml_tools.SetTrees(train_sample,'bkg_tree_all_4j_2b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'bkg_tree_all_5j_2b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'bkg_tree_all_6j_2b',file_names[train_year, train_sample])

    ml_tools.SetTrees(train_sample,'bkg_tree_all_4j_3b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'bkg_tree_all_5j_3b',file_names[train_year, train_sample])
    ml_tools.SetTrees(train_sample,'bkg_tree_all_6j_3b',file_names[train_year, train_sample])

    #ml_tools.SetTrees('TTLJ_powheg','bkg_tree_flipped_3b',file_names)
    ml_tools.SetVariables(variables)
    ml_tools.SetCuts(cuts)
    ml_tools.SetOptions(options)

    ml_tools.doTrain(['%s_sig_tree_4j_2b'%train_sample],['%s_bkg_tree_all_4j_2b'%train_sample],'%s_4j_2b'%train_sample,'out_train_%s_4j_2b.root'%train_sample)
    ml_tools.doTrain(['%s_sig_tree_5j_2b'%train_sample],['%s_bkg_tree_all_5j_2b'%train_sample],'%s_5j_2b'%train_sample,'out_train_%s_5j_2b.root'%train_sample)
    ml_tools.doTrain(['%s_sig_tree_6j_2b'%train_sample],['%s_bkg_tree_all_6j_2b'%train_sample],'%s_6j_2b'%train_sample,'out_train_%s_6j_2b.root'%train_sample)
    #
    #---------------------------------------------------
    #
    ml_tools.doTrain(['%s_sig_tree_4j_3b'%train_sample],['%s_bkg_tree_all_4j_3b'%train_sample],'%s_4j_3b'%train_sample,'out_train_%s_4j_3b.root'%train_sample)
    ml_tools.doTrain(['%s_sig_tree_5j_3b'%train_sample],['%s_bkg_tree_all_5j_3b'%train_sample],'%s_5j_3b'%train_sample,'out_train_%s_5j_3b.root'%train_sample)
    ml_tools.doTrain(['%s_sig_tree_6j_3b'%train_sample],['%s_bkg_tree_all_6j_3b'%train_sample],'%s_6j_3b'%train_sample,'out_train_%s_6j_3b.root'%train_sample)
    #
    #---------------------------------------------------
    #
    #ml_tools.doTrain(['%s_sig_tree_4j_2b'%train_sample,'%s_sig_tree_5j_2b'%train_sample,'%s_sig_tree_6j_2b'%train_sample],['%s_bkg_tree_all_4j_2b'%train_sample,'%s_bkg_tree_all_5j_2b'%train_sample,'%s_bkg_tree_all_6j_2b'%train_sample],'%s_2b'%train_sample,'out_train_%s_2b.root'%train_sample)
    #ml_tools.doTrain(['%s_sig_tree_4j_3b'%train_sample,'%s_sig_tree_5j_3b'%train_sample,'%s_sig_tree_6j_3b'%train_sample],['%s_bkg_tree_all_4j_3b'%train_sample,'%s_bkg_tree_all_5j_3b'%train_sample,'%s_bkg_tree_all_6j_3b'%train_sample],'%s_3b'%train_sample,'out_train_%s_3b.root'%train_sample)
  os.system('mv TMVAClassification TMVAClassification_%s'%(train_year))
  os.system('mkdir out_root_%s'%(train_year))
  os.system('mv out_*.root out_root_%s'%(train_year))
