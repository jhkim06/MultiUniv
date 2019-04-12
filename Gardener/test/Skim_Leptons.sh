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

for sample in DoubleEG DoubleMuon SingleElectron SingleMuon DYJets10to50_MG DYJets TTJJ_powheg TTLJ_powheg TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia ttW ttZ SingleTop_sch SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
do
  echo $sample
  #./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 1 --dry_run 
  mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 1
done

#for sample in DoubleEG DoubleMuon SingleElectron SingleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_Leptons -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 1 --dry_run 
#done

