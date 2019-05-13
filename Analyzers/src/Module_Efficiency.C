#include "Module_Efficiency.h"

void Module_Efficiency::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //=================================
  // Skim Types
  //=================================
  if( HasFlag("L")){
    cout<<"[Module_Efficiency::initializeAnalyzer] Single Lepton Skim"<<endl;}
  else if(HasFlag("LL")){
    cout<<"[Module_Efficiency::initializeAnalyzer] Di-Lepton Skim"<<endl;}
  else if(HasFlag("LLL")){
    cout<<"[Module_Efficiency::initializeAnalyzer] Three-Lepton Skim"<<endl;}
  else{
    cout <<"[Module_Efficiency::executeEvent] Not ready for this Flags ";
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
  newtree->Branch("recoSF",    &recoSF,   "recoSF/D");
  newtree->Branch("recoSF_Up", &recoSF_Up,"recoSF_Up/D");
  newtree->Branch("recoSF_Dn", &recoSF_Dn,"recoSF_Dn/D");

  newtree->Branch("IdSF",    &IdSF,   "IdSF/D");
  newtree->Branch("IdSF_Up", &IdSF_Up,"IdSF_Up/D");
  newtree->Branch("IdSF_Dn", &IdSF_Dn,"IdSF_Dn/D");

  newtree->Branch("IsoSF",    &IsoSF,   "IsoSF/D");
  newtree->Branch("IsoSF_Up", &IsoSF_Up,"IsoSF_Up/D");
  newtree->Branch("IsoSF_Dn", &IsoSF_Dn,"IsoSF_Dn/D");

}

void Module_Efficiency::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  evt = new Event;
  *evt = GetEvent();

  newtree->SetBranchAddress("recoSF",   &recoSF);
  newtree->SetBranchAddress("recoSF_Up",&recoSF_Up);
  newtree->SetBranchAddress("recoSF_Dn",&recoSF_Dn);

  newtree->SetBranchAddress("IdSF",   &IdSF);
  newtree->SetBranchAddress("IdSF_Up",&IdSF_Up);
  newtree->SetBranchAddress("IdSF_Dn",&IdSF_Dn);

  newtree->SetBranchAddress("IsoSF",   &IsoSF);
  newtree->SetBranchAddress("IsoSF_Up",&IsoSF_Up);
  newtree->SetBranchAddress("IsoSF_Dn",&IsoSF_Dn);

  bool isSaveSFs = false;
  LeptonID_SF  = NULL;
  LeptonISO_SF = NULL;
  LeptonReco_SF= NULL;

  if( HasFlag("LL") ){ // save dilepton SFs for ISR analysis

  	muons=GetMuons("POGTightWithTightIso",7.,2.4);
  	electrons=GetElectrons("passMediumID",9.,2.5);

	if(muons.size() > 1){
	   isSaveSFs = true;
           leps=MakeLeptonPointerVector(muons);
           LeptonID_SF =&MCCorrection::MuonID_SF;
           LeptonISO_SF=&MCCorrection::MuonISO_SF;

           LeptonID_key= "NUM_TightID_DEN_genTracks";	
           LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";
           
           trgSF_key0="Lead17_POGTight";
           trgSF_key1="Tail8_POGTight";
	}
	if(electrons.size() > 1){
	   isSaveSFs = true;
           leps=MakeLeptonPointerVector(electrons);            
    	   LeptonID_SF  = &MCCorrection::ElectronID_SF;
    	   LeptonReco_SF= &MCCorrection::ElectronReco_SF;

           LeptonID_key= "passMediumID";	
           trgSF_key0="LeadEle23_MediumID";
           trgSF_key1="TailEle12_MediumID";
	}
  }
  else{
    cout <<"[Module_Efficiency::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }

  trgSF    = 1;
  trgSF_Up = 1;
  trgSF_Dn = 1;

  recoSF    = 1;
  recoSF_Up = 1;
  recoSF_Dn = 1;

  IdSF    = 1;
  IdSF_Up = 1;
  IdSF_Dn = 1;

  IsoSF =1;
  IsoSF_Up =1;
  IsoSF_Dn =1;

  if(isSaveSFs){

     int nLep = 0;
     if( HasFlag("L") ) nLep = 1;
     if( HasFlag("LL") ) nLep = 2;
     if( HasFlag("LLL") ) nLep = 3;

     if(!IsDATA){

        for(int i(0); i < nLep; i++){ // two lepton only, pt eta the same to TnP
          if(leps[i]->LeptonFlavour()==Lepton::MUON){
           Aod_pt[i]=((Muon*)leps.at(i))->MiniAODPt();
           Aod_eta[i]=leps.at(i)->Eta();
          }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
           Aod_pt[i]=leps.at(i)->Pt();
           Aod_eta[i]=((Electron*)leps.at(i))->scEta();
           // TODO do we need this gap veto? it is already in Electron.h for id pass ftn
           //if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
          }
        }

       for( int i(0); i<nLep ; i++){

         recoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  0) : 1.;
         recoSF_Up *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  1) : 1.;
         recoSF_Dn *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i], -1) : 1.;

         IdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],0):1.;
         IdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],1):1.;
         IdSF_Dn   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],-1):1.;

         IsoSF  *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],0):1.;
         IsoSF_Up       *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],1):1.;
         IsoSF_Dn       *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],-1):1.;

       }
     }
  }// save SFs if there are enough leptons


  //std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h
  // dilepton condition

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

