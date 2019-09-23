#ifndef Skim_Cutflow_h
#define Skim_Cutflow_h

#include "AnalyzerCore.h"
#include "RootHelper.h"

// forward declaration of class and struct
class Skim_Cutflow;
template<typename T=Skim_Cutflow>
class FlowMonad;
template<typename T=Skim_Cutflow>
struct Flow;

// definde alias of standard type
typedef std::vector<double> vectorD;
typedef std::vector<int> vectorI;
typedef std::vector<Muon> vectorM;
typedef std::vector<Electron> vectorE;
typedef std::vector<Jet> vectorJ;
typedef std::vector<TString> vectorS;


// begin definition of class and struct
class Skim_Cutflow : public AnalyzerCore {

public:
  Skim_Cutflow();
  ~Skim_Cutflow();

  void initializeAnalyzer();
  void executeEventFromParameter(AnalyzerParameter param);
  void executeEvent();
  
  Event* evt;

private:

  vectorS SingleMuTrgs;
  vectorS SingleElTrgs;
  TString trgSFkeyMu;
  TString trgSFkeyEl;
  double TriggerSafePtCutMu;
  double TriggerSafePtCutEl;

  FlowMonad<>& NoCut(FlowMonad<>& flowM);
  FlowMonad<>& MetFt(FlowMonad<>& flowM);
  FlowMonad<>& LooseSingleLepton(FlowMonad<>& flowM);
  FlowMonad<>& TightSingleLepton(FlowMonad<>& flowM);
  FlowMonad<>& Trigger(FlowMonad<>& flowM);
  FlowMonad<>& FourJets(FlowMonad<>& flowM);
  FlowMonad<>& OneBTags(FlowMonad<>& flowM);
  FlowMonad<>& TwoBTags(FlowMonad<>& flowM);
  FlowMonad<>& ThreeBTags(FlowMonad<>& flowM);
  
  FlowMonad<>& FillCutFlow(FlowMonad<>& flowM);

};


template<typename T>
struct Flow {

  enum Channel{
    NONE,
    SingleLep,
    SingleMu,
    SingleEl,
  };

  bool isFlow;
  bool isMu;
  bool isEl;
  bool isTightMu;
  bool isTightEl;
  int nbtags;
  vectorI channels;
  vectorD weights;
  vectorM muons;
  vectorE electrons;
  vectorJ jets;
  T *class_pointer; //use to call class method functor

  void clear();
  void updates(bool isPass_, double addWeight_, Flow<T>::Channel);

};


template<typename T>
class FlowMonad {

// a monadic structure

public:
  FlowMonad(){}
  ~FlowMonad(){}
  FlowMonad<T>& pure(Flow<T> &&value_){ value = value_; return *this; }
  FlowMonad<T>& pure(bool isFlow_, vectorM muons_, vectorE electrons_, vectorJ jets_, Skim_Cutflow *class_pointer_);

  Flow<T> value;

  //(>>=) :: m a -> (a -> m b) -> m b
  FlowMonad<T>& operator>>=(FlowMonad<T> (T::*functor)(Flow<T>&));
  //(>>) :: m a -> (m a -> m b) -> m b
  FlowMonad<T>& operator>>(FlowMonad<T>& (T::*functor)(FlowMonad<T>&));
  //similar as (>>) but ignore value.isFlow, i.e. run functor anyway
  FlowMonad<T>& operator|(FlowMonad<T>& (T::*functor)(FlowMonad<T>&));

};

#endif
