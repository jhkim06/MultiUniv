#nuisances['lumi'] = {
#    'name' : 'lumi_13TeV',
#    'samples' : {
#      'DY'	: '1.023',
#      }
#    'type' : 'lnN',
#    }

########## Efficiency and Energy Scale
trg_syst = ['evt_weight_trigSF_up_rec_Nominal/evt_weight_trigSF_rec_Nominal', 'evt_weight_trigSF_down_rec_Nominal/evt_weight_trigSF_rec_Nominal']
trgDZ_syst = ['evt_weight_trigSFDZ_up_rec_Nominal/evt_weight_trigSFDZ_rec_Nominal', 'evt_weight_trigSFDZ_down_rec_Nominal/evt_weight_trigSFDZ_rec_Nominal']
reco_syst  = ['evt_weight_recoSF_up_rec_Nominal/evt_weight_recoSF_rec_Nominal', 'evt_weight_recoSF_down_rec_Nominal/evt_weight_recoSF_rec_Nominal']
id_syst  = ['evt_weight_idSF_up_rec_Nominal/evt_weight_idSF_rec_Nominal', 'evt_weight_idSF_down_rec_Nominal/evt_weight_idSF_rec_Nominal']
l1prefire_syst = ['evt_weight_l1prefire_up/evt_weight_l1prefire','evt_weight_l1prefire_down/evt_weight_l1prefire']
pileup_syst = ['evt_weight_pureweight_up/evt_weight_pureweight','evt_weight_pureweight_down/evt_weight_pureweight']
alphaS_syst  = 'PDFWeights_AlphaS'
pdfScale_syst  = 'PDFWeights_Scale'
pdfErr_syst  = 'PDFWeights_Error'

nuisances['trig_sf'] = {
    'name'	: 'trgSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'	: {
      	'DYJets'	: trg_syst ,
      	'DYJets10to50'	: trg_syst ,
	},
}

nuisances['trigDZ_sf'] = {
    'name'	: 'trgSFDZ',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'	: {
      	'DYJets'	        : trgDZ_syst ,
      	'DYJets10to50'	: trgDZ_syst ,
	},
}

nuisances['id_sf'] = {
    'name'      : 'IdSF',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJets'            : id_syst ,
        'DYJets10to50'      : id_syst ,

        },
}

nuisances['reco_sf'] = {
    'name'      : 'recoSF',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJets'            : reco_syst ,
        'DYJets10to50'      : reco_syst ,
        },
}

nuisances['l1prefire'] = {
    'name'      : 'L1Prefire',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJets'            : l1prefire_syst ,
        'DYJets10to50'      : l1prefire_syst ,
        },
}

nuisances['pileup'] = {
    'name'      : 'PU',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJets'            : pileup_syst ,
        'DYJets10to50'      : pileup_syst ,
        },
}

#nuisances['alphaS'] = {
#    'name'	: 'AlphaS',
#    'kind'	: 'PDF',
#    'type'	: 'alphaS',
#    'samples'	: {
#      	'DYJets'	: alphaS_syst ,
#      	'DYJets10to50'	: alphaS_syst ,
#	},
#}
#
#nuisances['pdfScale'] = {
#    'name'	: 'Scale',
#    'kind'	: 'PDF',
#    'type'	: 'Scale',
#    'samples'	: {
#        'DYJets'            : pdfScale_syst ,
#        'DYJets10to50'      : pdfScale_syst ,
#	},
#}
#
###nuisances['pdfErr'] = {
###    'name'	: 'PDFerror',
###    'kind'	: 'PDF',
###    'type'	: 'HESSIAN',
###    'samples'	: {
###      	'DYJets'	: pdfErr_syst ,
###      	'DYJets10to50'	: pdfErr_syst ,
###	},
###}
###
