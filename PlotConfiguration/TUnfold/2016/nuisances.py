
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
trg_syst = ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF']
id_syst  = ['IdSF_Q_Up/IdSF_Q', 'IdSF_Q_Do/IdSF_Q']
alphaS_syst  = ['PDFWeights_AlphaS']
pdfScale_syst  = ['PDFWeights_Scale']
pdfErr_syst  = ['PDFWeights_Error']
#id_syst_ele = ['LepSF'+Nlep+'l_ele_'+eleWP+'_Up', 'LepSF'+Nlep+'l_ele_'+eleWP+'_Do']

nuisances['trigg'] = {
    'name'	: 'trg_2016',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'	: {
      	'DYJets'	: trg_syst ,
	'TT_powheg'	: trg_syst ,
	'WJets_MG'	: trg_syst ,
	'WW_pythia'	: trg_syst ,
	'WZ_pythia'	: trg_syst ,
	'ZZ_pythia'	: trg_syst ,
	},
}


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

