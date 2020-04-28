from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

#columns=['ALL'] # To read all
#columns=['diLep_Ch','diLep_m','diLep_pt','diLep_passSelectiveQ','IdSF_Q_Up','IdSF_Q_Do','IdSF_Q','baseW','PUweight','trgSF_Q','recoSF','IsoSF','ZPtCor','trgSF_Q_Up','trgSF_Q_Do','PDFWeights_AlphaS']

# xaxis, yaxis to set title

variables['leading pt'] = {
    'name': 'leadinglep_pt_rec',
    'range':(100,0,100),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['sub-leading pt'] = {
    'name': 'subleadinglep_pt_rec',
    'range':(100,0,100),
    'xaxis': 'p_{T} [GeV]',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['leading eta'] = {
    'name': 'leadinglep_eta_rec',
    'range':(50, -2.5, 2.5),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading eta'] = {
    'name': 'subleadinglep_eta_rec',
    'range':(50, -2.5, 2.5),
    'xaxis': '|#eta|',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['ptll-mll'] = {
    'name': 'dilep_pt_rec:dilep_mass_rec',
    #'range':(100,0,100),
    'range':([40., 60., 80., 100., 200., 350.],[0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.]),
    'xaxis': ' p_{T}^{ee} [GeV]',
    'yaxis': 'Events/ bin',
    'xlabels': {'labels': ["100", "100", "100", "100", "100"],'option': "u"},
    'go1D': True,
    'fold' : 0
    }
variables['mll'] = {
    'name': 'dilep_mass_rec',
    'range': (800, 0, 400),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }
variables['mll_m80to100'] = {
    'name': 'dilep_mass_rec',
    'range': (40, 80, 100),
    'xaxis': 'm_{ll} [GeV]',
    'fold' : 0
    }
variables['mll_variable_bin'] = {
    'name': 'dilep_mass_rec',
    'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440],),
    'xaxis': 'm_{ee} [GeV]',
    'go1D':  True,
    'fold' : 0
    }
variables['PU'] = {
    'name': 'nPV',
    'range':(50,0,50),
    'xaxis': 'Number of PU',
    'fold' : 0
    }

# ID variables

variables['leading_electron_sigmaIEtaIEta'] = {
    'name': 'electron_sigmaIEtaIEta[el1_ntuple_index]',
    'range':(40, 0, 0.04),
    'xaxis': '#sigma_{i#etai#eta}',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_electron_sigmaIEtaIEta'] = {
    'name': 'electron_sigmaIEtaIEta[el2_ntuple_index]',
    'range':(40, 0, 0.04),
    'xaxis': '#sigma_{i#etai#eta}',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['leading_electron_HoverE'] = {
    'name': 'electron_HoverE[el1_ntuple_index]',
    'range':(50, 0, 0.1),
    'xaxis': 'H/E_{SC}',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_electron_HoverE'] = {
    'name': 'electron_HoverE[el2_ntuple_index]',
    'range':(50, 0, 0.1),
    'xaxis': 'H/E_{SC}',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['leading_electron_InvEminusInvP'] = {
    'name': 'electron_InvEminusInvP[el1_ntuple_index]',
    'range':(50, 0, 0.15),
    'xaxis': '1/E-1/P',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['subleading_electron_InvEminusInvP'] = {
    'name': 'electron_InvEminusInvP[el2_ntuple_index]',
    'range':(50, 0, 0.15),
    'xaxis': '1/E-1/P',
    'yaxis': 'Events / bin',
    'fold' : 0
    }

variables['leading_electron_dEtaInSeed'] = { 
    'name': 'abs(electron_dEtaInSeed[el1_ntuple_index])',
    'range':(50, 0, 0.02),
    'xaxis': '#delta#eta_{inseed}',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }   

variables['subleading_electron_dEtaInSeed'] = { 
    'name': 'abs(electron_dEtaInSeed[el2_ntuple_index])',
    'range':(50, 0, 0.02),
    'xaxis': '#delta#eta_{inseed}',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }   

variables['leading_electron_dPhiIn'] = { 
    'name': 'abs(electron_dPhiIn[el1_ntuple_index])',
    'range':(50, 0, 0.2),
    'xaxis': '#delta#phi_{seed}',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }   

variables['subleading_electron_dPhiIn'] = { 
    'name': 'abs(electron_dPhiIn[el2_ntuple_index])',
    'range':(50, 0, 0.2),
    'xaxis': '#delta#phi_{seed}',
    'yaxis': 'Events / bin',
    'fold' : 0 
    } 

variables['leading_electron_dxyVTX'] = { 
    'name': 'electron_dxyVTX[el1_ntuple_index]',
    'range':(100, -0.1, 0.1),
    'xaxis': 'd_{xy}(VTX)',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }   

variables['subleading_electron_dxyVTX'] = { 
    'name': 'electron_dxyVTX[el2_ntuple_index]',
    'range':(100, -0.1, 0.1),
    'xaxis': 'd_{xy}(VTX)',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }  

variables['leading_electron_dzVTX'] = { 
    'name': 'electron_dzVTX[el1_ntuple_index]',
    'range':(100, -1, 1), 
    'xaxis': 'd_{z}(VTX)',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }   

variables['subleading_electron_dzVTX'] = { 
    'name': 'electron_dzVTX[el2_ntuple_index]',
    'range':(100, -1, 1),
    'xaxis': 'd_{z}(VTX)',
    'yaxis': 'Events / bin',
    'fold' : 0 
    } 

variables['leading_electron_iso_rec'] = { 
    'name': 'leadinglep_iso_rec',
    'range':(100, 0, 0.2), 
    'xaxis': 'Relative isolation',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }   

variables['subleading_electron_iso_rec'] = { 
    'name': 'subleadinglep_iso_rec',
    'range':(100, 0, 0.2), 
    'xaxis': 'Relative isolation',
    'yaxis': 'Events / bin',
    'fold' : 0 
    }  
