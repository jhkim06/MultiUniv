from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='1'
#eleWP='mediumSelectiveQ'

#McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*recoSF*BTagSF'
#XXX
#McWeight = 'baseW*trgSF*recoSF*IdSF*IsoSF*recoSF*TopPtReweight*BTagSF'
#test version pileUp weight
McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*recoSF*TopPtReweight*BTagSF'
#HEM
McWeight += '*((HEMweight==1.)*1.+(HEMweight!=1.)*(1-HEMweight))'

#--------------------    
# MC
#--------------------    

IsoCut = 'passIso==1'

samples['DYJets_MG'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['DYJets10to50_MG'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['WJets_MG'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLJ_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }
'''
samples['TTLJ_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLJ_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLJ_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLJ_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLJ_powheg_mass_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

#samples['TTLJ_powheg_mass_Do'] = {
#    'skim'   :'',
#    'weight' :McWeight,
    'cut'    :IsoCut,
#    }
'''
samples['TTLL_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }
'''
samples['TTLL_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLL_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLL_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLL_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLL_powheg_mass_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTLL_powheg_mass_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }
'''
'''
samples['TTJJ_powheg'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTJJ_powheg_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTJJ_powheg_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTJJ_powheg_hdamp_Up'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TTJJ_powheg_hdamp_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

#samples['TTJJ_powheg_mass_Up'] = {
#    'skim'   :'',
#    'weight' :McWeight,
    'cut'    :IsoCut,
#    }
#
samples['TTJJ_powheg_mass_Do'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['TT_MG'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :IsoCut,
    }

samples['ttbb'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }
'''
samples['SingleTop_sch_Lep'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['SingleTop_tch_top_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['SingleTop_tch_antitop_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['SingleTop_tW_top_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['SingleTop_tW_antitop_Incl'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['WW_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['WZ_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['ZZ_pythia'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['ttW'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['ttZ'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }
'''
samples['ttH_bb'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }
'''

#--------------------    
# DATA driven QCD (Matrix Element method)
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
    'cut'    :IsoCut,
    }

samples['SingleMuon'] = {
    'skim'   :'',
    'weight' :'1',
    'cut'    :IsoCut,
    }
#-------------------
# DATA driven QCD (ABCD Method)
#-------------------
AntiIsoCut = 'passAntiIso==1'
samples_QCD ={}
for key, val in samples.iteritems():
  key_QCD = "%s@%s_QCD"%(key,key)
  samples_QCD[key_QCD] = val.copy()
  samples_QCD[key_QCD]['cut'] = AntiIsoCut
  #XXX
  if key == 'EGamma' or key == 'SingleMuon':
    samples_QCD[key_QCD]['weight'] += '*ABCDweight' #normalization of iso/anti_iso
  else:
    samples_QCD[key_QCD]['weight'] += '*(-ABCDweight)'
samples.update(samples_QCD)

#--------------------    
# Signal
#--------------------
'''
samples['CHToCB_M090'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :IsoCut,
    }
samples['CHToCB_M120'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :IsoCut,
    }
samples['CHToCB_M140'] = {
    'skim'   :'',
    'weight' :McWeight+'/PUweight', #XXX no PUweight
    'cut'    :IsoCut,
    }
'''
