from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['leading pt'] = {
    'name': 'leadinglep_pt_rec',
    'range':(20,0,100),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['sub-leading pt'] = {
    'name': 'subleadinglep_pt_rec',
    'range':(20,0,100),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['leading eta'] = {
    'name': 'leadinglep_eta_rec',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading eta'] = {
    'name': 'subleadinglep_eta_rec',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['ptll-mll'] = {
    'name': 'dilep_pt_rec:dilep_mass_rec',
    #'range':(100,0,100),
    'range':([40., 60., 80., 100., 200., 350.],[0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.]),
    'xaxis': ' Mass p_{T} bin index',
    'yaxis': 'Events/ bin',
    'fold' : 0
    }

variables['mll'] = {
    'name': 'dilep_mass_rec',
    'range':(380, 20,400),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }

#variables['mllgamma_85_105'] = {
#    'name': 'dilep_photon_mass_rec',
#    'range':(20, 85, 105),
#    'xaxis': 'm_{ll#gamma} [GeV]',
#    'fold' : 0
#    }
#
#variables['dR_lep_gamma'] = {
#    'name': 'leadingphoton_lepton_dr_rec',
#    'range':(50, 0., 5.),
#    'xaxis': '#DeltaR',
#    'fold' : 0
#    }
#
#variables['leadingPhoton_Et'] = {
#    'name': 'leadingphoton_pt_rec',
#    'range':(100, 0., 100.),
#    'xaxis': '#gamma E_{T} [GeV]',
#    'fold' : 0
#    }

variables['PU'] = {
    'name': 'nPV',
    'range':(50,0,50),
    'xaxis': 'Number of PU',
    'fold' : 0
    }
