#!/bin/bash -f

# --userflags a,b,c,... to be used inside of analyser

#############################
# userflags for Skim_DiLep
# MuMu,ElEl,MuMuOrElEl
#############################

# options: see mkGardener for more details
# --no_exec :Dry run, job will not be submitted.
# --MonitJob True: default False
# -n : number of jobs in SNU, it is 999999 whatever number you put in.
# --nTotFiles : number of files to run

rm JobCheck.log

for sample in DYJets10to50_MG DYJets 
#for sample in ZToMuMu_M_50_120_powheg ZToMuMu_M_120_200_powheg ZToMuMu_M_200_400_powheg
#for sample in TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#for sample in DYFSR_PHOTOS DYFSR_PYTHIA DY_MuMu_FSR_PYTHIA DY_MuMu_FSR_PHOTOS 
#for sample in DYFSR_PHOTOS DYFSR_PYTHIA 
#for sample in DoubleEG DoubleMuon TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#for sample in DoubleMuon DoubleEG TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
#for sample in DoubleEG DoubleMuon TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
#for sample in EGamma DoubleMuon DYJets10to50_MG DYJets TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
#for sample in EGamma DoubleMuon TTLL_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia
do
  echo $sample
  #mkGardener.py --Category SMP -a Skim_ISR -y 2016 -i $sample -n 50 --skimV 1 --userflags MakeZptCorrNtuple --multiQueue 
  #mkGardener.py --Category SMP -a Skim_ISR -y 2016 -i $sample -n 50 --skimV 1 --userflags ISR --multiQueue 
  #mkGardener.py --Category SMP -a Skim_ISR -y 2016 -i $sample -n 50 --skimV 1 --userflags ISR_generator_only --multiQueue --treeDir GEN --OnlyGenLevel 
  #mkGardener.py --Category SMP -a Skim_ISR -y 2016 -i $sample -n 50 --skimV 1 --userflags ISR --multiQueue  --dry_run
  #mkGardener.py --Category SMP -a Skim_ISR -y 2016 -i $sample -n 50 --skimV 1 --userflags ISR_detector_only --multiQueue 

  #mkGardener.py --Category SMP -a Skim_ISR -y 2017 -i $sample -n 50 --skimV 1 --userflags MakeZptCorrNtuple --multiQueue 
  #mkGardener.py --Category SMP -a Skim_ISR -y 2017 -i $sample -n 50 --skimV 1 --userflags ISR_generator_only --multiQueue --treeDir GEN  --OnlyGenLevel
  #mkGardener.py --Category SMP -a Skim_ISR -y 2017 -i $sample -n 50 --skimV 1 --userflags ISR --multiQueue 
  #mkGardener.py --Category SMP -a Skim_ISR -y 2017 -i $sample -n 50 --skimV 1 --userflags ISR_detector_only --multiQueue 

  mkGardener.py --Category SMP -a Skim_ISR -y 2018 -i $sample -n 50 --skimV 1 --userflags MakeZptCorrNtuple --multiQueue 
  #mkGardener.py --Category SMP -a Skim_ISR -y 2018 -i $sample -n 50 --skimV 1 --userflags ISR_detector_only --multiQueue
  #mkGardener.py --Category SMP -a Skim_ISR -y 2018 -i $sample -n 50 --skimV 1 --userflags ISR --multiQueue 
done

#for sample in DoubleEG DoubleMuon DYJets10to50_MG DYJets TT_powheg WJets_MG WW_pythia WZ_pythia ZZ_pythia 
#do
#  echo $sample
#  ./mkGardener.py --Category SMP -a Skim_DiLep -y 2016 -i $sample  -n 500 --nTotFiles 1  --userflags MetFt,L --skimV 9 --no_exec 
#done
