#include "Skim_Jets.h"

void Skim_Jets::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //=================================
  // Skim Types
  //=================================
  if( HasFlag("JJJJ")){
    cout<<"[Skim_Jets::initializeAnalyzer] 4 jet Skim"<<endl;
  }
  else if(HasFlag("DeepCSVMBB")){
    cout<<"[Skim_Jets::initializeAnalyzer] 2 b Skim"<<endl;
  }
  else if(HasFlag("prune")){
    cout<<"[Skim_Jets::initializeAnalyzer] prune Skim, remove fatjet, photon"<<endl;
  }
  else{
    cout <<"[Skim_Jets::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  if(HasFlag("prune")){
    newtree->SetBranchStatus("fatjet*",0);
    newtree->SetBranchStatus("photon*",0);
  }
  if(HasFlag("DeepCSVMBB")){
    // setup btagger
    std::vector<Jet::Tagger> taggers = {Jet::DeepCSV};
    std::vector<Jet::WP> wps ={Jet::Medium};
    SetupBTagger(taggers, wps, true, true);
  }

}

void Skim_Jets::executeEvent(){

  
  vector<Jet> this_AllJets = GetAllJets();

  if( HasFlag("JJJJ")){
    if (this_AllJets.size() < 4) return;
    FillHist("CutFlow",3,1,30,0,30);
  }
  else if(HasFlag("DeepCSVMBB")){
    int n_bjet_deepcsv_m_noSF=0;

    for(unsigned int ij = 0 ; ij < this_AllJets.size(); ij++){
      if(IsBTagged(this_AllJets.at(ij), Jet::DeepCSV, Jet::Medium,false,0)){
        n_bjet_deepcsv_m_noSF++; // method for getting btag with no SF applied to MC
      }
    }
    //require more than 2b tagged jets
    if(n_bjet_deepcsv_m_noSF < 2) return;
    FillHist("CutFlow",4,1,30,0,30);
  }
  else{
    cout <<"[Skim_Jets::executeEvent] Not ready for this Flags ";
    for(unsigned int i=0; i<Userflags.size(); i++){
      cout <<"  "<< Userflags.at(i);
    }
    cout<<endl;
    exit(EXIT_FAILURE);
  }
  newtree->Fill();

  return;

}


void Skim_Jets::executeEventFromParameter(AnalyzerParameter param){

}

Skim_Jets::Skim_Jets(){

}

Skim_Jets::~Skim_Jets(){

}

void Skim_Jets::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_Jets::initializeAnalyzer
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

