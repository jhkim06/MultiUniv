from CommonPyTools.python.CommonTools import *



variables['fitted_dijet_mass'] = {
    'name': 'fitted_dijet_m',
    'range':(36,0,180),
    'xaxis': 'm_{jj} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['fitter_status'] = {
    'name': 'fitter_status',
    'range':(3,-1,2),
    'xaxis': 'fitter status',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['lepton_pt'] = { 
    'name': 'selected_lepton_pt',
    'range':(60,0,300),
    'xaxis': 'lepton p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['lepton_eta'] = { 
    'name': 'selected_lepton_eta',
    'range':(60,-2.5,2.5),
    'xaxis': 'lepton eta [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['lepton_phi'] = { 
    'name': 'selected_lepton_phi',
    'range':(60,-3.14,3.14),
    'xaxis': 'lepton phi [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['1st_leading_jet_pt'] = { 
    'name': 'selected_jet_pt[0]',
    'range':(60,0,300),
    'xaxis': '1st leading jet p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['1st_leading_jet_eta'] = { 
    'name': 'selected_jet_eta[0]',
    'range':(60,-2.4,2.4),
    'xaxis': '1st leading jet eta [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['1st_leading_jet_phi'] = { 
    'name': 'selected_jet_phi[0]',
    'range':(60,-3.14,3.14),
    'xaxis': '1st leading jet phi [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['2nd_leading_jet_pt'] = { 
    'name': 'selected_jet_pt[1]',
    'range':(60,0,300),
    'xaxis': '2nd leading jet p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['2nd_leading_jet_eta'] = { 
    'name': 'selected_jet_eta[1]',
    'range':(60,-2.4,2.4),
    'xaxis': '2nd leading jet eta [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['2nd_leading_jet_phi'] = { 
    'name': 'selected_jet_phi[1]',
    'range':(60,-3.14,3.14),
    'xaxis': '2nd leading jet phi [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['3rd_leading_jet_pt'] = { 
    'name': 'selected_jet_pt[2]',
    'range':(60,0,300),
    'xaxis': '3rd leading jet p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['3rd_leading_jet_eta'] = { 
    'name': 'selected_jet_eta[2]',
    'range':(60,-2.4,2.4),
    'xaxis': '3rd leading jet eta [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['3rd_leading_jet_phi'] = { 
    'name': 'selected_jet_phi[2]',
    'range':(60,-3.14,3.14),
    'xaxis': '3rd leading jet phi [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['4th_leading_jet_pt'] = { 
    'name': 'selected_jet_pt[3]',
    'range':(60,0,300),
    'xaxis': '4th leading jet p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }

variables['4th_leading_jet_eta'] = { 
    'name': 'selected_jet_eta[3]',
    'range':(60,-2.4,2.4),
    'xaxis': '4th leading jet eta [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['4th_leading_jet_phi'] = { 
    'name': 'selected_jet_phi[3]',
    'range':(60,-3.14,3.14),
    'xaxis': '4th leading jet phi [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }


variables['njets'] = {
    'name': 'njets',
    'range':(6,4,10),
    'xaxis': 'jet multiplicity [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }

variables['nbjets'] = {
    'name': 'n_bjet_deepcsv_m_noSF',
    'range':(3,2,5),
    'xaxis': 'b jet multiplicity [GeV]',
    'yaxis': 'Events',
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
    'name': 'MET',
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
