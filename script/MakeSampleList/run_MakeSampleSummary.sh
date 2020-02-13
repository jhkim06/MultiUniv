#!/bin/bash


# to make CH sample lists
#for mass in 'M020' 'M030' 'M040' 'M050' 'M060' 'M070' 'M075' 'M085' 'M090' 'M100' 'M110' 'M120' 'M130' 'M140' 'M160'
: '
for mass in 'M090' 'M100' 'M110' 'M120' 'M130' 'M140' 'M150'
do
  ./MakeSampleSummary.py --alias 'CHToCB_'$mass --sample 'ChargedHiggsToCB_'$mass'_TuneCP5_PSweights_13TeV-madgraph-pythia8' --xsec '365.34' --out 'SampleSummary_Signal_CHToCB.txt'
done
'

#ttH samples
#./MakeSampleSummary.py --sample ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8 --alias ttHTobb --xsec '0.2953' --out 'SampleSummary_ttH.txt'

# to make TT systematic lists
#./MakeSampleSummary.py --sample TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8 --alias TT_aMC --xsec '831.59' --out 'SampleSummary_ttbar_syst.txt'
./MakeSampleSummary.py --sample TT_TuneCH3_13TeV-powheg-herwig7 --alias TT_herwig --xsec '831.59' --out 'SampleSummary_ttbar_syst.txt'
#./MakeSampleSummary.py --sample ttbb_4FS_ckm_NNPDF31_TuneCP5_amcatnlo_madspin_pythia --alias ttbb --xsec '2.5' --out 'SampleSummary_ttbar_syst.txt'
./MakeSampleSummary.py --sample TTToSemiLeptonic_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_Tune_Do --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

#./MakeSampleSummary.py --sample TTToSemiLeptonic_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_Tune_Up --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToSemiLeptonic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_hdamp_Do --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

#./MakeSampleSummary.py --sample TTToSemiLeptonic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTLJ_powheg_hdamp_Up --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

#./MakeSampleSummary.py --sample TTToSemiLeptonic_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_mass_Do --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'

./MakeSampleSummary.py --sample TTToSemiLeptonic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLJ_powheg_mass_Up --xsec '365.34' --out 'SampleSummary_ttbar_syst.txt'


#./MakeSampleSummary.py --sample TTTo2L2Nu_TuneCP5down_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_Tune_Do --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'
#
#./MakeSampleSummary.py --sample TTTo2L2Nu_TuneCP5up_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_Tune_Up --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'
#
#./MakeSampleSummary.py --sample TTTo2L2Nu_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_hdamp_Do --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'
#
#./MakeSampleSummary.py --sample TTTo2L2Nu_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias  TTLL_powheg_hdamp_Up --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'
#
#./MakeSampleSummary.py --sample TTTo2L2Nu_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_mass_Do --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'
#
#./MakeSampleSummary.py --sample TTTo2L2Nu_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8 --alias TTLL_powheg_mass_Up --xsec '88.29' --out 'SampleSummary_ttbar_syst.txt'
#




: '
./MakeSampleSummary.py --sample DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8 --alias ForSNU/DYJets_MG --xsec '6225.42' --out 'SampleSummary_DYJets_MG_2018.txt'
./MakeSampleSummary.py --sample DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8 --alias ForSNU/DYJets10to50_MG --xsec '-999' --out 'SampleSummary_DYJets10to50_MG_2018.txt'
./MakeSampleSummary.py --sample ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8 --alias ForSNU/SingleTop_sch_Lep --xsec '-999' --out 'SampleSummary_SingleTop_sch_Lep_2018.txt'
./MakeSampleSummary.py --sample ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8 --alias ForSNU/SingleTop_tW_antitop_Incl --xsec '-999' --out 'SampleSummary_SingleTop_tW_antitop_Incl_2018.txt'
./MakeSampleSummary.py --sample ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8 --alias ForSNU/SingleTop_tW_top_Incl --xsec '-999' --out 'SampleSummary_SingleTop_tW_top_Incl_2018.txt'
./MakeSampleSummary.py --sample ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8 --alias ForSNU/SingleTop_tch_antitop_Incl --xsec '-999' --out 'SampleSummary_SingleTop_tch_antitop_Incl_2018.txt'
./MakeSampleSummary.py --sample ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8 --alias ForSNU/SingleTop_tch_top_Incl --xsec '-999' --out 'SampleSummary_SingleTop_tch_top_Incl_2018.txt'
./MakeSampleSummary.py --sample TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8 --alias ForSNU/TTLJ_powheg --xsec '-999' --out 'SampleSummary_TTLJ_powheg_2018.txt'
./MakeSampleSummary.py --sample TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8 --alias ForSNU/TTLL_powheg --xsec '-999' --out 'SampleSummary_TTLL_powheg_2018.txt'
./MakeSampleSummary.py --sample WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8 --alias ForSNU/WJets_MG --xsec '-999' --out 'SampleSummary_WJets_MG_2018.txt'

./MakeSampleSummary.py --sample WW_TuneCP5_13TeV-pythia8 --alias ForSNU/WW_pythia --xsec '-999' --out 'SampleSummary_WW_pythia_2018.txt'
./MakeSampleSummary.py --sample WZ_TuneCP5_13TeV-pythia8 --alias ForSNU/WZ_pythia --xsec '-999' --out 'SampleSummary_WZ_pythia_2018.txt'
./MakeSampleSummary.py --sample ZZ_TuneCP5_13TeV-pythia8 --alias ForSNU/ZZ_pythia --xsec '-999' --out 'SampleSummary_ZZ_pythia_2018.txt'
./MakeSampleSummary.py --sample ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8 --alias ForSNU/ttW --xsec '-999' --out 'SampleSummary_ttW_2018.txt'
./MakeSampleSummary.py --sample ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8 --alias ForSNU/ttZ --xsec '-999' --out 'SampleSummary_ttZ_2018.txt'
'
