#nuisances['lumi'] = {
#    'name' : 'lumi_13TeV',
#    'samples' : {
#      'DY'	: '1.023',
#      }
#    'type' : 'lnN',
#    }

########## Efficiency and Energy Scale
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
#	},
#}

