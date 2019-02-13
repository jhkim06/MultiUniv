#!/usr/bin/python

import os,sys,time
sys.path.insert(0,'../../CommonTools/python')
from getEvn import *

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

