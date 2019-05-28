#include "Fitting_Response.h"
#define NUM_PAR 4


Fitting_Response::Fitting_Response(){

} // end of function


Fitting_Response::~Fitting_Response(){

  for(map<TString,TProfile*>::iterator it=MapProfile.begin(); it!=MapProfile.end(); it++){
    delete it->second;
  }
} // end of function


void Fitting_Response::MakeProfile(TString sample){

  SetProfile();
  SetResponseCuts(sample);
  FillProfile(sample);
  SaveProfile(sample);

} // end of function


void Fitting_Response::SetProfile(){

  for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
  for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
    TString name = Form("%s_%s_%s",it_res->first.Data(),it_flav->first.Data(),it_eta->first.Data());
    MapProfile[name] = new TProfile(name,name,60,0.,300.);
    MapProfile[name]->Sumw2();
    cout << ">> SetProfile  :    " << name << "  has been created" << endl;
  }
  }
  }

} // end of function


void Fitting_Response::FillProfile(TString sample){

  cout << ">> Process  :    " << MapTTree[sample]->GetEntries() <<" events" << endl;

  Int_t num_entries = MapTTree[sample]->GetEntries();
  for(Int_t i=0; i<num_entries; i++){
    MapTTree[sample]->GetEntry(i);
    if(i%(num_entries/20) ==0) cout <<">>     " << i/num_entries*100 << " %% processed" << endl;
    //fill response
    for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
    for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
      // initialized as false, if a response is filled at corresponding pt,eta bin, reset as true
      bool isFilled_top_b = false, isFilled_anti_top_b = false;
      bool isFilled_up_type = false, isFilled_down_type = false;
      for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
        // check if all response was filled at corresponding pt,eta bin
        if(isFilled_top_b && isFilled_anti_top_b && isFilled_up_type && isFilled_down_type) break;
        // name of response histogram
        TString name = Form("%s_%s_%s",it_res->first.Data(),
                                       it_flav->first.Data(),
                                       it_eta->first.Data()
                           );
        if(!isFilled_top_b &&
           it_flav->second->Eval(5) &&
           it_eta->second->Eval( b_jet_from_top.Eta() )
          ){

           double response_top_b = this->GetResponse(it_res->first, &b_jet_from_top, &b_parton_from_top);
           MapProfile[name]->Fill(b_jet_from_top.Pt(),response_top_b);
           isFilled_top_b = true;

        }
        if(!isFilled_anti_top_b &&
           it_flav->second->Eval(5) &&
           it_eta->second->Eval( b_jet_from_anti_top.Eta() ) 
          ){

           double response_anti_top_b = this->GetResponse(it_res->first, &b_jet_from_anti_top, &b_parton_from_anti_top);
           MapProfile[name]->Fill(b_jet_from_anti_top.Pt(),response_anti_top_b);
           isFilled_anti_top_b = true;

        }
        if(!isFilled_up_type &&
           it_flav->second->Eval(up_type_parton_flavour) &&
           it_eta->second->Eval( up_type_jet_from_w_ch.Eta() ) 
          ){

           double response_up_type_flav = this->GetResponse(it_res->first, &up_type_jet_from_w_ch, &up_type_parton_from_w_ch);
           MapProfile[name]->Fill(up_type_jet_from_w_ch.Pt(),response_up_type_flav); 
           isFilled_up_type = true;

        }
        if(!isFilled_down_type &&
           it_flav->second->Eval(down_type_parton_flavour) &&
           it_eta->second->Eval( down_type_jet_from_w_ch.Eta() )
          ){

           double response_down_type_flav = this->GetResponse(it_res->first, &down_type_jet_from_w_ch, &down_type_parton_from_w_ch);
           MapProfile[name]->Fill(down_type_jet_from_w_ch.Pt(),response_down_type_flav); 
           isFilled_down_type = true;

        }
      }

    }
    }
      
  } //end of for : iter through ntuple

} // end of function


void Fitting_Response::SaveProfile(TString sample){

  TString fileName = std::getenv("TSCorrOutRootDir");
  fileName += Form("%s_%s.root","jetPt_vs_response",sample.Data());

  TFile *outFile = new TFile(fileName,"RECREATE");
  if(outFile->IsZombie()){
    cout << "Error: output file is not created!!" << endl;
    exit(1);
  }
  outFile->cd();

  for(map<TString,TProfile*>::iterator it=MapProfile.begin(); it!=MapProfile.end(); it++){
    it->second->Write();
    cout <<"  Write Profile:  " << it->first << endl;
  }
  outFile->Close();

} // end of function


void Fitting_Response::FitProfile(TString sample){
 
  TString fileName = std::getenv("TSCorrOutRootDir");
  fileName += "response_histograms_";
  fileName += sample;
  fileName += ".root";

  TFile* inputFile = new TFile(fileName,"READ");
  if(inputFile->IsZombie()){
    cout << "Error: cannot read file!!!" << endl;
    exit(1);
  }

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas
  c->cd();
  Double_t par[NUM_PAR], best_par[NUM_PAR], chi2, best_chi2, NDF, best_NDF;
  TString fitting_method, best_fitting_method;

  TF1 *fitFcn = new TF1("fitFcn",ResponseFittingFunction,20.,300.,NUM_PAR);

  if(MapProfile.size()!=0){
    cout << "WARNING  :    MapProfile is not empty!!!" << endl;
  }
  else{
    for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
    for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
    for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
      TString name = Form("%s_%s_%s",it_res->first.Data(),it_flav->first.Data(),it_eta->first.Data());
      MapProfile[name] = (TProfile*)inputFile->Get("response_profile/" + name);
      cout << ">> FitProfile  :    " << name << "  is loaded" << endl;
      MapProfile[name+"_nocut"] = (TProfile*)inputFile->Get("response_profile_nocut/" + name);
      cout << ">> FitProfile  :    " << name +"_nocut" << "  is loaded" << endl;
    }
    }
    }
  }

  
  ofstream fout(TString(std::getenv("TSCorrOutFormulaDir"))+Form("%s_%s.txt","TSCorrection",sample.Data()));

  for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
  for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){

    TString name = Form("%s_%s_%s",it_res->first.Data(),it_flav->first.Data(),it_eta->first.Data());
    MapProfile[name]->GetYaxis()->SetRangeUser(-0.5,0.5);
    TString x_name = it_res->first;
    x_name.ReplaceAll("Pt","P_{T}");
    x_name.ReplaceAll("Et","E_{T}");
    MapProfile[name]->GetYaxis()->SetTitle(Form("(True parton %s - Jet %s)/Jet %s",x_name.Data(),x_name.Data(),x_name.Data()));
    MapProfile[name]->GetXaxis()->SetRangeUser(18.,300.);
    MapProfile[name]->GetXaxis()->SetTitle(Form("Jet %s [GeV]",x_name.Data()));

    //TODO: different colors for udscb, udsc, uds, c, b
    if(it_flav->second->Eval(5))
      fitFcn->SetLineColor(6);
    else if(it_flav->second->Eval(4))
      fitFcn->SetLineColor(8);
    else 
      fitFcn->SetLineColor(9);

    fitFcn->SetLineWidth(3);

    best_chi2=-999; // initialize best chi2
    fitting_method="Q0";
    MapProfile[name]->Fit("fitFcn",fitting_method,"ep");
    UpdateBestParameter(fitFcn,par,best_par,chi2,best_chi2,NDF,best_NDF, fitting_method, best_fitting_method);

    fitting_method="QP0";
    MapProfile[name]->Fit("fitFcn",fitting_method,"ep");
    UpdateBestParameter(fitFcn,par,best_par,chi2,best_chi2,NDF,best_NDF, fitting_method, best_fitting_method);

    fitting_method="QE0";
    MapProfile[name]->Fit("fitFcn",fitting_method,"ep");
    UpdateBestParameter(fitFcn,par,best_par,chi2,best_chi2,NDF,best_NDF, fitting_method, best_fitting_method);

    fitting_method="QI0";
    MapProfile[name]->Fit("fitFcn",fitting_method,"ep");
    UpdateBestParameter(fitFcn,par,best_par,chi2,best_chi2,NDF,best_NDF, fitting_method, best_fitting_method);

    fitting_method="QW0";
    MapProfile[name]->Fit("fitFcn",fitting_method,"ep");
    UpdateBestParameter(fitFcn,par,best_par,chi2,best_chi2,NDF,best_NDF, fitting_method, best_fitting_method);

    /*
    fitting_method="QL0";
    MapProfile[name]->Fit("fitFcn",fitting_method,"ep");
    UpdateBestParameter(fitFcn,par,best_par,chi2,best_chi2,NDF,best_NDF, fitting_method, best_fitting_method);

    fitting_method="QWL0";
    MapProfile[name]->Fit("fitFcn",fitting_method,"ep");
    UpdateBestParameter(fitFcn,par,best_par,chi2,best_chi2,NDF,best_NDF, fitting_method, best_fitting_method);
    */

    fitFcn->SetParameters(best_par);
    fitFcn->SetChisquare(best_chi2); 
    fitFcn->SetNDF(best_NDF);
    cout << "   >> FitProfile  :    " << "best_par[0]  :    " << best_par[0]
                                      << "best_par[1]  :    " << best_par[1]
                                      << "best_par[2]  :    " << best_par[2]
                                      << "best_par[3]  :    " << best_par[3] << endl;

    cout << " >>FitProfile  :    best fitting method is '" << best_fitting_method << "'" << endl;

    MapProfile[name]->GetXaxis()->SetRangeUser(0.,300.);
    gStyle->SetOptFit(1111);
    MapProfile[name]->Draw();
    fitFcn -> Draw("same");

    TString save_dir = std::getenv("TSCorrOutImgDir");
    save_dir+=Form("Response_profile_%s_%s.pdf",name.Data(),sample.Data());
    c->SaveAs(save_dir);

    fitFcn->GetParameters(par);
    TString out_formula = ResponseFittingFunction();
    out_formula = Form(out_formula.Data(),par[0],par[1],par[2],par[3]);
    out_formula.ReplaceAll("+-","-");
    fout << name << "\t\t" << out_formula << endl;
 


  }
  }
  }

  inputFile->Close();
  fout.close();

} // end of function


/*
void Fitting_Response::FitProfileCombined(){

  TFile** inputFile;
  inputFile = new TFile*[NUM_SAMPLE];

  for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){
    TString fileName = base_dir;
    fileName += "output/root/";
    fileName += "jetPt_vs_response_";
    fileName += samples[i_sample];
    fileName += ".root";
    inputFile[i_sample] = new TFile(fileName, "READ");

    if(inputFile[i_sample]->IsZombie()){
      cout << "Error: cannot read file!!!" << endl;
      exit(1);
    }
  } // end of for

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas
  c->cd();
  Double_t par[NUM_PAR];
  TString fitting_method;

  TF1 *fitFcn1 = new TF1("fitFcn1",ResponseFittingFunction,0.,300.,NUM_PAR);
  TF1 *fitFcn2 = new TF1("fitFcn2",ResponseFittingFunction,0.,300.,NUM_PAR);

  if(MapProfile.size()!=0){
    cout << "Error  :    MapProfile is not empty!!!" << endl;
    exit(1);
  }
  else{

    for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){
    for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){
    for(Int_t i_cut=0; i_cut<NUM_CUT; i_cut++){
    for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){ 
      TString name_base = flavour[i_flav] + etaBin[i_eta] + cut[i_cut];
      TString name = name_base + TString("_") + samples[i_sample];
      MapProfile[name] = (TProfile*)inputFile[i_sample]->Get(name_base);
      cout << ">> FitProfile  :    " << name << "  is loaded" << endl;
    }
    }
    }
    } // end of nested for
  }


  for(Int_t i_cut=0; i_cut<NUM_CUT; i_cut++){
  for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){
  for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){

    TString name =flavour[i_flav] + etaBin[i_eta] + cut[i_cut];
    TString name_pythia = name + TString("_") + samples[PYTHIA];
    TString name_herwig = name + TString("_") + samples[HERWIG];

    TString tag;



    // pythia
    MapProfile[name_pythia]->GetYaxis()->SetRangeUser(-0.5,0.5);
    MapProfile[name_pythia]->GetYaxis()->SetTitle("(True parton pT - Jet pT)/Jet pT");
    MapProfile[name_pythia]->GetXaxis()->SetRangeUser(18.,300.);
    MapProfile[name_pythia]->GetXaxis()->SetTitle("Jet pT [GeV]");

    if(i_flav==TOP_B){
      fitFcn1->SetLineColor(6);
      MapProfile[name_pythia]->SetLineColor(6);
      tag = "#bf{b flavour jet}";
    }
    else if(i_flav==CHARM){
      fitFcn1->SetLineColor(8);
      MapProfile[name_pythia]->SetLineColor(8);
      tag = "#bf{c flavour jet}";
    }
    else if(i_flav==LIGHT){
      fitFcn1->SetLineColor(9);
      MapProfile[name_pythia]->SetLineColor(9);
      tag = "#bf{u/d/s flavour jet}";
    }

    fitFcn1->SetLineWidth(1);

    fitting_method="W";
    MapProfile[name_pythia]->Fit("fitFcn1",fitting_method,"same");
   

    MapProfile[name_pythia]->GetXaxis()->SetRangeUser(0.,300.);
    gStyle->SetOptFit(0);
    MapProfile[name_pythia]->Draw();

    // herwig
    MapProfile[name_herwig]->GetYaxis()->SetRangeUser(-0.5,0.5);
    MapProfile[name_herwig]->GetYaxis()->SetTitle("(True parton pT - Jet pT)/Jet pT");
    MapProfile[name_herwig]->GetXaxis()->SetRangeUser(18.,300.);
    MapProfile[name_herwig]->GetXaxis()->SetTitle("Jet pT [GeV]");

    if(i_flav==TOP_B){
      fitFcn2->SetLineColor(1);
      MapProfile[name_herwig]->SetLineColor(1);
    }
    else if(i_flav==CHARM){
      fitFcn2->SetLineColor(1);
      MapProfile[name_herwig]->SetLineColor(1);
    }
    else if(i_flav==LIGHT){
      fitFcn2->SetLineColor(1);
      MapProfile[name_herwig]->SetLineColor(1);
    }

    fitFcn2->SetLineWidth(1);

    fitting_method="W";
    MapProfile[name_herwig]->Fit("fitFcn2",fitting_method,"same");

    MapProfile[name_herwig]->GetXaxis()->SetRangeUser(0.,300.);
    gStyle->SetOptFit(0);
    MapProfile[name_herwig]->Draw("same");

    TLegend* legend;
    legend = new TLegend(0.76,0.67,0.90,0.77);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetShadowColor(0);
    legend->SetLineColor(0.);
    legend->SetEntrySeparation(0.3);

    legend->AddEntry(MapProfile[name_pythia],"pythia","l");
    legend->AddEntry(MapProfile[name_herwig],"herwig","l");
    legend->Draw("same");

    TLatex *latex = new TLatex();
    latex->SetNDC(kTRUE);
    latex->SetTextFont(42);
    latex->SetTextSize(0.027);
    latex->SetTextColor(kBlack); 
    latex->DrawLatex(0.15,0.91,tag);

    TString save_dir = base_dir;
    save_dir+="output/pdf/Fitting_Response/";
    save_dir+="combined";
    save_dir+="/";
    save_dir+=name;
    save_dir+=".pdf";

    c->SaveAs(save_dir);

  }
  }
  }

  // delete memory
  for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){
    inputFile[i_sample]->Close();
    delete inputFile[i_sample];
  }
  delete [] inputFile;

} // end of function


void Fitting_Response::FitProfile_8TeV_13TeV(){

  TFile** inputFile;
  inputFile = new TFile*[2];
  TString samples_[2]={"pythia","8TeV"};
  for(Int_t i_sample=0; i_sample<2; i_sample++){
    TString fileName = base_dir;
    fileName += "output/root/";
    fileName += "jetPt_vs_response_";
    fileName += samples_[i_sample];
    fileName += ".root";
    inputFile[i_sample] = new TFile(fileName, "READ");

    if(inputFile[i_sample]->IsZombie()){
      cout << "Error: cannot read file!!!" << endl;
      exit(1);
    }
  } // end of for

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas
  c->cd();
  Double_t par[NUM_PAR];
  TString fitting_method;

  TF1 *fitFcn1 = new TF1("fitFcn1",ResponseFittingFunction,0.,300.,NUM_PAR);
  TF1 *fitFcn2 = new TF1("fitFcn2",ResponseFittingFunction,0.,300.,NUM_PAR);

  // define etaBin_
  TString etaBin_[NUM_ETA_BIN];
  std::copy(etaBin,etaBin+NUM_ETA_BIN,etaBin_);
  for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){
    etaBin_[i_eta].Remove(etaBin_[i_eta].Length()-1);
  }
  //

  if(MapProfile.size()!=0){
    cout << "Error  :    MapProfile is not empty!!!" << endl;
    exit(1);
  }
  else{

    for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){
    for(Int_t i_eta=0; i_eta<NUM_ETA_BIN-1; i_eta++){
    for(Int_t i_sample=0; i_sample<2; i_sample++){
      TString tmp_cut="";
      if(i_sample==0){
        tmp_cut = "_two_sigma";
      }
      else if(i_sample==1){
        if(i_flav==2)
          tmp_cut = "_20cut";
        else
          tmp_cut = "";
      }
      TString name_base = flavour[i_flav] + etaBin_[i_eta] + tmp_cut;
      TString name = name_base +"_"+ samples_[i_sample];
      MapProfile[name] = (TProfile*)inputFile[i_sample]->Get(name_base);
      if(!MapProfile[name]){
        cout << ">> FitProfile  :    " << name << "  is not exist!" << endl;
        exit(1);
      }
      else{
        cout << ">> FitProfile  :    " << name << "  is loaded" << endl;
      }
    }
    }
    } // end of nested for
  }


  for(Int_t i_eta=0; i_eta<NUM_ETA_BIN-1; i_eta++){
  for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){

    TString name =flavour[i_flav] + etaBin_[i_eta];
    TString name_13TeV = name + "_two_sigma" + TString("_") + samples_[0];
    TString name_8TeV="";
    if(i_flav==2)
      name_8TeV = name + "_20cut" + TString("_") + samples_[1];
    else
      name_8TeV = name + TString("_") + samples_[1];

    TString tag;


    // pythia
    MapProfile[name_13TeV]->GetYaxis()->SetRangeUser(-0.5,0.5);
    MapProfile[name_13TeV]->GetYaxis()->SetTitle("(True parton pT - Jet pT)/Jet pT");
    MapProfile[name_13TeV]->GetXaxis()->SetRangeUser(18.,300.);
    MapProfile[name_13TeV]->GetXaxis()->SetTitle("Jet pT [GeV]");

    if(i_flav==TOP_B){
      fitFcn1->SetLineColor(6);
      MapProfile[name_13TeV]->SetLineColor(6);
      tag = "#bf{b flavour jet}";
    }
    else if(i_flav==CHARM){
      fitFcn1->SetLineColor(8);
      MapProfile[name_13TeV]->SetLineColor(8);
      tag = "#bf{c flavour jet}";
    }
    else if(i_flav==LIGHT){
      fitFcn1->SetLineColor(9);
      MapProfile[name_13TeV]->SetLineColor(9);
      tag = "#bf{u/d/s flavour jet}";
    }

    fitFcn1->SetLineWidth(1);

    fitting_method="W";
    MapProfile[name_13TeV]->Fit("fitFcn1",fitting_method,"same");
   

    MapProfile[name_13TeV]->GetXaxis()->SetRangeUser(0.,300.);
    gStyle->SetOptFit(0);
    MapProfile[name_13TeV]->Draw();

    // herwig
    MapProfile[name_8TeV]->GetYaxis()->SetRangeUser(-0.5,0.5);
    MapProfile[name_8TeV]->GetYaxis()->SetTitle("(True parton pT - Jet pT)/Jet pT");
    MapProfile[name_8TeV]->GetXaxis()->SetRangeUser(18.,300.);
    MapProfile[name_8TeV]->GetXaxis()->SetTitle("Jet pT [GeV]");

    if(i_flav==TOP_B){
      fitFcn2->SetLineColor(1);
      MapProfile[name_8TeV]->SetLineColor(1);
    }
    else if(i_flav==CHARM){
      fitFcn2->SetLineColor(1);
      MapProfile[name_8TeV]->SetLineColor(1);
    }
    else if(i_flav==LIGHT){
      fitFcn2->SetLineColor(1);
      MapProfile[name_8TeV]->SetLineColor(1);
    }

    fitFcn2->SetLineWidth(1);

    fitting_method="W";
    MapProfile[name_8TeV]->Fit("fitFcn2",fitting_method,"same");

    MapProfile[name_8TeV]->GetXaxis()->SetRangeUser(0.,300.);
    gStyle->SetOptFit(0);
    MapProfile[name_8TeV]->Draw("same");

    TLegend* legend;
    legend = new TLegend(0.76,0.67,0.90,0.77);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetShadowColor(0);
    legend->SetLineColor(0.);
    legend->SetEntrySeparation(0.3);

    legend->AddEntry(MapProfile[name_13TeV],"13TeV","l");
    legend->AddEntry(MapProfile[name_8TeV],"8TeV","l");
    legend->Draw("same");

    TLatex *latex = new TLatex();
    latex->SetNDC(kTRUE);
    latex->SetTextFont(42);
    latex->SetTextSize(0.027);
    latex->SetTextColor(kBlack); 
    latex->DrawLatex(0.15,0.91,tag);

    TString save_dir = base_dir;
    save_dir+="output/png/Fitting_Response/";
    save_dir+="8TeV_13TeV";
    save_dir+="/";
    save_dir+=name;
    save_dir+=".png";

    c->SaveAs(save_dir);

  }
  }

  // delete memory
  for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){
    inputFile[i_sample]->Close();
    delete inputFile[i_sample];
  }
  delete [] inputFile;

} // end of function
*/

void Fitting_Response::UpdateBestParameter(TF1* fcn_, Double_t *par_, Double_t *best_par_,
                                           Double_t &chi2_, Double_t &best_chi2_, 
                                           Double_t &NDF_, Double_t &best_NDF_,
                                           TString &fitting_method_, TString &best_fitting_method_){

    chi2_ = fcn_->GetChisquare();
    if(best_chi2_<0 || chi2_<best_chi2_){
      cout << "   >> UpdateBestParameter  :    " << "best_chi2  :    " << best_chi2_
         << "    chi2  :    " << chi2_ << endl;
      NDF_ = fcn_->GetNDF();
      fcn_->GetParameters(par_);
      best_chi2_ = chi2_;
      best_NDF_ = NDF_;
      std::copy(par_,par_+NUM_PAR,best_par_);
      best_fitting_method_ = fitting_method_;
      /*
      cout << "   >> UpdateBestParameter  :    " << "par[0]_  :    " << par_[0]
                                                 << "par[1]_  :    " << par_[1]
                                                 << "par[2]_  :    " << par_[2]
                                                 << "par[3]_  :    " << par_[3] << endl;*/
    }

} // end of function


