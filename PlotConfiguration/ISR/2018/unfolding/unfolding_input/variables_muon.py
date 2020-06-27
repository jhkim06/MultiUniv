from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['Pt'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon", "CoarseCoarse"),
    'go1D': True
}

variables['Mass'] = {

    'unfoldBinType': ISRUnfold.MassRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_Nominal, dilep_pt_rec_Nominal)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon", "CoarseCoarse"),
    'go1D': False
}

variables['Pt_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon", "FineCoarse"),
    'go1D': True
}

variables['Mass_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.MassRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_Nominal, dilep_pt_rec_Nominal)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon", "FineCoarse"),
    'go1D': False
}

variables['Mass_1D'] = {

    'fold':   0,
    'range':  ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320],),
    'name':  'dilep_mass_rec_Nominal',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
}

variables['Pt_1D'] = {

    'fold':   0,
    'range':  (100, 0, 100),
    'name':  'dilep_pt_rec_Nominal',
    'xaxis': 'Pt [GeV]',
    'yaxis': 'Events',
}

variables['Pt_1D_bin1'] = {

    'fold':   0,
    'range':  ([0., 4., 8., 12., 18., 28., 40., 55., 75., 100.],),
    'name':  'dilep_pt_rec_Nominal',
    'xaxis': 'Pt [GeV]',
    'yaxis': 'Events',
}

variables['Pt_1D_bin2'] = {

    'fold':   0,
    'range':  ([0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.],),
    'name':  'dilep_pt_rec_Nominal',
    'xaxis': 'Pt [GeV]',
    'yaxis': 'Events',
}

#variables['hist_ptll_lepMomDown'] = {
#
#    'unfoldBinType': ISRUnfold.PtRec2DHist,
#    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
#    'fold':   0,
#    'range':  None,
#    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_LepMomScaleDown, dilep_mass_rec_LepMomScaleDown)',
#    'xaxis': 'Mass p_{T} [GeV]',
#    'yaxis': 'Events',
#    'useTUnfoldBin': True,
#    'unfoldBinDefinition': "muon",
#    'go1D': True
#}
#
#variables['hist_mll_lepMomDown'] = {
#
#    'unfoldBinType': ISRUnfold.MassRec2DHist,
#    'fold':   0,
#    'range':  None,
#    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_LepMomScaleDown, dilep_pt_rec_LepMomScaleDown)',
#    'xaxis': 'Mass [GeV]',
#    'yaxis': 'Events',
#    'useTUnfoldBin': True,
#    'unfoldBinDefinition': "muon",
#    'go1D': False
#}
#
#variables['hist_ptll_lepMomUp'] = {
#
#    'unfoldBinType': ISRUnfold.PtRec2DHist,
#    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
#    'fold':   0,
#    'range':  None,
#    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_LepMomScaleUp, dilep_mass_rec_LepMomScaleUp)',
#    'xaxis': 'Mass p_{T} [GeV]',
#    'yaxis': 'Events',
#    'useTUnfoldBin': True,
#    'unfoldBinDefinition': "muon",
#    'go1D': True
#}
#
#variables['hist_mll_lepMomUp'] = {
#
#    'unfoldBinType': ISRUnfold.MassRec2DHist,
#    'fold':   0,
#    'range':  None,
#    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_LepMomScaleUp, dilep_pt_rec_LepMomScaleUp)',
#    'xaxis': 'Mass [GeV]',
#    'yaxis': 'Events',
#    'useTUnfoldBin': True,
#    'unfoldBinDefinition': "muon",
#    'go1D': False
#}
