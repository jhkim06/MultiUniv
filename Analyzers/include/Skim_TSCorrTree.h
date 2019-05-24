#ifndef Skim_TSCorrTree_h
#define Skim_TSCorrTree_h

#include "AnalyzerCore.h"
#include "RootHelper.h"
#include "GenMatching_CHToCB.h"
#include "TSCorrection.h"


class Skim_TSCorrTree : public AnalyzerCore {

public:
  Skim_TSCorrTree();
  ~Skim_TSCorrTree();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();

  Event* evt;

  TTree *newtree;

  void WriteHist();  

private:
  GenMatching_CHToCB *gen_matcher;
  TSCorrection *ts_correction;

  double baseW;

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

  map<TString,TFormula*> response;
  map<TString,TFormula*> flavour;
  map<TString,TFormula*> ptBin;
  map<TString,TFormula*> etaBin;

  std::vector<Muon> muons;
  std::vector<Electron> electrons;
 
  std::vector<Muon> muons_loose;
  std::vector<Electron> electrons_veto;

  double GetResponse(TString var, TLorentzVector *jet, TLorentzVector *parton);
  double GetResponse_Pt(TLorentzVector *jet, TLorentzVector *parton);
  double GetResponse_Et(TLorentzVector *jet, TLorentzVector *parton);
  double GetResponse_Eta(TLorentzVector *jet, TLorentzVector *parton);
  double GetResponse_Phi(TLorentzVector *jet, TLorentzVector *parton);



};



#endif

