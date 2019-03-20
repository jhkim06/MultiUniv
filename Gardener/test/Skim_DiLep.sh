#!/bin/bash -f

# --userflags a,b,c,... to be used inside of analyser

#############################
# userflags for Skim_DiLep
# MuMu,ElEl,MuMuOrElEl
#############################

# options: see mkGardener for more details
# --dry_run :Dry run, job will not be submitted.
# --MonitJob True: default False
# -n : number of jobs in SNU, it is 999999 whatever number you put in.
# --nTotFiles : number of files to run

rm JobCheck.log

for sample in DYJets10to50_MG
#for sample in DoubleEG DoubleMuon DYJets10to50_MG DYJets TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
do
  echo $sample
  mkGardener.py --Category SMP -a Skim_DiLep -y 2017 -i $sample -n 500 --nTotFiles 1 --InSkim MetFt_L_v0_LL_v0 --userflags MuMuOrElEl --skimV 999 --dry_run
  #checkGardenerBatch.py -a Skim_DiLep -y 2017 -i $sample -n 500 --nTotFiles 0 --RundirBase /data7/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0_LL_v0_MuMuOrElEl_v0
  #./mkGardener.py --Category SMP -a hadd -y 2017 -i $sample -n 500 --nTotFiles 0 --InSkim MetFt_L_v0_LL_v0_MuMuOrElEl_v0 --userflags hadd --skimV 0 --dry_run
  #checkGardenerBatch.py -a hadd -y 2017 -i $sample -n 500 --nTotFiles 0 --RundirBase /data7/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0_LL_v0_MuMuOrElEl_v0_hadd_v0
done

#for sample in DoubleEG DoubleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_DiLep -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 9 --dry_run 
#done

