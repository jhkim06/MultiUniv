#!/bin/bash
base_dir='/data7/DATA/SKFlat/Run2Legacy_v1/2017/PrivateMC/'


for mass in 'M020' 'M030' 'M040' 'M060' 'M070' 'M075' 'M085' 'M090' 'M100' 'M120' 'M130' 'M140' 'M160'
do
  ./MakeSampleList.py --base $base_dir --sample 'ChargedHiggsToCB_'$mass'_TuneCP5_PSweights_13TeV-madgraph-pythia8' --alias 'CHToCB_'$mass
done
