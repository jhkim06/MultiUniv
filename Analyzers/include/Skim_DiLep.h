#ifndef Skim_DiLep_h
#define Skim_DiLep_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

class Skim_DiLep : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Skim_DiLep();
  ~Skim_DiLep();

  TTree *newtree;

  void WriteHist();

private:


  bool IsMuMu;
  bool IsElEl;

  //RootHelper rootHelp;
  double DiLepTrg_SF(TString Leg0Key, TString Leg1Key, const vector<Lepton*>& leps, int sys);
  //TBranch *b_trgSF;
  //TBranch *b_trgSF_Up;
  //TBranch *b_trgSF_Dn;

  vector<TString> DiMuTrgs;
  vector<TString> DiElTrigs;

  TString trgSF_Key0, trgSF_Key1;
  Event* evt;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;

  double (MCCorrection::*LeptonID_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonISO_SF)(TString,double,double,int);
  double (MCCorrection::*LeptonReco_SF)(double,double,int);
  double (MCCorrection::*PileUpWeight)(int,int);
 
  double puW, puW_Up, puW_Dn;

  bool PtEtaPass;
  double Lep0PtCut;
  double Lep1PtCut;
  double EtaCut;

  Double_t trgSF;
  Double_t trgSF_Up;
  Double_t trgSF_Dn;

  double recoSF;
  double recoSF_Up;
  double recoSF_Dn;

  double effSfIdIso;


};



#endif

