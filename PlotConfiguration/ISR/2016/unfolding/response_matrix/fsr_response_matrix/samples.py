from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

McWeight = 'evt_weight_total_gen'
McWeight_forDY10to50 = 'evt_weight_total_gen * 1.0687524'

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

samples['DYJets10to50'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'1',
    'weight' :McWeight,
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

#--------------------
# DATA driven QCD
#--------------------

'''
samples['DoubleEG_FakeElEl'] = {
    'skim'   :'MetFt_L_v0_LL_v0_MuMuOrElElFake_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }

samples['DobuleElectron_FakeMuMu'] = {
    'skim'   :'MetFt_L_v0_LL_v0_MuMuOrElElFake_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }
'''
