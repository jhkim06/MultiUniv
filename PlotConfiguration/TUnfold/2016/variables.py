from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['ptll-mll TUnfold'] = {

    'unfoldBinType': ISRUnfold.PtRec2DHist, 
    'linesToAdd': (".L /home/jhkim/MultiUniv/ShapeAnalysis/python/userfunc.C",),
    'fold': 3, 
    'range': None, 
    'name': 'Get2DPtRecBinIndex(ptRec[2], mRec[2])', 
    'xaxis': 'Mass p_{T} [GeV]', 
    'yaxis': 'Events',
    'useTUnfoldBin': True,
    'go1D': True
}

variables['mll TUnfold matrix'] = {

    'unfoldBinType': ISRUnfold.MassMigrationM,
    'fold': 3, 
    'range': None, 
    'name': 'Get1DMassRecBinIndex(mRec[2]):Get1DMassGenBinIndex(mPreFSR[2])', 
    'xaxis': 'm_{ll} [GeV]',
    'useTUnfoldBin': True,
    'go1D': False,
    'isResMatrix':True
}
