#ifndef Skim_K1_h
#define Skim_K1_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "Definitions.h"

class Skim_K1 : public AnalyzerCore {

public:
  Skim_K1();
  ~Skim_K1();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();

private:


  bool   Is_baseW;
  double baseW;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;

  bool   Is_El0;
  bool   Is_El1;
  bool   Is_Mu0;
  bool   Is_Mu1;
  bool   Is_diLep;

  // lepton kinematics
  double El0_pt;
  double El0_eta;
  double El0_phi;
  double El1_pt;
  double El1_eta;
  double El1_phi;
  double Mu0_pt;
  double Mu0_eta;
  double Mu0_phi;
  double Mu1_pt;
  double Mu1_eta;
  double Mu1_phi;

  // diLepton Variables
  DiLepCh diLep_Ch;
  bool diLep_passSelectiveQ;
  TLorentzVector diLep;
  double diLep_m;
  double diLep_pt;
  double diLep_eta;

  // MET related
  double MET;
  double projectedMET; //XXX: projectedMET of what?
  double MT; //XXX: MT of what?
  double MT2;
  int nPV; // evt->nPV()

};



#endif

