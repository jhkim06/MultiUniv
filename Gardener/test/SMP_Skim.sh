#!/bin/bash

# --userflags a,b,c,... to be used inside of analyser
# userflags for Skim
# DoubleLepTrg

#python python/SKFlat.py -a SMP_SkimTree -y 2017 -i DYtest -n 50 &
#python ../python/SKFlat.py -a SMP_Validation -y 2017 -i DYJets -n 5 --nTotFiles 5 --userflags haha,hoho  &
./mkGardener.py -a SMP_SkimTree -y 2017 -i DYJets -n 5 --nTotFiles 5 --userflags DoubleLepTrg &
#./mkGardener.py -a SMP_Validation -y 2017 -i DYJets -n 5 --nTotFiles 5 --userflags haha,hoho --no_exec &
#python ../python/SKFlat.py -a SMP_Validation -y 2017 -i DYJets -n 5 --nTotFiles 5 --userflags haha,hoho --no_exec &

#python python/SKFlat.py -a SMP_Validation -y 2017 -i DYJets -n 50 --skim SMP_SkimTree &
#python python/SKFlat.py -a ExampleRun -y 2017 -i DYtest -n 50 &

#python python/SKFlat.py -a SMPValidation -y 2017 -i TTLL_powheg -n 20 --skim SkimTree_SMP &
#python python/SKFlat.py -a SMPValidation -y 2017 -i WJets_MG -n 20 --skim SkimTree_SMP &
#python python/SKFlat.py -a SMPValidation -y 2017 -i WW_pythia -n 10 --skim SkimTree_SMP &
#python python/SKFlat.py -a SMPValidation -y 2017 -i WZ_pythia -n 10 --skim SkimTree_SMP &
#python python/SKFlat.py -a SMPValidation -y 2017 -i ZZ_pythia -n 10 --skim SkimTree_SMP &
#python python/SKFlat.py -a SMPValidation -y 2017 -i DoubleEG -n 20 --userflags diLep &
#python python/SKFlat.py -a SMPValidation -y 2017 -i DoubleEG -n 20 --skim SkimTree_SMP &
#python python/SKFlat.py -a SMP_Validation -y 2017 -i DoubleMuon -n 20  --userflags diLep&
#python python/SKFlat.py -a SMPValidation -y 2017 -i DoubleMuon -n 20 --skim SkimTree_SMP  --userflags diLep&
#python python/SKFlat.py -a SMPValidation -y 2017 -i DYJets -n 100 --skim SkimTree_SMP &

#python python/SKFlat.py -a SMPValidation -y 2017 -i DoubleEG -n 20 &
#python python/SKFlat.py -a SMPValidation -y 2017 -i DoubleMuon -n 20 &
#python python/SKFlat.py -a SMPValidation -y 2017 -i DYJets -n 100 &
#python python/SKFlat.py -a SMPValidation -y 2017 -i TTLL_powheg -n 20 &
#python python/SKFlat.py -a SMPValidation -y 2017 -i WJets_MG -n 50 &
#python python/SKFlat.py -a SMPValidation -y 2017 -i WW_pythia -n 10 &
#python python/SKFlat.py -a SMPValidation -y 2017 -i WZ_pythia -n 10 &
#python python/SKFlat.py -a SMPValidation -y 2017 -i ZZ_pythia -n 10 &
