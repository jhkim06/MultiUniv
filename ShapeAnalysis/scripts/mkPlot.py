#!/usr/bin/env python

import os, sys
import ROOT
import logging
import argparse
from collections import OrderedDict

import CommonPyTools.python.CommonTools as Tools
from ShapeAnalysis.python.PlotFactory import PlotFactory

print '''
-----------------------------------------------------------------------------------------
                                                         
  _____  _       _     __  __       _               _    _       _           _           
 |  __ \| |     | |   |  \/  |     | |             | |  | |     | |         | |          
 | |__) | | ___ | |_  | \  / | __ _| | _____ _ __  | |__| | __ _| |__   __ _| |__   __ _ 
 |  ___/| |/ _ \| __| | |\/| |/ _` | |/ / _ \ '__| |  __  |/ _` | '_ \ / _` | '_ \ / _` |
 | |    | | (_) | |_  | |  | | (_| |   <  __/ |    | |  | | (_| | | | | (_| | | | | (_| |
 |_|    |_|\___/ \__| |_|  |_|\__,_|_|\_\___|_|    |_|  |_|\__,_|_| |_|\__,_|_| |_|\__,_|
	                                                                                          
-----------------------------------------------------------------------------------------

'''


parser = argparse.ArgumentParser(description='SKFlat Command')
parser.add_argument('--InSkim', dest='InSkim', default="")
parser.add_argument('--dry_run', action='store_true')
parser.add_argument('--doBatch', action='store_true')
parser.add_argument('--userflags', dest='Userflags', default="test")
parser.add_argument('--skimV', dest='skimV', default="0")
parser.add_argument('--nTotFiles', dest='nTotFiles', default=0, type=int)
parser.add_argument('--Category', dest='Category', default="SMP")
parser.add_argument('--treeName', dest='treeName', default="")

parser.add_argument('--scaleToPlot'    , dest='scaleToPlot'    , help='scale of maxY to maxHistoY'                 , default=2.0  ,    type=float   )
parser.add_argument('--minLogC'        , dest='minLogC'        , help='min Y in log plots'                         , default=0.01  ,    type=float   )
parser.add_argument('--maxLogC'        , dest='maxLogC'        , help='max Y in log plots'                         , default=100   ,    type=float   )
parser.add_argument('--minLogCratio'   , dest='minLogCratio'   , help='min Y in log ratio plots'                   , default=0.001 ,    type=float   )
parser.add_argument('--maxLogCratio'   , dest='maxLogCratio'   , help='max Y in log ratio plots'                   , default=10    ,    type=float   )
parser.add_argument('--maxLinearScale' , dest='maxLinearScale' , help='scale factor for max Y in linear plots (1.45 magic number as default)'     , default=1.45   ,    type=float   )
parser.add_argument('--outputDirPlots' , dest='outputDirPlots' , help='output directory'                           , default='./')
parser.add_argument('--inputFile'      , dest='inputFile'      , help='input file with histograms'                 , default='input.root')
		    
parser.add_argument('--onlyVariable'   , dest='onlyVariable'   , help='draw only one variable (may be needed in post-fit plots)'          , default=None)
parser.add_argument('--onlyCut'        , dest='onlyCut'        , help='draw only one cut phase space (may be needed in post-fit plots)'   , default=None)
     
parser.add_argument('--plotNormalizedDistributions'  , dest='plotNormalizedDistributions'  , help='plot also normalized distributions for optimization purposes'         , default=None )
parser.add_argument('--showIntegralLegend'           , dest='showIntegralLegend'           , help='show the integral, the yields, in the legend'                         , default=0,    type=float )
               
parser.add_argument('--showRelativeRatio'   , dest='showRelativeRatio'   , help='draw instead of data-expected, (data-expected) / expected' ,    action='store_true', default=False)
parser.add_argument('--showDataMinusBkgOnly', dest='showDataMinusBkgOnly', help='draw instead of data-expected, data-expected background only' , action='store_true', default=False)
						          
parser.add_argument('--removeWeight', dest='removeWeight', help='Remove weight S/B for PR plots, just do the sum' , action='store_true', default=False)
										      
parser.add_argument('--invertXY', dest='invertXY', help='Invert the weighting for X <-> Y. Instead of slices along Y, do slices along X' , action='store_true', default=False)
											  
parser.add_argument('--postFit', dest='postFit', help='Plot sum of post-fit backgrounds, and the data/post-fit ratio.' , default='n') 



ROOT.gROOT.SetBatch()

Tools.AddOptions(parser)
Tools.LoadOptDefaults(parser)
opt = parser.parse_args()


print ""
print "          configuration file =", opt.pycfg
print "                        lumi =", opt.lumi
print "                   inputFile =", opt.inputFile
print "              outputDirPlots =", opt.outputDirPlots
print " plotNormalizedDistributions =", opt.plotNormalizedDistributions
print "          showIntegralLegend =", opt.showIntegralLegend
print "                 scaleToPlot =", opt.scaleToPlot
print "                     minLogC =", opt.minLogC
print "                     maxLogC =", opt.maxLogC
print "                minLogCratio =", opt.minLogCratio
print "                maxLogCratio =", opt.maxLogCratio
print "           showRelativeRatio =", opt.showRelativeRatio
print "        showDataMinusBkgOnly =", opt.showDataMinusBkgOnly
print "                removeWeight =", opt.removeWeight
print "                    invertXY =", opt.invertXY    
print "                    postFit  =", opt.postFit
print ""

opt.scaleToPlot = float(opt.scaleToPlot)
opt.minLogC = float(opt.minLogC)
opt.maxLogC = float(opt.maxLogC)

opt.minLogCratio = float(opt.minLogCratio)
opt.maxLogCratio = float(opt.maxLogCratio)

if not opt.debug:
  pass
elif opt.debug == 2:
  print 'Logging level set to DEBUG (%d)' % opt.debug
  logging.basicConfig( level=logging.DEBUG )
elif opt.debug == 1:
  print 'Logging level set to INFO (%d)' % opt.debug
  logging.basicConfig( level=logging.INFO )

Userflags = []
if opt.Userflags != "":
  Userflags = (opt.Userflags).split(',')

IsFirstFlag = True
tag=''
for flag in Userflags:
  if IsFirstFlag:
    tag = flag
  else:
    tag += '_'+flag 
print tag

factory = PlotFactory()
factory._tag = tag
factory._lumi = opt.lumi
factory._plotNormalizedDistributions = opt.plotNormalizedDistributions
factory._showIntegralLegend = opt.showIntegralLegend
	    
factory._scaleToPlot = opt.scaleToPlot 
factory._minLogC = opt.minLogC 
factory._maxLogC = opt.maxLogC 
factory._minLogCratio = opt.minLogCratio
factory._maxLogCratio = opt.maxLogCratio
factory._maxLinearScale = opt.maxLinearScale

factory._minLogCdifference = opt.minLogCratio
factory._maxLogCdifference = opt.maxLogCratio

factory._showRelativeRatio = opt.showRelativeRatio
factory._showDataMinusBkgOnly = opt.showDataMinusBkgOnly

factory._removeWeight = opt.removeWeight

factory._invertXY = opt.invertXY

factory._postFit = opt.postFit

samples = OrderedDict()
if os.path.exists(opt.samplesFile):
  handle = open(opt.samplesFile,'r')
  exec(handle)
  handle.close()
else:
  print 'You should have sample configuration file,  exiting...'
  exit()

supercut = '1'
cuts = {}
if os.path.exists(opt.cutsFile):
  handle = open(opt.cutsFile,'r')
  exec(handle)
  handle.close()
else:
  print 'You should have cut configuration file,  exiting...'
  exit()


variables = {}
columns = []
if os.path.exists(opt.variablesFile):
  handle = open(opt.variablesFile,'r')
  exec(handle)
  #exec(handle,globals())
  handle.close()
else:
  print 'You should have variable configuration file,  exiting...'
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
if os.path.exists(opt.nuisancesFile):
  handle = open(opt.nuisancesFile,'r')
  exec(handle)
  #exec(handle,globals())
  handle.close()
else:
  print 'Warning: there is no nuisancesFile.'




if opt.onlyVariable != None :
  list_to_remove = []
  for variableName, variable in variables.iteritems():
    if variableName != opt.onlyVariable :
      list_to_remove.append(variableName)
  for toRemove in list_to_remove:
    del variables[toRemove]
  print " variables = ", variables


if opt.onlyCut != None :
  list_to_remove = []
  for cutName, cutExtended in cuts.iteritems():
    if cutName != opt.onlyCut :
      list_to_remove.append(cutName)
  for toRemove in list_to_remove:
    del cuts[toRemove]
  print  " cuts = ", cuts

factory.makePlot(opt.inputFile,opt.outputDirPlots, variables, cuts, samples, plot, nuisances, legend, groupPlot)

print 'Now closing......, Bye!'
