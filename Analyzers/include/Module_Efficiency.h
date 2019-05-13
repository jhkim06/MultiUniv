#ifndef Module_Efficiency_h
#define Module_Efficiency_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class Module_Efficiency : public AnalyzerCore {

public:
  Module_Efficiency();
  ~Module_Efficiency();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();

private:

  std::vector<Lepton*> leps;
  double Aod_pt[2], Aod_eta[2]; //TODO lets use vector later

  double trgSF;
  double trgSF_Up;
  double trgSF_Dn;

  double recoSF;
  double recoSF_Up;
  double recoSF_Dn;

  double IdSF, IdSF_Up, IdSF_Dn;
  double IsoSF, IsoSF_Up, IsoSF_Dn;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);

  std::vector<Muon> muons;
  std::vector<Electron> electrons;

  TString LeptonID_key;
  TString trgSF_key0, trgSF_key1;

  TString LeptonISO_key;


};



#endif

