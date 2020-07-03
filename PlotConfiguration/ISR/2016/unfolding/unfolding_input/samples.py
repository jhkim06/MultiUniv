from CommonPyTools.python.CommonTools import *

#McWeight = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal * evt_weight_trigSFDZ_rec_Nominal / evt_weight_bveto'
McWeight        = 'evt_weight_total_gen * 1.                 * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal * evt_weight_trigSFDZ_rec_Nominal'
McWeightZptCorr = 'evt_weight_total_gen * zptweight_electron * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal * evt_weight_trigSFDZ_rec_Nominal'

#--------------------
# MC
#--------------------

samples['DYJets@DYJetsToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_dielectron_hardprocess == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50@DYJets10to50ToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_dielectron_hardprocess == 1',
    'weight' :McWeight,
    }

samples['DYJets@DYJetsToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_ditau_hardprocess == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50@DYJets10to50ToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_ditau_hardprocess == 1',
    'weight' :McWeight,
    }

samples['TTLL_powheg'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WJets_MG'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WW_pythia'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WZ_pythia'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['ZZ_pythia'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['DoubleEG'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :'1',
    }

