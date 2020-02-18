from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

variables['hist_ptll'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist, 
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0, 
    'range':  None, 
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec, dilep_mass_rec)', 
    'xaxis': 'Mass p_{T} [GeV]', 
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': True
}

variables['hist_mll'] = {

    'unfoldBinType': ISRUnfold.MassRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec, dilep_pt_rec)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': False
}

variables['hist_ptll_lepMomUp'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist, 
    'fold':   0, 
    'range':  None, 
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_LepMomScaleUp, dilep_mass_rec_LepMomScaleUp)', 
    'xaxis': 'Mass p_{T} [GeV]', 
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': True
}

variables['hist_mll_lepMomUp'] = {

    'unfoldBinType': ISRUnfold.MassRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_LepMomScaleUp, dilep_pt_rec_LepMomScaleUp)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': False
}

variables['hist_ptll_lepMomResUp'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist, 
    'fold':   0, 
    'range':  None, 
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_LepMomResUp, dilep_mass_rec_LepMomResUp)', 
    'xaxis': 'Mass p_{T} [GeV]', 
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': True
}

variables['hist_mll_lepMomResUp'] = {

    'unfoldBinType': ISRUnfold.MassRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_LepMomResUp, dilep_pt_rec_LepMomResUp)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': False
}


variables['hist_ptll_lepMomDown'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist, 
    'fold':   0, 
    'range':  None, 
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_LepMomScaleDown, dilep_mass_rec_LepMomScaleDown)', 
    'xaxis': 'Mass p_{T} [GeV]', 
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': True
}

variables['hist_mll_lepMomDown'] = {

    'unfoldBinType': ISRUnfold.MassRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_LepMomScaleDown, dilep_pt_rec_LepMomScaleDown)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': False
}

variables['hist_ptll_lepMomResDown'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist, 
    'fold':   0, 
    'range':  None, 
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_LepMomResDown, dilep_mass_rec_LepMomResDown)', 
    'xaxis': 'Mass p_{T} [GeV]', 
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': True
}

variables['hist_mll_lepMomResDown'] = {

    'unfoldBinType': ISRUnfold.MassRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_LepMomResDown, dilep_pt_rec_LepMomResDown)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "electron",
    'go1D': False
}
