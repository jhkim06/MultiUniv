#include "TS_Correction_Core.h"

TS_Correction_Core::TS_Correction_Core(){

  flavour["uds"] = new TFormula("uds","x[0]<4");
  flavour["udsc"] = new TFormula("udsc","x[0]<5");
  flavour["b"] = new TFormula("b","x[0]==5");
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

  /*
  TString tmp_cut[NUM_CUT] = {"20cut","20_010cut","20_020cut","20_030cut","30cut","30_010cut","30_020cut","30_030cut","1.5_sigma", "two_sigma", "nocut"};


  TString tmp_object[NUM_OBJ]={"dijet_ll_","hadronic_top_llb_","dijet_cl_","hadronic_top_clb_","leptonic_top_"};
  TString tmp_corrections[NUM_CORR]={"corr_20cut_","corr_20_010cut_","corr_20_020cut_","corr_20_030cut_",
                                     "corr_30cut_","corr_30_010cut_","corr_30_020cut_","corr_30_030cut_",
                                     "1.5_sigma_", "two_sigma_","nocut_", "optimized_","uncorrected_"};
  TString tmp_samples[NUM_SAMPLE]={"pythia","herwig"};
  */

} // end of function


TS_Correction_Core::~TS_Correction_Core(){

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
