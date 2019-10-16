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

  def SetTrees(self,sampleName,tree_name,inFiles):
    inputDir = ''
    # get chained ttree
    self._treeName = "%s_%s"%(sampleName,tree_name)
    trees = self._connectInputs( inFiles, inputDir, tree_name,False)
    self._tools.SetTrees(self._treeName, trees)

  def SetVariables(self, variables):
    self._tools.SetVariables(variables)

  def SetCuts(self,cuts):
    self._tools.SetCuts(cuts)

  def SetOptions(self,options):
    self._tools.SetOptions(options)
    
  def doTrain(self,sigTreeName,bkgTreeName,outWeightsSuffix,outFileName,epoch=1):
    self._tools.doTrain(sigTreeName,bkgTreeName,outFileName,epoch)
    os.system('mv TMVAClassification/weights TMVAClassification/weights_%s'%(outWeightsSuffix))

  def doTest(self):
    self._tools.doTest()

  def _connectInputs(self, inFiles, inputDir, tree_name, skipMissingFiles, friendsDir = None, skimListDir = None):
    tree = TChain(tree_name)
    for aFile in inFiles:
      tree.Add(aFile)
    return tree

