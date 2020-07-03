
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

  def makeNominals(self, sampleName, sample, inFiles, outFile, variables, columns, definitions, cuts, supercut, nuisances, isFisrtJob = False):
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
      totCut = supercut+" && "+cut 
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

        # option to use TUnfold bins
        useTUnfoldBin = False
        if 'useTUnfoldBin' in variable.keys() :
          print "       variable[useTUnfoldBin] = ", variable['useTUnfoldBin']
          useTUnfoldBin = variable['useTUnfoldBin']

        # option to select bin type: response matrix or histogram
        unfoldBinType  = None
        if 'unfoldBinType' in variable.keys() :
          print "       variable[unfoldBinType] = ", variable['unfoldBinType']
          unfoldBinType = variable['unfoldBinType']

        # option to select bin definitions
        unfoldBinDefinition  = None
        if 'unfoldBinDefinition' in variable.keys() :
          print "       variable[unfoldBinDefinition] = ", variable['unfoldBinDefinition']
          unfoldBinDefinition = variable['unfoldBinDefinition']

        combine_cuts = True
	if 'combine_cuts' in sample.keys():
          if sample['combine_cuts'] == False:
            combine_cuts = False

        # sumwxHistX
        sumwxHistX = None
        if 'sumwxHist' in variable.keys():
            sumwxHistX = variable['sumwxHist']
        	
	# create histogram
	if 'weights' in sample.keys() :
	  if 'cut' in sample.keys():
	    outputsHisto = self._draw( variable['name'], variable['range'], combine_cuts, sample['cut'], sample['weight'], sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
	  else:
	    outputsHisto = self._draw( variable['name'], variable['range'], combine_cuts, [],            sample['weight'], sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
	else :
	  if 'cut' in sample.keys():
	    outputsHisto = self._draw( variable['name'], variable['range'], combine_cuts, sample['cut'], sample['weight'], [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
	  else:
	    outputsHisto = self._draw( variable['name'], variable['range'], combine_cuts, [],            sample['weight'], [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, True, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)

	outputsHisto.Write()
    
        # save bin definition just for unfolding histograms
        if isFisrtJob and useTUnfoldBin:
            rt.ptBinningRec.Write()
            rt.ptBinningGen.Write()
            rt.massBinningRec.Write()
            rt.massBinningGen.Write()

            rt.ClearUnfoldBins()
 
        # weight based nuisances: kind = weight
	for nuisanceName, nuisance in nuisances.iteritems():
	  if ('cuts' not in nuisance) or ( ('cuts' in nuisance) and (cutName in nuisance['cuts']) ) :
	    if 'kind' in  nuisance :
	      if nuisance['kind'] == 'weight' :
		for sampleNuisName, configurationNuis in nuisance['samples'].iteritems() :
		  if sampleNuisName ==  sampleName :
		    #newSampleNameUp = sampleName + '_' + nuisance['name'] + 'Up'
		    #newSampleNameDo = sampleName + '_' + nuisance['name'] + 'Down'

		    sysNameUp = '_' + nuisance['name'] + 'Up'
		    sysNameDo = '_' + nuisance['name'] + 'Down'
		    #                                 the first weight is "up", the second is "down"
		    newSampleWeightUp = sample['weight'] + '* (' + configurationNuis[0]  + ")"
		    newSampleWeightDo = sample['weight'] + '* (' + configurationNuis[1]  + ")"

		    if 'weights' in sample.keys() :
	              if 'cut' in sample.keys():
		        outputsHistoUp = self._draw( variable['name'], variable['range'], combine_cuts, sample['cut'], newSampleWeightUp, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameUp)
		        outputsHistoDo = self._draw( variable['name'], variable['range'], combine_cuts, sample['cut'], newSampleWeightDo, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameDo)
		      else:
		        outputsHistoUp = self._draw( variable['name'], variable['range'], combine_cuts, [],            newSampleWeightUp, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameUp)
		        outputsHistoDo = self._draw( variable['name'], variable['range'], combine_cuts, [],            newSampleWeightDo, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameDo)
		    else :
		      #print 'newSampleWeightUp', newSampleWeightUp
	              if 'cut' in sample.keys():
		        outputsHistoUp = self._draw( variable['name'], variable['range'], combine_cuts, sample['cut'], newSampleWeightUp, [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameUp)
		        outputsHistoDo = self._draw( variable['name'], variable['range'], combine_cuts, sample['cut'], newSampleWeightDo, [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameDo)
		      else:
		        outputsHistoUp = self._draw( variable['name'], variable['range'], combine_cuts, [],            newSampleWeightUp, [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameUp)
		        outputsHistoDo = self._draw( variable['name'], variable['range'], combine_cuts, [],            newSampleWeightDo, [],                totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX, sysNameDo)

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
		    sysNameUp = '_' + nuisance['name'] + 'Up'
		    sysNameDo = '_' + nuisance['name'] + 'Down'
		    #                                 the first weight is "up", the second is "down"
		    newSampleWeightUp = sample['weight'] + '* (' + configurationNuis[0]  + ")"
		    newSampleWeightDo = sample['weight'] + '* (' + configurationNuis[1]  + ")"

		    for k, v in nuisance['variablesUp'].iteritems():
		      totCutUp = totCut.replace(variables[k]['name'],v[1])
		      
		    for k, v in nuisance['variablesDo'].iteritems():
		      totCutDo = totCut.replace(variables[k]['name'],v[1])

		    if 'weights' in sample.keys() :
		      if not newVariableNameUp==None:
			if 'cut' in sample.keys():
		          outputsHistoUp = self._draw( newVariableNameUp[1], variable['range'], combine_cuts, sample['cut'], newSampleWeightUp, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, newVariableNameUp[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
			else:
		          outputsHistoUp = self._draw( newVariableNameUp[1], variable['range'], combine_cuts, []           , newSampleWeightUp, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, newVariableNameUp[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
		      if not newVariableNameDo==None:
			if 'cut' in sample.keys():
		          outputsHistoDo = self._draw( newVariableNameDo[1], variable['range'], combine_cuts, sample['cut'], newSampleWeightDo, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, newVariableNameDo[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
			else:
		          outputsHistoDo = self._draw( newVariableNameDo[1], variable['range'], combine_cuts, [],            newSampleWeightDo, sample['weights'], totCut, sampleName, trees, columns, doFold, cutName, newVariableNameDo[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
		    else :
		      #print 'newSampleWeightUp', newSampleWeightUp
		      if not newVariableNameUp==None:
			if 'cut' in sample.keys():
		          outputsHistoUp = self._draw( newVariableNameUp[1], variable['range'], combine_cuts, sample['cut'], newSampleWeightUp, [],                totCut, sampleName, trees, columns, doFold, cutName, newVariableNameUp[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
			else:
		          outputsHistoUp = self._draw( newVariableNameUp[1], variable['range'], combine_cuts, [],            newSampleWeightUp, [],                totCut, sampleName, trees, columns, doFold, cutName, newVariableNameUp[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
		      if not newVariableNameDo==None:
			if 'cut' in sample.keys():
		          outputsHistoDo = self._draw( newVariableNameDo[1], variable['range'], combine_cuts, sample['cut'], newSampleWeightDo, [],                totCut, sampleName, trees, columns, doFold, cutName, newVariableNameDo[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)
			else:
		          outputsHistoDo = self._draw( newVariableNameDo[1], variable['range'], combine_cuts, [],            newSampleWeightDo, [],                totCut, sampleName, trees, columns, doFold, cutName, newVariableNameDo[0], sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition, sumwxHistX)

		    if not newVariableNameUp==None:
		      outputsHistoUp.Write()
		    if not newVariableNameDo==None:
		      outputsHistoDo.Write()

	      elif nuisance['kind' ] == 'PDF' :
		for sampleNuisName, pdfW in nuisance['samples'].iteritems() :
		  if sampleNuisName ==  sampleName :
		    newSampleName = sampleName + '_' + nuisance['name'] 

		    if 'weights' in sample.keys() :
                      if 'cut' in sample.keys():
		        histoList = self._drawPDF(nuisance['type'], pdfW, variable['name'], variable['range'], combine_cuts, sample['cut'], sample['weight'], sample['weights'], totCut, newSampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
                      else:
		        histoList = self._drawPDF(nuisance['type'], pdfW, variable['name'], variable['range'], combine_cuts, [],            sample['weight'], sample['weights'], totCut, newSampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
        
		    else :
		      #print 'newSampleWeightUp', newSampleWeightUp
                      if  'cut' in sample.keys():
	       	        histoList = self._drawPDF(nuisance['type'], pdfW, variable['name'], variable['range'], combine_cuts, sample['cut'], sample['weight'], [],                totCut, newSampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
                      else :
	       	        histoList = self._drawPDF(nuisance['type'], pdfW, variable['name'], variable['range'], combine_cuts, [],            sample['weight'], [],                totCut, newSampleName, trees, columns, doFold, cutName, variableName, sample, False, go1D, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
            

                    print 'length of histoList', len(histoList)
		    for ahist in histoList :
		      #print 'writing ahist'
		      ahist.Write()
		    #outputsHistoUp.Write()
		    #outputsHistoDo.Write()

    self.outFile.Close()
    print 'FINISHED'


  def _draw(self, var, rng, combine_cuts, sample_cut, global_weight, weights, totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, fixZeros, go1D = True, useTUnfoldBin = False, unfoldBinType = None, unfoldBinDefinition = None, sumwxHistX = None, sysName = None) :

    '''
    var           :   the variable to plot
    rng           :   the variable to plot
    global_weight :   the global weight for the samples
    weights       :   the weights 'root file' dependent
    totCut        :   the selection
    trees         :   the list of input files for this particular sample

    =============== variables related to unfolding histograms ===================================
    go1D          : option to select whether to go 1D from 2D or not  
    useTUnfoldBin : use TUnfoldBinning class in TUnfold
    unfoldBinType : miagraion matrix or input histogram    
    sumwxHistX   : draw sumwx histograms
    =============================================================================================
    '''
    
    self._logger.info('Yields by process')

    numTree = 0
    bigName = 'histo_' + sampleName + '_' + cutName + '_' + variableName
    globalCut = "(" + totCut + ") * (" + global_weight + ")" # totCut = superCut + cuts,  globalcut = weight * totCut, 
    hTotal = self._makeshape(bigName, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition) 
    #print 'number of trees >>>>>>>>>>>>>>>>>>', len(trees)
    
    for tree in trees :
          
        #chain = TChain(self._treeName)
        #chain.AddFile(aFile)
        print '   sampleName     {0:<20} : entries {1:^9}'.format(sampleName,tree.GetEntries())

        ## temporary histogram
        shapeName = 'histo_' + sampleName + str(numTree)
        # create a temporary histogram to fill, it will be summed to hTotal as the final histogram
        shape = self._makeshape(shapeName, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)

        self._logger.debug('---'+sampleName+'---')
        self._logger.debug('Formula: '+var+'>>'+shapeName)
        self._logger.debug('Cut:     '+totCut)
        self._logger.debug('ROOTFiles:'+'\n'.join([f.GetTitle() for f in tree.GetListOfFiles()]))

        # if weights vector is not given, do not apply file dependent weights
        if len(weights) != 0 :
          # if weight is not given for a given root file, '-', do not apply file dependent weight for that root file
          if weights[numTree] != '-' :
            globalCut = "(" + globalCut + ") * (" + weights[numTree] + ")" 

        if len(sample_cut) != 0 :
              if combine_cuts: 
                    
                  #globalCut = "(" + totCut + " && " + sample_cut + ") * (" + global_weight + ")"
                  totCut = sample_cut + " && " + totCut
                  globalCut = "(" + totCut + ") * (" + global_weight + ")"
              else :
                  globalCut = "(" + sample_cut + ") * (" + global_weight + ")"

        if sumwxHistX is not None:
            globalCut = globalCut + " * (" + sumwxHistX + ")"
     
        entries = tree.Draw( var+'>>'+shapeName, globalCut, 'goff')
        
        if useTUnfoldBin: 
             
            # for migration matrix
            if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.PtMigrationM:
                # Fill bin zero
                # Caution: if the vector size of branch in an event is zero, the event is just skipped  

                if sumwxHistX is None:              
                    # Fill not selected but generated events, for the case the size of PtRec is not zero: i.e., acceptance correction
                    #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+")", 'goff') 
                    # Fill bin zero for efficiency correction: gen_weight * ( 1 - ( rec_weight) ): i.e., efficiency correction
                    tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + "*(1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')
                    # Fake events: passed Rec Sel but failed to pass Gen Sel
                    #tree.Draw(var.split(":")[0]+":0" + ">>+"+shapeName, "(" + "&&".join(totCut.split("&&")[0:2]) + " && " + "&&".join(totCut.split("&&")[4:]) + " && !(" + totCut.split("&&")[2] + "))*(" + global_weight +")", 'goff') 

                else:
                    tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + "&&".join(totCut.split("&&")[0:2]) + "&& !(" + "&&".join(totCut.split("&&")[2:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+") *" + sumwxHistX, 'goff')
                    tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + "*(1-(" + "*".join(global_weight.split("*")[2:])  +")) *" + sumwxHistX, 'goff')

            if unfoldBinType == ISRUnfold.MassFSRMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM:
                # for FSR response, consider only acceptance correction
                if sumwxHistX is None:              
                    #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+")", 'goff') 
                    pass
                else:
                    tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + "&&".join(totCut.split("&&")[0:2]) + "&& !(" + "&&".join(totCut.split("&&")[2:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+") *" + sumwxHistX, 'goff') 

        nTries = shape.Integral()
        #print ' entries after cut    >> ',entries,' integral:', nTries

        if nTries == 0 :
            
            print 'Warning : entries is 0 for', shapeName
        if math.isnan(nTries) :
            print 'ERROR : entries is nan for', shapeName

        hTotal.Add( shape )
        shape.Delete()
        
        numTree += 1
    
    # fold if needed: add under/overflow bin to the first/last bin
    if doFold == 1 or doFold == 3 :
      self._FoldOverflow (hTotal)
    if doFold == 2 or doFold == 3 :
      self._FoldUnderflow (hTotal)
    
    # go 1d
    hTotalFinal = hTotal
    if go1D: hTotalFinal = self._h2toh1(hTotal)

    # decide the histogram name to be written in the output file
    hTotalFinalName = 'histo_' + sampleName

    if useTUnfoldBin:
        if unfoldBinType == ISRUnfold.PtMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM: # 
            hTotalFinalName = 'hmcPtGenRec'

        if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.MassFSRMigrationM: # 
            hTotalFinalName = 'hmcMassGenRec'
    
        if sysName == None:
            hTotalFinalName = hTotalFinalName

    if sysName != None: hTotalFinalName = hTotalFinalName + sysName

    hTotalFinal.SetTitle(hTotalFinalName)
    hTotalFinal.SetName(hTotalFinalName)

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

  def _drawPDF(self, pdfType, pdfW, var, rng, combine_cuts, sample_cut, global_weight, weights, totCut, sampleName, trees, columns, doFold, cutName, variableName, sample, fixZeros, go1D = True, useTUnfoldBin = False, unfoldBinType = None, unfoldBinDefinition = None) :
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

      hTotalAlphaUp = self._makeshape(bigNameUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
      hTotalAlphaDo = self._makeshape(bigNameDo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)

    elif pdfW is 'PDFWeights_Scale':
      bigNameAUp  = 'histo_' + sampleName + 'AUp_' + cutName + '_' + variableName
      bigNameADo  = 'histo_' + sampleName + 'ADo_' + cutName + '_' + variableName
      bigNameBUp  = 'histo_' + sampleName + 'BUp_' + cutName + '_' + variableName
      bigNameBDo  = 'histo_' + sampleName + 'BDo_' + cutName + '_' + variableName
      bigNameABUp = 'histo_' + sampleName + 'ABUp_' + cutName + '_' + variableName
      bigNameABDo = 'histo_' + sampleName + 'ABDo_' + cutName + '_' + variableName

      hTotalAUp  = self._makeshape(bigNameAUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
      hTotalADo  = self._makeshape(bigNameADo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
      hTotalBUp  = self._makeshape(bigNameBUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
      hTotalBDo  = self._makeshape(bigNameBDo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
      hTotalABUp = self._makeshape(bigNameABUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
      hTotalABDo = self._makeshape(bigNameABDo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)

    elif pdfW is 'PDFWeights_Error':
      hTotal_Err = [None] * 101
      for idx in xrange(101):
        bigName = 'histo_' + sampleName + str(idx) +'_' + cutName + '_' + variableName

        hTotal_Err[idx] = self._makeshape(bigName, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
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

      if len(sample_cut) != 0 :
            if combine_cuts:
                globalCut = "(" + totCut + " && " + sample_cut + ") * (" + global_weight + ")"
            else :
                globalCut = "(" + sample_cut + ") * (" + global_weight + ")"

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
	shapeDo = self._makeshape(shapeNameDo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
	shapeUp = self._makeshape(shapeNameUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)

	# fill
        entriesDo = tree.Draw( var+'>>'+shapeNameDo, globalCutDo, 'goff')
        entriesUp = tree.Draw( var+'>>'+shapeNameUp, globalCutUp, 'goff')

        if useTUnfoldBin:
          # for migration matrix
          if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.PtMigrationM:
              # Fill bin zero
              # Caution: if the vector size of branch in an event is zero, the event is just skipped  

              # Fill not selected but generated events, for the case the size of PtRec is not zero: i.e., acceptance correction
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameDo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_AlphaS[0]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_AlphaS[1]))", 'goff')

              # Fill not selected but generated events, for the case the size of PtRec is zero
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + totCut.split("&&")[0] + "&& (@ptRec.size()==0))*(" + "*".join(global_weight.split("*")[0:2])+")", 'goff')
              #

              # Fill bin zero for efficiency correction: gen_weight * ( 1 - ( rec_weight) ): i.e., efficiency correction
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameDo, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_AlphaS[0]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameUp, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_AlphaS[1]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')

          if unfoldBinType == ISRUnfold.MassFSRMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM:
              # for FSR response, consider only acceptance correction
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameDo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_AlphaS[0]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_AlphaS[1]))", 'goff')
              pass


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

        shapeAUp  = self._makeshape( shapeNameAUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
        shapeADo  = self._makeshape( shapeNameADo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
        shapeBUp  = self._makeshape( shapeNameBUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
        shapeBDo  = self._makeshape( shapeNameBDo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
        shapeABUp = self._makeshape( shapeNameABUp, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
        shapeABDo = self._makeshape( shapeNameABDo, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)

	# fill
        entriesAUp=  tree.Draw( var+'>>'+shapeNameAUp,  globalCut_muAUp,  'goff' )
        entriesADo=  tree.Draw( var+'>>'+shapeNameADo,  globalCut_muADo,  'goff' )
        entriesBUp=  tree.Draw( var+'>>'+shapeNameBUp,  globalCut_muBUp,  'goff' )
        entriesBDo=  tree.Draw( var+'>>'+shapeNameBDo,  globalCut_muBDo,  'goff' )
        entriesABUp= tree.Draw( var+'>>'+shapeNameABUp, globalCut_muABUp, 'goff' )
        entriesABDo= tree.Draw( var+'>>'+shapeNameABDo, globalCut_muABDo, 'goff' )

        if useTUnfoldBin:
          # for migration matrix
          if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.PtMigrationM:
              # Fill bin zero
              # Caution: if the vector size of branch in an event is zero, the event is just skipped  

              # Fill not selected but generated events, for the case the size of PtRec is not zero: i.e., acceptance correction
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameAUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[1]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameADo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[2]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameBUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[3]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameBDo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[6]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameABUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[4]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameABDo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[8]))", 'goff')

              # Fill not selected but generated events, for the case the size of PtRec is zero
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + totCut.split("&&")[0] + "&& (@ptRec.size()==0))*(" + "*".join(global_weight.split("*")[0:2])+")", 'goff')
              #
              # Fill bin zero for efficiency correction: gen_weight * ( 1 - ( rec_weight) ): i.e., efficiency correction
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameAUp, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_Scale[1]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameADo, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_Scale[2]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameBUp, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_Scale[3]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameBDo, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_Scale[6]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameABUp, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_Scale[4]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')
              tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameABDo, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_Scale[8]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')

          if unfoldBinType == ISRUnfold.MassFSRMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM:
              # for FSR response, consider only acceptance correction
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameAUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[1]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameADo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[2]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameBUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[3]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameBDo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[6]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameABUp, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[4]))", 'goff')
              #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeNameABDo, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Scale[8]))", 'goff')
              pass

        
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
	  shape     = self._makeshape( shapeName, rng, useTUnfoldBin, unfoldBinType, unfoldBinDefinition)
	  #  fill
          entries = tree.Draw( var+'>>'+shapeName, globalCut_pdfErr[idx], 'goff')

          if useTUnfoldBin:
            # for migration matrix
            if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.PtMigrationM:
                # Fill bin zero
                # Caution: if the vector size of branch in an event is zero, the event is just skipped  

                # Fill not selected but generated events, for the case the size of PtRec is not zero: i.e., acceptance correction
                #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Error[" + str(idx) + "]))", 'goff')

                # Fill not selected but generated events, for the case the size of PtRec is zero
                #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + totCut.split("&&")[0] + "&& (@ptRec.size()==0))*(" + "*".join(global_weight.split("*")[0:2])+")", 'goff')
                #

                # Fill bin zero for efficiency correction: gen_weight * ( 1 - ( rec_weight) ): i.e., efficiency correction
                tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + totCut + ")*(" + "*".join(global_weight.split("*")[0:2]) + " * (PDFWeights_Error[" + str(idx) + "]) * (1-(" + "*".join(global_weight.split("*")[2:])  +")))", 'goff')

            if unfoldBinType == ISRUnfold.MassFSRMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM:
                # for FSR response, consider only acceptance correction
                #tree.Draw( "0:"+var.split(":")[1] +'>>+'+shapeName, "(" + "&&".join(totCut.split("&&")[0:4]) + "&& !(" + "&&".join(totCut.split("&&")[4:]) + "))*(" + "*".join(global_weight.split("*")[0:2])+" * (PDFWeights_Error[" + str(idx) + "]))", 'goff')
                pass

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
      hTotalFinalAlphaUp = hTotalAlphaUp
      hTotalFinalAlphaDo = hTotalAlphaDo
      if go1D: hTotalFinalAlphaUp = self._h2toh1(hTotalAlphaUp)
      if go1D: hTotalFinalAlphaDo = self._h2toh1(hTotalAlphaDo)
      
      if useTUnfoldBin == False:
        hTotalFinalAlphaUp.SetTitle('histo_' + sampleName+ 'Up')
        hTotalFinalAlphaDo.SetTitle('histo_' + sampleName+ 'Down')
        hTotalFinalAlphaUp.SetName('histo_' + sampleName + 'Up')
        hTotalFinalAlphaDo.SetName('histo_' + sampleName + 'Down')
      else :

          hTotalFinalAlphaUp.SetTitle('histo_' + sampleName+ 'Up') # sampleName = sample name + AlphaS
          hTotalFinalAlphaDo.SetTitle('histo_' + sampleName+ 'Down')
          hTotalFinalAlphaUp.SetName('histo_' + sampleName + 'Up')
          hTotalFinalAlphaDo.SetName('histo_' + sampleName + 'Down')

          if unfoldBinType == ISRUnfold.PtMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM: # 
            hTotalFinalAlphaUp.SetTitle('hmcPtGenRec_AlphaSUp')
            hTotalFinalAlphaDo.SetTitle('hmcPtGenRec_AlphaSDown')
            hTotalFinalAlphaUp.SetName('hmcPtGenRec_AlphaSUp')
            hTotalFinalAlphaDo.SetName('hmcPtGenRec_AlphaSDown')

          if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.MassFSRMigrationM: # 
            hTotalFinalAlphaUp.SetTitle('hmcMassGenRec_AlphaSUp')
            hTotalFinalAlphaDo.SetTitle('hmcMassGenRec_AlphaSDown')
            hTotalFinalAlphaUp.SetName('hmcMassGenRec_AlphaSUp')
            hTotalFinalAlphaDo.SetName('hmcMassGenRec_AlphaSDown')

    if pdfW is 'PDFWeights_Scale':

      hTotalFinalAUp = hTotalAUp
      hTotalFinalADo = hTotalADo
      if go1D: hTotalFinalAUp = self._h2toh1(hTotalAUp)
      if go1D: hTotalFinalADo = self._h2toh1(hTotalADo)

      if useTUnfoldBin == False:
        hTotalFinalAUp.SetTitle('histo_' + sampleName+ 'AUp')
        hTotalFinalADo.SetTitle('histo_' + sampleName+ 'ADown')
        hTotalFinalAUp.SetName('histo_' + sampleName + 'AUp')
        hTotalFinalADo.SetName('histo_' + sampleName + 'ADown')
      else :
        hTotalFinalAUp.SetTitle('histo_' + sampleName+ 'AUp')
        hTotalFinalADo.SetTitle('histo_' + sampleName+ 'ADown')
        hTotalFinalAUp.SetName('histo_' + sampleName + 'AUp')
        hTotalFinalADo.SetName('histo_' + sampleName + 'ADown')

        if unfoldBinType == ISRUnfold.PtMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM: #
            hTotalFinalAUp.SetTitle('hmcPtGenRec_ScaleAUp')
            hTotalFinalADo.SetTitle('hmcPtGenRec_ScaleADown')
            hTotalFinalAUp.SetName('hmcPtGenRec_ScaleAUp')
            hTotalFinalADo.SetName('hmcPtGenRec_ScaleADown')
        if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.MassFSRMigrationM: # 
            hTotalFinalAUp.SetTitle('hmcMassGenRec_ScaleAUp')
            hTotalFinalADo.SetTitle('hmcMassGenRec_ScaleADown')
            hTotalFinalAUp.SetName('hmcMassGenRec_ScaleAUp')
            hTotalFinalADo.SetName('hmcMassGenRec_ScaleADown')

      hTotalFinalBUp = hTotalBUp
      hTotalFinalBDo = hTotalBDo
      if go1D: hTotalFinalBUp = self._h2toh1(hTotalBUp)
      if go1D: hTotalFinalBDo = self._h2toh1(hTotalBDo)

      if useTUnfoldBin == False:
        hTotalFinalBUp.SetTitle('histo_' + sampleName+ 'BUp')
        hTotalFinalBDo.SetTitle('histo_' + sampleName+ 'BDown')
        hTotalFinalBUp.SetName('histo_' + sampleName + 'BUp')
        hTotalFinalBDo.SetName('histo_' + sampleName + 'BDown')
      else:
        hTotalFinalBUp.SetTitle('histo_' + sampleName+ 'BUp')
        hTotalFinalBDo.SetTitle('histo_' + sampleName+ 'BDown')
        hTotalFinalBUp.SetName('histo_' + sampleName + 'BUp')
        hTotalFinalBDo.SetName('histo_' + sampleName + 'BDown') 

        if unfoldBinType == ISRUnfold.PtMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM: #
            hTotalFinalBUp.SetTitle('hmcPtGenRec_ScaleBUp')
            hTotalFinalBDo.SetTitle('hmcPtGenRec_ScaleBDown')
            hTotalFinalBUp.SetName('hmcPtGenRec_ScaleBUp')
            hTotalFinalBDo.SetName('hmcPtGenRec_ScaleBDown')
        if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.MassFSRMigrationM: #
            hTotalFinalBUp.SetTitle('hmcMassGenRec_ScaleBUp')
            hTotalFinalBDo.SetTitle('hmcMassGenRec_ScaleBDown')
            hTotalFinalBUp.SetName('hmcMassGenRec_ScaleBUp')
            hTotalFinalBDo.SetName('hmcMassGenRec_ScaleBDown')

      hTotalFinalABUp = hTotalABUp
      hTotalFinalABDo = hTotalABDo
      if go1D: hTotalFinalABUp = self._h2toh1(hTotalABUp)
      if go1D: hTotalFinalABDo = self._h2toh1(hTotalABDo)

      if useTUnfoldBin == False:
        hTotalFinalABUp.SetTitle('histo_' + sampleName+ 'ABUp')
        hTotalFinalABDo.SetTitle('histo_' + sampleName+ 'ABDown')
        hTotalFinalABUp.SetName('histo_' + sampleName + 'ABUp')
        hTotalFinalABDo.SetName('histo_' + sampleName + 'ABDown')
      else:
        hTotalFinalABUp.SetTitle('histo_' + sampleName+ 'ABUp')
        hTotalFinalABDo.SetTitle('histo_' + sampleName+ 'ABDown')
        hTotalFinalABUp.SetName('histo_' + sampleName + 'ABUp')
        hTotalFinalABDo.SetName('histo_' + sampleName + 'ABDown')
    
        if unfoldBinType == ISRUnfold.PtMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM: #
            hTotalFinalABUp.SetTitle('hmcPtGenRec_ScaleABUp')
            hTotalFinalABDo.SetTitle('hmcPtGenRec_ScaleABDown')
            hTotalFinalABUp.SetName('hmcPtGenRec_ScaleABUp')
            hTotalFinalABDo.SetName('hmcPtGenRec_ScaleABDown')
        if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.MassFSRMigrationM: #
            hTotalFinalABUp.SetTitle('hmcMassGenRec_ScaleABUp')
            hTotalFinalABDo.SetTitle('hmcMassGenRec_ScaleABDown')
            hTotalFinalABUp.SetName('hmcMassGenRec_ScaleABUp')
            hTotalFinalABDo.SetName('hmcMassGenRec_ScaleABDown')

    if pdfW is 'PDFWeights_Error':
      hTotalFinalErr = [None] * 101
      for idx in xrange(101):
        hTotalFinalErr[idx] = hTotal_Err[idx]
        if go1D: hTotalFinalErr[idx] = self._h2toh1(hTotal_Err[idx])
        
        if useTUnfoldBin == False:
            hTotalFinalErr[idx].SetTitle('histo_' + sampleName+ str(idx).zfill(3))
            hTotalFinalErr[idx].SetName('histo_' + sampleName + str(idx).zfill(3))
        else :
            hTotalFinalErr[idx].SetTitle('histo_' + sampleName+ str(idx).zfill(3))
            hTotalFinalErr[idx].SetName('histo_' + sampleName + str(idx).zfill(3))

            if unfoldBinType == ISRUnfold.PtMigrationM or unfoldBinType == ISRUnfold.PtFSRMigrationM: # 
                hTotalFinalErr[idx].SetTitle('hmcPtGenRec_PDFerror' + str(idx).zfill(3))
                hTotalFinalErr[idx].SetName('hmcPtGenRec_PDFerror' + str(idx).zfill(3))
            if unfoldBinType == ISRUnfold.MassMigrationM or unfoldBinType == ISRUnfold.MassFSRMigrationM: #
                hTotalFinalErr[idx].SetTitle('hmcMassGenRec_PDFerror' + str(idx).zfill(3))
                hTotalFinalErr[idx].SetName('hmcMassGenRec_PDFerror' + str(idx).zfill(3))


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
  def _makeshape( name, bins, useTUnfoldBin = False, unfoldBinType = None, unfoldBinDefinition = None):

    if useTUnfoldBin == False :
        hclass, hargs, ndim = ShapeFactory._bins2hclass( bins )
        return hclass(name, name, *hargs)

    elif useTUnfoldBin :
        # Use TUnfoldBinnig
        rt.SetMassBinningRec(unfoldBinDefinition)
        rt.SetPtBinningRec(unfoldBinDefinition)
        rt.SetMassBinningGen(unfoldBinDefinition)
        rt.SetPtBinningGen(unfoldBinDefinition)

        if unfoldBinType == ISRUnfold.PtRec2DHist:     return rt.get2DHistogramPtRec(name) 
        if unfoldBinType == ISRUnfold.PtGen2DHist:     return rt.get2DHistogramPtGen(name) 
        if unfoldBinType == ISRUnfold.PtMigrationM:    return rt.getMigrationMforPt(name) 
        if unfoldBinType == ISRUnfold.MassRec2DHist:   return rt.get2DHistogramMassRec(name) 
        if unfoldBinType == ISRUnfold.MassGen2DHist:   return rt.get2DHistogramMassGen(name) 
        if unfoldBinType == ISRUnfold.MassMigrationM:  return rt.getMigrationMforMass(name) 
        if unfoldBinType == ISRUnfold.PtFSRMigrationM:  return rt.getFSRMigrationMforPt(name) 
        if unfoldBinType == ISRUnfold.MassFSRMigrationM:  return rt.getFSRMigrationMforMass(name) 

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

