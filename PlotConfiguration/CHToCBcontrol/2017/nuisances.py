
#nuisances['lumi'] = {
#    'name' : 'lumi_13TeV',
#    'type' : 'lnN',
#    'samples' : {
#      'DY'	: '1.023',
#      }
#    }

#nuisances['ttxsec'] = {
#    'name' : 'ttxsec',
#    'type' : 'lnN',
#    'samples' : {
#      'TTLJ_powheg'	: '1.06114',
#      'TTLL_powheg'	: '1.06114',
#      'TTJJ_powheg'	: '1.06114',
#      }
#    }

#nuisances['pileup'] = {
#    'name' :'pileup',
#    'kind' : 'weight',
#    'type' : 'shape',
#    'samples' : {
#      'DYJet'       : ['puWup/puW', 'puWdown/puW'],
#      'TTLL_powheg' : ['puWup/puW', 'puWdown/puW'],
#      }
#}

#nuisances['BTagSF'] = {
#    'name' : 'BTagSF',
#    'kind'	: 'weight',
#    'type'	: 'shape',
#    'samples' : {
#      'TTLJ_powheg'	: ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
#      'TTLL_powheg'	: ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
#      'TTJJ_powheg'	: ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
#      }
#}

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
trg_syst = ['trgSF_Q_Up/trgSF_Q', 'trgSF_Q_Do/trgSF_Q']
id_syst  = ['IdSF_Q_Up/IdSF_Q', 'IdSF_Q_Do/IdSF_Q']
alphaS_syst  = ['PDFWeights_AlphaS[0]', 'PDFWeights_AlphaS[1]']
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


