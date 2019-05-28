import os

from CommonPyTools.DataSample.SampleDef import *


def AddOptions (parser):
  parser.add_argument('-a', dest='Analyzer', default="")
  parser.add_argument('-i', dest='InputSampleKey', default="")
  parser.add_argument('-p', dest='DataPeriod', default="ALL")
  parser.add_argument('-l', dest='InputSampleKeyList', default="")
  parser.add_argument('-n', dest='NJobs', default=1, type=int)
  parser.add_argument('--debug', dest='debug', default=0, type=int)
  parser.add_argument('-o', dest='Outputdir', default="")
  parser.add_argument('-q', dest='Queue', default="")
  parser.add_argument('-y', dest='Year', default="2017")
  parser.add_argument('--overWrite',default=False, action='store_true')
  parser.add_argument('--pycfg', dest='pycfg', default="configuration.py")
  parser.add_argument('--sampleCfg', dest='sampleCfg', default="")
  parser.add_argument('--plotCfg', dest='plotCfg', default="")
  parser.add_argument('--variableCfg', dest='variableCfg', default="")
  parser.add_argument('--cutCfg', dest='cutCfg', default="")
  parser.add_argument('--nuisancesCfg', dest='nuisancesCfg', default="")
  parser.add_argument('--lumi', dest='lumi', default=1, type=float)

def findOptAndChange(parser, opt_name, opt_value):
  args = parser.parse_args()
  for action in parser._actions:
    if action.dest == opt_name:
      action.default = opt_value
      return True
  return False

def LoadOptDefaults(parser):
  opt = parser.parse_args()
  pycfg = opt.pycfg
  #print 'LoadOptDefaults:: pycfg',pycfg
  if os.path.exists(pycfg):
    print 'it exists',pycfg
    infile = open(pycfg,'r')
    variables = {}
    exec(infile,variables)
    infile.close()
    for opt_name, opt_value in variables.iteritems():
      if opt_name[0] == '_': continue
      #print opt_name, opt_value
      if findOptAndChange(parser, opt_name, opt_value) :
	print 'Option found and changed', opt_name, opt_value
  else:
    print 'there is no configuration file', pycfg, 'exiting....'
    exit()


def GetInputSamples(InputSampleKeys,DataPeriod,Year,Category,ProductionKey):
  Dataperiods = DataPeriods(Year)
  InputSamples = {}
  StringForHash = ""
  print 'File to import', Productions[Category][ProductionKey]['MC']
  cmd = 'from '+Productions[Category][ProductionKey]['MC'] +' import *'

  exec(cmd, globals())

  print 'CommonTools InputSampleKey', InputSampleKeys
  for key in InputSampleKeys:
    if key in DATaSets:
      if DataPeriod=="ALL":
        print key, Year,'ALL', Dataperiods
        for period in Dataperiods:
          InputSamples[key+":"+period]={'key':key}
          StringForHash += key+":"+period
      elif DataPeriod in Dataperiods:
        print key, Year, DataPeriod
        InputSamples[key+":"+DataPeriod]={'key':key}
        StringForHash += key+":"+DataPeriod
    elif key in DATaSets_Fake:
      tmp_key = key.split('_')[0]
      if DataPeriod=="ALL":
        print key, Year,'ALL', Dataperiods
        for period in Dataperiods:
          InputSamples[tmp_key+":"+period]={'key':key}
          StringForHash += tmp_key+":"+period
      elif DataPeriod in Dataperiods:
        print key, Year, DataPeriod
        InputSamples[tmp_key+":"+DataPeriod]={'key':key}
        StringForHash += tmp_key+":"+DataPeriod
    elif 'Fake' in key:
      raise RuntimeError('Fake sample %s is not defined!!'%key)
    else:
      print 'key', key
      fullName=sampleInfo[key]['name'] #full MC name defined in CommonPyTools/DataSample/Samples
      InputSamples[fullName]={'key':key}
      StringForHash += key

  return InputSamples, StringForHash


def GetOutDirBase(Category,ProductionKey, Outputdir,InSkimString,Userflags):
  ### if Outputdir is not set, go to default setting
  if Outputdir=="":
    if InSkimString == "":
      OutBase = Productions[Category][ProductionKey]['SkimDir']+'/'
    else:
      OutBase = Productions[Category][ProductionKey]['SkimDir']+'/'+InSkimString
  else:
    if Outputdir[0]!='/':
      ## Add Abosolute path for outputdir
      Outputdir = os.getcwd()+'/'+Outputdir
    OutBase = Outputdir
    if InSkimString != "":
      OutBase = OutBase+'_'+InSkimString
  
  IsFirstFlag=True
  for flag in Userflags:
    if IsFirstFlag:
      IsFirstFlag=False
      if InSkimString == "":
        OutBase += flag
      else:
        OutBase += '_'+flag
    else:
      OutBase += '_'+flag

  return OutBase

def GetOutDir(OutBase, SampleKey, DataPeriod):
  if DataPeriod != "":
    OutDir = OutBase + '/' + SampleKey + '_' + DataPeriod 
  else:
    OutDir = OutBase + '/' + SampleKey
  return OutDir
 

def IsThis( aThis ):
  if not os.path.exists(aThis):
    print aThis, 'does not exixt'
    return False
  else:
    return True
