from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

McWeight = 'weightGen*weightRec'
#McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor'

#--------------------    
# MC
#--------------------    

samples['DYJets'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'weight' :McWeight,
    }

#samples['DYJets10to50_MG'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'weight' :McWeight,
#    }
#
samples['TT_powheg'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'weight' :McWeight,
    }

samples['WJets_MG'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['WW_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['WZ_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['ZZ_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['DoubleEG'] = {
    'skim'   :'',
    'weight' :'1',
    }

#samples['DoubleMuon'] = {
#    'skim'   :'',
#    'weight' :'1',
#    }
#--------------------    
# DATA driven QCD
#--------------------
'''
samples['DoubleEG_FakeElEl'] = {
    'skim'   :'MetFt_L_v0_LL_v0_MuMuOrElElFake_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }

samples['DobuleMuon_FakeMuMu'] = {
    'skim'   :'MetFt_L_v0_LL_v0_MuMuOrElElFake_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }
'''
