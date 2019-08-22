#ifndef LeptonSFs_h
#define LeptonSFs_h

#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

#include "Definitions.h"
#include "AnalyzerParameter.h"

using namespace std;

class LeptonSFs {

 public:
  //LeptonSFs();
  ~LeptonSFs();

  LeptonSFs(LeptonType leptonType, const unsigned int nLepton, const TString idName, const TString isoName, const TString trigName, unsigned int dataYear);
  LeptonSFs(LeptonType leptonType, const unsigned int nLepton, const TString idName, const TString isoName, const TString trigName, unsigned int dataYear, const TString additionalName);

  // make branch name
    void setBranchForSFs(TTree *tree);
    void resetSFs();
    void setIDSF(Double_t sf, SysUpDown sys);
    void setISOSF(Double_t sf, SysUpDown sys);
    void setTriggerSF(Double_t sf, SysUpDown sys);
    void setAnalyzerParameter(AnalyzerParameter & param);

    unsigned int getNLeptons();

 private:

    static map<TString,TString> muon_IDname_key_map;
    static map<TString, map<TString, TString>>  muon_ISOname_key_map;
    static map<TString, map<TString, vector<TString>>> muon_TRIGname_key_map;

    unsigned int dataYear_;
    bool momentumCorrected_;
    LeptonType leptonType_;
    unsigned int nLepton_;
    TString idName_;
    TString isoName_;
    TString trigName_;
    TString additionalName_;

    std::map<TString, TString> idName_key;
    std::map<TString, TString> isoName_key;
    std::map<TString, vector<TString>> trigName_key; // use vector for trigger since double lepton trigger use two keys for each legs

    TString leptonName;
    TString strLeptonN;
    TString outIdBranchName;
    TString outIsoBranchName;
    TString outTrigBranchName;
    TString outAdditionalBranchName;

    Double_t recoSF, recoSFUp, recoSFDown;
    Double_t idSF, idSFUp, idSFDown;
    Double_t isoSF, isoSFUp, isoSFDown;
    Double_t trigSF, trigSFUp, trigSFDown;
    Double_t additionalSF, additionalSFUp, additionalSFDown;

};

#endif
