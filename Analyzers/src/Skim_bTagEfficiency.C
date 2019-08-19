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

  ptBin["pt_20to40"] = new TFormula("pt_20to40","x[0]>=20&&x[0]<40");
  ptBin["pt_40to60"] = new TFormula("pt_40to60","x[0]>=40&&x[0]<60");
  ptBin["pt_60to80"] = new TFormula("pt_60to80","x[0]>=60&&x[0]<80");
  ptBin["pt_80to100"] = new TFormula("pt_80to100","x[0]>=80&&x[0]<100");
  ptBin["pt_100to120"] = new TFormula("pt_100to120","x[0]>=100&&x[0]<120");
  ptBin["pt_120to3000"] = new TFormula("pt_120to3000","x[0]>=120&&x[0]<3000");

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

  std::vector<Jet> jets = GetAllJets();
  

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



