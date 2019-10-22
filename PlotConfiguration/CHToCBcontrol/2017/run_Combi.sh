
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




#------------------------------------
#### ver. 2 (19. 06. 10)
#mkShapes.py --pycfg  configuration_2b_Combi.py -n 20 --nTotFiles 0  --overWrite --doBatch 
#checkMakeShapeBatch.py -y 2017 -n 20 --nTotFiles 0 --RundirBase $SKFlatRunlogDir --SkimName MetFt_L_v1_TTSemiLep_v3_K2_v1_CHToCB_2b

#sleep 30m
#mkShapes.py --pycfg  configuration_2b_Combi.py -n 20 --nTotFiles 0  --overWrite --doHadd --cleanUp

#mkPDfUncert.py --pycfg  configuration_2b_Combi.py --overWrite --cleanUp

#sleep 5s
#mkPlot.py --pycfg configuration_2b_Combi.py --inputFile=Output_MetFt_L_v2_TTSemiLep_v1_K2_v1_CHToCB_2b_Combi/CHToCB_2b_Combi.root  --minLogC=1 --maxLogC=1000 --showIntegralLegend=1


mkDatacards.py --pycfg configuration_2b_Combi.py --inputFile=Output_MetFt_L_v2_TTSemiLep_v1_K2_v1_CHToCB_2b_Combi/CHToCB_2b_Combi.root 


