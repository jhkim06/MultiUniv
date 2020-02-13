#nuisances['lumi'] = {
#    'name' : 'lumi_13TeV',
#    'samples' : {
#      'DY'	: '1.023',
#      }
#    'type' : 'lnN',
#    }

########## Efficiency and Energy Scale
trg_syst = ['evt_weight_trigSF_up_rec/evt_weight_trigSF_rec', 'evt_weight_trigSF_down_rec/evt_weight_trigSF_rec']
id_syst  = ['evt_weight_idSF_up_rec/evt_weight_idSF_rec', 'evt_weight_idSF_down_rec/evt_weight_idSF_rec']
reco_syst = ['evt_weight_recoSF_up_rec/evt_weight_recoSF_rec', 'evt_weight_recoSF_down_rec/evt_weight_recoSF_rec']
l1prefire_syst = ['evt_weight_l1prefire_up/evt_weight_l1prefire','evt_weight_l1prefire_down/evt_weight_l1prefire']
pileup_syst = ['evt_weight_pureweight_up/evt_weight_pureweight','evt_weight_pureweight_down/evt_weight_pureweight']
pileup_syst = ['evt_weight_pureweight_up/evt_weight_pureweight','evt_weight_pureweight_down/evt_weight_pureweight']
alphaS_syst  = 'PDFWeights_AlphaS'
pdfScale_syst  = 'PDFWeights_Scale'
pdfErr_syst  = 'PDFWeights_Error'
#id_syst_ele = ['LepSF'+Nlep+'l_ele_'+eleWP+'_Up', 'LepSF'+Nlep+'l_ele_'+eleWP+'_Do']

nuisances['trig_sf'] = {
    'name'	: 'trgSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'	: {
      	'DYJetsToEE'	        : trg_syst ,
      	'DYJets10to50ToEE'	: trg_syst ,
      	'DYJetsToTauTau'	: trg_syst ,
      	'DYJets10to50ToTauTau'	: trg_syst ,
      	'TTLL_powheg'	        : trg_syst ,
      	'WJets_MG'	        : trg_syst ,
      	'WW_pythia'	        : trg_syst ,
      	'WZ_pythia'	        : trg_syst ,
      	'ZZ_pythia'	        : trg_syst ,
	},
}

nuisances['id_sf'] = {
    'name'      : 'IdSF',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJetsToEE'            : id_syst ,
        'DYJets10to50ToEE'      : id_syst ,
        'DYJetsToTauTau'        : id_syst ,
        'DYJets10to50ToTauTau'  : id_syst ,
        'TTLL_powheg'           : id_syst ,
        'WJets_MG'              : id_syst ,
        'WW_pythia'             : id_syst ,
        'WZ_pythia'             : id_syst ,
        'ZZ_pythia'             : id_syst ,

        },
}

nuisances['reco_sf'] = {
    'name'      : 'recoSF',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJetsToEE'            : reco_syst ,
        'DYJets10to50ToEE'      : reco_syst ,
        'DYJetsToTauTau'        : reco_syst ,
        'DYJets10to50ToTauTau'  : reco_syst ,
        'TTLL_powheg'           : reco_syst ,
        'WJets_MG'              : reco_syst ,
        'WW_pythia'             : reco_syst ,
        'WZ_pythia'             : reco_syst ,
        'ZZ_pythia'             : reco_syst ,
        },
}

nuisances['l1prefire'] = {
    'name'      : 'L1Prefire',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJetsToEE'            : l1prefire_syst ,
        'DYJets10to50ToEE'      : l1prefire_syst ,
        'DYJetsToTauTau'        : l1prefire_syst ,
        'DYJets10to50ToTauTau'  : l1prefire_syst ,
        'TTLL_powheg'           : l1prefire_syst ,
        'WJets_MG'              : l1prefire_syst ,
        'WW_pythia'             : l1prefire_syst ,
        'WZ_pythia'             : l1prefire_syst ,
        'ZZ_pythia'             : l1prefire_syst ,
        },
}

nuisances['pileup'] = {
    'name'      : 'PU',
    'kind'      : 'weight',
    'type'      : 'shape',
    'samples'   : {
        'DYJetsToEE'            : pileup_syst ,
        'DYJets10to50ToEE'      : pileup_syst ,
        'DYJetsToTauTau'        : pileup_syst ,
        'DYJets10to50ToTauTau'  : pileup_syst ,
        'TTLL_powheg'           : pileup_syst ,
        'WJets_MG'              : pileup_syst ,
        'WW_pythia'             : pileup_syst ,
        'WZ_pythia'             : pileup_syst ,
        'ZZ_pythia'             : pileup_syst ,
        },
}

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
	'WJets_MG'	: alphaS_syst ,
	},
}

nuisances['pdfScale'] = {
    'name'	: 'Scale',
    'kind'	: 'PDF',
    'type'	: 'Scale',
    'samples'	: {
      	'DYJetsToEE'	: pdfScale_syst ,
      	'DYJets10to50ToEE'	: pdfScale_syst ,
      	'DYJetsToTauTau'	: pdfScale_syst ,
      	'DYJets10to50ToTauTau'	: pdfScale_syst ,
	'TTLL_powheg'	: pdfScale_syst ,
	'WJets_MG'	: pdfScale_syst ,
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
