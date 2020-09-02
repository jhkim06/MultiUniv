from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

McWeight        = 'evt_weight_total_gen * 1. * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal'
McWeightZptCorr = 'evt_weight_total_gen * zptweight_electron * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal'
GenMcWeight     = 'evt_weight_total_gen * 1.'

#--------------------
# MC
#--------------------

samples['DYJets'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :McWeight,
    }

samples['DYJets10to50_MG'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :McWeight,
    }

