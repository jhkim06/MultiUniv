from CommonPyTools.python.CommonTools import *

#columns=['ALL'] # To read all
columns=['diLep_Ch','diLep_m','diLep_pt','nPV']

# xaxis, yaxis to set title

variables['mll'] = {
    'name': 'diLep_m',
    'range':(120,50,120),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }
variables['ZpT'] = {
    'name': 'diLep_pt',
    'range':(120,0,120),
    'xaxis': 'Z_{pt} [GeV]',
    'fold' : 0
    }
