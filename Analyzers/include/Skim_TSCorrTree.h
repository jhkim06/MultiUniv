#ifndef GetTSCorrTree_h
#define GetTSCorrTree_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "GenMatching_CHToCB.h"


class GetTSCorrTree : public AnalyzerCore {

public:
  GetTSCorrTree();
  ~GetTSCorrTree();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();

private:
  GenMatching_CHToCB *gen_matcher;

  //out obj. reco
  TLorentzVector *b_jet_from_top;
  TLorentzVector *b_jet_from_anti_top;
  TLorentzVector *down_type_jet_from_w_ch;
  TLorentzVector *up_type_jet_from_w_ch;
  TLorentzVector *lepton;
  TLorentzVector *METv;

  //out obj. truth
  TLorentzVector *b_parton_from_top;
  TLorentzVector *b_parton_from_anti_top;
  TLorentzVector *down_type_parton_from_w_ch;
  TLorentzVector *up_type_parton_from_w_ch;
  TLorentzVector *neutrino;

  int down_type_parton_flavour;
  int up_type_parton_flavour;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
 


};



#endif

