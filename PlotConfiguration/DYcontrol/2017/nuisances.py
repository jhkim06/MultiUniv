
#nuisances['pileup'] = {
#    'name' :'pileup',
#    'kind' : 'weight',
#    'type' : 'shape',
#    'samples' : {
#      'DYJet'       : ['puWup/puW', 'puWdown/puW'],
#      'TTLL_powheg' : ['puWup/puW', 'puWdown/puW'],
#      }
#    }

#nuisances['lumi'] = {
#    'name' : 'lumi_13TeV',
#    'samples' : {
#      'DY'	: '1.023',
#      }
#    'type' : 'lnN',
#    }


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
	'WW_pythia'	: alphaS_syst ,
	'WZ_pythia'	: alphaS_syst ,
	'ZZ_pythia'	: alphaS_syst ,
	},
}


