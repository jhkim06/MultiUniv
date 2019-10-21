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
  parser.add_argument('--samplesFile', dest='samplesFile', default="")
  parser.add_argument('--plotFile', dest='plotFile', default="")
  parser.add_argument('--variablesFile', dest='variablesFile', default="")
  parser.add_argument('--cutsFile', dest='cutsFile', default="")
  parser.add_argument('--nuisancesFile', dest='nuisancesFile', default="")
  parser.add_argument('--structureFile', dest='structureFile', default="structure.py")
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

    if len(key.split("@")) > 1 :
      base_key = key.split("@")[0] # sample key as defined in CommonPyTools/DataSample/
      key_ =     key.split("@")[1] # key to make a histogram out of existing sample as defined in CommonPyTools/DataSample/
    else :
      base_key = key
      key_ = key

    if base_key in DATaSets:
      if DataPeriod=="ALL":
        print key_, Year,'ALL', Dataperiods
        for period in Dataperiods:
          #InputSamples[key+":"+period]={'key':key}
          InputSamples[key_+":"+period]={'full_name':base_key}
          StringForHash += key_+":"+period
      elif DataPeriod in Dataperiods:
        print key_, Year, DataPeriod
        #InputSamples[key+":"+DataPeriod]={'key':key}
        InputSamples[key_+":"+DataPeriod]={'full_name':base_key}
        StringForHash += key_+":"+DataPeriod

    elif key in DATaSets_Fake:
      tmp_key = key.split('_')[0]
      if DataPeriod=="ALL":
        print key, Year,'ALL', Dataperiods
        for period in Dataperiods:
          #InputSamples[tmp_key+":"+period]={'key':key}
          InputSamples[key+":"+period]={'full_path':key}
          StringForHash += tmp_key+":"+period
      elif DataPeriod in Dataperiods:
        print key, Year, DataPeriod
        #InputSamples[tmp_key+":"+DataPeriod]={'key':key}
        InputSamples[key+":"+DataPeriod]={'full_path':key}
        StringForHash += tmp_key+":"+DataPeriod
    elif 'Fake' in key:
      raise RuntimeError('Fake sample %s is not defined!!'%key)

    else:
      print 'key', key

      fullName=sampleInfo[base_key]['name'] #full MC name defined in CommonPyTools/DataSample/Samples
      #InputSamples[fullName]={'key':key_}
      InputSamples[key_]={'full_name':fullName}
      StringForHash += key_
    
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


#####################################################
# To use import optparse
#####################################################

#---
class list_maker:
    def __init__(self, var, sep=',', type=None ):
        self._type= type
        self._var = var
        self._sep = sep

    def __call__(self,option, opt_str, value, parser):
        if not hasattr(parser.values,self._var):
               setattr(parser.values,self._var,[])

        try:
           array = value.split(self._sep)
           if self._type:
               array = [ self._type(e) for e in array ]
           setattr(parser.values, self._var, array)

        except:
           print 'Malformed option (comma separated list expected):',value


# def make_cat_list(option, opt_str, value, parser):

#     if not hasattr(parser.values,'cats'):
#         setattr(parser.values,'cats',[])

#     try:
#         cats = value.split(',')
#         parser.values.cats = cats

#     except:
#         print 'Malformed option (comma separated list expected):',value







#------------------------------------
def addOptions(parser):
    parser.add_option('--pycfg'          , dest='pycfg'       , help='configuration file (def=%default)' , default='configuration.py')
    parser.add_option('-d', '--debug'    , dest='debug'       , help='Debug level'                           , default=0      , action='count' )
    #parser.add_option('-c', '--chans'    , dest='chans'       , help='list of channels'                      , default=['0j'] , type='string' , action='callback' , callback=list_maker('chans'))
    parser.add_option('-E', '--energy'   , dest='energy'      , help='Energy (def=%default)'                 , default='13TeV' , type='string')
    parser.add_option('-l', '--lumi'     , dest='lumi'        , help='Luminosity'                            , default=None   , type='float'   )
    
    #parser.add_option('-v', '--variable' , dest='variable'    , help='variable'                              , default=None )
    #parser.add_option('-m', '--mass'     , dest='mass'        , help='run on one mass point only '           , default=hwwinfo.masses[:]      , type='string' , action='callback' , callback=list_maker('mass',',',int))

    parser.add_option('-A', '--aliasesFile',    dest='aliasesFile'      , help='optional file with TTreeFormula aliases'     , default=None )
    parser.add_option('-V', '--variablesFile' , dest='variablesFile'    , help='file with variables'                         , default=None )
    parser.add_option('-C', '--cutsFile' ,      dest='cutsFile'         , help='file with cuts'                              , default=None )
    parser.add_option('-S', '--samplesFile' ,   dest='samplesFile'      , help='file with cuts'                              , default=None )
    parser.add_option('-P', '--plotFile' ,      dest='plotFile'         , help='file with plot configurations'               , default=None )

#------------------------------------

#---
def findopt(parser,dest):
    ''' find the option with dest as destination'''
    for o in parser.option_list:
        if hasattr(o,'dest') and o.dest==dest:
            return o
    return None

#---


#---
def loadOptDefaults(parser, pycfg=None, quiet=False):
    '''
    Load the default options from the configuation file.
    The new defaults options shall be written in python, as they are interpreted
    '''

    print " loadOptDefaults::pycfg = ", pycfg

    if not pycfg:
        import sys
        import re
        try:
            # pre-parse the python cfg location
            pyexp = re.compile('--pycfg(=)+')
            j = max([i for i,a in enumerate(sys.argv) if pyexp.match(a) ])   # if more than one, only the last one is used
            dummy = [sys.argv[j]]
            try:
                dummy += [sys.argv[i+1]]
            except IndexError:
                pass

        except:
            dummy = []
        (opt,args) = parser.parse_args(dummy)

        pycfg = opt.pycfg

    #print " pycfg = ", pycfg
    
    if os.path.exists(pycfg):
        handle = open(pycfg,'r')
        vars = {}
        exec(handle,vars)
        handle.close()

        #print " vars = ", vars
        for opt_name, opt_value in vars.iteritems():
            if opt_name[0] == '-': continue

            #print " opt_name[0] = ", opt_name[0]
            #print " opt_name    = ", opt_name
            
            o = findopt(parser, opt_name)
            if o is None: continue

            o.default = opt_value
            parser.defaults[opt_name] = opt_value
            # it modifies the default values
            # if then not defined, these ones will be used
            
            if not quiet: print ' - new default value:',opt_name,'=',opt_value
        return


#---


