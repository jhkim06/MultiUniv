#!/bin/bash

for sample in DoubleEG DoubleMuon SingleElectron SingleMuon
do
  ./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 300 --nTotFiles 1  --userflags MetFt,L --skimV 2
  sleep 2h
done


