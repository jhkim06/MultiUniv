#ifndef Fitting_Response_H
#define Fitting_Response_H

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
#include "TLegend.h"
#include "TLatex.h"

#include <map>
#include <iostream>
#include <fstream>

using namespace std;

class Fitting_Response : public TS_Correction_Core {

  public:
    Fitting_Response();
    ~Fitting_Response();

    void MakeProfile(TString sample);
    void FitProfile(TString sample);
    //void FitProfileCombined();
    //void FitProfile_8TeV_13TeV();

  private:
    map<TString,TProfile*> MapProfile;

    void SetProfile();
    void FillProfile(TString sample);
    void SaveProfile(TString sample);
    void UpdateBestParameter(TF1* fcn_, Double_t *par_, Double_t *best_par_,
                                        Double_t &chi2_, Double_t &best_chi2_, 
                                        Double_t &NDF_, Double_t &best_NDF_,
                                        TString &fitting_method_, TString &best_fitting_method_);

    void SaveFitParameter(ofstream &fout_, Double_t *best_par_,
                          Int_t i_flav_, Int_t i_eta_, Int_t i_cut_);

/*    void SaveFitParameter(ofstream &fout_, Double_t *best_par_,
                          Int_t i_flav_, Int_t i_eta_, Int_t i_cut_);
    void SaveFitParameter2(ofstream &fout_, Double_t *best_par_,
                           Int_t i_flav_, Int_t i_eta_, Int_t i_cut_);
*/  
};

#endif
