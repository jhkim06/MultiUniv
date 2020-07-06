from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

McWeight             = 'evt_weight_total_gen * 1. *             evt_weight_total_rec * evt_weight_isoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal'
McWeightZptCorr      = 'evt_weight_total_gen * zptweight_muon * evt_weight_total_rec * evt_weight_isoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal'
GenMcWeight          = 'evt_weight_total_gen'
McWeight_forDY10to50 = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_isoSF_rec * evt_weight_idSF_rec * evt_weight_trigSF_rec * 1.0687524'

#--------------------
# MC
#--------------------

#samples['DYJets200to400'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'dilep_mass_lhe > 200',
#    'weight' :McWeight,
#    }
#
samples['DYJets'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :GenMcWeight,
    }

samples['DYJets10to50'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :GenMcWeight,
    }

#samples['ZToMuMu_M_50_120_powheg'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['ZToMuMu_M_120_200_powheg'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['ZToMuMu_M_200_400_powheg'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }

