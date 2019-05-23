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

  std::vector<Muon> muons; // default muon in this analyzer: apply ROC as saved in the SKFlat ntuple
  std::vector<Muon> muons_woROC; // muon without ROC
  std::vector<Muon> muons_updatedROC; // muon applied ROC on the fly (updated ROC)
  std::vector<Muon> muons_updatedROC_zpt; // muon applied ROC on the fly, variation set 2, Zpt
  std::vector<Muon> muons_updatedROC_ewk; // muon applied ROC on the fly, variation set 3, ewk
  std::vector<Muon> muons_updatedROC_dM; // muon applied ROC on the fly, variation set 4, dM

  std::vector<Electron> electrons;
  std::vector<Lepton*> leps;


  /*
  bool   Is_El0;
  bool   Is_El1;
  bool   Is_Mu0;
  bool   Is_Mu1;
  */
  bool   Is_singleLep;
  bool   Is_diLep;
  
  // diLepton Variables
  DiLepCh diLep_Ch;
  bool diLep_passSelectiveQ;
  TLorentzVector diLep;
  double diLep_m;
  double diLep_pt;
  double diLep_eta;

  // without muon momentum correction
  double diLep_m_woROC;
  double diLep_pt_woROC;
  double diLep_eta_woROC;

  double diLep_m_updatedROC;
  double diLep_pt_updatedROC;
  double diLep_eta_updatedROC;

  double diLep_m_updatedROC_zpt;
  double diLep_pt_updatedROC_zpt;
  double diLep_eta_updatedROC_zpt;

  double diLep_m_updatedROC_ewk;
  double diLep_pt_updatedROC_ewk;
  double diLep_eta_updatedROC_ewk;

  double diLep_m_updatedROC_dM;
  double diLep_pt_updatedROC_dM;
  double diLep_eta_updatedROC_dM;

  // MET related
  double MET;
  double projectedMET; //XXX: projectedMET of what?
  double MT; //XXX: MT of what?
  double MT2;
  int nPV; // evt->nPV()

};



#endif

