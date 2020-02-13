import ROOT
from ROOT import TFile
import os
import argparse

def GetHistPath(selection,variable,sample):
  return '%s/%s/histo_%s'%(selection,variable,sample)

parser = argparse.ArgumentParser(description='ABCDMethod')
parser.add_argument('--base', dest='base', default='')
parser.add_argument('--pycfg', dest='pycfg', default='')
parser.add_argument('--inputFile', dest='inputFile', default='')
parser.add_argument('--outFile', dest='outFile', default='')
parser.add_argument('--channel', dest='ch', default='')

args = parser.parse_args()

if args.base=='' or args.pycfg=='' or args.inputFile=='':
  raise RuntimeError('insufficient arguments')

handle='%s/%s'%(args.base, args.pycfg)
exec(open(handle).read())

cuts={}
handle='%s/%s'%(args.base, cutsFile)
exec(open(handle).read())

variables={}
handle='%s/%s'%(args.base, variablesFile)
exec(open(handle).read())

samples={}
handle='%s/%s'%(args.base, samplesFile)
exec(open(handle).read())

plot={}
groupPlot={}
legend={}
handle='%s/%s'%(args.base, plotFile)
exec(open(handle).read())

filePath = '%s/%s'%(args.base, args.inputFile)
inputFile = TFile(filePath,'READ')
outFile = TFile(args.outFile,'RECREATE')

selection_region = ['Mu2b', 'Mu3b', 'El2b', 'El3b']

rebin_th1f={}
normalization_th1f={}
outFile.cd()
#outFile.mkdir("Shape")

for sel in selection_region:
  
  if not str(args.ch) in sel:
    continue

  if 'Mu' in sel:
    data = 'SingleMuon'
    xvar = 'lepton_eta'
    nbins = 6
    bins = [-2.4, -1.8, -1.5, 0, 1.5, 1.8, 2.4] #variable bin size is not available yet
  elif 'El' in sel:
    data = 'SingleElectron'
    #data = 'EGamma'
    xvar = 'electron_scEta'
    nbins = 6
    bins = [-2.5,-1.8,-1.5,0,1.5,1.8,2.5] #variable bin size is not available yet

  th1f_A = inputFile.Get(GetHistPath('_'.join([sel,'A']), xvar, data))
  histName="%s_%s_%s"%(sel,'%s',xvar)
  #histName.replace('lepton_eta','muon_eta') #XXX be careful, this line possibly cause error
  rebin_th1f[histName%'A'] = th1f_A.Rebin(10,histName%'A')
  th1f_B = inputFile.Get(GetHistPath('_'.join([sel,'B']), xvar, data))
  rebin_th1f[histName%'B'] = th1f_B.Rebin(10,histName%'B')
  '''
  for variable in variables:
    th1f_C = inputFile.Get(GetHistPath('_'.join([sel,'C']), variable, data))
    histName="%s_%s_%s"%(sel,'%s',variable)
    rebin_th1f[histName%'C'] = th1f_C.Clone(histName%'C')
  '''
  for key, val in plot.iteritems():
    if val['isSignal']==1:
      continue
    if val['isData']==1:
      continue
       
    histName="%s_%s_%s"%(sel,'%s',xvar)
    #histName.replace('lepton_eta','muon_eta') #XXX be careful, this line possibly cause error
    print(key)
    th1f_A = inputFile.Get(GetHistPath('_'.join([sel,'A']), xvar, key))
    rebin_th1f[histName%'A'].Add(th1f_A.Rebin(10,histName%'A'+"_%s"%key), -1)
    th1f_B = inputFile.Get(GetHistPath('_'.join([sel,'B']), xvar, key))
    rebin_th1f[histName%'B'].Add(th1f_B.Rebin(10,histName%'B'+"_%s"%key), -1)

  '''
    for variable in variables:
      th1f_C = inputFile.Get(GetHistPath('_'.join([sel,'C']), variable, key))
      histName="%s_%s_%s"%(sel,'%s',variable)
      rebin_th1f[histName%'C'].Add(th1f_C, -1)
  outFile.cd()
  outFile.cd("Shape")
  rebin_th1f[histName%'C'].Write()
  print("write %s"%(histName%'C'))
  '''

  histName="%s_%s_%s"%(sel,'%s',xvar)
  #histName.replace('lepton_eta','muon_eta') #XXX be careful, this line possibly cause error
  normalization_th1f[histName%"AoverB"] = rebin_th1f[histName%'A'].Clone(histName%"AoverB")
  normalization_th1f[histName%"AoverB"].Divide(rebin_th1f[histName%'B'])
  outFile.cd()

  normalization_th1f[histName%"AoverB"].Write()
  print("write %s"%(histName%'AoverB'))

# ABCD Shape

