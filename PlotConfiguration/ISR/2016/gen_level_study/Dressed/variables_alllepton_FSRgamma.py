from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

# xaxis, yaxis to set title

variables['mass_m40to350'] = {
    'name': 'dilep_mass_alllepton_FSRgamma_gen_ispromptfinal',
    'range':(310, 40, 350),
    'xaxis': 'mass^{ll} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['ptll'] = {
    'name': 'dilep_pt_alllepton_FSRgamma_gen_ispromptfinal',
    'range':(100, 0, 100),
    'xaxis': 'p_{T}^{ll} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
