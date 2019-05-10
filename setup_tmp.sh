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

elif [[ $HOSTNAME == *"tamsa2"* ]]; then

  echo "Working on tamsa2"
  export SKFlatRunlogDir="/data6/Users/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/data9/Users/salee/Higgs"
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

  export GCC_HOME=/usr/
  export PATH=$GCC_HOME/bin:$PATH
  export PATH=$HOME/bin/cmake-3.14.3-Linux-x86_64/bin:$PATH
  export LD_LIBRARY_PATH=$GCC_HOME/lib:$GCC_HOME/lib64:$LD_LIBRARY_PATH
  source /data6/Users/salee/ROOT616/bin/thisroot.sh
  #export LD_LIBRARY_PATH=$GCC_HOME/lib64:$GCC_HOME/lib:$LD_LIBRARY_PATH
  #export LD_LIBRARY_PATH=/home/salee/lib/cling/lib/:$LD_LIBRARY_PATH
  ##export PATH=/home/salee/lib/cling/bin:$PATH
  #export CC=/opt/ohpc/pub/compiler/gcc/7.3.0/gcc
  #export CXX=/opt/ohpc/pub/compiler/gcc/7.3.0/g++
  #export CPP=/opt/ohpc/pub/compiler/gcc/7.3.0/cpp
  #export LD=/opt/ohpc/pub/compiler/gcc/7.3.0/gcc
  #alias  ld='/opt/ohpc/pub/compiler/gcc/7.3.0/gcc'
  #alias  cc='/opt/ohpc/pub/compiler/gcc/7.3.0/gcc'
  #source /data6/Users/salee/ROOT616/bin/thisroot.sh
  #export PATH=/share/apps/python2.7/bin/:$PATH

  #export CMS_PATH=/cvmfs/cms.cern.ch
  #source $CMS_PATH/cmsset_default.sh
  #export SCRAM_ARCH=slc6_amd64_gcc630
  #cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0/src/
  #eval `scramv1 runtime -sh`
  #cd -
  #source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0/external/slc6_amd64_gcc630/bin/thisroot.sh
  #source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.14.06/x86_64-centos7-gcc48-opt/bin/thisroot.sh
  #source /data6/Users/salee/ROOT616/bin/thisroot.sh
  #export PYTHONPATH=$PYTHONPATH:/data6/Users/salee/ROOTLib
elif [[ $HOSTNAME == *"tamsa1"* ]]; then

  echo "Working on tamsa1"
  export SKFlatRunlogDir="/data6/Users/$USER/SKFlatRunlog/"
  export SKFlatOutputDir="/data9/Users/salee/Higgs"
  #export SKFlatOutputDir="/data7/Users/$USER/SKFlatOutput/"
  export DATA_DIR=$SKFlat_WD/data/$SKFlatV


  export GCC_HOME=/usr/
  export PATH=$GCC_HOME/bin:$PATH
  export LD_LIBRARY_PATH=$GCC_HOME/lib/gcc/x86_64-redhat-linux:$GCC_HOME/lib64:$LD_LIBRARY_PATH
  source /data6/Users/salee/ROOT616/bin/thisroot.sh
  #export LD_LIBRARY_PATH=$GCC_HOME/lib64:$GCC_HOME/lib:$LD_LIBRARY_PATH
  #export LD_LIBRARY_PATH=/home/salee/lib/cling/lib/:$LD_LIBRARY_PATH
  ##export PATH=/home/salee/lib/cling/bin:$PATH
  #export CC=/opt/ohpc/pub/compiler/gcc/7.3.0/gcc
  #export CXX=/opt/ohpc/pub/compiler/gcc/7.3.0/g++
  #export CPP=/opt/ohpc/pub/compiler/gcc/7.3.0/cpp
  #export LD=/opt/ohpc/pub/compiler/gcc/7.3.0/gcc
  #alias  ld='/opt/ohpc/pub/compiler/gcc/7.3.0/gcc'
  #alias  cc='/opt/ohpc/pub/compiler/gcc/7.3.0/gcc'
  #source /data6/Users/salee/ROOT616/bin/thisroot.sh
  #export PATH=/share/apps/python2.7/bin/:$PATH

  #export CMS_PATH=/cvmfs/cms.cern.ch
  #source $CMS_PATH/cmsset_default.sh
  #export SCRAM_ARCH=slc6_amd64_gcc630
  #cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0/src/
  #eval `scramv1 runtime -sh`
  #cd -
  #source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_2_0/external/slc6_amd64_gcc630/bin/thisroot.sh
  #source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.14.06/x86_64-centos7-gcc48-opt/bin/thisroot.sh
  #source /data6/Users/salee/ROOT616/bin/thisroot.sh
  #export PYTHONPATH=$PYTHONPATH:/data6/Users/salee/ROOTLib


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
export PATH=${SKFlat_WD}/ShapeAnalysis/scripts/:${PATH}
export PATH=${SKFlat_WD}/Gardener/scripts/:${PATH}

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SKFlat_WD/DataFormats/include/:$SKFlat_WD/AnalyzerTools/include/:$SKFlat_WD/Analyzers/include/:$SKFlat_WD/CommonTools/include/
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
