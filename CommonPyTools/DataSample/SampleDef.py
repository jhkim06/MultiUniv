#!/usr/bin/python

import os,sys,time
from CommonPyTools.getEvn import *

InputSample_Data = ["DoubleMuon", "DoubleEG", "SingleMuon", "SingleElectron", "SinglePhoton"]

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

def SampleDataDir(Year):
  SAMPLE_DATA_DIR = SKFlat_WD+'/data/'+SKFlatV+'/'+Year+'/Sample/'
  return SAMPLE_DATA_DIR


MCProductions = {
    'Run2Legacy_v1_SMP2017' : {
      'samples' : 'CommonPyTools.DataSample.Samples_Fall17_miniaodv2',
      'SNU_Location': '/data7/DATA/SKFlat/Run2Legacy_v1/2017/MC/'
      },
}

