from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='1'
#eleWP='mediumSelectiveQ'

#McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor'
McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*recoSF*TopPtReweight*BTagSF'
#HEM
McWeight += '*((HEMweight==1.)*1.+(HEMweight!=1.)*(1-HEMweight))'

#--------------------    
# MC
#--------------------

samples['DYJets_MG'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'weight' :McWeight,
    'cut'    :'',
    }

samples['DYJets10to50_MG'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['WJets_MG'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLJ_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }
'''
samples['TTLJ_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLJ_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLJ_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLJ_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLJ_powheg_mass_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

#samples['TTLJ_powheg_mass_Do'] = {
#    'skim'   :'',
#    'weight' :McWeight,
    'cut'    :'',
#    }
'''
samples['TTLL_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }
'''
samples['TTLL_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLL_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLL_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLL_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLL_powheg_mass_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTLL_powheg_mass_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }
'''
'''
samples['TTJJ_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTJJ_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTJJ_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTJJ_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TTJJ_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

#samples['TTJJ_powheg_mass_Up'] = {
#    'skim'   :'',
#    'weight' :McWeight,
    'cut'    :'',
#    }
#
samples['TTJJ_powheg_mass_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['TT_MG'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :'',
    }

samples['ttbb'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }
'''
samples['SingleTop_sch_Lep'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['SingleTop_tch_top_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['SingleTop_tch_antitop_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['SingleTop_tW_top_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['SingleTop_tW_antitop_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['WW_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['WZ_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['ZZ_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['ttW'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }

samples['ttZ'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }
'''
samples['ttH_bb'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :'',
    }
'''

#--------------------    
# DATA driven QCD
#--------------------
'''
samples['SingleElectron_FakeEl'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    'cut'    :'',
    }

samples['SingleMuon_FakeMu'] = {
    'skim'   :'MetFt_L_v0_TTSemiLepFake_v0', #TODO: this skim is not exist currently
    'weight' :'1',
    'cut'    :'',
    }
'''
#--------------------    
# DATA
#--------------------    
samples['EGamma'] = {
    'skim'   :'',
    'weight' :'1',
    'cut'    :'',
    }

samples['SingleMuon'] = {
    'skim'   :'',
    'weight' :'1',
    'cut'    :'',
    }
#--------------------    
# Signal
#--------------------
'''
samples['CHToCB_M090'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :'',
    }
samples['CHToCB_M120'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :'',
    }
samples['CHToCB_M140'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :'',
    }
'''
