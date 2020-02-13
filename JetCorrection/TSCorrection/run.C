//void run_Fitting_Resopnse();
void run_Fitting_Histogram();

void run(){
  run_Fitting_Histogram();
  //run_Fitting_Resopnse();
  //run_Fitting_Mass();
}

void run_Fitting_Resopnse(){

  Fitting_Response *r;
  r = new Fitting_Response();
  //r->MakeProfile("pythia");
  r->FitProfile("pythia_2017");
  //r->FitProfile("herwig");
  //r->FitProfileCombined();
  //r->FitProfile_8TeV_13TeV();

}

void run_Fitting_Histogram(){

  Fitting_Histogram *r;
  r = new Fitting_Histogram();
  //r->MakeHistogram("pythia");
  r->FitHistogram("pythia_2017");
  //r->FitHistogram("herwig");
  r->FitHistMean("pythia_2017");
  //r->FitHistMean("herwig");
  r->FitHistError("pythia_2017");
  //r->FitHistError("herwig");
  //r->DrawCorrectionDifference("pythia");
  //r->SaveHistogram_CorrectionDifference("pythia");

}

/*
void run_Fitting_Mass(){

  Fitting_Mass *m;
  m = new Fitting_Mass();
  TString mode;
  mode="pythia";
  //mode="herwig";
  //mode="CH_120";
  //mode="CH_140";

  m->ReadNTuple(mode);
  m->MakeHistogram();
  m->FitHistogram(mode);
  //m->FitHistogram_Combined(mode);

}
*/
