from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

variables['Pt_ResMatrix_Dressed_DRp1_Dressed_DR4PI_CoarseCoarse'] = {

    'unfoldBinType': ISRUnfold.PtFSRMigrationM,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold': 0,
    'range': None,
    'name': 'Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal):Get2DPtGenBinIndex(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron","CoarseCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Mass_ResMatrix_Dressed_DRp1_Dressed_DR4PI_CoarseCoarse'] = {

    'unfoldBinType': ISRUnfold.MassFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal):Get2DMassGenBinIndex(dilep_mass_FSRgamma_gen_ispromptfinal, dilep_pt_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron","CoarseCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['PtGen_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.PtGen2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtGenBinIndex(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron","FineCoarse"),
    'go1D': True
}

variables['MassGen_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.MassGen2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassGenBinIndex(dilep_mass_FSRgamma_gen_ispromptfinal, dilep_pt_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron","FineCoarse"),
    'go1D': False
}

variables['Pt_CoarseCoarse'] = {

    'unfoldBinType': ISRUnfold.PtGen2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron","CoarseCoarse"),
    'go1D': True
}

variables['Mass_CoarseCoarse'] = {

    'unfoldBinType': ISRUnfold.MassGen2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("electron","CoarseCoarse"),
    'go1D': False
}
