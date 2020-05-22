from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

McWeight = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal'

#--------------------
# MC
#--------------------

samples['DYJets200to400'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'dilep_mass_FSRgamma_gen_ispromptfinal > 200',
    'weight' :McWeight,
    }

samples['DYJets'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'dilep_mass_FSRgamma_gen_ispromptfinal < 200',
    'weight' :McWeight,
    }

samples['DYJets10to50_MG'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :' 1 ',
    'weight' :McWeight,
    }

