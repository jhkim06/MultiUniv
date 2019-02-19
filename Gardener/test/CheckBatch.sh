#!/bin/bash

# --userflags a,b,c,... to be used inside of analyser
#############################
# userflags for Skim
# DoubleLepTrg
#############################

# options: see mkGardener for more details
# --no_exec
# --MonitJob True: default False
# --nTotFiles : number of files to process

rm JobCheck.log

for sample in DoubleEG DoubleMuon DYJets10to50_MG DYJets TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
do
  echo $sample
  ./checkGardenerBatch.py -a Skim_Leptons -y 2017 -i $sample -n 100  --RundirBase /data7/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0
done
