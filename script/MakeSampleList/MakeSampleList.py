#!/usr/bin/env python

import os
import argparse

parser = argparse.ArgumentParser(description='MakeSampleList')
parser.add_argument('--base', dest='base', default='')
parser.add_argument('--sample', dest='sample', default='')
parser.add_argument('--alias', dest='alias', default='')

args = parser.parse_args()

if args.base=='' or args.sample=='' or args.alias=='':
  raise RuntimeError('insufficient arguments')

dirPath = args.base + args.sample
if not os.path.isdir(dirPath):
  raise RuntimeError('directory is not exist  : %s'%dirPath)

outFileName='%s.txt'%(args.alias)
outFile = open(outFileName,'w')
for dirName, subdirList, fileList in os.walk(dirPath):
  for aFile in fileList:
    if '.root' in aFile:
      fileFullPathName = dirName+'/'+aFile
      outFile.write(fileFullPathName+'\n')
    print('processing:  %s'%aFile)
outFile.close()
print('close : %s'%outFileName)


