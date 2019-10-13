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

for sample in DYJets 
#for sample in DYJets10to50_MG DYJets_MG TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 

#for sample in SingleTop_sch SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
#for sample in DoubleEG DoubleMuon SingleElectron SingleMuon DYJets10to50_MG DYJets TTJJ_powheg TTLJ_powheg TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia ttW ttZ SingleTop_sch SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
do
  echo $sample
  #mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 999
  #mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 999 --dry_run 
  #mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 200 --userflags LL --InSkim MetFt_L_v2 --skimV 1 --multiQueue

  #mkGardener.py --Category SMP -a Skim_Leptons -y 2018 -i $sample -n 100 --InSkim MetFt_L_v2 --userflags MetFt,L --skimV 1 --multiQueue
  mkGardener.py --Category SMP -a Skim_Leptons -y 2018 -i $sample -n 100 --userflags MetFt,L --skimV 2 --multiQueue
done

#for sample in DoubleEG DoubleMuon SingleElectron SingleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_Leptons -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 1 --dry_run 
#done

