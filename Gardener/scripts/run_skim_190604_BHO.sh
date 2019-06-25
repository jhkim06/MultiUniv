#!/bin/bash

# --userflags a,b,c,... to be used inside of analyser
#############################
# userflags for Skim
# DoubleLepTrg
#############################

# options: see mkGardener for more details

# --dry_run :Dry run, job will not be submitted.
# --MonitJob True: default False
# -n : number of jobs in SNU, it is 999999 whatever number you put in.
# --nTotFiles : number of files to run

: '
# for data
for sample in SingleElectron SingleMuon
#for sample in SingleMuon
do
  #./mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2017 -i $sample -n 50 --nTotFiles 0  --userflags TTSemiLep --InSkim  MetFt_L_v1 --skimV 2
  #./mkGardener.py --Category SMP -a Skim_K2 -y 2017 -i $sample -n 50 --nTotFiles 0  --userflags K2 --InSkim MetFt_L_v1_TTSemiLep_v2 --skimV 1 --resubmit
  #sleep 1h
done
'
# for TT SemiLeptonic MC
for sample in TTLJ_powheg 
do
  #./mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2017 -i $sample -n 300 --nTotFiles 0  --userflags TTSemiLep --InSkim  MetFt_L_v1 --skimV 2 --resubmit
  ./mkGardener.py --Category SMP -a Skim_K2 -y 2017 -i $sample -n 300 --nTotFiles 0  --userflags K2 --InSkim MetFt_L_v1_TTSemiLep_v2 --skimV 2
  #sleep 1h
done

: '
# other MC
for sample in DYJets10to50_MG DYJets TTJJ_powheg TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia ttW ttZ SingleTop_sch_top SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop ttH_bb ttbb
#for sample in SingleTop_sch_top SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
#for sample in SingleElectron SingleMuon DYJets10to50_MG DYJets TTJJ_powheg TTLJ_powheg TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia ttW ttZ SingleTop_sch_top SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
do
  echo $sample
  #./mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2017 -i $sample -n 50 --nTotFiles 0  --userflags TTSemiLep --InSkim  MetFt_L_v1 --skimV 2
  #./mkGardener.py --Category SMP -a Skim_K2 -y 2017 -i $sample -n 50 --nTotFiles 0  --userflags K2 --InSkim MetFt_L_v1_TTSemiLep_v2 --skimV 1 --resubmit
  #sleep 30m
done
'
#for sample in DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#for sample in DoubleEG DoubleMuon SingleElectron SingleMuon
#for sample in SingleElectron SingleMuon DYJets10to50_MG DYJets TTLJ_powheg TTJJ_powheg TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia ttW ttZ SingleTop_sch_top SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
#for sample in SingleTop_sch_top SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
#for sample in SingleElectron SingleMuon DYJets10to50_MG DYJets TTJJ_powheg TTLJ_powheg TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia ttW ttZ SingleTop_sch_top SingleTop_tch_top SingleTop_tch_antitop SingleTop_tW_top SingleTop_tW_antitop
#do
  #echo $sample
  #./mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2017 -i $sample -n 300 --nTotFiles 0  --userflags TTSemiLep --InSkim  MetFt_L_v1 --skimV 1
  #./mkGardener.py --Category SMP -a Skim_K2 -y 2017 -i $sample -n 50 --nTotFiles 0  --userflags K2 --InSkim MetFt_L_v1_TTSemiLep_v1 --skimV 1
  #sleep 1h
#done




#for sample in DoubleEG DoubleMuon SingleElectron SingleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_Leptons -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 1 --dry_run 
#done

