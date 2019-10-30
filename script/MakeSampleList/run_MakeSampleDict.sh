#!/bin/bash

# to make 2016 bkg sample lists
#./MakeSampleDict.py --in 'SampleSummary_MC_2016.txt' --out 'Samples_SMP_Summer16_miniaodv3.py'

# to make 2017 bkg sample lists
#./MakeSampleDict.py --in 'SampleSummary_MC_2017.txt' --out 'Samples_SMP_Fall17_miniaodv2.py'

# to make 2018 bkg sample lists
#./MakeSampleDict.py --in 'SampleSummary_MC_2018.txt' --out 'Samples_SMP_Autumn18_miniaodv3.py'



# to make CH sample lists
./MakeSampleDict.py --in 'SampleSummary_Signal_CHToCB.txt' --out 'Samples_CHToCB_Fall17_miniaodv2_CHToCB.py'


# to make TT systematic lists
./MakeSampleDict.py --in 'SampleSummary_ttbar_syst.txt' --out 'Samples_ttbar_syst_Fall17_miniaodv2.py'
