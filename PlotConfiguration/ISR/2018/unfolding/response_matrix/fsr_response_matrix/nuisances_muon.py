#nuisances['lumi'] = {
#    'name' : 'lumi_13TeV',
#    'samples' : {
#      'DY'	: '1.023',
#      }
#    'type' : 'lnN',
#    }

########## Efficiency and Energy Scale
trg_syst = ['electron_double_trigSFUp_DoubleElectron_passMediumID/electron_double_trigSF_DoubleElectron_passMediumID', 'electron_double_trigSFDn_DoubleElectron_passMediumID/electron_double_trigSF_DoubleElectron_passMediumID']
id_syst  = ['electron_double_idSFUp_passMediumID/electron_double_idSF_passMediumID', 'electron_double_idSFDn_passMediumID/electron_double_idSF_passMediumID']
reco_syst = ['electron_double_recoSFUp_passMediumID/electron_double_recoSF_passMediumID','electron_double_recoSFDn_passMediumID/electron_double_recoSF_passMediumID']
l1prefire_syst = ['evt_weight_l1prefire_up/evt_weight_l1prefire','evt_weight_l1prefire_down/evt_weight_l1prefire']
pileup_syst = ['evt_weight_pureweight_up/evt_weight_pureweight','evt_weight_pureweight_down/evt_weight_pureweight']
alphaS_syst  = 'PDFWeights_AlphaS'
pdfScale_syst  = 'PDFWeights_Scale'
pdfErr_syst  = 'PDFWeights_Error'
#id_syst_ele = ['LepSF'+Nlep+'l_ele_'+eleWP+'_Up', 'LepSF'+Nlep+'l_ele_'+eleWP+'_Do']

nuisances['alphaS'] = {
    'name'	: 'alphaS',
    'kind'	: 'PDF',
    'type'	: 'alphaS',
    'samples'	: {
      	'DYJets'	: alphaS_syst ,
      	'DYJets10to50_MG'	: alphaS_syst ,
	},
}

nuisances['pdfScale'] = {
    'name'	: 'pdfScale',
    'kind'	: 'PDF',
    'type'	: 'Scale',
    'samples'	: {
      	'DYJets'	: pdfScale_syst ,
      	'DYJets10to50_MG'	: pdfScale_syst ,
	},
}

#nuisances['pdfErr'] = {
#    'name'	: 'pdfErr',
#    'kind'	: 'PDF',
#    'type'	: 'HESSIAN',
#    'samples'	: {
#      	'DYJets'	: pdfErr_syst ,
#	'TTLL_powheg'	: pdfErr_syst ,
#	'WJets_MG'	: pdfErr_syst ,
#	'WW_pythia'	: pdfErr_syst ,
#	'WZ_pythia'	: pdfErr_syst ,
#	'ZZ_pythia'	: pdfErr_syst ,
#	},
#}

