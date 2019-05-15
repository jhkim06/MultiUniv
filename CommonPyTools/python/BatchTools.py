#!/usr/bin/python

import os
from getEvn import *

class batchJobs:
  def __init__(self, jobName, Queue, jobDir, cmdType, dry_run):
    self.jobDir = jobDir
    if self.jobDir[-1] != "/":
      self.jobDir = self.jobDir + '/'

    self.Queue   = Queue
    self.jobName = jobName
    self.dry_run = dry_run
    self.cmdType = cmdType

    self.MacShell     = self.jobDir + self.jobName+'.sh'
    self.MacPy        = self.jobDir + self.jobName+'.py'
    self.MacRoot      = self.jobDir + self.jobName+'.C'
    self.condoJdsName = self.jobDir + 'submit.jds'

    self.exCmd =""
    if self.cmdType == "root":
      self.exCmd = 'root -l -b -q ' + self.MacRoot
      aFile = open(self.MacRoot,'w')
      aFile.close()
    elif self.cmdType == "python":
      self.exCmd = 'python ' + self.MacPy
      aFile = open(self.MacPy,'w')
      aFile.close()


  def AddPy2Sh(self):
    sFile = open(self.MacShell,'a')
    command = 'python commands.py'
    sFile.write(command+'\n')
    sFile.close()

  def AddSh(self, command):
    sFile = open(self.MacShell,'a')
    sFile.write(command+'\n')
    sFile.close()
  
  def AddPy (self,command):
    pFile = open(self.MacPy, 'a')
    pFile.write(command+'\n')
    pFile.close()

  def AddRooMac(self, command):
    aFile = open(self.MacRoot, 'a')
    aFile.write(command+'\n')
    aFile.close()

  def SetExCmd(self, cmd):
    self.exCmd = cmd


  def Sub(self):
    if IsSNU or IsKISTI or IsKNU :
      print 'SNU farm', 'Queue', self.Queue, 'jobName', self.jobName
      if IsSNU or IsKISTI:
        cmd = 'condor_submit submit.jds '+self.Queue
      else:
        cmd = 'qsub -V -q '+self.Queue+' -N '+self.jobName+' -wd '+self.jobDir+' commands.sh '

      if not self.dry_run:
	cwd = os.getcwd()
	os.chdir(self.jobDir)
	os.system(cmd)
	os.chdir(cwd)
      else:
	print 'cmd at here',self.jobDir
	print'dry_run, cmd=',cmd

      sublog = open(self.jobDir+'/submitlog.log','a')
      sublog.write('\nSubmission command was : '+cmd+'\n')
      sublog.close()
    else:
      print HOSTNAME, 'is not ready for batchJob'

  def mkJds(self):
    jdsFile = open(self.condoJdsName, 'w')

    if IsUI10:
      print>>jdsFile,'''executable = {1}
universe   = vanilla
arguments  = $(Process)
requirements = OpSysMajorVer == 6
log = condor.log
getenv     = True
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
output = job_$(Process).log
error = job_$(Process).err
queue {0}
'''.format(str(1), self.MacShell)
# we don't use arguments and multi queue at the moment.
#transfer_output_remaps = "hists.root = output/hists_$(Process).root"
    elif IsUI20:
      print>>jdsFile,'''executable = {1}
universe   = vanilla
requirements = ( HasSingularity == true )
arguments  = $(Process)
log = condor.log
getenv     = True
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
output = job_$(Process).log
error = job_$(Process).err
accounting_group=group_cms
+SingularityImage = "/cvmfs/singularity.opensciencegrid.org/opensciencegrid/osgvo-el6:latest"
+SingularityBind = "/cvmfs, /cms, /share"
queue {0}
'''.format(str(1), self.MacShell)
# We don't use the multi queue at the moment
#transfer_output_remaps = "hists.root = output/hists_$(Process).root"
    elif IsSNU:
      print>>jdsFile,'''executable = {1}
universe = vanilla
arguments  = $(Process)
log = condor.log
getenv     = True
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
output = job_$(Process).log
error = job_$(Process).err
accounting_group=group_cms
queue {0}
'''.format(str(1), self.MacShell)
# We don't use the multi queue at the moment
#transfer_output_remaps = "hists.root = output/hists_$(Process).root"
    else:
      print "This host", HOSTNAME, "is not ready for batch job, exiting..........."
      exit()

    jdsFile.close()

  def mkShCommand(self):
    sFile = open(self.MacShell,'w')
    if IsKNU:
      print>>sFile,'''cd {0}
cp ../x509up_u{1} /tmp/
echo "[mkGardener.py] Okay, let's run the analysis"
{2} 1>stdout.log 2>stderr.log
'''.format(thisjob_dir, UID, self.exCmd)
    elif IsTAMSA1:
      #export GCC_HOME=/usr/
      #export PATH=$GCC_HOME/bin:$PATH
      #export LD_LIBRARY_PATH=$GCC_HOME/lib/gcc/x86_64-redhat-linux:$GCC_HOME/lib64:$LD_LIBRARY_PATH
      print>>sFile,'''#!/bin/bash
SECTION=`printf $1`
WORKDIR=`pwd`
SumNoAuth=999
Trial=0
export GCC_HOME=/usr/
export PATH=$GCC_HOME/bin:$PATH
export LD_LIBRARY_PATH=$GCC_HOME/lib/gcc/x86_64-redhat-linux:$GCC_HOME/lib64:$LD_LIBRARY_PATH
source /data6/Users/salee/ROOT616_TAMSA1/bin/thisroot.sh

while [ "$SumNoAuth" -ne 0 ]; do
  if [ "$Trial" -gt 9999 ]; then
    break
  fi
  echo "#### running ####"
  {0} 2> err.log
  NoAuthError_Open=`grep "Error in <TNetXNGFile::Open>" err.log -R | wc -l`
  NoAuthError_Close=`grep "Error in <TNetXNGFile::Close>" err.log -R | wc -l`

  SumNoAuth=$(($NoAuthError_Open + $NoAuthError_Close))

  if [ "$SumNoAuth" -ne 0 ]; then
    echo "SumNoAuth="$SumNoAuth
    echo "AUTH error occured.. running again in 30 seconds.."
    Trial=$((Trial+=1))
    sleep 30
  fi

done
cat err.log >&2
'''.format(self.exCmd)
      sFile.close()
    else:
      print>>sFile,'''#!/bin/bash
SECTION=`printf $1`
WORKDIR=`pwd`
SumNoAuth=999
Trial=0

source /data6/Users/salee/ROOT616/bin/thisroot.sh

while [ "$SumNoAuth" -ne 0 ]; do
  if [ "$Trial" -gt 9999 ]; then
    break
  fi
  echo "#### running ####"
  {0} 2> err.log
  NoAuthError_Open=`grep "Error in <TNetXNGFile::Open>" err.log -R | wc -l`
  NoAuthError_Close=`grep "Error in <TNetXNGFile::Close>" err.log -R | wc -l`

  SumNoAuth=$(($NoAuthError_Open + $NoAuthError_Close))

  if [ "$SumNoAuth" -ne 0 ]; then
    echo "SumNoAuth="$SumNoAuth
    echo "AUTH error occured.. running again in 30 seconds.."
    Trial=$((Trial+=1))
    sleep 30
  fi

done
cat err.log >&2
'''.format(self.exCmd)
      sFile.close()

      #os.system('chmod +x '+self.MacShell)
#TODO export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKFlat_LIB_PATH

