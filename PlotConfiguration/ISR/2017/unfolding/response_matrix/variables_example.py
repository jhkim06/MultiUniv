from CommonPyTools.python.CommonTools import *

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['mll'] = {
    'name': 'mRec[2]',
    'range':(120,50,120),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 3
    }

variables['mll TUnfold'] = {
    'name': 'mRec[2]',
    'range':([50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350]),
    'xaxis': 'm_{ll} [GeV]',
    'useTUnfoldBin': True, 
    'go1D': False,
    'fold' : 3
    }

variables['leading pt'] = {
    'name': 'ptRec[0]',
    'range':(40,0,200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }
variables['sub-leading pt'] = {
    'name': 'ptRec[1]',
    'range':(40,0,200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }
variables['ptll-mll'] = { 
    'name': 'ptRec[2]:mRec[2]',
    #'range':(100,0,100),
    'range':([50., 65., 80., 100., 200., 350.],[0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.]),
    'xaxis': ' Mass p_{T} [GeV]',
    'yaxis': 'Events',
    'fold' : 3
    }
