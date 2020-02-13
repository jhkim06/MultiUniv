#ifndef TKinFitterDriver_h
#define TKinFitterDriver_h

#include "TString.h"
#include "TRegexp.h"
#include <iostream>
#include <numeric>

#include "TFitConstraintM.h"
#include "TFitConstraintM2Gaus.h"
#include "TFitConstraintMGaus.h"
#include "TAbsFitParticle.h"
#include "TFitParticlePt.h"
#include "TFitParticlePz.h"
#include "TFitParticlePxPy.h"
#include "TFitParticleEtPhi.h"
#include "TKinFitter.h"
#include "TSCorrection.h"

#include "Jet.h"

#include "TSystem.h"
#include "TMVA/Tools.h"
//#include "TMVA/PyMethodBase.h"
#include "TMVA/Reader.h"


using namespace std;

class TKinFitterDriver{

public:

  TKinFitterDriver();
  TKinFitterDriver(int DataYear_,bool useMLCut_, TString MCSample_);
  ~TKinFitterDriver();

  int DataYear;
  void SetDataYear(int i);
  void SetMLCut(bool useMLCut_){ useMLCut = useMLCut_; }

  void SetAllObjects(std::vector<Jet> jet_vector_,
                     std::vector<bool> btag_vector_,
                     TLorentzVector lepton_,
                     TLorentzVector met_);
  void SetHadronicTopBJets(TLorentzVector jet_); // it doesn't check tagging status
  void SetLeptonicTopBJets(TLorentzVector jet_); // it doesn't check tagging status
  void SetWCHUpTypeJets(TLorentzVector jet_); // u/c jet from W(H+)
  void SetWCHDownTypeJets(TLorentzVector jet_); // d/s/b jet from W(H+)
  void SetLepton(TLorentzVector lepton_);
  void SetMET(TLorentzVector met_);
  void SetMETShift(double met_shift_, double met_phi_shift_);
  void SetNeutrino(TLorentzVector met_, double met_shift_, double met_phi_shift_, int i); // i is related to neu. Pz

  void Fit();
  void FindBestChi2Fit(bool UseLeading5Jets=false, bool IsHighMassFitter=false);

  int GetStatus();
  double GetChi2();
  double GetFittedDijetMass();
  double GetInitialDijetMass();
  double GetCorrectedDijetMass();

  double GetBestChi2Variables(TString varName, TString mass_, bool highMassFitter);
  int GetBestStatus(TString mass_="");
  double GetBestChi2(TString mass_="");
  double GetBestFittedDijetMass(TString mass_="");
  double GetBestInitialDijetMass(TString mass_="");
  double GetBestCorrectedDijetMass(TString mass_="");

  double GetBestHadronicTopMass();
  double GetBestLeptonicTopMass();
  double GetBestLeptonicWMass();
  bool GetBestIsRealNeuPz();

  double GetBestHadronicTopMassF();
  double GetBestLeptonicTopMassF();
  double GetBestLeptonicWMassF();
  double GetBestDeltaS();

  std::vector<double> GetHadronicTopMassVector(bool IsConverge=true);
  std::vector<double> GetHadronicTopBPtVector(bool IsConverge=true);
  std::vector<double> GetLeptonicTopBPtVector(bool IsConverge=true);
  std::vector<double> GetWCHDownTypePtVector(bool IsConverge=true);
  std::vector<double> GetWCHUpTypePtVector(bool IsConverge=true);

  enum JET_ASSIGNMENT{
    HADRONIC_TOP_B,
    LEPTONIC_TOP_B,
    W_CH_UP_TYPE,
    W_CH_DOWN_TYPE,
    NONE
  };

  struct ResultContainer{
    ResultContainer(){}
    ~ResultContainer(){}
    int status; //fitter status
    double fitted_dijet_M;
    double initial_dijet_M;
    double corrected_dijet_M;
    double hadronic_top_M;
    double hadronic_top_pt;
    double leptonic_top_M;
    double leptonic_W_M;
    bool IsRealNeuPz;

    double hadronic_top_b_pt;
    double leptonic_top_b_pt;
    double w_ch_up_type_pt;
    double w_ch_down_type_pt;

    // fitted object
    const TLorentzVector* fitted_hadronic_top_b_jet;
    const TLorentzVector* fitted_leptonic_top_b_jet;
    const TLorentzVector* fitted_hadronic_w_ch_jet1;
    const TLorentzVector* fitted_hadronic_w_ch_jet2;

    // F from constraints
    double hadronic_top_mass_F;
    double leptonic_top_mass_F;
    double leptonic_w_mass_F;
    double currS;
    double deltaS;
    double chi2;

    // cuts
    std::map<TString, bool> passMLcut;
    bool passGoodnessCut;
    bool passAngularCorr;
    bool passThirdBTaggingCut;
  };

private:

  void SetJetError(TMatrixD *matrix,  double Pt, double Eta, double Phi, TString flavour_key);
  void SetUnclError(TMatrixD *matrix, TLorentzVector &met);
  double JetErrorPt(double Pt, double Eta, TString flavour_key);
  double JetErrorEta(double Pt, double Eta, TString flavour_key);
  double JetErrorPhi(double Pt, double Eta, TString flavour_key);

  void SetConstraint();
  void SetFitter();
  void SaveResults();

  double CalcChi2();
  double CalcEachChi2(TAbsFitParticle* ptr);
  double CalcEachChi2(TFitConstraintM* ptr, double width);
  double CalcEachChi2(TFitConstraintMGaus* ptr);

  void SetCurrentPermutationJets();
  bool Check_BJet_Assignment();
  bool NextPermutation(bool UseLeading5Jets=false);

  //ML
  TMVA::Reader *tmva_reader;
  // ML variables
  float dijet_deltaR;       // 1 
  float had_w_ch_deltaR;    // 2 

  float had_top_b_jet_csv;
  float lep_top_b_jet_csv;
  float up_type_jet_csv;
  float down_type_jet_csv;

  float hadronic_top_mass;
  float hadronic_top_mass_flipped1; 
  float hadronic_top_mass_flipped2; 
  float tt_deltaPhi;        
  float tt_deltaPhi_flipped1;      
  float tt_deltaPhi_flipped2;      
  float Mbl;                
  float Mbl_flipped1;              
  float Mbl_flipped2;              
 
  bool useMLCut;
  TString MCSample;
  void initML();
  bool ML_Cut(TString mass_); // ex)mass_: "CHToCB_M120"
  double GetMLCut(TString sample);
  void updatesMLVariables();
  bool Kinematic_Cut();
  bool ThirdBTaggingCut();
  bool GoodnessCut();
  bool AngularCorr();

  void Sol_Neutrino_Pz();
  void Resol_Neutrino_Pt();
  double neutrino_pz_sol[2];
  bool IsRealNeuPz;

  TKinFitter *fitter;
  TSCorrection *ts_correction;

  std::vector<Jet> jet_vector;
  std::vector<bool> btag_vector;
  TLorentzVector METv;
  double MET_shift;
  double MET_phi_shift;
  TLorentzVector recal_METv;

  int njets;
  int nbtags;
  std::vector<TKinFitterDriver::JET_ASSIGNMENT> permutation_vector;

  TLorentzVector hadronic_top_b_jet; // b jet comes from hadronic top 
  TLorentzVector leptonic_top_b_jet; // b jet comes from leptonic top
  TLorentzVector hadronic_w_ch_jet1; // u/c jet comes from W(H+)
  TLorentzVector hadronic_w_ch_jet2; // d/s/b jet comes from W(H+)
  TLorentzVector corr_hadronic_top_b_jet; // applied TS Correction
  TLorentzVector corr_leptonic_top_b_jet; 
  TLorentzVector corr_hadronic_w_ch_jet1;
  TLorentzVector corr_hadronic_w_ch_jet2;
  TLorentzVector corr_extra_jet;
  TLorentzVector lepton; // lepton comes from leptonic W
  //TLorentzVector neutrino_pt;
  TLorentzVector neutrino_etphi;
  //TLorentzVector neutrino_pxpy; // neutrino_pxpy comes from leptonic W
  //TLorentzVector neutrino_pz; // neutrino_pz

  TFitParticlePt *fit_hadronic_top_b_jet;
  TFitParticlePt *fit_leptonic_top_b_jet;
  TFitParticlePt *fit_hadronic_w_ch_jet1;
  TFitParticlePt *fit_hadronic_w_ch_jet2;
  TFitParticlePt *fit_extra_jet;
  //std::vector<TFitParticlePt*> fit_extra_jets;
  TFitParticlePt *fit_lepton;
  //TFitParticlePt *fit_neutrino_pt;
  TFitParticleEtPhi *fit_neutrino_etphi;
  //TFitParticlePxPy *fit_neutrino_pxpy;
  //TFitParticlePz *fit_neutrino_pz;

  TMatrixD error_hadronic_top_b_jet; 
  TMatrixD error_leptonic_top_b_jet;
  TMatrixD error_hadronic_w_ch_jet1;
  TMatrixD error_hadronic_w_ch_jet2;
  TMatrixD error_lepton;
  //TMatrixD error_neutrino_pxpy;
  //TMatrixD error_neutrino_pt;
  TMatrixD error_neutrino_etphi;
  //TMatrixD error_neutrino_pz;

  TFitConstraintM *constrain_hadronic_top_M;
  //TFitConstraintMGaus *constrain_hadronic_top_MGaus;
  TFitConstraintM *constrain_leptonic_top_M;
  //TFitConstraintMGaus *constrain_leptonic_top_MGaus;
  TFitConstraintM *constrain_leptonic_W_M;
  //TFitConstraintMGaus *constrain_leptonic_W_MGaus;

  TKinFitterDriver::ResultContainer fit_result;

  std::vector<TKinFitterDriver::ResultContainer> fit_result_vector;
  std::vector<TKinFitterDriver::ResultContainer> GetResults();
  static bool Chi2Comparing(const TKinFitterDriver::ResultContainer& rc1, const TKinFitterDriver::ResultContainer& rc2);
  static bool HadTopPtComparing(const TKinFitterDriver::ResultContainer& rc1, const TKinFitterDriver::ResultContainer& rc2);
  static bool HighMassFitter(const TKinFitterDriver::ResultContainer& rc1, const TKinFitterDriver::ResultContainer& rc2);
};

#endif
