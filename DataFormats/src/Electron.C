#include "Electron.h"

ClassImp(Electron)

Electron::Electron(){

  j_En_up=1.;
  j_En_down=1.;;
  j_Res_up = 1.;
  j_Res_down = 1.;

  j_scEta = -999.;
  j_scPhi = -999.;
  j_scE = -999.;
  j_mvaiso = -999.;
  j_mvanoiso = -999.;
  j_EnergyUnCorr = -999.;
  j_passConversionVeto = false;
  _isGsfCtfScPixChargeConsistent = false;
  j_NMissingHits = 0;
  j_Full5x5_sigmaIetaIeta = -999.;
  j_dEtaSeed = -999.;
  j_dPhiIn = -999.;
  j_HoverE  = -999.;
  j_InvEminusInvP = -999.;
  j_e2x5OverE5x5 = -999.;
  j_e1x5OverE5x5 = -999.;
  j_trkiso = -999.;
  j_dr03EcalRecHitSumEt = -999.;
  j_dr03HcalDepth1TowerSumEt = -999.;
  j_IDBit = 0;
  j_Rho = -999.;
  this->SetLeptonFlavour(ELECTRON);
}

Electron::~Electron(){

}

void Electron::SetEnShift(double en_up, double en_down){
  j_En_up = en_up;
  j_En_down = en_down;
}

void Electron::SetResShift(double res_up, double res_down){
  j_Res_up = res_up;
  j_Res_down = res_down;
}

void Electron::SetSC(double sceta, double scphi, double sce){
  j_scEta = sceta;
  j_scPhi = scphi;
  j_scE = sce;
}

void Electron::SetMVA(double mvaiso, double mvanoiso){
  j_mvaiso = mvaiso;
  j_mvanoiso = mvanoiso;
}

void Electron::SetSelectiveQ(bool isGsfCtfScPixChargeConsistent){
  _isGsfCtfScPixChargeConsistent = isGsfCtfScPixChargeConsistent;
}

void Electron::SetUncorrE(double une){
  j_EnergyUnCorr = une;
}

void Electron::SetPassConversionVeto(bool b){
  j_passConversionVeto = b;
}

void Electron::SetNMissingHits(int n){
  j_NMissingHits = n;
}

void Electron::SetCutBasedIDVariables(
    double Full5x5_sigmaIetaIeta,
    double dEtaSeed,
    double dPhiIn,
    double HoverE,
    double InvEminusInvP,
    double e2x5OverE5x5,
    double e1x5OverE5x5,
    double trackIso,
    double dr03EcalRecHitSumEt,
    double dr03HcalDepth1TowerSumEt
  ){
  j_Full5x5_sigmaIetaIeta = Full5x5_sigmaIetaIeta;
  j_dEtaSeed = dEtaSeed;
  j_dPhiIn = dPhiIn;
  j_HoverE = HoverE;
  j_InvEminusInvP = InvEminusInvP;
  j_e2x5OverE5x5 = e2x5OverE5x5;
  j_e1x5OverE5x5 = e1x5OverE5x5;
  j_trkiso = trackIso;
  j_dr03EcalRecHitSumEt = dr03EcalRecHitSumEt;
  j_dr03HcalDepth1TowerSumEt = dr03HcalDepth1TowerSumEt;
}

void Electron::SetIDBit(unsigned int idbit){
  j_IDBit = idbit;
}

void Electron::SetRelPFIso_Rho(double r){
  j_RelPFIso_Rho = r;
  this->SetRelIso(r);
}

double Electron::EA(){

  //==== RecoEgamma/ElectronIdentification/data/Fall17/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt
  
  double eta = fabs(this->scEta());

  if     (eta<1.000) return 0.1440;
  else if(eta<1.479) return 0.1562;
  else if(eta<2.000) return 0.1032;
  else if(eta<2.200) return 0.0859;
  else if(eta<2.300) return 0.1116;
  else if(eta<2.400) return 0.1321;
  else if(eta<2.500) return 0.1654;
  else return 0.1654;

}

bool Electron::PassID(TString ID){

  //==== XXX veto Gap Always
  if(etaRegion()==GAP) return false;

  //==== POG
  if(ID=="passVetoID") return passVetoID();
  if(ID=="passLooseID") return passLooseID();
  if(ID=="passMediumID") return passMediumID();
  if(ID=="passTightID") return passTightID();
  if(ID=="passHEEPID") return passHEEPID();
  if(ID=="passMVAID_noIso_WP80") return passMVAID_noIso_WP80();
  if(ID=="passMVAID_noIso_WP90") return passMVAID_noIso_WP90();
  if(ID=="passMVAID_iso_WP80") return passMVAID_iso_WP80();
  if(ID=="passMVAID_iso_WP90") return passMVAID_iso_WP90();
  //==== Customized
  if(ID=="passTightID_noIso") return Pass_CutBasedTightNoIso();
  if(ID=="passMediumID_noIso") return Pass_CutBasedMediumNoIso();
  if(ID=="passLooseID_noIso") return Pass_CutBasedLooseNoIso();
  if(ID=="SUSYTight") return Pass_SUSYTight();
  if(ID=="SUSYLoose") return Pass_SUSYLoose();
  if(ID=="NOCUT") return true;
  if(ID=="TEST") return Pass_TESTID();

  cout << "[Electron::PassID] No id : " << ID << endl;
  exit(EXIT_FAILURE);

  return false;
}

bool Electron::Pass_SUSYMVAWP(TString wp){

  double sceta = fabs(scEta());

    double cutA = 0.77;
    double cutB = 0.52;

  if(wp=="Tight"){
    if     (sceta<0.8)  { cutA = 0.77; cutB = 0.52; }
    else if(sceta<1.479){ cutA = 0.56; cutB = 0.11; } 
    else                { cutA = 0.48; cutB =-0.01; }
  }
  else if(wp=="Loose"){
    if     (sceta<0.8)  { cutA =-0.48; cutB =-0.85; }
    else if(sceta<1.479){ cutA =-0.67; cutB =-0.91; }
    else                { cutA =-0.49; cutB =-0.83; }
  }
  else{}

  double cutSlope = (cutB-cutA) / 10.;
  double cutFinal = std::min( cutA, std::max(cutB , cutA + cutSlope*(this->Pt()-15.) ) );

  //==== Using NoIso MVA, because we apply MiniIso later
  if(MVANoIso()>cutFinal) return true;
  else return false;

}

bool Electron::Pass_SUSYTight(){
  if(! Pass_SUSYMVAWP("Tight") ) return false;
  if(! (MiniRelIso()<0.1) ) return false;	
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<8.) ) return false;
  if(! PassConversionVeto() ) return false;
  if(! (NMissingHits()==0) ) return false;

  return true;
}

bool Electron::Pass_SUSYLoose(){
  if(! Pass_SUSYMVAWP("Loose") ) return false;
  if(! (MiniRelIso()<0.4) ) return false;
  if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<8.) ) return false;
  if(! PassConversionVeto() ) return false;
  if(! (NMissingHits()==0) ) return false;

  return true;
}

//==== TEST ID

bool Electron::Pass_TESTID(){
  return true;
}

bool Electron::Pass_CutBasedTightNoIso(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (Full5x5_sigmaIetaIeta() < 0.0104) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00255) ) return false;
    if(! (fabs(dPhiIn()) < 0.022) ) return false;
    if(! (HoverE() < 0.026 + 1.15/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.159) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (Full5x5_sigmaIetaIeta() < 0.0353) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00501) ) return false;
    if(! (fabs(dPhiIn()) <  0.0236 ) ) return false;
    if(! (HoverE() < 0.0188 + 2.06/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.0197) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}

bool Electron::Pass_CutBasedMediumNoIso(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (Full5x5_sigmaIetaIeta() < 0.0106) ) return false;
    if(! (fabs(dEtaSeed()) < 0.0032) ) return false;
    if(! (fabs(dPhiIn()) < 0.0547) ) return false;
    if(! (HoverE() < 0.046 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.184) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (Full5x5_sigmaIetaIeta() < 0.0387) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00632) ) return false;
    if(! (fabs(dPhiIn()) <  0.0394 ) ) return false;
    if(! (HoverE() < 0.0275 + 2.52/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.0721) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}

bool Electron::Pass_CutBasedLooseNoIso(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (Full5x5_sigmaIetaIeta() < 0.0112) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00377) ) return false;
    if(! (fabs(dPhiIn()) < 0.0884) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.193) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (Full5x5_sigmaIetaIeta() < 0.0425) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00674) ) return false;
    if(! (fabs(dPhiIn()) <  0.169 ) ) return false;
    if(! (HoverE() < 0.0441 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.111) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}

bool Electron::isCutBasedTightIso(){

  if( fabs(scEta()) <= 1.479 ){
    if(! (RelIso() < 0.0287+0.506/UncorrPt()) ) return false;
    return true;
  }
  else{
    if(! (RelIso() < 0.0445+0.963/UncorrPt()) ) return false;
    return true;
  }
}

bool Electron::isCutBasedMediumIso(){

  if( fabs(scEta()) <= 1.479 ){
    if(! (RelIso() < 0.0478+0.506/UncorrPt()) ) return false;
    return true;
  }
  else{
    if(! (RelIso() < 0.0658+0.963/UncorrPt()) ) return false;
    return true;
  }
}

bool Electron::isAntiIso(TString ID, int syst){
  // for ChargedHiggsToCB : ID==Tight
  // for ISR : ID==Medium
  double reliso = RelIso();
  double reliso_min_b=0; //b means barrel
  double reliso_max_b=0;
  double reliso_min_e=0; // e means endcap
  double reliso_max_e=0;
  if(ID=="Tight"){
    if(syst==0){
      reliso_min_b=0.0287+0.506/UncorrPt(); //reliso cut at POGTight ID
      reliso_max_b=0.198+0.506/UncorrPt(); // reliso cut at POGVeto ID
      reliso_min_e=0.0445+0.963/UncorrPt(); //reliso cut at POGTight ID
      reliso_max_e=0.203+0.963/UncorrPt(); // reliso cut at POGVeto ID
    }
    else if(syst==1){
      //XXX: currently same as central
      reliso_min_b=0.0287+0.506/UncorrPt(); //reliso cut at POGTight ID
      reliso_max_b=0.198+0.506/UncorrPt(); // reliso cut at POGVeto ID
      reliso_min_e=0.0445+0.963/UncorrPt(); //reliso cut at POGTight ID
      reliso_max_e=0.203+0.963/UncorrPt(); // reliso cut at POGVeto ID
    }
    else if(syst==-1){
      //XXX: currently same as central
      reliso_min_b=0.0287+0.506/UncorrPt(); //reliso cut at POGTight ID
      reliso_max_b=0.198+0.506/UncorrPt(); // reliso cut at POGVeto ID
      reliso_min_e=0.0445+0.963/UncorrPt(); //reliso cut at POGTight ID
      reliso_max_e=0.203+0.963/UncorrPt(); // reliso cut at POGVeto ID
    }
    else{
      cout << "[Electron::isAntiIso] No syst flag : " << syst << endl;
      exit(EXIT_FAILURE);
      return false;
    }
  }
  else if(ID=="Medium"){
    if(syst==0){
      reliso_min_b=0.0478+0.506/UncorrPt(); //reliso cut at POGMedium ID
      reliso_max_b=0.112+0.506/UncorrPt(); // reliso cut at POGLoose ID
      reliso_min_e=0.0658+0.963/UncorrPt(); //reliso cut at POGMedium ID
      reliso_max_e=0.108+0.963/UncorrPt(); // reliso cut at POGLoose ID
    }
    else if(syst==1){
      //XXX: currently same as central
      reliso_min_b=0.0478+0.506/UncorrPt();
      reliso_max_b=0.112+0.506/UncorrPt();
      reliso_min_e=0.0658+0.963/UncorrPt();
      reliso_max_e=0.108+0.963/UncorrPt();
    }
    else if(syst==-1){
      //XXX: currently same as central
      reliso_min_b=0.0478+0.506/UncorrPt();
      reliso_max_b=0.112+0.506/UncorrPt();
      reliso_min_e=0.0658+0.963/UncorrPt();
      reliso_max_e=0.108+0.963/UncorrPt();
    }
    else{
      cout << "[Electron::isAntiIso] No syst flag : " << syst << endl;
      exit(EXIT_FAILURE);
      return false;
    }
  }
  else{
    cout << "[Muon::isAntiIso] No id : " << ID << endl;
    exit(EXIT_FAILURE);
  }

  if( fabs(scEta()) <= 1.479 ){
      if(! ( reliso > reliso_min_b && reliso < reliso_max_b )) return false;
      return true;
  }
  else{
    if(! ( reliso > reliso_min_e && reliso < reliso_max_e) ) return false;
    return true;
  }
}

bool Electron::Pass_CutBasedVetoNoIso(){
  
  if( fabs(scEta()) <= 1.479 ){
    
    if(! (Full5x5_sigmaIetaIeta() < 0.0126 ) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00463 ) ) return false;
    if(! (fabs(dPhiIn()) < 0.148) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.209) ) return false;
    if(! (NMissingHits() <= 2) ) return false;
    if(! (PassConversionVeto()) ) return false;
    
    return true;
  
  }
  else{
    
    if(! (Full5x5_sigmaIetaIeta() < 0.0457) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00814) ) return false;
    if(! (fabs(dPhiIn()) < 0.19) ) return false;
    if(! (HoverE() < 0.05 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.132) ) return false;
    if(! (NMissingHits() <= 3) ) return false;
    if(! (PassConversionVeto()) ) return false;
    
    return true;
  
  }

}

bool Electron::Pass_CutBasedLoose(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (Full5x5_sigmaIetaIeta() < 0.0112) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00377) ) return false;
    if(! (fabs(dPhiIn()) < 0.0884) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.112+0.506/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.193) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (Full5x5_sigmaIetaIeta() < 0.0425) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00674) ) return false;
    if(! (fabs(dPhiIn()) <  0.169 ) ) return false;
    if(! (HoverE() < 0.0441 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.108+0.963/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.111) ) return false;
    if(! (NMissingHits() <= 1) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}

bool Electron::Pass_CutBasedVeto(){

  if( fabs(scEta()) <= 1.479 ){

    if(! (Full5x5_sigmaIetaIeta() < 0.0126 ) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00463 ) ) return false;
    if(! (fabs(dPhiIn()) < 0.148) ) return false;
    if(! (HoverE() < 0.05 + 1.16/scE() + 0.0324*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.198+0.506/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.209) ) return false;
    if(! (NMissingHits() <= 2) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }
  else{

    if(! (Full5x5_sigmaIetaIeta() < 0.0457) ) return false;
    if(! (fabs(dEtaSeed()) < 0.00814) ) return false;
    if(! (fabs(dPhiIn()) < 0.19) ) return false;
    if(! (HoverE() < 0.05 + 2.54/scE() + 0.183*Rho()/scE()) ) return false;
    if(! (RelIso() < 0.203+0.963/UncorrPt()) ) return false;
    if(! (fabs(InvEminusInvP()) < 0.132) ) return false;
    if(! (NMissingHits() <= 3) ) return false;
    if(! (PassConversionVeto()) ) return false;

    return true;

  }

}

void Electron::SetRho(double r){
  j_Rho = r;
}
