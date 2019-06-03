#!/usr/bin/env python

import argparse

parser = argparse.ArgumentParser(description='MakeSampleDict')
parser.add_argument('--in', dest='infile', default='')
parser.add_argument('--out', dest='out', default='')

args = parser.parse_args()

if args.infile=='' or args.out=='':
  raise RuntimeError('insufficient arguments')

with open(args.out, 'w') as f_out:
  f_out.write('# alias PD xsec nmc sumw\n')
  f_out.write('sampleInfo = {\n')
  with open(args.infile, 'r') as f_in:
    for line_ in f_in:
      if '#' in line_:
        continue
      line = line_.rstrip('\n')
      elements = line.split()
      if len(elements)!=5:
	print('skip this line:')
	pirnt(line)
        continue
      print(elements)
      print(tuple(elements))
      f_out.write("'%s'		:{'name' :'%s',	'xsec': %s,	'nMC':%s,	'Nsum': %s },\n"%tuple(elements))
  f_out.write("}\n")
