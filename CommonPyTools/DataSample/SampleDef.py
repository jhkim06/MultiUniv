#!/usr/bin/python

import os,sys,time
from CommonPyTools.python.getEvn import *

DATaSets = ["DoubleMuon", "DoubleEG", "SingleMuon", "SingleElectron", "SinglePhoton", "EGamma"]
DATaSets_Fake = ["DoubleMuon_FakeMuMu", "DoubleEG_FakeElEl", "SingleMuon_FakeMu", "SingleElectron_FakeEl"]
def DataPeriods(Year):
  AvailableDataPeriods = []
  if Year == "2016":
    AvailableDataPeriods = ["B_ver2","C","D","E","F","G","H"]
  elif Year == "2017":
    AvailableDataPeriods = ["B","C","D","E","F"]
  elif Year == "2018":
    AvailableDataPeriods = ["A", "B","C","D"]
  else:
    print "[mkGardener.py] Wrong Year : "+Year
  
  return AvailableDataPeriods

def SampleInfoDir(Year):
  SAMPLE_DATA_DIR = SKFlat_WD+'/data/'+SKFlatV+'/'+Year+'/Sample/'
  return SAMPLE_DATA_DIR


Productions = {
    'SMP' : {
      #TODO: will modify MC definition by 'SKFlatV'
      'Run2Legacy_v3_2018' : {
        'MC' : 'CommonPyTools.DataSample.Samples_SMP_Autumn18_miniaodv3',
	'DATA' : ['DoubleEG', 'DoubleMuon', 'SingleElectron', 'SingleMuon' ],
        'SkimDir': '/data8/DATA/SMP/Run2Legacy_v3/2018/',
        },
      'Run2Legacy_v3_2017' : {
        'MC' : 'CommonPyTools.DataSample.Samples_SMP_Fall17_miniaodv2',
	'DATA' : ['DoubleEG', 'DoubleMuon', 'SingleElectron', 'SingleMuon' ],
        'SkimDir': '/data8/DATA/SMP/Run2Legacy_v3/2017/',
        },
      'Run2Legacy_v3_2016' : {
        'MC' : 'CommonPyTools.DataSample.Samples_SMP_Summer16_miniaodv3',
	'DATA' : ['DoubleEG', 'DoubleMuon', 'SingleElectron', 'SingleMuon' ],
        'SkimDir': '/data8/DATA/SMP/Run2Legacy_v3/2016/',
        },
      },
}

