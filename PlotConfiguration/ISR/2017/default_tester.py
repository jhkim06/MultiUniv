from ShapeAnalysis.python.ShapeFactory import ShapeFactory

factory = ShapeFactory()
factory._treeName = "tree"
factory.makeNominals( 
		'DYJets', 
		{'skim': '', 'weight': 'weightGen*weightRec'}, 
		['/data8/DATA/SMP/Run2Legacy_v1/2016//MuMuOrElEl_v0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/190104_194922/0000/SKFlatNtuple_2016_MC_807.root'], 
		'/home/jhkim/MultiUniv/PlotConfiguration/TUnfold/2016/Output_MuMuOrElEl_v0_DY/DYJets/DYJets_tmp_0.root ', 
		{'sub-leading pt': {'fold': 3, 'range': (40, 0, 200), 'name': 'ptRec[1]', 'xaxis': 'p_{T} [GeV]', 'yaxis': 'Events / 5GeV'}, 
                 'leading pt': {'fold': 3, 'range': (40, 0, 200), 'name': 'ptRec[0]', 'xaxis': 'p_{T} [GeV]', 'yaxis': 'Events / 5GeV'}, 
                 'mll': {'fold': 3, 'range': (120, 50, 120), 'name': 'mRec[2]', 'xaxis': 'm_{ll} [GeV]'}, 
                 'ptll-mll': {'fold': 3, 'range': ([0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 18.0, 22.0, 28.0, 35.0, 45.0, 55.0, 65.0, 75.0, 85.0, 100.0], [50.0, 65.0, 80.0, 100.0, 200.0, 350.0]), 'name': 'mRec[2]:ptRec[2]', 'xaxis': ' Mass p_{T} [GeV]', 'yaxis': 'Events'}}, 
		[], 
		{}, 
		{'eventSel': 'ispassRec == 1 && IsElEl == 1'}, 
		'1==1', 
		{'trigg': {'kind': 'weight', 'type': 'shape', 'name': 'trg_2016', 'samples': {'ZZ_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WJets_MG': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'TT_powheg': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'DYJets': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WZ_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WW_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF']}}}) 

