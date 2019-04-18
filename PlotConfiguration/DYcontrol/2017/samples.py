from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

Nlep='2'
eleWP='mediumSelectiveQ'

McWeight = 'baseW*PUweight*trgSF_Q*recoSF*IdSF_Q*IsoSF*ZPtCor'
#McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor'

samples['DYJets'] = {
    'weight' :McWeight,
    }

samples['DYJets10to50_MG'] = {
    'weight' :McWeight,
    }


samples['TTLL_powheg'] = {
    'weight' :McWeight,
    }


samples['WJets_MG'] = {
    'weight' :McWeight,
    }

samples['WW_pythia'] = {
    'weight' :McWeight,
    }

samples['WZ_pythia'] = {
    'weight' :McWeight,
    }

samples['ZZ_pythia'] = {
    'weight' :McWeight,
    }

samples['DoubleEG'] = {
    'weight' :'1',
    }

#samples['DoubleMuon'] = {
#    'weight' :'1',
#    }
#
