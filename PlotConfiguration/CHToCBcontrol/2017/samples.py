from CommonPyTools.python.CommonTools import *

###########################
# Number of Leptons and WP
###########################

Nlep='2'
eleWP='mediumSelectiveQ'

McWeight = 'baseW*PUweight*trgSF_Q*recoSF*IdSF_Q*IsoSF*ZPtCor'
#McWeight = 'baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor'

def Add_QCD_Samples(sample_list){
  qcd_weight="'"+McWeight.strip("'")
  qcd_weight+="*ABCD_weight'"
  for key in sample_list.keys():
    sample_list[key+'_QCD'] = {
        'weight': qcd_weight, # 1 for data, negative weight for MC
        'cut'    :'passAntiISO==1',
        }
}

samples['DYJets'] = {
    'weight' :McWeight,
    'cut'    :'passTightISO==1',
    }

samples['DYJets10to50_MG'] = {
    'weight' :McWeight,
    'cut'    :'passTightISO==1',
    }


samples['TTLL_powheg'] = {
    'weight' :McWeight,
    'cut'    :'passTightISO==1',
    }


samples['WJets_MG'] = {
    'weight' :McWeight,
    'cut'    :'passTightISO==1',
    }

samples['WW_pythia'] = {
    'weight' :McWeight,
    'cut'    :'passTightISO==1',
    }

samples['WZ_pythia'] = {
    'weight' :McWeight,
    'cut'    :'passTightISO==1',
    }

samples['ZZ_pythia'] = {
    'weight' :McWeight,
    'cut'    :'passTightISO==1',
    }

samples['SingleElectron'] = {
    'weight' :'1',
    'cut'    :'passTightISO==1',
    }

samples['SingleMuon'] = {
    'weight' :'1',
    'cut'    :'passTightISO==1',
    }

Add_QCD_Samples(samples)
