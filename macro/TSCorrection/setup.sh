#!/bin/bash

if [ $TSCorrWD ]; then
   echo 'WARNING            :  TSCorrWD is already defined as '$TSCorrWD
fi

make_directory(){
 if [ ! -d $1 ]; then
    mkdir -p $1
    echo "directory is not exist! :     mkdir -p "$1
 fi
}

export TSCorrWD=${PWD}"/"
export TSCorrInputRootDir=$TSCorrWD"data/root/" # place for input root file in use
export TSCorrInputTextDir=$TSCorrWD"data/txt/" # place for list
export TSCorrOutTextDir=$TSCorrWD"output/txt/"
export TSCorrOutFormulaDir=$TSCorrWD"output/formula/" # save fitting formula
export TSCorrOutImgDir=$TSCorrWD"output/img/"
export TSCorrOutRootDir=$TSCorrWD"output/root/"

make_directory $TSCorrWD
make_directory $TSCorrInputRootDir
make_directory $TSCorrInputTextDir
make_directory $TSCorrOutTextDir
make_directory $TSCorrOutFormulaDir
make_directory $TSCorrOutImgDir
make_directory $TSCorrOutRootDir

echo 'TSCorrWD              :  '$TSCorrWD
echo 'TSCorrInputRootDir    :  '$TSCorrInputRootDir
echo 'TSCorrInputTextDir    :  '$TSCorrInputTextDir
echo 'TSCorrOutTextDir      :  '$TSCorrOutTextDir
echo 'TSCorrOutFormulaDir   :  '$TSCorrOutFormulaDir
echo 'TSCorrOutImgDir       :  '$TSCorrOutImgDir
echo 'TSCorrOutRootDir      :  '$TSCorrOutRootDir
