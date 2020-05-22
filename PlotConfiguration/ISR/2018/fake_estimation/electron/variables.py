from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

variables['leading_pt'] = {
    'name': 'leadinglep_pt_rec_Fake',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['subleading_pt'] = {
    'name': 'subleadinglep_pt_rec_Fake',
    'range':(200, 0, 200),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['leading_eta'] = {
    'name': 'leadinglep_eta_rec_Fake',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }
variables['subleading_eta'] = {
    'name': 'subleadinglep_eta_rec_Fake',
    'range':(50, -2.4, 2.4),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['ptll'] = {
    'name': 'dilep_pt_rec_Fake',
    #'range':(100,0,100),
    'range':([0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.],),
    'xaxis': ' p_{T} bin index',
    'yaxis': 'Events/ bin',
    'go1D': True,
    'fold' : 0
    }

variables['mll'] = {
    'name': 'dilep_mass_rec_Fake',
    'range': (310, 40, 350),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }

variables['Pt'] = {                                                                                                                                                                          
                                                                                                                                                                                             
    'unfoldBinType': ISRUnfold.PtRec2DHist,                                                                                                                                                  
    'linesToAdd': (".L " + SKFlat_WD + "/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C",),                                                                                         
    'fold':   0,                                                                                                                                                                             
    'range':  None,                                                                                                                                                                          
    'name':  'Get2DPtRecBinIndex(dilep_pt_rec_Fake, dilep_mass_rec_Fake)',                                                                                                             
    'xaxis': 'Mass p_{T} [GeV]',                                                                                                                                                             
    'yaxis': 'Events',                                                                                                                                                                       
    'useTUnfoldBin': True,                                                                                                                                                                   
    'unfoldBinDefinition': "electron",                                                                                                                                                           
    'go1D': True                                                                                                                                                                             
}                                                                                                                                                                                            
                                                                                                                                                                                             
variables['Mass'] = {                                                                                                                                                                        
                                                                                                                                                                                             
    'unfoldBinType': ISRUnfold.MassRec2DHist,                                                                                                                                                
    'fold':   0,                                                                                                                                                                             
    'range':  None,                                                                                                                                                                          
    'name':  'Get2DMassRecBinIndex(dilep_mass_rec_Fake, dilep_pt_rec_Fake)',                                                                                                           
    'xaxis': 'Mass [GeV]',                                                                                                                                                                   
    'yaxis': 'Events',                                                                                                                                                                       
    'useTUnfoldBin': True,                                                                                                                                                                   
    'unfoldBinDefinition': "electron",                                                                                                                                                           
    'go1D': False                                                                                                                                                                            
}   
