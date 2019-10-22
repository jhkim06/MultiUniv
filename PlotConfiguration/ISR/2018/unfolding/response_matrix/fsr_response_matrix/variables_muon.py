from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['hist_ptll_post_fsr'] = {

    'unfoldBinType': ISRUnfold.PtGen2DHist,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtGenBinIndex(dilep_pt_gen_postfsr, dilep_mass_gen_postfsr)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': True
}

variables['hist_mll_post_fsr'] = {

    'unfoldBinType': ISRUnfold.MassGen2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassGenBinIndex(dilep_mass_gen_postfsr, dilep_pt_gen_postfsr)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False
}

variables['hist_ptll_pre_fsr'] = {

    'unfoldBinType': ISRUnfold.PtGen2DHist,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtGenBinIndex(dilep_pt_gen_lepton_matched_dressed_drX[9], dilep_mass_gen_lepton_matched_dressed_drX[9])',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': True
}

variables['hist_mll_pre_fsr'] = {

    'unfoldBinType': ISRUnfold.MassGen2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassGenBinIndex(dilep_mass_gen_lepton_matched_dressed_drX[9], dilep_pt_gen_lepton_matched_dressed_drX[9])',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False
}

variables['mll_gen_post_fsr_pre_fsr_dRp1_response_matrix'] = {

    'unfoldBinType': ISRUnfold.MassFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassGenBinIndex(dilep_mass_gen_postfsr, dilep_pt_gen_postfsr):Get2DMassGenBinIndex(dilep_mass_gen_lepton_matched_dressed_drX[0], dilep_pt_gen_lepton_matched_dressed_drX[0])',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['ptll_gen_post_fsr_pre_fsr_dRp1_response_matrix'] = {

    'unfoldBinType': ISRUnfold.PtFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtGenBinIndex(dilep_pt_gen_postfsr, dilep_mass_gen_postfsr):Get2DPtGenBinIndex(dilep_pt_gen_lepton_matched_dressed_drX[0], dilep_mass_gen_lepton_matched_dressed_drX[0])',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}


variables['mll_gen_post_fsr_pre_fsr_response_matrix'] = {

    'unfoldBinType': ISRUnfold.MassFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassGenBinIndex(dilep_mass_gen_postfsr, dilep_pt_gen_postfsr):Get2DMassGenBinIndex(dilep_mass_gen_lepton_matched_dressed_drX[9], dilep_pt_gen_lepton_matched_dressed_drX[9])',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['ptll_gen_post_fsr_pre_fsr_response_matrix'] = {

    'unfoldBinType': ISRUnfold.PtFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtGenBinIndex(dilep_pt_gen_postfsr, dilep_mass_gen_postfsr):Get2DPtGenBinIndex(dilep_pt_gen_lepton_matched_dressed_drX[9], dilep_mass_gen_lepton_matched_dressed_drX[9])',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['ptll_gen_post_fsr_dRp1_pre_fsr_response_matrix'] = {

    'unfoldBinType': ISRUnfold.PtFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtGenBinIndex(dilep_pt_gen_lepton_matched_dressed_drX[0], dilep_mass_gen_lepton_matched_dressed_drX[0]):Get2DPtGenBinIndex(dilep_pt_gen_lepton_matched_dressed_drX[9], dilep_mass_gen_lepton_matched_dressed_drX[9])',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}

variables['mll_gen_post_fsr_dRp1_pre_fsr_response_matrix'] = {

    'unfoldBinType': ISRUnfold.MassFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassGenBinIndex(dilep_mass_gen_lepton_matched_dressed_drX[0], dilep_pt_gen_lepton_matched_dressed_drX[0]):Get2DMassGenBinIndex(dilep_mass_gen_lepton_matched_dressed_drX[9], dilep_pt_gen_lepton_matched_dressed_drX[9])',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': "muon",
    'go1D': False,
    'isResMatrix':True
}
