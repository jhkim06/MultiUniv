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
import CommonPyTools.python.CommonTools import *

parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="")
parser.add_argument('-i', dest='InputSampleKey', default="")
parser.add_argument('-p', dest='DataPeriod', default="ALL")
parser.add_argument('-l', dest='InputSampleKeyList', default="")
parser.add_argument('-n', dest='NJobs', default=1, type=int)
parser.add_argument('-o', dest='Outputdir', default="")
parser.add_argument('-q', dest='Queue', default="fastq")
parser.add_argument('-y', dest='Year', default="2017")
parser.add_argument('--InSkim', dest='InSkim', default="")
parser.add_argument('--dry_run', action='store_true')
parser.add_argument('--userflags', dest='Userflags', default="")
parser.add_argument('--skimV', dest='skimV', default="0")
parser.add_argument('--nTotFiles', dest='nTotFiles', default=0, type=int)
parser.add_argument('--MonitJob', dest='MonitJob', default=False, type=bool)
parser.add_argument('--Category', dest='Category', default="SMP")

args = parser.parse_args()
print '=================================================================='
print "Let's go for",SKFlatV,"to execute",args.Analyzer
print '=================================================================='
## make flags
Userflags = []
if args.Userflags != "":
  Userflags = (args.Userflags).split(',')

## Add Abosolute path for outputdir
if args.Outputdir!='':
  if args.Outputdir[0]!='/':
    args.Outputdir = os.getcwd()+'/'+args.Outputdir

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


## Is Skim run?
IsSKim = "Skim" in args.Analyzer
IsHadd = "hadd" in args.Analyzer


if IsSKim:
  if IsSNU:
    print  "Skim in SNU setting NJobs = 999999 !!!!!!!!!!!"
    args.NJobs = 999999
  elif IsKISTI:
    print "Skim in Kisti"
  else:
    print "Skimming in ", HostNickName, "is not prepared kkk"
    exit()



## Machine-dependent variables
if IsKNU:
  args.Queue = "cms"

## Make Sample List

SAMPLE_INFO_DIR = SampleInfoDir(args.Year)
ProductionKey = SKFlatV+'_'+args.Year
print 'Productions key:',ProductionKey

InputSamples = {}
StringForHash = ""

##############################
# Dump Input Sample list
##############################
# Dump MC infor

print 'File to import', Productions[args.Category][ProductionKey]['MC']
cmd = 'from '+Productions[args.Category][ProductionKey]['MC'] +' import *'
exec(cmd, globals())

## When using list
if args.InputSampleKeyList is not "":
  lines = open(args.InputSampleKeyList)
  for line in lines:
    if "#" in line:
      continue
    line = line.strip('\n')
    #TODO MC case put the Sample name instead of key name
    InputSamples[line]=line
    StringForHash += line
else:
  InputSamples,StringForHash = GetInputSamples(args.InputSampleKey,args.DataPeriod,args.Year,args.Category,ProductionKey)

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
if IsKISTI:
  cwd = os.getcwd()
  os.chdir(SKFlat_WD)
  os.system('tar --exclude=data/'+SKFlatV+'/Sample -czf '+str_RandomNumber+'_data.tar.gz data/'+SKFlatV+'/')
  os.system('tar -czf '+str_RandomNumber+'_lib.tar.gz lib/*')
  os.chdir(cwd)




############################
## Loop over samples
############################


for InputSample in InputSamples:

  NJobs = args.NJobs


  ## Global Varialbes

  IsDATA = False
  DataPeriod = ""
  print 'InputSample', InputSample
  if ":" in InputSample:
    IsDATA = True
    #tmp = InputSample
    #InputSample = tmp.split(":")[0]
    DataPeriod = InputSample.split(":")[1]
    print 'DataPeriod', DataPeriod

  InSkimString = args.InSkim

  ## Prepare RunDir

  base_rundir = SKFlatRunlogDir+'/'+args.Analyzer+'_'+'Y'+args.Year+'_'+InputSamples[InputSample]['key']
  if IsDATA:
    base_rundir = base_rundir + '_'+DataPeriod
  if InSkimString !="":
    base_rundir = base_rundir + '_'+InSkimString
  for flag in Userflags:
    base_rundir += '_'+flag
  base_rundir = base_rundir+'_v'+args.skimV+"/"
  print "base_rundir: ", base_rundir
  if os.path.isdir(base_rundir):
    print 'base_rundir already exists exiting... remove or mv this directory to run again'
    exit()

  os.system('mkdir -p '+base_rundir)
  os.system('mkdir -p '+base_rundir+'/output/')

  ## Set Output directory
  ### if args.Outputdir is not set, go to default setting
  FinalOutputPath = args.Outputdir
  if args.Outputdir=="":
    if InSkimString == "":
      FinalOutputPath = Productions[args.Category][ProductionKey]['SkimDir']+'/'
      #FinalOutputPath = SKFlatOutputDir+'/'+SKFlatV+'/'+args.Analyzer+'/'+args.Year+'/'
    else:
      FinalOutputPath = Productions[args.Category][ProductionKey]['SkimDir']+'/'+InSkimString
      #FinalOutputPath = SKFlatOutputDir+'/'+SKFlatV+'/'+args.Analyzer+'/'+args.Year+'/'+InSkimString
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
    #FinalOutputPath +='/'+InputSample+'/'
    FinalOutputPath +='_v'+args.skimV+'/'
  os.system('mkdir -p '+FinalOutputPath)
  print 'FinalOutputPath', FinalOutputPath




  ## Copy shared library file

  if IsKISTI:
    ## In KISTI, we have copy both library and data file
    os.system('cp '+SKFlat_WD+'/'+str_RandomNumber+'_data.tar.gz '+base_rundir+'/data.tar.gz')
    os.system('cp '+SKFlat_WD+'/'+str_RandomNumber+'_lib.tar.gz '+base_rundir+'/lib.tar.gz')
    os.system('cp '+SKFlat_WD+'/lib/CommonPyTools.tar.gz '+base_rundir)
    os.system('cp '+SKFlat_WD+'/lib/CommonTools.tar.gz '+base_rundir)
    os.system('cp '+SKFlat_WD+'/lib/Analyzers.tar.gz '+base_rundir)
    os.system('cp '+SKFlat_WD+'/lib/AnalyzerTools.tar.gz '+base_rundir)
    os.system('cp '+SKFlat_WD+'/lib/DataFormats.tar.gz '+base_rundir)

  else:
    ## Else, we only have to copy libray
    os.system('mkdir -p '+base_rundir+'/lib/')
    os.system('cp '+SKFlat_LIB_PATH+'/* '+base_rundir+'/lib')

  ## Create webdir

  this_webdir = webdirpathbase+'/'+base_rundir.replace(SKFlatRunlogDir,'')
  os.system('mkdir -p '+this_webdir)

  ## If KNU, copy grid cert
  if IsKNU:
    os.system('cp /tmp/x509up_u'+UID+' '+base_rundir)

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
      tmpSkimDir=Productions[args.Category][ProductionKey]['SkimDir']+'/'+InSkimString+'/'+ sampleBaseName + '/'
    else:
      tmpSkimDir=Productions[args.Category][ProductionKey]['SkimDir']+'/'+InSkimString+'/'+ sampleBaseName + '/'
    
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



  if args.nTotFiles > 0:
    NTotalFiles = args.nTotFiles
  else:
    NTotalFiles = len(inputFileList)

  print "NTotalFiles: ", NTotalFiles

  if NJobs>NTotalFiles:
    NJobs = NTotalFiles


  SumFileSize=0
  if 'hadd' in args.Analyzer:
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
    this_xsec = sampleInfo[InputSamples[InputSample]['key']]['xsec']
    this_sumw = sampleInfo[InputSamples[InputSample]['key']]['Nsum']
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

  ## Write run script

  if IsKISTI:

    commandsfilename = args.Analyzer+'_'+InputSamples[InputSample]['key']
    if IsDATA:
      commandsfilename += '_'+DataPeriod
    for flag in Userflags:
      commandsfilename += '_'+flag
    run_commands = open(base_rundir+'/'+commandsfilename+'.sh','w')
    print>>run_commands,'''#!/bin/bash
SECTION=`printf %03d $1`
WORKDIR=`pwd`
echo "####  Extracting CommonPyTools ####"
tar -zxvf CommonPyTools.tar.gz
echo "####  Extracting CommonTools ####"
tar -zxvf CommonTools.tar.gz
echo "#### Extracting DataFormats ####"
tar -zxvf DataFormats.tar.gz
echo "####  Extracting AnalyzerTools ####"
tar -zxvf AnalyzerTools.tar.gz
echo "####  Extracting Analyzers ####"
tar -zxvf Analyzers.tar.gz
echo "#### Extracting libraries ####"
tar -zxvf lib.tar.gz
echo "#### Extracting run files ####"
tar -zxvf runFile.tar.gz
echo "#### Extracting data files ####"
tar -zxvf data.tar.gz
echo "#### cmsenv ####"
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/src/
eval `scramv1 runtime -sh`
cd -
echo "#### setup root ####"
source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/external/slc6_amd64_gcc630/bin/thisroot.sh

export SKFlatV="{0}"
export SKFlat_WD=`pwd`
export SKFlat_LIB_PATH=$SKFlat_WD/lib/
export DATA_DIR=data/$SKFlatV
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SKFlat_WD/DataFormats/include/:$SKFlat_WD/Analyzers/include/:$SKFlat_WD/AnalyzerTools/include/:$SKFlat_WD/CommonTools/include/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKFlat_LIB_PATH

SumNoAuth=999
Trial=0

while [ "$SumNoAuth" -ne 0 ]; do

  if [ "$Trial" -gt 9999 ]; then
    break
  fi

  echo "#### running ####"
  echo "root -l -b -q run_${{SECTION}}.C"
  root -l -b -q run_${{SECTION}}.C 2> err${{SECTION}}.log
  NoAuthError_Open=`grep "Error in <TNetXNGFile::Open>" err${{SECTION}}.log -R | wc -l`
  NoAuthError_Close=`grep "Error in <TNetXNGFile::Close>" err${{SECTION}}.log -R | wc -l`

  SumNoAuth=$(($NoAuthError_Open + $NoAuthError_Close))

  if [ "$SumNoAuth" -ne 0 ]; then
    echo "SumNoAuth="$SumNoAuth
    echo "AUTH error occured.. running again in 30 seconds.."
    Trial=$((Trial+=1))
    sleep 30
  fi

done

cat err${{SECTION}}.log >&2
'''.format(SKFlatV)
    run_commands.close()

    submit_command = open(base_rundir+'/submit.jds','w')
    if IsUI10:
      print>>submit_command,'''executable = {3}.sh
universe   = vanilla
arguments  = $(Process)
requirements = OpSysMajorVer == 6
log = condor.log
getenv     = False
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
output = job_$(Process).log
error = job_$(Process).err
transfer_input_files = {0}, {1}, {4}, {5}, {6}, {7}, {8}, {9}
transfer_output_remaps = "hists.root = output/hists_$(Process).root"
queue {2}
'''.format(base_rundir+'/runFile.tar.gz', base_rundir+'/lib.tar.gz',str(NJobs), commandsfilename, base_rundir+'/data.tar.gz', base_rundir+'/Analyzers.tar.gz', base_rundir+'/AnalyzerTools.tar.gz', base_rundir+'/DataFormats.tar.gz',base_rundir+'/CommonTools.tar.gz',base_rundir+'/CommonPyTools.tar.gz')
      submit_command.close()
    if IsUI20:
      print>>submit_command,'''executable = {3}.sh
universe   = vanilla
requirements = ( HasSingularity == true )
arguments  = $(Process)
log = condor.log
getenv     = False
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
output = job_$(Process).log
error = job_$(Process).err
transfer_input_files = {0}, {1}, {4}, {5}, {6}, {7}, {8}, {9}
accounting_group=group_cms
+SingularityImage = "/cvmfs/singularity.opensciencegrid.org/opensciencegrid/osgvo-el6:latest"
+SingularityBind = "/cvmfs, /cms, /share"
transfer_output_remaps = "hists.root = output/hists_$(Process).root"
queue {2}
'''.format(base_rundir+'/runFile.tar.gz', base_rundir+'/lib.tar.gz',str(NJobs), commandsfilename, base_rundir+'/data.tar.gz', base_rundir+'/Analyzers.tar.gz', base_rundir+'/AnalyzerTools.tar.gz', base_rundir+'/DataFormats.tar.gz',base_rundir+'/CommonTools.tar.gz',base_rundir+'/CommonPyTools.tar.gz')
      submit_command.close()



  CheckTotalNFile=0
  for it_job in range(0,len(FileRanges)):
    time.sleep(0.3)

    #print "["+str(it_job)+"th]",
    #print FileRanges[it_job],
    #print " --> "+str(len(FileRanges[it_job]))

    CheckTotalNFile = CheckTotalNFile+len(FileRanges[it_job])

    thisjob_dir = base_rundir+'/job_'+str(it_job)+'/'

    runfunctionname = "run"
    libdir = (base_rundir+'/lib').replace('///','/').replace('//','/')+'/'
    #print "libdir: ",libdir
    runCfileFullPath = ""
    if IsKISTI:
      libdir = './lib/'
      runfunctionname = "run_"+str(it_job).zfill(3)
      runCfileFullPath = base_rundir+'/run_'+str(it_job).zfill(3)+'.C'
    else:
      os.system('mkdir -p '+thisjob_dir)
      runCfileFullPath = thisjob_dir+'run.C'

    if not IsHadd:
      IncludeLine  = 'R__LOAD_LIBRARY(libPhysics.so)\n'
      IncludeLine += 'R__LOAD_LIBRARY(libTree.so)\n'
      IncludeLine += 'R__LOAD_LIBRARY(libHist.so)\n'
      IncludeLine += 'R__LOAD_LIBRARY({0}libCommonTools.so)\n'.format(libdir)
      IncludeLine += 'R__LOAD_LIBRARY({0}libDataFormats.so)\n'.format(libdir)
      IncludeLine += 'R__LOAD_LIBRARY({0}libAnalyzerTools.so)\n'.format(libdir)
      IncludeLine += 'R__LOAD_LIBRARY({0}libAnalyzers.so)\n'.format(libdir)
      IncludeLine += 'R__LOAD_LIBRARY(/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/lhapdf/6.2.1-fmblme/lib/libLHAPDF.so)\n'
      #IncludeLine = 'R__LOAD_LIBRARY({1}/{0}_C.so)'.format(args.Analyzer, libdir)

    out = open(runCfileFullPath, 'w')
    if not IsHadd:
      print>>out,'''{3}

void {2}(){{

  {0} m;

  m.SetTreeName("recoTree/SKFlat");
'''.format(args.Analyzer, libdir, runfunctionname, IncludeLine)

      if IsDATA:
        out.write('  m.IsDATA = true;\n')
        out.write('  m.DataStream = "'+InputSamples[InputSample]['key']+'";\n')
      else:
        out.write('  m.MCSample = "'+InputSamples[InputSample]['key']+'";\n');
        out.write('  m.IsDATA = false;\n')
        out.write('  m.xsec = '+str(this_xsec)+';\n')
        out.write('  m.sumW = '+str(this_sumw)+';\n')

      out.write('  m.DataYear = '+str(args.Year)+';\n')

      if len(Userflags)>0:
        out.write('  m.Userflags = {\n')
        for flag in Userflags:
          out.write('    "'+flag+'",\n')
        out.write('  };\n')

      for it_file in FileRanges[it_job]:
        thisfilename = inputFileList[it_file].strip('\n')
        out.write('  m.AddFile("'+thisfilename+'");\n')

#TODO
    if IsSKim :
      if IsSNU:
        tmp_inputFilename = inputFileList[ FileRanges[it_job][0] ].strip('\n')
	#print 'tmp_inputFilename', tmp_inputFilename
	#print 'InputSample',InputSample
	#if "_" in InputSample:
	#  delemeter = InputSample.split('_')[0]+'_'
	#  chunkedInputFileName = delemeter+tmp_inputFilename.split(delemeter)[1]
	#else:
	#  chunkedInputFileName = InputSample+tmp_inputFilename.split(InputSample)[1]
	if IsDATA:
	  chunkedInputFileName = InputSamples[InputSample]['key']+tmp_inputFilename.split(InputSamples[InputSample]['key'])[1]
	else:
	  chunkedInputFileName = InputSample+tmp_inputFilename.split(InputSample)[1]

	#print 'chumkedInputFileName',chunkedInputFileName

        ## /data7/DATA/SKFlat/v949cand2_2/2017/DATA/SingleMuon/periodB/181107_231447/0000
        ## /data7/DATA/SKFlat/v949cand2_2/2017/MC/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/181108_152345/0000/SKFlatNtuple_2017_MC_100.root
        #dir1 = '/data7/DATA/SKFlat/'+SKFlatV+'/'+args.Year+'/'
        #dir2 = dir1
        #if IsDATA:
        #  dir1 += "DATA/"
        #  dir2 += "DATA_"+args.Analyzer+"/"
        #else:
        #  dir1 += "MC/"
        #  dir2 += "MC_"+args.Analyzer+"/"

        #skimoutname = tmp_filename.replace(dir1,dir2)

        #tmp_filename = skimoutname.split('/')[-1]
	#outPath = skimoutname.replace(tmp_filename,'')
	#print "outPath", outPath
	#outPath = FinalOutputPath + '/'+InSkimString
	out_Path_FileName = FinalOutputPath+'/'+chunkedInputFileName
	out_FileName = out_Path_FileName.split('/')[-1]
	out_Path          = out_Path_FileName.replace(out_FileName,'')
	#print 'out_Path_FileName',out_Path_FileName
	#print 'out_Path',out_Path
	#print 'out_FileName',out_FileName
	#fileName=InSkimString+str(it_job).zfill(3)+'root'
        os.system('mkdir -p '+ out_Path)
        out.write('  m.SetOutfilePath("'+out_Path_FileName+'");\n')
      else:
        out.write('  m.SetOutfilePath("hists.root");\n')
    elif IsHadd:
      out_Path = FinalOutputPath +'/' +sampleBaseName +'/'
      os.system('mkdir -p '+ out_Path)
      out_Path_FileName = out_Path +'/hadd_'+str(it_job)+'.root'
      out.write(' hadd -f '+out_Path_FileName+' ')
      for it_file in FileRanges[it_job]:
        thisfilename = inputFileList[it_file].strip('\n')
        out.write(' '+thisfilename)
    else:
      if IsKISTI:
        out.write('  m.SetOutfilePath("hists.root");\n')
      else:
        out.write('  m.SetOutfilePath("'+thisjob_dir+'/hists.root");\n')


    if not IsHadd:
      out.write('  m.Init();'+'\n')
      #if not IsSKim:
      #  out.write('  m.initializeAnalyzerTools();'+'\n')
      print>>out,'''  m.initializeAnalyzer();
  m.Loop();

  m.WriteHist();

}'''
      out.close()

    if IsSNU:
      run_commands = open(thisjob_dir+'commands.sh','w')
      if not IsHadd:
        print>>run_commands,'''cd {0}
echo "[mkGardener.py] Okay, let's run the analysis"
root -l -b -q run.C
'''.format(thisjob_dir)
      elif IsHadd:
        print>>run_commands,'''cd {0}
echo "[mkGardener.py] Okay, let's run the analysis"
source ./run.C
'''.format(thisjob_dir)

      run_commands.close()

      jobname = 'job_'+str(it_job)+'_'+args.Analyzer
      cmd = 'qsub -V -q '+args.Queue+' -N '+jobname+' -wd '+thisjob_dir+' commands.sh '

      if not args.dry_run:
        cwd = os.getcwd()
        os.chdir(thisjob_dir)
	print 'submitting',cmd
        os.system(cmd+' > submitlog.log')
        os.chdir(cwd)
      else:
	print 'Dry-Run: cmd',cmd
      sublog = open(thisjob_dir+'/submitlog.log','a')
      sublog.write('\nSubmission command was : '+cmd+'\n')
      sublog.close()

    if IsKNU:
      run_commands = open(thisjob_dir+'commands.sh','w')
      print>>run_commands,'''cd {0}
cp ../x509up_u{1} /tmp/
echo "[mkGardener.py] Okay, let's run the analysis"
root -l -b -q run.C 1>stdout.log 2>stderr.log
'''.format(thisjob_dir,UID)
      run_commands.close()

      jobname = 'job_'+str(it_job)+'_'+args.Analyzer
      cmd = 'qsub -V -q '+args.Queue+' -N '+jobname+' commands.sh'

      if not args.dry_run:
        cwd = os.getcwd()
        os.chdir(thisjob_dir)
        os.system(cmd+' > submitlog.log')
        os.chdir(cwd)
      sublog = open(thisjob_dir+'/submitlog.log','a')
      sublog.write('\nSubmission command was : '+cmd+'\n')
      sublog.close()

  if IsKISTI:

    cwd = os.getcwd()
    os.chdir(base_rundir)
    os.system('tar -czf runFile.tar.gz run_*.C')
    cmd = 'condor_submit submit.jds'
    if not args.dry_run:
      os.system(cmd)
    else:
      print 'Dry run, command "'+cmd+'" will be excuted for real run at '+ base_rundir
    os.chdir(cwd)

  else:

    if args.dry_run:
      continue

    ## Write Kill Command

    KillCommand = open(base_rundir+'/Script_JobKill.sh','w')
    for it_job in range(0,len(FileRanges)):
      thisjob_dir = base_rundir+'/job_'+str(it_job)+'/'
      jobid = GetJobID(thisjob_dir, args.Analyzer, it_job, HostNickName)
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
os.system('rm -f '+SKFlat_WD+'/'+str_RandomNumber+'_data.tar.gz')
os.system('rm -f '+SKFlat_WD+'/'+str_RandomNumber+'_lib.tar.gz')



print '##################################################'
print 'Submission Finished'
print '- Analyzer = '+args.Analyzer
print '- InSkim = '+args.InSkim
print '- InputSamples =',
print InputSamples
print '- NJobs = '+str(NJobs)
print '- Year = '+args.Year
print '- UserFlags =',
print Userflags, args.skimV
if IsSNU or IsKNU:
  print '- Queue = '+args.Queue
print '- output will be send to : '+ out_Path
print '##################################################'

if args.dry_run:
  print "Exiting dry_run "
  exit()

if not args.MonitJob:
  print 'No monitering job'
  print 'Bye!!!'
  exit()



print "Every process has done, bye!!!"
exit()
