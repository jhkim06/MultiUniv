from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='1'
#eleWP='mediumSelectiveQ'

#XXX: diff. between IdSF and IdSF_Q ?
is2b = '(n_bjet_deepcsv_m_noSF==2)'
is3b = '(n_bjet_deepcsv_m_noSF>=3)'
McWeight_2b = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*recoSF*MisTagSF'
McWeight_3b = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*recoSF*BTagSF'
McWeight = '%s*%s+%s*%s'%(is2b, McWeight_2b, is3b, McWeight_3b)

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

samples['WJets_MG'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLJ_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLJ_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLJ_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLJ_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLJ_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLJ_powheg_mass_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLJ_powheg_mass_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg_mass_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTLL_powheg_mass_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTJJ_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTJJ_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTJJ_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTJJ_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TTJJ_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

#samples['TTJJ_powheg_mass_Up'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#
samples['TTJJ_powheg_mass_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['TT_MG'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    }

samples['ttbb'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['SingleTop_sch_top'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['SingleTop_tch_top'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['SingleTop_tch_antitop'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['SingleTop_tW_top'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['SingleTop_tW_antitop'] = {
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

samples['ttW'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['ttZ'] = {
    'skim'   :'',
    'weight' :McWeight,
    }

samples['ttH_bb'] = {
    'skim'   :'',
    'weight' :McWeight,
    }
#--------------------    
# DATA driven QCD
#--------------------
'''
samples['SingleElectron_FakeEl'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    }

samples['SingleMuon_FakeMu'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    }
'''
#--------------------    
# DATA
#--------------------    
samples['SingleElectron'] = {
    'skim'   :'MetFt_L_v1_TTSemiLep_v1_K2_v3',
    'weight' :'n_bjet_deepcsv_m_noSF>=3',
    }

samples['SingleMuon'] = {
    'skim'   :'MetFt_L_v1_TTSemiLep_v1_K2_v3',
    'weight' :'n_bjet_deepcsv_m_noSF>=3',
    }
#--------------------    
# Signal
#--------------------    
samples['CHToCB_M120'] = {
    'skim'   :'',
    'weight' :'1',
    }
