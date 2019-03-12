export SKFlat_WD=`pwd`
#TODO
export PYTHONPATH=${PYTHONPATH}:${SKFlat_WD} 
# this guy is working only python only directory with __init__.py,
# another solution: using sys.path.insert(0,'../../CommonTools/python') instead at a relavant python script

export SKFlat_LIB_PATH=$SKFlat_WD/lib/
mkdir -p $SKFlat_LIB_PATH

export SKFlatV="Run2Legacy_v1"
mkdir -p $SKFlat_WD/data/$SKFlatV

export SKFlatSEDir="/xrootd/store/user/$USER/SKFlatOutput/"

#### USER INFO ####
export SKFlatLogEmail=''
export SKFlatLogWeb='' # leave if blank if you don't have webpage
export SKFlatLogWebDir='' # leave if blank if you don't have webpage

if [[ $HOSTNAME == *"ui"*".sdfarm.kr"* ]]; then

  echo "Working on KISTI"
  export SKFlatRunlogDir="/cms/ldap_home/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/cms/ldap_home/$USER/SKFlatOutput/"
  export DATA_DIR=data/$SKFlatV

  export CMS_PATH=/cvmfs/cms.cern.ch
  source $CMS_PATH/cmsset_default.sh
  export SCRAM_ARCH=slc6_amd64_gcc630
  cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_9_cand2/src/
  eval `scramv1 runtime -sh`
  cd -
  source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_9_cand2/external/slc6_amd64_gcc630/bin/thisroot.sh

elif [[ $HOSTNAME == *"cms.snu.ac.kr"* ]]; then

  echo "Working on 42cluster"
  export SKFlatRunlogDir="/data7/Users/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/data8/DATA/SMP/"
  #export SKFlatOutputDir="/data7/Users/$USER/SKFlatOutput/"
  export DATA_DIR=$SKFlat_WD/data/$SKFlatV

  #source /share/apps/root_v6-12-06/bin/thisroot.sh
  #export GCC_HOME=/share/apps/gcc491
  #export PATH=$GCC_HOME/bin:$PATH
  #export LD_LIBRARY_PATH=$GCC_HOME/lib64:$GCC_HOME/lib:$LD_LIBRARY_PATH

  #export CMS_PATH=/cvmfs/cms.cern.ch
  #source $CMS_PATH/cmsset_default.sh
  #export SCRAM_ARCH=slc6_amd64_gcc630
  #cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_9_cand2/src/
  #eval `scramv1 runtime -sh`
  #cd -
  #source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_9_cand2/external/slc6_amd64_gcc630/bin/thisroot.sh

  source /share/apps/root_v6-14-04/bin/thisroot.sh
  export GCC_HOME=/share/apps/gcc491
  export PATH=$GCC_HOME/bin:$PATH
  export LD_LIBRARY_PATH=$GCC_HOME/lib64:$GCC_HOME/lib:$LD_LIBRARY_PATH
  export LD_LIBRARY_PATH=/share/apps/python2.7/lib/:$LD_LIBRARY_PATH
  export PATH=/share/apps/python2.7/bin/:$PATH

  #export CMS_PATH=/cvmfs/cms.cern.ch
  #source $CMS_PATH/cmsset_default.sh
  #export SCRAM_ARCH=slc6_amd64_gcc630
  #cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0/src/
  #eval `scramv1 runtime -sh`
  #cd -
  #source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0/external/slc6_amd64_gcc630/bin/thisroot.sh


elif [[ $HOSTNAME == *"knu"* ]]; then

  echo "Working on KNU"
  export SKFlatRunlogDir="/u/user/$USER/scratch/SKFlatRunlog/"
  export SKFlatOutputDir="/u/user/$USER/scratch//SKFlatOutput/"
  export DATA_DIR=$SKFlat_WD/data/$SKFlatV

  export CMS_PATH=/cvmfs/cms.cern.ch
  source $CMS_PATH/cmsset_default.sh
  export SCRAM_ARCH=slc6_amd64_gcc630
  cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_9_cand2/src/
  eval `scramv1 runtime -sh`
  cd -
  source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_9_cand2/external/slc6_amd64_gcc630/bin/thisroot.sh

fi

alias skout="cd $SKFlatOutputDir/$SKFlatV/"

export MYBIN=$SKFlat_WD/bin/
export PYTHONDIR=$SKFlat_WD/python/
export PATH=${MYBIN}:${PYTHONDIR}:${PATH}
export PATH=${SKFlat_WD}/CommonPyTools/scripts/:${PATH}

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SKFlat_WD/DataFormats/include/:$SKFlat_WD/AnalyzerTools/include/:$SKFlat_WD/Analyzers/include/:$SKFlat_WD/CommonTools/include/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKFlat_LIB_PATH

source $SKFlat_WD/bin/BashColorSets.sh

## Todo list ##
python python/PrintToDoLists.py
source $SKFlat_WD/tmp/ToDoLists.sh
rm $SKFlat_WD/tmp/ToDoLists.sh

## Log Dir ##
echo "* Your Log Directory Usage"
du -sh $SKFlatRunlogDir
echo "-----------------------------------------------------------------"
