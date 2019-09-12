from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['hist_ptll'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist, 
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),
    'fold':   0, 
    'range':  None, 
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec, dilep_mass_rec)', 
    'xaxis': 'Mass p_{T} [GeV]', 
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'go1D': True
}

variables['hist_mll'] = {

    'unfoldBinType': ISRUnfold.MassRec1DHist,
    'fold':   0,
    'range':  None,
    'name':  'Get1DMassRecBinIndex(dilep_mass_rec)',
    'xaxis': 'Mass [GeV]',
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'go1D': False
}
