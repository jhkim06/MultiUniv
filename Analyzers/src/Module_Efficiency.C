#include "Module_Efficiency.h"

void Module_Efficiency::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //=================================
  // Skim Types
  //=================================

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  // New Branch
  // assume the input lepton skim don't have below SFs branch
  newtree->Branch("IsEl", &IsEl,"IsEl/I");
  newtree->Branch("IsMu", &IsMu,"IsMu/I");

  newtree->Branch("L_recoSF",    &L_recoSF,   "L_recoSF/D");
  newtree->Branch("LL_recoSF",    &LL_recoSF,   "LL_recoSF/D");

  newtree->Branch("L_IdSF",    &L_IdSF,   "L_IdSF/D");
  newtree->Branch("LL_IdSF",    &LL_IdSF,   "LL_IdSF/D");

  newtree->Branch("L_IsoSF",    &L_IsoSF,   "L_IsoSF/D");
  newtree->Branch("LL_IsoSF",    &LL_IsoSF,   "LL_IsoSF/D");

}

void Module_Efficiency::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();
  Aod_pt.clear();
  Aod_eta.clear();

  evt = new Event;
  *evt = GetEvent();

  // need to consider ElMu case?
  newtree->SetBranchAddress("IsMu",   &IsMu);  
  newtree->SetBranchAddress("IsEl",   &IsEl);  

  newtree->SetBranchAddress("L_recoSF",   &L_recoSF);  
  newtree->SetBranchAddress("LL_recoSF",   &LL_recoSF);  

  newtree->SetBranchAddress("L_IdSF",   &L_IdSF);  
  newtree->SetBranchAddress("LL_IdSF",   &LL_IdSF);  

  newtree->SetBranchAddress("L_IsoSF",   &L_IsoSF);  
  newtree->SetBranchAddress("LL_IsoSF",   &LL_IsoSF);  

  // get muons and electrons
  muons=GetMuons("POGTightWithTightIso",7.,2.4); // returns muons passing ID and the given kinematic cuts (after the Rochester correction)
  electrons=GetElectrons("passMediumID",9.,2.5); 

  IsMu = 0;
  IsEl = 0;

  // not considered lepton veto here
  if(electrons.size() > 0){
    IsEl = 1; 
  }
  if(muons.size() > 0){
    IsMu = 1;
  }
  if(IsEl && IsMu){
    // compare pt and decide whether to electron or muon
    IsMu = electrons.at(0).Pt() > muons.at(0).Pt() ? 0:1; 
    IsEl = electrons.at(0).Pt() > muons.at(0).Pt() ? 1:0; 
  }

  // pointer to function?
  LeptonID_SF  = NULL;
  LeptonISO_SF = NULL;
  LeptonReco_SF= NULL;

  if( IsEl == 1){
    leps=MakeLeptonPointerVector(electrons);
    LeptonID_key= "passMediumID";

    LeptonID_SF =&MCCorrection::ElectronID_SF; 
    LeptonReco_SF= &MCCorrection::ElectronReco_SF; 
  }
  if( IsMu == 1){
    leps=MakeLeptonPointerVector(muons);
    LeptonID_key="NUM_TightID_DEN_genTracks";
    LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";

    LeptonID_SF =&MCCorrection::MuonID_SF;  
    LeptonISO_SF=&MCCorrection::MuonISO_SF;
  }

  for(int i(0); i < leps.size(); i++){ // pt eta the same to TnP
    if(leps[i]->LeptonFlavour()==Lepton::MUON){
     Aod_pt.push_back(((Muon*)leps.at(i))->MiniAODPt());
     Aod_eta.push_back(leps.at(i)->Eta());
    }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
     Aod_pt.push_back(leps.at(i)->Pt());
     Aod_eta.push_back(((Electron*)leps.at(i))->scEta());
     //if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
    }
  }

  L_recoSF = 1., L_recoSF_Up = 1., L_recoSF_Do = 1.; 
  LL_recoSF = 1., LL_recoSF_Up = 1., LL_recoSF_Do = 1.; 

  L_IdSF = 1., L_IdSF_Up = 1., L_IdSF_Do = 1.; 
  LL_IdSF = 1., LL_IdSF_Up = 1., LL_IdSF_Do = 1.; 

  L_IsoSF = 1., L_IsoSF_Up = 1., L_IsoSF_Do = 1.; 
  LL_IsoSF = 1., LL_IsoSF_Up = 1., LL_IsoSF_Do = 1.;

  if(!IsData){

    for( int i(0); i<Aod_pt.size() ; i++){

       if( i == 2 ) break; // only consider up to two leptons  
    
       if(i==0){   
          
          L_recoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  0) : 1.;
          L_recoSF_Up *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  1) : 1.;
          L_recoSF_Do *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i], -1) : 1.;

          L_IdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i],  0) : 1.;
          L_IdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i],  1) : 1.;
          L_IdSF_Do   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i], -1) : 1.;

          L_IsoSF     *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i],  0) : 1.;
          L_IsoSF_Up  *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i],  1) : 1.;
          L_IsoSF_Do  *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i], -1) : 1.;
       }

       if(i==1){   
          LL_recoSF    = L_recoSF    * (LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  0) : 1.); 
          LL_recoSF_Up = L_recoSF_Up * (LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  1) : 1.); 
          LL_recoSF_Do = L_recoSF_Do * (LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i], -1) : 1.); 
                                     
          LL_IdSF      = L_IdSF      * (LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i],  0) : 1.); 
          LL_IdSF_Up   = L_IdSF_Up   * (LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i],  1) : 1.); 
          LL_IdSF_Do   = L_IdSF_Do   * (LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta[i], Aod_pt[i], -1) : 1.); 
                                     
          LL_IsoSF     = L_IsoSF     * (LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i],  0) : 1.); 
          LL_IsoSF_Up  = L_IsoSF_Up  * (LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i],  1) : 1.); 
          LL_IsoSF_Do  = L_IsoSF_Do  * (LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta[i], Aod_pt[i], -1) : 1.); 
       }   

    }
  }// save SFs for MC

  newtree->Fill();

  return;

}


void Module_Efficiency::executeEventFromParameter(AnalyzerParameter param){

}

Module_Efficiency::Module_Efficiency(){

}

Module_Efficiency::~Module_Efficiency(){

}

void Module_Efficiency::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Module_Efficiency::initializeAnalyzer
  newtree->AutoSave();
  //newtree->Write();
  outfile->cd();
  for(std::map< TString, TH1D* >::iterator mapit = maphist_TH1D.begin(); mapit!=maphist_TH1D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
  }
  for(std::map< TString, TH2D* >::iterator mapit = maphist_TH2D.begin(); mapit!=maphist_TH2D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
  }

  outfile->cd();
  for(std::map< TString, std::map<TString, TH1D*> >::iterator mapit=JSmaphist_TH1D.begin(); mapit!=JSmaphist_TH1D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH1D* > this_maphist = mapit->second;


    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH1D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }

  for(std::map< TString, std::map<TString, TH2D*> >::iterator mapit=JSmaphist_TH2D.begin(); mapit!=JSmaphist_TH2D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH2D* > this_maphist = mapit->second;

    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH2D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }

}

