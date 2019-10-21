from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

McWeight = 'evt_weight_total_gen * evt_weight_total_rec * muon_double_idSF_POGTightWithTightIso * muon_double_isoSF_POGTightWithTightIso * muon_double_trigSF_DoubleMuon_POGTightWithTightIso'

#McWeight = 'evt_weight_total_gen * evt_weight_total_rec'

#--------------------    
# MC
#--------------------    

samples['DYJets@DYJetsToMuMu'] = {
    'skim'   :'ISR_v1_Eff_SF_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_dimuon_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50_MG@DYJets10to50ToMuMu'] = {
    'skim'   :'ISR_v1_Eff_SF_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_dimuon_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets@DYJetsToTauTau'] = {
    'skim'   :'ISR_v1_Eff_SF_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_ditau_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50_MG@DYJets10to50ToTauTau'] = {
    'skim'   :'ISR_v1_Eff_SF_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_ditau_gen == 1',
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

samples['DoubleMuon'] = {
    'skim'   :'MetFt_L_v2_LL_v1_ISR_detector_only_v1',
    'cut'    :'',
    'weight' :'1',
    }
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
