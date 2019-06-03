#!/bin/bash

for mass in 'M020' 'M030' 'M040' 'M060' 'M070' 'M075' 'M085' 'M090' 'M100' 'M120' 'M130' 'M140' 'M160'
do
  ./MakeSampleSummary.py --alias 'CHToCB_'$mass --sample 'ChargedHiggsToCB_'$mass'_TuneCP5_PSweights_13TeV-madgraph-pythia8' --xsec '365.34' --out 'SampleSummary_Signal_CHToCB.txt'
done
