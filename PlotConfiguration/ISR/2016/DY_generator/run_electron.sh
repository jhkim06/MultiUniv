
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

#mkShapes.py --pycfg  configuration_electron.py -n 50 --nTotFiles 0  --overWrite --doBatch --multiQueue  
#mkShapes.py --pycfg  configuration.py -n 300 --nTotFiles 0  --overWrite --doBatch  

#checkMakeShapeBatch.py -y 2017 -n 300 --nTotFiles 0 --RundirBase /data6/Users/salee/SKFlatRunlog/ --SkimName MetFt_L_v0_LL_v0_MuMuOrElEl_v1_PDF

mkShapes.py --pycfg  configuration_electron.py -n 50 --nTotFiles 0  --overWrite --doHadd --cleanUp

#mkPDfUncert.py --pycfg configuration_electron.py --overWrite --cleanUp
#mkPlot.py --pycfg configuration_electron.py --inputFile=Output_Electron_control_SFapplied_ISR_detector_only_v2_Eff_SF_v1_ISR_detector_plots_electron/ISR_detector_plots_electron.root  --minLogC=1 --maxLogC=1000 --showIntegralLegend=0 --minLogCratio=2 --maxLogCratio=5000 
#mkPlot.py --pycfg configuration_electron.py --inputFile=Output_Electron_control_SFapplied_ISR_detector_only_v2_Eff_SF_v1_ISR_detector_plots_electron/electron_hist.root  --minLogC=1 --maxLogC=1000 --showIntegralLegend=0 --minLogCratio=2 --maxLogCratio=5000 
#scp -r Plot_AlPhaS lxplus.cern.ch:www/
