from CommonPyTools.python.CommonTools import *

#McWeight = 'evt_weight_total_gen * evt_weight_total_rec * evt_weight_recoSF_rec_NoLepMomCorr * evt_weight_idSF_rec_NoLepMomCorr * evt_weight_trigSF_rec_NoLepMomCorr * evt_weight_trigSFDZ_rec_NoLepMomCorr / evt_weight_bveto'
McWeight        = 'evt_weight_total_gen * 1. *             evt_weight_total_rec * evt_weight_recoSF_rec_NoLepMomCorr * evt_weight_idSF_rec_NoLepMomCorr * evt_weight_trigSF_rec_NoLepMomCorr * evt_weight_trigSFDZ_rec_NoLepMomCorr'
McWeightZptCorr = 'evt_weight_total_gen * zptweight_muon * evt_weight_total_rec * evt_weight_recoSF_rec_NoLepMomCorr * evt_weight_idSF_rec_NoLepMomCorr * evt_weight_trigSF_rec_NoLepMomCorr * evt_weight_trigSFDZ_rec_NoLepMomCorr'

#--------------------
# MC
#--------------------

#samples['DYJets200to400@DYJets200to400ToEE'] = {
#    'skim'   :'ISR_v1', # use default skim defined in configuration.py
#    'cut'    :'evt_tag_dielectron_hardprocess == 1 && dilep_mass_FSRgamma_gen_ispromptfinal > 200',
#    'weight' :McWeight,
#    }

samples['DYJets@DYJetsToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    #'cut'    :'evt_tag_dielectron_hardprocess == 1 && dilep_mass_FSRgamma_gen_ispromptfinal < 200',
    'cut'    :'evt_tag_dielectron_hardprocess == 1',
    'weight' :McWeightZptCorr,
    }

samples['DYJets10to50@DYJets10to50ToEE'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_dielectron_hardprocess == 1',
    'weight' :McWeightZptCorr,
    }

samples['DYJets@DYJetsToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    #'cut'    :'evt_tag_ditau_hardprocess == 1 && dilep_mass_FSRgamma_gen_ispromptfinal < 200',
    'cut'    :'evt_tag_ditau_hardprocess == 1',
    'weight' :McWeight,
    }

samples['DYJets10to50@DYJets10to50ToTauTau'] = {
    'skim'   :'ISR_v1', # use default skim defined in configuration.py
    'cut'    :'evt_tag_ditau_hardprocess == 1',
    'weight' :McWeight,
    }

#samples['SingleTop_tW_antitop_Incl'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }
#
#samples['SingleTop_tW_top_Incl'] = {
#    'skim'   :'', # use default skim defined in configuration.py
#    'cut'    :'',
#    'weight' :McWeight,
#    }

samples['TTLL_powheg'] = {
    'skim'   :'', # use default skim defined in configuration.py
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WJets_MG'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WW_pythia'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['WZ_pythia'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['ZZ_pythia'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :McWeight,
    }

samples['DoubleEG'] = {
    'skim'   :'',
    'cut'    :'',
    'weight' :'1',
    }

