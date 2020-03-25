from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

variables['ptll_HardProcess'] = {
    'name': 'dilep_pt_gen_prefsr',
    'range':(100, 0., 100.),
    'xaxis': ' p_{T} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['mll_HardProcess'] = {
    'name': 'dilep_mass_gen_prefsr',
    'range':(5000, 0., 500.),
    'xaxis': ' m [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['ptll_mySelection'] = {
    'name': 'dilep_pt_alllepton_FSRgamma_gen_ispromptfinal',
    'range':(100, 0., 100.),
    'xaxis': ' p_{T} [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }

variables['mll_mySelection'] = {
    'name': 'dilep_mass_alllepton_FSRgamma_gen_ispromptfinal',
    'range':(5000, 0., 500.),
    'xaxis': ' m [GeV]',
    'yaxis': 'Events/ bin',
    'go1D': False,
    'fold' : 0
    }
