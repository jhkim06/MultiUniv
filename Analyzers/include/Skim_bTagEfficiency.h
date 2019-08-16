#ifndef Skim_bTagEfficiency_h
#define Skim_bTagEfficiency_h

#include "AnalyzerCore.h"

class Skim_bTagEfficiency : public AnalyzerCore {

public:

  void initializeAnalyzer();

  void executeEvent();


  Skim_bTagEfficiency();
  ~Skim_bTagEfficiency();

  TTree *newtree;
  //virtual void WriteHist();  

private:
  map<TString,TFormula*> flavour;
  map<TString,TFormula*> ptBin;
  map<TString,TFormula*> etaBin;

  std::vector<Jet> jets;

};



#endif

