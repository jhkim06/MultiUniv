from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

Nlep='1'
eleWP='mediumSelectiveQ'

McWeight = 'baseW*PUweight*trgSF_Q*recoSF*IdSF_Q*IsoSF*ZPtCor'
#McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor'

#--------------------    
# MC
#--------------------    

samples['DYJets'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'weight' :McWeight,
    }

samples['DYJets10to50_MG'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg'] = {
    'skim'   :'',
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
#--------------------    
# DATA driven QCD
#--------------------    
samples['SingleElectron_FakeEl'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    }

samples['SingleMuon_FakeMu'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    }
#--------------------    
# DATA
#--------------------    
samples['SingleElectron'] = {
    'skim'   :'',
    'weight' :'1',
    }

samples['SingleMuon'] = {
    'skim'   :'',
    'weight' :'1',
    }
