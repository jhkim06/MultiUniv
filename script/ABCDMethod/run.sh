
BASE_PATH=$SKFlat_WD/PlotConfiguration/CHToCBcontrol/2017/
python ABCDMethod.py --base $BASE_PATH \
	--pycfg FakeConfig/configuration_Fake_El.py \
       	--inputFile Output_MetFt_L_v2_TTSemiLep_v1_K2_v1_CHToCB_Fake_El/CHToCB_Fake_El.root \
	--outFile ABCD_El_CHToCB_2017.root \
	--channel El

python ABCDMethod.py --base $BASE_PATH \
	--pycfg FakeConfig/configuration_Fake_Mu.py \
       	--inputFile Output_MetFt_L_v2_TTSemiLep_v1_K2_v1_CHToCB_Fake_Mu/CHToCB_Fake_Mu.root \
	--outFile ABCD_Mu_CHToCB_2017.root \
	--channel Mu
