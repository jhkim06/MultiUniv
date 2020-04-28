from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['leading_pt'] = {
    'name': 'leadinglep_pt_rec',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['subleading_pt'] = {
    'name': 'subleadinglep_pt_rec',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['leading_pt_bf_roc'] = {
    'name': 'muon_pt[mu1_ntuple_index]',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['subleading_pt_bf_roc'] = {
    'name': 'muon_pt[mu2_ntuple_index]',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['leading_eta'] = {
    'name': 'leadinglep_eta_rec',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['subleading_eta'] = {
    'name': 'subleadinglep_eta_rec',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['ptll_mll'] = {
    'name': 'dilep_pt_rec:dilep_mass_rec',
    #'range':(100,0,100),
    'range':([40., 60., 80., 100., 200., 350.],[0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.]),
    'xaxis': ' p_{T}^{#mu#mu} [GeV]',
    'xlabels': {'labels': ["100", "100", "100", "100", "100"],'option': "u"},
    'yaxis': 'Events/ bin',
    'go1D': True,
    'fold' : 0
    }
variables['mll'] = {
    'name': 'dilep_mass_rec',
    'range': (800, 0, 400),
    'xaxis': 'm_{\\mu\\mu} [GeV]',
    'fold' : 0
    }
variables['mll_m80to100'] = {
    'name': 'dilep_mass_rec',
    'range': (40, 80, 100),
    'xaxis': 'm_{\\mu\\mu} [GeV]',
    'fold' : 0
    }
variables['mll_variable_bin'] = {
   'name': 'dilep_mass_rec',
   'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440],),
   'xaxis': 'm_{\\mu\\mu} [GeV]',
   'go1D':  True,
   'fold' : 0
   }
variables['PU'] = {
    'name': 'nPV',
    'range':(50,0,50),
    'xaxis': 'Number of PU',
    'fold' : 0
    }
# Muon ID variables
#
variables['leading_muon_normChi2'] = {
    'name': 'muon_normchi[mu1_ntuple_index]',
    'range':(200, 0, 50),
    'xaxis': 'Normalized global track #chi^{2}',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_muon_normChi2'] = {
    'name': 'muon_normchi[mu2_ntuple_index]',
    'range':(200, 0, 50),
    'xaxis': 'Normalized global track #chi^{2}',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
#
variables['leading_muon_d0_vtx'] = {
    'name': 'muon_dxyVTX[mu1_ntuple_index]',
    'range':(50, -0.3, 0.3),
    'xaxis': 'dxy(PV)',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_muon_d0_vtx'] = {
    'name': 'muon_dxyVTX[mu2_ntuple_index]',
    'range':(50, -0.3, 0.3),
    'xaxis': 'dxy(PV)',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
#
variables['leading_muon_dz_vtx'] = {
    'name': 'muon_dzVTX[mu1_ntuple_index]',
    'range':(50, -0.6, 0.6),
    'xaxis': 'dz(PV)',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_muon_dz_vtx'] = {
    'name': 'muon_dzVTX[mu2_ntuple_index]',
    'range':(50, -0.6, 0.6),
    'xaxis': 'dz(PV)',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
#
variables['leading_muon_valid_pixelhits'] = {
    'name': 'muon_pixelHits[mu1_ntuple_index]',
    'range':(15, 0, 15),
    'xaxis': 'Number of valid pixel hits',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_muon_valid_pixelhits'] = {
    'name': 'muon_pixelHits[mu2_ntuple_index]',
    'range':(15, 0, 15),
    'xaxis': 'Number of valid pixel hits',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
#
variables['leading_muon_trackerLayers'] = {
    'name': 'muon_trackerLayers[mu1_ntuple_index]',
    'range':(20, 0, 20),
    'xaxis': 'Number of tracker layers',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_muon_trackerLayers'] = {
    'name': 'muon_trackerLayers[mu2_ntuple_index]',
    'range':(20, 0, 20),
    'xaxis': 'Number of tracker layers',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
#
variables['leading_muon_isolation'] = {
    'name': 'leadinglep_iso_rec',
    'range':(100, 0, 0.2),
    'xaxis': 'Relative isolation',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_muon_isolation'] = {
    'name': 'subleadinglep_iso_rec',
    'range':(100, 0, 0.2),
    'xaxis': 'Relative isolation',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

#
variables['leading_muon_trkIsolation'] = {
    'name': 'muon_trkiso[mu1_ntuple_index]/leadinglep_pt_rec',
    'range':(100, 0, 0.2),
    'xaxis': 'Tracker isolation',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_muon_trkIsolation'] = {
    'name': 'muon_trkiso[mu2_ntuple_index]/subleadinglep_pt_rec',
    'range':(100, 0, 0.2),
    'xaxis': 'Tracker isolation',
    'yaxis': 'Events / bin',
    'fold' : 0
    }


