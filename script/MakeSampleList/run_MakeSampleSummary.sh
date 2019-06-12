#!/bin/bash


# to make CH sample lists
: '
for mass in 'M020' 'M030' 'M040' 'M050' 'M060' 'M070' 'M075' 'M085' 'M090' 'M100' 'M110' 'M120' 'M130' 'M140' 'M160'
do
  ./MakeSampleSummary.py --alias 'CHToCB_'$mass --sample 'ChargedHiggsToCB_'$mass'_TuneCP5_PSweights_13TeV-madgraph-pythia8' --xsec '365.34' --out 'SampleSummary_Signal_CHToCB.txt'
done
'

# to make TT systematic lists
./MakeSampleSummary.py --sample TTJets_TuneCP5_13TeV-madgraphMLM-pythia8 --alias TT_MG --xsec '831.59' --out 'SampleSummary_ttbar_syst.txt'
./MakeSampleSummary.py --sample ttbb_4FS_ckm_NNPDF31_TuneCP5_amcatnlo_madspin_pythia --alias ttbb --xsec '0.6' --out 'SampleSummary_ttbar_syst.txt'
./MakeSampleSummary.py --sample TTToSemiLeptonic_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_Do --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToSemiLeptonic_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_Up --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToSemiLeptonic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_hdamp_Do --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToSemiLeptonic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTLJ_powheg_hdamp_Up --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToSemiLeptonic_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_mass_Do --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToSemiLeptonic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_mass_Up --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

#TODO change cross section
./MakeSampleSummary.py --sample TTToHadronic_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_Do --xsec '377.96' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToHadronic_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_Up --xsec '377.96' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToHadronic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_hdamp_Do --xsec '377.96' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToHadronic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTJJ_powheg_hdamp_Up --xsec '377.96' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToHadronic_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_mass_Do --xsec '377.96' --out 'SampleSummary_ttbar_syst.txt'

#./MakeSampleSummary.py --sample TTToHadronic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTJJ_powheg_mass_Up --xsec '377.96' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTTo2L2Nu_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_Do --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTTo2L2Nu_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_Up --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTTo2L2Nu_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_hdamp_Do --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTTo2L2Nu_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTLL_powheg_hdamp_Up --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTTo2L2Nu_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_mass_Do --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTTo2L2Nu_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_mass_Up --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'
