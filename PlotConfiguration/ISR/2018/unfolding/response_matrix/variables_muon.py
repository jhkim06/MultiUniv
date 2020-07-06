from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title
# for closure test

variables['Pt'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist,
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0,
    'range':  None,
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal)',
    'xaxis': 'Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
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
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
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
    'unfoldBinDefinition': ("muon","FineCoarse"),
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
    'unfoldBinDefinition': ("muon","FineCoarse"),
    'go1D': False
}


variables['Mass_ResMatrix_Detector_Dressed_DRp1'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassRecBinIndex(dilep_mass_rec_Nominal, dilep_pt_rec_Nominal):Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Pt_ResMatrix_Detector_Dressed_DRp1'] = {

    'unfoldBinType': ISRUnfold.PtMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal):Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Mass_ResMatrix_Detector_Dressed_DR4PI'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassRecBinIndex(dilep_mass_rec_Nominal, dilep_pt_rec_Nominal):Get2DMassGenBinIndex(dilep_mass_FSRgamma_gen_ispromptfinal, dilep_pt_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Pt_ResMatrix_Detector_Dressed_DR4PI'] = {

    'unfoldBinType': ISRUnfold.PtMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal):Get2DPtGenBinIndex(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","CoarseCoarse"),
    'go1D': False,
    'isResMatrix':True
}

# Different bin definitions
variables['Mass_ResMatrix_Detector_Dressed_DRp1_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassRecBinIndex(dilep_mass_rec_Nominal, dilep_pt_rec_Nominal):Get2DMassGenBinIndex(dilep_mass_FSRgammaDRp1_gen_ispromptfinal, dilep_pt_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Pt_ResMatrix_Detector_Dressed_DRp1_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.PtMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal):Get2DPtGenBinIndex(dilep_pt_FSRgammaDRp1_gen_ispromptfinal, dilep_mass_FSRgammaDRp1_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Mass_ResMatrix_Detector_Dressed_DR4PI_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DMassRecBinIndex(dilep_mass_rec_Nominal, dilep_pt_rec_Nominal):Get2DMassGenBinIndex(dilep_mass_FSRgamma_gen_ispromptfinal, dilep_pt_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineCoarse"),
    'go1D': False,
    'isResMatrix':True
}

variables['Pt_ResMatrix_Detector_Dressed_DR4PI_FineCoarse'] = {

    'unfoldBinType': ISRUnfold.PtMigrationM,
    'fold': 0,
    'range': None,
    'name': 'Get2DPtRecBinIndex(dilep_pt_rec_Nominal, dilep_mass_rec_Nominal):Get2DPtGenBinIndex(dilep_pt_FSRgamma_gen_ispromptfinal, dilep_mass_FSRgamma_gen_ispromptfinal)',
    'xaxis': 'Pre FSR',
    'useTUnfoldBin': True,
    'unfoldBinDefinition': ("muon","FineCoarse"),
    'go1D': False,
    'isResMatrix':True
}

