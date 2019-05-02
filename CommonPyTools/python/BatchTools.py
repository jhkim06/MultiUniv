#!/usr/bin/python

import os
from getEvn import *

class batchJobs:
  def __init__(self,jobName,Queue,jobDir,dry_run):
    self.jobDir = jobDir
    if self.jobDir[-1] != "/":
      self.jobDir = self.jobDir + '/'

    self.Queue = Queue
    self.jobName = jobName
    self.dry_run = dry_run

    self.CmdShell     = self.jobDir + self.jobName+'.sh'
    self.CmdPy        = self.jobDir + self.jobName+'.py'
    self.condoJdsName = self.jobDir + 'submit.jds'

    if IsUI10 or IsUI20 or IsTAMSA2 or IsTAMSA1:
      self.mkShCommand()
      self.mkJds()

    pFile = open(self.CmdPy,'w')
    pFile.close()

  def AddPy2Sh(self):
    sFile = open(self.CmdShell,'a')
    command = 'python commands.py'
    sFile.write(command+'\n')
    sFile.close()

  def AddSh(self, command):
    sFile = open(self.CmdShell,'a')
    sFile.write(command+'\n')
    sFile.close()
  
  def AddPy (self,command):
    pFile = open(self.CmdPy, 'a')
    pFile.write(command+'\n')
    pFile.close()


  def Sub(self):
    if IsTAMSA1 or IsTAMSA2:
      print 'SNU farm', 'Queue', self.Queue, 'jobName', self.jobName
      cmd = 'condor_submit submit.jds '+self.Queue
      #cmd = 'qsub -V -q '+self.Queue+' -N '+self.jobName+' -wd '+self.jobDir+' commands.sh '
      if not self.dry_run:
	cwd = os.getcwd()
	os.chdir(self.jobDir)
	os.system(cmd)
	os.chdir(cwd)
      else:
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
'''.format(str(1), self.CmdShell)
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
'''.format(str(1), self.CmdShell)
# We don't use the multi queue at the moment
#transfer_output_remaps = "hists.root = output/hists_$(Process).root"
    
    elif IsTAMSA1 or IsTAMSA2:
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
'''.format(str(1), self.CmdShell)
# We don't use the multi queue at the moment
#transfer_output_remaps = "hists.root = output/hists_$(Process).root"
    else:
      print "This host", HOSTNAME, "is not ready for batch job, exiting..........."
      exit()

    jdsFile.close()

  def mkShCommand(self):
    sFile = open(self.CmdShell,'w')
    print>>sFile,'''#!/bin/bash
SECTION=`printf $1`
WORKDIR=`pwd`
SumNoAuth=999
Trial=0

source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.14.06/x86_64-centos7-gcc48-opt/bin/thisroot.sh

while [ "$SumNoAuth" -ne 0 ]; do
  if [ "$Trial" -gt 9999 ]; then
    break
  fi
  echo "#### running ####"
  python {0} 2> err.log
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
'''.format(self.CmdPy)
    sFile.close()
    #os.system('chmod +x '+self.CmdShell)

