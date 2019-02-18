#!/bin/bash

# --userflags a,b,c,... to be used inside of analyser
#############################
# userflags for Skim
# DoubleLepTrg
#############################

# options: see mkGardener for more details
# --no_exec
# --MonitJob True: default False

./checkGardenerBatch.py -a Skim_Leptons -y 2017 -i DYJets10to50_MG -n 100 --nTotFiles 1 --RundirBase /data7/Users/salee/SKFlatRunlog/Skim_Leptons_2019_02_18_185530 --SkimName MetFt_L_v0
./checkGardenerBatch.py -a Skim_Leptons -y 2017 -i DoubleEG -n 20 --nTotFiles 1 --RundirBase /data7/Users/salee/SKFlatRunlog/Skim_Leptons_2019_02_18_185524 --SkimName MetFt_L_v0
