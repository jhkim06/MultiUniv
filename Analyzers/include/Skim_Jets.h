#ifndef Skim_Jets_h
#define Skim_Jets_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class Skim_Jets : public AnalyzerCore {

public:
  Skim_Jets();
  ~Skim_Jets();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  TTree *newtree;

  void WriteHist();

private:

};



#endif

