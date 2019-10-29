#!/usr/bin/env python
import os
from array import array
import math
import ROOT
import logging
from collections import OrderedDict

class PlotContainer:

  generalCounter = 0

  def __init__(self, cutName, variableName, plotNormalizedDistributions):
    self.cutName = cutName
    self.variableName = variableName
    self._plotNormalizedDistributions = plotNormalizedDistributions

    self.list_thsData       = {}
    self.list_thsSignal     = {}
    self.list_thsBackground = {}

    self.list_thsSignal_grouped     = {}
    self.list_thsSignalSup_grouped  = {}
    self.list_thsBackground_grouped = {}

    self.list_tcanvas               = {}
    self.list_tcanvasRatio          = {}
    self.list_weight_X_tcanvasRatio = {}
    self.list_tcanvasDifference          = {}
    self.list_weight_X_tcanvasDifference = {}
    self.list_tcanvasSigVsBkg       = {}

    self.histos = {}
    self.histo = None
    self.histos_grouped = {}

    self.tgrData        = None
    self.tgrData_vx     = array('f')
    self.tgrData_evx    = array('f')
    self.tgrData_vy     = array('f')
    self.tgrData_evy_up = array('f')
    self.tgrData_evy_do = array('f')

    #these vectors are needed for nuisances accounting
    self.nuisances_vy_up = {}
    self.nuisances_vy_do = {}
    self.nuisances_err_up = array('f')
    self.nuisances_err_do = array('f')

    self.tgrMC    = None
    self.tgrMC_vy = array('f')
    self.tgrMC_vx = array('f')
    self.tgrMC_evx = array('f')

    self.canvasNameTemplateRatio = 'Ratio_' + self.cutName + "_" + self.variableName
    self.canvasNameTemplateDifference = 'Difference_' + self.cutName + "_" + self.variableName
    self.canvasNameTemplate = self.cutName + "_" + self.variableName

    self.sigSupList = []
    self.sigSupList_grouped = []
    # list of additional histograms to be used in the ratio plot
    self.sigForAdditionalRatioList = {}
    self.sigForAdditionalDifferenceList = {}

    # enhanced list of nuisances, including bin-by-bin 
    self.mynuisances = {}

    self.nexpected = 0

    self.tgrDataOverPF  = None
    self.histoPF        = None
    self.tgrDataOverMC  = None   
    self.tgrDataMinusMC = None  
    self.tgrMCOverMC    = None
    self.tgrMCMinusMC   = None

    self.tgrRatioList = {}
    self.tgrDifferenceList = {}

    self.frame = None

  def makeCanvas(self):
    self.tcanvas = ROOT.TCanvas( self.cutName + "_" + self.variableName, "distro" , 800, 600 )
    self.tcanvasRatio = ROOT.TCanvas( "Ratio" + self.cutName + "_" + self.variableName, "Ratio", 800, 800 )
    weight_X_tcanvasRatio = ROOT.TCanvas( "weight_X_tcanvasRatio" + self.cutName + "_" + self.variableName, "weight_X_tcanvasRatio", 800, 800 )
    tcanvasDifference = ROOT.TCanvas( "Difference" + self.cutName + "_" + self.variableName, "Difference", 800, 800 )
    weight_X_tcanvasDifference = ROOT.TCanvas( "weight_X_tcanvasDifference" + self.cutName + "_" + self.variableName, "weight_X_tcanvasDifference", 800, 800 )
    if self._plotNormalizedDistributions : #XXX
      self.tcanvasSigVsBkg = ROOT.TCanvas( "SigVsBkg" + self.cutName + "_" + self.variableName, "" , 800, 600 )

    self.list_tcanvas [PlotContainer.generalCounter] = self.tcanvas
    self.list_tcanvasRatio [PlotContainer.generalCounter] = self.tcanvasRatio
    self.list_weight_X_tcanvasRatio [PlotContainer.generalCounter] = weight_X_tcanvasRatio
    self.list_tcanvasDifference [PlotContainer.generalCounter] = tcanvasDifference
    self.list_weight_X_tcanvasDifference [PlotContainer.generalCounter] = weight_X_tcanvasDifference
    if self._plotNormalizedDistributions : #XXX
      self.list_tcanvasSigVsBkg [PlotContainer.generalCounter] = self.tcanvasSigVsBkg
	
    self.tcanvas.cd()


  def makeStack(self):
    cutName = self.cutName
    variableName = self.variableName

    ROOT.gROOT.cd()
    self.thsData = ROOT.THStack ("thsData_" + cutName + "_" + variableName, "thsData_" + cutName + "_" + variableName)
    self.thsSignal = ROOT.THStack ("thsSignal_" + cutName + "_" + variableName, "thsSignal_" + cutName + "_" + variableName)
    self.thsBackground = ROOT.THStack ("thsBackground_" + cutName + "_" + variableName,"thsBackground_" + cutName + "_" + variableName)

    self.thsSignal_grouped = ROOT.THStack ("thsSignal_grouped_" + cutName + "_" + variableName, "thsSignal_grouped_" + cutName + "_" + variableName)
    self.thsBackground_grouped = ROOT.THStack ("thsBackground_grouped_" + cutName + "_" + variableName,"thsBackground_grouped_" + cutName + "_" + variableName)


    self.list_thsData [PlotContainer.generalCounter] = self.thsData
    self.list_thsSignal [PlotContainer.generalCounter] = self.thsSignal
    self.list_thsBackground [PlotContainer.generalCounter] = self.thsBackground
    self.list_thsSignal_grouped [PlotContainer.generalCounter] = self.thsSignal_grouped
    self.list_thsBackground_grouped [PlotContainer.generalCounter] = self.thsBackground_grouped
 
  def updateCounter(self):
    PlotContainer.generalCounter += 1




class PlotFactory:
  _logger = logging.getLogger('PlotFactory')

  def __init__(self):

    self._tag = ''
    self._variables = {}
    self._cuts = {}
    self._nuisances = {}
    samples = OrderedDict()
    self._samples = samples
    self._outputDirPlots = 'test'
    self._showIntegralLegend = 1

    self._FigNamePF = ''


  def makePlot(self, inputFile, outDir, variables, cuts, samples, plot, nuisances, legend, groupPlot):
    print "===================="
    print "===== makePlot ====="
    print "===================="

    self.defineStyle()

    self._variables = variables
    self._samples   = samples
    self._cuts      = cuts
    self._plot      = plot
    self._nuisances = nuisances
    self._legend    = legend
    self._groupPlot = groupPlot
    self._outputDirPlots    = outDir
    
    if self._outputDirPlots == "./":
      self._outputDirPlots = 'Plot_'+self._tag
    else:
      self._outputDirPlots = self._outputDirPlots + self._tag

    print 'Plot out dir',self._outputDirPlots
    os.system('mkdir '+self._outputDirPlots)

    ROOT.TH1.SetDefaultSumw2(True)
    ROOT.gROOT.cd()

    list_PlotContainer = []

    print 'inputFile', inputFile
    self.fileIn = ROOT.TFile(inputFile, 'READ')

    #---- save one TCanvas for every cut and every variable

    for cutName in self._cuts:
      print 'cut =', cutName
      for variableName, variable in self._variables.iteritems():
	if 'cuts' in variable and cutName not in variable['cuts']:
	  continue

	if type(self.fileIn) is not dict and not self.fileIn.GetDirectory(cutName+"/"+variableName):
	  continue

	print 'variableName = ', variableName

	if not "divideByBinWidth" in variable.keys():
	  variable["divideByBinWidth"] = 0
	########
	plot_container = PlotContainer(cutName,variableName, self._plotNormalizedDistributions)
	plot_container.makeCanvas()
	plot_container.makeStack()
	plot_container.updateCounter()
	list_PlotContainer.append(plot_container)
	########

	for sampleName, plotdef in plot.iteritems():
	  if 'samples' in variable and sampleName not in variable['samples']:
	    continue
          self.addShape(sampleName, plot_container, variable, plotdef)
	  self.SetDataStyle(sampleName, plot_container, variable, plotdef)
          self.SetMCStyle(sampleName, plot_container, variable, plotdef)
	  self.HandleNuisanceShape(sampleName, plot_container, variable, plotdef)
	  self.FillGroupHisto(sampleName, plot_container)

        self.DecorateGroupHisto(plot_container)
	self.SaveBkgSumErrCentral(plot_container)
	self.addSigToBkg(sampleName, plot_container, variable, plotdef)
	self.calcNuisanceErr(plot_container)
	self.prepareHistoPF(plot_container)
        self.prepareRatio(plot_container, variable)
	self.prepareGroupedHistos(plot_container, variable)
	self.setCanvasFrame(plot_container, variable)
	self.draw(plot_container,variable)


  def addShape(self, sampleName_, plot_container_, variable_, plotdef_):
    cutName = plot_container_.cutName
    variableName = plot_container_.variableName
    shapeName = cutName + '/' + variableName + '/histo_' + sampleName_
    histos = plot_container_.histos
    print 'infile:',self.fileIn,'	-> shapeName = ', shapeName
    if type(self.fileIn) is dict:
      plot_container_.histo = self.fileIn[sampleName_].Get(shapeName)
    else:
      print 'before getting', shapeName
      plot_container_.histo = self.fileIn.Get(shapeName)
      print 'after getting', shapeName

    histoName = 'new_histo_' + sampleName_ + '_' + cutName + '_' + variableName
    histos[sampleName_] = plot_container_.histo.Clone(histoName)
    if 'scale' in plotdef_.keys():
      histos[sampleName_].Scale(plotdef_['scale'])
      print 'after clone', sampleName_

    # apply cut dependent scale factors
    # for example when plotting different phase spaces
    if 'cuts' in plotdef_.keys():
      if cutName in plotdef_['cuts']:
        histos[sampleName_].Scale( float( plotdef_['cuts'][cutName] ) )

    if plotdef_['isData'] == 1:
      if variable_['divideByBinWidth'] == 1:
        histos[sampleName_].Scale(1, "width")
        plot_container_.thsData.Add(histos[sampleName_])
      else:
        plot_container_.thsData.Add(histos[sampleName_])

  def SetDataStyle(self, sampleName_, plot_container_, variable_, plotdef_):
    # data style ===================================================================================

    if not plotdef_['isData'] == 1:
      return

    histos = plot_container_.histos
    tgrData_vx = plot_container_.tgrData_vx 
    tgrData_evx = plot_container_.tgrData_evx
    tgrData_vy = plot_container_.tgrData_vy 
    tgrData_evy_up = plot_container_.tgrData_evy_up
    tgrData_evy_do = plot_container_.tgrData_evy_do

    histos[sampleName_].SetMarkerColor(plotdef_['color'])
    histos[sampleName_].SetMarkerSize(1)
    histos[sampleName_].SetMarkerStyle(20)
    histos[sampleName_].SetLineColor(plotdef_['color'])

    # blind data
    if 'isBlind' in plotdef_.keys():
      if plotdef_['isBlind'] == 1:
	for iBin in range(1, histos[sampleName_].GetNbinsX()+1):
	  histos[sampleName_].SetBinContent(iBin,0)
	  histos[sampleName_].SetBinError  (iBin,0)
	histos[sampleName_].Reset()

    # first time fill vectors X axis
    if len(tgrData_vx) == 0:
      plot_container_.dataColor = histos[sampleName_].GetMarkerColor()
      for iBin in range(1, histos[sampleName_].GetNbinsX()+1):
        tgrData_vx.append( histos[sampleName_].GetBinCenter(iBin))
        tgrData_evx.append( histos[sampleName_].GetBinWidth(iBin)/2.)
        tgrData_vy.append( histos[sampleName_].GetBinContent(iBin))
        if( 'isSignal' not in plotdef_.keys() or plotdef_['isSignal'] !=3) and not ('isBlind' in plotdef_.keys() and plotdef_['isBlind'] == 1):
          if variable_['divideByBinWidth'] == 1:
            tgrData_evy_up.append( self.GetPoissError(histos[sampleName_].GetBinContent(iBin) * histos[sampleName_].GetBinWidth(iBin),0,1)/histos[sampleName_].GetBinWidth(iBin) )
            tgrData_evy_do.append( self.GetPoissError(histos[sampleName_].GetBinContent(iBin) * histos[sampleName_].GetBinWidth(iBin),1,0)/histos[sampleName_].GetBinWidth(iBin) )
          else:
            tgrData_evy_up.append( self.GetPoissError(histos[sampleName_].GetBinContent (iBin), 0, 1) )
            tgrData_evy_do.append( self.GetPoissError(histos[sampleName_].GetBinContent (iBin), 1, 0) )
        else :
          tgrData_evy_up.append( 0 )
          tgrData_evy_do.append( 0 )
    
    else :
      for iBin in range(1, histos[sampleName_].GetNbinsX() + 1):
        tgrData_vx[iBin -1] = ( histos[sampleName_].GetBinCenter (iBin) )
        tgrData_evx.append( histos[sampleName_].GetBinWidth (iBin) / 2.) # do we need this after we did this for the first iteration, somehow we don't use for bin>GetNbinsX
        tgrData_vy[iBin-1] += histos[sampleName_].GetBinContent (iBin)
        if 'isSignal' not in plotdef_.keys() or plotdef_['isSignal'] == 3 :
	  if variable_['divideByBinWidth'] == 1:
	    tgrData_evy_up[iBin-1] = SumQ ( tgrData_evy_up[iBin-1], self.GetPoissError(histos[sampleName_].GetBinContent(iBin) * histos[sampleName_].GetBinWidth(iBin), 0, 1) / histos[sampleName_].GetBinWidth (iBin) )
	    tgrData_evy_do[iBin-1] = SumQ ( tgrData_evy_up[iBin-1], self.GetPoissError(histos[sampleName_].GetBinContent(iBin) * histos[sampleName_].GetBinWidth(iBin), 1, 0) / histos[sampleName_].GetBinWidth (iBin) )
	  else :
	    tgrData_evy_up[iBin-1] = SumQ ( tgrData_evy_up[iBin-1], self.GetPoissError(histos[sampleName_].GetBinContent(iBin), 0, 1) )
	    tgrData_evy_do[iBin-1] = SumQ ( tgrData_evy_up[iBin-1], self.GetPoissError(histos[sampleName_].GetBinContent(iBin), 1, 0) )


  def SetMCStyle(self, sampleName_, plot_container_, variable_, plotdef_):
    
    if not plotdef_['isData'] == 0 :
      return
    # _____________________________________________________________________________
    # MC style
    # _____________________________________________________________________________
    histos = plot_container_.histos
    thsSignal = plot_container_.thsSignal
    sigSupList = plot_container_.sigSupList
    sigForAdditionalRatioList = plot_container_.sigForAdditionalRatioList
    sigForAdditionalDifferenceList = plot_container_.sigForAdditionalDifferenceList
    thsBackground = plot_container_.thsBackground

    # only background "filled" histogram
    histos[sampleName_].SetFillColor(plotdef_['color'])
    if 'style' in plotdef_.keys():
      print sampleName_,'style changing to',plotdef_['style']
      histos[sampleName_].SetFillStyle(plotdef_['style'])
    else:
      histos[sampleName_].SetFillStyle(3001)

    if 'lineWidth' in plotdef_.keys():
      print sampleName_,'lineWidth changing to',plotdef_['lineWidth']
      histos[sampleName_].SetLineWidth(plotdef_['lineWidth'])
    else:
      pass

    histos[sampleName_].SetLineColor(plotdef_['color'])

    if plotdef_['isSignal'] == 1 :
      if variable_['divideByBinWidth'] == 1:
        histos[sampleName_].Scale(1, "width")
  	thsSignal.Add(histos[sampleName_])
      else:
        thsSignal.Add(histos[sampleName_])
    elif plotdef_['isSignal'] == 2  or plotdef_['isSignal'] == 3 :
      if variable_['divideByBinWidth'] == 1:
        histos[sampleName_].Scale(1,"width")
  	sigSupList.append(histos[sampleName_])
      else:
  	sigSupList.append(histos[sampleName_])
      if plotdef_['isSignal'] == 3  :
  	sigForAdditionalRatioList[sampleName_] = histos[sampleName_]
  	sigForAdditionalDifferenceList[sampleName_] = histos[sampleName_]
    else:
      plot_container_.nexpected += histos[sampleName_].Integral(-1,-1)
      if variable_['divideByBinWidth'] == 1:
  	histos[sampleName_].Scale(1,"width")
  	thsBackground.Add(histos[sampleName_])
      else:
  	thsBackground.Add(histos[sampleName_])
    

  def HandleNuisanceShape(self, sampleName_, plot_container_, variable_, plotdef_):

    if not plotdef_['isData'] == 0 :
      return

    cutName = plot_container_.cutName
    variableName = plot_container_.variableName
    sampleName = sampleName_
    histos = plot_container_.histos
    histo = plot_container_.histo
    mynuisances = plot_container_.mynuisances
    nuisances_vy_up = plot_container_.nuisances_vy_up
    nuisances_vy_do = plot_container_.nuisances_vy_do

    for nuisanceName, nuisance in self._nuisances.iteritems():
      if('cuts' not in nuisance) or ( ('cuts' in nuisance) and (cutName in nuisance['cuts']) ) : # run only if this nuisance will affect the phase space defined in "cut"
	if nuisanceName == 'stat' : # 'stat' has a separate treatment, it's the MC/data statistics
	  if 'samples' in nuisance.keys():
	    if sampleName in nuisance['samples'].keys() :
	      if nuisance['samples'][sampleName]['typeStat'] == 'uni' : # unified approach
		print 'In principle nothing to be done here ... just wait'
	      if nuisance['samples'][sampleName]['typeStat'] == 'bbb' : # bin-by-bin
		# add N ad hoc nuisances, one for each bin
		for iBin in range(1, histos[sampleName].GetNbinsX()+1):
		  if ('ibin_' + str(iBin) + '_stat') not in mynuisances.keys() : # if new, add the new nuisance
		    mynuisances['ibin_' + str(iBin) + '_stat'] = {
			'samples' : { sampleName : '1.00', },
			}
		  else : # otherwise just add the new sample in the list of samples to be considered
		    mynuisances['ibin_' + str(iBin) + '_stat']['samples'][sampleName] = '1.00'
	else :
	  if nuisanceName not in mynuisances.keys() :
	    if 'type' in nuisance.keys() and (nuisance['type'] == 'rateParam' or nuisance['type'] == 'lnU') :
	      pass
	      #print "skip this nuisance since 100 percent uncertainty :: ", nuisanceName
	    else :
	      mynuisances[nuisanceName] = self._nuisances[nuisanceName]

    for nuisanceName, nuisance in mynuisances.iteritems():
      is_this_nuisance_to_be_considered = False
      if 'samples' in nuisance.keys() :
	for sampleNuisName, configurationNuis in nuisance['samples'].iteritems() :
	  if sampleNuisName == sampleName: # complain only if the nuisance was supposed to show up
	    print 'nuisance cfg', configurationNuis, 'for', sampleName
	    is_this_nuisance_to_be_considered = True
      elif 'all' in nuisance.keys() and nuisance ['all'] == 1 : # for all samples
	is_this_nuisance_to_be_considered = True

      histoUp = None
      histoDown = None

      if not ( ('cuts' not in nuisance) or ( ('cuts' in nuisance) and (cutName in nuisance['cuts']) ) ) : # run only if this nuisance will affect the phase space defined in "cut"
	is_this_nuisance_to_be_considered = False

      if is_this_nuisance_to_be_considered :
	if nuisance.get('kind')=='sampleChange':
	  for sampleNuisName, sampleToChange in nuisance['samplesUp'].iteritems():
	    if sampleNuisName == sampleName:
	      shapeNameUp = cutName+"/"+variableName+'/histo_' + sampleToChange
	  for sampleNuisName, sampleToChange in nuisance['samplesDo'].iteritems():
	    if sampleNuisName == sampleName:
	      shapeNameDown = cutName+"/"+variableName+'/histo_' + sampleToChange
	elif nuisance.get('kind')=='variableChange':
	  if variableName in nuisance['variablesUp']:
	    shapeNameUp = cutName+"/"+nuisance['variablesUp'][variableName][0]+'/histo_' + sampleName
	  else:
	    shapeNameUp = cutName+"/"+variableName+'/histo_' + sampleName
	  if variableName in nuisance['variablesDo']:
	    shapeNameDown = cutName+"/"+nuisance['variablesDo'][variableName][0]+'/histo_' + sampleName
	  else:
	    shapeNameDown = cutName+"/"+variableName+'/histo_' + sampleName
	elif 'name' in nuisance:
	  shapeNameUp = cutName+"/"+variableName+'/histo_' + sampleName+"_"+nuisance['name']+"Up"
	  shapeNameDown = cutName+"/"+variableName+'/histo_' + sampleName+"_"+nuisance['name']+"Down"
	else:
	  shapeNameUp = cutName+"/"+variableName+'/histo_' + sampleName+"_"+nuisanceName+"Up"
	  shapeNameDown = cutName+"/"+variableName+'/histo_' + sampleName+"_"+nuisanceName+"Down"
	if type(self.fileIn) is dict:
	  if 'histo_zeros' in shapeNameUp:
	    histoUp = self.ZeroHisto(self.fileIn[sampleName].Get(shapeName),shapeName+'_Up_zeros')
	  else:
	    histoUp = self.fileIn[sampleName].Get(shapeNameUp)
	  if 'histo_zeros' in shapeNameDown:
	    histoDown = self.ZeroHisto(self.fileIn[sampleName].Get(shapeName),shapeName+'_Down_zeros')
	  else:
	    histoDown = self.fileIn[sampleName].Get(shapeNameDown)
	else :
	  if 'histo_zeros' in shapeNameUp:
	    histoUp = self.ZeroHisto(self.fileIn.Get(shapeName),shapeName+'_Up_zeros')
	  else:
	    histoUp = self.fileIn.Get(shapeNameUp)
	  if 'histo_zeros' in shapeNameDown:
	    histoDown = self.ZeroHisto(self.fileIn.Get(shapeName),shapeName+'_Down_zeros')
	  else:
	    histoDown = self.fileIn.Get(shapeNameDown)

        # No stored histogram case
	if histoUp == None:
	  if 'all' in nuisance.keys() and nuisance ['all'] == 1 : # for all samples
	    if nuisance['type'] == 'lnN' :
	      down_variation = 0.
	      up_variation = 0.

	      if "/" in nuisance['value'] :
		twovariations = nuisance['value'].split("/")
		down_variation = float(twovariations[0])
		up_variation = float(twovariations[1])
	      else:
		down_variation = 2. - float(nuisance['value'])
		up_variation = float(nuisance['value'])

	      # don't use  histos[sampleName], or the second "scale" will fail!!!
	      if 'name' in nuisance:
		histoUp = histo.Clone(cutName+"_"+variableName+'_histo_' + sampleName+"_"+nuisance['name']+"Up")
	      else :
		histoUp = histo.Clone(cutName+"_"+variableName+'_histo_' + sampleName+"_"+nuisanceName+"Up")

	      histoUp.Scale(up_variation)

	  elif 'samples' in nuisance.keys():
	    for sampleNuisName, configurationNuis in nuisance['samples'].iteritems() :
	      if sampleNuisName == sampleName: # complain only if the nuisance was supposed to show up
		if 'type' in nuisance.keys() :
		  if nuisance['type'] == 'lnN' : 
		    # example:
		    #              'samples'  : {
		    #                   'WW' : '1.00',
		    #                   'ggH': '1.23/0.97'
		    #                },
		    down_variation = 0.
		    up_variation = 0.

		    if "/" in configurationNuis :
		      twovariations = configurationNuis.split("/")
		      down_variation = float(twovariations[0])
		      up_variation = float(twovariations[1])
		    else:
		      down_variation = 2. - float(configurationNuis)
		      up_variation = float(configurationNuis)

		    # don't use  histos[sampleName], or the second "scale" will fail!!!
		    if 'name' in nuisance:
		      histoUp = histo.Clone(cutName+"_"+variableName+'_histo_' + sampleName+"_"+nuisance['name']+"Up")
		    else :
		      histoUp = histo.Clone(cutName+"_"+variableName+'_histo_' + sampleName+"_"+nuisanceName+"Up")
		    histoUp.Scale(up_variation)
        if histoDown == None:
	  if 'all' in nuisance.keys() and nuisance ['all'] == 1 : # for all samples
	    if nuisance['type'] == 'lnN' :
	      down_variation = 0.
	      up_variation = 0.

	      if "/" in nuisance['value'] :
		twovariations = nuisance['value'].split("/")
		down_variation = float(twovariations[0])
		up_variation = float(twovariations[1])
	      else:
		down_variation = 2. - float(nuisance['value'])
		up_variation = float(nuisance['value'])

	      # don't use  histos[sampleName], or the second "scale" will fail!!!
	      if 'name' in nuisance:
		histoDown = histo.Clone(cutName+"_"+variableName+'_histo_' + sampleName+"_"+nuisance['name']+"Down")
	      else:
		histoDown = histo.Clone(cutName+"_"+variableName+'_histo_' + sampleName+"_"+nuisanceName+"Down")
	      
	      histoDown.Scale(down_variation)

          elif 'samples' in nuisance.keys():
	    for sampleNuisName, configurationNuis in nuisance['samples'].iteritems() :
	      if sampleNuisName == sampleName:
		if 'type' in nuisance.keys() :
		  if nuisance['type'] == 'lnN' :
		    down_variation = 0.
		    up_variation = 0.

		    if "/" in configurationNuis :
		      twovariations = configurationNuis.split("/")
		      down_variation = float(twovariations[0])
		      up_variation = float(twovariations[1])
		    else:
		      down_variation = 2. - float(configurationNuis)
		      up_variation = float(configurationNuis)

		    # don't use  histos[sampleName], or the second "scale" will fail!!!
		    if 'name' in nuisance:
		      histoDown = histo.Clone(cutName + "_" + variableName + '_histo_' + sampleName + "_" +nuisance['name']+"Down")
		    else :
		      histoDown = histo.Clone(cutName+"_"+variableName+'_histo_' + sampleName+"_"+nuisanceName+"Down")
		    histoDown.Scale(down_variation)

      if 'scale' in plotdef_.keys() :
	if histoDown != None:
	  histoDown.Scale(plotdef_['scale'])
	if histoUp != None:
	  histoUp.Scale(plotdef_['scale'])
      # apply cut dependent scale factors
      # for example when plotting different phase spaces
      if 'cuts' in plotdef_.keys() :
	if cutName in plotdef_['cuts'] :
	  if histoDown != None:
	    histoDown.Scale( float(plotdef_['cuts'][cutName]) )
	  if histoUp   != None:
	    histoUp.Scale( float(plotdef_['cuts'][cutName]) )
      
      if variable_["divideByBinWidth"] == 1:
	if histoUp != None:
	  histoUp.Scale(1,"width")
	if histoDown != None:
	  histoDown.Scale(1,"width")

      # now, even if not considered this nuisance, I need to add it, 
      # so that in case is "empty" it will add the nominal value
      # for this sample that is not affected by the nuisance

      if nuisanceName not in nuisances_vy_up.keys() or nuisanceName not in nuisances_vy_do.keys():
	nuisances_vy_up[nuisanceName] = array('f')
	nuisances_vy_do[nuisanceName] = array('f')
      if (len(nuisances_vy_up[nuisanceName]) == 0):
	for iBin in range(1, histos[sampleName].GetNbinsX()+1):
	  nuisances_vy_up[nuisanceName].append(0.)
      if (len(nuisances_vy_do[nuisanceName]) == 0):
	for iBin in range(1, histos[sampleName].GetNbinsX()+1):
	  nuisances_vy_do[nuisanceName].append(0.)
      # get the background sum
      if plotdef_['isSignal'] == 0: # ---> add the signal too????? See ~ 20 lines below
	#print "plot[", sampleName, "]['isSignal'] == ", plotdef_['isSignal']
	for iBin in range(1, histos[sampleName].GetNbinsX()+1):
	  if histoUp != None:
	    nuisances_vy_up[nuisanceName][iBin-1] += histoUp.GetBinContent (iBin)
	  else:
	    # add the central sample
	    nuisances_vy_up[nuisanceName][iBin-1] += histos[sampleName].GetBinContent (iBin)
	  if histoDown != None:
	    nuisances_vy_do[nuisanceName][iBin-1] += histoDown.GetBinContent (iBin)
	  else:
	    # add the central sample
	    nuisances_vy_do[nuisanceName][iBin-1] += histos[sampleName].GetBinContent (iBin)


  def FillGroupHisto(self, sampleName_, plot_container_):
    #________________________________________________________________________________________
    # Data and MC
    #________________________________________________________________________________________
    # create the group of histograms to plot
    # this has to be done after the scaling of the previous lines
    # and also after all the rest, so that we inherit the style of the histograms
    histos_grouped = plot_container_.histos_grouped
    histos = plot_container_.histos
    cutName = plot_container_.cutName
    sampleName = sampleName_
    variableName = plot_container_.variableName
    for sampleNameGroup, sampleConfiguration in self._groupPlot.iteritems():
      if sampleName in sampleConfiguration['samples']:
        if sampleNameGroup in histos_grouped.keys() :
          histos_grouped[sampleNameGroup].Add(histos[sampleName])
	else:
	  histos_grouped[sampleNameGroup] = histos[sampleName].Clone('new_histo_group_' + sampleNameGroup + '_' + cutName + '_' + variableName)


  def DecorateGroupHisto(self, plot_container_):
    #_________________________________________________________________________________
    # Sample Loop Over by plot dictionary
    #_________________________________________________________________________________
    histos_grouped = plot_container_.histos_grouped

    # set the colors for the groups of samples
    for sampleNameGroup, sampleConfiguration in self._groupPlot.iteritems():
      if sampleNameGroup in histos_grouped.keys() :
        histos_grouped[sampleNameGroup].SetLineColor(sampleConfiguration['color'])
        histos_grouped[sampleNameGroup].SetFillColor(sampleConfiguration['color'])
        if sampleConfiguration['isSignal'] == 0:
	  histos_grouped[sampleNameGroup].SetFillStyle(3001)
	else:
	  histos_grouped[sampleNameGroup].SetFillStyle(0)
	  histos_grouped[sampleNameGroup].SetLineWidth(2)

	if 'style' in sampleConfiguration.keys():
	  #print 'style', sampleConfiguration['style']
	  histos_grouped[sampleNameGroup].SetFillStyle(sampleConfiguration['style'])
	if 'lineWidth' in sampleConfiguration.keys():
	  histos_grouped[sampleNameGroup].SetLineWidth(sampleConfiguration['lineWidth'])
	if 'lineColor' in sampleConfiguration.keys():
	  histos_grouped[sampleNameGroup].SetLineColor(sampleConfiguration['lineColor'])


  def SaveBkgSumErrCentral(self, plot_container_):

    thsBackground = plot_container_.thsBackground
    tgrMC_vy      = plot_container_.tgrMC_vy
    tgrMC_vx      = plot_container_.tgrMC_vx
    tgrMC_evx     = plot_container_.tgrMC_evx

    # fill the reference distribution with the background only distribution
    # save the central values of the bkg sum for use for the nuisance band
    #
    if thsBackground.GetNhists() != 0:
      for iBin in range(1,thsBackground.GetStack().Last().GetNbinsX()+1):
        tgrMC_vy.append(thsBackground.GetStack().Last().GetBinContent(iBin))
        tgrMC_vx.append(thsBackground.GetStack().Last().GetBinCenter(iBin))
        tgrMC_evx.append(thsBackground.GetStack().Last().GetBinWidth(iBin)/2.)


  def addSigToBkg(self, sampleName_, plot_container_, variable_, plotdef_):
    #NOTE##################################################################
    # and now  let's add the signal on top of the background stack
    # It is important to do this after setting (without signal) tgrMC_vy
    #######################################################################
    for sampleName_, plotdef_ in self._plot.iteritems():
      if 'samples' in variable_ and sampleName_ not in variable_['samples'] :
        continue

      # MC style
      if plotdef_['isData'] == 0 :
        if plotdef_['isSignal'] == 1 :
          plot_container_.thsBackground.Add(plot_container_.histos[sampleName_])


  def calcNuisanceErr(self, plot_container_):
    #
    # you need to add the signal as well, since the signal was considered in the nuisances vector
    # otherwise you would introduce an uncertainty as big as the signal itself!!!
    #
    mynuisances      = plot_container_.mynuisances      
    nuisances_err_up = plot_container_.nuisances_err_up
    nuisances_err_do = plot_container_.nuisances_err_do
    nuisances_vy_up  = plot_container_.nuisances_vy_up 
    nuisances_vy_do  = plot_container_.nuisances_vy_do 
    tgrData          = plot_container_.tgrData
    tgrData_vx       = plot_container_.tgrData_vx      
    tgrData_evx      = plot_container_.tgrData_evx     
    tgrData_vy       = plot_container_.tgrData_vy       
    tgrData_evy_up   = plot_container_.tgrData_evy_up   
    tgrData_evy_do   = plot_container_.tgrData_evy_do   
    
    tgrMC_vy       = plot_container_.tgrMC_vy       
    thsBackground    = plot_container_.thsBackground
    dataColor     = plot_container_.dataColor

    for nuisanceName in mynuisances.keys():
      if len(nuisances_err_up) == 0 : 
        for iBin in range(len(tgrMC_vy)):
	  nuisances_err_up.append(0.)
	  nuisances_err_do.append(0.)
      # now we need to tell whether the variation is actually up or down and sum in quadrature those with the same sign 
      for iBin in range(len(tgrMC_vy)):
        if nuisances_vy_up[nuisanceName][iBin] - tgrMC_vy[iBin] > 0:
          nuisances_err_up[iBin] = self.SumQ (nuisances_err_up[iBin], nuisances_vy_up[nuisanceName][iBin] - tgrMC_vy[iBin])
	  nuisances_err_do[iBin] = self.SumQ (nuisances_err_do[iBin], nuisances_vy_do[nuisanceName][iBin] - tgrMC_vy[iBin])
	else:
	  nuisances_err_up[iBin] = self.SumQ (nuisances_err_up[iBin], nuisances_vy_do[nuisanceName][iBin] - tgrMC_vy[iBin])
	  nuisances_err_do[iBin] = self.SumQ (nuisances_err_do[iBin], nuisances_vy_up[nuisanceName][iBin] - tgrMC_vy[iBin])
	
    if len(tgrData_vx) > 0:
      plot_container_.tgrData = ROOT.TGraphAsymmErrors(thsBackground.GetStack().Last().GetNbinsX())
      tgrData = plot_container_.tgrData
      for iBin in range(0, len(tgrData_vx)) : 
        tgrData.SetPoint (iBin, tgrData_vx[iBin], tgrData_vy[iBin])
        tgrData.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], tgrData_evy_do[iBin], tgrData_evy_up[iBin])
      tgrData.SetMarkerColor(dataColor)
      tgrData.SetLineColor(dataColor)


  def prepareHistoPF(self, plot_container_):


    ## Default: --postFit 0 --> No additional line is drawn
    ## ----------------------------------------------------

    ## --postFit 1 ---> line is prefit
    if self._postFit == 'p':
      plot_container_.tgrDataOverPF = tgrData.Clone("tgrDataOverPF") # use this for ratio with Post-Fit MC 
      plot_container_.histoPF = self.fileIn.Get(cutName+"/"+variableName+'/histo_total_prefit')
    ## --postFit 2 --> line is (S+B) postfit
    if self._postFit == 's':
      plot_container_.tgrDataOverPF = tgrData.Clone("tgrDataOverPF") # use this for ratio with Post-Fit MC
      plot_container_.histoPF = self.fileIn.Get(cutName+"/"+variableName+'/histo_total_postfit_s')
    ## --postFit 3 --> line is B-only postfit
    if self._postFit == 'b':
      plot_container_.tgrDataOverPF = tgrData.Clone("tgrDataOverPF") # use this for ratio with Post-Fit MC
      plot_container_.histoPF = self.fileIn.Get(cutName+"/"+variableName+'/histo_total_postfit_b')


  def prepareRatio(self, plot_container_, variable_):
    cutName        = plot_container_.cutName      
    variableName   = plot_container_.variableName  

    tgrData        = plot_container_.tgrData        
    tgrData_vx     = plot_container_.tgrData_vx      
    tgrData_vy     = plot_container_.tgrData_vy      
    tgrData_evx    = plot_container_.tgrData_evx       
    tgrData_evy_do = plot_container_.tgrData_evy_do   
    tgrData_evy_up = plot_container_.tgrData_evy_up  
    histoPF        = plot_container_.histoPF          
    thsBackground  = plot_container_.thsBackground   

    tgrMC_vx         = plot_container_.tgrMC_vx         
    tgrMC_vy         = plot_container_.tgrMC_vy
    tgrMC_evx        = plot_container_.tgrMC_evx        
    nuisances_err_do = plot_container_.nuisances_err_do 
    nuisances_err_up = plot_container_.nuisances_err_up 

    mynuisances    = plot_container_.mynuisances

    sigForAdditionalRatioList = plot_container_.sigForAdditionalRatioList
    sigForAdditionalDifferenceList = plot_container_.sigForAdditionalDifferenceList

    if len(tgrData_vx) > 0:
      plot_container_.tgrDataOverMC = tgrData.Clone("tgrDataOverMC")
      plot_container_.tgrDataMinusMC = tgrData.Clone("tgrDataMinusMC")
      tgrDataOverMC  = plot_container_.tgrDataOverMC 
      tgrDataMinusMC = plot_container_.tgrDataMinusMC
      for iBin in range(0, len(tgrData_vx)) :
        tgrDataOverMC.SetPoint (iBin, tgrData_vx[iBin], self.Ratio(tgrData_vy[iBin] , thsBackground.GetStack().Last().GetBinContent(iBin+1)) )
        tgrDataOverMC.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], self.Ratio(tgrData_evy_do[iBin], thsBackground.GetStack().Last().GetBinContent(iBin+1)) , self.Ratio(tgrData_evy_up[iBin], thsBackground.GetStack().Last().GetBinContent(iBin+1)) )
        if self._postFit == 'p' or self._postFit == 's' or self._postFit == 'b':
          tgrDataOverPF.SetPoint(iBin, tgrData_vx[iBin], self.Ratio(tgrData_vy[iBin] , histoPF.GetBinContent(iBin+1)) )
          tgrDataOverPF.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], self.Ratio(tgrData_evy_do[iBin], histoPF.GetBinContent(iBin+1)) , self.Ratio(tgrData_evy_up[iBin], thsBackground.GetStack().Last().GetBinContent(iBin+1)) )
          print "Pre-fit ratio: " + str(self.Ratio(tgrData_vy[iBin] , histoPF.GetBinContent(iBin+1)))
          print "Post-fit ratio: " + str(self.Ratio(tgrData_vy[iBin] , thsBackground.GetStack().Last().GetBinContent(iBin+1)))
          print iBin

      if len(tgrData_vx) > 0:
        #
        # data - MC :
        #    MC could be background only
        #    or it can include the signal.
        #    Default is background+signal (check isSignal = 1,2,3 options).
        #    You can activate the data - "background only" by 
        #    using the flag "showDataMinusBkgOnly".
        #    NB: this will change also the case of "(data - expected) / expected"
        #
        if self._showRelativeRatio :
          if self._showDataMinusBkgOnly :
            tgrDataMinusMC.SetPoint (iBin, tgrData_vx[iBin], self.Ratio( self.Difference(tgrData_vy[iBin] , tgrMC_vy[iBin]), tgrMC_vy[iBin] ) )
            tgrDataMinusMC.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], self.Ratio(tgrData_evy_do[iBin], tgrMC_vy[iBin]) , self.Ratio(tgrData_evy_up[iBin], tgrMC_vy[iBin]) )
          else:
            tgrDataMinusMC.SetPoint (iBin, tgrData_vx[iBin], self.Ratio( self.Difference(tgrData_vy[iBin] , thsBackground.GetStack().Last().GetBinContent(iBin+1)), thsBackground.GetStack().Last().GetBinContent(iBin+1)) )
            tgrDataMinusMC.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], self.Ratio(tgrData_evy_do[iBin], thsBackground.GetStack().Last().GetBinContent(iBin+1)) , self.Ratio(tgrData_evy_up[iBin], thsBackground.GetStack().Last().GetBinContent(iBin+1)) )
        else:
          if self._showDataMinusBkgOnly :
            tgrDataMinusMC.SetPoint (iBin, tgrData_vx[iBin], self.Difference(tgrData_vy[iBin] , tgrMC_vy[iBin] ) )
            tgrDataMinusMC.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], tgrData_evy_do[iBin] , tgrData_evy_up[iBin] )
          else:
            tgrDataMinusMC.SetPoint (iBin, tgrData_vx[iBin], self.Difference(tgrData_vy[iBin] , thsBackground.GetStack().Last().GetBinContent(iBin+1)) )
            tgrDataMinusMC.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], tgrData_evy_do[iBin] , tgrData_evy_up[iBin] )

    #
    # if there is an histogram called 'histo_total'
    # it means that post-fit plots are provided,
    # and we can neglect about the nuisances as "quadrature sum" here
    # and use directly the error bars (so far symmetric
    # see https://hypernews.cern.ch/HyperNews/CMS/get/higgs-combination/995.html )
    # from the histogram itself
    #

    special_shapeName = cutName+"/"+variableName+'/histo_total' 
    if type(self.fileIn) is dict:
      if 'total' in self.fileIn:
        histo_total = self.fileIn['total'].Get(special_shapeName)
      else:
        histo_total = None
    else:
      histo_total = self.fileIn.Get(special_shapeName)
      print 'special_shapeName', special_shapeName
	
    if variable_['divideByBinWidth'] == 1:
      if(histo_total) :
        histo_total.Scale(1,"width")
    if(histo_total) :
      print ' --> ', histo_total

    if len(mynuisances.keys()) != 0:
      plot_container_.tgrMC = ROOT.TGraphAsymmErrors()
      tgrMC = plot_container_.tgrMC
      for iBin in range(0, len(tgrMC_vx)) :
        tgrMC.SetPoint (iBin, tgrMC_vx[iBin], tgrMC_vy[iBin])
        if histo_total:
          tgrMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], histo_total.GetBinError(iBin+1), histo_total.GetBinError(iBin+1))
        else:
          tgrMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], nuisances_err_do[iBin], nuisances_err_up[iBin])

      plot_container_.tgrMCOverMC = tgrMC.Clone("tgrMCOverMC") 
      plot_container_.tgrMCMinusMC = tgrMC.Clone("tgrMCMinusMC")
      tgrMCOverMC = plot_container_.tgrMCOverMC
      tgrMCMinusMC = plot_container_.tgrMCMinusMC
      for iBin in range(0, len(tgrMC_vx)) :
        tgrMCOverMC.SetPoint (iBin, tgrMC_vx[iBin], 1.)
        tgrMCMinusMC.SetPoint (iBin, tgrMC_vx[iBin], 0.)
        if histo_total:
          tgrMCOverMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], self.Ratio(histo_total.GetBinError(iBin+1), tgrMC_vy[iBin]), self.Ratio(histo_total.GetBinError(iBin+1), tgrMC_vy[iBin]))
          if self._showRelativeRatio :
            tgrMCMinusMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], self.Ratio(histo_total.GetBinError(iBin+1), tgrMC_vy[iBin]), self.Ratio(histo_total.GetBinError(iBin+1), tgrMC_vy[iBin]))
          else:
            tgrMCMinusMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], histo_total.GetBinError(iBin+1), histo_total.GetBinError(iBin+1))
	else:
	  tgrMCOverMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], self.Ratio(nuisances_err_do[iBin], tgrMC_vy[iBin]), self.Ratio(nuisances_err_up[iBin], tgrMC_vy[iBin]))
	  if self._showRelativeRatio :
	    tgrMCMinusMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], self.Ratio(nuisances_err_do[iBin], tgrMC_vy[iBin]), self.Ratio(nuisances_err_up[iBin], tgrMC_vy[iBin]))
	  else:
	    tgrMCMinusMC.SetPointError(iBin, tgrMC_evx[iBin], tgrMC_evx[iBin], nuisances_err_do[iBin], nuisances_err_up[iBin])


    tgrRatioList = plot_container_.tgrRatioList
    if len(tgrData_vx) > 0:
      for samplesToRatioName, samplesToRatio in sigForAdditionalRatioList.iteritems() :
        tgrDataOverMCTemp = tgrData.Clone("tgrDataOverMC"+samplesToRatioName)
        for iBin in range(0, len(tgrData_vx)) : 
          tgrDataOverMCTemp.SetPoint (iBin, tgrData_vx[iBin], self.Ratio(tgrData_vy[iBin] , samplesToRatio.GetBinContent(iBin+1)) )
          tgrDataOverMCTemp.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], self.Ratio(tgrData_evy_do[iBin], samplesToRatio.GetBinContent(iBin+1)) , self.Ratio(tgrData_evy_up[iBin], samplesToRatio.GetBinContent(iBin+1)) )
          if variableName == 'events' :
            print ' >> ratio[', cutName, '][', samplesToRatioName, ']  = ', self.Ratio(tgrData_vy[0] , samplesToRatio.GetBinContent(0+1)) 
        tgrDataOverMCTemp.SetLineColor(samplesToRatio.GetLineColor())
        tgrDataOverMCTemp.SetMarkerColor(samplesToRatio.GetLineColor())
        tgrDataOverMCTemp.SetMarkerSize(0.3)
        tgrRatioList[samplesToRatioName] = tgrDataOverMCTemp


    tgrDifferenceList = plot_container_.tgrDifferenceList
    if len(tgrData_vx) > 0:
      for samplesToDifferenceName, samplesToDifference in sigForAdditionalDifferenceList.iteritems() :
        tgrDataMinusMCTemp = tgrData.Clone("tgrDataMinusMC"+samplesToDifferenceName)
        for iBin in range(0, len(tgrData_vx)) : 
          tgrDataMinusMCTemp.SetPoint (iBin, tgrData_vx[iBin], self.Difference(tgrData_vy[iBin] , samplesToDifference.GetBinContent(iBin+1)) )
          tgrDataMinusMCTemp.SetPointError(iBin, tgrData_evx[iBin], tgrData_evx[iBin], tgrData_evy_do[iBin] , tgrData_evy_up[iBin] )
          if variableName == 'events' :
            print ' >> difference[', cutName, '][', samplesToDifferenceName, ']  = ', self.Difference(tgrData_vy[0] , samplesToDifference.GetBinContent(0+1)) 

        tgrDataMinusMCTemp.SetLineColor(samplesToDifference.GetLineColor())
        tgrDataMinusMCTemp.SetMarkerColor(samplesToDifference.GetLineColor())
        tgrDataMinusMCTemp.SetMarkerSize(0.3)
        tgrDifferenceList[samplesToDifferenceName] = tgrDataMinusMCTemp


  def prepareGroupedHistos(self, plot_container_, variable_):
    thsSignal_grouped     = plot_container_.thsSignal_grouped      
    histos_grouped        = plot_container_.histos_grouped         
    sigSupList_grouped    = plot_container_.sigSupList_grouped      
    thsBackground_grouped = plot_container_.thsBackground_grouped  
    groupFlag = False
    #---- prepare the grouped histograms
    for sampleNameGroup, sampleConfiguration in self._groupPlot.iteritems():
      if 'samples' in variable_ and len(set(sampleConfiguration['samples']) & set(variable_['samples'])) == 0:
        continue

      if sampleConfiguration['isSignal'] == 1 :
        print "############################################################## isSignal 1", sampleNameGroup
        thsSignal_grouped.Add(histos_grouped[sampleNameGroup])
      elif sampleConfiguration['isSignal'] == 2 :
        print "############################################################## isSignal 2", sampleNameGroup
        groupFlag = True
        sigSupList_grouped.append(histos_grouped[sampleNameGroup])
      # the signal is added on top of the background
      # the signal has to be the last one in the dictionary!
      # make it sure in plot.py
      if groupFlag == False:
        thsBackground_grouped.Add(histos_grouped[sampleNameGroup])
      groupFlag = False


  def setCanvasFrame(self, plot_container_, variable_):

    thsBackground = plot_container_.thsBackground
    thsData       = plot_container_.thsData      
    histos        = plot_container_.histos       
    thsSignal     = plot_container_.thsSignal    
    
    #---- now plot

    if thsBackground.GetNhists() != 0:
      print " MC   = ", thsBackground.GetStack().Last().Integral()
      for ihisto in range(thsBackground.GetNhists()) :
        print "     - ",ihisto, " - ", ((thsBackground.GetHists().At(ihisto))).GetName(), " = ", ((thsBackground.GetHists().At(ihisto))).Integral()
	
    if thsData.GetNhists() != 0:
      print " DATA = ", thsData.GetStack().Last().Integral()


    #  - get axis range
    minXused = 0.
    maxXused = 1.

    minYused = 1.
    maxYused = 1.
    for sampleName, plotdef in self._plot.iteritems():
      if 'samples' in variable_ and sampleName not in variable_['samples']:
        continue

      if plotdef['isData'] == 1 :
        histos[sampleName].Draw("p")
        minXused = histos[sampleName].GetXaxis().GetBinLowEdge(1)
        maxXused = histos[sampleName].GetXaxis().GetBinUpEdge(histos[sampleName].GetNbinsX())
        maxY = self.GetMaximumIncludingErrors(histos[sampleName])
        histos[sampleName].SetMaximum(self._scaleToPlot * maxY)
        maxYused = self._scaleToPlot * maxY
        minYused = self.GetMinimum(histos[sampleName])

    if thsBackground.GetNhists() != 0:
      thsBackground.Draw("hist")
      maxY = thsBackground.GetMaximum ()
      minXused = thsBackground.GetXaxis().GetBinLowEdge(1)
      maxXused = thsBackground.GetXaxis().GetBinUpEdge(thsBackground.GetHistogram().GetNbinsX())
      if (self._scaleToPlot * maxY) > maxYused :
        maxYused = self._scaleToPlot * maxY
      minY = thsBackground.GetMinimum ()
      if (minY < minYused) :
        minYused = minY


    if thsSignal.GetNhists() != 0:
      thsSignal.Draw("hist")
      maxY = thsSignal.GetMaximum ()
      minXused = thsSignal.GetXaxis().GetBinLowEdge(1)
      maxXused = thsSignal.GetXaxis().GetBinUpEdge(thsSignal.GetHistogram().GetNbinsX())
      if (self._scaleToPlot * maxY) > maxYused :
        maxYused = self._scaleToPlot * maxY
      minY = thsSignal.GetMinimum ()
      if (minY < minYused) :
        minYused = minY
	
    plot_container_.minXused = minXused
    plot_container_.maxXused = maxXused
                                      
    plot_container_.minYused = minYused
    plot_container_.maxYused = maxYused

    #print " X axis = ", minXused, " - ", maxXused
    plot_container_.frame = ROOT.TH1F
    plot_container_.frame = plot_container_.tcanvas.DrawFrame(minXused, minYused, maxXused, maxYused) # previous arguments(minXused, 0, maxXused, 1), why set ymin ymax as 0 1?
    frame = plot_container_.frame
    # style from https://ghm.web.cern.ch/ghm/plots/MacroExample/myMacro.py
    xAxis = frame.GetXaxis()
    xAxis.SetNdivisions(6,5,0)

    # setup axis names
    if 'xaxis' in variable_.keys() :
      frame.GetXaxis().SetTitle(variable_['xaxis'])
      if variable_["divideByBinWidth"] == 1:
        if "GeV" in variable_['xaxis']: 
          frame.GetYaxis().SetTitle("dN/d"+variable_['xaxis'].replace("GeV","GeV^{-1}"))
        else:
          frame.GetYaxis().SetTitle("dN/d"+variable_['xaxis'])
      else:
        if 'yaxis' in variable_.keys() : 
          frame.GetYaxis().SetTitle(variable_['yaxis'])
        else:
          frame.GetYaxis().SetTitle("Events")
    else:
      if variable_["divideByBinWidth"] == 1:
        frame.GetYaxis().SetTitle("dN/d"+variableName)
      else:
        if 'yaxis' in variable_.keys() :
	  frame.GetYaxis().SetTitle(variable_['yaxis'])
	else:
	  frame.GetYaxis().SetTitle("Events")
    # setup xbin labels
    if 'xlabels' in variable_.keys() :
      for i, label in enumerate(variable_['xlabels']['labels']):
        frame.GetXaxis().ChangeLabel(i+1,20,0.03,-1,-1,-1 ,label)
      frame.GetXaxis().LabelsOption(variable_['xlabels']['option'])
      frame.GetXaxis().CenterLabels(True)
      xAxis.SetNdivisions(len(variable_['xlabels']['labels']),5,0)




  def draw(self, plot_container_, variable_):

    cutName               = plot_container_.cutName      
    variableName          = plot_container_.variableName

    thsBackground         = plot_container_.thsBackground         
    thsSignal             = plot_container_.thsSignal            
    thsBackground_grouped = plot_container_.thsBackground_grouped
    thsSignal_grouped     = plot_container_.thsSignal_grouped    
    sigSupList_grouped    = plot_container_.sigSupList_grouped   
    histos                = plot_container_.histos               
    tgrMC                 = plot_container_.tgrMC                 
    tgrData               = plot_container_.tgrData              
    tgrData_vx            = plot_container_.tgrData_vx           
    mynuisances           = plot_container_.mynuisances           

    sigSupList            = plot_container_.sigSupList
    histos_grouped        = plot_container_.histos_grouped         

    tgrMCOverMC           = plot_container_.tgrMCOverMC           
    tgrDataOverMC         = plot_container_.tgrDataOverMC  
    tgrDataOverPF         = plot_container_.tgrDataOverPF  
    tgrRatioList          = plot_container_.tgrRatioList    

    #
    # - now Draw
    #     - first the MC  
    #         before the background+signal, and then only the signal alone
    #
    if len(self._groupPlot.keys()) == 0:
      if thsBackground.GetNhists() != 0:
        thsBackground.Draw("hist same")

      if thsSignal.GetNhists() != 0:
        thsSignal.Draw("hist same noclear") # By default the background of the histograms is erased before drawing the histograms. The option "noclear" avoid this behaviour
    else :
      if thsBackground_grouped.GetNhists() != 0:
        thsBackground_grouped.Draw("hist same")

      if thsSignal_grouped.GetNhists() != 0:
        thsSignal_grouped.Draw("hist same noclear")

      if len(sigSupList_grouped) != 0:
        for histo in sigSupList_grouped:
          histo.Draw("hist same")

    # if there is a systematic band draw it
    if len(mynuisances.keys()) != 0:
      tgrMC.SetLineColor(12)
      tgrMC.SetFillColor(12)
      tgrMC.SetLineWidth(2)
      tgrMC.SetFillStyle(3004)
      tgrMCOverMC.SetLineColor(12)
      tgrMCOverMC.SetFillColor(12)
      tgrMCOverMC.SetLineWidth(2)
      tgrMCOverMC.SetFillStyle(3004)
      tgrMC.Draw("2")

    #     - then the superimposed MC
    if len(sigSupList) != 0 and groupFlag==False:
      for hist in sigSupList:
        hist.Draw("hist same")
	
    #     - then the DATA 
    if len(tgrData_vx) > 0:
    #if tgrData.GetN() != 0:
      tgrData.Draw("P0")
    else: # never happening if at least one data histogram is provided  -> modified for mc only case
      for sampleName, plotdef in self._plot.iteritems():
        if 'samples' in variable_ and sampleName not in variable_['samples']:
          continue
        if plotdef['isData'] == 1 :
          histos[sampleName].Draw("p same")

    #---- the Legend
    tlegend = ROOT.TLegend(0.20, 0.70, 0.80, 0.88)
    tlegend.SetFillColor(0)
    tlegend.SetTextFont(42)
    tlegend.SetTextSize(0.035)
    tlegend.SetLineColor(0)
    tlegend.SetShadowColor(0)
    reversedSampleNames = list(self._samples)
    reversedSampleNames.reverse()

    legMarkStyle = "F"
    #ROOT.TString legMarkStyle = "F"
    if len(self._groupPlot.keys()) == 0:
      for sampleName in reversedSampleNames:
        try:
          plotdef = plot[sampleName]
        except KeyError:
          continue

        if plotdef['isData'] == 0 :
          legMarkStyle = "F"
        elif plotdef['isData'] == 1:
          legMarkStyle = "EPL"
        else :
          print 'Specify isData at plot.py !!!!!!!!!!!!!!!!!!!!!!!!'
          continue


        if 'nameHR' in plotdef.keys() :
	  if plotdef['nameHR'] != '' :
	    if self._showIntegralLegend == 0 :
	      tlegend.AddEntry(histos[sampleName], plotdef['nameHR'], legMarkStyle)
	    else :
	      if variable_["divideByBinWidth"] == 1:
	        nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1,"width")
	      else :
	        nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1)
	      tlegend.AddEntry(histos[sampleName], plotdef['nameHR'] + " [" + str(round(nevents,1)) + "]", legMarkStyle)
	  else:
	    if self._showIntegralLegend == 0 :
	      tlegend.AddEntry(histos[sampleName], sampleName, legMarkStyle)
	    else :
	      if variable_["divideByBinWidth"] == 1:
	        nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1,"width")
	      else :
	        nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1)
	      tlegend.AddEntry(histos[sampleName], sampleName + " [" + str(round(nevents,1)) + "]", legMarkStyle)
	else :
	  if self._showIntegralLegend == 0 :
	    tlegend.AddEntry(histos[sampleName], sampleName, legMarkStyle)
	  else :
	    if variable_["divideByBinWidth"] == 1:
	      nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1,"width")
	    else :
	      nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1)
	    tlegend.AddEntry(histos[sampleName], sampleName + " [" + str(round(nevents,1)) + "]", legMarkStyle)

    else : #If there are groupPlots
      for sampleNameGroup, sampleConfiguration in self._groupPlot.iteritems():
        if 'samples' in variable_ and len(set(sampleConfiguration['samples']) & set(variable_['samples'])) == 0:
          continue

        if self._showIntegralLegend == 0 :
          tlegend.AddEntry(histos_grouped[sampleNameGroup], sampleConfiguration['nameHR'], "F")
        else :
          if variable_["divideByBinWidth"] == 1:
            nevents = histos_grouped[sampleNameGroup].Integral(1,histos_grouped[sampleNameGroup].GetNbinsX()+1,"width")
	  else :
	    nevents = histos_grouped[sampleNameGroup].Integral(1,histos_grouped[sampleNameGroup].GetNbinsX()+1)
	  tlegend.AddEntry(histos_grouped[sampleNameGroup], sampleConfiguration['nameHR'] + " [" + str(round(nevents,1)) + "]" , "F")
      for sampleName in reversedSampleNames:
        if 'samples' in variable_ and sampleName not in variable_['samples']:
	  continue

	try :
	  plotdef = self._plot[sampleName]
	except KeyError:
	  continue

	if plotdef['isData'] == 1 :
	  if 'nameHR' in plotdef.keys() :
	    if self._showIntegralLegend == 0 :
	      tlegend.AddEntry(histos[sampleName], plotdef['nameHR'], "EPL")
	    else:
	      if variable_["divideByBinWidth"] == 1:
                nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1,"width")
	      else :
	        nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1)
	      print " nevents [", sampleName, "] = ", nevents
	      tlegend.AddEntry(histos[sampleName], plotdef['nameHR'] + " [" + str(round(nevents,1)) + "]", "EPL")
	  else :
	    if self._showIntegralLegend == 0 :
	      tlegend.AddEntry(histos[sampleName], sampleName , "EPL")
	    else :
	      if variable["divideByBinWidth"] == 1:
	        nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1,"width")
	      else:
	        nevents = histos[sampleName].Integral(1,histos[sampleName].GetNbinsX()+1)
	      print " nevents [", sampleName, "] = ", nevents
	      tlegend.AddEntry(histos[sampleName], sampleName + " [" + str(round(nevents,1)) + "]", "EPL")

    if len(mynuisances.keys()) != 0:
      if self._showIntegralLegend == 0 :
        tlegend.AddEntry(tgrMC, "All MC", "F")
      else :
        print " nexpected  = ", plot_container_.nexpected
        tlegend.AddEntry(tgrMC, "All MC [" + str(round(plot_container_.nexpected,1)) + "]", "F")

    tlegend.SetNColumns(2)
    tlegend.Draw()

    #change the CMS_lumi variables (see CMS_lumi.py)
    import ShapeAnalysis.python.CMS_lumi as CMS_lumi
    CMS_lumi.lumi_7TeV = "4.8 fb^{-1}"
    CMS_lumi.lumi_8TeV = "18.3 fb^{-1}"
    CMS_lumi.lumi_13TeV = "100 fb^{-1}"
    CMS_lumi.writeExtraText = 1
    #CMS_lumi.extraText = "Preliminary"
    CMS_lumi.extraText = "work in progress"
    CMS_lumi.relPosX = 0.12
    CMS_lumi.lumi_sqrtS = "13 TeV"
    if 'sqrt' in self._legend.keys() :
      CMS_lumi.lumi_sqrtS = self._legend['sqrt']
    if 'lumi' in self._legend.keys() :
      CMS_lumi.lumi_13TeV = self._legend['lumi']
    if 'iPeriod' in self._legend.keys() :
      iPeriod = self._legend['iPeriod']
    else :
      iPeriod = 0
    if 'iPos' in self._legend.keys() :
      iPos = self._legend['iPos']
    else :
      iPos = 0

    tcanvas      = plot_container_.tcanvas
    tcanvasRatio = plot_container_.tcanvasRatio
    CMS_lumi.CMS_lumi(tcanvas, iPeriod, iPos)

    print "- draw tlegend"
    tlegend.Draw()
    frame = plot_container_.frame
    minXused = plot_container_.minXused
    maxXused = plot_container_.maxXused
    minYused = plot_container_.minYused
    maxYused = plot_container_.maxYused
    #frame.GetYaxis().SetRangeUser( 0, maxYused ) # why set ymin as zero here?
    # draw back all the axes
    tcanvas.RedrawAxis()

    tcanvas.SaveAs(self._outputDirPlots + "/" + plot_container_.canvasNameTemplate + self._FigNamePF + ".png")
    tcanvas.SaveAs(self._outputDirPlots + "/" + plot_container_.canvasNameTemplate + self._FigNamePF + ".root")

    # log Y axis
    frame.GetYaxis().SetRangeUser( self._minLogC, self._maxLogC * maxYused )
    #frame.GetYaxis().SetRangeUser( max(self._minLogC, minYused), self._maxLogC * maxYused )
    tcanvas.SetLogy()
    tcanvas.SaveAs(self._outputDirPlots + "/log_" + plot_container_.canvasNameTemplate + self._FigNamePF + ".png")
    tcanvas.SetLogy(0)

    if self._plotNormalizedDistributions :
      # plot signal vs background normalized
      plot_container_.tcanvasSigVsBkg.cd()

      frameNorm = ROOT.TH1F
      frameNorm = plot_container_.tcanvasSigVsBkg.DrawFrame(minXused, 0.0, maxXused, 1.0)

      frameNorm.GetYaxis().SetRangeUser( 0, 1.5 )
      # setup axis names
      if 'xaxis' in variable_.keys() : 
        frameNorm.GetXaxis().SetTitle(variable_['xaxis'])
      # setup xbin labels
      if 'xlabels' in variable_.keys() :
        for i, label in enumerate(variable_['xlabels']['labels']):
          frameNorm.GetXaxis().ChangeLabel(i+1,20,0.03,-1,-1,-1 ,label)
        frameNorm.GetXaxis().LabelsOption(variable_['xlabels']['option'])
        frameNorm.GetXaxis().CenterLabels(True)
      plot_container_.tcanvasSigVsBkg.RedrawAxis()
   
      maxY_normalized=0.0

      for ihisto in range(thsBackground_grouped.GetNhists()) :
        num_bins = (thsBackground_grouped.GetHists().At(ihisto)).GetNbinsX()
	if (thsBackground_grouped.GetHists().At(ihisto)).Integral() > 0:
	  if (thsBackground_grouped.GetHists().At(ihisto)).GetBinContent((thsBackground_grouped.GetHists().At(ihisto)).GetMaximumBin())/(thsBackground_grouped.GetHists().At(ihisto)).Integral() > maxY_normalized:
	    maxY_normalized =(thsBackground_grouped.GetHists().At(ihisto)).GetBinContent((thsBackground_grouped.GetHists().At(ihisto)).GetMaximumBin())/(thsBackground_grouped.GetHists().At(ihisto)).Integral()

	for ibin in range( num_bins ) :
	  (thsBackground_grouped.GetHists().At(ihisto)).SetBinError(ibin+1, 0.000001)
	(thsBackground_grouped.GetHists().At(ihisto)).SetFillStyle(0)
	(thsBackground_grouped.GetHists().At(ihisto)).SetLineWidth(3)
	(thsBackground_grouped.GetHists().At(ihisto)).DrawNormalized("hist,same")

      for ihisto in range(thsSignal_grouped.GetNhists()) :
	num_bins = (thsSignal_grouped.GetHists().At(ihisto)).GetNbinsX()
	if (thsSignal_grouped.GetHists().At(ihisto)).Integral() > 0:
	  if (thsSignal_grouped.GetHists().At(ihisto)).GetBinContent((thsSignal_grouped.GetHists().At(ihisto)).GetMaximumBin())/(thsSignal_grouped.GetHists().At(ihisto)).Integral() > maxY_normalized:
	    maxY_normalized = (thsSignal_grouped.GetHists().At(ihisto)).GetBinContent((thsSignal_grouped.GetHists().At(ihisto)).GetMaximumBin())/(thsSignal_grouped.GetHists().At(ihisto)).Integral()

	for ibin in range( num_bins ) :
	  (thsSignal_grouped.GetHists().At(ihisto)).SetBinError(ibin+1, 0.000001)
	(thsSignal_grouped.GetHists().At(ihisto)).SetFillStyle(0)
	(thsSignal_grouped.GetHists().At(ihisto)).SetLineWidth(3)
	(thsSignal_grouped.GetHists().At(ihisto)).DrawNormalized("hist,same")

      frameNorm.GetYaxis().SetRangeUser(0, 1.8*maxY_normalized)

      tlegend.Draw()
      plot_container_.tcanvasSigVsBkg.SaveAs(self._outputDirPlots + "/" + 'SigVsBkg_' + cutName + "_" + variableName + self._FigNamePF + ".png")

    # ~~~~~~~~~~~~~~~~~~~~
    # plot with ratio plot
    print "- draw with ratio"

    canvasRatioNameTemplate = 'ratio_' + cutName + "_" + variableName

    tcanvasRatio.cd()
    canvasPad1Name = 'pad1_' + cutName + "_" + variableName
    pad1 = ROOT.TPad(canvasPad1Name,canvasPad1Name, 0, 1-0.72, 1, 1)
    pad1.SetTopMargin(0.098)
    pad1.SetBottomMargin(0.000) 
    pad1.Draw()

    pad1.cd()
    canvasFrameDistroName = 'frame_distro_' + cutName + "_" + variableName
    frameDistro = pad1.DrawFrame(minXused, 0.0, maxXused, 1.0, canvasFrameDistroName)

    xAxisDistro = frameDistro.GetXaxis()
    xAxisDistro.SetNdivisions(6,5,0)

    if 'xaxis' in variable_.keys() :
      frameDistro.GetXaxis().SetTitle(variable_['xaxis'])
      if variable_["divideByBinWidth"] == 1:
        if "GeV" in variable_['xaxis']:
          frameDistro.GetYaxis().SetTitle("dN/d"+variable_['xaxis'].replace("GeV","GeV^{-1}"))
        else:
	  frameDistro.GetYaxis().SetTitle("dN/d"+variable_['xaxis'])
      else :
	if 'yaxis' in variable_.keys() : 
	  frameDistro.GetYaxis().SetTitle(variable_['yaxis'])
	else :
	  frameDistro.GetYaxis().SetTitle("Events")
    else :
      frameDistro.GetXaxis().SetTitle(variableName)
      if variable_["divideByBinWidth"] == 1:
	frameDistro.GetYaxis().SetTitle("dN/d"+variableName)
      else :
	if 'yaxis' in variable_.keys() : 
	  frameDistro.GetYaxis().SetTitle(variable_['yaxis'])
	else :
	  frameDistro.GetYaxis().SetTitle("Events")

    if 'xlabels' in variable_.keys() :
      for i, label in enumerate(variable_['xlabels']['labels']):
	frameDistro.GetXaxis().ChangeLabel(i+1,20,0.03,-1,-1,-1 ,label)
      frameDistro.GetXaxis().LabelsOption(variable_['xlabels']['option'])
      frameDistro.GetXaxis().CenterLabels(True)
      xAxisDistro.SetNdivisions(len(variable_['xlabels']['labels']),5,0)

    frameDistro.GetYaxis().SetRangeUser( min(0.001, minYused), maxYused )

    if len(self._groupPlot.keys()) == 0:
      if thsBackground.GetNhists() != 0:
        thsBackground.Draw("hist same")

      if thsSignal.GetNhists() != 0:
        thsSignal.Draw("hist same noclear")
    else :
      if thsBackground_grouped.GetNhists() != 0:
	thsBackground_grouped.Draw("hist same")

      if thsSignal_grouped.GetNhists() != 0:
        thsSignal_grouped.Draw("hist same noclear")

      if len(sigSupList_grouped) != 0:
        for histo in sigSupList_grouped:
          histo.Draw("hist same")

    if (len(mynuisances.keys())!=0):
      tgrMC.Draw("2")

    #     - then the superimposed MC
    if len(sigSupList) != 0 and groupFlag==False:
      for hist in sigSupList:
        hist.Draw("hist same")

    #     - then the DATA  
    if len(tgrData_vx) > 0:
    #if tgrData.GetN() != 0:
      tgrData.Draw("P0")

    tlegend.Draw()

    CMS_lumi.CMS_lumi(tcanvasRatio, iPeriod, iPos)

    # draw back all the axes
    pad1.RedrawAxis()

    tcanvasRatio.cd()
    canvasPad2Name = 'pad2_' + cutName + "_" + variableName
    pad2 = ROOT.TPad(canvasPad2Name,canvasPad2Name,0,0,1,1-0.72)
    pad2.SetTopMargin(0.000)
    pad2.SetBottomMargin(0.392)
    pad2.Draw()
    #pad2.cd().SetGrid()
    pad2.cd()

    canvasFrameRatioName = 'frame_ratio_' + cutName + "_" + variableName
    frameRatio = pad2.DrawFrame(minXused, 0.0, maxXused, 2.0, canvasFrameRatioName)
    xAxisDistro = frameRatio.GetXaxis()
    xAxisDistro.SetNdivisions(6,5,0)

    if 'xaxis' in variable_.keys() : 
      frameRatio.GetXaxis().SetTitle(variable_['xaxis'])
    else :
      frameRatio.GetXaxis().SetTitle(variableName)

    frameRatio.GetYaxis().SetTitle("Data/Expected")
    frameRatio.GetYaxis().SetRangeUser( 0.5, 1.5 )
    self.Pad2TAxis(frameRatio)

    if 'xlabels' in variable_.keys() :
      for i, label in enumerate(variable_['xlabels']['labels']):
        frameRatio.GetXaxis().ChangeLabel(i+1,20,0.06,-1,-1,-1 ,label)
        frameRatio.GetXaxis().SetNdivisions(len(variable_['xlabels']['labels']),5,0)
      frameRatio.GetXaxis().LabelsOption(variable_['xlabels']['option'])
      frameRatio.GetXaxis().CenterLabels(True)

    if (len(mynuisances.keys())!=0):
      tgrMCOverMC.Draw("2") 

    if len(tgrData_vx) > 0:
    #if tgrData.GetN() != 0:
      tgrDataOverMC.Draw("P0")

    if self._postFit == 'p' or self._postFit == 's' or self._postFit == 'b':
      #---- Ratio Legend
      tlegendRatio = ROOT.TLegend(0.20, 0.40, 0.60, 0.55)
      tlegendRatio.SetFillColor(0)
      tlegendRatio.SetTextFont(42)
      tlegendRatio.SetLineColor(0)
      tlegendRatio.SetShadowColor(0)

      if self._postFit == 'p':
        tlegendRatio.AddEntry(tgrDataOverMC, "post-fit", "PL")
        tlegendRatio.AddEntry(tgrDataOverPF, "pre-fit", "PL")
      if self._postFit == 's' or self._postFit == 'b':
        tlegendRatio.AddEntry(tgrDataOverMC, "pre-fit", "PL")
        tlegendRatio.AddEntry(tgrDataOverPF, "post-fit", "PL")

      for sampleName, sample in self._samples.iteritems():
        if 'total' in sampleName:
          tgrDataOverPF.SetMarkerColor(self._plot[sampleName]['color'])
          tgrDataOverPF.SetLineColor(self._plot[sampleName]['color'])
      tgrDataOverPF.Draw("PE,same")
      tlegendRatio.Draw("same")

    for samplesToRatioGrName, samplesGrToRatio in tgrRatioList.iteritems() :
      samplesGrToRatio.Draw("P")

    oneLine2 = ROOT.TLine(frameRatio.GetXaxis().GetXmin(), 1, frameRatio.GetXaxis().GetXmax(), 1);
    oneLine2.SetLineStyle(3)
    oneLine2.SetLineWidth(3)
    oneLine2.Draw("same")

    # draw back all the axes
    pad2.RedrawAxis()
    pad2.SetGrid()

    tcanvasRatio.SaveAs(self._outputDirPlots + "/" + canvasRatioNameTemplate + self._FigNamePF + ".png")
    tcanvasRatio.SaveAs(self._outputDirPlots + "/" + canvasRatioNameTemplate + self._FigNamePF + ".root")

    # log Y axis
    frameDistro.GetYaxis().SetRangeUser( min(self._minLogCratio, maxYused/1000), self._maxLogCratio * maxYused )
    pad1.SetLogy()
    tcanvasRatio.SaveAs(self._outputDirPlots + "/log_" + canvasRatioNameTemplate + self._FigNamePF + ".png")
    pad1.SetLogy(0)


  # _______________________________________________
  # --- squared sum
  def Pad2TAxis(self, hist):
    xaxis = hist.GetXaxis()
    xaxis.SetLabelFont ( 42)
    xaxis.SetLabelOffset( 0.025)
    xaxis.SetLabelSize ( 0.1)
    xaxis.SetNdivisions ( 505)
    xaxis.SetTitleFont ( 42)
    xaxis.SetTitleOffset( 1.35)
    xaxis.SetTitleSize ( 0.11)

    yaxis = hist.GetYaxis()
    yaxis.CenterTitle ( )
    yaxis.SetLabelFont ( 42)
    yaxis.SetLabelOffset( 0.02)
    yaxis.SetLabelSize ( 0.1)
    yaxis.SetNdivisions ( 505)
    yaxis.SetTitleFont ( 42)
    yaxis.SetTitleOffset( .6)
    yaxis.SetTitleSize ( 0.11)



  # _________________________________________________
  def defineStyle(self):

    import ShapeAnalysis.python.tdrStyle as tdrStyle
    tdrStyle.setTDRStyle()

    ROOT.TGaxis.SetExponentOffset(-0.08, 0.00,"y")

  # ____ poissonian error bayesian 1sigma band ___
  def GetPoissError(self, numberEvents, down, up):
    alpha = (1-0.6827)
    L = 0
    if numberEvents != 0:
      L = ROOT.Math.gamma_quantile (alpha/2, numberEvents, 1.)
    U = 0
    if numberEvents == 0:
      #
      # Poisson error agreed in the CMS statistics committee
      # see: https://hypernews.cern.ch/HyperNews/CMS/get/statistics/263.html
      # and https://hypernews.cern.ch/HyperNews/CMS/get/HIG-16-042/32/1/1/1/1/1.html
      # and https://twiki.cern.ch/twiki/bin/viewauth/CMS/PoissonErrorBars
      # to avoid flip-flop.
      # The commented version would have created 1.147 for 0 observed events
      # while now we get 1.84 in the case of 0 observed events
      #
      U = ROOT.Math.gamma_quantile_c (alpha/2, numberEvents+1, 1.)
    else:
      U = ROOT.Math.gamma_quantile_c (alpha/2, numberEvents+1, 1.)

    # the error
    L = numberEvents -L
    if numberEvents > 0:
      U = U - numberEvents
    #else:
      #U = 1.14 # --> bayesian interval Poisson with 0 events observed
      #1.14790758039 from 10 lines above

    if up and not down:
      return U
    if down and not up :
      return L
    if up and down:
      return (L,U)

  def GetMaximumIncludingErrors(self, histo):
    maxWithErrors = 0.
    for iBin in range(1, histo.GetNbinsX()+1):
      binHeight = histo.GetBinContent (iBin) + histo.GetBinError (iBin)
      if binHeight > maxWithErrors :
	maxWithErrors = binHeight

    return maxWithErrors;

  #________________________________________
  def GetMinimum(self, histo):
    minimum = -1.
    for iBin in range(1, histo.GetNbinsX()+1):
      binHeight = histo.GetBinContent (iBin)
      if binHeight < minimum or minimum<0:
	minimum = binHeight
      
    return minimum;

  def SumQ(self, A, B):
    return math.sqrt(A*A + B*B)

  # --- Ratio: if denominator is zero, then put 0!
  def Ratio(self, A, B):
    if B == 0:
      return 0.
    else:
      return A / B

  def Difference(self, A, B):
    return A - B

  def ZeroHisto(self,histo, name):
    out_histo = histo.Clone(name)
    for i in range(out_histo.GetNbinsX()):
      out_histo.SetBinContent(i,0)
      out_histo.SetBinError(i,0)
    return out_histo



    


