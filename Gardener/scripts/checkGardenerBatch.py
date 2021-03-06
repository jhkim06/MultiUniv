#!/usr/bin/env python

import os,sys,time
#import os.path
import argparse
import datetime
import random
#sys.path.insert(0,'../../CommonTools/python')
from CommonPyTools.python.getEvn import *
from CommonPyTools.python.CheckJobStatus import *
from CommonPyTools.python.TimeTools import *
#sys.path.insert(0,'../../data/python')
from CommonPyTools.DataSample.SampleDef import *
from CommonPyTools.python.BatchTools import *
from CommonPyTools.python.CommonTools import *

parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('-a', dest='Analyzer', default="")
parser.add_argument('-i', dest='InputSampleKey', default="")
parser.add_argument('-p', dest='DataPeriod', default="ALL")
parser.add_argument('-l', dest='InputSampleList', default="")
parser.add_argument('-n', dest='NJobs', default=1, type=int)
parser.add_argument('-o', dest='Outputdir', default="")
parser.add_argument('-q', dest='Queue', default="fastq")
parser.add_argument('-y', dest='Year', default="2017")
parser.add_argument('--RundirBase', dest='RundirBase', default="")
parser.add_argument('--InSkim', dest='InSkim', default="")
parser.add_argument('--dry_run', action='store_true')
parser.add_argument('--SkimName', dest='SkimName', default="")
parser.add_argument('--flagVer', dest='flagVer', default="0")
parser.add_argument('--nTotFiles', dest='nTotFiles', default=0, type=int)
parser.add_argument('--MonitJob', dest='MonitJob', default=False, type=bool)
parser.add_argument('--Category', dest='Category', default="SMP")

args = parser.parse_args()

print "Let's go"
InputSampleName = []
InputSampleName.append(args.InputSampleKey)
## make flags
SkimName = args.SkimName

## Is Skim run?
IsSKim = "Skim" in args.Analyzer
IsHadd = "hadd" in args.Analyzer


if IsSKim:
  if IsSNU:
    print  "Skim in SNU setting "
    print 'argss.NJobs',args.NJobs
  elif IsKISTI:
    print "Skim in Kisti"
  else:
    print "Skimming in ", HostNickName, "is not prepared kkk"
    exit()


SendLogToWeb = True
if SKFlatLogWeb=='' or SKFlatLogWebDir=='':
  SendLogToWeb = False

ProductionKey = SKFlatV+'_'+args.Year
print 'Productions key:',ProductionKey
InputSamples = {}
StringForHash = ""
#print 'File to import', Productions[args.Category][ProductionKey]['MC']
cmd = 'from '+Productions[args.Category][ProductionKey]['MC'] +' import *'
exec(cmd, globals())

## When using list
if args.InputSampleList is not "":
  lines = open(args.InputSampleList)
  for line in lines:
    if "#" in line:
      continue
    line = line.strip('\n')
    InputSamples[line]=line
else:
  InputSamples,StringForHash = GetInputSamples(InputSampleName, args.DataPeriod, args.Year, args.Category, ProductionKey)


print 'InputSamples', InputSamples
print 'len(InputSamples)',len(InputSamples)
## Get Random Number for webdir

webdirpathbase = SKFlatRunlogDir+'/www/SKFlatAnalyzerJobLogs/'

## Loop over samples
SampleFinishedForEachSample = {}
BaseDirForEachSample = []



for InputSample in InputSamples:
  SampleFinishedForEachSample[InputSample]=False

AllSampleFinished = False
GotError = False
ErrorLog = ""

try:
  while not AllSampleFinished:

    if GotError:
      break

    AllSampleFinished = True

    CheckLog = open('JobCheck.log','a')
    #for it_sample in range(0,len(InputSamples)):
    for it_sample in InputSamples:

      print 'checking for sample:',it_sample
      IsDATA = False
      DataPeriod = ""
      if ":" in it_sample:
        IsDATA = True
        InputSample = it_sample.split(":")[0]
        DataPeriod  = it_sample.split(":")[1]
	InputSample = InputSample+'_'+DataPeriod
      if IsDATA == False:
	InputSample = InputSamples[it_sample]['key']

      CheckLog.write('checking for sample:'+InputSample+'\n')
      SampleFinished = SampleFinishedForEachSample[it_sample]
      if SampleFinished:
        continue
      else:
	pass
        #AllSampleFinished = False

      ## Prepare output
      ## This should be copied from above
      base_rundir = args.RundirBase+'/'+args.Analyzer + '_Y'+args.Year+'_'+InputSample
      base_rundir += '_'+SkimName+'/'
      for line in open(base_rundir+'SubmitOutput.log','r'):
        line = line.rstrip('\n')
	if 'NJobs' in line:
	  NJobs = int(line.split(' ')[3])
	  break

      print 'from',base_rundir+'SubmitOutput.log','NJobs', NJobs

      #NJobs = 1
      this_webdir = webdirpathbase+'/'+base_rundir.replace(SKFlatRunlogDir,'')
      os.system('mkdir -p '+this_webdir)

      if not SampleFinished:

        ## This sample was not finished in the previous monitoring
        ## Monitor again this time

        ThisSampleFinished = True

        ## Write Job status until it's done
        statuslog = open(base_rundir+'/JobStatus.log','w')
        statuslog.write('JobNumber\t| Status\n')

        ToStatuslog = []
        n_eventran = 0
        finished = []
        EventDone = 0
        EventTotal = 0

        TotalEventRunTime = 0
        MaxTimeLeft = 0
        MaxEventRunTime = 0

	CheckLog.write('Njob: '+ str(NJobs)+'\n')

        for it_job in range(0,NJobs):
          this_status = ""
          this_status = CheckJobStatus(base_rundir, args.Analyzer, it_job, HostNickName, IsHadd)
	  print base_rundir, args.Analyzer, 'job',it_job
	  print "this_status",this_status

          if "ERROR" in this_status:
            GotError = True
            statuslog.write("#### ERROR OCCURED ####\n")
            CheckLog.write("#### ERROR OCCURED #### for job_"+str(it_job)+"\n")
            statuslog.write(this_status+'\n')
            CheckLog.write(this_status+'\n')
            ErrorLog = this_status
            print '###################### ERROR OCCURED ##########################'
	    print ErrorLog

            break

          if "FINISHED" not in this_status:
	    CheckLog.write('Not FINISHED at job # '+ str(it_job)+'\n' )
	    CheckLog.write(this_status+'\n' )
            ThisSampleFinished = False

          outlog = ""
          if "FINISHED" in this_status:
            finished.append("Finished")
	    if IsHadd:
	      continue

            EventInfo = this_status.split()[1].split(':')

	    # Finished status, this is a trick to make Ntotal = NDone
            this_EventDone = int(EventInfo[2])
            this_EventTotal = int(EventInfo[2])

            EventDone += this_EventDone
            EventTotal += this_EventTotal

            #### start
            line_EventRunTime = this_status.split()[2]+' '+this_status.split()[3]
            this_jobstarttime = GetDatetimeFromMyFormat(line_EventRunTime)
            #### end
            line_EventEndTime = this_status.split()[4]+' '+this_status.split()[5]
            this_jobendtime   = GetDatetimeFromMyFormat(line_EventEndTime)

            this_diff = this_jobendtime-this_jobstarttime
            this_EventRunTime = 86400*this_diff.days+this_diff.seconds

            this_TimePerEvent = float(this_EventRunTime)/float(this_EventDone)
            this_TimeLeft = (this_EventTotal-this_EventDone)*this_TimePerEvent

            TotalEventRunTime += this_EventRunTime
            MaxTimeLeft = max(MaxTimeLeft,this_TimeLeft)
            MaxEventRunTime = max(MaxEventRunTime,this_EventRunTime)

          elif "RUNNING" in this_status:
            outlog = str(it_job)+'\t| '+this_status.split()[1]+' %'

            if len(this_status.split())<3 :
              SubmitOutput.write('len(this_status.split())<3;; Priting this_status.split()\n')
              SubmitOutput.write(this_status.split()+'\n')

            EventInfo = this_status.split()[2].split(':')

            this_EventDone = int(EventInfo[1])
            this_EventTotal = int(EventInfo[2])

            EventDone += this_EventDone
            EventTotal += this_EventTotal

            line_EventRunTime = this_status.split()[3]+' '+this_status.split()[4]
            this_jobstarttime = GetDatetimeFromMyFormat(line_EventRunTime)
            this_diff = datetime.datetime.now()-this_jobstarttime
            this_EventRunTime = 86400*this_diff.days+this_diff.seconds

            if this_EventDone==0:
              this_EventDone = 1

            this_TimePerEvent = float(this_EventRunTime)/float(this_EventDone)
            this_TimeLeft = (this_EventTotal-this_EventDone)*this_TimePerEvent

            TotalEventRunTime += this_EventRunTime
            MaxTimeLeft = max(MaxTimeLeft,this_TimeLeft)
            MaxEventRunTime = max(MaxEventRunTime,this_EventRunTime)

            round_this_TimeLeft = round(this_TimeLeft,1)
            round_this_EventRunTime = round(this_EventRunTime,1)

            outlog += ' ('+str(round_this_EventRunTime)+' s ran, and '+str(round_this_TimeLeft)+' s left)'
            ToStatuslog.append(outlog)
            n_eventran += 1

          else:
            outlog = str(it_job)+'\t| '+this_status
            ToStatuslog.append(outlog)

          ##---- END it_job loop

        if GotError:
          ## When error occured, change both Finished/PostJob Flag to True
          SampleFinishedForEachSample[it_sample] = True
          break

        for l in ToStatuslog:
          statuslog.write(l+'\n')
        statuslog.write('\n==============================================================\n')
        statuslog.write('HostNickName = '+HostNickName+'\n')
        statuslog.write('queue = '+args.Queue+'\n')
        statuslog.write(str(NJobs)+' jobs submitted\n')
        statuslog.write(str(n_eventran)+' jobs are running\n')
        statuslog.write(str(len(finished))+' jobs are finished\n')

        ThisTime = datetime.datetime.now()
        string_ThisTime =  ThisTime.strftime('%Y-%m-%d %H:%M:%S')

        statuslog.write('EventDone = '+str(EventDone)+'\n')
        statuslog.write('EventTotal = '+str(EventTotal)+'\n')
        statuslog.write('EventLeft = '+str(EventTotal-EventDone)+'\n')
        statuslog.write('TotalEventRunTime = '+str(TotalEventRunTime)+'\n')
        statuslog.write('MaxTimeLeft = '+str(MaxTimeLeft)+'\n')
        statuslog.write('MaxEventRunTime = '+str(MaxEventRunTime)+'\n')

        t_per_event = 1
        if EventDone is not 0:
          t_per_event = float(TotalEventRunTime)/float(EventDone)
        statuslog.write('t_per_event = '+str(t_per_event)+'\n')

        EstTime = ThisTime+datetime.timedelta(0, MaxTimeLeft)

        statuslog.write('Estimated Finishing Time : '+EstTime.strftime('%Y-%m-%d %H:%M:%S')+'\n')
        statuslog.write('Last checked at '+string_ThisTime+'\n')
        statuslog.close()

        ## copy statuslog to webdir
        os.system('cp '+base_rundir+'/JobStatus.log '+this_webdir)

        ## This time, it is found to be finished
        ## Change the flag
        if ThisSampleFinished:
          SampleFinishedForEachSample[it_sample] = True
        ##---- END if finished

      else:
	pass

    
    CheckLog.close()
    print 'possible error recoded on JobCheck.log'

    if SendLogToWeb:

      os.system('scp -r '+webdirpathbase+'/* '+SKFlatLogWeb+':'+SKFlatLogWebDir)
      os.system('ssh -Y '+SKFlatLogWeb+' chmod -R 777 '+SKFlatLogWebDir+'/'+args.Analyzer+"*")

    #time.sleep(5)

except KeyboardInterrupt:
  print('interrupted!')


# Send Email now

##from SendEmail import *
#JobFinishEmail = '''#### Job Info ####
#HOST = {3}
#Analyzer = {0}
#SkimName = {5}
## of Jobs = {4}
#InputSample = {1}
#Output sent to : {2}
#'''.format(args.Analyzer,InputSamples,FinalOutputPath,HostNickName,NJobs,args.SkimName)
##JobFinishEmail += '''##################
##Job started at {0}
##Job finished at {1}
##'''.format(string_JobStartTime,string_ThisTime)
#
#if IsSNU or IsKNU:
#  JobFinishEmail += 'Queue = '+args.Queue+'\n'
#
#EmailTitle = '['+HostNickName+']'+' Job Summary'
#if GotError:
#  JobFinishEmail = "#### ERROR OCCURED ####\n"+JobFinishEmail
#  JobFinishEmail = ErrorLog+"\n------------------------------------------------\n"+JobFinishEmail
#  EmailTitle = '[ERROR] Job Summary'
#else:
#  print 'Congratulation! there is no error occured'
#  print 'Check log file at', base_rundir+'/JobStatus.log'
#
#if IsKNU:
#  SendEmailbyGMail(USER,SKFlatLogEmail,EmailTitle,JobFinishEmail)
#else:
#  SendEmail(USER,SKFlatLogEmail,EmailTitle,JobFinishEmail)


print "Every process has done, bye!!!"
exit()
