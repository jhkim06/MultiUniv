from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

#McWeight = 'evt_weight_total_gen * evt_weight_total_rec '
McWeight = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_trigSF_rec * evt_weight_idSF_rec * evt_weight_recoSF_rec'
#McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor'

#--------------------    
# MC
#--------------------    

samples['DYJets@DYJetsToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_dielectron_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50_MG@DYJets10to50ToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_dielectron_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets@DYJetsToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_ditau_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50_MG@DYJets10to50ToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_ditau_gen == 1',
    'weight' :McWeight,
    }

samples['TTLL_powheg'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WJets_MG'] = {
    'skim'   :'',
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WW_pythia'] = {
    'skim'   :'',
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WZ_pythia'] = {
    'skim'   :'',
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :McWeight,
    }

samples['ZZ_pythia'] = {
    'skim'   :'',
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :McWeight,
    }

samples['EGamma'] = {
    'skim'   :'',
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :'1',
    }

#samples['DoubleMuon'] = {
#    'skim'   :'',
#    'cut'    :'',
#    'weight' :'1',
#    }
#--------------------    
# DATA driven QCD
#--------------------
'''
samples['DoubleEG_FakeElEl'] = {
    'skim'   :'MetFt_L_v0_LL_v0_EEOrElElFake_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }

samples['DobuleMuon_FakeEE'] = {
    'skim'   :'MetFt_L_v0_LL_v0_EEOrElElFake_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }
'''
