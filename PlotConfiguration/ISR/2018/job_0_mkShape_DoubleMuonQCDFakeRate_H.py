from ShapeAnalysis.python.ShapeFactory import ShapeFactory

factory = ShapeFactory()
factory._treeName = 'recoTree/SKFlat'
factory.makeNominals( 
		'DoubleMuonQCDFakeRate', 
		{'cut': 'evt_tag_analysisevnt_sel_rec_Fake == 1 && evt_tag_dimuon_rec_Fake == 1 && evt_tag_dielectron_rec_Fake == 0 && dilep_pt_rec_Fake < 100. && dilep_mass_rec_Fake > 40. && dilep_mass_rec > 40.', 'skim': 'ISR_detector_only_v1', 'combine_cuts': False, 'weight': 'evt_weight_fake'}, 
		['/data8/DATA/SMP/Run2Legacy_v3/2016//ISR_detector_only_v1/DoubleMuonQCDFakeRate/periodH/190420_142531/0000/SKFlatNtuple_2016_DATA_6.root'], 
		'/home/jhkim/MultiUniv/PlotConfiguration/ISR/2016/Output_MetFt_L_v2_LL_v1_ISR_detector_only_v1_Eff_SF_v1_ISR/DoubleMuonQCDFakeRate_H/DoubleMuonQCDFakeRate_H_tmp_0.root ', 
		{'ptll_100': {'fold': 0, 'range': (100, 0, 100), 'name': 'dilep_pt_rec', 'xaxis': 'pt_{ll} [GeV]'}, 'mll_80_100': {'fold': 0, 'range': (20, 80, 100), 'name': 'dilep_mass_rec', 'xaxis': 'm_{ll} [GeV]'}, 'PU': {'fold': 0, 'range': (50, 0, 50), 'name': 'nPV', 'xaxis': 'Number of PU'}, 'mll_60_80': {'fold': 0, 'range': (20, 60, 80), 'name': 'dilep_mass_rec', 'xaxis': 'm_{ll} [GeV]'}, 'mll': {'fold': 0, 'range': (380, 20, 400), 'name': 'dilep_mass_rec', 'xaxis': 'm_{ll} [GeV]'}, 'ptll': {'fold': 0, 'range': (100, 0, 1000), 'name': 'dilep_pt_rec', 'xaxis': 'pt_{ll} [GeV]'}, 'mll_40_60': {'fold': 0, 'range': (20, 40, 60), 'name': 'dilep_mass_rec', 'xaxis': 'm_{ll} [GeV]'}}, 
		[], 
		{}, 
		{'detector_level': 'evt_tag_dimuon_rec == 1 && evt_tag_analysisevnt_sel_rec == 1 && dilep_pt_rec < 100. && dilep_mass_rec > 40'}, 
		'1==1', 
		{}, 
		False) 

