from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

#GenMcWeight = 'evt_weight_total_gen * zptweight_electron'
GenMcWeight = 'evt_weight_total_gen'
#McWeight = 'evt_weight_total_gen'

#--------------------
# MC
#--------------------

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

#samples['ZToEE_M_50_120_powheg'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['ZToEE_M_120_200_powheg'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['ZToEE_M_200_400_powheg'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }
