
import os,sys
import logging
from ROOT import TFile, RDataFrame, TH1D, gROOT, TChain, vector
SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

class ShapeFactory:
  _logger = logging.getLogger('ShapeFactory')
  
  def __init__(self):

    self._inFiles =[] 

    self._variables = {}

    self._cuts = {}

    self._treeName = "recoTree/SKFlat"

  def __del__(self):
    pass

  def getvariable(self, tag, mass, cat):
    if tag in self._variables:
      try:
	theVariable = (self._variables[tag])(mass,cat)
      except KeyError as ke:
	self._logger.error('Variable '+tag+' not available. Possible values: '+', '.join(self._variables.iterkeys()) )
	raise ke
    else:
      theVariable = tag

    return theVariable

  def makeNominals(self,sample, inFiles, outFile, variables,columns, cuts, supercut, weight):
    print "===================="
    print "=== makeNominals ==="
    print "===================="
    gROOT.SetBatch()

    self._sample   = sample
    self._inFiles   = inFiles
    self._variables = variables
    self._cuts      = cuts

    #print 'ShapeFactory:sample',self._sample
    #print 'ShapeFactory:inFiles',self._inFiles
    #print 'ShapeFactory:outFile',self._outFile
    #print 'ShapeFactory:variables',self._variables
    #print 'ShapeFactory:cuts',self._cuts
    print 'ShapeFactory:supercut',supercut
    print 'ShapeFactory:weight', weight

    #in case some variables need a compiled function
    for variableName, variable in self._variables.iteritems():
      if variable.has_key('linesToAdd'):
	linesToAdd = variable['linesToAdd']
	for line in linesToAdd:
	  ROOT.gROOT.ProcessLineSync(line)
    
    TH1D.SetDefaultSumw2(True)
    self.outFile = TFile(outFile,'recreate')

 
    #print 'ShapeFactory',self._treeName
    chain = TChain(self._treeName)
    for infile in inFiles:
      #print 'ShapeFactory: infile',infile
      chain.AddFile(infile)
    RDF = RDataFrame
    #print columns
    if 'ALL' in columns:
      D = RDF(chain)
    else:
      v_columns = vector('string')()
      for column in columns:
	print 'colmumn:',column
	v_columns.push_back(column)
      D = RDF(chain,v_columns)

    D_weighted = D.Define('totW',weight)
    for cutName, cut in self._cuts.iteritems():
      cut = cut+"&&"+supercut
      print 'cut',cutName,'::',cut
      self.outFile.mkdir(cutName)
      for varName, var in variables.iteritems():
	self.outFile.mkdir(cutName+"/"+varName)
	self.outFile.cd(cutName+"/"+varName)
        print varName
        print 'var[name]', var['name']
	print 'var[range]', var['range'][0],':', var['range'][1],':', var['range'][2]
	#augmented_d = d.Define('totW',str(weight)) \
	#augmented_d = d.Define('totW','baseW') 
	#               #.Filter(cut)
        #basicCut = 'diLep_Ch =='+str(1)

        #augmented_d = d.Define('totW','baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor') \
        #               .Filter(basicCut) 
	#hist = augmented_d.Histo1D('haha','haha','120','50','120','diLep_m','totW')

	#hist.Write()
        #basicCut = 'diLep_Ch =='+str(DiLepCh.ElElOS)
        #augmented_d = d.Define('totW',weight) \
        #               .Filter(cut) 
        #
	hstName = 'histo_'+ self._sample
	hist = D_weighted.Filter(cut).Histo1D((hstName,hstName,var['range'][0],var['range'][1],var['range'][2]),var['name'],'totW')
	hist.SetXTitle(var['xaxis'])

	hist.Write()

        #hist = d.Filter(basicCut).Histo1D(("","",50,60,120),'diLep_m','baseW*PUweight*trgSF*recoSF*IdSF*IsoSF*ZPtCor')
        #histList = {'diLep_m':{'Nbin':50,'bin1':60, 'bin2': 120},\
        #    'diLep_pt':{'Nbin':50,'bin1':0,'bin2':150},'diLep_eta':{'Nbin':50,'bin1':-3.14,'bin2':3.14}, \
        #    'nPV':{'Nbin':50,'bin1':0,'bin2':50}}
        #for title in histList:
        #  hist = augmented_d.Histo1D((title,title,var['range'][0],var['range'][1],var['range'][2]),title,'totW')
        #  hist.Write()

    self.outFile.Close()
    



