#include "Skim_Leptons.h"

void Skim_Leptons::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //=================================
  // Skim Types
  //=================================
  if( HasFlag("L")){
    cout<<"[Skim_Leptons::initializeAnalyzer] Single Lepton Skim"<<endl;}
  else if(HasFlag("LL")){
    cout<<"[Skim_Leptons::initializeAnalyzer] Di-Lepton Skim"<<endl;}
  else if(HasFlag("LLL")){
    cout<<"[Skim_Leptons::initializeAnalyzer] Three-Lepton Skim"<<endl;}
  else{
    cout <<"[Skim_Leptons::executeEvent] Not ready for this Flags ";
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



}

void Skim_Leptons::executeEvent(){

  muons.clear();
  electrons.clear();


  if(Is_baseW == false){
    newtree->SetBranchAddress("baseW",&baseW);
  }


  FillHist("CutFlow",0,1,30,0,30);

  // Filters ====================
  if( HasFlag("MetFt"))if(!PassMETFilter()) return;
  FillHist("CutFlow",1,1,30,0,30);

  muons=GetMuons("POGLoose",7.,2.4);
  TString ElectronID = HasFlag("L") ? "passLooseID_noIso" : "passLooseID";
  electrons=GetElectrons(ElectronID,9.,2.5);
  //std::sort(muons.begin(),muons.end(),PtComparing); //PtComaring @ AnalyzerCore.h

  // dilepton condition

  if( HasFlag("L")){
    if (muons.size() + electrons.size() < 1) return;
    FillHist("CutFlow",2,1,30,0,30);
  }
  else if(HasFlag("LL")){
    if (muons.size() + electrons.size() < 2) return;
    FillHist("CutFlow",3,1,30,0,30);
  }
  else if(HasFlag("LLL")){
    if (muons.size() + electrons.size() < 3) return;
    FillHist("CutFlow",4,1,30,0,30);
  }
  else{
    cout <<"[Skim_Leptons::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }


  evt = new Event;
  *evt = GetEvent();

  if(Is_baseW == false){
    if(IsDATA){
      baseW = 1;
    }else{
      baseW = weight_norm_1invpb*evt->MCweight()*evt->GetTriggerLumi("Full");
    }
  }


  newtree->Fill();

  return;


}


void Skim_Leptons::executeEventFromParameter(AnalyzerParameter param){

}

Skim_Leptons::Skim_Leptons(){

}

Skim_Leptons::~Skim_Leptons(){

}

void Skim_Leptons::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_Leptons::initializeAnalyzer
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

