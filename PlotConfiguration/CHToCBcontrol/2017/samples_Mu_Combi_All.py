from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

#Nlep='1'
#eleWP='mediumSelectiveQ'

#XXX: diff. between IdSF and IdSF_Q ?
McWeight = 'baseW*PUweight*trgSF*IdSF*IsoSF*recoSF*BTagSF*BTagNorm*TopPtReweight*L1PrefireReweight_Central'
McWeight_tt = McWeight + "*((831.59-2.5)/831.59)"
McWeight_ch = McWeight + "*(0.01)"
#--------------------    
# MC
#--------------------    

IsoCut = 'passIso==1'

samples['DYJets'] = {
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
    'weight' :McWeight_tt,
    'cut'    :IsoCut,
    }

#samples['TTLJ_powheg_Tune_Up@TTLJ_powheg_TuneCP5Up'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLJ_powheg_Tune_Do@TTLJ_powheg_TuneCP5Down'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLJ_powheg_hdamp_Up@TTLJ_powheg_hdampUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLJ_powheg_hdamp_Do@TTLJ_powheg_hdampDown'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLJ_powheg_mass_Up@TTLJ_powheg_top_massUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#samples['TTLJ_powheg_mass_Do@TTLJ_powheg_top_massDown'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }


samples['TTLL_powheg'] = {
    'skim'   :'',
    'weight' :McWeight_tt,
    'cut'    :IsoCut,
    }

#samples['TTLL_powheg_Tune_Up@TTLL_powheg_TuneCP5Up'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLL_powheg_Tune_Do@TTLL_powheg_TuneCP5Down'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLL_powheg_hdamp_Up@TTLL_powheg_hdampUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLL_powheg_hdamp_Do@TTLL_powheg_hdampDown'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLL_powheg_mass_Up@TTLL_powheg_top_massUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }
#
#samples['TTLL_powheg_mass_Do@TTLL_powheg_top_massDown'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt,
#    'cut'    :IsoCut,
#    }

#samples['TTJJ_powheg'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#
#samples['TTJJ_powheg_Up'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#
#samples['TTJJ_powheg_Do'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#
#samples['TTJJ_powheg_hdamp_Up'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#
#samples['TTJJ_powheg_hdamp_Do'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#
#samples['TTJJ_powheg_mass_Up'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#
#samples['TTJJ_powheg_mass_Do'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    }
#

#samples['TT_aMC@TTLJ_powheg_generatorUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt+"*(0.5)",
#    'cut'    :IsoCut,
#    }
#samples['TT_aMC@TTLL_powheg_generatorUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt+"*(0.5)",
#    'cut'    :IsoCut,
#    }
#
#samples['TT_powheg_herwig@TTLJ_powheg_herwigUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt+"*(0.5)",
#    'cut'    :IsoCut,
#    }
#samples['TT_powheg_herwig@TTLL_powheg_herwigUp'] = {
#    'skim'   :'',
#    'weight' :McWeight_tt+"*(0.5)",
#    'cut'    :IsoCut,
#    }
#
#
#samples['ttbb'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    'cut'    :IsoCut,
#    }

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

samples['SingleTop_tW_top_NoFullyHad'] = {
    'skim'   :'',
    'weight' :McWeight,
    'cut'    :IsoCut,
    }

samples['SingleTop_tW_antitop_NoFullyHad'] = {
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

#samples['ttHTobb'] = {
#    'skim'   :'',
#    'weight' :McWeight,
#    'cut'    :IsoCut,
#    }

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
#samples['SingleElectron'] = {
#    'skim'   :'',
#    'weight' :'1',
#    'cut'    :'',
#    }

samples['SingleMuon'] = {
    'skim'   :'',
    'weight' :'1',
    'cut'    :IsoCut,
    }

#--------------------    
# DATA driven QCD
#--------------------

#AntiIsoCut = 'passAntiIso==1'
#samples_QCD ={}
#for key, val in samples.iteritems():
#  if "@" in key: # not to include top systematic samples
#    continue
#  key_QCD = "%s@%s_QCD"%(key,key)
#  samples_QCD[key_QCD] = val.copy()
#  samples_QCD[key_QCD]['cut'] = AntiIsoCut
#  #XXX
#  if key == 'SingleElectron' or key == 'SingleMuon':
#    samples_QCD[key_QCD]['skim'] = 'MetFt_L_v2_TTSemiLep_v1_K2_v1_ABCD_v1'
#    samples_QCD[key_QCD]['weight'] += '*ABCDweight' #normalization of iso/anti_iso
#  else:
#    samples_QCD[key_QCD]['skim'] = 'MetFt_L_v2_TTSemiLep_v1_K2_v1_ABCD_v1'
#    samples_QCD[key_QCD]['weight'] += '*(-ABCDweight)'
#samples.update(samples_QCD)


#--------------------    
# Signal
#--------------------
#samples['CHToCB_M090'] = {
#    'skim'   :'',
#    'weight' :McWeight_ch,
#    'cut'    :IsoCut,
#    }
#samples['CHToCB_M100'] = {
#    'skim'   :'',
#    'weight' :McWeight_ch,
#    'cut'    :IsoCut,
#    }
#samples['CHToCB_M110'] = {
#    'skim'   :'',
#    'weight' :McWeight_ch, 
#    'cut'    :IsoCut,
#    }
#samples['CHToCB_M120'] = {
#    'skim'   :'',
#    'weight' :McWeight_ch, 
#    'cut'    :IsoCut,
#    }
#samples['CHToCB_M130'] = {
#    'skim'   :'',
#    'weight' :McWeight_ch, 
#    'cut'    :IsoCut,
#    }
#samples['CHToCB_M140'] = {
#    'skim'   :'',
#    'weight' :McWeight_ch, 
#    'cut'    :IsoCut,
#    }
#samples['CHToCB_M150'] = {
#    'skim'   :'',
#    'weight' :McWeight_ch, 
#    'cut'    :IsoCut,
#    }
