#!/usr/bin/env python

import os,sys,time
#import os.path
import argparse
import datetime
import random
import subprocess
import math
import ROOT

ROOT.gROOT.SetBatch()

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
parser.add_argument('--concLimit', dest='ConcurrencyLimit', default=-1, type=int)
parser.add_argument('--InSkim', dest='InSkim', default="")
parser.add_argument('--userflags', dest='Userflags', default="test")
parser.add_argument('--skimV', dest='skimV', default="0")
parser.add_argument('--Category', dest='Category', default="SMP")
parser.add_argument('--treeName', dest='treeName', default="")
parser.add_argument('--cleanUp', dest='cleanUp', action='store_true')


Tools.AddOptions(parser)
Tools.LoadOptDefaults(parser)
opt = parser.parse_args()
print '=================================================================='
print "Let's go for",SKFlatV,"to calculate pdf uncertainties"
print '=================================================================='
##########################
# Dump configurations
##########################

sys.path.append(os.getcwd())

ROOT.TH1D.SetDefaultSumw2(True)
ROOT.TH2D.SetDefaultSumw2(True)

variables = {}
columns = []
definitions = {}
if opt.variablesFile != '':
  if os.path.exists(opt.variablesFile):
    handle = open(opt.variablesFile,'r')
    exec(handle)
    #exec(handle,globals())
    handle.close()
  else:
    print 'You should have variable configuration file,  exiting...'
    exit()
else:
  print 'You should have variable configuration file,  exiting...'
  exit()

cuts = {}
if opt.cutsFile != '':
  if os.path.exists(opt.cutsFile):
    handle = open(opt.cutsFile,'r')
    exec(handle)
    handle.close()
  else:
    print 'You should have cut configuration file,  exiting...'
    exit()
else:
  print 'You should have cut configuration file,  exiting...'
  exit()

samples = OrderedDict()
##print 'sample cfg',opt.samplesFile
if opt.samplesFile != '':
  if os.path.exists(opt.samplesFile):
    handle = open(opt.samplesFile,'r')
    exec(handle)
    handle.close()
  else:
    print 'You should have sample configuration file,  exiting...'
    exit()
else:
  print 'You should have sample configuration file,  exiting...'
  exit()

groupPlot = OrderedDict()
plot = {}
legend = {}
if os.path.exists(opt.plotFile) :
  handle = open(opt.plotFile,'r')
  exec(handle)
  handle.close()
else:
  print 'You should have plot configuration file,  exiting...'
  exit()

nuisances = {}
if opt.nuisancesFile != '':
  if os.path.exists(opt.nuisancesFile):
    handle = open(opt.nuisancesFile,'r')
    exec(handle)
    handle.close()
  else:
    print 'You should have nuisances configuration file,  exiting...'
    exit()
else:
  print 'You should have nuisances configuration file,  exiting...'
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
print "OutBase", OutBase
#
##############################
# Dump Input Sample list
##############################
# Dump MC infor

InputSampleKeys = []
InputSampleSkims = {}
print 'samples keys', samples.keys()
for key in samples:

  InputSampleKeys.append(key)
  if len(key.split("@")) > 1 :
    key_ =     key.split("@")[1]
  else :
    key_ = key

#  InputSampleSkims[key_]=tmp_skim_string
InputSamples,StringForHash = GetInputSamples(InputSampleKeys,opt.DataPeriod,opt.Year,opt.Category,ProductionKey)
print 'InputSamples', InputSamples  
#
#
#############################
### Loop over samples
#############################

AllSampleFile = OutBase + '/'
for flag in Userflags:
  AllSampleFile += flag
AllSampleFile += '.root'

#if os.path.exists(AllSampleFile) :
if os.path.isfile(AllSampleFile) :
  print 'The input file is', '"'+ AllSampleFile+'"'
else:
  print 'There is no file', '"'+AllSampleFile+'"'

InF = ROOT.TFile(AllSampleFile,"UPDATE")
try:
  InF.IsZombie()
except:
  print 'There is no file:', AllSampleFile
  exit()

#print 'cuts', cuts

#print 'variables',variables

#print 'nuisances', nuisances
for icut in cuts:
  print 'icut',icut
  for ivar in variables:
    print 'ivar', ivar
    for InputSample in InputSamples:
      # no data used
      if ":" in InputSample: continue
      for nuisanceName, nuisance in nuisances.iteritems():
	if 'kind' in nuisance:
          if nuisance['kind'] is not 'PDF': continue
	  if InputSample in nuisance['samples']:
	    print 'nuisanceName in PDF kind', nuisanceName
	    print 'name', nuisance['name']
	    print 'InputSample', InputSample
            NominalName  = icut+'/'+ivar+'/histo_'+InputSample
	    hNom = InF.Get(NominalName)
	    if not hNom:
	      print 'there is no',NominalName,'exiting......'
	      exit()
	    #####################################PDF error #######################################
	    if 'HESSIAN' in nuisance['name'] or 'GAUSSIAN' in nuisance['name'] :
	      # 000 is nominal histogram
              CentName  = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+str(0).zfill(3)
	      hCent = InF.Get(CentName)
	      if not hCent:
		print 'there is no',CentName,'exiting.....'
		exit()

              binN = hCent.GetNbinsX()
	      print 'Total bin number',binN
	      BinVar2 = [0]*binN
	      # Looping for Variants Histograms
	      for iVar in range(100):
                VariantName  = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+str(iVar+1).zfill(3)
	        hTmp = InF.Get(VariantName)
	        if not hTmp:
	          print 'there is no',VariantName,'exiting......'
		  exit()
	        for ibin in range(binN):
	          nominal = hCent.GetBinContent(ibin+1)
		  variant = hTmp.GetBinContent(ibin+1)
		  BinVar2[ibin] = BinVar2[ibin] + (variant - nominal)*(variant - nominal)
	      # Output histogram for Pdf error up/down
	      if 'HESSIAN' in nuisance['name']:
                PDFerrUpName    = 'histo_'+InputSample+'_pdfHESSIANUp'
                PDFerrDownName  = 'histo_'+InputSample+'_pdfHESSIANDown'
	      if 'GAUSSIAN' in nuisance['name']:
                PDFerrUpName    = 'histo_'+InputSample+'_pdfGAUSSIANUp'
                PDFerrDownName  = 'histo_'+InputSample+'_pdfGAUSSIANDown'
	      hPDFerrUp   = hNom.Clone(PDFerrUpName)
	      hPDFerrDown = hNom.Clone(PDFerrDownName)
              # Calculation of variation rate for each bin and fill
	      for ibin in range(binN):
		contentOrg = hNom.GetBinContent(ibin+1)
                if 'HESSIAN' in nuisance['name']:
		  if hCent.GetBinContent(ibin+1) != 0:
	            BinVarRate = math.sqrt(BinVar2[ibin])/hCent.GetBinContent(ibin+1)
		  else:
	            BinVarRate = math.sqrt(BinVar2[ibin])
                if 'GAUSSIAN' in nuisance['name']:
		  if hCent.GetBinContent(ibin+1) != 0:
		    BinVarRate = math.sqrt(BinVar2[ibin])/hCent.GetBinContent(ibin+1)/99.
		  else:
		    BinVarRate = math.sqrt(BinVar2[ibin])/99.
		if hCent.GetBinContent(ibin+1) != 0:
	          print 'PDFError varRate for',ibin,'bin is',BinVarRate
		else:
	          print 'PDFError variation for',ibin,'bin is',BinVarRate

		if hCent.GetBinContent(ibin+1) != 0:
		  contentUp   = contentOrg*(1+BinVarRate)
		  contentDown = contentOrg*(1-BinVarRate)
		else:
		  contentUp   = contentOrg+BinVarRate
		  contentDown = contentOrg-BinVarRate

		hPDFerrUp.SetBinContent(ibin+1, contentUp)
		hPDFerrDown.SetBinContent(ibin+1, contentDown)
	      
	      InF.cd(icut+'/'+ivar)
	      hPDFerrUp.Write("",ROOT.TObject.kOverwrite)
	      #hPDFerrUp.Write("", TObject::kOverwrite)
	      hPDFerrDown.Write("",ROOT.TObject.kOverwrite)
	    ##################################### pdfScale error #######################################
	    if 'pdfScale' in nuisance['name'] :
              AUpName    = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+'AUp'
              ADownName  = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+'ADown'
              BUpName    = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+'BUp'
              BDownName  = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+'BDown'
              ABUpName   = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+'ABUp'
              ABDownName = icut+'/'+ivar+'/histo_'+InputSample+'_'+nuisance['name']+'ABDown'
	      hScale = [ROOT.TH1F]*6
	      hScale[0] = InF.Get(AUpName)
	      hScale[1] = InF.Get(ADownName)
	      hScale[2] = InF.Get(BUpName)
	      hScale[3] = InF.Get(BDownName)
	      hScale[4] = InF.Get(ABUpName)
	      hScale[5] = InF.Get(ABDownName)

	      Nnom    = hNom.Integral()
	      Nvaris = [0]*6
	      Nvaris[0] = hScale[0].Integral()
	      Nvaris[1] = hScale[1].Integral()
	      Nvaris[2] = hScale[2].Integral()
	      Nvaris[3] = hScale[3].Integral()
	      Nvaris[4] = hScale[4].Integral()
	      Nvaris[5] = hScale[5].Integral()
	      diff_Plus  = -999
	      diff_Minus = 999
	      idxPlus = -1
	      idxMinus = -1
	      for idx in range(6):
		diff = Nvaris[idx] - Nnom
		if diff > diff_Plus:
		  diff_Plus = diff
		  idxPlus = idx
		if diff < diff_Minus:
		  diff_Minus = diff
		  idxMinus = idx
	      if idxPlus < 0 or idxMinus <0:
		print 'Something wrong in Scale variation'
		exit()
	      if not Nnom==0:
	        print 'Max Scale Up variation', diff_Plus/Nnom, 'for',idxPlus
	        print 'Max Scale Down variation', diff_Minus/Nnom, 'for',idxMinus
	      else:
		print 'Nnom is zero'
	        pass
	      InF.cd(icut+'/'+ivar)
              ScaleUpName    = 'histo_'+InputSample+'_'+nuisance['name']+'Up'
              ScaleDownName    = 'histo_'+InputSample+'_'+nuisance['name']+'Down'
	      hScaleUp   = hScale[idxPlus].Clone(ScaleUpName)
	      hScaleDown = hScale[idxMinus].Clone(ScaleDownName)
	      hScaleUp.Write("",ROOT.TObject.kOverwrite)
	      hScaleDown.Write("",ROOT.TObject.kOverwrite)


InF.Close()
      #hist =InF.Get(histoName)
      #if hist:
      #  print histoName,'exists'
      #else:
      #  print histoName,'no no no'


#      #jobs.AddSh(shCmd)
#      #jobs.AddPy2Sh()
#     
#      jobs.AddPy("from ShapeAnalysis.python.ShapeFactory import ShapeFactory\n") 
#      jobs.AddPy("factory = ShapeFactory()")
#      jobs.AddPy("factory._treeName = "+"'"+opt.treeName+"'" )
#      instructions  = ""
#      instructions += "factory.makeNominals( \n"
#      instructions += "		'"+ sampleName + "', \n"
#      instructions += "		"+str(sample) + ", \n"
#      instructions += "		"+str(inFileFullNames) + ", \n"
#      instructions += "		'"+OutFullPathFile +" ', \n"
#      instructions += "		"+str(variables) + ", \n"
#      instructions += "		"+str(columns) + ", \n"
#      instructions += "		"+str(definitions) + ", \n"
#      instructions += "		"+str(cuts) + ", \n"
#      instructions += "		'"+supercut + "', \n"
#      instructions += "		"+str(nuisances) + ", \n"
#      instructions += "		"+ isFirstJob + ") \n"
#      jobs.AddPy(instructions)
#
#      # submit jobs when ONE queue 
#      if not opt.multiQueue: jobs.Sub()
#
#      # make ONE shell script and ONE submit.jds here for MULTIPLE queue case
#      if opt.multiQueue and it_job == len(FileRanges)-1: 
#        jobs.mkShCommand()
#        jobs.mkJds(opt.ConcurrencyLimit,it_job+1)
#        jobs.Sub()
#
#      #cmd = thisjob_dir+'commands.sh'
#      #if opt.dry_run:
#      #  print 'command is',cmd
#      #elif not opt.doBatch:
#      #  print 'excuting',cmd
#      #  logfile=open('mylog.log','w')
#      #  process = subprocess.Popen(cmd, shell=True,stdout=logfile,stderr=logfile)
#      #  process.wait()
#      #  status = process.returncode
#      #  #os.system('sh '+cmd)
#      #else:
#      #  pass
#    elif not opt.doHadd:
#      print 'mkShape: histo making in interactive is not ready, use dry_run in doBatch for the test, exiting'
#      exit()
#      pass
#      #print "======== Running mkShape in interactive mode ======="
#      #factory = ShapeFactory()
#      #factory._treeName = opt.treeName
#      #factory.makeNominals(inFileFullNames,OutFullPathFile,variables, cuts,supercut, weight)
#
#  if CheckTotalNFile != NTotalFiles:
#    print 'mkShapes: CheckTotalNFile is not the same to NTotalFiles, plz check, exitting...'
#    exit()
#
#  isFirstSample = False
#
#
#if opt.doHadd:
#  print "let's collect them all"
#  if opt.dry_run:
#    print haddAllSample_cmd
#  else:
#    os.system(haddAllSample_cmd)
#
#print 'All done, bye!!!'
#


