#include "Skim_K1.h"

void Skim_K1::initializeAnalyzer(){

  Is_El0   = false;
  Is_El1   = false;
  Is_Mu0   = false;
  Is_Mu1   = false;
  Is_diLep = false;

  //initializeAnalyzerTools();
  //=================================
  // Skim Types
  //=================================
  if( HasFlag("muK1")){
    Is_Mu0   = true;
    cout<<"[Skim_K1::initializeAnalyzer] muK1, add Kinematic variables for leading muon"<<endl;
  }
  else if(HasFlag("elK1")){
    Is_El0   = true;
    cout<<"[Skim_K1::initializeAnalyzer] elK1, add Kinematic variables for leading electron"<<endl;
  }
  else if( HasFlag("mumuK1")){
    Is_Mu0   = true;
    Is_Mu1   = true;
    Is_diLep = true;
    cout<<"[Skim_K1::initializeAnalyzer] mumuK1, add Kinematic variables for di-muon"<<endl;
  }
  else if(HasFlag("elelK1")){
    Is_El0   = true;
    Is_El1   = true;
    Is_diLep = true;
    cout<<"[Skim_K1::initializeAnalyzer] elelK1, add Kinematic variables for di-electron"<<endl;
  }
  /*
  else if(HasFlag("mumuOrelelK1")){
    Is_Mu0   = true;
    Is_Mu1   = true;
    Is_El0   = true;
    Is_El1   = true;
    Is_diLep = true;
    cout<<"[Skim_K1::initializeAnalyzer] mumuOrelelK1, add Kinematic variables for di-muon or di-electron"<<endl;
  }
  */
  else{
    cout <<"[Skim_K1::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  // New Branch
  TBranch* b_baseW =(TBranch*) newtree->GetListOfBranches()->FindObject("baseW");
  Is_baseW = false;
  if(b_baseW) {Is_baseW = true;}
  if(Is_baseW == false){
    newtree->Branch("baseW", &baseW,"baseW/D");
  }

  if(Is_El0){
    newtree->Branch("El0_pt", &El0_pt,"El0_pt/D");
    newtree->Branch("El0_eta", &El0_eta,"El0_eta/D");
    newtree->Branch("El0_phi", &El0_phi,"El0_phi/D");
  }
  if(Is_El1){
    newtree->Branch("El1_pt", &El1_pt,"El1_pt/D");
    newtree->Branch("El1_eta", &El1_eta,"El1_eta/D");
    newtree->Branch("El1_phi", &El1_phi,"El1_phi/D");
  }
  if(Is_Mu0){
    newtree->Branch("Mu0_pt", &Mu0_pt,"Mu0_pt/D");
    newtree->Branch("Mu0_eta", &Mu0_eta,"Mu0_eta/D");
    newtree->Branch("Mu0_phi", &Mu0_phi,"Mu0_phi/D");
  }
  if(Is_Mu1){
    newtree->Branch("Mu1_pt", &Mu1_pt,"Mu1_pt/D");
    newtree->Branch("Mu1_eta", &Mu1_eta,"Mu1_eta/D");
    newtree->Branch("Mu1_phi", &Mu1_phi,"Mu1_phi/D");
  }
  if(Is_diLep){
    newtree->Branch("diLep_Ch", &diLep_Ch,"diLep_Ch/I");
    newtree->Branch("diLep_passSelectiveQ", &diLep_passSelectiveQ,"diLep_passSelectiveQ/O");
    newtree->Branch("diLep_m", &diLep_m,"diLep_m/D");
    newtree->Branch("diLep_pt", &diLep_pt,"diLep_pt/D");
    newtree->Branch("diLep_eta", &diLep_eta,"diLep_eta/D");
  }
  
  newtree->Branch("MET", &MET,"MET/D");
  //newtree->Branch("projectedMET", &projectedMET,"projectedMET/D");
  //newtree->Branch("MT", &MT,"MT/D");
  if(Is_diLep){
    newtree->Branch("MT2", &MT2,"MT2/D");
  }
  newtree->Branch("nPV", &nPV,"nPV/D");

}

void Skim_K1::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  diLep_passSelectiveQ = false;

  // Basic Weights if ntuple doesn't have them -----------------------------
  evt = new Event;
  *evt = GetEvent();
  TLorentzVector MET_vector = (TLorentzVector)evt->GetMETVector();

  if(Is_baseW == false){
    if(IsDATA){
      baseW = 1;
    }else{
      baseW = weight_norm_1invpb*evt->MCweight()*evt->GetTriggerLumi("Full");
    }
  }

  if(Is_baseW == false){
    newtree->SetBranchAddress("baseW",&baseW);
  }
  //------------------------------------------------------------------------
  if(Is_El0){
    newtree->Branch("El0_pt", &El0_pt);
    newtree->Branch("El0_eta", &El0_eta);
    newtree->Branch("El0_phi", &El0_phi);
  }
  if(Is_El1){
    newtree->Branch("El1_pt", &El1_pt);
    newtree->Branch("El1_eta", &El1_eta);
    newtree->Branch("El1_phi", &El1_phi);
  }
  if(Is_Mu0){
    newtree->Branch("Mu0_pt", &Mu0_pt);
    newtree->Branch("Mu0_eta", &Mu0_eta);
    newtree->Branch("Mu0_phi", &Mu0_phi);
  }
  if(Is_Mu1){
    newtree->Branch("Mu1_pt", &Mu1_pt);
    newtree->Branch("Mu1_eta", &Mu1_eta);
    newtree->Branch("Mu1_phi", &Mu1_phi);
  }
  if(Is_diLep){
    newtree->Branch("diLep_Ch", &diLep_Ch);
    newtree->Branch("diLep_passSelectiveQ", &diLep_passSelectiveQ);
    newtree->Branch("diLep_m", &diLep_m);
    newtree->Branch("diLep_pt", &diLep_pt);
    newtree->Branch("diLep_eta", &diLep_eta);
  }
  newtree->Branch("MET", &MET);
  //newtree->Branch("projectedMET", &projectedMET);
  //newtree->Branch("MT", &MT);
  if(Is_diLep){
    newtree->Branch("MT2", &MT2);
  }
  newtree->Branch("nPV", &nPV);

  muons=GetMuons("POGLoose",7.,2.4);
  std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  TString ElectronID = HasFlag("elK1") ? "passVetoID" : "passLooseID";
  electrons=GetElectrons("ElectronID",9.,2.5);
  std::sort(electrons.begin(),electrons.end(),PtComparing); //PtComaring @ AnalyzerCore.h

  if(Is_El0){
    if(electrons.size()>=1){
      El0_pt = electrons.at(0).Pt();
      El0_eta = electrons.at(0).Eta();
      El0_phi = electrons.at(0).Phi();
    }
  }
  if(Is_El1){
    if(electrons.size()>1){
      El1_pt = electrons.at(1).Pt();
      El1_eta = electrons.at(1).Eta();
      El1_phi = electrons.at(1).Phi();
    }
  }
  if(Is_Mu0){
    if(muons.size()>=1){
      Mu0_pt = muons.at(0).Pt();
      Mu0_eta = muons.at(0).Eta();
      Mu0_phi = muons.at(0).Phi();
    }
  }
  if(Is_Mu1){
    if(muons.size()>1){
      Mu1_pt = muons.at(1).Pt();
      Mu1_eta = muons.at(1).Eta();
      Mu1_phi = muons.at(1).Eta();
    }
  }
  if(Is_diLep){
    if(muons.size()+electrons.size()==2){
      if(muons.size()==2) leps=MakeLeptonPointerVector(muons);
      else if(electrons.size()==2) leps=MakeLeptonPointerVector(electrons);
      diLep_Ch = DiLepCh::NA;
      diLep_m  = DEFAULT;
      diLep_pt  = DEFAULT;
      diLep_eta  = DEFAULT;
      if(leps.size() > 1){
        if(leps[0]->LeptonFlavour() == Lepton::MUON)if(leps[1]->LeptonFlavour() == Lepton::MUON){
          if(leps[0]->Charge() == 1) if(leps[1]->Charge() == 1) diLep_Ch = DiLepCh::MuMuPP;
          if(leps[0]->Charge() == -1)if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::MuMuMM;
          if(leps[0]->Charge() == 1) if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::MuMuOS;
          if(leps[0]->Charge() == -1)if(leps[1]->Charge() ==  1)diLep_Ch = DiLepCh::MuMuOS;
        }
        if(leps[0]->LeptonFlavour() == Lepton::ELECTRON)if(leps[1]->LeptonFlavour() == Lepton::ELECTRON){
          if(leps[0]->Charge() == 1) if(leps[1]->Charge() == 1) diLep_Ch = DiLepCh::ElElPP;
          if(leps[0]->Charge() == -1)if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::ElElMM;
          if(leps[0]->Charge() == 1) if(leps[1]->Charge() == -1)diLep_Ch = DiLepCh::ElElOS;
          if(leps[0]->Charge() == -1)if(leps[1]->Charge() ==  1)diLep_Ch = DiLepCh::ElElOS;
        }
        diLep    = *leps.at(0) + *leps.at(1);
        diLep_pt = diLep.Pt();
        diLep_eta = diLep.Eta();
        diLep_m  = diLep.M();
        MT2 = AnalyzerCore::MT2((TLorentzVector)(*leps.at(0)),(TLorentzVector)(*leps.at(1)), MET_vector, 0);
      }
    }
  }
  MET = MET_vector.E();
  //TODO: projectedMET
  nPV =evt->nPV();
  //TODO: MT
  // dilepton condition


  newtree->Fill();

  return;

}


void Skim_K1::executeEventFromParameter(AnalyzerParameter param){

}

Skim_K1::Skim_K1(){

}

Skim_K1::~Skim_K1(){

}

void Skim_K1::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_K1::initializeAnalyzer
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

