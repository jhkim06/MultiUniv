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
alphaS_syst  = ['PDFWeights_AlphaS']
pdfScale_syst  = ['PDFWeights_Scale']
pdfErr_syst  = ['PDFWeights_Error']
#id_syst_ele = ['LepSF'+Nlep+'l_ele_'+eleWP+'_Up', 'LepSF'+Nlep+'l_ele_'+eleWP+'_Do']

#nuisances['trig_sf'] = {
#    'name'	: 'trg_2016',
#    'kind'	: 'weight',
#    'type'	: 'shape',
#    'samples'	: {
#      	'DYJets'	: trg_syst ,
#      	'DYJets10to50'	: trg_syst ,
#	},
#}
#
#nuisances['id_sf'] = {
#    'name'      : 'id_2016',
#    'kind'      : 'weight',
#    'type'      : 'shape',
#    'samples'   : {
#        'DYJets'        : id_syst ,
#        'DYJets10to50'  : id_syst ,
#        },
#}
#
#nuisances['reco_sf'] = {
#    'name'      : 'reco_2016',
#    'kind'      : 'weight',
#    'type'      : 'shape',
#    'samples'   : {
#        'DYJets'        : reco_syst ,
#        'DYJets10to50'  : reco_syst ,
#        },
#}
#
#nuisances['l1prefire'] = {
#    'name'      : 'l1prefire_2016',
#    'kind'      : 'weight',
#    'type'      : 'shape',
#    'samples'   : {
#        'DYJets'        : l1prefire_syst ,
#        'DYJets10to50'  : l1prefire_syst ,
#        },
#}
#
#nuisances['pileup'] = {
#    'name'      : 'pileup_2016',
#    'kind'      : 'weight',
#    'type'      : 'shape',
#    'samples'   : {
#        'DYJets'        : pileup_syst ,
#        'DYJets10to50'  : pileup_syst ,
#        },
#}

#nuisances['alphaS'] = {
#    'name'	: 'alphaS',
#    'kind'	: 'PDF',
#    'type'	: 'alphaS',
#    'samples'	: {
#      	'DYJets'	: alphaS_syst ,
#	'TTLL_powheg'	: alphaS_syst ,
#	'WJets_MG'	: alphaS_syst ,
#	'WW_pythia'	: alphaS_syst ,
#	'WZ_pythia'	: alphaS_syst ,
#	'ZZ_pythia'	: alphaS_syst ,
#	},
#}
#
#nuisances['pdfScale'] = {
#    'name'	: 'pdfScale',
#    'kind'	: 'PDF',
#    'type'	: 'Scale',
#    'samples'	: {
#      	'DYJets'	: pdfScale_syst ,
#	'TTLL_powheg'	: pdfScale_syst ,
#	'WJets_MG'	: pdfScale_syst ,
#	'WW_pythia'	: pdfScale_syst ,
#	'WZ_pythia'	: pdfScale_syst ,
#	'ZZ_pythia'	: pdfScale_syst ,
#	},
#}
#
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

