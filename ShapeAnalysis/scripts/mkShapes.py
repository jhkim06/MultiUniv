#!/usr/bin/env python

import os,sys,time
#import os.path
import argparse
import datetime
import random
import subprocess
import ROOT
import logging
from collections import OrderedDict
#import importlib

from CommonPyTools.python.getEvn import *
from CommonPyTools.python.CheckJobStatus import *
from CommonPyTools.python.TimeTools import *
#sys.path.insert(0,'../../data/python')
from CommonPyTools.DataSample.SampleDef import *
from CommonPyTools.python.pythonHelper import *
from CommonPyTools.python.BatchTools import *
import CommonPyTools.python.CommonTools as Tools
from ShapeAnalysis.python.ShapeFactory import ShapeFactory

parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('--InSkim', dest='InSkim', default="")
parser.add_argument('--dry_run', action='store_true')
parser.add_argument('--doBatch', action='store_true')
parser.add_argument('--doHadd', action='store_true')
parser.add_argument('--userflags', dest='Userflags', default="test")
parser.add_argument('--skimV', dest='skimV', default="0")
parser.add_argument('--nTotFiles', dest='nTotFiles', default=0, type=int)
parser.add_argument('--MonitJob', dest='MonitJob', default=False, type=bool)
parser.add_argument('--Category', dest='Category', default="SMP")
parser.add_argument('--treeName', dest='treeName', default="")
parser.add_argument('--cleanUp', dest='cleanUp', action='store_true')

ROOT.gROOT.SetBatch()

Tools.AddOptions(parser)
Tools.LoadOptDefaults(parser)
opt = parser.parse_args()
print '=================================================================='
print "Let's go for",SKFlatV,"to make histograms of", opt.InputSampleKey
print '=================================================================='
##########################
# Dump configurations
##########################

sys.path.append(os.getcwd())

variables = {}
columns = []
if opt.variableCfg != '':
  if os.path.exists(opt.variableCfg):
    handle = open(opt.variableCfg,'r')
    exec(handle)
    #exec(handle,globals())
    handle.close()
  else:
    print 'You should have variable configuration file,  exiting...'
    exit()
else:
  print 'You should have variable configuration file,  exiting...'
  exit()

supercut = '1'
cuts = {}
if opt.cutCfg != '':
  if os.path.exists(opt.cutCfg):
    handle = open(opt.cutCfg,'r')
    exec(handle)
    handle.close()
  else:
    print 'You should have cut configuration file,  exiting...'
    exit()
else:
  print 'You should have cut configuration file,  exiting...'
  exit()

samples = OrderedDict()
#print 'sample cfg',opt.sampleCfg
if opt.sampleCfg != '':
  if os.path.exists(opt.sampleCfg):
    handle = open(opt.sampleCfg,'r')
    exec(handle)
    handle.close()
  else:
    print 'You should have sample configuration file,  exiting...'
    exit()
else:
  print 'You should have sample configuration file,  exiting...'
  exit()

# Global Variables
InSkimString = opt.InSkim
SAMPLE_INFO_DIR = SampleInfoDir(opt.Year)
ProductionKey = SKFlatV+'_'+opt.Year
## make flags
Userflags = []
if opt.Userflags != "":
  Userflags = (opt.Userflags).split(',')


## Set Output directory
OutBase = Tools.GetOutDirBase(opt.Category,ProductionKey,opt.Outputdir,InSkimString,Userflags)




######### Necessary?##############
## TimeStamp
# 1) dir/file name style
JobStartTime = datetime.datetime.now()
timestamp =  JobStartTime.strftime('%Y_%m_%d_%H%M%S')
# 2) log style
JobStartTime = datetime.datetime.now()
string_JobStartTime =  JobStartTime.strftime('%Y-%m-%d %H:%M:%S')
string_ThisTime = ""


if SKFlatLogEmail=='':
  print '[mkGardener.py] Put your email address in setup.sh'
  exit()
SendLogToWeb = True
if SKFlatLogWeb=='' or SKFlatLogWebDir=='':
  SendLogToWeb = False


## Machine-dependent variables
if IsKNU:
  opt.Queue = "cms"

## Make Sample List

InputSamples = {}
StringForHash = ""


##############################
# Dump Input Sample list
##############################
# Dump MC infor

InputSampleKeys = []
for key in samples:
  InputSampleKeys.append(key)
InputSamples,StringForHash = GetInputSamples(InputSampleKeys,opt.DataPeriod,opt.Year,opt.Category,ProductionKey)
print 'InputSamples', InputSamples  


############################
## Loop over samples
############################

if opt.doHadd:
  haddAllSample_cmd = 'hadd '+OutBase + '/'
  for flag in Userflags:
    haddAllSample_cmd += flag
  haddAllSample_cmd += '.root '



for InputSample in InputSamples:

  NJobs = opt.NJobs


  ## Global Varialbes

  IsDATA = False
  DataPeriod = ""
  print 'InputSample', InputSample
  weight = '1'
  if ":" in InputSample:
    IsDATA = True
    #tmp = InputSample
    #InputSample = tmp.split(":")[0]
    DataPeriod = InputSample.split(":")[1]
    print 'DataPeriod', DataPeriod
  else:
    weight = samples[InputSamples[InputSample]['key']]['weight']

  #print 'weight',weight


  ## Prepare RunDir
  base_rundir = SKFlatRunlogDir+'/'+opt.Analyzer+'_'+'Y'+opt.Year+'_'+InputSamples[InputSample]['key']
  if IsDATA:
    base_rundir = base_rundir + '_'+DataPeriod
  if InSkimString !="":
    base_rundir = base_rundir + '_'+InSkimString
  for flag in Userflags:
    base_rundir += '_'+flag
  print "base_rundir: ", base_rundir
  if not opt.overWrite:
    if os.path.isdir(base_rundir):
      print 'base_rundir already exists exiting... remove or mv this directory to run again'
      exit()

  os.system('mkdir -p '+base_rundir)
  os.system('mkdir -p '+base_rundir+'/output/')

  ## Prepare OutPutDir
  OutSampleDir = GetOutDir(OutBase, InputSamples[InputSample]['key'],DataPeriod)
  print 'OutSampleDir',OutSampleDir
  if opt.doHadd and opt.doBatch:
    print 'Hadd in Batch is not ready, exiting...'
    exit()
  elif opt.doHadd:
    print 'Hadd interactive mode'
    #print 'files to add',OutFullPathFile_List
    here = os.getcwd()
    os.chdir(OutSampleDir)
    if IsDATA:
      haddedSampleName = InputSamples[InputSample]['key']+'_'+DataPeriod+'.root '
      cmd = 'hadd '+ haddedSampleName + InputSamples[InputSample]['key']+'_'+DataPeriod+'_tmp_*.root'
      rm_cmd = 'rm '+InputSamples[InputSample]['key']+'_'+DataPeriod+'_tmp_*.root'
    else:
      haddedSampleName = InputSamples[InputSample]['key']+'.root '
      cmd = 'hadd '+ haddedSampleName + InputSamples[InputSample]['key']+'_tmp_*.root'
      rm_cmd = 'rm '+InputSamples[InputSample]['key']+'_tmp_*.root'

    haddAllSample_cmd += OutSampleDir+'/'+haddedSampleName

    if opt.dry_run:
      print 'cmd is',cmd
      print 'rm_cmd is',rm_cmd
    elif opt.cleanUp:
      os.system(cmd)
      time.sleep(1)
      os.system(rm_cmd)
    else:
      os.system(cmd)
    os.chdir(here)
  continue

  ############################
  # Do the hadd business here
  ############################


  os.system('mkdir -p '+ OutSampleDir)


  ## Get Sample Path

  inputFileList = []
  if IsDATA:
    sampleBaseName = InputSamples[InputSample]['key']+'/'+'period'+DataPeriod
  else:
    sampleBaseName = InputSample

  if InSkimString == "":
    if IsDATA:
      tmpfilepath = SAMPLE_INFO_DIR+'/For'+HostNickName+'/'+InputSamples[InputSample]['key']+'_'+DataPeriod+'.txt'
    else:
      tmpfilepath = SAMPLE_INFO_DIR+'/For'+HostNickName+'/'+InputSamples[InputSample]['key']+'.txt'
    inputFileList = open(tmpfilepath).readlines()
    os.system('cp '+tmpfilepath+' '+base_rundir+'/input_filelist.txt')
    print 'Sample ROOT file list', tmpfilepath
  else:
    # Skim data list setup
    if IsDATA:
      tmpSkimDir=Productions[opt.Category][ProductionKey]['SkimDir']+'/'+InSkimString+'/'+ sampleBaseName + '/'
    else:
      tmpSkimDir=Productions[opt.Category][ProductionKey]['SkimDir']+'/'+InSkimString+'/'+ sampleBaseName + '/'
    
    print 'Input SkimDir',tmpSkimDir
    input_filelist = open(base_rundir+'/input_filelist,txt','w')
    for dirName, subdirList, fileList in os.walk(tmpSkimDir):
      for aFile in fileList:
	if '.root' in aFile:
	  fileFullPathName = dirName +'/'+aFile
          inputFileList.append(fileFullPathName)
	  input_filelist.write(fileFullPathName+'\n')

    input_filelist.close()
  #print 'inputFiles',inputFileList


  if opt.nTotFiles > 0:
    NTotalFiles = opt.nTotFiles
  else:
    NTotalFiles = len(inputFileList)

  print "NTotalFiles: ", NTotalFiles

  if NJobs>NTotalFiles:
    NJobs = NTotalFiles


  #SumFileSize=0
  #if 'hadd' in opt.Analyzer:
  #  with open(base_rundir+'/input_filelist','r') as filelist:
  #    for afile in filelist:
  #      afile = afile.rstrip('\n')
  #      #print afile
  #      SumFileSize += float(cmdline('ls -l '+afile + ' | cut -d " " -f 5'))

  #  NJobs =int(SumFileSize/200000000)
  #  if NJobs < 1: NJobs=1
  #  nFilePerJob = NTotalFiles/NJobs
  #  if nFilePerJob > 499:
  #    nFilePerJob = 499;
  #    NJobs = NTotalFiles/nFilePerJob

  #  print 'hadd: Sum file size:', SumFileSize, 'NJobs',NJobs, 'nFilePerJob', nFilePerJob

  SubmitOutput = open(base_rundir+'/SubmitOutput.log','w')

  SubmitOutput.write("<SKFlat> NTotalFiles = "+str(NTotalFiles)+'\n')
  SubmitOutput.write("<SKFlat> NJobs = "+str(NJobs)+'\n')
  nfilepjob = int(NTotalFiles/NJobs)
  SubmitOutput.write("<SKFlat> --> # of files per job = "+str(nfilepjob)+'\n')
  nfilepjob_remainder = NTotalFiles-(NJobs)*(nfilepjob)
  if nfilepjob_remainder>=(NJobs):
    SubmitOutput.write('nfilepjob_remainder = '+str(nfilepjob_remainder)+'\n')
    SubmitOutput.write('while, NJobs = '+str(NJobs)+'\n')
    SubmitOutput.write('--> exit'+'\n')
    sys.exit()

  # FileRanges format: [[0,1,2],[3,4,5]]
  FileRanges = []
  temp_end_largerjob = 0
  nfile_checksum = 0
  ## First nfilepjob_remainder jobs will have (nfilepjob+1) files per job
  for it_job in range(0,nfilepjob_remainder):
    FileRanges.append(range(it_job*(nfilepjob+1),(it_job+1)*(nfilepjob+1)))
    temp_end_largerjob = (it_job+1)*(nfilepjob+1)
    nfile_checksum += len(range(it_job*(nfilepjob+1),(it_job+1)*(nfilepjob+1)))
  ## Remaining NJobs-nfilepjob_remainder jobs will have (nfilepjob) files per job
  for it_job in range(0,NJobs-nfilepjob_remainder):
    FileRanges.append(range(temp_end_largerjob+(it_job*nfilepjob),temp_end_largerjob+((it_job+1)*nfilepjob) ))
    nfile_checksum += len(range(temp_end_largerjob+(it_job*nfilepjob),temp_end_largerjob+((it_job+1)*nfilepjob) ))
  SubmitOutput.write('nfile_checksum = '+str(nfile_checksum)+'\n')
  SubmitOutput.write('NTotalFiles = '+str(NTotalFiles)+'\n')


  ## Write run script

  CheckTotalNFile=0
  #OutFullPathFile_List =[]
  for it_job in range(0,len(FileRanges)):
    time.sleep(0.3)

    #print "["+str(it_job)+"th]",
    #print FileRanges[it_job],
    #print " --> "+str(len(FileRanges[it_job]))

    CheckTotalNFile = CheckTotalNFile+len(FileRanges[it_job])

    thisjob_dir = (base_rundir+'/job_'+str(it_job)+'/').replace('///','/').replace('//','/')
    #print 'thisjob dir',thisjob_dir
    os.system('mkdir -p '+thisjob_dir)

    inFileFullNames =[]
    for it_file in FileRanges[it_job]:
      inFileFullNames.append( inputFileList[it_file].strip('\n') )

    
    if IsDATA:
      outFileName = InputSamples[InputSample]['key']+'_'+DataPeriod+'_tmp_'+str(it_job)+'.root'
    else:
      outFileName = InputSamples[InputSample]['key']+'_tmp_'+str(it_job)+'.root'

    OutFullPathFile = OutSampleDir + '/' + outFileName
    #OutFullPathFile_List.append(OutFullPathFile)


    if opt.doBatch and not opt.doHadd:
      print 'batch making histo'
      jobName = 'mkShape'+str(it_job)
      jobs = batchJobs(jobName,opt.Queue, thisjob_dir,opt.dry_run)
      jobs.AddPy2Sh()
      jobs.AddPy("from ShapeAnalysis.python.ShapeFactory import ShapeFactory\n")
      jobs.AddPy("factory = ShapeFactory()")
      jobs.AddPy('factory._treeName = '+'"'+opt.treeName+'"' )
      instructions  = ""
      instructions += "factory.makeNominals( \n"
      instructions += "		'"+InputSamples[InputSample]['key'] + "', \n"
      instructions += "		"+str(inFileFullNames) + ", \n"
      instructions += "		'"+OutFullPathFile +" ', \n"
      instructions += "		"+str(variables) + ", \n"
      instructions += "		"+str(columns) + ", \n"
      instructions += "		"+str(cuts) + ", \n"
      instructions += "		'"+supercut + "', \n"
      instructions += "		'"+weight + "' ) \n"
      jobs.AddPy(instructions)

      jobs.Sub()


      #cmd = thisjob_dir+'commands.sh'
      #if opt.dry_run:
      #  print 'command is',cmd
      #elif not opt.doBatch:
      #  print 'excuting',cmd
      #  logfile=open('mylog.log','w')
      #  process = subprocess.Popen(cmd, shell=True,stdout=logfile,stderr=logfile)
      #  process.wait()
      #  status = process.returncode
      #  #os.system('sh '+cmd)
      #else:
      #  pass
    elif not opt.doHadd:
      print 'mkShape: histo making in interactive is not ready, use dry_run in doBatch for the test, exiting'
      exit()
      pass
      #print "======== Running mkShape in interactive mode ======="
      #factory = ShapeFactory()
      #factory._treeName = opt.treeName
      #factory.makeNominals(inFileFullNames,OutFullPathFile,variables, cuts,supercut, weight)

  if CheckTotalNFile != NTotalFiles:
    print 'mkShapes: CheckTotalNFile is not the same to NTotalFiles, plz check, exitting...'
    exit()

if opt.doHadd:
  print "let's collect them all"
  if opt.dry_run:
    print haddAllSample_cmd
  else:
    os.system(haddAllSample_cmd)

print 'All done, bye!!!'



