#ifndef TS_Correction_Core_H
#define TS_Correction_Core_H

#include "TF1.h"
#include "TObject.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TFormula.h"

#include <map>
#include <iostream>
#include <fstream>

#include "Ntuple_Reader.h"


using namespace std;

class TS_Correction_Core : public Ntuple_Reader {

  public:
    TS_Correction_Core();
    ~TS_Correction_Core();

    //void ReadNTuple(TString type_);
    //TODO: method to read TS-correction
  protected:

    map<TString,TFormula*> response;
    map<TString,TFormula*> flavour;
    map<TString,TFormula*> ptBin;
    map<TString,TFormula*> etaBin;

    vector<TString> histNameVector;

    void SetHistNameVector();
    double GetResponse(TString var, TLorentzVector *jet, TLorentzVector *parton);
    double GetResponse_Pt(TLorentzVector *jet, TLorentzVector *parton);
    double GetResponse_Et(TLorentzVector *jet, TLorentzVector *parton);
    double GetResponse_Eta(TLorentzVector *jet, TLorentzVector *parton);
    double GetResponse_Phi(TLorentzVector *jet, TLorentzVector *parton);

    map<TString,TFormula*> cut; // response cut
    void SetResponseCuts(TString sample);
 

    /*
    map<TString, TFormula*> cut;
    map<TString, TLorentzVector*> object;
    map<TString, TString*> sample;
    */

    //void SetBranchAddress();
    //void UpdateLorentzVector();

    /*
    void Read_TS_Correction();
    void Read_TS_Correction_Mean();
    void Read_TS_Correction_Error();
    TLorentzVector Get_Corrected_Jet(TLorentzVector inputJet, Int_t i_sample_, Int_t i_corr_, Int_t i_flav_);
    Int_t FindEtaBin(Double_t eta);
    */
};

#endif
