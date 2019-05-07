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

rm JobCheck.log

: '
for sample in SingleMuon SingleElectron TTLJ_powheg TTLL_powheg TTJJ_powheg DYJets10to50_MG DYJets WJets_MG WW_pythia WZ_pythia ZZ_pythia ttW ttZ
do
  echo $sample
  ./mkGardener.py --Category TTSemiLep -a Skim_TTSemiLep -y 2017 -i $sample  -n 50 --nTotFiles 1  --userflags MetFt,L --skimV 9 --dry_run 
done
'
for sample in SingleMuon SingleElectron TTLJ_powheg TTLL_powheg TTJJ_powheg DYJets10to50_MG DYJets WJets_MG WW_pythia WZ_pythia ZZ_pythia
do
  echo $sample
  mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2017 -i $sample  -n 500 --nTotFiles 1  --InSkim METFt_L_v0 --userflags TTSemiLepMu --skimV 999
done
#for sample in DoubleEG DoubleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 9 --dry_run 
#done

