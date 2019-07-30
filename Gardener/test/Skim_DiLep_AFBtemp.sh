#!/bin/bash -f

# --userflags a,b,c,... to be used inside of analyser

#############################
# userflags for Skim_DiLep
# MuMu,ElEl,MuMuOrElEl
#############################

# options: see mkGardener for more details
# --no_exec :Dry run, job will not be submitted.
# --MonitJob True: default False
# -n : number of jobs in SNU, it is 999999 whatever number you put in.
# --nTotFiles : number of files to run

rm JobCheck.log

for sample in  DoubleMuon DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#for sample in DoubleEG DoubleMuon DYJets10to50 DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
do
  echo $sample
  mkGardener.py --Category SMP -a Skim_DiLep_AFBtemp -y 2016 -i $sample -n 100 --userflags MuMu --InSkim MetFt_L_v2 --skimV 1 
  #mkGardener.py --Category SMP -q fastq -a Skim_FakeEst -y 2016 -i $sample -n 200 --userflags MuMu --skimV 0 
  #mkGardener.py --Category SMP -q fastq -a Skim_FakeEst -y 2017 -i $sample -n 200 --userflags MuMu --skimV 0 
  #./checkGardenerBatch.py -a Skim_DiLep -y 2017 -i $sample -n 500 --nTotFiles 1 --RundirBase /data7/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0_LL_v0_MuMuOrElEl_v9
done

#for sample in DoubleEG DoubleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_DiLep -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 9 --no_exec 
#done
