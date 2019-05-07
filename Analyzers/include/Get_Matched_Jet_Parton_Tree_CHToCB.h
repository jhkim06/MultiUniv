#ifndef Get_Matched_Jet_Parton_Tree_CHToCB_h
#define Get_Matched_Jet_Parton_Tree_CHToCB_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "GenMatching_CHToCB.h"

class Get_Matched_Jet_Parton_Tree_CHToCB : public AnalyzerCore {

public:
  Get_Matched_Jet_Parton_Tree_CHToCB();
  ~Get_Matched_Jet_Parton_Tree_CHToCB();

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

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
 


};



#endif

