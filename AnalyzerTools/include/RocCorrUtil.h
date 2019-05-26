#ifndef RocCorrUtil_h
#define RocCorrUtil_h

#include "TRandom.h"
//#include <TROOT.h>
//#include <TChain.h>
//#include <TFile.h>
//#include <TString.h>
//#include "TLorentzVector.h"
#include "TString.h"
//#include "TMath.h"
//#include "TProfile.h"
//#include <sstream>      
//#include "TRint.h"
#include <vector>
#include <iostream>
#include "RoccoR.h"
#include "Muon.h"
#include "Gen.h"

class RocCorrUtil{

  public:
    RocCorrUtil(TString data);
    ~RocCorrUtil();
    void CalcScaleAndError(Muon& mu, int s, int m, const ULong64_t event, vector<Gen> gens, const bool IsDATA );
  private:
    RoccoR RC;


};

#endif

