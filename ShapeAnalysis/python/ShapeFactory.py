
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


    



