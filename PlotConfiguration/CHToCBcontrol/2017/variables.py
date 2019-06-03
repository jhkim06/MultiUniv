from CommonPyTools.python.CommonTools import *



variables['fitted_dijet_mass'] = {
    'name': 'fitted_dijet_m',
    'range':(36,0,180),
    'xaxis': 'm_{jj} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['leading_muon_pt'] = { #FIXME: this is a test
    'name': 'muon_pt[0]',
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

#variables['IdSF'] = {
#    'name': 'IdSF',
#    'range':(40,-1,2.0),
#    'xaxis': 'IdSF',
#    'fold' : 3
#    }
#
#variables['IsoSF'] = {
#    'name': 'IsoSF',
#    'range':(40,-1,2.0),
#    'xaxis': 'IsoSF',
#    'fold' : 3
#    }
#
#variables['recoSF'] = {
#    'name': 'recoSF',
#    'range':(40,-1,2.0),
#    'xaxis': 'recoSF',
#    'fold' : 3
#    }
#
#variables['BTagSF'] = {
#    'name': 'BTagSF',
#    'range':(40,-1,2.0),
#    'xaxis': 'BTagSF',
#    'fold' : 3
#    }
#
#variables['MisTagSF'] = {
#    'name': 'MisTagSF',
#    'range':(40,-1,2.0),
#    'xaxis': 'MisTagSF',
#    'fold' : 3
#    }
