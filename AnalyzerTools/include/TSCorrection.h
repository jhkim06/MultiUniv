#ifndef TSCorrection_h
#define TSCorrection_h

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include "TString.h"
#include "TFormula.h"

class TSCorrection{

public:

  TSCorrection();
  ~TSCorrection();

  void ReadFittedError(TString fileName);
  void ReadFittedMean(TString fileName);
  void ReadFittedResponse(TString fileName);

  int DataYear;
  void SetDataYear(int i);

  double GetFittedError(TString key, double x);
  double GetFittedMean(TString key, double x);
  double GetFittedResponse(TString key, double x);

  bool PassResponseCut(TString key, double x, double response, double n_sigma=2.0);

private:

  std::map<TString, TFormula*> MapFittedErrorFormula;
  std::map<TString, TFormula*> MapFittedMeanFormula;
  std::map<TString, TFormula*> MapFittedResponseFormula;


};

#endif
