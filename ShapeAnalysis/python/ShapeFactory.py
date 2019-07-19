
import os,sys
import logging
import math 
from ROOT import TFile, TH1D, TH2, TH2D, gROOT, TChain, vector
import ROOT as rt
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

  def makeNominals(self, sampleName, sample, inFiles, outFile, variables, columns, definitions, cuts, supercut, nuisances):
    print "===================="
    print "=== makeNominals ==="
    print "===================="
    gROOT.SetBatch()

    # only one sample dilivered for now
    self._inFiles   = inFiles
    self._variables = variables
    self._cuts      = cuts
    self._definitions = definitions

    #print 'ShapeFactory:sample',self._sample
    #print 'ShapeFactory:inFiles',self._inFiles
    #print 'ShapeFactory:outFile',self._outFile
    #print 'ShapeFactory:variables',self._variables
    #print 'ShapeFactory:cuts',self._cuts
    print 'ShapeFactory:supercut',supercut

    #in case some variables need a compiled function
    for variableName, variable in self._variables.iteritems():
      if variable.has_key('linesToAdd'):
	linesToAdd = variable['linesToAdd']
	for line in linesToAdd:
	  gROOT.ProcessLineSync(line)
    
    TH1D.SetDefaultSumw2(True)
    TH2D.SetDefaultSumw2(True)

    self.outFile = TFile(outFile,'recreate')
 
    #print 'ShapeFactory',self._treeName
    #chain = TChain(self._treeName)
    #                                                         skipMissingFiles
    inputDir = ''
    #print 'inFiles', inFiles
    trees = self._connectInputs( inFiles, inputDir, False)
    for cutName, cut in self._cuts.iteritems():
      totCut = cut+"&&"+supercut
      print 'cut',cutName,'::',cut
      self.outFile.mkdir(cutName)
      for variableName, variable in variables.iteritems():
	self.outFile.mkdir(cutName+"/"+variableName)
	self.outFile.cd(cutName+"/"+variableName)
        print variableName
        print " variable[name] = ", variable['name']

	doFold = 0
	if 'fold' in variable.keys() :
	  print "       variable[fold] = ", variable['fold']
	  doFold = variable['fold']

        go1D = False
        if 'go1D' in variable.keys() :
          print "       variable[go1D] = ", variable['go1D']
          go1D = variable['go1D']

        useTUnfoldBin = False
        if 'useTUnfoldBin' in variable.keys() :
          print "       variable[useTUnfoldBin] = ", variable['useTUnfoldBin']
          useTUnfoldBin = variable['useTUnfoldBin']

        unfoldBinType  = None
        if 'unfoldBinType' in variable.keys() :
          print "       variable[unfoldBinType] = ", variable['unfoldBinType']
          unfoldBinType = variable['unfoldBinType']

	
	# create histogram
	if 'weights' in sample.keys() :
	  outputsHisto = self._draw( variable['name'], variable['range'], sample['weight'], sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True, go1D, useTUnfoldBin, unfoldBinType)
	else :
	  outputsHisto = self._draw( variable['name'], variable['range'], sample['weight'], [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True, go1D, useTUnfoldBin, unfoldBinType)

	outputsHisto.Write()

 
        # weight based nuisances: kind = weight
	for nuisanceName, nuisance in nuisances.iteritems():
	  if ('cuts' not in nuisance) or ( ('cuts' in nuisance) and (cutName in nuisance['cuts']) ) :
	    if 'kind' in  nuisance :
	      if nuisance['kind'] == 'weight' :
		for sampleNuisName, configurationNuis in nuisance['samples'].iteritems() :
		  if sampleNuisName ==  sampleName :
		    newSampleNameUp = sampleName + '_' + nuisance['name'] + 'Up'
		    newSampleNameDo = sampleName + '_' + nuisance['name'] + 'Down'
		    #                                 the first weight is "up", the second is "down"
		    newSampleWeightUp = sample['weight'] + '* (' + configurationNuis[0]  + ")"
		    newSampleWeightDo = sample['weight'] + '* (' + configurationNuis[1]  + ")"

		    if 'weights' in sample.keys() :
		      outputsHistoUp = self._draw( variable['name'], variable['range'], newSampleWeightUp, sample['weights'], totCut, newSampleNameUp, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType)
		      outputsHistoDo = self._draw( variable['name'], variable['range'], newSampleWeightDo, sample['weights'], totCut, newSampleNameDo, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType)
		    else :
		      #print 'newSampleWeightUp', newSampleWeightUp
		      outputsHistoUp = self._draw( variable['name'], variable['range'], newSampleWeightUp, [],                totCut, newSampleNameUp, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType)
		      outputsHistoDo = self._draw( variable['name'], variable['range'], newSampleWeightDo, [],                totCut, newSampleNameDo, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType)

		    outputsHistoUp.Write()
		    outputsHistoDo.Write()

	      elif nuisance['kind'] == 'variableChange' :
                if variableName not in nuisance['variablesUp'] and variableName not in nuisance['variablesDo'] :
	          continue 
		if variableName in nuisance['variablesUp']:
		  newVariableNameUp = nuisance['variablesUp'][variableName]
		else:
		  newVariableNameUp = None
		if variableName in nuisance['variablesDo']:
		  newVariableNameDo = nuisance['variablesDo'][variableName]
		else:
		  newVariableNameDo = None

		for sampleNuisName, configurationNuis in nuisance['samples'].iteritems() :
		  if sampleNuisName ==  sampleName :
		    #                                 the first weight is "up", the second is "down"
		    newSampleWeightUp = sample['weight'] + '* (' + configurationNuis[0]  + ")"
		    newSampleWeightDo = sample['weight'] + '* (' + configurationNuis[1]  + ")"

		    for k, v in nuisance['variablesUp'].iteritems():
		      totCutUp = totCut.replace(variables[k]['name'],v[1])
		      
		    for k, v in nuisance['variablesDo'].iteritems():
		      totCutDo = totCut.replace(variables[k]['name'],v[1])

		    if 'weights' in sample.keys() :
		      if not newVariableNameUp==None:
		        outputsHistoUp = self._draw( newVariableNameUp[1], variable['range'], newSampleWeightUp, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, newVariableNameUp[0], sample, False, go1D, useTUnfoldBin, unfoldBinType)
		      if not newVariableNameDo==None:
		        outputsHistoDo = self._draw( newVariableNameDo[1], variable['range'], newSampleWeightDo, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, newVariableNameDo[0], sample, False, go1D, useTUnfoldBin, unfoldBinType)
		    else :
		      #print 'newSampleWeightUp', newSampleWeightUp
		      if not newVariableNameUp==None:
		        outputsHistoUp = self._draw( newVariableNameUp[1], variable['range'], newSampleWeightUp, [],                totCut, sampleName, trees, columns, doFold, cutName, newVariableNameUp[0], sample, False, go1D, useTUnfoldBin, unfoldBinType)
		      if not newVariableNameDo==None:
		        outputsHistoDo = self._draw( newVariableNameDo[1], variable['range'], newSampleWeightDo, [],                totCut, sampleName, trees, columns, doFold, cutName, newVariableNameDo[0], sample, False, go1D, useTUnfoldBin, unfoldBinType)

		    if not newVariableNameUp==None:
	              self.outFile.mkdir(cutName+"/"+newVariableNameUp[0])
	              self.outFile.cd(cutName+"/"+newVariableNameUp[0])
		      outputsHistoUp.Write()
	              self.outFile.cd(cutName+"/"+variableName)
		    if not newVariableNameDo==None:
	              self.outFile.mkdir(cutName+"/"+newVariableNameDo[0])
	              self.outFile.cd(cutName+"/"+newVariableNameDo[0])
		      outputsHistoDo.Write()
	              self.outFile.cd(cutName+"/"+variableName)

	      elif nuisance['kind' ] == 'PDF' :
		for sampleNuisName, configurationNuis in nuisance['samples'].iteritems() :
		  if sampleNuisName ==  sampleName :
		    newSampleName = sampleName + '_' + nuisance['name'] 

		    if 'weights' in sample.keys() :
		      histoList = self._drawPDF(nuisance['type'], configurationNuis[0], variable['name'], variable['range'], sample['weight'], sample['weights'], totCut, newSampleName, trees, columns, doFold, cutName, variableName, sample, False)
		    else :
		      #print 'newSampleWeightUp', newSampleWeightUp
		      histoList = self._drawPDF(nuisance['type'], configurationNuis[0], variable['name'], variable['range'], sample['weight'], [],                totCut, newSampleName, trees, columns, doFold, cutName, variableName, sample, False)

                    print 'length of histoList', len(histoList)
		    for ahist in histoList :
		      #print 'writing ahist'
		      ahist.Write()
		    #outputsHistoUp.Write()
		    #outputsHistoDo.Write()

    self.outFile.Close()
    print 'FINISHED'


  def _draw(self, var, rng, global_weight, weights, totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, fixZeros, go1D = True, useTUnfoldBin = False, unfoldBinType = None) :
    '''
    var           :   the variable to plot
    rng           :   the variable to plot
    global_weight :   the global weight for the samples
    weights       :   the wieghts 'root file' dependent
    totCut           :   the selection
    trees        :   the list of input files for this particular sample
    '''
    # go1D: option to select whether to go 1D from 2D or not  
    # useTUnfoldBin: use TUnfoldBinning class in TUnfold
    
    self._logger.info('Yields by process')

    numTree = 0
    bigName = 'histo_' + sampleName + '_' + cutName + '_' + variableName
    globalCut = "(" + totCut + ") * (" + global_weight + ")" 
    hTotal = self._makeshape(bigName, rng, useTUnfoldBin, unfoldBinType) 
    #print 'number of trees >>>>>>>>>>>>>>>>>>', len(trees)
    for tree in trees :
      #chain = TChain(self._treeName)
      #chain.AddFile(aFile)
      print '   sampleName     {0:<20} : entries {1:^9}'.format(sampleName,tree.GetEntries())
      ## new histogram
      shapeName = 'histo_' + sampleName + str(numTree)
      # prepare a dummy to fill
      shape = self._makeshape(shapeName, rng, useTUnfoldBin, unfoldBinType)

      self._logger.debug('---'+sampleName+'---')
      self._logger.debug('Formula: '+var+'>>'+shapeName)
      self._logger.debug('Cut:     '+totCut)
      self._logger.debug('ROOTFiles:'+'\n'.join([f.GetTitle() for f in tree.GetListOfFiles()]))

      # if weights vector is not given, do not apply file dependent weights
      if len(weights) != 0 :
        # if weight is not given for a given root file, '-', do not apply file dependent weight for that root file
        if weights[numTree] != '-' :
          globalCut = "(" + globalCut + ") * (" + weights[numTree] + ")" 
     
      entries = tree.Draw( var+'>>'+shapeName, globalCut, 'goff')
      if useTUnfoldBin: rt.ClearUnfoldBins()

      nTries = shape.Integral()
      #print ' entries after cut    >> ',entries,' integral:', nTries

      if nTries == 0 :
	print 'Warning : entries is 0 for', shapeName
      if math.isnan(nTries) :
	print 'ERROR : entries is nan for', shapeName

      hTotal.Add( shape )
      shape.Delete()
      
      numTree += 1

    # fold if needed
    if doFold == 1 or doFold == 3 :
      self._FoldOverflow (hTotal)
    if doFold == 2 or doFold == 3 :
      self._FoldUnderflow (hTotal)
    
    # go 1d
    hTotalFinal = hTotal
    if go1D: hTotalFinal = self._h2toh1(hTotal)

    hTotalFinal.SetTitle('histo_' + sampleName)
    hTotalFinal.SetName('histo_' + sampleName)

    # fix negative (almost never happening)
    # don't do it here by default, because you may have interference that is actually negative!
    # do this only if triggered: use with caution!
    # This also checks that only in specific phase spaces this is activated, "cutName"
    #
    # To be used with caution -> do not use this option if you don't know what you are playing with
    #
    if fixZeros and 'suppressNegative' in sample.keys() and ( cutName in sample['suppressNegative'] or 'all' in sample['suppressNegative']) : 
      self._fixNegativeBinAndError(hTotalFinal)

     
    return hTotalFinal

  def _drawPDF(self, pdfType, pdfW, var, rng, global_weight, weights, totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, fixZeros) :
    '''
    pdfType       : alphaS,...
    pdfW          :  pdfW
    var           :   the variable to plot
    rng           :   the variable to plot
    global_weight :   sample global_weight 
    weights       :   the wieghts 'root file' dependent
    totCut           :   the selection
    trees        :   the list of input files for this particular sample
    '''

    self._logger.info('Yields by process')
    globalCut = "(" + totCut + ") * (" + global_weight + ")" 
    #print 'pdfW tree Name', pdfW

    if pdfW is 'PDFWeights_AlphaS':
      bigNameUp = 'histo_' + sampleName + 'Up_' + cutName + '_' + variableName
      bigNameDo = 'histo_' + sampleName + 'Do_' + cutName + '_' + variableName
      hTotalAlphaUp = self._makeshape(bigNameUp, rng)
      hTotalAlphaDo = self._makeshape(bigNameDo, rng)
    elif pdfW is 'PDFWeights_Scale':
      bigNameAUp  = 'histo_' + sampleName + 'AUp_' + cutName + '_' + variableName
      bigNameADo  = 'histo_' + sampleName + 'ADo_' + cutName + '_' + variableName
      bigNameBUp  = 'histo_' + sampleName + 'BUp_' + cutName + '_' + variableName
      bigNameBDo  = 'histo_' + sampleName + 'BDo_' + cutName + '_' + variableName
      bigNameABUp = 'histo_' + sampleName + 'ABUp_' + cutName + '_' + variableName
      bigNameABDo = 'histo_' + sampleName + 'ABDo_' + cutName + '_' + variableName
      hTotalAUp  = self._makeshape(bigNameAUp, rng)
      hTotalADo  = self._makeshape(bigNameADo, rng)
      hTotalBUp  = self._makeshape(bigNameBUp, rng)
      hTotalBDo  = self._makeshape(bigNameBDo, rng)
      hTotalABUp = self._makeshape(bigNameABUp, rng)
      hTotalABDo = self._makeshape(bigNameABDo, rng)

    elif pdfW is 'PDFWeights_Error':
      hTotal_Err = [None] * 101
      for idx in xrange(101):
        bigName = 'histo_' + sampleName + str(idx) +'_' + cutName + '_' + variableName
        hTotal_Err[idx] = self._makeshape(bigName, rng)
    else:
      print 'This pdfW', pdfW, 'is not ready, exiting...'
      exit()

    numTree = 0
    for tree in trees :
      #myBr = tree.GetBranch(pdfW)
      #myBr = tree.GetBranch(pdfW).GetListOfLeaves()
      print '        {0:<20} : {1:^9}'.format(sampleName,tree.GetEntries())

      ## if weights vector is not given, do not apply file dependent weights
      if len(weights) != 0 :
        # if weight is not given for a given root file, '-', do not apply file dependent weight for that root file
        if weights[numTree] != '-' :
          globalCut = "(" + globalCut + ") * (" + weights[numTree] + ")" 
      ################################################
      # PDFWeights_AlphaS
      ################################################
      if pdfW is 'PDFWeights_AlphaS':
	print 'checking size of PDFWeights_AlphaS'
	size = 0
        for event in tree:
  	  size = event.PDFWeights_AlphaS.size()
	  break
	if size == 2:
	  print 'PDFWeights_AlphaS size is 2, let evaluate'
          globalCutDo = "(" + globalCut + ") * (PDFWeights_AlphaS[0])" 
          globalCutUp = "(" + globalCut + ") * (PDFWeights_AlphaS[1])" 
	else :
	  print 'PDFWeights_AlphaS size is not 2, let us make Up and Down is the same to norminal'
          globalCutDo =  globalCut 
          globalCutUp =  globalCut 

        # New histogram
        shapeNameDo = 'histo_' + sampleName + 'Do' + str(numTree)
        shapeNameUp = 'histo_' + sampleName + 'Up' + str(numTree)
	shapeDo = self._makeshape(shapeNameDo, rng)
	shapeUp = self._makeshape(shapeNameUp, rng)

	# fill
        entriesDo = tree.Draw( var+'>>'+shapeNameDo, globalCutDo, 'goff')
        entriesUp = tree.Draw( var+'>>'+shapeNameUp, globalCutUp, 'goff')

        nTriesUp = shapeUp.Integral()
        nTriesDo = shapeDo.Integral()
        #print 'entries, integral  Up and Do',entriesDo, entriesUp, nTriesDo, nTriesUp
        if nTriesDo == 0 :
          print 'Warning : entries is 0 for', shapeNameDo
        if nTriesUp == 0 :
          print 'Warning : entries is 0 for', shapeNameUp
        if math.isnan(nTriesDo) :
          print 'ERROR : entries is nan for', shapeNameDo
        if math.isnan(nTriesUp) :
          print 'ERROR : entries is nan for', shapeNameUp

        hTotalAlphaUp.Add(shapeUp)
        hTotalAlphaDo.Add(shapeDo)
	#print 'numTree =', numTree,' integral of hTotalAlphaUp', hTotalAlphaUp.Integral()
	shapeUp.Delete()
	shapeDo.Delete()

      #####################################################
      #  PDFWeights_Scale
      #####################################################
      if pdfW is 'PDFWeights_Scale':
	# Using Three nuisances for muR up/do, muF up/do, correlated up/do
	# as recommanded: https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf

	size = 0
        for event in tree:
  	  size = event.PDFWeights_Scale.size()
	  break
	#tree.GetEntry(0)
	#size = len( tree.PDFWeights_Scale )
	#for idx in xrange(size) :
	#  if idx == 5 or idx == 7:
	#    continue
	#  print idx, tree.PDFWeights_Scale[idx]
	#print 'scale size', size
	if size == 9:
	  #print 'saving scale nuisance variation: Renormalization and Factorization order changing'
	  globalCut_muAUp  = "(" + globalCut + ") * (PDFWeights_Scale[1])"
	  globalCut_muADo  = "(" + globalCut + ") * (PDFWeights_Scale[2])"
	  globalCut_muBUp  = "(" + globalCut + ") * (PDFWeights_Scale[3])"
	  globalCut_muBDo  = "(" + globalCut + ") * (PDFWeights_Scale[6])"
	  globalCut_muABUp = "(" + globalCut + ") * (PDFWeights_Scale[4])"
	  globalCut_muABDo = "(" + globalCut + ") * (PDFWeights_Scale[8])"
	else :
	  globalCut_muAUp  =       globalCut
	  globalCut_muADo  =       globalCut
	  globalCut_muBUp  =       globalCut
	  globalCut_muBDo  =       globalCut
	  globalCut_muABUp =       globalCut
	  globalCut_muABDo =       globalCut
	
        # New histogram
        shapeNameAUp  = 'histo_' + sampleName + 'AUp' + str(numTree)
        shapeNameADo  = 'histo_' + sampleName + 'ADo' + str(numTree)
        shapeNameBUp  = 'histo_' + sampleName + 'BUp' + str(numTree)
        shapeNameBDo  = 'histo_' + sampleName + 'BDo' + str(numTree)
        shapeNameABUp = 'histo_' + sampleName + 'ABUp' + str(numTree)
        shapeNameABDo = 'histo_' + sampleName + 'ABDo' + str(numTree)
        shapeAUp  = self._makeshape( shapeNameAUp, rng)
        shapeADo  = self._makeshape( shapeNameADo, rng)
        shapeBUp  = self._makeshape( shapeNameBUp, rng)
        shapeBDo  = self._makeshape( shapeNameBDo, rng)
        shapeABUp = self._makeshape( shapeNameABUp, rng)
        shapeABDo = self._makeshape( shapeNameABDo, rng)
	# fill
        entriesAUp=  tree.Draw( var+'>>'+shapeNameAUp,  globalCut_muAUp,  'goff' )
        entriesADo=  tree.Draw( var+'>>'+shapeNameADo,  globalCut_muADo,  'goff' )
        entriesBUp=  tree.Draw( var+'>>'+shapeNameBUp,  globalCut_muBUp,  'goff' )
        entriesBDo=  tree.Draw( var+'>>'+shapeNameBDo,  globalCut_muBDo,  'goff' )
        entriesABUp= tree.Draw( var+'>>'+shapeNameABUp, globalCut_muABUp, 'goff' )
        entriesABDo= tree.Draw( var+'>>'+shapeNameABDo, globalCut_muABDo, 'goff' )
        
        nTriesAUp = shapeAUp.Integral()
        nTriesADo = shapeADo.Integral()
        nTriesBUp = shapeBUp.Integral()
        nTriesBDo = shapeBDo.Integral()
        nTriesABUp = shapeABUp.Integral()
        nTriesABDo = shapeABDo.Integral()
        #print 'integral  AUp and ADo', nTriesAUp, nTriesADo
        #print 'integral  AUp and ADo', nTriesAUp, nTriesADo
        #print 'integral  BUp and BDo', nTriesBUp, nTriesBDo
        #print 'integral  BUp and BDo', nTriesBUp, nTriesBDo
        #print 'integral  ABUp and ABDo', nTriesABUp, nTriesABDo
        #print 'integral  ABUp and ABDo', nTriesABUp, nTriesABDo
        if nTriesAUp == 0 :
          print 'Warning : entries is 0 for', shapeNameAUp
        if nTriesADo == 0 :
          print 'Warning : entries is 0 for', shapeNameADo
        if nTriesBUp == 0 :
          print 'Warning : entries is 0 for', shapeNameBUp
        if nTriesBDo == 0 :
          print 'Warning : entries is 0 for', shapeNameBDo
        if nTriesABUp == 0 :
          print 'Warning : entries is 0 for', shapeNameABUp
        if nTriesABDo == 0 :
          print 'Warning : entries is 0 for', shapeNameABDo

        if math.isnan(nTriesAUp) :
          print 'ERROR : entries is nan for', shapeNameAUp
        if math.isnan(nTriesADo) :
          print 'ERROR : entries is nan for', shapeNameADo
        if math.isnan(nTriesBUp) :
          print 'ERROR : entries is nan for', shapeNameBUp
        if math.isnan(nTriesBDo) :
          print 'ERROR : entries is nan for', shapeNameBDo
        if math.isnan(nTriesABUp) :
          print 'ERROR : entries is nan for', shapeNameABUp
        if math.isnan(nTriesABDo) :
          print 'ERROR : entries is nan for', shapeNameABDo

        hTotalAUp.Add( shapeAUp )
        hTotalADo.Add( shapeADo )
        hTotalBUp.Add( shapeBUp )
        hTotalBDo.Add( shapeBDo )
        hTotalABUp.Add( shapeABUp )
        hTotalABDo.Add( shapeABDo )

	shapeAUp.Delete()
	shapeADo.Delete()
	shapeBUp.Delete()
	shapeBDo.Delete()
	shapeABUp.Delete()
	shapeABDo.Delete()

      #########################################
      # PDFWeights_Error
      #########################################
      # 0-100, 0=> nominal?
      if pdfW is 'PDFWeights_Error':
	globalCut_pdfErr = []
	size = 0
	for event in tree:
	  size = event.PDFWeights_Error.size()
	  break
	print 'PDFWeights_Error size', size
	if  size > 101:
	  print 'size of PDFWeights_Error is gt 101, exiting...'
	  exit()
	for idx in xrange(size) :
	  globalCut_pdfErr.append("(" + globalCut + ") * (PDFWeights_Error[" + str(idx) + "])")
	for idx in xrange(101 - size) :
	  globalCut_pdfErr.append("(" + globalCut + ") ")
	for idx in xrange(101):
	  # new histogram
	  shapeName = 'histo_' + sampleName + '_' + str(idx) + '_' + str(numTree)
	  shape     = self._makeshape( shapeName, rng )
	  #  fill
          entries = tree.Draw( var+'>>'+shapeName, globalCut_pdfErr[idx], 'goff')

          nTries = shape.Integral()
          if nTries == 0 :
            print 'Warning : entries is 0 for', shapeName
          if math.isnan(nTries) :
            print 'ERROR : entries is nan for', shapeName
          hTotal_Err[idx].Add( shape )
	  shape.Delete()


      numTree += 1
      #Dtree.Delete()
      #RDF.Delete()

      
    # fold if needed
    if doFold == 1 or doFold == 3 :
      if pdfW is 'PDFWeights_AlphaS':
	#print 'befor foldOverflow integral of hTotalAlphaUp', hTotalAlphaUp.Integral()
        self._FoldOverflow (hTotalAlphaUp)
        self._FoldOverflow (hTotalAlphaDo)
      if pdfW is 'PDFWeights_Scale':
        self._FoldOverflow (hTotalAUp)
        self._FoldOverflow (hTotalADo)
        self._FoldOverflow (hTotalBUp)
        self._FoldOverflow (hTotalBDo)
        self._FoldOverflow (hTotalABUp)
        self._FoldOverflow (hTotalABDo)
      if pdfW is 'PDFWeights_Error':
	for idx in xrange(101):
          self._FoldOverflow (hTotal_Err[idx])
    if doFold == 2 or doFold == 3 :
      if pdfW is 'PDFWeights_AlphaS':
        self._FoldUnderflow (hTotalAlphaUp)
        self._FoldUnderflow (hTotalAlphaDo)
      if pdfW is 'PDFWeights_Scale':
        self._FoldUnderflow (hTotalAUp)
        self._FoldUnderflow (hTotalADo)
        self._FoldUnderflow (hTotalBUp)
        self._FoldUnderflow (hTotalBDo)
        self._FoldUnderflow (hTotalABUp)
        self._FoldUnderflow (hTotalABDo)
      if pdfW is 'PDFWeights_Error':
	for idx in xrange(101):
          self._FoldUnderflow (hTotal_Err[idx])
    
    # go 1d
    if pdfW is 'PDFWeights_AlphaS':
      hTotalFinalAlphaUp = self._h2toh1(hTotalAlphaUp)
      hTotalFinalAlphaDo = self._h2toh1(hTotalAlphaDo)
      hTotalFinalAlphaUp.SetTitle('histo_' + sampleName+ 'Up')
      hTotalFinalAlphaDo.SetTitle('histo_' + sampleName+ 'Do')
      hTotalFinalAlphaUp.SetName('histo_' + sampleName + 'Up')
      hTotalFinalAlphaDo.SetName('histo_' + sampleName + 'Do')

    if pdfW is 'PDFWeights_Scale':
      hTotalFinalAUp = self._h2toh1(hTotalAUp)
      hTotalFinalADo = self._h2toh1(hTotalADo)
      hTotalFinalAUp.SetTitle('histo_' + sampleName+ 'AUp')
      hTotalFinalADo.SetTitle('histo_' + sampleName+ 'ADo')
      hTotalFinalAUp.SetName('histo_' + sampleName + 'AUp')
      hTotalFinalADo.SetName('histo_' + sampleName + 'ADo')

      hTotalFinalBUp = self._h2toh1(hTotalBUp)
      hTotalFinalBDo = self._h2toh1(hTotalBDo)
      hTotalFinalBUp.SetTitle('histo_' + sampleName+ 'BUp')
      hTotalFinalBDo.SetTitle('histo_' + sampleName+ 'BDo')
      hTotalFinalBUp.SetName('histo_' + sampleName + 'BUp')
      hTotalFinalBDo.SetName('histo_' + sampleName + 'BDo')

      hTotalFinalABUp = self._h2toh1(hTotalABUp)
      hTotalFinalABDo = self._h2toh1(hTotalABDo)
      hTotalFinalABUp.SetTitle('histo_' + sampleName+ 'ABUp')
      hTotalFinalABDo.SetTitle('histo_' + sampleName+ 'ABDo')
      hTotalFinalABUp.SetName('histo_' + sampleName + 'ABUp')
      hTotalFinalABDo.SetName('histo_' + sampleName + 'ABDo')


    if pdfW is 'PDFWeights_Error':
      hTotalFinalErr = [None] * 101
      for idx in xrange(101):
        hTotalFinalErr[idx] = self._h2toh1(hTotal_Err[idx])
        hTotalFinalErr[idx].SetTitle('histo_' + sampleName+ str(idx).zfill(3))
        hTotalFinalErr[idx].SetName('histo_' + sampleName + str(idx).zfill(3))

    #fix negative (almost never happening)
    # don't do it here by default, because you may have interference that is actually negative!
    # do this only if triggered: use with caution!
    # This also checks that only in specific phase spaces this is activated, "cutName"
    #
    # To be used with caution -> do not use this option if you don't know what you are playing with
    #
    if fixZeros and 'suppressNegative' in sample.keys() and ( cutName in sample['suppressNegative'] or 'all' in sample['suppressNegative']) : 
      if pdfW is 'PDFWeights_AlphaS':
        self._fixNegativeBinAndError(hTotalFinalAlphaUp)
        self._fixNegativeBinAndError(hTotalFinalAlphaDo)
      if pdfW is 'PDFWeights_Scale':
        self._fixNegativeBinAndError(hTotalFinalAUp)
        self._fixNegativeBinAndError(hTotalFinalADo)
        self._fixNegativeBinAndError(hTotalFinalBUp)
        self._fixNegativeBinAndError(hTotalFinalBDo)
        self._fixNegativeBinAndError(hTotalFinalABUp)
        self._fixNegativeBinAndError(hTotalFinalABDo)
      if pdfW is 'PDFWeights_Error':
        for idx in xrange(101):
          self._fixNegativeBinAndError(hTotalFinalErr[idx])

    histoList = []
    if pdfW is 'PDFWeights_AlphaS':
      histoList.append(hTotalFinalAlphaUp)
      histoList.append(hTotalFinalAlphaDo)
    if pdfW is 'PDFWeights_Scale':
      histoList.append(hTotalFinalAUp)
      histoList.append(hTotalFinalADo)
      histoList.append(hTotalFinalBUp)
      histoList.append(hTotalFinalBDo)
      histoList.append(hTotalFinalABUp)
      histoList.append(hTotalFinalABDo)

    if pdfW is 'PDFWeights_Error':
      return hTotalFinalErr
    else:
      return histoList
    #return hTotalFinalAlphaUp, hTotalFinalAlphaDo


  def _FoldUnderflow(self, h) :

    if h.GetDimension() == 1:
      nx = h.GetNbinsX()
      # 0 --> 1
      ShapeFactory._moveAddBin(h, (0,),(1,) )
      return
    elif h.GetDimension() == 2:
      nx = h.GetNbinsX()
      ny = h.GetNbinsY()
      for i in xrange(1,nx+1):
	ShapeFactory._moveAddBin(h,(i,0 ),(i, 1 ) )
      for j in xrange(1,ny+1):
	ShapeFactory._moveAddBin(h,(0,    j),(1, j) )

      # 0,0 -> 1,1
      # 0,ny+1 -> 1,ny+1
      # nx+1,0 -> nx+1,1

      ShapeFactory._moveAddBin(h, (0,0),(1,1) )
      ShapeFactory._moveAddBin(h, (0,ny+1),(1,ny+1) )
      ShapeFactory._moveAddBin(h, (nx+1,0),(nx+1,1) )

  def _FoldOverflow(self, h):

    if h.GetDimension() == 1:
      nx = h.GetNbinsX()
      # n+1 --> n
      ShapeFactory._moveAddBin(h, (nx+1,),(nx,) )
      return
    elif h.GetDimension() == 2:
      nx = h.GetNbinsX()
      ny = h.GetNbinsY()
      for i in xrange(1,nx+1):
	ShapeFactory._moveAddBin(h,(i,ny+1),(i, ny) )
      for j in xrange(1,ny+1):
	ShapeFactory._moveAddBin(h,(nx+1, j),(nx,j) )
	# 0,ny+1 -> 0,ny
	# nx+1,0 -> nx,0
	# nx+1,ny+1 ->nx,ny

	ShapeFactory._moveAddBin(h, (0,ny+1),(0,ny) )
	ShapeFactory._moveAddBin(h, (nx+1,0),(nx,0) )
	ShapeFactory._moveAddBin(h, (nx+1,ny+1),(nx,ny) )

  def _h2toh1(self, h):
    import array

    if not isinstance(h, TH2):
      return h
    nx = h.GetNbinsX()
    ny = h.GetNbinsY()


    h_flat = TH1D(h.GetName()+"_flat",h.GetTitle() + "_flat",nx*ny,0,nx*ny) # add _flat to avoid warning message
    sumw2 = h.GetSumw2()
    sumw2_flat = h_flat.GetSumw2()

    for i in xrange(1,nx+1):
      for j in xrange(1,ny+1):
	# i,j must be mapped in 
	b2d = h.GetBin( i,j )
	b1d = ((j-1)+(i-1)*ny)+1

	h_flat.SetAt( h.At(b2d), b1d )
	sumw2_flat.SetAt( sumw2.At(b2d), b1d ) 

    h_flat.SetEntries(h.GetEntries())

    stats2d = array.array('d',[0]*7)
    h.GetStats(stats2d)

    stats1d = array.array('d',[0]*4)
    stats1d[0] = stats2d[0]
    stats1d[1] = stats2d[1]
    stats1d[2] = stats2d[2]+stats2d[4]
    stats1d[3] = stats2d[3]+stats2d[5]
    h_flat.PutStats(stats1d)
    xtitle = h.GetXaxis().GetTitle()
    h_flat.GetXaxis().SetTitle(xtitle)

    return h_flat

  def _fixNegativeBinAndError(self, histogram_to_be_fixed):
    # if a histogram has a bin < 0
    # then put the bin content to 0
    # and also if a histogram has uncertainties that go <0,
    # then put the uncertainty to the maximum allowed

    for ibin in range(1, histogram_to_be_fixed.GetNbinsX()+1) :
      if histogram_to_be_fixed.GetBinContent(ibin) < 0 :
	histogram_to_be_fixed.SetBinContent(ibin, 0) 

    # the SetBinError does not allow asymmetric -> fine, maximum uncertainty set
    for ibin in range(1, histogram_to_be_fixed.GetNbinsX()+1) :
      if histogram_to_be_fixed.GetBinContent(ibin) - histogram_to_be_fixed.GetBinErrorLow(ibin) < 0 :
	histogram_to_be_fixed.SetBinError(ibin, histogram_to_be_fixed.GetBinContent(n)) 

  @staticmethod
  def _makeshape( name, bins, useTUnfoldBin = False, unfoldBinType = None):

    if useTUnfoldBin == False :
        hclass, hargs, ndim = ShapeFactory._bins2hclass( bins )
        return hclass(name, name, *hargs)

    elif useTUnfoldBin :
        # use TUnfoldBinnig
        rt.SetMassBinningRec()
        rt.SetPtBinningRec()
        rt.SetMassBinningGen()
        rt.SetPtBinningGen()

        if unfoldBinType == ISRUnfold.PtRec2DHist:     return rt.get2DHistogramPtRec(name) 
        if unfoldBinType == ISRUnfold.PtGen2DHist:     return rt.get2DHistogramPtGen(name) 
        if unfoldBinType == ISRUnfold.PtMigrationM:    return rt.getMigrationMforPt(name) 
        if unfoldBinType == ISRUnfold.MassRec1DHist:   return rt.get1DHistogramMassRec(name) 
        if unfoldBinType == ISRUnfold.MassGen1DHist:   return rt.get1DHistogramMassGen(name) 
        if unfoldBinType == ISRUnfold.MassMigrationM:  return rt.getMigrationMforMass(name) 

  def _connectInputs(self, samples, inputDir, skipMissingFiles, friendsDir = None, skimListDir = None):
    listTrees = []
    #tree = TChain(self._treeName)
    #for aFile in samples :
    #  tree.AddFile(aFile)
    #listTrees.append(tree)
    for aFile in samples :
      tree = TChain(self._treeName)
      tree.AddFile(aFile)
      listTrees.append(tree)

    return listTrees

  @staticmethod
  def _bins2hclass( bins ):
    '''
    Fixed bin width
    bins = (nx,xmin,xmax)
    bins = (nx,xmin,xmax, ny,ymin,ymax)
    Variable bin width
    bins = ([x0,...,xn])
    bins = ([x0,...,xn],[y0,...,ym])
    '''

    from array import array
    if not bins :
      return name, 0 # name?
    elif not ( isinstance(bins, tuple) or isinstance( bins, list) ) :
      raise RuntimeError('bin must be an ntuple or an arrays')

    l = len(bins)
    # 1D variable binning
    if l == 1 and isinstance(bins[0], list) :
      ndim = 1
      hclass = TH1D
      xbins = bins[0]
      hargs = (len(xbins)-1, array('d', xbins) )
    elif l == 2 and isinstance( bins[0], list) and isinstance( bins[1], list) :
      ndim = 2
      hclass = TH2D
      xbins = bins[0]
      ybins = bins[1]
      hargs = (len(xbins)-1, array('d', xbins),
	       len(ybins)-1, array('d', ybins) )
    elif l == 3 :
      # nx, xmin, xmax
      ndim = 1
      hclass = TH1D
      hargs = bins
    elif l == 6 :
      # nx, xmin, xmax, ny, ymin, ymax
      ndim = 2
      hclass = TH2D
      hargs = bins
    else :
      raise RuntimeError('What a mess!!! bin malformed!')

    return hclass, hargs, ndim


  @staticmethod
  def _moveAddBin(h, fromBin, toBin ):
    if not isinstance(fromBin,tuple) or not isinstance(toBin,tuple):
      raise ValueError('Arguments must be tuples')
    dims = [h.GetDimension(), len(fromBin), len(toBin) ]
    if dims.count(dims[0]) != len(dims):
      raise ValueError('histogram and the 2 bins don\'t have the same dimension')
    # get bins
    b1 = h.GetBin( *fromBin )
    b2 = h.GetBin( *toBin )

    # move contents
    c1 = h.At( b1 )
    c2 = h.At( b2 )
    h.SetAt(0, b1)
    h.SetAt(c1+c2, b2)
    # move weights as well
    sumw2 = h.GetSumw2()

    w1 = sumw2.At( b1 )
    w2 = sumw2.At( b2 )
    sumw2.SetAt(0, b1)
    sumw2.SetAt(w1+w2, b2)

