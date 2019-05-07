R__LOAD_LIBRARY(libPhysics.so)
R__LOAD_LIBRARY(libTree.so)
R__LOAD_LIBRARY(libHist.so)
R__LOAD_LIBRARY(../../lib/libCommonTools.so)
R__LOAD_LIBRARY(../../lib/libDataFormats.so)
R__LOAD_LIBRARY(../../lib/libAnalyzerTools.so)
R__LOAD_LIBRARY(../../lib/libKinematicFitter.so) //TODO: check if it's working or not without this line
R__LOAD_LIBRARY(../../lib/libAnalyzers.so)
R__LOAD_LIBRARY(/cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/lhapdf/6.2.1-fmblme/lib/libLHAPDF.so)


void run(){

  Skim_TTSemiLep m;


  m.SetTreeName("recoTree/SKFlat");

  //m.MCSample = "WJets_MG";
  m.MCSample = "TTLJ_powheg";
  m.IsDATA = false;
  m.xsec = 365.34;
  m.sumW = 110424244;
  m.DataYear = 2017;
  m.Userflags = {
    "TTSemiLepMu",
  };
  m.AddFile("/data8/DATA/SMP/Run2Legacy_v1/2017/MetFt_L_v1/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/190102_194718/0000/SKFlatNtuple_2017_MC_100.root");
  //m.AddFile("./WJetAll.root");
  m.SetOutfilePath("SKFlatNtuple_2017_MC.root");
  m.Init();
  m.initializeAnalyzer();
  m.MaxEvent=300;
  //m.Loop();

  m.WriteHist();

}
