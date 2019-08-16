from CommonPyTools.python.CommonTools import *

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['mll'] = {
    'name': 'diLep_m',
    'range':(120,60,120),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 3
    }
variables['leading_muon_pt'] = {
    'name': 'leading_pt',
    'range':(100,0,100),
    'xaxis': '#mu p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }
variables['subleading_muon_pt'] = {
    'name': 'subleading_pt',
    'range':(100,0,100),
    'xaxis': '#mu p_{T} [GeV]',
    'yaxis': 'Events / 5GeV',
    'fold' : 3
    }
#variables['ZpT'] = {
#    'name': 'diLep_pt',
#    'range':(120,0,120),
#    'xaxis': 'Z_{pt} [GeV]',
#    'fold' : 3
#    }
#
#variables['passSelectQ'] = {
#    'name': 'diLep_passSelectiveQ',
#    'range':(4,-1,3),
#    'xaxis': 'passSelectQ',
#    'fold' : 3
#    }
#
#variables['IdSF_Q_Up'] = {
#    'name': 'IdSF_Q_Up',
#    'range':(40,-1,2.0),
#    'xaxis': 'IdSF_Q_Up',
#    'fold' : 3
#    }
#
#variables['IdSF_Q_Do'] = {
#    'name': 'IdSF_Q_Do',
#    'range':(40,-1,2.0),
#    'xaxis': 'IdSF_Q_Do',
#    'fold' : 3
#    }
#
#variables['IdSF_Q'] = {
#    'name': 'IdSF_Q',
#    'range':(40,-1,2.0),
#    'xaxis': 'IdSF_Q',
#    'fold' : 3
#    }
