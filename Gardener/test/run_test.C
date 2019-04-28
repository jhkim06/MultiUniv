R__LOAD_LIBRARY(libPhysics.so)
R__LOAD_LIBRARY(libTree.so)
R__LOAD_LIBRARY(libHist.so)
R__LOAD_LIBRARY(../../lib/libCommonTools.so)
R__LOAD_LIBRARY(../../lib/libDataFormats.so)
R__LOAD_LIBRARY(../../lib/libAnalyzerTools.so)
R__LOAD_LIBRARY(../../lib/libAnalyzers.so)
R__LOAD_LIBRARY(/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/lhapdf/6.2.1-fmblme/lib/libLHAPDF.so)


void run(){

  Skim_DiLep m;


  m.SetTreeName("recoTree/SKFlat");

  //m.MCSample = "WJets_MG";
  m.MCSample = "DYJets";
  m.IsDATA = false;
  m.xsec = 6225.42;
  m.sumW = 123584524;
  m.DataYear = 2017;
  m.Userflags = {
    "MuMuOrElEl",
  };
  m.AddFile("/data8/DATA/SMP/Run2Legacy_v1/2017/MetFt_L_v0_LL_v0_MuMuOrElEl_v1/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/190101_204350/0000/SKFlatNtuple_2017_MC_10.root");
  //m.AddFile("./WJetAll.root");
  m.SetOutfilePath("SKFlatNtuple_2017_MC.root");
  m.Init();
  m.initializeAnalyzer();
  m.MaxEvent=300;
  //m.Loop();

  m.WriteHist();

}
