from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title
# for closure test

variables['hist_ptll'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec, dilep_mass_rec)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
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
    'unfoldBinDefinition': "muon",
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
    'unfoldBinDefinition': "muon",
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
    'unfoldBinDefinition': "muon",
    'go1D': False
}

variables['mll_rec_gen_dressed_dRp1_response_matrix'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassRecBinIndex(dilep_mass_rec, dilep_pt_rec):Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['hist_ptll_lepMomDown'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_LepMomScaleDown, dilep_mass_rec_LepMomScaleDown)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
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
    'unfoldBinDefinition': "muon",
    'go1D': False
}

variables['ptll_rec_gen_dressed_dRp1_response_matrix'] = {

    'unfoldBinType': ISRUnfold.PtMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtRecBinIndex(dilep_pt_rec, dilep_mass_rec):Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['mll_rec_gen_dressed_dRp1_response_matrix_lepMomUp'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassRecBinIndex(dilep_mass_rec_LepMomScaleUp, dilep_pt_rec_LepMomScaleUp):Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['ptll_rec_gen_dressed_dRp1_response_matrix_lepMomUp'] = {

    'unfoldBinType': ISRUnfold.PtMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtRecBinIndex(dilep_pt_rec_LepMomScaleUp, dilep_mass_rec_LepMomScaleUp):Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['mll_rec_gen_dressed_dRp1_response_matrix_lepMomDown'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassRecBinIndex(dilep_mass_rec_LepMomScaleDown, dilep_pt_rec_LepMomScaleDown):Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['ptll_rec_gen_dressed_dRp1_response_matrix_lepMomDown'] = {

    'unfoldBinType': ISRUnfold.PtMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtRecBinIndex(dilep_pt_rec_LepMomScaleDown, dilep_mass_rec_LepMomScaleDown):Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}
