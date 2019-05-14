{  
  TString base_dir = std::getenv("TSCorrWD");
  if(base_dir==""){
    cout << "Exception  :    TSCorrWD is not defined!" << endl;
    cout << "                >>    source setup.sh" << endl;
    exit(1);
  }
  TString path = gSystem->GetIncludePath();
  //cout << path << endl;
  path.Append(" -I" + base_dir + "include ");
  gSystem->SetIncludePath(path);
  cout << "include path: " << path << endl;
  gROOT->ProcessLine(".L src/Ntuple_Reader.C+")
  //gROOT->ProcessLine(".L src/tdrstyle.C+");
  //gROOT->ProcessLine(".L src/functions.C+");
  //gROOT->ProcessLine(".L src/TS_Correction_Core.C+");
  //gROOT->ProcessLine(".L src/TS_Correction.C+");
  //gROOT->ProcessLine(".L src/Fitting_Response.C+");
  //gROOT->ProcessLine(".L src/Fitting_Histogram.C+");
  //gROOT->ProcessLine(".L src/Fitting_Mass.C+");
}
