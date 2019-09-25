import ROOT as rt
from ROOT import TFile, TTree, TChain

import os,sys
import logging
import CommonPyTools.python.CommonTools as common_tools
import CommonPyTools.python.getEvn


class MLTools():

  def __init__(self):
    self._tools = None

  def __del__(self):
    pass

  def SetMLTools(self,tools):
    self._tools = tools()

  def SetTrees(self,sampleName,label,inFiles):
    inputDir = ''
    # get chained ttree
    self._treeName = "%s_%s"%(sampleName,label)
    trees = self._connectInputs( inFiles, inputDir, False)
    self._tools.SetTrees(self._treeName, trees)

  def SetVariables(self, variables):
    self._tools.SetVariables(variables)

  def SetCuts(self,cuts):
    self._tools.SetCuts(cuts)

  def SetOptions(self,options):
    self._tools.SetOptions(options)
    
  def doTrain(self,sigTreeName,bkgTreeName,epoch=1):
    self._tools.doTrain(sigTreeName,bkgTreeName,epoch)

  def doTest(self):
    self._tools.doTest()

  def _connectInputs(self, inFiles, inputDir, skipMissingFiles, friendsDir = None, skimListDir = None):
    tree = TChain('recoTree/SKFlat')
    for aFile in inFiles:
      tree.Add(aFile)
    return tree
    #listTrees = []
    #for aFile in samples :
    #  tree = TChain(self._treeName)
    #  tree.AddFile(aFile)
    #  listTrees.append(tree)

    #return listTrees




