from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

McWeight = 'evt_weight_total_gen'

#--------------------
# MC
#--------------------

samples['DYFSR_PYTHIA'] = {
    'skim'   :'ISR_generator_only_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :McWeight,
    }

#samples['DYJets'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['DYJets10to50'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['DYJets_MG'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['DYJets10to50_MG'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }

#samples['ZToEE_M_50_120_powheg'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['ZToEE_M_120_200_powheg'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['ZToEE_M_200_400_powheg'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }
