from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['mll'] = {
    'name': 'dilep_mass_rec',
    'range':(380, 20,400),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }

variables['mll_40_60'] = {
    'name': 'dilep_mass_rec',
    'range':(20, 40, 60),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }

variables['mll_60_80'] = {
    'name': 'dilep_mass_rec',
    'range':(20, 60, 80),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }

variables['mll_80_100'] = {
    'name': 'dilep_mass_rec',
    'range':(20, 80, 100),
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

variables['ptll'] = {
    'name': 'dilep_pt_rec',
    'range':(100,0,1000),
    'xaxis': 'pt_{ll} [GeV]',
    'fold' : 0
    }

variables['ptll_100'] = {
    'name': 'dilep_pt_rec',
    'range':(100,0,100),
    'xaxis': 'pt_{ll} [GeV]',
    'fold' : 0
    }

variables['PU'] = {
    'name': 'nPV',
    'range':(50,0,50),
    'xaxis': 'Number of PU',
    'fold' : 0
    }
