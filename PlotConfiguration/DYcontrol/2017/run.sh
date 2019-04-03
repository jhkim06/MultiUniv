

#####################################################
#            _     _____ _                      
#           | |   / ____| |                     
#  _ __ ___ | | _| (___ | |__   __ _ _ __   ___ 
# | '_ ` _ \| |/ /\___ \| '_ \ / _` | '_ \ / _ \
# | | | | | |   < ____) | | | | (_| | |_) |  __/
# |_| |_| |_|_|\_\_____/|_| |_|\__,_| .__/ \___|
#                                   | |         
#                                   |_|         
#
#####################################################

# Options
# --debug 0 default, 1 INFO, 2 DEBUG
# -q :Queue tamsa1(fastq)
# --dry_run : no execution
# --overWrite : 
# --doBatch
# --doHadd
# --cleanUp
# --onlyVariable=mll

#for sample in DYJets10to50_MG
##for sample in DoubleEG DoubleMuon DYJets10to50_MG DYJets TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
#do
#  echo $sample
#  mkShapes.py  -i $sample -n 12345 --nTotFiles 1  --overWrite --dry_run
#  #checkGardenerBatch.py -a Skim_DiLep -y 2017 -i $sample -n 500 --nTotFiles 0 --RundirBase /data7/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0_LL_v0_MuMuOrElEl_v0
#  #./mkGardener.py --Category SMP -a hadd -y 2017 -i $sample -n 500 --nTotFiles 0 --InSkim MetFt_L_v0_LL_v0_MuMuOrElEl_v0 --userflags hadd --skimV 0 --dry_run
#  #checkGardenerBatch.py -a hadd -y 2017 -i $sample -n 500 --nTotFiles 0 --RundirBase /data7/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0_LL_v0_MuMuOrElEl_v0_hadd_v0
#done


#mkShapes.py --pycfg  configuration.py -n 400 --nTotFiles 0  --overWrite --doBatch 
#mkShapes.py --pycfg  configuration.py -n 400 --nTotFiles 0  --overWrite --doHadd --cleanUp
mkPlot.py --pycfg configuration.py --inputFile=Output_MetFt_L_v0_LL_v0_MuMuOrElEl_v0_hadd_v0_DY/DY.root --onlyVariable=mll
