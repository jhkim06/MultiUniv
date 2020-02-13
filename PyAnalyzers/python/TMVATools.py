from ROOT import TFile, TTree, TCut, TMVA, gROOT

#------
# ver.1
#-----
# what to imporve:
# 3 class of options factory, prepare trees, book MVA methods
# apply weights

class TMVATools():



  def __init__(self):
    gROOT.SetBatch()
    TMVA.Tools.Instance()
    TMVA.PyMethodBase.PyInitialize()
    self._trees = {}
    self._fout = None
    self._variables = {}
    self._cuts = {}
    self._options = {}


  def SetTrees(self,treeName,trees):
    self._trees[treeName] = trees


  def SetVariables(self,variables):
    self._variables = variables


  def SetCuts(self,cuts):
    self._cuts = cuts


  def SetOptions(self,options):
    self._options = options


  def _setFactory(self,outFileName):
    self._fout = TFile(outFileName,"RECREATE")
    self._factory = TMVA.Factory(self._options['factory']['name'],
		                 self._fout,
				 self._options['factory']['options']
                                )


  def _dataLoader(self,sigTreeNames,bkgTreeNames):
    self._data_loader = TMVA.DataLoader(self._options['factory']['name'])
    for value in self._variables.values():
      self._data_loader.AddVariable(value['name'],value['type'])
    #----
    for sigTreeName in sigTreeNames:
      self._data_loader.AddSignalTree(self._trees[sigTreeName+"_Train"],1.0,"train")
      self._data_loader.AddSignalTree(self._trees[sigTreeName+"_Test"],1.0,"test")
    for bkgTreeName in bkgTreeNames:
      self._data_loader.AddBackgroundTree(self._trees[bkgTreeName+"_Train"],1.0,"train")
      self._data_loader.AddBackgroundTree(self._trees[bkgTreeName+"_Test"],1.0,"test")
    self._data_loader.SetSignalWeightExpression(self._options['factory']['weight'])
    self._data_loader.SetBackgroundWeightExpression(self._options['factory']['weight'])
    #----
    self._data_loader.PrepareTrainingAndTestTree(TCut(self._cuts['sig']),
		                                TCut(self._cuts['bkg']),
                                                self._options['prepareTrees']
			        	       )


  def _bookMethod(self):
    for method in self._options['bookMethod']:
      self._factory.BookMethod(self._data_loader,
	  	               method['type'],
		               method['name'],
			       method['options']
			       )


  def doTrain(self,sigTreeNameList,bkgTreeNameList,outWeightsSuffix,outFileName,epoch=1):
    self._setFactory(outFileName)
    self._dataLoader(sigTreeNameList,bkgTreeNameList)
    self._bookMethod()
    self._factory.TrainAllMethods()
    self._factory.TestAllMethods()
    self._factory.EvaluateAllMethods()
    self._getSignalReferenceCut(outWeightsSuffix)


  def doTest(self):
    pass

  def _getSignalReferenceCut(self,outWeightsSuffix):
    fOut = open('signal_reference_cut.txt','a')
    for method in self._options['bookMethod']:
      cut = self._factory.GetMethod(self._options['factory']['name'], method['name']).GetSignalReferenceCut()
      out = "%s_%s		%s\n"%(method['name'],outWeightsSuffix,cut)
      fOut.write(out)

    fOut.close()
