#!/bin/bash

#echo "Positional Parameters"
#echo '$0 = ' $0
#echo '$1 = ' $1


####################################################################################
#                                                                                  #
#            _     _____ _                         ____        _   _               #
#           | |   / ____| |                       / __ \      | | (_)              #
#  _ __ ___ | | _| (___ | |__   __ _ _ __   ___  | |  | |_ __ | |_ _  ___  _ __    #
# | '_ ` _ \| |/ /\___ \| '_ \ / _` | '_ \ / _ \ | |  | | '_ \| __| |/ _ \| '_ \   #
# | | | | | |   < ____) | | | | (_| | |_) |  __/ | |__| | |_) | |_| | (_) | | | |  #
# |_| |_| |_|_|\_\_____/|_| |_|\__,_| .__/ \___|  \____/| .__/ \__|_|\___/|_| |_|  #
#                                   | |                 | |                        #
#                                   |_|                 |_|                        #
#                                                                                  #
####################################################################################
# --debug 0 default, 1 INFO, 2 DEBUG
# -q :Queue tamsa1(fastq)
# --dry_run : no execution
# --overWrite :
# --doBatch
# --doHadd
# --cleanUp
# --onlyVariable=mll


############################################################################
#            _    _____  _       _                 _   _                   #
#           | |  |  __ \| |     | |               | | (_)                  #
#  _ __ ___ | | _| |__) | | ___ | |_    ___  _ __ | |_ _  ___  _ __        #
# | '_ ` _ \| |/ /  ___/| |/ _ \| __|  / _ \| '_ \| __| |/ _ \| '_ \       #
# | | | | | |   <| |    | | (_) | |_  | (_) | |_) | |_| | (_) | | | |      #
# |_| |_| |_|_|\_\_|    |_|\___/ \__|  \___/| .__/ \__|_|\___/|_| |_|      #
#                                           | |                            #
#                                           |_|                            #
#                                                                          #
############################################################################
# --scaleToPlot : default 2.0
# --showIntegralLegend=0 default
# --onlyVariable=mll

############################################################################################
#        _             _ _                 _           _     _           _             _   #
#       (_)           (_) |               | |         | |   | |         | |           | |  #
#   __ _ ___   _____   _| |_    __ _   ___| |__   ___ | |_  | |__   __ _| |__  _   _  | |  #
#  / _` | \ \ / / _ \ | | __|  / _` | / __| '_ \ / _ \| __| | '_ \ / _` | '_ \| | | | | |  #
# | (_| | |\ V /  __/ | | |_  | (_| | \__ \ | | | (_) | |_  | |_) | (_| | |_) | |_| | |_|  #
#  \__, |_| \_/ \___| |_|\__|  \__,_| |___/_| |_|\___/ \__| |_.__/ \__,_|_.__/ \__, | (_)  #
#   __/ |                                                                       __/ |      #
#  |___/                                                                       |___/       #
#                                                                                          #
############################################################################################

# 1: make shape
# 2: hadd
# 3: make plot

#fake_selection="TLOS TLSS LLOS LLSS"
fake_selection="TLSS LLOS LLSS"

for fake in $fake_selection
do
    echo $fake
    #mkShapes.py --pycfg  $fake/configuration.py -n 50 --nTotFiles 0  --overWrite --doBatch --multiQueue
    mkShapes.py --pycfg  $fake/configuration.py -n 50 --nTotFiles 0  --overWrite --doHadd --cleanUp
done

#mkShapes.py --pycfg  configuration_electron.py -n 50 --nTotFiles 0  --overWrite --doBatch --multiQueue

#checkMakeShapeBatch.py -y 2017 -n 300 --nTotFiles 0 --RundirBase /data6/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0_LL_v0_MuMuOrElEl_v1_PDF

#mkShapes.py --pycfg  configuration_electron.py -n 50 --nTotFiles 0  --overWrite --doHadd --cleanUp
