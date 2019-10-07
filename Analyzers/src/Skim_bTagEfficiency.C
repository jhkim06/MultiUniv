#include "Skim_bTagEfficiency.h"

Skim_bTagEfficiency::Skim_bTagEfficiency(){

}

void Skim_bTagEfficiency::initializeAnalyzer(){

  outfile->cd();
  newtree = fChain->CloneTree(0);
  newtree->SetBranchStatus("*",0);
  //=================================
  // init
  //=================================

  flavour["b"] = new TFormula("b", "abs(x[0])==5");
  flavour["c"] = new TFormula("c", "abs(x[0])==4");
  flavour["l"] = new TFormula("l", "abs(x[0])<4");

  ptBin["pt_20to30"] = new TFormula("pt_20to30","x[0]>=20&&x[0]<30");
  ptBin["pt_30to50"] = new TFormula("pt_30to50","x[0]>=30&&x[0]<50");
  ptBin["pt_50to70"] = new TFormula("pt_50to70","x[0]>=50&&x[0]<70");
  ptBin["pt_70to100"] = new TFormula("pt_70to100","x[0]>=70&&x[0]<100");
  ptBin["pt_100to140"] = new TFormula("pt_100to140","x[0]>=100&&x[0]<140");
  ptBin["pt_140to200"] = new TFormula("pt_140to200","x[0]>=140&&x[0]<200");
  ptBin["pt_200to300"] = new TFormula("pt_200to300","x[0]>=200&&x[0]<300");
  ptBin["pt_300to600"] = new TFormula("pt_300to600","x[0]>=300&&x[0]<600");
  ptBin["pt_600to1000"] = new TFormula("pt_600to1000","x[0]>=600&&x[0]<1000");

  etaBin["eta_0.0to0.6"] = new TFormula("eta_0.0to0.6","x[0]>=0.0&&x[0]<0.6");
  etaBin["eta_0.6to1.2"] = new TFormula("eta_0.6to1.2","x[0]>=0.6&&x[0]<1.2");
  etaBin["eta_1.2to1.8"] = new TFormula("eta_1.2to1.8","x[0]>=1.2&&x[0]<1.8");
  etaBin["eta_1.8to2.4"] = new TFormula("eta_1.8to2.4","x[0]>=1.8&&x[0]<2.4");

  std::vector<Jet::Tagger> taggers = {Jet::DeepCSV};
  std::vector<Jet::WP> wps ={Jet::Medium};

  SetupBTagger(taggers, wps, false, false);

}

Skim_bTagEfficiency::~Skim_bTagEfficiency(){
  for(auto &x : ptBin){
    delete x.second;
  }
  for(auto &x : etaBin){
    delete x.second;
  }
  for(auto &x : flavour){
    delete x.second;
  }
}

void Skim_bTagEfficiency::executeEvent(){

  
  auto jets = GetJets("tight", 20., 2.4);
  auto muons=GetMuons("POGLooseWithLooseIso",15.,2.4);
  auto electrons=GetElectrons("passVetoID",15.,2.5);
  jets = JetsVetoLeptonInside(jets, electrons, muons);
  // NOTE: below jet pT < 40 GeV. pileup contribution is significant
  // but I didn't use any method to reject those.
  // To remove puleup jet, we can require matching with genjet

  for(auto& jet: jets){ 

    TString histName = "";
    for(auto &flav_ : flavour){
    for(auto &pt_ : ptBin){
    for(auto &eta_ : etaBin){
      if(!flav_.second->Eval(jet.hadronFlavour())){
        continue;
      }
      if(!pt_.second->Eval(jet.Pt())){
        continue;
      }
      if(!eta_.second->Eval(fabs(jet.Eta()))){
        continue;
      }
      histName = TString::Format("%s_%s_%s",
		               flav_.first.Data(),
		               pt_.first.Data(),
			       eta_.first.Data()
		              );

      bool isTagged = IsBTagged(jet, Jet::DeepCSV, Jet::Medium, false, 0);
      
      FillHist(histName, isTagged, 1., 2, 0, 2);
    }
    }
    }

  }

}



