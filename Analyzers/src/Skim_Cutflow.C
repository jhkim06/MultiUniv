#include "Skim_Cutflow.h"

void Skim_Cutflow::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //=================================
  // Skim Types
  //=================================
  if(DataYear==2016){
    SingleMuTrgs = {
      "HLT_IsoMu24_v",
      "HLT_IsoTkMu24_v"
    };
    trgSFkeyMu = "IsoMu24";
    TriggerSafePtCutMu=26.;
    SingleElTrgs = {
      "HLT_Ele27_WPTight_Gsf_v"
    };
    TriggerSafePtCutEl=30.;
  }
  else if(DataYear==2017){
    SingleMuTrgs = {
      "HLT_IsoMu27_v"
    };
    trgSFkeyMu = "IsoMu27";
    TriggerSafePtCutMu=30.;
    SingleElTrgs = {
      "HLT_Ele35_WPTight_Gsf_v"
    };
    TriggerSafePtCutEl=37.;
  }
  else if(DataYear==2018){
    SingleMuTrgs = {
      "HLT_IsoMu24_v"
    };
    trgSFkeyMu = "IsoMu24";
    TriggerSafePtCutMu=26.;
    SingleElTrgs = {
      "HLT_Ele32_WPTight_Gsf_v"
    };
    TriggerSafePtCutEl=35.;
  }
  else{
    cout<<"[Skim_TTSemiLep::executeEvent] ERROR, this year "<<DataYear<<" is not prepared sorry, exiting..."<<endl;
    exit(EXIT_FAILURE);
  }

  // setup btagger
  std::vector<Jet::Tagger> taggers = {Jet::DeepCSV};
  std::vector<Jet::WP> wps ={Jet::Medium};

  SetupBTagger(taggers, wps, true, DataYear==2017?true:false);

}

void Skim_Cutflow::executeEvent(){

  evt = new Event;
  *evt = GetEvent();

  Flow<> flow = {
	  true,
	  false,false,false,false,
	  0,
	  vectorI(),
	  vectorD(),
	  vectorM(), vectorE(), 
	  vectorJ(),
	  this
                };
  FlowMonad<> flowM;
  
  // top-pt reweight is not apply cause it shoudln't cange normalization
  // PUreweight is not applied yet
  flowM.pure(std::move(flow))
    >> &Skim_Cutflow::NoCut
    >> &Skim_Cutflow::MetFt
    >> &Skim_Cutflow::LooseSingleLepton
    >> &Skim_Cutflow::TightSingleLepton
    >> &Skim_Cutflow::Trigger
    >> &Skim_Cutflow::FourJets
    >> &Skim_Cutflow::OneBTags
    >> &Skim_Cutflow::TwoBTags
    >> &Skim_Cutflow::ThreeBTags
    |  &Skim_Cutflow::FillCutFlow;

  return;

}


void Skim_Cutflow::executeEventFromParameter(AnalyzerParameter param){

}

Skim_Cutflow::Skim_Cutflow(){

}

Skim_Cutflow::~Skim_Cutflow(){

}


FlowMonad<>& Skim_Cutflow::NoCut(FlowMonad<>& flowM){
  double addWeight = IsDATA ? 1. : weight_norm_1invpb*evt->MCweight()*evt->GetTriggerLumi("Full");
  flowM.value.updates(true,addWeight,Flow<>::Channel::SingleLep);
  return flowM;
}


FlowMonad<>& Skim_Cutflow::MetFt(FlowMonad<>& flowM){
  bool isPass = PassMETFilter();
  flowM.value.updates(isPass,1.,Flow<>::Channel::SingleLep);
  return flowM;
}


FlowMonad<>& Skim_Cutflow::LooseSingleLepton(FlowMonad<>& flowM){
  flowM.value.muons = GetMuons("POGLooseWithLooseIso",15.,2.4);
  flowM.value.electrons = GetElectrons("passVetoID",15.,2.5);
  auto value = &(flowM.value);
  vectorM* mu = &(value->muons);
  vectorE* el = &(value->electrons);
  value->isMu = mu->size() == 1;
  value->isEl = el->size() == 1;
  bool isPass = value->isMu != value->isEl; // != behaves as XOR. pass if one lepton.
  double addWeight =1.;
  auto channel = !isPass ? Flow<>::Channel::NONE :
	           value->isMu ? 
		     Flow<>::Channel::SingleMu :
	             value->isEl ? 
		       Flow<>::Channel::SingleEl :
		       Flow<>::Channel::NONE;

  value->updates(isPass,addWeight,channel);
  return flowM;
}


FlowMonad<>& Skim_Cutflow::TightSingleLepton(FlowMonad<>& flowM){

  auto value = &(flowM.value);
  vectorM* mu = &(value->muons);
  vectorE* el = &(value->electrons);
  *mu = SelectMuons(*mu,"POGTightWithTightIso",TriggerSafePtCutMu,2.4);
  *el = SelectElectrons(*el,"passTightID",TriggerSafePtCutEl,2.5);
  value->isTightMu = mu->size() == 1;
  value->isTightEl = el->size() == 1;
  bool isPass = value->isTightMu != value->isTightEl; // != behaves as XOR. pass if one lepton.
  double addWeight;
  auto channel = Flow<>::Channel::NONE;

  if(value->isTightMu){
    channel = Flow<>::Channel::SingleMu;
  }
  else if(value->isTightEl){
    channel = Flow<>::Channel::SingleEl;
  }
  // apply SFs
  if(IsDATA){
    addWeight = 1.;
  }
  else if(isPass){

    double (MCCorrection::*LeptonID_SF)(TString,double,double,int)=NULL;
    double (MCCorrection::*LeptonISO_SF)(TString,double,double,int)=NULL;
    double (MCCorrection::*LeptonReco_SF)(double,double,int)=NULL;

    TString LeptonID_key="", LeptonISO_key="";
    double recoSF=1.0, IdSF=1.0, IsoSF=1.0;
    double Aod_eta=-999, Aod_pt=0;
    if(value->isTightMu){
      Aod_pt = mu->at(0).MiniAODPt();
      Aod_eta = mu->at(0).Eta();
      LeptonID_SF =&MCCorrection::MuonID_SF;
      LeptonISO_SF=&MCCorrection::MuonISO_SF;
      // key for private or official SF
      LeptonID_key="NUM_TightID_DEN_genTracks";
      LeptonISO_key="NUM_TightRelIso_DEN_TightIDandIPCut";
    }
    else if(value->isTightEl){
      Aod_pt = el->at(0).Pt();
      Aod_eta = el->at(0).scEta();
      LeptonID_SF  = &MCCorrection::ElectronID_SF;
      LeptonReco_SF= &MCCorrection::ElectronReco_SF;
      // key for private or official SF
      LeptonID_key    = "passTightID";
    }
    // get SFs
    recoSF    *= LeptonReco_SF?(mcCorr->*LeptonReco_SF)(Aod_eta, Aod_pt,  0) : 1.;
    IdSF      *= LeptonID_SF?(mcCorr->*LeptonID_SF)(LeptonID_key, Aod_eta, Aod_pt,  0) : 1.;
    IsoSF     *= LeptonISO_SF?(mcCorr->*LeptonISO_SF)(LeptonISO_key, Aod_eta, Aod_pt,  0) : 1.;
    //
    addWeight = recoSF*IdSF*IsoSF;
  }
  else{
    addWeight=0.;
  }
  value->updates(isPass,addWeight,channel);
  return flowM;
}

FlowMonad<>& Skim_Cutflow::Trigger(FlowMonad<>& flowM){

  auto value = &(flowM.value);
  bool isPass = false;
  double addWeight = 1.;
  auto channel = Flow<>::Channel::NONE;
  if(value->isTightMu==true){
    isPass = evt->PassTrigger(SingleMuTrgs);
    channel = Flow<>::Channel::SingleMu;
  }
  else if(value->isTightEl==true){
    isPass = evt->PassTrigger(SingleElTrgs);
    channel = Flow<>::Channel::SingleEl;
  }
  else{
    std::cout << "[Skim_Cutflow::Trigger]" << " no single lepton exists" << std::endl;
    exit(EXIT_FAILURE);
  }
  // apply SFs
  if(IsDATA){
    //pass
  }
  else if(isPass){
    addWeight *= value->isTightMu ? mcCorr->MuonTrigger_SF("POGTight", trgSFkeyMu, value->muons, 0) : 1.;
  }
  value->updates(isPass,addWeight,channel);
  return flowM;
}


FlowMonad<>& Skim_Cutflow::FourJets(FlowMonad<>& flowM){
  flowM.value.jets = GetJets("tight",30.,2.4);
  auto value = &(flowM.value);
  value->jets = JetsVetoLeptonInside(value->jets, value->electrons, value->muons);
  auto channel = value->isTightMu ? Flow<>::Channel::SingleMu : Flow<>::Channel::SingleEl;
  if(value->jets.size()>=4){
    value->updates(true,1.,channel);
  }
  else{
    value->updates(false,0.,Flow<>::Channel::NONE);
  }
  return flowM;
}

FlowMonad<>& Skim_Cutflow::OneBTags(FlowMonad<>& flowM){

  auto value = &(flowM.value);
  auto channel = value->isTightMu ? Flow<>::Channel::SingleMu : Flow<>::Channel::SingleEl;
  int nbtags=0;
  for(auto &jet : value->jets){
    if(IsBTagged(jet, Jet::DeepCSV, Jet::Medium, false, 0))
    nbtags++;
  }
  value->nbtags = nbtags;
  if(value->nbtags>=1){
    float BTagSF = 1., MisTagSF = 0.;
    if(!IsDATA){
      BtaggingSFEvtbyEvt(value->jets, Jet::DeepCSV, Jet::Medium, 0, BTagSF, MisTagSF); //@AnalyzerCore
    }
    value->updates(true,(double)BTagSF,channel);
  }
  else{
    value->updates(false,0.,Flow<>::Channel::NONE);
  }
  return flowM;
}

FlowMonad<>& Skim_Cutflow::TwoBTags(FlowMonad<>& flowM){

  auto value = &(flowM.value);
  auto channel = value->isTightMu ? Flow<>::Channel::SingleMu : Flow<>::Channel::SingleEl;
  bool isPass =value->nbtags>=2;
  value->updates(isPass,isPass?1.:0.,isPass?channel : Flow<>::Channel::NONE);
  return flowM;

}

FlowMonad<>& Skim_Cutflow::ThreeBTags(FlowMonad<>& flowM){

  auto value = &(flowM.value);
  auto channel = value->isTightMu ? Flow<>::Channel::SingleMu : Flow<>::Channel::SingleEl;
  bool isPass =value->nbtags>=3;
  value->updates(isPass,isPass?1.:0.,isPass?channel : Flow<>::Channel::NONE);
  return flowM;

}

FlowMonad<>& Skim_Cutflow::FillCutFlow(FlowMonad<>& flowM){
  auto value = &(flowM.value);
  vectorS histNamesAll = {"CutFlow", "CutFlow_Mu", "CutFlow_El"};
  vectorS histNamesMu = {"CutFlow", "CutFlow_Mu"};
  vectorS histNamesEl = {"CutFlow", "CutFlow_El"};

  int nbins = value->weights.size();
  for(int i=0; i<nbins; i++){

    double content = value->weights.at(i);
    auto channel = value->channels.at(i);
    vectorS *outHistNames;
    if(channel==Flow<>::Channel::NONE){
      outHistNames = NULL;
      break;
    }
    else if(channel==Flow<>::Channel::SingleLep){
      outHistNames = &histNamesAll;
    }
    else if(channel==Flow<>::Channel::SingleMu){
      outHistNames = &histNamesMu;
    }
    else if(channel==Flow<>::Channel::SingleEl){
      outHistNames = &histNamesEl;
    }

    for(auto &outHistName : *outHistNames){
      FillHist(outHistName,i,content,nbins,0,nbins);
    }

  }
  value->clear();
  return flowM;
}

/// methods of FlowMonad

template<typename T>
FlowMonad<T>& FlowMonad<T>::operator>>=(FlowMonad<T> (T::*functor)(Flow<T>&)){
  if(this->value.isFlow){
    return (value.class_pointer->*functor)(this->value);
  }
  else{
    this.value->updates(false, 0.,0.);
    return (*this);
  }	  
}

template<typename T>
FlowMonad<T>& FlowMonad<T>::operator>>(FlowMonad<T>& (T::*functor)(FlowMonad<T>&)){
  if(this->value.isFlow){
    return (value.class_pointer->*functor)(*this);
  }
  else{
    this->value.updates(false, 0., Flow<>::Channel::NONE);
    return (*this);
  }	  
}

template<typename T>
FlowMonad<T>& FlowMonad<T>::operator|(FlowMonad<T>& (T::*functor)(FlowMonad<T>&)){
  return (value.class_pointer->*functor)(*this);
}

template<typename T>
FlowMonad<T>& FlowMonad<T>::pure(bool isFlow_, vectorM muons_, vectorE electrons_, vectorJ jets_, Skim_Cutflow *class_pointer_){
  value.clear();
  value.isFlow = isFlow_;
  value.muons = muons_;
  value.electrons = electrons_;
  value.jets = jets_;
  value.class_pointer = class_pointer_;
  return *this;
}

template<typename T>
void Flow<T>::clear(){
  isFlow = false;
  channels.clear();
  weights.clear();
  muons.clear();
  electrons.clear();
  jets.clear();
  class_pointer = NULL;
}

template<typename T>
void Flow<T>::updates(bool isPass_, double addWeight_, Flow<T>::Channel channel){
  // updates weights
  if(isPass_){ //if pass cut
    double weight = 1.;
    if(weights.size()>0){
      weight = weights.back(); // get last element.
    }
    weight *= addWeight_; //additional weight
    weights.push_back(weight);
    channels.push_back(channel);
    isFlow = true;
  }
  else{ // if not pass cut
    isFlow = false;
    weights.push_back(0.);
    channels.push_back(channel);
  }

}
