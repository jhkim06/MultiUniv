#ifndef functions_H
#define functions_H

#include "TString.h"

#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>     //necessary for setprecision

Double_t CrystalFnc(Double_t* x, Double_t* par);
Double_t ResponseFittingFunction(Double_t *x, Double_t *par);
Double_t SigmaErrorFittingFunction(Double_t *x, Double_t *par);
TString ResponseFittingFunction();
TString SigmaErrorFittingFunction();
TString Double_t_to_TString(Double_t num);

#endif


