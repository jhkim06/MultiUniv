from CommonPyTools.python.CommonTools import *

#columns=['ALL'] # To read all
columns=['passIso','passTightID','n_bjet_deepcsv_m_noSF','IsMu','IsEl','baseW',
         'PUweight','PUweight_Up','PUweight',
	 'trgSF','trgSF_Up','trgSF_Do',
	 'recoSF','recoSF_Up','recoSF_Do',
	 'IdSF','IdSF_Up','IdSF_Do',
	 'IsoSF','IsoSF_Up','IsoSF_Do',
	 'recoSF','recoSF_Up','recoSF_Do',
	 'BTagSF','BTagSF_Up','BTagSF_Do',
	 'MisTagSF','MisTagSF_Up','MisTagSF_Do',
	 'nPV',
	 'jet_pt','jet_eta','jet_phi',
	 'electron_Energy', 'electron_eta', 'electron_phi', #TODO: add electron_pt to the tree
	 'muon_pt', 'muon_eta', 'muon_phi',
	 'pfMET_Type1_pt',
         'fitted_dijet_m','best_chi2'
	]

# xaxis, yaxis to set title

variables['fitted_dijet_mass'] = {
    'name': 'fitted_dijet_m',
    'range':(36,0,180),
    'xaxis': 'm_{jj} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['leading_muon_pt'] = { #FIXME: this is a test
    'name': 'muon_pt->at(0)',
    'range':(60,0,300),
    'xaxis': 'muon p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['nPV'] = {
    'name': 'nPV',
    'range':(50,0,50),
    'xaxis': 'nPv [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['MET'] = {
    'name': 'pfMET_Type1_pt',
    'range':(60,0,300),
    'xaxis': 'MET [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['IdSF'] = {
    'name': 'IdSF',
    'range':(40,-1,2.0),
    'xaxis': 'IdSF',
    'fold' : 3
    }

variables['IsoSF'] = {
    'name': 'IsoSF',
    'range':(40,-1,2.0),
    'xaxis': 'IsoSF',
    'fold' : 3
    }

variables['recoSF'] = {
    'name': 'recoSF',
    'range':(40,-1,2.0),
    'xaxis': 'recoSF',
    'fold' : 3
    }

variables['BTagSF'] = {
    'name': 'BTagSF',
    'range':(40,-1,2.0),
    'xaxis': 'BTagSF',
    'fold' : 3
    }

variables['MisTagSF'] = {
    'name': 'MisTagSF',
    'range':(40,-1,2.0),
    'xaxis': 'MisTagSF',
    'fold' : 3
    }
