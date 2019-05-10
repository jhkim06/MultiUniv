#ifndef Skim_Leptons_h
#define Skim_Leptons_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class Skim_Leptons : public AnalyzerCore {

public:
  Skim_Leptons();
  ~Skim_Leptons();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();

private:


  bool   Is_baseW;
  double baseW;
  bool   Is_pdf_error;
  double pdf_error_Up, pdf_error_Do;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;

};



#endif

