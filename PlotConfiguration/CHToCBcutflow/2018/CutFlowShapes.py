import ROOT
from ROOT import TFile
import os
from collections import OrderedDict
from CommonPyTools.DataSample.SampleDef import *
import CommonPyTools.python.CommonTools as Tools

SKFlatV = os.getenv("SKFlatV")
SkimBaseDir = os.getenv("")

class CutFlowShapes():

  def __init__(self):
    pass


  def loadCfg(self,cfgName):
    configPath = cfgName
    handle = open(configPath)
    exec(handle)
    handle.close()
    self.Category = Category
    self.Year = Year
    self.InSkim = InSkim
    self.Userflags = Userflags
    self.sampleCfg = sampleCfg
    self.variableCfg = variableCfg
    self.cutCfg = cutCfg
    ###
    self.shapeDir = "Shape_%s"%self.Userflags
    ###
    self.loadSamples()
    self.loadVariables()
    self.loadCuts()


  def loadSamples(self):
    samples = OrderedDict()
    handle = open(self.sampleCfg)
    exec(handle)
    handle.close()
    self.samples = samples


  def loadVariables(self):
    variables = OrderedDict()
    handle = open(self.variableCfg)
    exec(handle)
    handle.close()
    self.variables = variables


  def loadCuts(self):
    cuts = OrderedDict()
    handle = open(self.cutCfg)
    exec(handle)
    handle.close()
    self.cuts = cuts


  def printout(self):
    print("\n\nprint self.samepls \n\n")
    for sample in self.samples:
      print(sample)
    print("\n\nprint self.variables \n\n")
    for variable in self.variables:
      print(variable)
    print("\n\nprint self.cuts \n\n")
    for cut in self.cuts:
      print(cut)

  def getFullNames(self, sampleAlias):
    ProductionKey = SKFlatV+'_' + self.Year
    sampleFullName,_ = Tools.GetInputSamples([sampleAlias],"ALL",self.Year,self.Category,ProductionKey)
    outDict = {}
    for key1, value1 in sampleFullName.iteritems():
      key2 = value1['key']
      value2 = key1
      if key2 in outDict:
        outDict[key2].append(value2)
      else:
        outDict[key2] = [value2]

    # {alias : [full names]}
    return outDict

  def getFullPath(self, sampleAlias):
    FullNames = self.getFullNames(sampleAlias)[sampleAlias]
    isData = False if len(FullNames)==1 else True
    ProductionKey = SKFlatV+'_' + self.Year
    baseSkimDir = Productions[self.Category][ProductionKey]['SkimDir']
    fullPath=[]
    if isData:
      for FullName in FullNames:
        dataName, period = FullName.split(":")       
        fullPath.append("%s/%s/%s/period%s/"%(baseSkimDir,self.InSkim,dataName,period))
    else:
      fullPath.append("%s/%s/%s/"%(baseSkimDir,self.InSkim,FullNames[0]))
    return fullPath


  def cpShape(self, sampleAlias):
    sampleFullPath = self.getFullPath(sampleAlias)
    isData = False if len(sampleFullPath)==1 else True
    for path in sampleFullPath:
      if isData:
	period = path.split('/')[-2]
	outfileName="%s_%s.root"%(sampleAlias,period)
      else:
        outfileName="%s.root"%(sampleAlias)
      target = "%s%s"%(path,"hadd_0.root")
      os.system("mkdir -p %s"%self.shapeDir)
      os.system("cp %s %s/%s"%(target,self.shapeDir,outfileName))
    if isData:
      os.system("hadd %s/%s.root %s"%(self.shapeDir,sampleAlias,"%s/%s_period*.root"%(self.shapeDir,sampleAlias)))

    # cp *.root files(after hadd) from skim directory
    # and change each file name to sample alias
    # for DATA, sample alias + period

  def cpShapes(self): # loop list of sample aliases
    for sample in self.samples:
      self.cpShape(sample)

  def haddShapes(self):
    # hadd each shape histograms
    # after changing histograms to be compatible with mkPlot.py
    outFilePath = "%s/Shapes_%s.root"%(self.shapeDir,self.Userflags)
    outFile = TFile(outFilePath,"RECREATE")
    #READ files
    tfileDict = {}
    th1fDict = {}
    for sample in self.samples:
      tfileDict[sample] = TFile("%s/%s.root "%(self.shapeDir,sample),"READ")
    #Clone hists
    histName = {
        # <cut> : <histogram name>, 
        "All" : "CutFlow",
	"Mu" : "CutFlow_Mu",
	"El" : "CutFlow_El",
      }
    for cut in self.cuts:
      for var in self.variables:
	# make directory
	targetDir = "%s/%s"%(cut,var)
        outFile.mkdir(targetDir)
        for sample in self.samples:
          outHistName = "histo_%s"%sample
          th1fDict[cut,var] = tfileDict[sample].Get(histName[cut]).Clone(outHistName)
	  outFile.cd(targetDir)
	  th1fDict[cut,var].Write()
          
    outFile.Close()

if __name__ == "__main__":
  c = CutFlowShapes()
  #c.loadCfg("configuration_El.py")
  c.loadCfg("configuration_Mu.py")
  c.cpShapes()
  c.haddShapes()

