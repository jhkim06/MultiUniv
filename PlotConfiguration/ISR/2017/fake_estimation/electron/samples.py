from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='2'
#eleWP='mediumSelectiveQ'

FakeRate = 'evt_weight_LL_rec_Fake' 
McWeight = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_LL_rec_Fake' 

#--------------------    
# MC
#--------------------    

#samples['DYJets'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['DYJets10to50'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'combine_cuts' : True,
#    'cut'    :'',
#    'weight' :McWeight,
#    }

samples['DYJets@DYJetsToElEl'] = {
    'skim'   :'ISR_v2_Eff_SF_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_dielectron_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50@DYJets10to50ToElEl'] = {
    'skim'   :'ISR_v2_Eff_SF_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_dielectron_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets@DYJetsToTauTau'] = {
    'skim'   :'ISR_v2_Eff_SF_v1', # use default skim defined in configuration.py
    'combine_cuts' : True,
    'cut'    :'evt_tag_ditau_gen == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50@DYJets10to50ToTauTau'] = {
    'skim'   :'ISR_v2_Eff_SF_v1', # use default skim defined in configuration.py
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

samples['DoubleEG'] = {
    'skim'   :'ISR_detector_only_v2',
    'combine_cuts' : True,
    'cut'    :'',
    'weight' :FakeRate,
    }

#samples['DoubleMuon@DoubleMuonQCDFakeRate'] = {
#    'skim'   :'ISR_fake_rate_v2_Eff_SF_v1',
#    'combine_cuts' : False,
#    'cut'    :'evt_tag_analysisevnt_sel_rec == 1 && evt_tag_dielectron_rec == 1 && evt_tag_dielectron_rec == 0 && dilep_pt_rec < 100. && dilep_mass_rec > 40.',
#    'weight' :FakeRate,
#    }

#samples['DoubleMuon'] = {
#    'skim'   :'',
#    'weight' :'1',
#    }

#--------------------    
# DATA driven QCD
#--------------------
'''
samples['DoubleEG_FakeElEl'] = {
    'skim'   :'MetFt_L_v0_LL_v0_ElElOrElElFake_v2_Eff_SF_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }

samples['DobuleMuon_FakeElEl'] = {
    'skim'   :'MetFt_L_v0_LL_v0_ElElOrElElFake_v2_Eff_SF_v1', #TODO: this skim is not exist currently
    'weight' :'1',
    }
'''
