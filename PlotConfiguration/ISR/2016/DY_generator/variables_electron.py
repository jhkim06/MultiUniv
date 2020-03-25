from CommonPyTools.python.CommonTools import *
import os, sys

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import * # to use enumerate for unfolding histogram type

variables['pt_mass_PromptFinal_DressedDRp1'] = {
    'name': 'dilep_pt_FSRgammaDRp1_gen_ispromptfinal:dilep_mass_FSRgammaDRp1_gen_ispromptfinal',
    'range': ([40, 60, 80, 100, 200, 350],[0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 50., 55., 60., 65., 70., 75., 80., 85., 90., 95, 100.]),
    'xaxis': 'Mass (GeV)',
    'fold' : 0,
    'go1D' : True
}

#variables['mass_LHE'] = {
#    'name': 'dilep_mass_lhe',
#    'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510, 600, 700, 830, 1000, 1500, 3000],),
#    'xaxis': 'Mass (GeV)',
#    'fold' : 0
#    }
#variables['pt_LHE'] = {
#    'name': 'dilep_pt_lhe',
#    'range': ([0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 52., 65., 85., 120., 160., 190., 220., 250., 300., 400., 500., 800., 1500.],),
#    'xaxis': 'p_{T} (GeV)',
#    'fold' : 0
#    }
#variables['mass_HardProcess'] = {
#    'name': 'dilep_mass_gen_prefsr',
#    'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510, 600, 700, 830, 1000, 1500, 3000],),
#    'xaxis': 'Mass (GeV)',
#    'fold' : 0
#    }
#variables['pt_HardProcess'] = {
#    'name': 'dilep_pt_gen_prefsr',
#    'range': ([0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 52., 65., 85., 120., 160., 190., 220., 250., 300., 400., 500., 800., 1500.],),
#    'xaxis': 'p_{T} (GeV)',
#    'fold' : 0
#    }
#variables['mass_PromptFinal'] = {
#    'name': 'dilep_mass_gen_postfsr',
#    'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510, 600, 700, 830, 1000, 1500, 3000],),
#    'xaxis': 'Mass (GeV)',
#    'fold' : 0
#    }
#variables['pt_PromptFinal'] = {
#    'name': 'dilep_pt_gen_postfsr',
#    'range': ([0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 52., 65., 85., 120., 160., 190., 220., 250., 300., 400., 500., 800., 1500.],),
#    'xaxis': 'p_{T} (GeV)',
#    'fold' : 0
#    }
#
variables['mass_PromptFinal_DressedDRp1'] = {
    'name': 'dilep_mass_FSRgammaDRp1_gen_ispromptfinal',
    'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 350],),
    'xaxis': 'Mass (GeV)',
    'fold' : 0
    }
#variables['pt_PromptFinal_DressedDRp1'] = {
#    'name': 'dilep_pt_FSRgammaDRp1_gen_ispromptfinal',
#    'range': ([0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 52., 65., 85., 120., 160., 190., 220., 250., 300., 400., 500., 800., 1500.],),
#    'xaxis': 'p_{T} (GeV)',
#    'fold' : 0
#    }
#
#variables['mass_PromptFinal_Dressed4PI'] = {
#    'name': 'dilep_mass_FSRgamma_gen_ispromptfinal',
#    'range': ([15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510, 600, 700, 830, 1000, 1500, 3000],),
#    'xaxis': 'Mass (GeV)',
#    'fold' : 0
#    }
#variables['pt_PromptFinal_Dressed4PI'] = {
#    'name': 'dilep_pt_FSRgamma_gen_ispromptfinal',
#    'range': ([0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 52., 65., 85., 120., 160., 190., 220., 250., 300., 400., 500., 800., 1500.],),
#    'xaxis': 'p_{T} (GeV)',
#    'fold' : 0
#    }
#
#variables['photon_MotherID'] = {
#    'name': 'photon_motherID_isPromptFinalState_selected',
#    'range': (5000, -2500, 2500),
#    'xaxis': 'Particle ID',
#    'fold' : 0
#    }
#
#variables['dilepton_MotherID_myalgo'] = {
#    'name': 'dilep_motherID_myalgorithm',
#    'range': (5000, -2500, 2500),
#    'xaxis': 'Particle ID',
#    'fold' : 0
#    }
#
#variables['dilepton_MotherID_hardprocess'] = {
#    'name': 'dilep_motherID_hardprocess',
#    'range': (5000, -2500, 2500),
#    'xaxis': 'Particle ID',
#    'fold' : 0
#    }
