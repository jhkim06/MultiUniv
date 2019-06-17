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
