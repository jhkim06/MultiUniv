
nuisances['lumi'] = {
    'name' : 'lumi_13TeV',
    'type' : 'lnN',
    'samples' : {
      'DYJets'	              : '1.023',
      'DYJets10to50_MG'       : '1.023',
      'WJets_MG'              : '1.023',
      'TTLJ_powheg'	      : '1.023',
      'TTLL_powheg'	      : '1.023',
      'TTJJ_powheg'	      : '1.023',
      'SingleTop_sch_top'         : '1.023',
      'SingleTop_tch_top'     : '1.023',
      'SingleTop_tch_antitop' : '1.023',
      'SingleTop_tW_top'      : '1.023',
      'SingleTop_tW_antitop'  : '1.023',
      'WW_pythia'             : '1.023',
      'WZ_pythia'             : '1.023',
      'ZZ_pythia'             : '1.023',
      'ttW'                   : '1.023',
      'ttZ'                   : '1.023',
    }
}

nuisances['ttxsec'] = {
    'name' : 'ttxsec',
    'type' : 'lnN',
    'samples' : {
      'TTLJ_powheg'	: '1.06114',
      'TTLL_powheg'	: '1.06114',
      'TTJJ_powheg'	: '1.06114',
    }
}

#nuisances['ttMass'] = {
#    'name' : 'ttMass',
#    'kind' : 'tree',
#    'type' : 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: [1.,1.],
#    }
#    'folderUp' : '',
#    'folderDown' : '',
#}

nuisances['PUweight'] = {
    'name' :'PUweight',
    'kind' : 'weight',
    'type' : 'shape',
    'samples' : {
      'DYJet'                 : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'DYJets10to50_MG'       : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'WJets_MG'              : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'TTLJ_powheg'	      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'TTLL_powheg'	      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'TTJJ_powheg'	      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_sch_top'         : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tch_top'     : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tch_antitop' : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tW_top'      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tW_antitop'  : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'WW_pythia'             : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'WZ_pythia'             : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ZZ_pythia'             : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ttW'                   : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ttZ'                   : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],

    }
}

nuisances['IdSF'] = {
    'name' : 'IdSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets'	              : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'DYJets10to50_MG'       : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'WJets_MG'              : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'TTLJ_powheg'	      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'TTLL_powheg'	      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'TTJJ_powheg'	      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_sch_top'         : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tch_top'     : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tch_antitop' : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tW_top'      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tW_antitop'  : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'WW_pythia'             : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'WZ_pythia'             : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ZZ_pythia'             : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ttW'                   : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ttZ'                   : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
    }
}

nuisances['IsoSF'] = {
    'name' : 'IsoSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets'	              : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'DYJets10to50_MG'       : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'WJets_MG'              : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'TTLJ_powheg'	      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'TTLL_powheg'	      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'TTJJ_powheg'	      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_sch_top'         : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tch_top'     : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tch_antitop' : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tW_top'      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tW_antitop'  : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'WW_pythia'             : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'WZ_pythia'             : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ZZ_pythia'             : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ttW'                   : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ttZ'                   : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
    }
}

nuisances['recoSF'] = {
    'name' : 'recoSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets'	              : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'DYJets10to50_MG'       : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'WJets_MG'              : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'TTLJ_powheg'	      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'TTLL_powheg'	      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'TTJJ_powheg'	      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_sch_top'         : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tch_top'     : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tch_antitop' : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tW_top'      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tW_antitop'  : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'WW_pythia'             : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'WZ_pythia'             : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ZZ_pythia'             : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ttW'                   : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ttZ'                   : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
    }
}

nuisances['trgSF'] = {
    'name' : 'trgSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets'	              : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'DYJets10to50_MG'       : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'WJets_MG'              : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'TTLJ_powheg'	      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'TTLL_powheg'	      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'TTJJ_powheg'	      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_sch_top'         : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tch_top'     : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tch_antitop' : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tW_top'      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tW_antitop'  : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'WW_pythia'             : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'WZ_pythia'             : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ZZ_pythia'             : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ttW'                   : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ttZ'                   : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
    }
}

nuisances['BTagSF'] = {
    'name' : 'BTagSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets'	              : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'DYJets10to50_MG'       : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'WJets_MG'              : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'TTLJ_powheg'	      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'TTLL_powheg'	      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'TTJJ_powheg'	      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_sch_top'         : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tch_top'     : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tch_antitop' : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tW_top'      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tW_antitop'  : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'WW_pythia'             : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'WZ_pythia'             : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ZZ_pythia'             : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ttW'                   : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ttZ'                   : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
    }
}

nuisances['MisTagSF'] = {
    'name' : 'MisTagSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets'	              : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'DYJets10to50_MG'       : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'WJets_MG'              : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'TTLJ_powheg'	      : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'TTLL_powheg'	      : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'TTJJ_powheg'	      : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_sch_top'         : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tch_top'     : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tch_antitop' : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tW_top'      : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'SingleTop_tW_antitop'  : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'WW_pythia'             : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'WZ_pythia'             : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ZZ_pythia'             : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ttW'                   : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
      'ttZ'                   : ['MisTagSF_Up/MisTagSF', 'MisTagSF_Do/MisTagSF'],
    }
}

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

#nuisances['ttbbxsec'] = {
#    'name' : 'ttbbxsec',
#    'kind'	: 'weight', 
#    'type'	: 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['ttbbxsec_Up/ttbbxsec','ttbbxsec_Do/ttbbxsec'],
#      'TTLL_powheg'	: ['ttbbxsec_Up/ttbbxsec','ttbbxsec_Do/ttbbxsec'],
#      'TTJJ_powheg'	: ['ttbbxsec_Up/ttbbxsec','ttbbxsec_Do/ttbbxsec'],
#      }
#}

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

#nuisances['gentoppt_reweight'] = {
#    'name' : 'gentoppt_reweight',
#    'kind'	: 'weight', # Down is the same as nominal
#    'type'	: 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['gentoppt_reweight' , '1.'],
#      'TTLL_powheg'	: ['gentoppt_reweight' , '1.'],
#      'TTJJ_powheg'	: ['gentoppt_reweight' , '1.'],
#      }
#}

## other systematics(JEC/JER/top_mass/MEtoPS/generator) are not defined as event-by-event weight

########## Efficiency and Energy Scale
#trg_syst = ['trgSF_Q_Up/trgSF_Q', 'trgSF_Q_Do/trgSF_Q']
#id_syst  = ['IdSF_Q_Up/IdSF_Q', 'IdSF_Q_Do/IdSF_Q']
#alphaS_syst  = ['PDFWeights_AlphaS[0]', 'PDFWeights_AlphaS[1]']
#id_syst_ele = ['LepSF'+Nlep+'l_ele_'+eleWP+'_Up', 'LepSF'+Nlep+'l_ele_'+eleWP+'_Do']

#nuisances['trigg'] = {
#    'name'	: 'trg_2017',
#    'kind'	: 'weight',
#    'type'	: 'shape',
#    'samples'	: {
#      	'DYJets'	: trg_syst ,
#	'TTLL_powheg'	: trg_syst ,
#	'WJets_MG'	: trg_syst ,
#	'WW_pythia'	: trg_syst ,
#	'WZ_pythia'	: trg_syst ,
#	'ZZ_pythia'	: trg_syst ,
#	},
#}
#
#
#nuisances['eff'] = {
#    'name'	: 'eff_2017',
#    'kind'	: 'weight',
#    'type'	: 'shape',
#    'samples'	: {
#      	'DYJets'	: id_syst ,
#	'TTLL_powheg'	: id_syst ,
#	'WJets_MG'	: id_syst ,
#	'WW_pythia'	: id_syst ,
#	'WZ_pythia'	: id_syst ,
#	'ZZ_pythia'	: id_syst ,
#	},
#}
'''
nuisances['alphaS'] = {
    'name'	: 'alphaS',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'	: {
      	'DYJets'	: alphaS_syst ,
	'TTLL_powheg'	: alphaS_syst ,
	'WJets_MG'	: alphaS_syst ,
	#'WW_pythia'	: alphaS_syst ,
	#'WZ_pythia'	: alphaS_syst ,
	#'ZZ_pythia'	: alphaS_syst ,
	},
}
'''

