#!/usr/bin/env python

import os,sys,time
#import os.path
import argparse
import datetime
import random
#import importlib

from CommonPyTools.python.getEvn import *
from CommonPyTools.python.CheckJobStatus import *
from CommonPyTools.python.TimeTools import *
#sys.path.insert(0,'../../data/python')
from CommonPyTools.DataSample.SampleDef import *
from CommonPyTools.python.pythonHelper import *
from CommonPyTools.python.BatchTools import *
from CommonPyTools.python.CommonTools import *

parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="")
parser.add_argument('-i', dest='InputSampleKey', default="")
parser.add_argument('-p', dest='DataPeriod', default="ALL")
parser.add_argument('-l', dest='InputSampleKeyList', default="")
parser.add_argument('-n', dest='NJobs', default=1, type=int)
parser.add_argument('-o', dest='Outputdir', default="")
parser.add_argument('-q', dest='Queue', default="")
parser.add_argument('-y', dest='Year', default="2017")
parser.add_argument('--concLimit', dest='ConcurrencyLimit', default=-1, type=int)
parser.add_argument('--InSkim', dest='InSkim', default="")
parser.add_argument('--dry_run', action='store_true')
parser.add_argument('--multiQueue', action='store_true', default = False)
parser.add_argument('--userflags', dest='Userflags', default="")
parser.add_argument('--skimV', dest='skimV', default="0")
parser.add_argument('--nTotFiles', dest='nTotFiles', default=0, type=int)
parser.add_argument('--MonitJob', dest='MonitJob', default=False, type=bool)
parser.add_argument('--Category', dest='Category', default="SMP")
parser.add_argument('--FastSim', action='store_true')
parser.add_argument('--resubmit', action='store_true')
parser.add_argument('--OnlyGenLevel', action='store_true', default=False)
parser.add_argument('--treeDir', default='recoTree')

opt = parser.parse_args()
InSkimString = opt.InSkim
print '=================================================================='
print "Let's go for",SKFlatV,"to execute",opt.Analyzer
print '=================================================================='
InputSampleName = []
InputSampleName.append(opt.InputSampleKey)
## make flags
Userflags = []
if opt.Userflags != "":
  Userflags = (opt.Userflags).split(',')

## Add Abosolute path for outputdir
if opt.Outputdir!='':
  if opt.Outputdir[0]!='/':
    opt.Outputdir = os.getcwd()+'/'+opt.Outputdir

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
  #exit()
SendLogToWeb = True
if SKFlatLogWeb=='' or SKFlatLogWebDir=='':
  SendLogToWeb = False


## Is Skim run?
IsSKim = "Skim" in opt.Analyzer
IsHadd = "hadd" in opt.Analyzer

if IsSKim:
  print "skimskimskimskimskimskimskim"
  if IsSNU:
    print  "Skim in SNU setting !!!!!!!!!!!"
    print 'opts.NJobs',opt.NJobs
    #opt.NJobs = 999999
    #print 'opts.NJobs to be',opt.NJobs
  elif IsKISTI:
    print "Skim in Kisti"
    print 'opts.NJobs',opt.NJobs
  else:
    print "Skimming in ", HostNickName
    print 'opts.NJobs',opt.NJobs


## Machine-dependent variables
if IsKNU:
  opt.Queue = "cms"

## Make Sample List

SAMPLE_INFO_DIR = SampleInfoDir(opt.Year)
ProductionKey = SKFlatV+'_'+opt.Year
print 'Productions key:',ProductionKey

InputSamples = {}
StringForHash = ""

##############################
# Dump Input Sample list
##############################
# Dump MC infor

print 'File to import', Productions[opt.Category][ProductionKey]['MC']
cmd = 'from '+Productions[opt.Category][ProductionKey]['MC'] +' import *'
exec(cmd, globals())

## When using list
if opt.InputSampleKeyList is not "":
  lines = open(opt.InputSampleKeyList)
  for line in lines:
    if "#" in line:
      continue
    line = line.strip('\n')
    #TODO MC case put the Sample name instead of key name
    InputSamples[line]=line
    StringForHash += line
else:
  InputSamples,StringForHash = GetInputSamples(InputSampleName, opt.DataPeriod, opt.Year, opt.Category, ProductionKey)

FileRangesForEachSample = []

print 'InputSamples', InputSamples  
print 'StringForHash',StringForHash
####################################
# Get Random Number for webdir
####################################

random.seed(StringForHash)
RandomNumber = random.random()
str_RandomNumber = str(RandomNumber).replace('0.','')
webdirname = timestamp+"_"+str_RandomNumber
webdirpathbase = SKFlatRunlogDir+'/www/SKFlatAnalyzerJobLogs/'+webdirname

## If KISTI, compress files
#if IsKISTI:
#  cwd = os.getcwd()
#  os.chdir(SKFlat_WD)
#  os.system('tar --exclude=data/'+SKFlatV+'/Sample -czf '+str_RandomNumber+'_data.tar.gz data/'+SKFlatV+'/')
#  os.system('tar -czf '+str_RandomNumber+'_lib.tar.gz lib/*')
#  os.chdir(cwd)

###################################
#
# Copy Libraries
#
####################################
MasterJobDir = SKFlatRunlogDir+'/'+opt.Analyzer+'_'+'Y'+opt.Year
if InSkimString !="":
  MasterJobDir = MasterJobDir + '_'+InSkimString
for flag in Userflags:
  MasterJobDir += '_'+flag
MasterJobDir = (MasterJobDir+'_v'+opt.skimV+"/").replace('///','/').replace('//','/')

libDir = MasterJobDir+'lib/'
print 'libDir:', libDir
if opt.resubmit:
  if not os.path.isdir(libDir):
    print '%s is not exist!!'%libDir
else:
  os.system('mkdir -p ' + libDir)
  os.system('cp '+SKFlat_LIB_PATH+'/* '+libDir)

############################
## Loop over samples
############################

for InputSample in InputSamples:

  NJobs = opt.NJobs
  #print 'NJobs', NJobs

  ## Global Varialbes

  IsDATA = False
  DataPeriod = ""
  print 'InputSample', InputSample
  if ":" in InputSample:
    IsDATA = True
    DataPeriod = InputSample.split(":")[1]
    print 'DataPeriod', DataPeriod


  ## Prepare RunDir

  #base_rundir = MasterJobDir +InputSamples[InputSample]['key']
  if IsDATA:
    #base_rundir = base_rundir + '_'+DataPeriod

    base_rundir = MasterJobDir + InputSample.split(":")[0]
    base_rundir = base_rundir + '_'+InputSample.split(":")[1]
  else :
    base_rundir = MasterJobDir + InputSample
    

  base_rundir = base_rundir+"/"
  print "base_rundir: ", base_rundir
  if os.path.isdir(base_rundir):
    if not opt.resubmit:
      print 'base_rundir already exists exiting... remove or mv this directory to run again'
      exit()
  if opt.resubmit:
    print 'resubmit job in base dir : %s'%base_rundir
  else:
    os.system('mkdir -p '+base_rundir)
    os.system('mkdir -p '+base_rundir+'/output/')

  ## Set Output directory
  ### if opt.Outputdir is not set, go to default setting
  FinalOutputPath = opt.Outputdir
  if opt.Outputdir=="":
    if InSkimString == "":
      FinalOutputPath = Productions[opt.Category][ProductionKey]['SkimDir']+'/'
    else:
      FinalOutputPath = Productions[opt.Category][ProductionKey]['SkimDir']+'/'+InSkimString
    IsFirstFlag=True
    for flag in Userflags:
      if IsFirstFlag:
        IsFirstFlag=False
	if InSkimString == "":
          FinalOutputPath += flag
	else:
          FinalOutputPath += '_'+flag
      else:
        FinalOutputPath += '_'+flag
    FinalOutputPath +='_v'+opt.skimV+'/'
  if not opt.resubmit:
    os.system('mkdir -p '+FinalOutputPath)
  print 'FinalOutputPath', FinalOutputPath

  ## Copy shared library file

  #if IsKISTI:
  #  ## In KISTI, we have copy both library and data file
  #  os.system('cp '+SKFlat_WD+'/'+str_RandomNumber+'_data.tar.gz '+base_rundir+'/data.tar.gz')
  #  os.system('cp '+SKFlat_WD+'/'+str_RandomNumber+'_lib.tar.gz '+base_rundir+'/lib.tar.gz')
  #  os.system('cp '+SKFlat_WD+'/lib/CommonPyTools.tar.gz '+base_rundir)
  #  os.system('cp '+SKFlat_WD+'/lib/CommonTools.tar.gz '+base_rundir)
  #  os.system('cp '+SKFlat_WD+'/lib/Analyzers.tar.gz '+base_rundir)
  #  os.system('cp '+SKFlat_WD+'/lib/AnalyzerTools.tar.gz '+base_rundir)
  #  os.system('cp '+SKFlat_WD+'/lib/DataFormats.tar.gz '+base_rundir)

  #else:
  #  ## Else, we only have to copy libray

  ## Create webdir

  this_webdir = webdirpathbase+'/'+base_rundir.replace(SKFlatRunlogDir,'')
  os.system('mkdir -p '+this_webdir)

  ## If KNU, copy grid cert
  if IsKNU:
    os.system('cp /tmp/x509up_u'+UID+' '+base_rundir)

  ## Get Sample Path

  inputFileList = []
  if IsDATA:
    #sampleBaseName = InputSamples[InputSample]['key']+'/'+'period'+DataPeriod
    sampleBaseName = InputSample.split(":")[0] + '/'+'period'+DataPeriod
  else:
    sampleBaseName =  InputSamples[InputSample]['full_name']

  if InSkimString == "":
    if IsDATA:
      #tmpfilepath = SAMPLE_INFO_DIR+'/For'+HostNickName+'/'+InputSamples[InputSample]['key']+'_'+DataPeriod+'.txt'
      tmpfilepath = SAMPLE_INFO_DIR+'/For'+HostNickName+'/'+InputSample.split(":")[0]+'_'+DataPeriod+'.txt'
    else:
      #tmpfilepath = SAMPLE_INFO_DIR+'/For'+HostNickName+'/'+InputSamples[InputSample]['key']+'.txt'
      tmpfilepath = SAMPLE_INFO_DIR+'/For'+HostNickName+'/'+InputSample+'.txt'
    inputFileList = open(tmpfilepath).readlines()
    if not opt.resubmit:
      os.system('cp '+tmpfilepath+' '+base_rundir+'/input_filelist.txt')
    print 'Sample ROOT file list', tmpfilepath
  else:
    # Skim data list setup
    if IsDATA:
      tmpSkimDir=Productions[opt.Category][ProductionKey]['SkimDir']+'/'+InSkimString+'/'+ sampleBaseName + '/'
    else:
      tmpSkimDir=Productions[opt.Category][ProductionKey]['SkimDir']+'/'+InSkimString+'/'+ sampleBaseName + '/'
    
    print 'Input SkimDir',tmpSkimDir
    input_filelist = open(base_rundir+'/input_filelist','w')
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


  SumFileSize=0
  if 'hadd' in opt.Analyzer:
    with open(base_rundir+'/input_filelist','r') as filelist:
      for afile in filelist:
	afile = afile.rstrip('\n')
	#print afile
	SumFileSize += float(cmdline('ls -l '+afile + ' | cut -d " " -f 5'))

    NJobs =int(SumFileSize/200000000)
    if NJobs < 1: NJobs=1
    nFilePerJob = NTotalFiles/NJobs
    if nFilePerJob > 499:
      nFilePerJob = 499;
      NJobs = NTotalFiles/nFilePerJob

    print 'hadd: Sum file size:', SumFileSize, 'NJobs',NJobs, 'nFilePerJob', nFilePerJob

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
  FileRangesForEachSample.append(FileRanges)

  ## Get xsec and SumW
  this_xsec = 1.;
  this_sumw = 1.;
  if not IsDATA:
    print 'Reading x-section and sumw'
    this_xsec = sampleInfo[InputSample]['xsec']
    this_sumw = sampleInfo[InputSample]['Nsum']
    print this_xsec, this_sumw

#### Old method
#    lines_SamplePath = open(SAMPLE_INFO_DIR+'/CommonSampleInfo/'+InputSamples[InputSample]['key']+'.txt').readlines()
#    for line in lines_SamplePath:
#      if line[0]=="#":
#        continue
#      words = line.split()
#      if InputSample==words[0]:
#        this_xsec = words[2]
#        this_sumw = words[4]
#        break
#

  CheckTotalNFile=0
  cmdType = 'root'
  for it_job in range(0,len(FileRanges)):
    time.sleep(0.2)

    #print "["+str(it_job)+"th]",
    #print FileRanges[it_job],
    #print " --> "+str(len(FileRanges[it_job]))

    CheckTotalNFile = CheckTotalNFile+len(FileRanges[it_job])

    thisjob_dir = base_rundir+'/job_'+str(it_job)+'/'
    if opt.resubmit:
      if not os.path.isdir(thisjob_dir):
	print '%s is not exist!!!!!'%thisjob_dir
        exit()		    
    else:
      os.system('mkdir -p '+thisjob_dir)

    if IsDATA: 
        jobName = opt.Analyzer+'_'+InputSample.split(":")[0]
    else : 
        jobName = opt.Analyzer+'_'+InputSample

    if IsDATA:
      jobName += '_'+DataPeriod
    for flag in Userflags:
      jobName += '_'+flag
    #jobName += '_mkGardn_' + str(it_job).zfill(3)
    jobName += '_mkGardn_' + str(it_job)
    jobs = batchJobs(jobName, opt.Queue, thisjob_dir, cmdType, opt.dry_run, opt.multiQueue)

    if not IsHadd:
      IncludeLine = '''
R__LOAD_LIBRARY(libPhysics.so)
R__LOAD_LIBRARY(libTree.so)
R__LOAD_LIBRARY(libHist.so)
R__LOAD_LIBRARY(libUnfold.so)
R__LOAD_LIBRARY({1}libCommonTools.so)
R__LOAD_LIBRARY({1}libDataFormats.so)
R__LOAD_LIBRARY({1}libKinematicFitter.so)
R__LOAD_LIBRARY({1}libAnalyzerTools.so)
R__LOAD_LIBRARY({1}libAnalyzers.so)
R__LOAD_LIBRARY(/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/lhapdf/6.2.1-fmblme/lib/libLHAPDF.so)
void {0}(){{
  {2} m;
'''.format(jobName, libDir, opt.Analyzer)
      #IncludeLine = 'R__LOAD_LIBRARY({1}/{0}_C.so)'.format(opt.Analyzer, libdir)
      IncludeLine+= '  m.SetTreeName("' + opt.treeDir+'/SKFlat");\n'
      if IsDATA:
        IncludeLine+='  m.IsDATA = true;\n'
        IncludeLine+='  m.DataStream = "'+InputSample.split(":")[0]+'";\n'
	IncludeLine+='  m.DataPeriod = "'+ DataPeriod+'";\n'
      else:
        IncludeLine+='  m.MCSample = "'+InputSample+'";\n';
        IncludeLine+='  m.IsDATA = false;\n'
        if opt.OnlyGenLevel: IncludeLine+='  m.OnlyGenLevel = true;\n'
	else : IncludeLine+='  m.OnlyGenLevel = false;\n'
        IncludeLine+='  m.xsec = '+str(this_xsec)+';\n'
        IncludeLine+='  m.sumW = '+str(this_sumw)+';\n'
        if opt.FastSim:
          IncludeLine+='  m.IsFastSim = true;\n'
        else:
          IncludeLine+='  m.IsFastSim = false;\n'
      IncludeLine +='  m.DataYear = '+str(opt.Year)+';\n'

      if len(Userflags)>0:
        IncludeLine += '  m.Userflags = {\n'
        for flag in Userflags:
          IncludeLine += '    "'+flag+'",\n'
        IncludeLine += '  };\n'

      for it_file in FileRanges[it_job]:
        thisfilename = inputFileList[it_file].strip('\n')
        IncludeLine +='  m.AddFile("'+thisfilename+'");\n'

#TODO
    out_Path = ''
    if IsSKim :
      if IsSNU:
        tmp_inputFilename = inputFileList[ FileRanges[it_job][0] ].strip('\n')
	if IsDATA:
	  chunkedInputFileName = InputSample.split(":")[0]+tmp_inputFilename.split(InputSample.split(":")[0])[1]
	else:
	  chunkedInputFileName = InputSamples[InputSample]['full_name']+tmp_inputFilename.split(InputSamples[InputSample]['full_name'])[-1]
	out_Path_FileName = FinalOutputPath+'/'+chunkedInputFileName
	#print 'out_Path_FileName',out_Path_FileName
	out_FileName = out_Path_FileName.split('/')[-1]
	#print 'out_FileName',out_FileName
	out_Path          = out_Path_FileName.replace(out_FileName,'')
	#print 'out_Path',out_Path
	#fileName=InSkimString+str(it_job).zfill(3)+'root'
        os.system('mkdir -p '+ out_Path)
        IncludeLine += '  m.SetOutfilePath("'+out_Path_FileName+'");\n'
      else:
        IncludeLine += '  m.SetOutfilePath("hists.root");\n'

    elif IsHadd:
      out_Path = FinalOutputPath +'/' +sampleBaseName +'/'
      os.system('mkdir -p '+ out_Path)
      out_Path_FileName = out_Path +'/hadd_'+str(it_job)+'.root'
      exCmd = ' hadd -f '+out_Path_FileName+' '
      for it_file in FileRanges[it_job]:
        thisfilename = inputFileList[it_file].strip('\n')
        exCmd +=' '+thisfilename
	jobs.SetExCmd(exCmd)
    else:
      print "mkGardener: what kind of job is this?, exiting"
      exit()

    if not IsHadd:
      IncludeLine += '  m.Init();'+'\n'
      IncludeLine += '  m.initializeAnalyzerTools();'+'\n'
      IncludeLine += '  m.initializeAnalyzer();\n'
      IncludeLine += '  m.Loop();\n'
      IncludeLine += '  m.WriteHist();\n'
      IncludeLine += '}'

      jobs.AddRooMac(IncludeLine)

    if IsSNU or IsKISTI:
      if not opt.multiQueue: jobs.mkJds(opt.ConcurrencyLimit)

    if not opt.multiQueue: jobs.mkShCommand()
    if opt.resubmit:
      #print CheckJobStatus(base_rundir,"",it_job,"SNU",IsHadd)
      if "FINISHED" in CheckJobStatus(base_rundir,"",it_job,"SNU",IsHadd):
        print 'job finished    %s/job_%s '%(base_rundir,str(it_job))
	continue
      else:
        print 'lets resubmit!!      %s/job_%s '%(base_rundir,str(it_job))

    if not opt.multiQueue: jobs.Sub()

    # make ONE shell script and ONE submit.jds here for MULTIPLE queue case
    if opt.multiQueue and it_job == len(FileRanges)-1: 
      jobs.mkShCommand()
      jobs.mkJds(opt.ConcurrencyLimit, it_job+1)
      jobs.Sub()


    ## Write Kill Command
    KillCommand = open(base_rundir+'/Script_JobKill.sh','w')
    for it_job in range(0,len(FileRanges)):
      thisjob_dir = base_rundir+'/job_'+str(it_job)+'/'
      jobid = GetJobID(thisjob_dir, opt.Analyzer, it_job, HostNickName)
      KillCommand.write('qdel '+jobid+' ## job_'+str(it_job)+' ##\n')
    KillCommand.close()

  SubmitOutput.write('Job submitted at '+string_JobStartTime+'\n')

  if( CheckTotalNFile != NTotalFiles ):
    print "NTotalFiles is not the same to CheckTotalNFile", CheckTotalNFile, NTotalFiles
    exit()
  if( CheckTotalNFile != nfile_checksum ):
    print "NTotalFiles is not the same to nfile_checksum", CheckTotalNFile, nfile_checksum
    exit()


### remove tar.gz
#os.system('rm -f '+SKFlat_WD+'/'+str_RandomNumber+'_data.tar.gz')
#os.system('rm -f '+SKFlat_WD+'/'+str_RandomNumber+'_lib.tar.gz')



print '##################################################'
print 'Submission Finished'
print '- Analyzer = '+opt.Analyzer
print '- InSkim = '+opt.InSkim
print '- InputSamples =',
print InputSamples
print '- NJobs = '+str(NJobs)
print '- Year = '+opt.Year
print '- UserFlags =',
print Userflags, opt.skimV
if IsSNU or IsKNU:
  print '- Queue = '+opt.Queue
print '- output will be send to : '+ out_Path
print '##################################################'

if opt.dry_run:
  print "Exiting dry_run "
  exit()

if not opt.MonitJob:
  print 'No monitering job'
  print 'Bye!!!'
  exit()



print "Every process has done, bye!!!"
exit()
