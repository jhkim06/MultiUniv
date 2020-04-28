from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','rec_FakeoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['leading_pt'] = {
    'name': 'leadinglep_pt_rec_Fake',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['subleading_pt'] = {
    'name': 'subleadinglep_pt_rec_Fake',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['leading_eta'] = {
    'name': 'leadinglep_eta_rec_Fake',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_eta'] = {
    'name': 'subleadinglep_eta_rec_Fake',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['ptll_mll'] = {
    'name': 'dilep_pt_rec_Fake:dilep_mass_rec_Fake',
    #'range':(100,0,100),
    'range':([40., 60., 80., 100., 200., 350.],[0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.]),
    'xaxis': ' Mass p_{T} bin index',
    'yaxis': 'Events/ bin',
    'go1D': True,
    'fold' : 0
    }

variables['mll'] = {
    'name': 'dilep_mass_rec_Fake',
    'range': (310, 40, 350),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }

variables['mll_template'] = {
    'name': 'dilep_mass_rec_Fake',
    'range': (62, 40, 350),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }

variables['mll_variable_bin'] = {
    'name': 'dilep_mass_rec_Fake',
    'range': ([50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350],),
    'xaxis': 'm_{ll} [GeV]',
    'go1D':  True,
    'fold' : 0
    }

variables['PU'] = {
    'name': 'nPV',
    'range':(50,0,50),
    'xaxis': 'Number of PU',
    'fold' : 0
    }

