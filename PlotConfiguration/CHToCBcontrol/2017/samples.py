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
  qcd_weight+="*passAntiIso'"
  for key in sample_list.keys():
    sample_list[key+'_QCD'] = { #TODO: define duplicated sample in CommonPyTools
        'weight': qcd_weight, # 1 for data, negative weight for MC
        }
}

samples['DYJets'] = {
    'weight' :McWeight+"*passTightIso",
    }

samples['DYJets10to50_MG'] = {
    'weight' :McWeight+"*passTightIso",
    }


samples['TTLL_powheg'] = {
    'weight' :McWeight+"*passTightIso",
    }


samples['WJets_MG'] = {
    'weight' :McWeight+"*passTightIso",
    }

samples['WW_pythia'] = {
    'weight' :McWeight+"*passTightIso",
    }

samples['WZ_pythia'] = {
    'weight' :McWeight+"*passTightIso",
    }

samples['ZZ_pythia'] = {
    'weight' :McWeight+"*passTightIso",
    }

samples['SingleElectron'] = {
    'weight' :'1',
    }

samples['SingleMuon'] = {
    'weight' :'1',
    }

Add_QCD_Samples(samples)
