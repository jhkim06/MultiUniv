#ifndef Fitting_Histogram_H
#define Fitting_Histogram_H

#include "TS_Correction_Core.h"
#include "functions.h"
#include "tdrstyle.h"

#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TString.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TGraph.h"

#include <map>
#include <iostream>
#include <fstream>

using namespace std;

class Fitting_Histogram : public TS_Correction_Core {

  public:
    Fitting_Histogram();
    ~Fitting_Histogram();

    void MakeHistogram(TString sample);
    void FitHistogram(TString sample);
    void FitHistMean(TString sample);
    void FitHistError(TString sample);
    //void SaveHistogram_CorrectionDifference(TString type_);
    //void DrawCorrectionDifference(TString type_);

  private:
    map<TString, TH1F*> MapHistogram;
    map<TString, TGraph*> MapGraph;
    map<TString, TGraphErrors*> MapGraphErrors;

    void SetHistogram();
    void FillHistogram(TString sample);
    void SaveHistogram(TString sample);

    /*void UpdateBestParameter(TF1* fcn_, Double_t *par_, Double_t *best_par_,
                                        Double_t &chi2_, Double_t &best_chi2_, 
                                        Double_t &NDF_, Double_t &best_NDF_,
                                        TString &fitting_method_, TString &best_fitting_method_);*/
    
    void SaveFitParameter(ofstream &fout_, TString name,
                          Double_t meanPt, Double_t rmsPt,
                          Double_t mean, Double_t mean_error,
                          Double_t sigma, Double_t sigma_error);
    
};

#endif
