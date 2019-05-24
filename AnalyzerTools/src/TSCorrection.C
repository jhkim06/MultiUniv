#include "TSCorrection.h"

TSCorrection::TSCorrection(){

}

TSCorrection::~TSCorrection(){

  for(std::map<TString, TFormula*>::iterator it=MapFittedErrorFormula.begin(); it!=MapFittedErrorFormula.end(); it++){
    delete it->second;
  }
  for(std::map<TString, TFormula*>::iterator it=MapFittedMeanFormula.begin(); it!=MapFittedMeanFormula.end(); it++){
    delete it->second;
  }
  for(std::map<TString, TFormula*>::iterator it=MapFittedResponseFormula.begin(); it!=MapFittedResponseFormula.end(); it++){
    delete it->second;
  }
}

void TSCorrection::ReadFittedError(TString fileName){

  TString datapath = getenv("DATA_DIR");
  datapath = datapath+"/"+TString::Itoa(DataYear,10)+"/TSCorrection/";
  std::ifstream reader(datapath + fileName);

  TString key, formula;
  while(reader >> key >> formula){
    MapFittedErrorFormula[key] = new TFormula(key,formula);
  }

}

void TSCorrection::ReadFittedMean(TString fileName){


  TString datapath = getenv("DATA_DIR");
  datapath = datapath+"/"+TString::Itoa(DataYear,10)+"/TSCorrection/";
  std::ifstream reader(datapath + fileName);

  TString key, formula;
  while(reader >> key >> formula){
    MapFittedMeanFormula[key] = new TFormula(key,formula);
  }
}

void TSCorrection::ReadFittedResponse(TString fileName){

  TString datapath = getenv("DATA_DIR");
  datapath = datapath+"/"+TString::Itoa(DataYear,10)+"/TSCorrection/";
  std::ifstream reader(datapath + fileName);

  TString key, formula;
  while(reader >> key >> formula){
    MapFittedResponseFormula[key] = new TFormula(key,formula);
  }
}

void TSCorrection::SetDataYear(int i){
  DataYear = i;
}

double TSCorrection::GetFittedError(TString key, double x){
  return MapFittedErrorFormula[key]->Eval(x);
}

double TSCorrection::GetFittedMean(TString key, double x){
  return MapFittedMeanFormula[key]->Eval(x);
}

double TSCorrection::GetFittedResponse(TString key, double x){
  return MapFittedResponseFormula[key]->Eval(x);
}

bool TSCorrection::PassResponseCut(TString key, double x, double response, double n_sigma){

  double mean = this->GetFittedMean(key, x);
  double sigma = this->GetFittedError(key, x);
  double max = mean + n_sigma*sigma;
  double min = mean - n_sigma*sigma;

  return (response > min && response < max);
}

