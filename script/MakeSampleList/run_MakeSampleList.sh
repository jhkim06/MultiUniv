#!/bin/bash
base_dir='/data7/DATA/SKFlat/Run2Legacy_v1/2017/PrivateMC/'


# to make CH sample lists
: '
for mass in 'M020' 'M030' 'M040' 'M050' 'M060' 'M070' 'M075' 'M085' 'M090' 'M100' 'M110' 'M120' 'M130' 'M140' 'M160'
do
  ./MakeSampleList.py --base $base_dir --sample 'ChargedHiggsToCB_'$mass'_TuneCP5_PSweights_13TeV-madgraph-pythia8' --alias 'CHToCB_'$mass
done
'


# to make TT systematic lists
./MakeSampleList.py --base $base_dir --sample TTJets_TuneCP5_13TeV-madgraphMLM-pythia8 --alias TT_MG
./MakeSampleList.py --base $base_dir --sample ttbb_4FS_ckm_NNPDF31_TuneCP5_amcatnlo_madspin_pythia --alias ttbb
./MakeSampleList.py --base $base_dir --sample TTToSemiLeptonic_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_Do
./MakeSampleList.py --base $base_dir --sample TTToSemiLeptonic_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_Up
./MakeSampleList.py --base $base_dir --sample TTToSemiLeptonic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_hdamp_Do
./MakeSampleList.py --base $base_dir --sample TTToSemiLeptonic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTLJ_powheg_hdamp_Up
./MakeSampleList.py --base $base_dir --sample TTToSemiLeptonic_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_mass_Do
./MakeSampleList.py --base $base_dir --sample TTToSemiLeptonic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_mass_Up

./MakeSampleList.py --base $base_dir --sample TTToHadronic_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_Do
./MakeSampleList.py --base $base_dir --sample TTToHadronic_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_Up
./MakeSampleList.py --base $base_dir --sample TTToHadronic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_hdamp_Do
./MakeSampleList.py --base $base_dir --sample TTToHadronic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTJJ_powheg_hdamp_Up
./MakeSampleList.py --base $base_dir --sample TTToHadronic_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_mass_Do
#./MakeSampleList.py --base $base_dir --sample TTToHadronic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_mass_Up

./MakeSampleList.py --base $base_dir --sample TTTo2L2Nu_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_Do
./MakeSampleList.py --base $base_dir --sample TTTo2L2Nu_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_Up
./MakeSampleList.py --base $base_dir --sample TTTo2L2Nu_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_hdamp_Do
./MakeSampleList.py --base $base_dir --sample TTTo2L2Nu_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTLL_powheg_hdamp_Up
./MakeSampleList.py --base $base_dir --sample TTTo2L2Nu_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_mass_Do
./MakeSampleList.py --base $base_dir --sample TTTo2L2Nu_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_mass_Up
