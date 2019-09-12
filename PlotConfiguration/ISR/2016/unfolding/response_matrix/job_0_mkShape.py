from ShapeAnalysis.python.ShapeFactory import ShapeFactory

factory = ShapeFactory()
factory._treeName = 'tree'
factory.makeNominals( 
		'DYJets', 
		{'skim': '', 'weight': 'weightGen*weightRec'}, 
		['/data8/DATA/SMP/Run2Legacy_v1/2016//MuMuOrElEl_v0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/190104_194922/0000/SKFlatNtuple_2016_MC_807.root'], 
		'/home/jhkim/MultiUniv/PlotConfiguration/TUnfold/2016/Output_MuMuOrElEl_v0_DY/DYJets/DYJets_tmp_0.root ', 
		{'ptll TUnfold matrix': {'fold': 0, 'range': None, 'name': 'Get2DPtRecBinIndex(ptRec[2],mRec[2]):Get2DPtGenBinIndex(ptPreFSR[2],mPreFSR[2])', 'unfoldBinType': 2, 'isResMatrix': True, 'useTUnfoldBin': True, 'go1D': False, 'xaxis': 'Pre FSR'}, 
                 'mll TUnfold matrix':  {'fold': 0, 'range': None, 'name': 'Get1DMassRecBinIndex(mRec[2]):Get1DMassGenBinIndex(mPreFSR[2])', 'unfoldBinType': 5, 'isResMatrix': True, 'useTUnfoldBin': True, 'go1D': False, 'xaxis': 'Pre FSR'}, 
                 'ptll-mll TUnfold':    {'fold': 0, 'range': None, 'go1D': True, 'name': 'Get2DPtRecBinIndex(ptRec[2], mRec[2])', 'unfoldBinType': 0, 'yaxis': 'Events', 'useTUnfoldBin': True, 'linesToAdd': ('.L /home/jhkim/MultiUniv/ShapeAnalysis/scripts/userfunc/TUnfold_Bin_Definition.C',), 'xaxis': 'Mass p_{T} [GeV]'}}, 
		[], 
		{}, 
		{'eventSel': 'isdielectron == 1 && IsElEl == 1 && ispassRec == 1 && isBveto == 1 && ptRec[0] > 25. && ptRec[1] > 15. && ptRec[2] < 100. '}, 
		'1==1', 
		{'trigg': {'kind': 'weight', 'type': 'shape', 'name': 'trg_2016', 'samples': {'ZZ_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WJets_MG': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'TT_powheg': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'DYJets': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WZ_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WW_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF']}}
                }, 
		True) 

