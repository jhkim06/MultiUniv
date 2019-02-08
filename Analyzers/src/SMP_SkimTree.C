#include "SMP_SkimTree.h"

void SMP_SkimTree::initializeAnalyzer(){

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

  Event ev;
  ev.SetTrigger(*HLT_TriggerName);

  if(skim_DoubleLepTrg)if( ev.PassTrigger(doubleTrgs) ){
    newtree->Fill();
  }

}

void SMP_SkimTree::executeEventFromParameter(AnalyzerParameter param){

}

SMP_SkimTree::SMP_SkimTree(){

}

SMP_SkimTree::~SMP_SkimTree(){

}

void SMP_SkimTree::WriteHist(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree->Write();
  outfile->cd();

}


