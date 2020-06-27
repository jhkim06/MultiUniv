from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

# for FSR unfold closure test input
#variables['hist_ptll'] = {
#
#    'unfoldBinType': ISRUnfold.PtGen2DHist,
#    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
#    'fold':   0,
#    'range':  None,
#    'name':  'Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
#    'xaxis': 'Mass p_{T} [GeV]',
#    'yaxis': 'Events',
#    'useTUnfoldBin': True,
#    'unfoldBinDefinition': "muon",
#    'go1D': True
#}
#
#variables['hist_mll'] = {
#
#    'unfoldBinType': ISRUnfold.MassGen2DHist,
#    'fold':   0,
#    'range':  None,
#    'name':  'Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
#    'xaxis': 'Mass [GeV]',
#    'yaxis': 'Events',
#    'useTUnfoldBin': True,
#    'unfoldBinDefinition': "muon",
#    'go1D': False
#}

variables['Pt_ResMatrix_Dressed_DRp1_Dressed_DR4PI_CoarseCoarse'] = {

    'unfoldBinType': ISRUnfold.PtFSRMigrationM,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold': 0,
    'range': None,
    'name': 'Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal):Get2DPtGenBinIndex(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
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
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Pt_ResMatrix_Dressed_DRp1_Dressed_DR4PI_FineFine'] = {

    'unfoldBinType': ISRUnfold.PtFSRMigrationM,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold': 0,
    'range': None,
    'name': 'Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal):Get2DPtGenBinIndex(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineFine"),
    'go1D': False,
    'isResMatrix':True
}

variables['Mass_ResMatrix_Dressed_DRp1_Dressed_DR4PI_FineFine'] = {

    'unfoldBinType': ISRUnfold.MassFSRMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal):Get2DMassGenBinIndex(dilep_mass_FSRgamma_gen_ispromptfinal, dilep_pt_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Post FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineFine"),
    'go1D': False,
    'isResMatrix':True
}

variables['PtGen_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.PtGen2DHist,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineCoarse"),
    'go1D': True
}

variables['MassGen_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.MassGen2DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineCoarse"),
    'go1D': False
}
