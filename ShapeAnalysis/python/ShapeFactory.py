
import os,sys
import logging
import math 
from ROOT import TFile, RDataFrame, TH1D, TH2, gROOT, TChain, vector
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

  def makeNominals(self, sampleName, sample, inFiles, outFile, variables, columns, cuts, supercut, nuisances):
    print "===================="
    print "=== makeNominals ==="
    print "===================="
    gROOT.SetBatch()

    # only one sample dilivered for now
    self._inFiles   = inFiles
    self._variables = variables
    self._cuts      = cuts

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
    self.outFile = TFile(outFile,'recreate')

 
    #print 'ShapeFactory',self._treeName
    #chain = TChain(self._treeName)
    #                                                         skipMissingFiles
    inputDir = ''
    trees = self._connectInputs( inFiles, inputDir, False)
    for cutName, cut in self._cuts.iteritems():
      totCut = cut+"&&"+supercut
      print 'cut',cutName,'::',cut
      self.outFile.mkdir(cutName)
      for variableName, variable in variables.iteritems():
	self.outFile.mkdir(cutName+"/"+variableName)
	self.outFile.cd(cutName+"/"+variableName)
        print variableName
        print 'variable[name]', variable['name']
	print 'variable[range]', variable['range'][0],':', variable['range'][1],':', variable['range'][2]

	doFold = 0
	if 'fold' in variable.keys() :
	  print "	variable[fold] = ", variable['fold']
	  doFold = variable['fold']
	
	# create histogram
	if 'weights' in sample.keys() :
	  outputsHisto = self._draw( variable['name'], variable['range'], sample['weight'], sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True)
	else :
	  outputsHisto = self._draw( variable['name'], variable['range'], sample['weight'], [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True)

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
		      outputsHistoUp = self._draw( variable['name'], variable['range'], newSampleWeightUp, sample['weights'], totCut, newSampleNameUp, trees, columns, doFold, cutName, variableName, sample, False)
		      outputsHistoDo = self._draw( variable['name'], variable['range'], newSampleWeightDo, sample['weights'], totCut, newSampleNameDo, trees, columns, doFold, cutName, variableName, sample, False)
		    else :
		      #print 'newSampleWeightUp', newSampleWeightUp
		      outputsHistoUp = self._draw( variable['name'], variable['range'], newSampleWeightUp, [],                totCut, newSampleNameUp, trees, columns, doFold, cutName, variableName, sample, False)
		      outputsHistoDo = self._draw( variable['name'], variable['range'], newSampleWeightDo, [],                totCut, newSampleNameDo, trees, columns, doFold, cutName, variableName, sample, False)

		    outputsHistoUp.Write()
		    outputsHistoDo.Write()

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


  def _draw(self, var, rng, global_weight, weights, totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, fixZeros) :
    '''
    var           :   the variable to plot
    rng           :   the variable to plot
    global_weight :   the global weight for the samples
    weights       :   the wieghts 'root file' dependent
    totCut           :   the selection
    trees        :   the list of input files for this particular sample
    '''

    self._logger.info('Yields by process')

    numTree = 0
    bigName = 'histo_' + sampleName + '_' + cutName + '_' + variableName
    hTotal = self._makeshape(bigName, rng)
    for tree in trees :
      #chain = TChain(self._treeName)
      #chain.AddFile(aFile)
      print '        {0:<20} : {1:^9}'.format(sampleName,tree.GetEntries())
      RDF = RDataFrame
      if ('ALL' in columns) or (len(columns) == 0) :
	Dtree = RDF(tree)
      else :
	v_columns = vector('string')()
	for column in columns:
	  v_columns.push_back(column)
	Dtree = RDF(tree,v_columns)
      #shape = Dtree.Histo1D(('mine','mine',100,0,100),'diLep_pt')
      #shape = Dtree.Histo1D(('mine','mine',rng[0],rng[1],rng[2]),var)
      totalWeight = global_weight
      ## if weights vector is not given, do not apply file dependent weights
      if len(weights) != 0 :
        # if weight is not given for a given root file, '-', do not apply file dependent weight for that root file
        if weights[numTree] != '-' :
          totalWeight = "(" + totalWeight + ") * (" + weights[numTree] + ")" 
          #globalCut = "(" + globalCut + ") * (" + weights[numTree] + ")" 
      augmented_d = Dtree.Define('totW', totalWeight)

      ## new histogram
      shapeName = 'histo_' + sampleName + str(numTree)
      ## prepare a dummy to fill
      hclass, hargs, ndim = self._bins2hclass( rng)
      
      hModel = (shapeName, shapeName,) + hargs
      if ndim == 1 :
        #print 'hModel', hModel
        #print 'totCut', totCut
        #print 'var', var
        shape = augmented_d.Filter(totCut).Histo1D( hModel, var, 'totW')
      elif ndim == 2 :
        shape = augmented_d.Filter(totCut).Histo2D( hModel, var, 'totW')
        #shape = augmented_d.Filter(totCut).Histo1D((shapeName,shapeName,rng[0],rng[1],rng[2]),var,'totW')
      #
      # in principle if we use filter
      # I may remove the globalCut here
      # ... but it doesn't hurt leaving it
      #entries = tree.Draw( var+'>>'+shapeName, globalCut, 'goff')
      #print '     >> ',entries,':',shape.Integral()
      nTries = shape.Integral()
      print 'integral', nTries
      if nTries == 0 :
	print 'Warning : entries is 0 for', hModel
      if math.isnan(nTries) :
	print 'ERROR : entries is nan for', hModel

      if (numTree == 0) :
	shape.SetTitle(bigName)
	shape.SetName(bigName)
	hTotal = shape
      else :
	hTotal.Add(shape)
      
      numTree += 1

    # fold if needed
    if doFold == 1 or doFold == 3 :
      self._FoldOverflow (hTotal)
    if doFold == 2 or doFold == 3 :
      self._FoldUnderflow (hTotal)
    
    # go 1d
    hTotalFinal = self._h2toh1(hTotal)
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
    print 'pdfW treeName', pdfW

    numTree = 0
    bigNameUp = 'histo_' + sampleName + 'Up_' + cutName + '_' + variableName
    bigNameDo = 'histo_' + sampleName + 'Do_' + cutName + '_' + variableName
    hTotalUp = self._makeshape(bigNameUp, rng)
    hTotalDo = self._makeshape(bigNameDo, rng)

    if pdfW is 'PDFWeights_Scale':
      bigNameAUp = 'histo_' + sampleName + 'AUp_' + cutName + '_' + variableName
      bigNameADo = 'histo_' + sampleName + 'ADo_' + cutName + '_' + variableName
      hTotalAUp = self._makeshape(bigNameAUp, rng)
      hTotalADo = self._makeshape(bigNameADo, rng)
      bigNameBUp = 'histo_' + sampleName + 'BUp_' + cutName + '_' + variableName
      bigNameBDo = 'histo_' + sampleName + 'BDo_' + cutName + '_' + variableName
      hTotalBUp = self._makeshape(bigNameBUp, rng)
      hTotalBDo = self._makeshape(bigNameBDo, rng)
      bigNameABUp = 'histo_' + sampleName + 'ABUp_' + cutName + '_' + variableName
      bigNameABDo = 'histo_' + sampleName + 'ABDo_' + cutName + '_' + variableName
      hTotalABUp = self._makeshape(bigNameABUp, rng)
      hTotalABDo = self._makeshape(bigNameABDo, rng)

    for tree in trees :
      #myBr = tree.GetBranch(pdfW)
      #myBr = tree.GetBranch(pdfW).GetListOfLeaves()
      print '        {0:<20} : {1:^9}'.format(sampleName,tree.GetEntries())
      RDF = RDataFrame
      if ('ALL' in columns) or (len(columns) == 0) :
	Dtree = RDF(tree)
      else :
	v_columns = vector('string')()
	for column in columns:
	  v_columns.push_back(column)
	Dtree = RDF(tree,v_columns)
      totalWeight = global_weight
      ## if weights vector is not given, do not apply file dependent weights
      if len(weights) != 0 :
        # if weight is not given for a given root file, '-', do not apply file dependent weight for that root file
        if weights[numTree] != '-' :
          totalWeight = "(" + totalWeight + ") * (" + weights[numTree] + ")" 
      ################################################
      # PDFWeights_AlphaS
      ################################################
      if pdfW is 'PDFWeights_AlphaS':
	print 'checking size of PDFWeights_AlphaS'
        for event in tree:
  	  size = event.PDFWeights_AlphaS.size()
	  break
	if size == 2:
	  print 'PDFWeights_AlphaS size is 2, let evaluate'
          totalWeightDo = "(" + totalWeight + ") * (PDFWeights_AlphaS[0])" 
          totalWeightUp = "(" + totalWeight + ") * (PDFWeights_AlphaS[1])"
	else :
	  print 'PDFWeights_AlphaS size is not 2, Up and Down is the same to norminal'
          totalWeightDo = totalWeight 
          totalWeightUp = totalWeight

        augmented_d = Dtree.Define('totwDo', totalWeightDo) \
                           .Define('totwUp', totalWeightUp)
        # New histogram
        shapeNameUp = 'histo_' + sampleName + 'Up' + str(numTree)
        shapeNameDo = 'histo_' + sampleName + 'Do' + str(numTree)
	# prepare a dummy to fill
        hclass, hargs, ndim = self._bins2hclass( rng)
        hModelUp = (shapeNameUp, shapeNameUp,) + hargs
        hModelDo = (shapeNameDo, shapeNameDo,) + hargs
        if ndim == 1 :
          shapeUp = augmented_d.Filter(totCut).Histo1D( hModelUp, var, 'totwUp')
          shapeDo = augmented_d.Filter(totCut).Histo1D( hModelDo, var, 'totwDo')
        elif ndim == 2 :
          shapeUp = augmented_d.Filter(totCut).Histo2D( hModelUp, var, 'totwUp')
          shapeDo = augmented_d.Filter(totCut).Histo2D( hModelDo, var, 'totwDo')

        nTriesUp = shapeUp.Integral()
        nTriesDo = shapeDo.Integral()
        print 'integral  Up and Do', nTriesUp, nTriesDo
        if nTriesUp == 0 :
          print 'Warning : entries is 0 for', hModelUp
        if nTriesDo == 0 :
          print 'Warning : entries is 0 for', hModelDo
        if math.isnan(nTriesUp) :
          print 'ERROR : entries is nan for', hModelUp
        if math.isnan(nTriesDo) :
          print 'ERROR : entries is nan for', hModelDo

        if (numTree == 0) :
          shapeUp.SetTitle(bigNameUp)
          shapeUp.SetName(bigNameUp)
          hTotalUp = shapeUp

          shapeDo.SetTitle(bigNameDo)
          shapeDo.SetName(bigNameDo)
          hTotalDo = shapeDo
        else :
          hTotalUp.Add(shapeUp)
          hTotalDo.Add(shapeDo)

      #####################################################
      #  PDFWeights_Scale
      #####################################################
      if pdfW is 'PDFWeights_Scale':
	# Using Three nuisances for muR up/do, muF up/do, correlated up/do
	# as recommanded: https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf

	print 'checking size of PDFWeights_Scale'
        #for event in tree:
  	#  size = event.PDFWeights_Scale.size()
	#  break
	tree.GetEntry(0)
	size = len( tree.PDFWeights_Scale )
	#for idx in xrange(size) :
	#  if idx == 5 or idx == 7:
	#    continue
	#  print idx, tree.PDFWeights_Scale[idx]
	#print 'scale size', size
	if size == 9:
	  print 'saving scale nuisance variation: Renormalization and Factorization order changing'
	  totalW_muAUp  = "(" + totalWeight + ") * (PDFWeights_Scale[1])"
	  totalW_muADo  = "(" + totalWeight + ") * (PDFWeights_Scale[2])"
	  totalW_muBUp  = "(" + totalWeight + ") * (PDFWeights_Scale[3])"
	  totalW_muBDo  = "(" + totalWeight + ") * (PDFWeights_Scale[6])"
	  totalW_muABUp = "(" + totalWeight + ") * (PDFWeights_Scale[4])"
	  totalW_muABDo = "(" + totalWeight + ") * (PDFWeights_Scale[8])"
	else :
	  totalW_muAUp  =       totalWeight
	  totalW_muADo  =       totalWeight
	  totalW_muBUp  =       totalWeight
	  totalW_muBDo  =       totalWeight
	  totalW_muABUp =       totalWeight
	  totalW_muABDo =       totalWeight
	
	augmented_d = Dtree.Define('totalW_muAUp', totalW_muAUp) \
	                   .Define('totalW_muADo', totalW_muADo) \
			   .Define('totalW_muBUp', totalW_muBUp) \
			   .Define('totalW_muBDo', totalW_muBDo) \
			   .Define('totalW_muABUp', totalW_muABUp) \
			   .Define('totalW_muABDo', totalW_muABDo)
        # New histogram
        shapeNameAUp  = 'histo_' + sampleName + 'AUp' + str(numTree)
        shapeNameADo  = 'histo_' + sampleName + 'ADo' + str(numTree)
        shapeNameBUp  = 'histo_' + sampleName + 'BUp' + str(numTree)
        shapeNameBDo  = 'histo_' + sampleName + 'BDo' + str(numTree)
        shapeNameABUp = 'histo_' + sampleName + 'ABUp' + str(numTree)
        shapeNameABDo = 'histo_' + sampleName + 'ABDo' + str(numTree)
	# prepare a dummy to fill
        hclass, hargs, ndim = self._bins2hclass( rng)
        hModelAUp  = (shapeNameAUp,  shapeNameAUp,)  + hargs
        hModelADo  = (shapeNameADo,  shapeNameADo,)  + hargs
        hModelBUp  = (shapeNameBUp,  shapeNameBUp,)  + hargs
        hModelBDo  = (shapeNameBDo,  shapeNameBDo,)  + hargs
        hModelABUp = (shapeNameABUp, shapeNameABUp,) + hargs
        hModelABDo = (shapeNameABDo, shapeNameABDo,) + hargs
        if ndim == 1 :
          shapeAUp  = augmented_d.Filter(totCut).Histo1D( hModelAUp,  var, 'totalW_muAUp')
          shapeADo  = augmented_d.Filter(totCut).Histo1D( hModelADo,  var, 'totalW_muADo')
          shapeBUp  = augmented_d.Filter(totCut).Histo1D( hModelBUp,  var, 'totalW_muBUp')
          shapeBDo  = augmented_d.Filter(totCut).Histo1D( hModelBDo,  var, 'totalW_muBDo')
          shapeABUp = augmented_d.Filter(totCut).Histo1D( hModelABUp, var, 'totalW_muABUp')
          shapeABDo = augmented_d.Filter(totCut).Histo1D( hModelABDo, var, 'totalW_muABDo')
        elif ndim == 2 :
          shapeAUp  = augmented_d.Filter(totCut).Histo2D( hModelAUp,  var, 'totalW_muAUp')
          shapeADo  = augmented_d.Filter(totCut).Histo2D( hModelADo,  var, 'totalW_muADo')
          shapeBUp  = augmented_d.Filter(totCut).Histo2D( hModelBUp,  var, 'totalW_muBUp')
          shapeBDo  = augmented_d.Filter(totCut).Histo2D( hModelBDo,  var, 'totalW_muBDo')
          shapeABUp = augmented_d.Filter(totCut).Histo2D( hModelABUp, var, 'totalW_muABUp')
          shapeABDo = augmented_d.Filter(totCut).Histo2D( hModelABDo, var, 'totalW_muABDo')
        
        nTriesAUp = shapeAUp.Integral()
        nTriesADo = shapeADo.Integral()
        nTriesBUp = shapeBUp.Integral()
        nTriesBDo = shapeBDo.Integral()
        nTriesABUp = shapeABUp.Integral()
        nTriesABDo = shapeABDo.Integral()
        print 'integral  AUp and ADo', nTriesAUp, nTriesADo
        print 'integral  AUp and ADo', nTriesAUp, nTriesADo
        print 'integral  BUp and BDo', nTriesBUp, nTriesBDo
        print 'integral  BUp and BDo', nTriesBUp, nTriesBDo
        print 'integral  ABUp and ABDo', nTriesABUp, nTriesABDo
        print 'integral  ABUp and ABDo', nTriesABUp, nTriesABDo
        if nTriesAUp == 0 :
          print 'Warning : entries is 0 for', hModelAUp
        if nTriesADo == 0 :
          print 'Warning : entries is 0 for', hModelADo
        if nTriesBUp == 0 :
          print 'Warning : entries is 0 for', hModelBUp
        if nTriesBDo == 0 :
          print 'Warning : entries is 0 for', hModelBDo
        if nTriesABUp == 0 :
          print 'Warning : entries is 0 for', hModelABUp
        if nTriesABDo == 0 :
          print 'Warning : entries is 0 for', hModelABDo

        if math.isnan(nTriesAUp) :
          print 'ERROR : entries is nan for', hModelAUp
        if math.isnan(nTriesADo) :
          print 'ERROR : entries is nan for', hModelADo
        if math.isnan(nTriesBUp) :
          print 'ERROR : entries is nan for', hModelBUp
        if math.isnan(nTriesBDo) :
          print 'ERROR : entries is nan for', hModelBDo
        if math.isnan(nTriesABUp) :
          print 'ERROR : entries is nan for', hModelABUp
        if math.isnan(nTriesABDo) :
          print 'ERROR : entries is nan for', hModelABDo

        if (numTree == 0) :
          shapeAUp.SetTitle(bigNameAUp)
          shapeAUp.SetName(bigNameAUp)
          hTotalAUp = shapeAUp

          shapeADo.SetTitle(bigNameADo)
          shapeADo.SetName(bigNameADo)
          hTotalADo = shapeADo

          shapeBUp.SetTitle(bigNameBUp)
          shapeBUp.SetName(bigNameBUp)
          hTotalBUp = shapeBUp
          shapeBDo.SetTitle(bigNameBDo)
          shapeBDo.SetName(bigNameBDo)
          hTotalBDo = shapeBDo

          shapeABUp.SetTitle(bigNameABUp)
          shapeABUp.SetName(bigNameABUp)
          hTotalABUp = shapeABUp

          shapeABDo.SetTitle(bigNameABDo)
          shapeABDo.SetName(bigNameABDo)
          hTotalABDo = shapeABDo
        else :
          hTotalAUp.Add(shapeAUp)
          hTotalADo.Add(shapeADo)
          hTotalBUp.Add(shapeBUp)
          hTotalBDo.Add(shapeBDo)
          hTotalABUp.Add(shapeABUp)
          hTotalABDo.Add(shapeABDo)

      #########################################
      # PDFWeights_Error
      #########################################
      # 0-100, 0=> nominal?
      if pdfW is 'PDFWeights_Error':
	totalW_pdfErr = []
	tree.GetEntry(0)
	size = len( tree.PDFWeights_Error )
	if  size > 101:
	  print 'size of PDFWeights_Error is gt 101, exiting...'
	  exit()
	for idx in xrange(size) :
	  #print idx, tree.PDFWeights_Error[idx]
	  totalW_pdfErr.append("(" + totalWeight + ") * (PDFWeights_Error[" + str(idx) + "])")
	for idx in xrange(101 - size) :
	  totalW_pdfErr.append("1")
	print 'PDFWeights_Error size', size
	hTotal = [None] * 101
	for idx in xrange(101):
	#  print idx, totalW_pdfErr[idx]
	  augmented_d = Dtree.Define('totalW_pdfErr'+str(idx), totalW_pdfErr[idx])
	  # new histogram
	  shapeName = 'histo_' + sampleName + '_' + str(idx) + '_' + str(numTree)
	  # prepare a dummy to fill
          hclass, hargs, ndim = self._bins2hclass( rng)
          hModel  = (shapeName,  shapeName,)  + hargs
	  if ndim == 1 :
            shape  = augmented_d.Filter(totCut).Histo1D( hModel,  var, 'totalW_pdfErr'+str(idx))
	  elif ndim == 2 :
            shape  = augmented_d.Filter(totCut).Histo2D( hModel,  var, 'totalW_pdfErr'+str(idx))
	  else :
	    print 'this dim of hist not ready', ndim, 'exiting'
	    exit()
          nTries = shape.Integral()
          print idx, 'integral  ', nTries
          if nTries == 0 :
            print 'Warning : entries is 0 for', hModel
          if math.isnan(nTries) :
            print 'ERROR : entries is nan for', hModel
          if (numTree == 0) :
            bigName = 'histo_' + sampleName + str(idx) +'_' + cutName + '_' + variableName
            shape.SetTitle(bigName)
            shape.SetName(bigName)
            hTotal[idx] = shape
	  else :
	    hTotal[idx].Add(shape)


      numTree += 1

      
    # fold if needed
    if doFold == 1 or doFold == 3 :
      if pdfW is 'PDFWeights_AlphaS':
        self._FoldOverflow (hTotalUp)
        self._FoldOverflow (hTotalDo)
      if pdfW is 'PDFWeights_Scale':
        self._FoldOverflow (hTotalAUp)
        self._FoldOverflow (hTotalADo)
        self._FoldOverflow (hTotalBUp)
        self._FoldOverflow (hTotalBDo)
        self._FoldOverflow (hTotalABUp)
        self._FoldOverflow (hTotalABDo)
      if pdfW is 'PDFWeights_Error':
	for idx in xrange(101):
          self._FoldOverflow (hTotal[idx])
    if doFold == 2 or doFold == 3 :
      if pdfW is 'PDFWeights_AlphaS':
        self._FoldUnderflow (hTotalUp)
        self._FoldUnderflow (hTotalDo)
      if pdfW is 'PDFWeights_Scale':
        self._FoldUnderflow (hTotalAUp)
        self._FoldUnderflow (hTotalADo)
        self._FoldUnderflow (hTotalBUp)
        self._FoldUnderflow (hTotalBDo)
        self._FoldUnderflow (hTotalABUp)
        self._FoldUnderflow (hTotalABDo)
      if pdfW is 'PDFWeights_Error':
	for idx in xrange(101):
          self._FoldUnderflow (hTotal[idx])
    
    # go 1d
    if pdfW is 'PDFWeights_AlphaS':
      hTotalFinalUp = self._h2toh1(hTotalUp)
      hTotalFinalDo = self._h2toh1(hTotalDo)
      hTotalFinalUp.SetTitle('histo_' + sampleName+ 'Up')
      hTotalFinalDo.SetTitle('histo_' + sampleName+ 'Do')
      hTotalFinalUp.SetName('histo_' + sampleName + 'Up')
      hTotalFinalDo.SetName('histo_' + sampleName + 'Do')

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
      hTotalFinal = [None] * 101
      for idx in xrange(101):
        hTotalFinal[idx] = self._h2toh1(hTotal[idx])
        hTotalFinal[idx].SetTitle('histo_' + sampleName+ str(idx).zfill(3))
        hTotalFinal[idx].SetName('histo_' + sampleName + str(idx).zfill(3))

    #fix negative (almost never happening)
    # don't do it here by default, because you may have interference that is actually negative!
    # do this only if triggered: use with caution!
    # This also checks that only in specific phase spaces this is activated, "cutName"
    #
    # To be used with caution -> do not use this option if you don't know what you are playing with
    #
    if fixZeros and 'suppressNegative' in sample.keys() and ( cutName in sample['suppressNegative'] or 'all' in sample['suppressNegative']) : 
      if pdfW is 'PDFWeights_AlphaS':
        self._fixNegativeBinAndError(hTotalFinalUp)
        self._fixNegativeBinAndError(hTotalFinalDo)
      if pdfW is 'PDFWeights_Scale':
        self._fixNegativeBinAndError(hTotalFinalAUp)
        self._fixNegativeBinAndError(hTotalFinalADo)
        self._fixNegativeBinAndError(hTotalFinalBUp)
        self._fixNegativeBinAndError(hTotalFinalBDo)
        self._fixNegativeBinAndError(hTotalFinalABUp)
        self._fixNegativeBinAndError(hTotalFinalABDo)
      if pdfW is 'PDFWeights_Error':
        for idx in xrange(101):
          self._fixNegativeBinAndError(hTotalFinal[idx])

    histoList = []
    if pdfW is 'PDFWeights_AlphaS':
      histoList.append(hTotalFinalUp)
      histoList.append(hTotalFinalDo)
    if pdfW is 'PDFWeights_Scale':
      histoList.append(hTotalFinalAUp)
      histoList.append(hTotalFinalADo)
      histoList.append(hTotalFinalBUp)
      histoList.append(hTotalFinalBDo)
      histoList.append(hTotalFinalABUp)
      histoList.append(hTotalFinalABDo)

    if pdfW is 'PDFWeights_Error':
      return hTotalFinal
    else:
      return histoList
    #return hTotalFinalUp, hTotalFinalDo


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

    h_flat = TH1D(h.GetName(),h.GetTitle(),nx*ny,0,nx*ny)
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
	histogram_to_be_fixed.SetBinError(ibin, histogram_to_be_fixed.GetBinContent(ibin)) 


  @staticmethod
  def _makeshape( name, bins ):
    hclass, hargs, ndim = ShapeFactory._bins2hclass( bins )
    return hclass(name, name, *hargs)

  def _connectInputs(self, samples, inputDir, skipMissingFiles, friendsDir = None, skimListDir = None):
    listTrees = []
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
      return name, 0
    elif not ( isinstance(bins, tuple) or isinstance( bins, list) ) :
      raise RuntimeError('bin must be an ntuple or an arrays')

    l = len(bins)
    # 1D variable binning
    if l == 1 and isinstance(bins[0], list) :
      ndim = 1
      hclass = TH1D
      xbins = bins[0]
      hargs = (len(xbins)-1, array('d', xbins) )
    elif l == 1 and isinstance( bins[0], list) and isinstance( bins[1], list) :
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


    



