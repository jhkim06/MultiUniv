from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

variables['mll'] = {
    'name': 'dilep_mass_rec_Nominal',
    'range': (800, 0, 400),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }
variables['ptll'] = {
    'name': 'dilep_pt_rec_Nominal',
    'range': (100, 0, 100),
    'xaxis': 'pt_{ll} [GeV]',
    'fold' : 0
    }
variables['ptll_variable_bin'] = {
    'name': 'dilep_pt_rec_Nominal',
    'range': ([0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 50., 60., 72., 85., 100.],),
    'xaxis': 'pt_{ll} [GeV]',
    'fold' : 0
    }
variables['ptll_variable_wider_bin'] = {
    'name': 'dilep_pt_rec_Nominal',
    'range': ([0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.],),
    'xaxis': 'pt_{ll} [GeV]',
    'fold' : 0
    }
variables['mll_m80to100'] = {
    'name': 'dilep_mass_rec_Nominal',
    'range': (40, 80, 100),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }
variables['mll_variable_bin'] = {
    'name': 'dilep_mass_rec_Nominal',
    'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440],),
    'xaxis': 'm_{ll} [GeV]',
    'go1D':  True,
    'fold' : 0
    }
variables['ptll_mll'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron", "ZptWeight"),
    'go1D': True
}

variables['ptll_mll_analysis'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron", "FineCoarse"),
    'go1D': True
}
