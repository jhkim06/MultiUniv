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
  if(HasFlag("L")){

        // electron
        newtree->Branch("ElrecoSF",    &ElrecoSF,   "ElrecoSF/D");
        newtree->Branch("ElrecoSF_Up", &ElrecoSF_Up,"ElrecoSF_Up/D");
        newtree->Branch("ElrecoSF_Dn", &ElrecoSF_Dn,"ElrecoSF_Dn/D");

        newtree->Branch("ElIdSF",    &ElIdSF,   "ElIdSF/D");
        newtree->Branch("ElIdSF_Up", &ElIdSF_Up,"ElIdSF_Up/D");
        newtree->Branch("ElIdSF_Dn", &ElIdSF_Dn,"ElIdSF_Dn/D");

        // muon
        newtree->Branch("MuIdSF",    &MuIdSF,   "MuIdSF/D");
        newtree->Branch("MuIdSF_Up", &MuIdSF_Up,"MuIdSF_Up/D");
        newtree->Branch("MuIdSF_Dn", &MuIdSF_Dn,"MuIdSF_Dn/D");

        newtree->Branch("MuIsoSF",    &MuIsoSF,   "MuIsoSF/D");
        newtree->Branch("MuIsoSF_Up", &MuIsoSF_Up,"MuIsoSF_Up/D");
        newtree->Branch("MuIsoSF_Dn", &MuIsoSF_Dn,"MuIsoSF_Dn/D");

  }
  if(HasFlag("LL")){

        // electron
  	newtree->Branch("DiElrecoSF",    &DiElrecoSF,   "DiElrecoSF/D");
  	newtree->Branch("DiElrecoSF_Up", &DiElrecoSF_Up,"DiElrecoSF_Up/D");
  	newtree->Branch("DiElrecoSF_Dn", &DiElrecoSF_Dn,"DiElrecoSF_Dn/D");

  	newtree->Branch("DiElIdSF",    &DiElIdSF,   "DiElIdSF/D");
  	newtree->Branch("DiElIdSF_Up", &DiElIdSF_Up,"DiElIdSF_Up/D");
  	newtree->Branch("DiElIdSF_Dn", &DiElIdSF_Dn,"DiElIdSF_Dn/D");

        // muon
        newtree->Branch("DiMuIdSF",    &DiMuIdSF,   "DiMuIdSF/D");
        newtree->Branch("DiMuIdSF_Up", &DiMuIdSF_Up,"DiMuIdSF_Up/D");
        newtree->Branch("DiMuIdSF_Dn", &DiMuIdSF_Dn,"DiMuIdSF_Dn/D");

        newtree->Branch("DiMuIsoSF",    &DiMuIsoSF,   "DiMuIsoSF/D");
        newtree->Branch("DiMuIsoSF_Up", &DiMuIsoSF_Up,"DiMuIsoSF_Up/D");
        newtree->Branch("DiMuIsoSF_Dn", &DiMuIsoSF_Dn,"DiMuIsoSF_Dn/D");

  }

}

void Module_Efficiency::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  evt = new Event;
  *evt = GetEvent();

  if(HasFlag("L")){
     newtree->SetBranchAddress("ElrecoSF",   &ElrecoSF);
     newtree->SetBranchAddress("ElrecoSF_Up",&ElrecoSF_Up);
     newtree->SetBranchAddress("ElrecoSF_Dn",&ElrecoSF_Dn);

     newtree->SetBranchAddress("ElIdSF",   &ElIdSF);
     newtree->SetBranchAddress("ElIdSF_Up",&ElIdSF_Up);
     newtree->SetBranchAddress("ElIdSF_Dn",&ElIdSF_Dn);

     newtree->SetBranchAddress("MuIdSF",   &MuIdSF);
     newtree->SetBranchAddress("MuIdSF_Up",&MuIdSF_Up);
     newtree->SetBranchAddress("MuIdSF_Dn",&MuIdSF_Dn);

     newtree->SetBranchAddress("MuIsoSF",   &MuIsoSF);
     newtree->SetBranchAddress("MuIsoSF_Up",&MuIsoSF_Up);
     newtree->SetBranchAddress("MuIsoSF_Dn",&MuIsoSF_Dn);

  }

  if(HasFlag("LL")){
     newtree->SetBranchAddress("DiElrecoSF",   &DiElrecoSF);
     newtree->SetBranchAddress("DiElrecoSF_Up",&DiElrecoSF_Up);
     newtree->SetBranchAddress("DiElrecoSF_Dn",&DiElrecoSF_Dn);

     newtree->SetBranchAddress("DiElIdSF",   &DiElIdSF);
     newtree->SetBranchAddress("DiElIdSF_Up",&DiElIdSF_Up);
     newtree->SetBranchAddress("DiElIdSF_Dn",&DiElIdSF_Dn);

     newtree->SetBranchAddress("DiMuIdSF",   &DiMuIdSF);
     newtree->SetBranchAddress("DiMuIdSF_Up",&DiMuIdSF_Up);
     newtree->SetBranchAddress("DiMuIdSF_Dn",&DiMuIdSF_Dn);

     newtree->SetBranchAddress("DiMuIsoSF",   &DiMuIsoSF);
     newtree->SetBranchAddress("DiMuIsoSF_Up",&DiMuIsoSF_Up);
     newtree->SetBranchAddress("DiMuIsoSF_Dn",&DiMuIsoSF_Dn);

  }

  bool isSaveSFs = false;
  LeptonID_SF  = NULL;
  LeptonISO_SF = NULL;
  LeptonReco_SF= NULL;

  if( HasFlag("L") ){ // save dilepton SFs for ISR analysis

        muons=GetMuons("POGTightWithTightIso",7.,2.4);
        electrons=GetElectrons("passTightID",9.,2.5);

        if(muons.size() > 0){
           isSaveSFs = true;
           leps=MakeLeptonPointerVector(muons);
           LeptonID_SF =&MCCorrection::MuonID_SF;
           LeptonISO_SF=&MCCorrection::MuonISO_SF;

           LeptonID_key= "NUM_TightID_DEN_genTracks";
           LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";

           trgSF_key0="Lead17_POGTight";
           trgSF_key1="Tail8_POGTight";
        }
        if(electrons.size() > 0){
           isSaveSFs = true;
           leps=MakeLeptonPointerVector(electrons);
           LeptonID_SF  = &MCCorrection::ElectronID_SF;
           LeptonReco_SF= &MCCorrection::ElectronReco_SF;

           LeptonID_key= "passTightID";
           trgSF_key0="LeadEle23_TightID";
           trgSF_key1="TailEle12_TightID";
        }
  }
  else if( HasFlag("LL") ){ // save dilepton SFs for ISR analysis

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

  ElrecoSF    = 1;
  ElrecoSF_Up = 1;
  ElrecoSF_Dn = 1;

  ElIdSF    = 1;
  ElIdSF_Up = 1;
  ElIdSF_Dn = 1;

  MuIdSF    = 1;
  MuIdSF_Up = 1;
  MuIdSF_Dn = 1;

  MuIsoSF =1;
  MuIsoSF_Up =1;
  MuIsoSF_Dn =1;


  DiElrecoSF    = 1;
  DiElrecoSF_Up = 1;
  DiElrecoSF_Dn = 1;

  DiElIdSF    = 1;
  DiElIdSF_Up = 1;
  DiElIdSF_Dn = 1;

  DiMuIdSF    = 1;
  DiMuIdSF_Up = 1;
  DiMuIdSF_Dn = 1;

  DiMuIsoSF =1;
  DiMuIsoSF_Up =1;
  DiMuIsoSF_Dn =1;


  if(isSaveSFs){

     int nLep = 0;
     if( HasFlag("LLL") ) nLep = 3;

     if(!IsDATA){

        if( HasFlag("L") ){
           nLep = 1;
           for(int i(0); i < nLep; i++){ // two lepton only, pt eta the same to TnP
             if(leps[i]->LeptonFlavour()==Lepton::MUON){
                Aod_pt[i]=((Muon*)leps.at(i))->MiniAODPt();
                Aod_eta[i]=leps.at(i)->Eta();

                MuIdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],0):1.;
                MuIdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],1):1.;
                MuIdSF_Dn   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],-1):1.;

                MuIsoSF  *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],0):1.;
                MuIsoSF_Up       *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],1):1.;
                MuIsoSF_Dn       *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],-1):1.;
             }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
                      Aod_pt[i]=leps.at(i)->Pt();
                      Aod_eta[i]=((Electron*)leps.at(i))->scEta();
                      // TODO do we need this gap veto? it is already in Electron.h for id pass ftn
                      //if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
                      ElrecoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  0) : 1.; 
                      ElrecoSF_Up *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  1) : 1.; 
                      ElrecoSF_Dn *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i], -1) : 1.; 

                      ElIdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],0):1.;
                      ElIdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],1):1.;
                      ElIdSF_Dn   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],-1):1.;
             }
           }
        }

        if( HasFlag("LL") ){
           nLep = 2;
           for(int i(0); i < nLep; i++){ // two lepton only, pt eta the same to TnP
             if(leps[i]->LeptonFlavour()==Lepton::MUON){
                Aod_pt[i]=((Muon*)leps.at(i))->MiniAODPt();
                Aod_eta[i]=leps.at(i)->Eta();

                DiMuIdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],0):1.;
                DiMuIdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],1):1.;
                DiMuIdSF_Dn   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],-1):1.;

                DiMuIsoSF  *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],0):1.;
                DiMuIsoSF_Up       *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],1):1.;
                DiMuIsoSF_Dn       *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key,Aod_eta[i],Aod_pt[i],-1):1.;
             }else if(leps[i]->LeptonFlavour()==Lepton::ELECTRON){
                      Aod_pt[i]=leps.at(i)->Pt();
                      Aod_eta[i]=((Electron*)leps.at(i))->scEta();
                      // TODO do we need this gap veto? it is already in Electron.h for id pass ftn
                      //if(fabs(Aod_eta[i])>1.4442&&fabs(Aod_eta[i])<1.566) return; // two lepton only
                      DiElrecoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  0) : 1.; 
                      DiElrecoSF_Up *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i],  1) : 1.; 
                      DiElrecoSF_Dn *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta[i], Aod_pt[i], -1) : 1.; 

                      DiElIdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],0):1.;
                      DiElIdSF_Up   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],1):1.;
                      DiElIdSF_Dn   *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key,Aod_eta[i],Aod_pt[i],-1):1.;
             }
           }
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

