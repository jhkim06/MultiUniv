#!/bin/bash

# --userflags a,b,c,... to be used inside of analyser
#############################
# userflags for Skim
# DoubleLepTrg
#############################

# options: see mkGardener for more details
# --no_exec
# --MonitJob True: default False
# -n : number of jobs in SNU, it is 999999 whatever number you put in.
# --nTotFiles : number of files to run

./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i DoubleEG  -n 200 --nTotFiles 1  --userflags MetFt,L --skimV 9 --no_exec 
#./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i DoubleMuon      -n 200  --userflags MetFt,L --skimV 0  
./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i DYJets10to50_MG -n 100  --nTotFiles 1 --userflags MetFt,L  --skimV 9 --no_exec 
#./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i DYJets          -n 100 --userflags MetFt,L  --skimV 0  
#./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i TTLL_powheg     -n 20  --userflags MetFt,L  --skimV 0   
#./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i WJets_MG        -n 20  --userflags MetFt,L  --skimV 0   
#./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i WW_pythia       -n 10  --userflags MetFt,L  --skimV 0   
#./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i WZ_pythia       -n 10  --userflags MetFt,L  --skimV 0   
#./mkGardener.py --Category SMP -a Skim_Leptons -y 2017 -i ZZ_pythia       -n 10  --userflags MetFt,L  --skimV 0   

#./mkGardener.py -a Skim_Leptons -y 2016 -i DoubleEG        -n 200  --userflags MetFt,L --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i DoubleMuon      -n 200  --userflags MetFt,L --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i DYJets10to50_MG -n 100 --userflags MetFt,L  --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i DYJets          -n 100 --userflags MetFt,L  --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i TT_powheg       -n 20  --userflags MetFt,L  --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i WJets_MG        -n 20  --userflags MetFt,L  --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i WW_pythia       -n 10  --userflags MetFt,L  --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i WZ_pythia       -n 10  --userflags MetFt,L  --skimV 0 --no_exec 
#./mkGardener.py -a Skim_Leptons -y 2016 -i ZZ_pythia       -n 10  --userflags MetFt,L  --skimV 0 --no_exec 
