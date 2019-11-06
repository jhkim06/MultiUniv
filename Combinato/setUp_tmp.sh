# from: https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/
pushd .
cd /data6/Users/salee/CMS/
#export SCRAM_ARCH=slc7_amd64_gcc700
#cmsrel CMSSW_10_2_13
cd CMSSW_10_2_13/src
cmsenv
#git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
#cd HiggsAnalysis/CombinedLimit
#cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
#git fetch origin
#git checkout v8.0.1
#scramv1 b clean; scramv1 b

popd

echo "CMSSW_BASE is"
echo $CMSSW_BASE
