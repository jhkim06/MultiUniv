
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

nuisances['alphaS'] = {
    'name'	: 'AlphaS',
    'kind'	: 'PDF',
    'type'	: 'alphaS',
    'samples'	: {
      	'DYJetsToEE'	: alphaS_syst ,
      	'DYJets10to50ToEE'	: alphaS_syst ,
      	'DYJetsToTauTau'	: alphaS_syst ,
      	'DYJets10to50ToTauTau'	: alphaS_syst ,
	'TTLL_powheg'	: alphaS_syst ,
	#'WJets_MG'	: alphaS_syst ,
	#'WW_pythia'	: alphaS_syst ,
	#'WZ_pythia'	: alphaS_syst ,
	#'ZZ_pythia'	: alphaS_syst ,
	},
}

nuisances['pdfScale'] = {
    'name'	: 'Scale',
    'kind'	: 'PDF',
    'type'	: 'Scale',
    'samples'	: {
        'DYJetsToEE'            : pdfScale_syst ,
        'DYJets10to50ToEE'      : pdfScale_syst ,
        'DYJetsToTauTau'        : pdfScale_syst ,
        'DYJets10to50ToTauTau'  : pdfScale_syst ,
	'TTLL_powheg'	: pdfScale_syst ,
	#'WJets_MG'	: pdfScale_syst ,
	#'WW_pythia'	: pdfScale_syst ,
	#'WZ_pythia'	: pdfScale_syst ,
	#'ZZ_pythia'	: pdfScale_syst ,
	},
}

#nuisances['pdfErr'] = {
#    'name'	: 'PDFerror',
#    'kind'	: 'PDF',
#    'type'	: 'HESSIAN',
#    'samples'	: {
#      	'DYJetsToEE'	: pdfErr_syst ,
#      	'DYJets10to50ToEE'	: pdfErr_syst ,
#      	'DYJetsToTauTau'	: pdfErr_syst ,
#      	'DYJets10to50ToTauTau'	: pdfErr_syst ,
#	'TTLL_powheg'	: pdfErr_syst ,
#	'WJets_MG'	: pdfErr_syst ,
#	'WW_pythia'	: pdfErr_syst ,
#	'WZ_pythia'	: pdfErr_syst ,
#	'ZZ_pythia'	: pdfErr_syst ,
#	},
#}

