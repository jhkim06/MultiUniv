#include "Skim_K1.h"

void Skim_K1::initializeAnalyzer(){

  Is_singleLep = false;
  Is_diLep = false;

  //initializeAnalyzerTools();
  //=================================
  // Skim Types
  //=================================
  if( HasFlag("L1K1")){
    Is_singleLep = true;
    cout<<"[Skim_K1::initializeAnalyzer] L1K1, add Kinematic variables for single lepton"<<endl;
  }
  else if(HasFlag("L2K1")){
    Is_diLep = true;
    cout<<"[Skim_K1::initializeAnalyzer] L2K1, add Kinematic variables for di-lepton"<<endl;
  }
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

  //=================================
  // New Branch
  //=================================
  TBranch* b_baseW =(TBranch*) newtree->GetListOfBranches()->FindObject("baseW");
  Is_baseW = false;
  if(b_baseW) {Is_baseW = true;}
  if(Is_baseW == false){
    newtree->Branch("baseW", &baseW,"baseW/D");
  }

  if(Is_singleLep){
    newtree->Branch("MT2", &MT2,"MT2/D");
    newtree->Branch("MET", &MET,"MET/D");
    newtree->Branch("nPV", &nPV,"nPV/D");
    //newtree->Branch("projectedMET", &projectedMET,"projectedMET/D");
    //newtree->Branch("MT", &MT,"MT/D");
  }
  if(Is_diLep){
    newtree->Branch("diLep_Ch", &diLep_Ch,"diLep_Ch/I");
    newtree->Branch("diLep_passSelectiveQ", &diLep_passSelectiveQ,"diLep_passSelectiveQ/O");
    newtree->Branch("diLep_m", &diLep_m,"diLep_m/D");
    newtree->Branch("diLep_pt", &diLep_pt,"diLep_pt/D");
    newtree->Branch("diLep_eta", &diLep_eta,"diLep_eta/D");
    newtree->Branch("MT2", &MT2,"MT2/D");

    newtree->Branch("diLep_m_woROC", &diLep_m_woROC,"diLep_m_woROC/D");
    newtree->Branch("diLep_pt_woROC", &diLep_pt_woROC,"diLep_pt_woROC/D");
    newtree->Branch("diLep_eta_woROC", &diLep_eta_woROC,"diLep_eta_woROC/D");

    newtree->Branch("diLep_m_updatedROC", &diLep_m_updatedROC,"diLep_m_updatedROC/D");
    newtree->Branch("diLep_pt_updatedROC", &diLep_pt_updatedROC,"diLep_pt_updatedROC/D");
    newtree->Branch("diLep_eta_updatedROC", &diLep_eta_updatedROC,"diLep_eta_updatedROC/D");

    newtree->Branch("diLep_m_updatedROC_zpt", &diLep_m_updatedROC_zpt,"diLep_m_updatedROC_zpt/D");
    newtree->Branch("diLep_pt_updatedROC_zpt", &diLep_pt_updatedROC_zpt,"diLep_pt_updatedROC_zpt/D");
    newtree->Branch("diLep_eta_updatedROC_zpt", &diLep_eta_updatedROC_zpt,"diLep_eta_updatedROC_zpt/D");

    newtree->Branch("diLep_m_updatedROC_ewk", &diLep_m_updatedROC_ewk,"diLep_m_updatedROC_ewk/D");
    newtree->Branch("diLep_pt_updatedROC_ewk", &diLep_pt_updatedROC_ewk,"diLep_pt_updatedROC_ewk/D");
    newtree->Branch("diLep_eta_updatedROC_ewk", &diLep_eta_updatedROC_ewk,"diLep_eta_updatedROC_ewk/D");

    newtree->Branch("diLep_m_updatedROC_dM", &diLep_m_updatedROC_dM,"diLep_m_updatedROC_dM/D");
    newtree->Branch("diLep_pt_updatedROC_dM", &diLep_pt_updatedROC_dM,"diLep_pt_updatedROC_dM/D");
    newtree->Branch("diLep_eta_updatedROC_dM", &diLep_eta_updatedROC_dM,"diLep_eta_updatedROC_dM/D");

  }

}

void Skim_K1::executeEvent(){

  muons.clear();
  muons_woROC.clear();
  muons_updatedROC.clear();
  muons_updatedROC_zpt.clear();
  muons_updatedROC_ewk.clear();
  muons_updatedROC_dM.clear();
  

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

  //=================================
  // Branch Address
  //=================================
  if(Is_baseW == false){
    newtree->SetBranchAddress("baseW",&baseW);
  }
  //------------------------------------------------------------------------
  if(Is_singleLep){
    newtree->SetBranchAddress("MT2", &MT2);
    newtree->SetBranchAddress("MET", &MET);
    newtree->SetBranchAddress("nPV", &nPV);
    //newtree->Branch("projectedMET", &projectedMET);
    //newtree->Branch("MT", &MT);
  }
  //------------------------------------------------------------------------
  if(Is_diLep){
    newtree->SetBranchAddress("diLep_Ch", &diLep_Ch);
    newtree->SetBranchAddress("diLep_passSelectiveQ", &diLep_passSelectiveQ);
    newtree->SetBranchAddress("diLep_m", &diLep_m);
    newtree->SetBranchAddress("diLep_pt", &diLep_pt);
    newtree->SetBranchAddress("diLep_eta", &diLep_eta);
    newtree->SetBranchAddress("MT2", &MT2);
  }

  //=================================
  // Select Object
  //=================================
  muons=                GetMuons("POGLoose",7.,2.4);
  muons_woROC=          GetMuons("POGLoose",7.,2.4, false);
  muons_updatedROC=     GetMuons("POGLoose",7.,2.4, true, true);
  muons_updatedROC_zpt= GetMuons("POGLoose",7.,2.4, true, true, 2, 1);
  muons_updatedROC_ewk= GetMuons("POGLoose",7.,2.4, true, true, 3, 1);
  muons_updatedROC_dM=  GetMuons("POGLoose",7.,2.4, true, true, 4, 1);

  TString ElectronID = HasFlag("L1K1") ? "passVetoID" : "passLooseID";
  electrons=GetElectrons(ElectronID,9.,2.5);


  //=================================
  // variables for single Lepton
  //=================================
  if(Is_singleLep){
    MET = MET_vector.E();
    //TODO: projectedMET
    nPV =evt->nPV();
  }

  //=================================
  // variables for di Lepton
  //=================================
  if(Is_diLep){
    if(muons.size()+electrons.size()==2){
      if(muons.size()==2) leps=MakeLeptonPointerVector(muons);
      else if(electrons.size()==2) leps=MakeLeptonPointerVector(electrons);
      diLep_Ch = DiLepCh::NA;
      diLep_m  = DEFAULT;
      diLep_pt  = DEFAULT;
      diLep_eta  = DEFAULT;

      diLep_m_woROC  = DEFAULT;
      diLep_pt_woROC  = DEFAULT;
      diLep_eta_woROC  = DEFAULT;

      diLep_m_updatedROC  = DEFAULT;
      diLep_pt_updatedROC  = DEFAULT;
      diLep_eta_updatedROC  = DEFAULT;

      diLep_m_updatedROC_zpt  = DEFAULT;
      diLep_pt_updatedROC_zpt  = DEFAULT;
      diLep_eta_updatedROC_zpt  = DEFAULT;

      diLep_m_updatedROC_ewk  = DEFAULT;
      diLep_pt_updatedROC_ewk  = DEFAULT;
      diLep_eta_updatedROC_ewk  = DEFAULT;

      diLep_m_updatedROC_dM  = DEFAULT;
      diLep_pt_updatedROC_dM  = DEFAULT;
      diLep_eta_updatedROC_dM  = DEFAULT;

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
        //MT2 = AnalyzerCore::MT2((TLorentzVector)(*leps.at(0)),(TLorentzVector)(*leps.at(1)), MET_vector, 0); // temporarily commented out since the last argument set as 0 and fall in infite loop  
        MT2 = 1.0;

        //
	if(muons.size()==2){
           leps.clear(); leps.shrink_to_fit();
           leps=MakeLeptonPointerVector(muons_woROC.size()==2?muons_woROC:muons);

           diLep    = *leps.at(0) + *leps.at(1);
           diLep_pt_woROC = diLep.Pt();
           diLep_eta_woROC = diLep.Eta();
           diLep_m_woROC  = diLep.M();

           leps.clear(); leps.shrink_to_fit();
           leps=MakeLeptonPointerVector(muons_updatedROC.size()==2?muons_updatedROC:muons);

           diLep    = *leps.at(0) + *leps.at(1);
           diLep_pt_updatedROC = diLep.Pt();
           diLep_eta_updatedROC = diLep.Eta();
           diLep_m_updatedROC  = diLep.M();

           leps.clear(); leps.shrink_to_fit();
           leps=MakeLeptonPointerVector(muons_updatedROC_zpt.size()==2?muons_updatedROC_zpt:muons);

           diLep    = *leps.at(0) + *leps.at(1);
           diLep_pt_updatedROC_zpt = diLep.Pt();
           diLep_eta_updatedROC_zpt = diLep.Eta();
           diLep_m_updatedROC_zpt  = diLep.M();

           leps.clear(); leps.shrink_to_fit();
           leps=MakeLeptonPointerVector(muons_updatedROC_ewk.size()==2?muons_updatedROC_ewk:muons);

           diLep    = *leps.at(0) + *leps.at(1);
           diLep_pt_updatedROC_ewk = diLep.Pt();
           diLep_eta_updatedROC_ewk = diLep.Eta();
           diLep_m_updatedROC_ewk  = diLep.M();

           leps.clear(); leps.shrink_to_fit();
           leps=MakeLeptonPointerVector(muons_updatedROC_dM.size()==2?muons_updatedROC_dM:muons);

           diLep    = *leps.at(0) + *leps.at(1);
           diLep_pt_updatedROC_dM = diLep.Pt();
           diLep_eta_updatedROC_dM = diLep.Eta();
           diLep_m_updatedROC_dM  = diLep.M();
 	}

      }
    }
  }


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

