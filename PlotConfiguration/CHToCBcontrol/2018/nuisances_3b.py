nuisances['lumi'] = {
    'name' : 'lumi_13TeV',
    'type' : 'lnN',
    'samples' : {
      'DYJets_MG'	              : '1.023',
      'DYJets10to50_MG'       : '1.023',
      'WJets_MG'              : '1.023',
      'TTLJ_powheg'	      : '1.023',
      'TTLL_powheg'	      : '1.023',
      'TTJJ_powheg'	      : '1.023',
      'SingleTop_sch_Lep'     : '1.023',
      'SingleTop_tch_top_Incl'     : '1.023',
      'SingleTop_tch_antitop_Incl' : '1.023',
      'SingleTop_tW_top_Incl'      : '1.023',
      'SingleTop_tW_antitop_Incl'  : '1.023',
      'WW_pythia'             : '1.023',
      'WZ_pythia'             : '1.023',
      'ZZ_pythia'             : '1.023',
      'ttW'                   : '1.023',
      'ttZ'                   : '1.023',
      'ttH_bb'                : '1.023',
      'ttbb'                  : '1.023',
    }
}

nuisances['ttxsec'] = {
    'name' : 'ttxsec',
    'type' : 'lnN',
    'samples' : {
      'TTLJ_powheg'	: '1.06114',
      'TTLL_powheg'	: '1.06114',
      'TTJJ_powheg'	: '1.06114',
    }
}

nuisances['JES'] = {
    'name' : 'JES',
    'kind' : 'variableChange',
    'type' : 'shape',
    'samples' : {
      'DYJet'                 : ['1', '1'],
      'DYJets10to50_MG'       : ['1', '1'],
      'WJets_MG'              : ['1', '1'],
      'TTLJ_powheg'	      : ['1', '1'],
      'TTLL_powheg'	      : ['1', '1'],
      'TTJJ_powheg'	      : ['1', '1'],
      'SingleTop_sch_Lep'     : ['1', '1'],
      'SingleTop_tch_top_Incl'     : ['1', '1'],
      'SingleTop_tch_antitop_Incl' : ['1', '1'],
      'SingleTop_tW_top_Incl'      : ['1', '1'],
      'SingleTop_tW_antitop_Incl'  : ['1', '1'],
      'WW_pythia'             : ['1', '1'],
      'WZ_pythia'             : ['1', '1'],
      'ZZ_pythia'             : ['1', '1'],
      'ttW'                   : ['1', '1'],
      'ttZ'                   : ['1', '1'],
      'ttH_bb'                : ['1', '1'],
      'ttbb'                  : ['1', '1'],
    },
    'variablesUp' : {
	'fitted_dijet_mass' : [
          'fitted_dijet_mass_JES_Up',
	  'fitted_dijet_m_JES_Up'
	],
	'fitter_status' : [
	  'fitter_status_JES_Up',
	  'fitter_status_JES_Up'
	],
	'1st_leading_jet_pt' : [
	  '1st_leading_jet_pt_JES_Up',
	  'selected_jet_pt_JES_Up[0]'
	],
	'2nd_leading_jet_pt' : [
	  '2nd_leading_jet_pt_JES_Up',
	  'selected_jet_pt_JES_Up[1]'
        ],
	'3rd_leading_jet_pt' : [
	  '3rd_leading_jet_pt_JES_Up',
	  'selected_jet_pt_JES_Up[2]'
        ],
	'4th_leading_jet_pt' : [
	  '4th_leading_jet_pt_JES_Up',
	  'selected_jet_pt_JES_Up[3]',
        ],
	'njets' : [
	  'njets_JES_Up',
	  'njets_JES_Up'
	],
	'nbtags' : [
	  'nbtags_JES_Up',
	  'nbtags_JES_Up'
	],
	'MET' : [
	  'MET_JES_Up',
	  'MET_JES_Up'
	],
    },
    'variablesDo' : {
	'fitted_dijet_mass' : [
          'fitted_dijet_mass_JES_Do',
	  'fitted_dijet_m_JES_Do'
	],
	'fitter_status' : [
	  'fitter_status_JES_Do',
	  'fitter_status_JES_Do'
	],
	'1st_leading_jet_pt' : [
	  '1st_leading_jet_pt_JES_Do',
	  'selected_jet_pt_JES_Do[0]'
	],
	'2nd_leading_jet_pt' : [
	  '2nd_leading_jet_pt_JES_Do',
	  'selected_jet_pt_JES_Do[1]'
        ],
	'3rd_leading_jet_pt' : [
	  '3rd_leading_jet_pt_JES_Do',
	  'selected_jet_pt_JES_Do[2]'
        ],
	'4th_leading_jet_pt' : [
	  '4th_leading_jet_pt_JES_Do',
	  'selected_jet_pt_JES_Do[3]',
        ],
	'njets' : [
	  'njets_JES_Do',
	  'njets_JES_Do'
	],
	'nbtags' : [
	  'nbtags_JES_Do',
	  'nbtags_JES_Do'
	],
	'MET' : [
	  'MET_JES_Do',
	  'MET_JES_Do'
	],
    },
}

nuisances['JER'] = {
    'name' : 'JER',
    'kind' : 'variableChange',
    'type' : 'shape',
    'samples' : {
      'DYJet'                 : ['1', '1'],
      'DYJets10to50_MG'       : ['1', '1'],
      'WJets_MG'              : ['1', '1'],
      'TTLJ_powheg'	      : ['1', '1'],
      'TTLL_powheg'	      : ['1', '1'],
      'TTJJ_powheg'	      : ['1', '1'],
      'SingleTop_sch_Lep'     : ['1', '1'],
      'SingleTop_tch_top_Incl'     : ['1', '1'],
      'SingleTop_tch_antitop_Incl' : ['1', '1'],
      'SingleTop_tW_top_Incl'      : ['1', '1'],
      'SingleTop_tW_antitop_Incl'  : ['1', '1'],
      'WW_pythia'             : ['1', '1'],
      'WZ_pythia'             : ['1', '1'],
      'ZZ_pythia'             : ['1', '1'],
      'ttW'                   : ['1', '1'],
      'ttZ'                   : ['1', '1'],
      'ttH_bb'                : ['1', '1'],
      'ttbb'                  : ['1', '1'],
    },
    'variablesUp' : {
	'fitted_dijet_mass' : [
          'fitted_dijet_mass_JER_Up',
	  'fitted_dijet_m_JER_Up'
	],
	'fitter_status' : [
	  'fitter_status_JER_Up',
	  'fitter_status_JER_Up'
	],
	'1st_leading_jet_pt' : [
	  '1st_leading_jet_pt_JER_Up',
	  'selected_jet_pt_JER_Up[0]'
	],
	'2nd_leading_jet_pt' : [
	  '2nd_leading_jet_pt_JER_Up',
	  'selected_jet_pt_JER_Up[1]'
        ],
	'3rd_leading_jet_pt' : [
	  '3rd_leading_jet_pt_JER_Up',
	  'selected_jet_pt_JER_Up[2]'
        ],
	'4th_leading_jet_pt' : [
	  '4th_leading_jet_pt_JER_Up',
	  'selected_jet_pt_JER_Up[3]',
        ],
	'njets' : [
	  'njets_JER_Up',
	  'njets_JER_Up'
	],
	'nbtags' : [
	  'nbtags_JER_Up',
	  'nbtags_JER_Up'
	],
	'MET' : [
	  'MET_JER_Up',
	  'MET_JER_Up'
	],
    },
    'variablesDo' : {
	'fitted_dijet_mass' : [
          'fitted_dijet_mass_JER_Do',
	  'fitted_dijet_m_JER_Do'
	],
	'fitter_status' : [
	  'fitter_status_JER_Do',
	  'fitter_status_JER_Do'
	],
	'1st_leading_jet_pt' : [
	  '1st_leading_jet_pt_JER_Do',
	  'selected_jet_pt_JER_Do[0]'
	],
	'2nd_leading_jet_pt' : [
	  '2nd_leading_jet_pt_JER_Do',
	  'selected_jet_pt_JER_Do[1]'
        ],
	'3rd_leading_jet_pt' : [
	  '3rd_leading_jet_pt_JER_Do',
	  'selected_jet_pt_JER_Do[2]'
        ],
	'4th_leading_jet_pt' : [
	  '4th_leading_jet_pt_JER_Do',
	  'selected_jet_pt_JER_Do[3]',
        ],
	'njets' : [
	  'njets_JER_Do',
	  'njets_JER_Do'
	],
	'nbtags' : [
	  'nbtags_JER_Do',
	  'nbtags_JER_Do'
	],
	'MET' : [
	  'MET_JER_Do',
	  'MET_JER_Do'
	],
    },
}

'''
nuisances['top_mass'] = {
    'name' : 'top_mass',
    'kind' : 'sampleChange',
    'type' : 'shape',
    'samples' : {
      'TTLJ_powheg'	: ['1.','1.'],
      'TTLL_powheg'	: ['1.','1.'],
      'TTJJ_powheg'	: ['1.','1.'],
    },
    'samplesUp' : {
      'TTLJ_powheg'	: 'TTLJ_powheg_mass_Up',
      'TTLL_powheg'	: 'TTLL_powheg_mass_Up',
      'TTJJ_powheg'    : 'TTJJ_powheg' #TODO add TTJJ_powheg_mass_Up sample later
    },
    'samplesDo' : {
      'TTLJ_powheg'	: 'TTLJ_powheg', #TODO will add this sample
      'TTLL_powheg'	: 'TTLL_powheg_mass_Do',
      'TTJJ_powheg'	: 'TTJJ_powheg_mass_Do',
    },
}

nuisances['TuneCP5'] = {
    'name' : 'TuneCP5',
    'kind' : 'sampleChange',
    'type' : 'shape',
    'samples' : {
      'TTLJ_powheg'	: ['1.','1.'],
      'TTLL_powheg'	: ['1.','1.'],
      'TTJJ_powheg'	: ['1.','1.'],
    },
    'samplesUp' : {
      'TTLJ_powheg'	: 'TTLJ_powheg_Up',
      'TTLL_powheg'	: 'TTLL_powheg_Up',
      'TTJJ_powheg'	: 'TTJJ_powheg_Up',
    },
    'samplesDo' : {
      'TTLJ_powheg'	: 'TTLJ_powheg_Do',
      'TTLL_powheg'	: 'TTLL_powheg_Do',
      'TTJJ_powheg'	: 'TTJJ_powheg_Do',
    },
}

nuisances['hdamp'] = {
    'name' : 'hdamp',
    'kind' : 'sampleChange',
    'type' : 'shape',
    'samples' : {
      'TTLJ_powheg'	: ['1.','1.'],
      'TTLL_powheg'	: ['1.','1.'],
      'TTJJ_powheg'	: ['1.','1.'],
    },
    'samplesUp'   : { 
      'TTLJ_powheg'	: 'TTLJ_powheg_hdamp_Up',
      'TTLL_powheg'	: 'TTLL_powheg_hdamp_Up',
      'TTJJ_powheg'	: 'TTJJ_powheg_hdamp_Up',
    },
    'samplesDo'   : {
      'TTLJ_powheg'	: 'TTLJ_powheg_hdamp_Do',
      'TTLL_powheg'	: 'TTLL_powheg_hdamp_Do',
      'TTJJ_powheg'	: 'TTJJ_powheg_hdamp_Do',
    },
}

nuisances['generator'] = {
    'name' : 'generator',
    'kind' : 'sampleChange',
    'type' : 'shape',
    'samples' : {
      'TTLJ_powheg'	: ['1.','1.'],
      'TTLL_powheg'	: ['0.','1.'],
      'TTJJ_powheg'	: ['0.','1.'],
    },
    'samplesUp'   : {
      'TTLJ_powheg'	: 'TT_MG',
      'TTLL_powheg'	: 'zeros',
      'TTJJ_powheg'	: 'zeros',
    },
    'samplesDo' : {
      'TTLJ_powheg'	: 'TTLJ_powheg',
      'TTLL_powheg'	: 'TTLL_powheg',
      'TTJJ_powheg'	: 'TTJJ_powheg',
    },
    #TODO will add signal samples
}
'''

'''
nuisances['PUweight'] = {
    'name' :'PUweight',
    'kind' : 'weight',
    'type' : 'shape',
    'samples' : {
      'DYJet'                 : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'DYJets10to50_MG'       : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'WJets_MG'              : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'TTLJ_powheg'	      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'TTLL_powheg'	      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'TTJJ_powheg'	      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_sch_Lep'     : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tch_top_Incl'     : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tch_antitop_Incl' : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tW_top_Incl'      : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'SingleTop_tW_antitop_Incl'  : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'WW_pythia'             : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'WZ_pythia'             : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ZZ_pythia'             : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ttW'                   : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ttZ'                   : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ttH_bb'                : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],
      'ttbb'                  : ['PUweight_Up/PUweight', 'PUweight_Do/PUweight'],

    }
}
'''

nuisances['IdSF'] = {
    'name' : 'IdSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets_MG'	              : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'DYJets10to50_MG'       : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'WJets_MG'              : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'TTLJ_powheg'	      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'TTLL_powheg'	      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'TTJJ_powheg'	      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_sch_Lep'         : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tch_top_Incl'     : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tch_antitop_Incl' : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tW_top_Incl'      : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'SingleTop_tW_antitop_Incl'  : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'WW_pythia'             : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'WZ_pythia'             : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ZZ_pythia'             : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ttW'                   : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ttZ'                   : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ttH_bb'                : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
      'ttbb'                  : ['IdSF_Up/IdSF', 'IdSF_Do/IdSF'],
    }
}

nuisances['IsoSF'] = {
    'name' : 'IsoSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets_MG'	              : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'DYJets10to50_MG'       : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'WJets_MG'              : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'TTLJ_powheg'	      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'TTLL_powheg'	      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'TTJJ_powheg'	      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_sch_Lep'     : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tch_top_Incl'     : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tch_antitop_Incl' : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tW_top_Incl'      : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'SingleTop_tW_antitop_Incl'  : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'WW_pythia'             : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'WZ_pythia'             : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ZZ_pythia'             : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ttW'                   : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ttZ'                   : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ttH_bb'                : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
      'ttbb'                  : ['IsoSF_Up/IsoSF', 'IsoSF_Do/IsoSF'],
    }
}

nuisances['recoSF'] = {
    'name' : 'recoSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets_MG'	              : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'DYJets10to50_MG'       : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'WJets_MG'              : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'TTLJ_powheg'	      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'TTLL_powheg'	      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'TTJJ_powheg'	      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_sch_Lep'     : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tch_top_Incl'     : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tch_antitop_Incl' : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tW_top_Incl'      : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'SingleTop_tW_antitop_Incl'  : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'WW_pythia'             : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'WZ_pythia'             : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ZZ_pythia'             : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ttW'                   : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ttZ'                   : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ttH_bb'                : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
      'ttbb'                  : ['recoSF_Up/recoSF', 'recoSF_Do/recoSF'],
    }
}

nuisances['trgSF'] = {
    'name' : 'trgSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets_MG'	              : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'DYJets10to50_MG'       : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'WJets_MG'              : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'TTLJ_powheg'	      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'TTLL_powheg'	      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'TTJJ_powheg'	      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_sch_Lep'     : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tch_top_Incl'     : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tch_antitop_Incl' : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tW_top_Incl'      : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'SingleTop_tW_antitop_Incl'  : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'WW_pythia'             : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'WZ_pythia'             : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ZZ_pythia'             : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ttW'                   : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ttZ'                   : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ttH_bb'                : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
      'ttbb'                  : ['trgSF_Up/trgSF', 'trgSF_Do/trgSF'],
    }
}

nuisances['BTagSF'] = {
    'name' : 'BTagSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets_MG'	              : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'DYJets10to50_MG'       : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'WJets_MG'              : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'TTLJ_powheg'	      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'TTLL_powheg'	      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'TTJJ_powheg'	      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_sch_Lep'     : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tch_top_Incl'     : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tch_antitop_Incl' : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tW_top_Incl'      : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'SingleTop_tW_antitop_Incl'  : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'WW_pythia'             : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'WZ_pythia'             : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ZZ_pythia'             : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ttW'                   : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ttZ'                   : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ttH_bb'                : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
      'ttbb'                  : ['BTagSF_Up/BTagSF', 'BTagSF_Do/BTagSF'],
    }
}

MisTagSF_Up='(n_bjet_deepcsv_m_noSF==2)*MisTagSF_Up/MisTagSF+(n_bjet_deepcsv_m_noSF>=3)'
MisTagSF_Do='(n_bjet_deepcsv_m_noSF==2)*MisTagSF_Do/MisTagSF+(n_bjet_deepcsv_m_noSF>=3)'
nuisances['MisTagSF'] = {
    'name' : 'MisTagSF',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples' : {
      'DYJets_MG'	               : [MisTagSF_Up, MisTagSF_Do],
      'DYJets10to50_MG'       : [MisTagSF_Up, MisTagSF_Do],
      'WJets_MG'              : [MisTagSF_Up, MisTagSF_Do],
      'TTLJ_powheg'	       : [MisTagSF_Up, MisTagSF_Do],
      'TTLL_powheg'	       : [MisTagSF_Up, MisTagSF_Do],
      'TTJJ_powheg'	       : [MisTagSF_Up, MisTagSF_Do],
      'SingleTop_sch_Lep'     : [MisTagSF_Up, MisTagSF_Do],
      'SingleTop_tch_top_Incl'     : [MisTagSF_Up, MisTagSF_Do],
      'SingleTop_tch_antitop_Incl' : [MisTagSF_Up, MisTagSF_Do],
      'SingleTop_tW_top_Incl'      : [MisTagSF_Up, MisTagSF_Do],
      'SingleTop_tW_antitop_Incl'  : [MisTagSF_Up, MisTagSF_Do],
      'WW_pythia'             : [MisTagSF_Up, MisTagSF_Do],
      'WZ_pythia'             : [MisTagSF_Up, MisTagSF_Do],
      'ZZ_pythia'             : [MisTagSF_Up, MisTagSF_Do],
      'ttW'                   : [MisTagSF_Up, MisTagSF_Do],
      'ttZ'                   : [MisTagSF_Up, MisTagSF_Do],
      'ttH_bb'                : [MisTagSF_Up, MisTagSF_Do],
      'ttbb'                  : [MisTagSF_Up, MisTagSF_Do],
    }
}

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
nuisances['ttbbxsec'] = {
    'name' : 'ttbbxsec',
    'kind'	: 'weight', 
    'type'	: 'shape',
    'samples'   : {
      'ttbb'	: ['2.05', '-0.05'],
      }
}
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

nuisances['gentoppt_reweight'] = {
    'name' : 'gentoppt_reweight',
    'kind'	: 'weight', # Down is the same as nominal
    'type'	: 'shape',
    'samples' : {
      'TTLJ_powheg'	: ['1/TopPtReweight' , '1.'],
      'TTLL_powheg'	: ['1/TopPtReweight' , '1.'],
      'TTJJ_powheg'	: ['1/TopPtReweight' , '1.'],
      }
}


## other systematics(JEC/JER/top_mass/MEtoPS/generator) are not defined as event-by-event weight

########## Efficiency and Energy Scale
#trg_syst = ['trgSF_Q_Up/trgSF_Q', 'trgSF_Q_Do/trgSF_Q']
#id_syst  = ['IdSF_Q_Up/IdSF_Q', 'IdSF_Q_Do/IdSF_Q']
#alphaS_syst  = ['PDFWeights_AlphaS[0]', 'PDFWeights_AlphaS[1]']
#id_syst_ele = ['LepSF'+Nlep+'l_ele_'+eleWP+'_Up', 'LepSF'+Nlep+'l_ele_'+eleWP+'_Do']

#nuisances['trigg'] = {
#    'name'	: 'trg_2017',
#    'kind'	: 'weight',
#    'type'	: 'shape',
#    'samples'	: {
#      	'DYJets_MG'	: trg_syst ,
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
#      	'DYJets_MG'	: id_syst ,
#	'TTLL_powheg'	: id_syst ,
#	'WJets_MG'	: id_syst ,
#	'WW_pythia'	: id_syst ,
#	'WZ_pythia'	: id_syst ,
#	'ZZ_pythia'	: id_syst ,
#	},
#}
'''
nuisances['alphaS'] = {
    'name'	: 'alphaS',
    'kind'	: 'weight',
    'type'	: 'shape',
    'samples'	: {
      	'DYJets_MG'	: alphaS_syst ,
	'TTLL_powheg'	: alphaS_syst ,
	'WJets_MG'	: alphaS_syst ,
	#'WW_pythia'	: alphaS_syst ,
	#'WZ_pythia'	: alphaS_syst ,
	#'ZZ_pythia'	: alphaS_syst ,
	},
}
'''

