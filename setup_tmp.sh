
export SKFlatV="Run2Legacy_v3"

export SKFlat_WD=`pwd`
export SKFlat_LIB_PATH=$SKFlat_WD/lib/
mkdir -p $SKFlat_LIB_PATH

#mkdir -p $SKFlat_WD/data/$SKFlatV
export DATA_DIR=$SKFlat_WD/data/$SKFlatV
export ROC_DIR=$SKFlat_WD/data/RoccoR_Run2

export KistiSEDir="/xrootd/store/user/$USER/SKFlatOutput/"
export KistiUsrDir="/xrootd_user/$USER/xrootd/" # to access for writing


### USER INFO ####
export SKFlatLogEmail=''
export SKFlatLogWeb='' # leave if blank if you don't have webpage
export SKFlatLogWebDir='' # leave if blank if you don't have webpage

### cvmfs for root ###############################
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
# root v. 6.12/07
export cmsswrel='cmssw/CMSSW_10_2_13'
#export cmsswrel='cmssw-patch/CMSSW_10_4_0_patch1'
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
echo "cmsenving..................................."
eval `scramv1 runtime -sh`
source /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/external/$SCRAM_ARCH/bin/thisroot.sh
cd -
echo "SCRAM_ARCH = "$SCRAM_ARCH
echo "CMSSW Version = "$CMSSW_VERSION

if [[ $HOSTNAME == *"ui"*".sdfarm.kr"* ]]; then

  echo "Working on KISTI"
  export SKFlatRunlogDir="/cms/ldap_home/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/cms/ldap_home/$USER/SKFlatOutput/"

elif [[ $HOSTNAME == *"tamsa1"* ]]; then

  echo "Working on tamsa1 <<<<<<<<<<<<<<<<<<<<<<<<"
  export SKFlatRunlogDir="/data6/Users/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/data8/DATA/SMP/"

elif [[ $HOSTNAME == *"tamsa2"* ]]; then

  echo "Working on tamsa2 <<<<<<<<<<<<<<<<<<<<<<<<"
  export SKFlatRunlogDir="/data6/Users/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/data8/DATA/SMP/"

elif [[ $HOSTNAME == *"knu"* ]]; then

  echo "Working on KNU"
  export SKFlatRunlogDir="/u/user/$USER/scratch/SKFlatRunlog/"
  export SKFlatOutputDir="/u/user/$USER/scratch//SKFlatOutput/"

fi

alias skout="cd $SKFlatOutputDir/$SKFlatV/"

### Library Pathes ################################################
export MYBIN=$SKFlat_WD/bin/
export PYTHONDIR=$SKFlat_WD/python/
export PATH=${MYBIN}:${PYTHONDIR}:${PATH}
export PATH=${SKFlat_WD}/CommonPyTools/scripts/:${PATH}
export PATH=${SKFlat_WD}/ShapeAnalysis/scripts/:${PATH}
export PATH=${SKFlat_WD}/Gardener/scripts/:${PATH}
export PYTHONPATH=${PYTHONPATH}:${SKFlat_WD} 
# this guy is working only python only directory with __init__.py,
# another solution: using sys.path.insert(0,'../../CommonTools/python') instead at a relavant python script

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SKFlat_WD/DataFormats/include/:$SKFlat_WD/AnalyzerTools/include/:$SKFlat_WD/Analyzers/include/:$SKFlat_WD/CommonTools/include/:$SKFlat_WD/KinematicFitter/include
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKFlat_LIB_PATH

source $SKFlat_WD/bin/BashColorSets.sh

# TODO
# Sample list: set the xsec errors
# L1 Skim:
# (1) pdf_err: calculate and put into tree,
# (2)pdf_err, muF,R, alphaS: if empty, 0, or nan, then check size and fill 1 or check at the last calculation?
#  mkShape: (1) muF,R : envelop? (2) static_error [SangEun]



## Todo list ##
python python/PrintToDoLists.py


source $SKFlat_WD/tmp/ToDoLists.sh
rm $SKFlat_WD/tmp/ToDoLists.sh

## Log Dir ##
echo "* Your Log Directory Usage"
du -sh $SKFlatRunlogDir
echo "-----------------------------------------------------------------"
