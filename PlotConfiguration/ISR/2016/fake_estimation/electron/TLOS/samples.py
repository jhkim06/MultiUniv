from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

FakeRate            = 'evt_weight_TL_rec_Fake'
McWeight            = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_TL_rec_Fake'
McWeightZptReweight = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_TL_rec_Fake * evt_weight_zptcorr_Fake'

#--------------------
# MC
#--------------------

samples['DYJets@DYJetsToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_dielectron_hardprocess == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50@DYJets10to50ToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_dielectron_hardprocess == 1',
    'weight' :McWeight,
    }

samples['DYJets@DYJetsToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_ditau_hardprocess == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50@DYJets10to50ToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_ditau_hardprocess == 1',
    'weight' :McWeight,
    }

samples['SingleTop_tW_antitop_Incl'] = {                                                                                                                                                                                                                                            'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :McWeight,
    }

samples['SingleTop_tW_top_Incl'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
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

samples['DoubleEG'] = {
    'skim'   :'',
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :FakeRate,
    }

