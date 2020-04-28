from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title
# for closure test

variables['ptll'] = {
    'name': 'dilep_pt_gen_lepton_matched_dressed_drX[0]',
    'range':([0., 4., 8., 12., 18., 28., 40., 55., 75., 100.],),
    'xaxis': ' p_{T}^{ee} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['mll_electron'] = {
    'name': 'dilep_mass_gen_lepton_matched_dressed_drX[0]',
    'range':([50, 55, 60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350],),
    'xaxis': ' m^{ee} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['mll_muon'] = {
    'name': 'dilep_mass_gen_lepton_matched_dressed_drX[0]',
    'range':([40, 45, 50, 55, 60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350],),
    'xaxis': ' m^{ee} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['ptll_preFSR'] = {
    'name': 'dilep_pt_FSRgamma_gen_ispromptfinal',
    'range':([0., 4., 8., 12., 18., 28., 40., 55., 75., 100.],),
    'xaxis': ' p_{T}^{ee} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['mll_preFSR_electron'] = {
    'name': 'dilep_mass_FSRgamma_gen_ispromptfinal',
    'range':([50, 55, 60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350],),
    'xaxis': ' m^{ee} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['mll_preFSR_muon'] = {
    'name': 'dilep_mass_FSRgamma_gen_ispromptfinal',
    'range':([40, 45, 50, 55, 60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350],),
    'xaxis': ' m^{ee} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }
