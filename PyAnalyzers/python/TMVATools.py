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


  def _setFactory(self):
    self._fout = TFile(self._options['factory']['outfile'],"RECREATE")
    self._factory = TMVA.Factory(self._options['factory']['name'],
		                 self._fout,
				 self._options['factory']['options']
                                )
  def _dataLoader(self,sigTreeName,bkgTreeName):
    self._data_loader = TMVA.DataLoader(self._options['factory']['name'])
    for value in self._variables.values():
      self._data_loader.AddVariable(value['name'],value['type'])
    #----
    self._data_loader.AddSignalTree(self._trees[sigTreeName])
    self._data_loader.AddBackgroundTree(self._trees[bkgTreeName])
    #----
    self._data_loader.PrepareTrainingAndTestTree(TCut(self._cuts['sig']),
		                                TCut(self._cuts['bkg']),
                                                self._options['prepareTrees']
			        	       )


  def _bookMethod(self):
    self._factory.BookMethod(self._data_loader,
		             self._options['bookMethod']['type'],
		             self._options['bookMethod']['name'],
			     self._options['bookMethod']['options']
			    )

  def doTrain(self,sigTreeName,bkgTreeName,epoch=1):
    self._setFactory()
    self._dataLoader(sigTreeName,bkgTreeName)
    self._bookMethod()
    self._factory.TrainAllMethods()
    self._factory.TestAllMethods()
    self._factory.EvaluateAllMethods()

  def doTest(self):
    pass
