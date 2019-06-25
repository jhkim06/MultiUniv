#!/bin/bash

# --userflags a,b,c,... to be used inside of analyser
#############################
# userflags for Skim
# DoubleLepTrg
#############################

# options: see mkGardener for more details

# --dry_run :Dry run, job will not be submitted.
# --MonitJob True: default False
# -n : number of jobs in SNU, it is 999999 whatever number you put in.
# --nTotFiles : number of files to run

#for sample in CHToCB_M100 CHToCB_M120 CHToCB_M160
for sample in CHToCB_M020 CHToCB_M030 CHToCB_M040 CHToCB_M050 CHToCB_M060 CHToCB_M070 CHToCB_M075 CHToCB_M085 CHToCB_M090 CHToCB_M100 CHToCB_M120 CHToCB_M130 CHToCB_M140 CHToCB_M160
do
  echo $sample
 #./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 500 --nTotFiles 0  --userflags MetFt,L --skimV 1
 #./mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2017 -i $sample  -n 500 --nTotFiles 0  --userflags TTSemiLep --InSkim MetFt_L_v1 --skimV 2
 ./mkGardener.py --Category SMP -a Skim_K2 -y 2017 -i $sample  -n 500 --nTotFiles 0  --userflags K2 --InSkim MetFt_L_v1_TTSemiLep_v2 --skimV 2
done

#for sample in DoubleEG DoubleMuon SingleElectron SingleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_Leptons -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 1 --dry_run 
#done

