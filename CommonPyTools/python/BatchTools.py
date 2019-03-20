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

    self.CmdShell = self.jobDir + 'commands.sh'
    self.CmdPy    = self.jobDir + 'commands.py'

    jFile = open(self.CmdShell,'w')
    jFile.write('#!/bin/bash\n')
    jFile.close()
    os.system('chmod +x '+self.CmdShell)

    pFile = open(self.CmdPy,'w')
    pFile.close()

  def AddPy2Sh(self):
    jFile = open(self.CmdShell,'a')
    command = 'python commands.py'
    jFile.write(command+'\n')
    jFile.close()
  
  def AddPy (self,command):
    pFile = open(self.CmdPy, 'a')
    pFile.write(command+'\n')
    pFile.close()


  def Sub(self):
    if IsTamsa1:
      print 'tamsa1', 'Queue', self.Queue, 'jobName', self.jobName
      cmd = 'qsub -V -q '+self.Queue+' -N '+self.jobName+' -wd '+self.jobDir+' commands.sh '
      if not self.dry_run:
	cwd = os.getcwd()
	os.chdir(self.jobDir)
	os.system(cmd+' > submitlog.log')
	os.chdir(cwd)
      else:
	print'dry_run, cmd=',cmd

      sublog = open(self.jobDir+'/submitlog.log','a')
      sublog.write('\nSubmission command was : '+cmd+'\n')
      sublog.close()
    else:
      print HOSTNAME, 'is not ready for batchJob'


