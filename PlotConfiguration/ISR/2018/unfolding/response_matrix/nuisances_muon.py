#nuisances['lumi'] = {
#    'name' : 'lumi_13TeV',
#    'samples' : {
#      'DY'	: '1.023',
#      }
#    'type' : 'lnN',
#    }

########## Efficiency and Energy Scale
trg_syst = ['evt_weight_trigSF_up_rec_Nominal/evt_weight_trigSF_rec_Nominal', 'evt_weight_trigSF_down_rec_Nominal/evt_weight_trigSF_rec_Nominal']
id_syst  = ['evt_weight_idSF_up_rec_Nominal/evt_weight_idSF_rec_Nominal', 'evt_weight_idSF_down_rec_Nominal/evt_weight_idSF_rec_Nominal']
iso_syst = ['evt_weight_isoSF_up_rec_Nominal/evt_weight_isoSF_rec_Nominal','evt_weight_isoSF_down_rec_Nominal/evt_weight_isoSF_rec_Nominal']
pileup_syst = ['evt_weight_pureweight_up/evt_weight_pureweight','evt_weight_pureweight_down/evt_weight_pureweight']
alphaS_syst  = 'PDFWeights_AlphaS'
pdfScale_syst  = 'PDFWeights_Scale'
pdfErr_syst  = 'PDFWeights_Error'

nuisances['trig_sf'] = {
    'name'	: 'trgSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'	: {
      	'DYJets'	: trg_syst,
      	'DYJets10to50_MG'	: trg_syst,
	},
}

nuisances['id_sf'] = {
    'name'      : 'IdSF',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJets'            : id_syst,
        'DYJets10to50_MG'      : id_syst,

        },
}

nuisances['iso_sf'] = {
    'name'      : 'IsoSF',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJets'            : iso_syst,
        'DYJets10to50_MG'      : iso_syst,
        },
}

nuisances['pileup'] = {
    'name'      : 'PU',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJets'            : pileup_syst,
        'DYJets10to50_MG'      : pileup_syst,
        },
}

nuisances['alphaS'] = {
    'name'	: 'AlphaS',
    'kind'	: 'PDF',
    'type'	: 'alphaS',
    'samples'	: {
      	'DYJets'	: alphaS_syst,
      	'DYJets10to50_MG'	: alphaS_syst,
	},
}

nuisances['pdfScale'] = {
    'name'	: 'Scale',
    'kind'	: 'PDF',
    'type'	: 'Scale',
    'samples'	: {
      	'DYJets'	: pdfScale_syst,
      	'DYJets10to50_MG'	: pdfScale_syst,
	},
}

##nuisances['pdfErr'] = {
##    'name'	: 'PDFerror',
##    'kind'	: 'PDF',
##    'type'	: 'HESSIAN',
##    'samples'	: {
##      	'DYJets'	: pdfErr_syst,
##      	'DYJets10to50_MG'	: pdfErr_syst,
##	},
##}
#
