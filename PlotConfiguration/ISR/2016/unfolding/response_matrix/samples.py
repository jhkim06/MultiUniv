from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

McWeight        = 'evt_weight_total_gen * 1.                 * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal * evt_weight_trigSFDZ_rec_Nominal'
McWeightZptCorr = 'evt_weight_total_gen * zptweight_electron * evt_weight_total_rec * evt_weight_recoSF_rec_Nominal * evt_weight_idSF_rec_Nominal * evt_weight_trigSF_rec_Nominal * evt_weight_trigSFDZ_rec_Nominal'
GenMcWeightZptCorr = 'evt_weight_total_gen * zptweight_electron'
#McWeight = 'evt_weight_total_gen'

#--------------------
# MC
#--------------------

#samples['DYJets200to400'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'dilep_mass_FSRgamma_gen_ispromptfinal > 200',
#    'weight' :McWeight,
#    }

samples['DYJets'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :GenMcWeightZptCorr,
    }

samples['DYJets10to50'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :GenMcWeightZptCorr,
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
