#!/usr/bin/env python

import os
import argparse
import ROOT
from ROOT import TFile, TTree

parser = argparse.ArgumentParser(description='MakeSampleSummary')
parser.add_argument('--alias', dest='alias', default='')
parser.add_argument('--sample', dest='sample', default='')
parser.add_argument('--xsec', dest='xsec', default='')
parser.add_argument('--nmc', dest='nmc', default='')
parser.add_argument('--out', dest='out', default='')

args = parser.parse_args()

if args.alias=='' or args.sample=='' or args.out=='':
  print(args.alias)
  print(args.sample)
  print(args.out)
  raise RuntimeError('insufficient arguments')

inputFileName=args.alias+'.txt'
if not os.path.isfile(inputFileName):
  raise RuntimeError('file is not exist  : %s'%args.alias)
inputFile = open(inputFileName,'r')

outFileName=args.out
if os.path.isfile(outFileName):
  outFile = open(outFileName,'a')
  print('open :     %s'%inputFileName)
else:
  outFile = open(outFileName,'a')
  print('open :     %s'%inputFileName)
  outFile.write('# alias PD xsec nmc sumw\n')
  
sumw=0
for line in inputFile:
  filePath = line.rstrip('\n')
  f = TFile(filePath)
  t = f.Get('recoTree/SKFlat')
  sumw += t.GetEntries()
  print(filePath)

if args.nmc=='':
  nmc=sumw
else:
  nmc=args.nmc

outFile.write('%s  %s  %s  %s  %s\n'%(args.alias,
	                            args.sample,
				    args.xsec,
				    nmc,
				    sumw
				   ))

outFile.close()
inputFile.close()

