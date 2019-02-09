#include "SMP_SkimTree.h"

void SMP_SkimTree::initializeAnalyzer(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);
  //=================================
  // Skim Types
  skim_DoubleLepTrg = HasFlag("DoubleLepTrg");
  //=================================



  // clear vector residual
  doubleTrgs.clear();


  cout << "[SMP_SkimTree::initializeAnalyzer] Skim List====================== " << endl;
  if(skim_DoubleLepTrg){
    if(DataYear==2016){
      doubleTrgs = {
      };
    }
    else if(DataYear==2017){
      doubleTrgs = {
        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",
        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v"
      };
    }

    cout << "\t"<<"doubleTrgs to skim = " << endl;
    for(unsigned int i=0; i<doubleTrgs.size(); i++){
      cout << "\t" << doubleTrgs.at(i) << endl;
    }
  }

}

void SMP_SkimTree::executeEvent(){

  FillHist("InputEvent",1,1,2,0,2);

  Event ev;
  ev.SetTrigger(*HLT_TriggerName);

  if(skim_DoubleLepTrg)if( ev.PassTrigger(doubleTrgs) ){
    newtree->Fill();
    FillHist("PassEvent",1,1,2,0,2);
  }

}

void SMP_SkimTree::executeEventFromParameter(AnalyzerParameter param){

}

SMP_SkimTree::SMP_SkimTree(){

}

SMP_SkimTree::~SMP_SkimTree(){

}

void SMP_SkimTree::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at SMP_SkimTree::initializeAnalyzer
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


