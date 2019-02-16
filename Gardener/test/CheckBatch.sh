#!/bin/bash

# --userflags a,b,c,... to be used inside of analyser
#############################
# userflags for Skim
# DoubleLepTrg
#############################

# options: see mkGardener for more details
# --no_exec
# --MonitJob True: default False

./checkGardenerBatch.py -a Skim_Leptons -y 2017 -i DYJets -n 5 --nTotFiles 5 --RundirBase /data7/Users/salee/SKFlatRunlog/Skim_Leptons_2019_02_16_015021 --SkimName MetFilt_L_v00
./checkGardenerBatch.py -a Skim_Leptons -y 2017 -i DoubleMuon -n 5 --nTotFiles 5 --RundirBase /data7/Users/salee/SKFlatRunlog/Skim_Leptons_2019_02_16_015021 --SkimName MetFilt_L_v00
