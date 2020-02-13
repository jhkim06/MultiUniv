#sys.path.insert(0,'./')
#structure={}
#import  structure

try:
  #mc =[skey for skey in samples if skey not in ['SingleMuon', 'SingleElectron'] and not skey.startswith('Fake')]
  mc = [skey for skey in groupPlot if skey not in ['DATA','SingleMuon', 'SingleElectron'] and not skey.startswith('Fake') and "QCD" not in skey ]
  mc = mc + [skey for skey in plot if skey not in ['DATA','SingleMuon', 'SingleElectron'] and not skey.startswith('Fake') and "QCD" not in skey ]
except NameError:
  mc =[]

mc = mc + [ "CHToCB_M%s"%mass for mass in ["090","100","110","120","130","140","150"] ]

print 'nuisances: mc:',mc

nuisances['lumi'] = {
    'name' : 'lumi_13TeV',
    'type' : 'lnN',
    'samples' : dict((skey, '1.023') for skey in mc)
}


#nuisances['stat'] = {
#    'type': 'auto',
#    'maxPoiss': '10',
#    'includeSignal': '0',
#   #  nuisance ['maxPoiss'] =  Number of threshold events for Poisson modelling
#   #  nuisance ['includeSignal'] =  Include MC stat nuisances on signal processes (1=True, 0=False)
#    'samples': {}
#}

nuisances['ttxsec'] = {
    'name' : 'ttxsec',
    'type' : 'lnN',
    'samples' : {
      'TTLJ_powheg'	: '1.06114',
      'TTLL_powheg'	: '1.06114',
      #'TTJJ_powheg'	: '1.06114',
      'ttbb'            : '1.06114',
      'CHToCB_M090'     : '1.06114',
      'CHToCB_M100'     : '1.06114',
      'CHToCB_M110'     : '1.06114',
      'CHToCB_M120'     : '1.06114',
      'CHToCB_M130'     : '1.06114',
      'CHToCB_M140'     : '1.06114',
      'CHToCB_M150'     : '1.06114',
      'tt'              : '1.06114',
      'ttCH'            : '1.06114',
    }
}

nuisances['JES'] = {
    'name' : 'JES',
    'kind' : 'variableChange',
    'type' : 'shape',
    'samples' : dict((skey, ['1','1']) for skey in mc),
    'variablesUp' : {
	'fitted_dijet_M090to110' : [
         'fitted_dijet_M090to110_JESUp',
	 'fitted_dijet_M090to110_JESUp'
	],
	'fitted_dijet_M120to150' : [
         'fitted_dijet_M120to150_JESUp',
	 'fitted_dijet_M120to150_JESUp'
	],
	'njets' : [
	  'njets_JES_Up',
	  'njets_JES_Up'
	],
	'nbtags' : [
	  'nbtags_JES_Up',
	  'nbtags_JES_Up'
	],
	'MET' : [
	  'MET_JES_Up',
	  'MET_JES_Up'
	],
    },
    'variablesDo' : {
	'fitted_dijet_M090to110' : [
          'fitted_dijet_M090to110_JESDown',
	  'fitted_dijet_M090to110_JESDown'
	],
	'fitted_dijet_M120to150' : [
          'fitted_dijet_M120to150_JESDown',
	  'fitted_dijet_M120to150_JESDown'
	],
	'njets' : [
	  'njets_JES_Do',
	  'njets_JES_Do'
	],
	'nbtags' : [
	  'nbtags_JES_Do',
	  'nbtags_JES_Do'
	],
	'MET' : [
	  'MET_JES_Do',
	  'MET_JES_Do'
	],
    },
}

nuisances['JER'] = {
    'name' : 'JER',
    'kind' : 'variableChange',
    'type' : 'shape',
    'samples' : dict((skey, ['1','1']) for skey in mc),
    'variablesUp' : {
	'fitted_dijet_M090to110' : [
          'fitted_dijet_M090to110_JERUp',
	  'fitted_dijet_M090to110_JERUp'
	],
	'fitted_dijet_M120to150' : [
          'fitted_dijet_M120to150_JERUp',
	  'fitted_dijet_M120to150_JERUp'
	],
	'njets' : [
	  'njets_JER_Up',
	  'njets_JER_Up'
	],
	'nbtags' : [
	  'nbtags_JER_Up',
	  'nbtags_JER_Up'
	],
	'MET' : [
	  'MET_JER_Up',
	  'MET_JER_Up'
	],
    },
    'variablesDo' : {
	'fitted_dijet_M090to110' : [
          'fitted_dijet_M090to110_JERDown',
	  'fitted_dijet_M090to110_JERDown'
	],
	'fitted_dijet_M120to150' : [
          'fitted_dijet_M120to150_JERDown',
	  'fitted_dijet_M120to150_JERDown'
	],
	'njets' : [
	  'njets_JER_Do',
	  'njets_JER_Do'
	],
	'nbtags' : [
	  'nbtags_JER_Do',
	  'nbtags_JER_Do'
	],
	'MET' : [
	  'MET_JER_Do',
	  'MET_JER_Do'
	],
    },
}


#nuisances['top_mass'] = {
#    'name' : 'top_mass',
#    'kind' : 'sampleChange',
#    'type' : 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['1.','1.'],
#      'TTLL_powheg'	: ['1.','1.'],
#      #'TTJJ_powheg'	: ['1.','1.'],
#      'tt'	        : ['1.','1.'],
#       
#    },
#    'samplesUp' : {
#      'TTLJ_powheg'	: 'TTLJ_powheg',
#      'TTLL_powheg'	: 'TTLL_powheg_top_massUp',
#      #'TTJJ_powheg'    : 'TTJJ_powheg' #TODO add TTJJ_powheg_mass_Up sample later
#    },
#    'samplesDo' : {
#      'TTLJ_powheg'	: 'TTLJ_powheg_top_massDown',
#      'TTLL_powheg'	: 'TTLL_powheg_top_mass_Down',
#      #'TTJJ_powheg'	: 'TTJJ_powheg_mass_Do',
#    },
#}
#
#nuisances['TuneCP5'] = {
#    'name' : 'TuneCP5',
#    'kind' : 'sampleChange',
#    'type' : 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['1.','1.'],
#      'TTLL_powheg'	: ['1.','1.'],
#      #'TTJJ_powheg'	: ['1.','1.'],
#      'tt'	        : ['1.','1.'],
#    },
#    'samplesUp' : {
#      'TTLJ_powheg'	: 'TTLJ_powheg_TuneCP5Up',
#      'TTLL_powheg'	: 'TTLL_powheg_TuneCP5Up',
#      #'TTJJ_powheg'	: 'TTJJ_powheg_Up',
#    },
#    'samplesDo' : {
#      'TTLJ_powheg'	: 'TTLJ_powheg',
#      'TTLL_powheg'	: 'TTLL_powheg_TuneCP5Down',
#      #'TTJJ_powheg'	: 'TTJJ_powheg_Do',
#    },
#}
#
#nuisances['hdamp'] = {
#    'name' : 'hdamp',
#    'kind' : 'sampleChange',
#    'type' : 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['1.','1.'],
#      'TTLL_powheg'	: ['1.','1.'],
#      'TTJJ_powheg'	: ['1.','1.'],
#      'tt'	        : ['1.','1.'],
#    },
#    'samplesUp'   : { 
#      'TTLJ_powheg'	: 'TTLJ_powheg_hdampUp',
#      'TTLL_powheg'	: 'TTLL_powheg_hdampUp',
#      #'TTJJ_powheg'	: 'TTJJ_powheg_hdamp_Up',
#    },
#    'samplesDo'   : {
#      'TTLJ_powheg'	: 'TTLJ_powheg',
#      'TTLL_powheg'	: 'TTLL_powheg_hdampDown',
#      #'TTJJ_powheg'	: 'TTJJ_powheg_hdamp_Do',
#    },
#}

#nuisances['generator'] = {
#    'name' : 'generator',
#    'kind' : 'sampleChange',
#    'type' : 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['1.','1.'],
#      'TTLL_powheg'	: ['0.','1.'],
#      'tt'              : ['1.','1.'],
#      #'TTJJ_powheg'	: ['0.','1.'],
#    },
#    'samplesUp'   : {
#      'TTLJ_powheg'	: 'TTLJ_powheg_generatorUp',
#      'TTLL_powheg'	: 'TTLL_powheg_generatorUp',
#      #'TTJJ_powheg'	: 'zeros',
#    },
#    'samplesDo' : {
#      'TTLJ_powheg'	: 'TTLJ_powheg',
#      'TTLL_powheg'	: 'TTLL_powheg',
#      #'TTJJ_powheg'	: 'TTJJ_powheg',
#    },
#    #TODO will add signal samples
#}

nuisances['PUweight'] = {
    'name' :'PUweight',
    'kind' : 'weight',
    'type' : 'shape',
    'samples' : dict((skey, ['PUweight_Up/PUweight', 'PUweight_Do/PUweight']) for skey in mc),
}

nuisances['IdSF_El'] = {
    'name' : 'IdSF_El',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['IdSF_Up/IdSF', 'IdSF_Do/IdSF']) for skey in mc),
}

nuisances['IsoSF_El'] = {
    'name' : 'IsoSF_El',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF']) for skey in mc),

}

nuisances['recoSF_El'] = {
    'name' : 'recoSF_El',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['recoSF_Up/recoSF', 'recoSF_Do/recoSF']) for skey in mc),

}

nuisances['trgSF_El'] = {
    'name' : 'trgSF_El',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['trgSF_Up/trgSF', 'trgSF_Do/trgSF']) for skey in mc),

}

nuisances['L1Prefire'] = {
    'name' : 'L1Prefire',
    'kind' : 'weight',
    'type' : 'shape',
    'samples' : dict((skey,['L1PrefireReweight_Up/L1PrefireReweight_Central','L1PrefireReweight_Down/L1PrefireReweight_Central']) for skey in mc)
}

#nuisances['BTagSF'] = {
#    'name' : 'BTagSF',
#    'kind'	: 'weight',
#    'type'	: 'shape',
#    'samples' : dict((skey, ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF']) for skey in mc),
#
#}

nuisances['BTagSF_jes'] = {
    'name' : 'BTagSF_jes',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_jes*BTagNorm_up_jes)/(BTagSF*BTagNorm)', '(BTagSF_down_jes*BTagNorm_down_jes)/(BTagSF*BTagNorm)']) for skey in mc),

}

nuisances['BTagSF_hf'] = {
    'name' : 'BTagSF_hf',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_hf*BTagNorm_up_hf)/(BTagSF*BTagNorm)', '(BTagSF_down_hf*BTagNorm_down_hf)/(BTagSF*BTagNorm)']) for skey in mc),

}

nuisances['BTagSF_lf'] = {
    'name' : 'BTagSF_lf',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_lf*BTagNorm_up_lf)/(BTagSF*BTagNorm)', '(BTagSF_down_lf*BTagNorm_down_lf)/(BTagSF*BTagNorm)']) for skey in mc),

}


nuisances['BTagSF_lfstats1'] = {
    'name' : 'BTagSF_lfstats1',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_lfstats1*BTagNorm_up_lfstats1)/(BTagSF*BTagNorm)', '(BTagSF_down_lfstats1*BTagNorm_down_lfstats1)/(BTagSF*BTagNorm)']) for skey in mc),

}

nuisances['BTagSF_lfstats2'] = {
    'name' : 'BTagSF_lfstats2',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_lfstats2*BTagNorm_up_lfstats2)/(BTagSF*BTagNorm)', '(BTagSF_down_lfstats2*BTagNorm_down_lfstats2)/(BTagSF*BTagNorm)']) for skey in mc),

}

nuisances['BTagSF_hfstats1'] = {
    'name' : 'BTagSF_hfstats1',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_hfstats1*BTagNorm_up_hfstats1)/(BTagSF*BTagNorm)', '(BTagSF_down_hfstats1*BTagNorm_down_hfstats1)/(BTagSF*BTagNorm)']) for skey in mc),

}

nuisances['BTagSF_hfstats2'] = {
    'name' : 'BTagSF_hfstats2',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_hfstats2*BTagNorm_up_hfstats2)/(BTagSF*BTagNorm)', '(BTagSF_down_hfstats2*BTagNorm_down_hfstats2)/(BTagSF*BTagNorm)']) for skey in mc),

}

nuisances['BTagSF_cferr1'] = {
    'name' : 'BTagSF_cferr1',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_cferr1*BTagNorm_up_cferr1)/(BTagSF*BTagNorm)', '(BTagSF_down_cferr1*BTagNorm_down_cferr1)/(BTagSF*BTagNorm)']) for skey in mc),

}

nuisances['BTagSF_cferr2'] = {
    'name' : 'BTagSF_cferr2',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ['(BTagSF_up_cferr2*BTagNorm_up_cferr2)/(BTagSF*BTagNorm)', '(BTagSF_down_cferr2*BTagNorm_down_cferr2)/(BTagSF*BTagNorm)']) for skey in mc),

}

'''
nuisances['MisTagSF'] = {
    'name' : 'MisTagSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : dict((skey, ) for skey in mc),
    'samples' : {
      'DYJets'	               : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'DYJets10to50_MG'       : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'WJets_MG'              : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'TTLJ_powheg'	       : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'TTLL_powheg'	       : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'TTJJ_powheg'	       : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_sch_top'     : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tch_top'     : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tch_antitop' : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tW_top'      : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tW_antitop'  : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'WW_pythia'             : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'WZ_pythia'             : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ZZ_pythia'             : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ttW'                   : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ttZ'                   : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ttH_bb'                : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ttbb'                  : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
    }
}
'''

#nuisances['leptonSF'] = {
#    'name' : 'leptonSF',
#    'kind'	: 'weight',
#    'type'	: 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['leptonSF_Up/leptonSF','leptonSF_Do/leptonSF'],
#      'TTLL_powheg'	: ['leptonSF_Up/leptonSF','leptonSF_Do/leptonSF'],
#      'TTJJ_powheg'	: ['leptonSF_Up/leptonSF','leptonSF_Do/leptonSF'],
#      }
#}
#
nuisances['ttbbxsec'] = {
    'name' : 'ttbbxsec',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'   : {
      'TTLJ_powheg' : ['(831.59-5.0)/(831.59-2.5)','831.59/(831.59-2.5)'],
      'TTLL_powheg' : ['(831.59-5.0)/(831.59-2.5)','831.59/(831.59-2.5)'],
      'ttbb'	    : ['2.0','0.0'],
      'tt'          : ['1.0','1.0'],
      }
}
#
#nuisances['generator'] = {
#    'name' : 'generator',
#    'kind'	: 'weight', # Down is the same as nominal, nuisance for Signal sample
#    'type'	: 'shape',
#    'samples' : {
#      'CHToCB_M090'	: ['generator','1'],
#      'CHToCB_M100'	: ['generator','1'],
#      'CHToCB_M110'	: ['generator','1'],
#      }
#}

### NOT use in combination? it is not applicable to signal
#nuisances['gentoppt_reweight'] = {
#    'name' : 'gentoppt_reweight',
#    'kind'	: 'weight', # Down is the same as nominal
#    'type'	: 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['TopPtReweight' , '1.'],
#      'TTLL_powheg'	: ['TopPtReweight' , '1.'],
#      #'TTJJ_powheg'	: ['TopPtReweight' , '1.'],
#      }
#}

## other systematics(JEC/JER/top_mass/MEtoPS/generator) are not defined as event-by-event weight

########## Efficiency and Energy Scale
#alphaS_syst  = ['PDFWeights_AlphaS[0]', 'PDFWeights_AlphaS[1]']
#id_syst_ele = ['LepSF'+Nlep+'l_ele_'+eleWP+'_Up', 'LepSF'+Nlep+'l_ele_'+eleWP+'_Do']

nuisances['alphaS'] = {
    'name'	: 'alphaS',
    'kind'	: 'PDF',
    'type'	: 'shape',
    'samples' : dict((skey, 'PDFWeights_AlphaS') for skey in mc)
}

nuisances['PDFError'] = {
    'name'	: 'pdfHESSIAN',
    'kind'	: 'PDF',
    'type'	: 'shape',
    'samples' : dict((skey, 'PDFWeights_Error') for skey in mc)
}
nuisances['PDfScale'] = {
    'name'	: 'pdfScale',
    'kind'	: 'PDF',
    'type'	: 'shape',
    'samples' : dict((skey, 'PDFWeights_Scale') for skey in mc)
}

