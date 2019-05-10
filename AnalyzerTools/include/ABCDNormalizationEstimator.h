#ifndef ABCDNormalizationEstimator_h
#define ABCDNormalizationEstimator_h

#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"

#include "Lepton.h"
#include "Muon.h"
#include "Electron.h"
#include "AnalyzerParameter.h"

class ABCDNormalizationEstimator{ //modification of FakeBackgroundEstimator

public:

  ABCDNormalizationEstimator();
  ~ABCDNormalizationEstimator();

  void ReadHistograms();

  bool IgnoreNoHist;

  int DataYear;
  void SetDataYear(int i);

  std::map< TString, TH1D* > map_hist_Electron_1D;
  std::map< TString, TH1D* > map_hist_Muon_1D;
  std::map< TString, TH2D* > map_hist_Electron_2D;
  std::map< TString, TH2D* > map_hist_Muon_2D;

  double GetElectronABCDNormalization_1D(TString ID, TString key, double sceta, int stat=0);
  double GetMuonABCDNormalization_1D(TString ID, TString key, double eta, int stat=0);
  double GetElectronABCDNormalization_2D(TString ID, TString key, double mass, double pt, int stat=0);
  double GetMuonABCDNormalization_2D(TString ID, TString key, double mass, double pt, int stat=0);

  bool HasLooseLepton;

};

#endif
