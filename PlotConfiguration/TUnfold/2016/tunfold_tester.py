import os
import sys
from ShapeAnalysis.python.ShapeFactory import ShapeFactory

SKFlat_WD = os.getenv('SKFlat_WD')
sys.path.insert(0,SKFlat_WD+'/CommonTools/include')
from Definitions import *

factory = ShapeFactory()
factory._treeName = "tree"
factory.makeNominals( 
		'DYJets', 
		{'skim': '', 'weight': 'weightGen*weightRec'}, 
		['/home/jhkim/MultiUniv/lib/ISR_gen_test.root'], 
		'/home/jhkim/MultiUniv/PlotConfiguration/TUnfold/2016/Output_MuMuOrElEl_v0_DY/DYJets/DYJets_tmp_0.root ', 
		{ 'ptll-mll TUnfold': {'unfoldBinType': ISRUnfold.PtRec2DHist, 'linesToAdd': (".L /home/jhkim/MultiUniv/ShapeAnalysis/python/userfunc.C",),'fold': 3, 'range': None, 'name': 'Get2DPtRecBinIndex(ptRec[2], mRec[2])', 'xaxis': ' Mass p_{T} [GeV]', 'yaxis': 'Events','useTUnfoldBin': True,'go1D': True}, 
                  'mll TUnfold': {'unfoldBinType': ISRUnfold.MassRec1DHist, 'fold': 3, 'range': None, 'name': 'Get1DMassRecBinIndex(mRec[2])', 'xaxis': 'm_{ll} [GeV]','useTUnfoldBin': True,'go1D': True}, 
                  'mll TUnfold matrix': {'unfoldBinType': ISRUnfold.MassMigrationM,'fold': 3, 'range': None, 'name': 'Get1DMassRecBinIndex(mRec[2]):Get1DMassGenBinIndex(mPreFSR[2])', 'xaxis': 'm_{ll} [GeV]','useTUnfoldBin': True,'go1D': False,'isResMatrix':True}
                }, 
		[], 
		{}, 
		{'eventSel': 'ispassRec == 1 && IsElEl == 1'}, 
		'1==1', 
		{'trigg': {'kind': 'weight', 'type': 'shape', 'name': 'trg_2016', 'samples': {'ZZ_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WJets_MG': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'TT_powheg': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'DYJets': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WZ_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF'], 'WW_pythia': ['trgSF_Up/trgSF', 'trgSF_Dn/trgSF']}}}) 

