#!/usr/bin/python
from CommonPyTools.DataSample.SampleDef import *


def GetInputSamples(InputSampleKey,DataPeriod,Year,Category,ProductionKey):
  Dataperiods = DataPeriods(Year)
  InputSamples = {}
  StringForHash = ""
  if InputSampleKey in DATaSets:
    if DataPeriod=="ALL":
      print InputSampleKey, Year,'ALL', Dataperiods
      for period in Dataperiods:
	InputSamples[InputSampleKey+":"+period]={'key':InputSampleKey}
        StringForHash += InputSampleKey+":"+period
    elif DataPeriod in Dataperiods:
      print InputSampleKey, Year, DataPeriod
      InputSamples[InputSampleKey+":"+DataPeriod]={'key':InputSampleKey}
      StringForHash += InputSampleKey+":"+DataPeriod
  else:
    print 'File to import', Productions[Category][ProductionKey]['MC']
    #importlib.import_module(Productions[Category][ProductionKey]['MC'])
    #cmd = SKFlat_WD + Productions[Category][ProductionKey]['MC']
    #cmd = 'MCsamples : '+Productions[Category][ProductionKey]['MC']
    cmd = 'from '+Productions[Category][ProductionKey]['MC'] +' import *'
    exec(cmd, globals())
    #SampleInfo = __import__(Productions[Category][ProductionKey]['MC'])
    #SampleName = getattr(SampleInfo, MCsamples)
    #print sampleInfo
    #print sampleName[InputSampleKey]['name']
    #print sampleInfo[InputSampleKey]['name']
    InputSamples[sampleInfo[InputSampleKey]['name']]={'key':InputSampleKey}
    StringForHash += InputSampleKey

  return InputSamples, StringForHash
