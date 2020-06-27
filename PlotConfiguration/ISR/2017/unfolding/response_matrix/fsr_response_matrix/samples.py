from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

McWeight = 'evt_weight_total_gen * 1.'

#--------------------
# MC
#--------------------
#samples['DY_MuMu_FSR_PYTHIA'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'combine_cuts' : True,
#    'weight' :McWeight,
#    }

#samples['DY_MuMu_FSR_PHOTOS'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'combine_cuts' : True,
#    'weight' :McWeight,
#    }

#samples['DYFSR_PYTHIA'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }

#samples['DYFSR_PHOTOS'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }

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
