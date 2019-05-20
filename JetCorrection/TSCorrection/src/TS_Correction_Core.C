#include "TS_Correction_Core.h"

TS_Correction_Core::TS_Correction_Core(){

  response["Pt"] = NULL;
  response["Et"] = NULL;
  response["Eta"] = NULL;
  response["Phi"] = NULL;

  flavour["uds"] = new TFormula("uds","abs(x[0])<4");
  flavour["udsc"] = new TFormula("udsc","abs(x[0])<5");
  flavour["b"] = new TFormula("b","abs(x[0])==5");
  flavour["udscb"] = new TFormula("b","1");

  ptBin["pt_20to40"] = new TFormula("pt_20to40","x[0]>=20&&x[0]<40");
  ptBin["pt_40to50"] = new TFormula("pt_40to50","x[0]>=40&&x[0]<50");
  ptBin["pt_50to60"] = new TFormula("pt_50to60","x[0]>=50&&x[0]<60");
  ptBin["pt_60to70"] = new TFormula("pt_60to70","x[0]>=60&&x[0]<70");
  ptBin["pt_70to80"] = new TFormula("pt_70to80","x[0]>=70&&x[0]<80");
  ptBin["pt_80to90"] = new TFormula("pt_80to90","x[0]>=80&&x[0]<90");
  ptBin["pt_90to100"] = new TFormula("pt_90to100","x[0]>=90&&x[0]<100");
  ptBin["pt_100to120"] = new TFormula("pt_100to120","x[0]>=100&&x[0]<120");
  ptBin["pt_120to150"] = new TFormula("pt_120to150","x[0]>=120&&x[0]<150");
  ptBin["pt_150toINF"] = new TFormula("pt_150toINF","x[0]>=150");

  etaBin["eta_0.174"] = new TFormula("eta_0.174","abs(x[0])<0.174");
  etaBin["eta_0.348"] = new TFormula("eta_0.348","abs(x[0])>0.174&&abs(x[0])<0.348");
  etaBin["eta_0.522"] = new TFormula("eta_0.522","abs(x[0])>0.348&&abs(x[0])<0.522");
  etaBin["eta_0.696"] = new TFormula("eta_0.696","abs(x[0])>0.522&&abs(x[0])<0.696");
  etaBin["eta_0.879"] = new TFormula("eta_0.879","abs(x[0])>0.696&&abs(x[0])<0.879");
  etaBin["eta_1.131"] = new TFormula("eta_1.131","abs(x[0])>0.879&&abs(x[0])<1.131");
  etaBin["eta_1.392"] = new TFormula("eta_1.392","abs(x[0])>1.131&&abs(x[0])<1.392");
  etaBin["eta_1.74"] = new TFormula("eta_1.74","abs(x[0])>1.392&&abs(x[0])<1.74");
  etaBin["eta_2.4"] = new TFormula("eta_2.4","abs(x[0])>1.74&&abs(x[0])<2.4");

  this->SetHistNameVector();

} // end of function


TS_Correction_Core::~TS_Correction_Core(){

  for(map<TString,TFormula*>::iterator it=response.begin(); it!=response.end(); it++){
    delete it->second;
  }
  for(map<TString,TFormula*>::iterator it=flavour.begin(); it!=flavour.end(); it++){
    delete it->second;
  }
  for(map<TString,TFormula*>::iterator it=ptBin.begin(); it!=ptBin.end(); it++){
    delete it->second;
  }
  for(map<TString,TFormula*>::iterator it=etaBin.begin(); it!=etaBin.end(); it++){
    delete it->second;
  }
  for(map<TString,TFormula*>::iterator it=cut.begin(); it!=cut.end(); it++){
    delete it->second;
  }

} // end of function


void TS_Correction_Core::SetHistNameVector(){
  histNameVector.clear();
  for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
  for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
  for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
    // name of response histogram
    TString name = Form("%s_%s_%s_%s",it_res->first.Data(),
                                      it_flav->first.Data(),
                                      it_pt->first.Data(),
                                      it_eta->first.Data()
                       );
    histNameVector.push_back(name);
  }
  }
  }
  }
}


double TS_Correction_Core::GetResponse(TString var, TLorentzVector *jet, TLorentzVector *parton){
  if(var=="Pt"){
    return this->GetResponse_Pt(jet, parton);
  }
  else if(var=="Et"){
    return this->GetResponse_Et(jet, parton);
  }
  else if(var=="Eta"){
    return this->GetResponse_Eta(jet, parton);
  }
  else if(var=="Phi"){
    return this->GetResponse_Phi(jet, parton);
  }
  else{
    cout <<"    >>  TS_Correction_Core::GetResponse    : " << var  << " is not exist" << endl;
    exit(1);
  }
  return 1.;
}


double TS_Correction_Core::GetResponse_Pt(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Pt = jet->Pt(), parton_Pt = parton->Pt();
  return (parton_Pt - jet_Pt)/jet_Pt;
}


double TS_Correction_Core::GetResponse_Et(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Et = jet->Et(), parton_Et = parton->Et();
  return (parton_Et - jet_Et)/jet_Et;
}


double TS_Correction_Core::GetResponse_Eta(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Eta = jet->Eta(), parton_Eta = parton->Eta();
  return (parton_Eta - jet_Eta)/jet_Eta;
}


double TS_Correction_Core::GetResponse_Phi(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Phi = jet->Phi(), parton_Phi = parton->Phi();
  return (parton_Phi - jet_Phi)/jet_Phi;
}


void TS_Correction_Core::SetResponseCuts(TString sample){

  ifstream reader_mean(TString(std::getenv("TSCorrOutFormulaDir"))+Form("fit_mean_%s.txt",sample.Data()));
  ifstream reader_error(TString(std::getenv("TSCorrOutFormulaDir"))+Form("fit_error_%s.txt",sample.Data()));

  if(!reader_mean){
    cout << "  >>  Fitting_Histogram::SetResponseCuts  :  can't read mean" << endl;
    exit(1);
  }
  if(!reader_error){
    cout << "  >>  Fitting_Histogram::SetResponseCuts  :  can't read error" << endl;
    exit(1);
  }
  TString name, formula;
  map<TString, TString> mean_formula, error_formula;
  
  while(reader_mean >> name >> formula){
    mean_formula[name] = formula;
  }
  while(reader_error >> name >> formula){
    error_formula[name] = formula;
  }

  int n_sigma = 2;
  for(map<TString, TString>::iterator it=mean_formula.begin(); it!=mean_formula.end(); it++){
    TString key = it->first;
    TString upper_cut=it->second, lower_cut=it->second; // initialize as mean
    upper_cut += Form("+%d*(%s)",n_sigma,error_formula[key].Data());
    lower_cut += Form("-%d*(%s)",n_sigma,error_formula[key].Data());
    //TODO: check later 
    cut[key] = new TFormula(key, Form("(%s)>x[0] && (%s)<x[0]",lower_cut.Data(),upper_cut.Data()) );
  }

} // end of function


/*
void TS_Correction_Core::ReadNTuple(TString type_){
  
  type=type_;
  TString name;
  if(type=="pythia"){
    name=base_dir;
    name+="data/root/";
    name+="TopCorr_new_SKTT_powheg_cat_v8-0-7.root";
  }
  else if(type=="herwig"){
    name=base_dir;
    name+="data/root/";
    name+="TopCorr_new_SKTT_herwig_cat_v8-0-7.root";
  }
  else if(type=="CH_120"){
    name=base_dir;
    name+="data/root/";
    name+="TopCorr_new_SKCHToCB_M120_madgraph_13TeV_2016_cat_v8-0-7.root";
  }
  else if(type=="CH_140"){
    name=base_dir;
    name+="data/root/";
    name+="TopCorr_new_SKCHToCB_M140_madgraph_13TeV_2016_cat_v8-0-7.root";
  }
  if(!gSystem->AccessPathName(name)){
    MapTFile[type] = new TFile(name);
    if(MapTFile[type]->Get("tuple_var")){
      MapTuple[type] = (TNtuple*)MapTFile[type]->Get("tuple_var");
    }
    else{
      cout << "Error: object is not exist" << endl;
      exit(1);
    }
  }
  else{
    cout << "Error: '" << name << "' is not exist" << endl;
    exit(1);
  }

  SetBranchAddress();

} // end of function
*/
/*
void TS_Correction_Core::SetBranchAddress(){

  TObjArray *arr = MapTuple[type]->GetListOfBranches();
  for(Int_t i=0; i<arr->GetEntries(); i++){
    TString branch_name = arr->At(i)->GetName();
    if(MapTupleVariables.find(branch_name)==MapTupleVariables.end()){
      MapTuple[type]->SetBranchAddress(branch_name, &(MapTupleVariables[branch_name]));
      cout << "  SetBranchAddress   :     " << branch_name << endl;
    }
    else{
      cout << "Error:  branch_name is already exist!!" << endl; 
      exit(1);
    }
  }

} // end of function
*/
/*
void TS_Correction_Core::UpdateLorentzVector(){

  MapLorentzVector["hadronic_top_b_jet"].SetPtEtaPhiM(MapTupleVariables["hadronic_top_b_jet_Pt"],
                                                      MapTupleVariables["hadronic_top_b_jet_Eta"],
                                                      MapTupleVariables["hadronic_top_b_jet_Phi"],
                                                      MapTupleVariables["hadronic_top_b_jet_M"]);

  MapLorentzVector["leptonic_top_b_jet"].SetPtEtaPhiM(MapTupleVariables["leptonic_top_b_jet_Pt"],
                                                      MapTupleVariables["leptonic_top_b_jet_Eta"],
                                                      MapTupleVariables["leptonic_top_b_jet_Phi"],
                                                      MapTupleVariables["leptonic_top_b_jet_M"]);

  MapLorentzVector["up_type_quark"].SetPtEtaPhiM(MapTupleVariables["up_type_quark_Pt"],
                                                 MapTupleVariables["up_type_quark_Eta"],
                                                 MapTupleVariables["up_type_quark_Phi"],
                                                 MapTupleVariables["up_type_quark_M"]);

  MapLorentzVector["down_type_quark"].SetPtEtaPhiM(MapTupleVariables["down_type_quark_Pt"],
                                                   MapTupleVariables["down_type_quark_Eta"],
                                                   MapTupleVariables["down_type_quark_Phi"],
                                                   MapTupleVariables["down_type_quark_M"]);

  MapLorentzVector["lepton"].SetPtEtaPhiM(MapTupleVariables["lepton_Pt"],
                                          MapTupleVariables["lepton_Eta"],
                                          MapTupleVariables["lepton_Phi"],
                                          MapTupleVariables["lepton_M"]);

  MapLorentzVector["neutrino"].SetPtEtaPhiM(MapTupleVariables["neutrino_Pt"],
                                            MapTupleVariables["neutrino_Eta"],
                                            MapTupleVariables["neutrino_Phi"],
                                            MapTupleVariables["neutrino_M"]);

} // end of function
*/
/*
void TS_Correction_Core::Read_TS_Correction(){

  ts_correction = new TF1****[NUM_SAMPLE];

  for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){
  
    ifstream reader(base_dir+TString("output/parameter/FittingResponse/")+
                  TString("fitting_parameter_")+samples[i_sample]+TString(".txt"));
    if(!reader){
      cout << "  >> Read_TS_Correction  :    file is not imported!"  << endl;
      exit(1);
    }

    TString functions;
    Int_t i_flav_, i_eta_, i_cut_;
  
    ts_correction[i_sample] = new TF1***[NUM_FLAVOUR];
    for(Int_t i_flav=0; i_flav < NUM_FLAVOUR; i_flav++){
      ts_correction[i_sample][i_flav] = new TF1**[NUM_ETA_BIN];
      for(Int_t i_eta=0; i_eta < NUM_ETA_BIN; i_eta++){
        ts_correction[i_sample][i_flav][i_eta] = new TF1*[NUM_CUT];
      }
    }

    while(reader >> functions >> i_flav_ >> i_eta_ >> i_cut_){

      ts_correction[i_sample][i_flav_][i_eta_][i_cut_] = new TF1("",functions);
    
      cout << " >> Read_TS_Correction  :    " << functions << ",  " << i_flav_ << ",  " << i_eta_ <<",  " 
                                              << i_cut_ << endl;
      cout << "                             " << ts_correction[i_sample][i_flav_][i_eta_][i_cut_]->Eval(250) << endl;

    } // end of while

  } // end of for  

} // end of function


void TS_Correction_Core::Read_TS_Correction_Error(){

  ts_correction_error = new TF1***[NUM_SAMPLE];

  for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){
 
    ifstream reader(base_dir+TString("output/parameter/FittingHistogram_Error/")+
                    TString("fitting_parameter_sigma_")+samples[i_sample]+TString(".txt"));
    if(!reader){
      cout << "  >> Read_TS_Correction_Error  :    file is not imported!"  << endl;
      exit(1);
    }


    TString functions;
    Int_t i_flav_, i_eta_;
  
    ts_correction_error[i_sample] = new TF1**[NUM_FLAVOUR];
    for(Int_t i_flav=0; i_flav < NUM_FLAVOUR; i_flav++){
      ts_correction_error[i_sample][i_flav] = new TF1*[NUM_ETA_BIN];
    }

    while(reader >> functions >> i_flav_ >> i_eta_){

      ts_correction_error[i_sample][i_flav_][i_eta_] = new TF1("",functions);
    
      cout << " >> Read_TS_Correction_Error  :    " << functions << ",  " << i_flav_ << ",  " << i_eta_ << endl;
      cout << "                                   " 
           << ts_correction_error[i_sample][i_flav_][i_eta_]->Eval(250) << endl;

      ts_correction_error_function[i_sample][i_flav_][i_eta_] = TString("(")+functions+TString(")");
      cout << "ts_correction_error_function:" 
           << ts_correction_error_function[i_sample][i_flav_][i_eta_] << endl; 
    } // end of while
  } // end of for

} // end of function


void TS_Correction_Core::Read_TS_Correction_Mean(){

  ts_correction_mean = new TF1***[NUM_SAMPLE];

  for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){
 
    ifstream reader(base_dir+TString("output/parameter/FittingHistogram_Error/")+
                    TString("fitting_parameter_mean_")+samples[i_sample]+TString(".txt"));
    if(!reader){
      cout << "  >> Read_TS_Correction_Error  :    file is not imported!"  << endl;
      exit(1);
    }


    TString functions;
    Int_t i_flav_, i_eta_;
  
    ts_correction_mean[i_sample] = new TF1**[NUM_FLAVOUR];
    for(Int_t i_flav=0; i_flav < NUM_FLAVOUR; i_flav++){
      ts_correction_mean[i_sample][i_flav] = new TF1*[NUM_ETA_BIN];
    }

    while(reader >> functions >> i_flav_ >> i_eta_){

      ts_correction_mean[i_sample][i_flav_][i_eta_] = new TF1("",functions);
    
      cout << " >> Read_TS_Correction_Mean  :    " << functions << ",  " << i_flav_ << ",  " << i_eta_ << endl;
      cout << "                                   " 
           << ts_correction_mean[i_sample][i_flav_][i_eta_]->Eval(250) << endl;

      ts_correction_mean_function[i_sample][i_flav_][i_eta_] = TString("+(")+functions+TString(")");
      cout << "ts_correction_mean_function:" 
           << ts_correction_mean_function[i_sample][i_flav_][i_eta_] << endl; 
    } // end of while
  } // end of for

} // end of function


Int_t TS_Correction_Core::FindEtaBin(Double_t eta){

  Double_t abs_eta = fabs(eta);
  Int_t nth_bin;

  if(abs_eta < 0.174)     nth_bin=0;
  else if(abs_eta <0.348) nth_bin=1;
  else if(abs_eta <0.522) nth_bin=2;
  else if(abs_eta <0.696) nth_bin=3;
  else if(abs_eta <0.879) nth_bin=4;
  else if(abs_eta <1.131) nth_bin=5;
  else if(abs_eta <1.392) nth_bin=6;
  else if(abs_eta <1.74)  nth_bin=7;
  else if(abs_eta <2.4)   nth_bin=8;
  else{
    cout << "  >> FindEtaBin  :    eta is out of range!" << endl;
    exit(1);
  }

  return nth_bin;

} // end of function


TLorentzVector TS_Correction_Core::Get_Corrected_Jet(TLorentzVector inputJet, 
                                                     Int_t i_sample_, Int_t i_cut_, Int_t i_flav_){

  Double_t jetPt = inputJet.Pt();
  Double_t jetEta = inputJet.Eta();
  Int_t i_eta_ = FindEtaBin(jetEta);

  TLorentzVector out;

  out.SetPtEtaPhiM((ts_correction[i_sample_][i_flav_][i_eta_][i_cut_]->Eval(jetPt) + 1)*jetPt,
                   jetEta,
                   inputJet.Phi(),
                   inputJet.M()
                  );
  return out;

} // end of function
*/
