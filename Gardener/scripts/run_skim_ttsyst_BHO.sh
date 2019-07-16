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


# for TT SemiLeptonic MC
for sample in TT_MG ttbb TTLJ_powheg_Up TTLJ_powheg_Do TTLJ_powheg_mass_Up TTLJ_powheg_hdamp_Up TTLJ_powheg_hdamp_Do TTLL_powheg_Up TTLL_powheg_Do TTLL_powheg_mass_Up TTLL_powheg_mass_Do TTLL_powheg_hdamp_Up TTLL_powheg_hdamp_Do TTJJ_powheg_Up TTJJ_powheg_Do TTJJ_powheg_mass_Do TTJJ_powheg_hdamp_Up TTJJ_powheg_hdamp_Do
do
  #./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i $sample  -n 300 --nTotFiles 0  --userflags MetFt,L --skimV 1
  #./mkGardener.py --Category SMP -a Skim_TTSemiLep -y 2017 -i $sample -n 300 --nTotFiles 0  --userflags TTSemiLep --InSkim  MetFt_L_v1 --skimV 3 --resubmit
  ./mkGardener.py --Category SMP -a Skim_K2 -y 2017 -i $sample -n 300 --nTotFiles 0  --userflags K2 --InSkim MetFt_L_v1_TTSemiLep_v3 --skimV 1 --resubmit
  #echo 'pass'
  #sleep 5m
done



