#include "Fitting_Histogram.h"
#include "TMath.h"
#define NUM_PAR 4
#define NUM_PT_BIN 15

Fitting_Histogram::Fitting_Histogram(){

} // end of function


Fitting_Histogram::~Fitting_Histogram(){

} // end of function


void Fitting_Histogram::MakeHistogram(TString sample){
  SetHistogram();
  FillHistogram(sample);
  SaveHistogram(sample);

} // end of function


void Fitting_Histogram::SetHistogram(){

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
    MapHistogram[name] = new TH1F(name,name,50,-0.8,0.8);
    MapHistogram[name]->Sumw2();
    cout << ">> SetHistogram  :    " << name << "  has been created" << endl;
  }
  }
  }
  }
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
  for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
  for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
    TString name = Form("%s_%s_%s_%s",it_flav->first.Data(),it_pt->first.Data(),it_eta->first.Data(),"jet_pt");
    Double_t xlow=0.;
    Double_t xup=1000.;
    // find min pt and max pt
    for(int i=0; i<1000; i++){
      if(it_pt->second->Eval(i) && xlow==0.){
        xlow = (Double_t)i;
      }
      else if(!it_pt->second->Eval(i) && xlow!=0.){
        xup = (Double_t)i;
        break;
      }
    }
    Int_t nbins = (Int_t)(xup-xlow);
    MapHistogram[name] = new TH1F(name,name,nbins,xlow,xup);
    MapHistogram[name]->Sumw2();
    cout << ">> SetHistogram  :    " << name << "  has been created" << endl;
  }
  }
  }

} // end of function


void Fitting_Histogram::FillHistogram(TString sample){
  /*
  for(Int_t i_sample=0; i_sample<NUM_SAMPLE; i_sample++){
    TString key = samples[i_sample];
    ts_correction[key] = new TS_Correction(key);
    ts_correction[key] = new TS_Correction(key);
  }
  */
  //TODO: define variable sample
  if(MapTTree.find(sample) == MapTTree.end()){
    cout << "  >> MapTTree is empty" << endl;
    exit(1);
  }
  cout << ">> Process  :    " << MapTTree[sample]->GetEntries() <<" events" << endl;

  Int_t num_entries = MapTTree[sample]->GetEntries();
  for(Long64_t i=0; i<num_entries; i++){
    MapTTree[sample]->GetEntry(i);
    if(i%(num_entries/20) ==0) cout <<">>     " << i/num_entries*100 << " %% processed" << endl;
    //fill response
    for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
    for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
      // initialized as false, if a response is filled at corresponding pt,eta bin, reset as true
      bool isFilled_top_b = false, isFilled_anti_top_b = false;
      bool isFilled_up_type = false, isFilled_down_type = false;
      for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
      for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
        // check if all response was filled at corresponding pt,eta bin
        if(isFilled_top_b && isFilled_anti_top_b && isFilled_up_type && isFilled_down_type) break;
        // name of response histogram
        TString name = Form("%s_%s_%s_%s",it_res->first.Data(),
                                          it_flav->first.Data(),
                                          it_pt->first.Data(),
                                          it_eta->first.Data()
                           );
        if(!isFilled_top_b &&
           it_flav->second->Eval(5) &&
           it_eta->second->Eval( b_jet_from_top.Eta() ) &&
           it_pt->second->Eval( b_jet_from_top.Pt() )){

           double response_top_b = this->GetResponse(it_res->first, &b_jet_from_top, &b_parton_from_top);
           MapHistogram[name]->Fill(response_top_b);
           isFilled_top_b = true;

        }
        if(!isFilled_anti_top_b &&
           it_flav->second->Eval(5) &&
           it_eta->second->Eval( b_jet_from_anti_top.Eta() ) && 
           it_pt->second->Eval( b_jet_from_anti_top.Pt() )){

           double response_anti_top_b = this->GetResponse(it_res->first, &b_jet_from_anti_top, &b_parton_from_anti_top);
           MapHistogram[name]->Fill(response_anti_top_b);
           isFilled_anti_top_b = true;

        }
        if(!isFilled_up_type &&
           it_flav->second->Eval(up_type_parton_flavour) &&
           it_eta->second->Eval( up_type_jet_from_w_ch.Eta() ) && 
           it_pt->second->Eval( up_type_jet_from_w_ch.Pt() )){

           double response_up_type_flav = this->GetResponse(it_res->first, &up_type_jet_from_w_ch, &up_type_parton_from_w_ch);
           MapHistogram[name]->Fill(response_up_type_flav); 
           isFilled_up_type = true;

        }
        if(!isFilled_down_type &&
           it_flav->second->Eval(down_type_parton_flavour) &&
           it_eta->second->Eval( down_type_jet_from_w_ch.Eta() ) && 
           it_pt->second->Eval( down_type_jet_from_w_ch.Pt() )){

           double response_down_type_flav = this->GetResponse(it_res->first, &down_type_jet_from_w_ch, &down_type_parton_from_w_ch);
           MapHistogram[name]->Fill(response_down_type_flav); 
           isFilled_down_type = true;

        }
      }
      }
    }
    }
    // fill pt distribution
    for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
      bool isFilled_top_b = false, isFilled_anti_top_b = false;
      bool isFilled_up_type = false, isFilled_down_type = false;
      for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
      for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
        if(isFilled_top_b && isFilled_anti_top_b && isFilled_up_type && isFilled_down_type) break;
        TString name = Form("%s_%s_%s_%s",it_flav->first.Data(),it_pt->first.Data(),it_eta->first.Data(),"jet_pt");
        if(!isFilled_top_b &&
           it_flav->second->Eval(5) &&
           it_eta->second->Eval( b_jet_from_top.Eta() ) && 
           it_pt->second->Eval( b_jet_from_top.Pt() )){

           MapHistogram[name]->Fill(b_jet_from_top.Pt());
           isFilled_top_b = true;

        }
        if(!isFilled_anti_top_b &&
           it_flav->second->Eval(5) &&
           it_eta->second->Eval( b_jet_from_anti_top.Eta() ) &&
           it_pt->second->Eval( b_jet_from_anti_top.Pt() )){

           MapHistogram[name]->Fill(b_jet_from_anti_top.Pt());
           isFilled_anti_top_b = true;

        }
        if(!isFilled_up_type &&
           it_flav->second->Eval(up_type_parton_flavour) &&
           it_eta->second->Eval( up_type_jet_from_w_ch.Eta() ) &&
           it_pt->second->Eval( up_type_jet_from_w_ch.Pt() )){

           MapHistogram[name]->Fill(up_type_jet_from_w_ch.Pt());
           isFilled_up_type = true;

        }
        if(!isFilled_down_type &&
           it_flav->second->Eval(down_type_parton_flavour) &&
           it_eta->second->Eval( down_type_jet_from_w_ch.Eta() ) &&
           it_pt->second->Eval( down_type_jet_from_w_ch.Pt() )){

           MapHistogram[name]->Fill(down_type_jet_from_w_ch.Pt());
           isFilled_down_type = true;

        }
      }
      }
    }


  } //end of for : iter through ntuple

} // end of function


void Fitting_Histogram::SaveHistogram(TString sample){

  TString fileName = std::getenv("TSCorrOutRootDir");
  fileName += "response_histograms_";
  fileName += sample;
  fileName += ".root";

  TFile *outFile = new TFile(fileName,"RECREATE");
  if(outFile->IsZombie()){
    cout << "Error: output file is not created!!" << endl;
    exit(1);
  }
  outFile->cd();

  for(map<TString,TH1F*>::iterator it=MapHistogram.begin(); it!=MapHistogram.end(); it++){
    it->second->Write();
    cout <<"  Write Histogram:  " << it->first << endl;
  }
  outFile->Close();

} // end of function


void Fitting_Histogram::FitHistogram(TString sample){

  TString fileName = std::getenv("TSCorrOutRootDir");
  fileName += "response_histograms_";
  fileName += sample;
  fileName += ".root";

  TFile *inputFile = new TFile(fileName,"READ");
  if(inputFile->IsZombie()){
    cout << "Error: cannot read file!!!" << endl;
    cout << "or file is not exist!!!  : " << fileName << endl;
    exit(1);
  }

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas
  c->cd();
  Double_t par[3];

  TF1 *gausFit = new TF1("gausFit","gaus");

  if(MapHistogram.size()!=0){
    cout << "WARNING  :    MapHistogram is not empty!!!" << endl;
  }
  else{

    // read response histograms
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
      MapHistogram[name] = (TH1F*)inputFile->Get("response_histogram/" + name);
    }
    }
    }
    }
    // read pt distribution histogram
    for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
    for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
    for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
      TString name = Form("%s_%s_%s_%s",it_flav->first.Data(),it_pt->first.Data(),it_eta->first.Data(),"jet_pt");
      MapHistogram[name] = (TH1F*)inputFile->Get("pt_histogram/" + name);
    }
    }
    }
  }

  cout << "Fitting_Histogram::FitHistogram :  MapHistogram is ready" << endl;
  ofstream fout1(TString(std::getenv("TSCorrOutTextDir"))+Form("%s_%s.txt","gaus_fit_res_hist_parameters_",sample.Data()));

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
    if(!MapHistogram[name]){
      cout << "Fitting_Histogram::FitHistogram : " << name << " is not exist!!!!" << endl;
      exit(1);
    }
    cout <<"debug1" << endl;
    TString x_name = it_res->first;
    x_name.ReplaceAll("Pt","P_{T}");
    x_name.ReplaceAll("Et","E_{T}");
    MapHistogram[name]->GetXaxis()->SetTitle(Form("(True parton %s - Jet %s)/Jet %s",x_name.Data(),x_name.Data(),x_name.Data()));

    Double_t rawMean = MapHistogram[name]->GetMean();
    Double_t rawRMS = MapHistogram[name]->GetRMS();
    Double_t n_sigma = 1.5;
    Double_t min = rawMean - n_sigma*rawRMS;
    Double_t max = rawMean + n_sigma*rawRMS;
    cout << "  >>FitHistogram  :    " << "fit range    min  :    "  << min << "    max  :    "  << max << endl;
    gausFit->SetRange(min,max);
    MapHistogram[name]->Fit("gausFit","","ep",min,max);
    Double_t mean_gauss = gausFit->GetParameter(1);
    Double_t rms_gauss = gausFit->GetParameter(2);
    Double_t min_gauss = mean_gauss - n_sigma*rms_gauss;
    Double_t max_gauss = mean_gauss + n_sigma*rms_gauss;
    MapHistogram[name]->Fit("gausFit","W","ep",min_gauss,max_gauss);
    gausFit->GetParameters(par);
    MapHistogram[name]->Draw();
    gausFit->Draw("same");
   
    TString save_dir = std::getenv("TSCorrOutImgDir");
    save_dir+=Form("%s_%s_%s.pdf","response_histogram",name.Data(),sample.Data());
    c->SaveAs(save_dir);

    //TODO: find pt bin
    TString name_pt_dist=Form("%s_%s_%s_%s",it_flav->first.Data(),it_pt->first.Data(),it_eta->first.Data(),"jet_pt");

    if(!MapHistogram[name_pt_dist]){
      cout << "Fitting_Histogram::FitHistogram : " << name_pt_dist << " is not exist!!!!" << endl;
      exit(1);
    }
    Double_t meanPt = MapHistogram[name_pt_dist]->GetMean();
    Double_t rmsPt = MapHistogram[name_pt_dist]->GetRMS();
    Double_t mean = gausFit->GetParameter(1);
    Double_t mean_error = gausFit->GetParError(1);
    Double_t sigma = gausFit->GetParameter(2);
    Double_t sigma_error = gausFit->GetParError(2);

    SaveFitParameter(fout1, name,
                     meanPt, rmsPt, mean, mean_error, sigma, sigma_error);

  }
  }
  }
  }

  inputFile->Close();
  fout1.close();

} // end of function


void Fitting_Histogram::FitHistMean(TString sample){

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas

  TString name;
  Double_t tmp_meanPt, tmp_rmsPt, tmp_mean, tmp_mean_error, tmp_sigma, tmp_sigma_error;
  map<TString, Double_t> meanPt, rmsPt, mean, mean_error;

  ifstream reader(TString(std::getenv("TSCorrOutTextDir"))+Form("%s_%s.txt","gaus_fit_res_hist_parameters_",sample.Data()));
  ofstream fout(TString(std::getenv("TSCorrOutFormulaDir"))+Form("fit_mean_%s.txt",sample.Data()));

  Double_t par[NUM_PAR];
  TF1 *fitFcn = new TF1("fitFcn",SigmaErrorFittingFunction,0.,300.,NUM_PAR);

  while(reader >> name >>
        tmp_meanPt >> tmp_rmsPt >> tmp_mean >> tmp_mean_error >> tmp_sigma >> tmp_sigma_error){

    cout << name << "  "
         << tmp_meanPt << "  "<< tmp_rmsPt << "  "
         << tmp_mean << "  "<< tmp_mean_error << "  " 
         << tmp_sigma << "  "<< tmp_sigma_error << endl;

    meanPt[name]= tmp_meanPt;
    rmsPt[name] = tmp_rmsPt;
    mean[name] = tmp_mean;
    mean_error[name] = tmp_mean_error;
  }

  for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
  for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
    /*if(it_res->first == "Eta" || it_res->first == "Phi"){
      continue;
    }*/
    TString graph_name = Form("%s_%s_%s", it_res->first.Data(), it_flav->first.Data(), it_eta->first.Data());
    int n_ptBin = ptBin.size();
    Double_t meanPt_array[n_ptBin];
    Double_t mean_array[n_ptBin];
    Double_t rmsPt_array[n_ptBin];
    Double_t mean_error_array[n_ptBin];
    
    map<TString,TFormula*>::iterator it_pt_begin=ptBin.begin();
    for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
      TString name = Form("%s_%s_%s_%s",it_res->first.Data(),
                                        it_flav->first.Data(),
                                        it_pt->first.Data(),
                                        it_eta->first.Data()
                         );
      int i = std::distance(it_pt_begin, it_pt);
      meanPt_array[i] = meanPt[name];
      mean_array[i] = mean[name];
      rmsPt_array[i] = 0;// rmsPt[name];
      mean_error_array[i] = mean_error[name];
    }
    /*
    MapGraphErrors[graph_name] = new TGraphErrors(NUM_PT_BIN, meanPt_array,
                                                              mean_array,
                                                              rmsPt_array,
                                                              mean_error_array);
    MapGraphErrors[graph_name]->Fit("fitFcn","","ep",30.,300);
    MapGraphErrors[graph_name]->GetXaxis()->SetRangeUser(0,300.);
    MapGraphErrors[graph_name]->GetYaxis()->SetRangeUser(-0.1,0.3);
    MapGraphErrors[graph_name]->SetMarkerStyle(21);
    c->cd();
    MapGraphErrors[graph_name]->Draw("AP");
    */
    
    MapGraph[graph_name] = new TGraph(NUM_PT_BIN, meanPt_array, mean_array);

    MapGraph[graph_name]->Fit("fitFcn","","ep",30.,300);
    MapGraph[graph_name]->GetXaxis()->SetLimits(0,300);
    //MapGraph[graph_name]->GetXaxis()->SetRangeUser(0,300); //it's not work!
    MapGraph[graph_name]->GetYaxis()->SetRangeUser(-0.1,0.3);
    MapGraph[graph_name]->SetMarkerStyle(21);
    c->cd();
    MapGraph[graph_name]->Draw("AP");
    
    //fitFcn->Draw("same");
    fitFcn->GetParameters(par);
    
    TString save_dir = std::getenv("TSCorrOutImgDir");
    save_dir+=Form("fitting_mean_%s_%s.pdf", graph_name.Data(), sample.Data());
    c->SaveAs(save_dir);
    TString out_formula = SigmaErrorFittingFunction();
    out_formula = Form(out_formula.Data(),par[0],par[1],par[2],par[3]);
    out_formula.ReplaceAll("+-","-");
    fout << graph_name << "\t\t" << out_formula << endl;
    c->Clear();
  }
  }
  }
  fout.close(); 


} // end of function


void Fitting_Histogram::FitHistError(TString sample){

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas

  TString name;
  Double_t tmp_meanPt, tmp_rmsPt, tmp_mean, tmp_mean_error, tmp_sigma, tmp_sigma_error;
  map<TString, Double_t> meanPt, rmsPt, sigma, sigma_error;

  ifstream reader(TString(std::getenv("TSCorrOutTextDir"))+Form("%s_%s.txt","gaus_fit_res_hist_parameters_",sample.Data()));
  ofstream fout(TString(std::getenv("TSCorrOutFormulaDir"))+Form("fit_error_%s.txt",sample.Data()));

  Double_t par[NUM_PAR];
  TF1 *fitFcn = new TF1("fitFcn",SigmaErrorFittingFunction,0.,300.,NUM_PAR);

  while(reader >> name >>
        tmp_meanPt >> tmp_rmsPt >> tmp_mean >> tmp_mean_error >> tmp_sigma >> tmp_sigma_error){

    cout << name << "  "
         << tmp_meanPt << "  "<< tmp_rmsPt << "  "
         << tmp_mean << "  "<< tmp_mean_error << "  " 
         << tmp_sigma << "  "<< tmp_sigma_error << endl;

    meanPt[name]= tmp_meanPt;
    rmsPt[name] = tmp_rmsPt;
    sigma[name] = tmp_sigma;
    sigma_error[name] = tmp_sigma_error;
  }


  for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
  for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
    TString graph_name = Form("%s_%s_%s", it_res->first.Data(), it_flav->first.Data(), it_eta->first.Data());
    int n_ptBin = ptBin.size();
    Double_t meanPt_array[n_ptBin];
    Double_t sigma_array[n_ptBin];
    map<TString,TFormula*>::iterator it_pt_begin=ptBin.begin();
    for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
      TString name = Form("%s_%s_%s_%s",it_res->first.Data(),
                                        it_flav->first.Data(),
                                        it_pt->first.Data(),
                                        it_eta->first.Data()
                         );
      int i = std::distance(it_pt_begin, it_pt);
      meanPt_array[i] = meanPt[name];
      sigma_array[i] = sigma[name];
    }
    //MapGraphErrors[graph_name] = new TGraphErrors(NUM_PT_BIN, meanPt_array,
    //                                                          sigma_array,
    //                                                          rmsPt_array,
    //                                                          sigma_error_array);
    MapGraph[graph_name] = new TGraph(NUM_PT_BIN, meanPt_array, sigma_array);
    MapGraph[graph_name]->Fit("fitFcn","","ep",30.,300);
    MapGraph[graph_name]->GetXaxis()->SetLimits(0,300);
    //MapGraph[graph_name]->GetXaxis()->SetRangeUser(0,300); //it's not work!
    MapGraph[graph_name]->GetYaxis()->SetRangeUser(-0.05,0.5);
    MapGraph[graph_name]->SetMarkerStyle(21);
    c->cd();
    MapGraph[graph_name]->Draw("AP");
    
    //fitFcn->Draw("same");
    fitFcn->GetParameters(par);
    
    TString save_dir = std::getenv("TSCorrOutImgDir");
    save_dir+=Form("fitting_error_%s_%s.pdf", graph_name.Data(), sample.Data());
    c->SaveAs(save_dir);
    TString out_formula = SigmaErrorFittingFunction();
    out_formula = Form(out_formula.Data(),par[0],par[1],par[2],par[3]);
    out_formula.ReplaceAll("+-","-");
    fout << graph_name << "\t\t" << out_formula << endl;
    c->Clear();
  }
  }
  }
  fout.close(); 


} // end of function

/*
void Fitting_Histogram::SaveHistogram_CorrectionDifference(TString type_){

  type = type_;

  TString fileName = base_dir;
  fileName += "output/root/";
  fileName += "response_histograms_";
  fileName += type;
  fileName += ".root";

  TFile *inputFile = new TFile(fileName,"READ");
  if(inputFile->IsZombie()){
    cout << "Error: cannot read file!!!" << endl;
    exit(1);
  }

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas
  c->cd();

  if(MapHistogram.size()!=0){
    cout << "WARNING  :    MapHistogram is not empty!!!" << endl;
  }
  else{

    for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){
    for(Int_t i_pt=0; i_pt<NUM_PT_BIN; i_pt++){
    for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){
      TString name = flavour[i_flav] + ptBin[i_pt] + etaBin[i_eta];
      MapHistogram[name+TString("_corr_diff")] = (TH1F*)inputFile->Get(name+TString("_corr_diff"));
      cout << ">> FitHistogram  :    " << name+TString("_corr_diff") << "  is loaded" << endl;
    }
    }
    } // end of nested for
  }

  for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){
  for(Int_t i_pt=0; i_pt<NUM_PT_BIN; i_pt++){
  for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){
    TString name = flavour[i_flav] + ptBin[i_pt] + etaBin[i_eta];
    TString format;
    format = "pdf";
    TString save_dir = base_dir;
    if(format=="png")
      save_dir+="output/png/Histogram_Corr_Diff/";
    else
      save_dir+="output/pdf/Histogram_Corr_Diff/";

    save_dir+=type;
    save_dir+="/";
    save_dir+=name+TString("_corr_diff");
    if(format=="png")
      save_dir+=".png";
    else
      save_dir+=".pdf";
    MapHistogram[name+TString("_corr_diff")]->Draw();
    c->SaveAs(save_dir);
  }
  }
  } // end of nested for

} // end of function

void Fitting_Histogram::DrawCorrectionDifference(TString type_){

  type = type_;

  TString fileName = base_dir;
  fileName += "output/root/";
  fileName += "response_histograms_";
  fileName += type;
  fileName += ".root";

  TFile *inputFile = new TFile(fileName,"READ");
  if(inputFile->IsZombie()){
    cout << "Error: cannot read file!!!" << endl;
    exit(1);
  }

  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);

  TCanvas *c = new TCanvas("c", "", 800, 600);    // Canvas
  c->cd();

  if(MapHistogram.size()!=0){
    cout << "WARNING  :    MapHistogram is not empty!!!" << endl;
  }
  else{

    for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){
    for(Int_t i_pt=0; i_pt<NUM_PT_BIN; i_pt++){
    for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){
      TString name = flavour[i_flav] + ptBin[i_pt] + etaBin[i_eta];
      MapHistogram[name] = (TH1F*)inputFile->Get(name);
      cout << ">> FitHistogram  :    " << name << "  is loaded" << endl;
      MapHistogram[name+TString("_pt_dist")] = (TH1F*)inputFile->Get(name+TString("_pt_dist"));
      cout << ">> FitHistogram  :    " << name+TString("_pt_dist") << "  is loaded" << endl;
      MapHistogram[name+TString("_corr_diff")] = (TH1F*)inputFile->Get(name+TString("_corr_diff"));
      cout << ">> FitHistogram  :    " << name+TString("_corr_diff") << "  is loaded" << endl;
    }
    }
    } // end of nested for
  }

  Double_t ptMean[NUM_FLAVOUR][NUM_ETA_BIN][NUM_PT_BIN], ptRMS[NUM_FLAVOUR][NUM_ETA_BIN][NUM_PT_BIN], corrDiffMean[NUM_FLAVOUR][NUM_ETA_BIN][NUM_PT_BIN], corrDiffRMS[NUM_FLAVOUR][NUM_ETA_BIN][NUM_PT_BIN];

  for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){
  for(Int_t i_pt=0; i_pt<NUM_PT_BIN; i_pt++){
  for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){

    TString name = flavour[i_flav] + ptBin[i_pt] + etaBin[i_eta];
    TString name_pt_dist = name + TString("_pt_dist");
    TString name_corr_diff = name + TString("_corr_diff");

    ptMean[i_flav][i_eta][i_pt] = MapHistogram[name_pt_dist]->GetMean();
    ptRMS[i_flav][i_eta][i_pt] = MapHistogram[name_pt_dist]->GetRMS();
    corrDiffMean[i_flav][i_eta][i_pt] = MapHistogram[name_corr_diff]->GetMean();
    corrDiffRMS[i_flav][i_eta][i_pt] = MapHistogram[name_corr_diff]->GetRMS();
  }
  }
  } // end of nested for

  TString format;
  //format = "png";
  format = "pdf";

  for(Int_t i_flav=0; i_flav<NUM_FLAVOUR; i_flav++){
  for(Int_t i_eta=0; i_eta<NUM_ETA_BIN; i_eta++){
    TString graph_name = flavour[i_flav] + etaBin[i_eta] + TString("_corr_diff");

    MapGraphErrors[graph_name] = new TGraphErrors(NUM_PT_BIN,ptMean[i_flav][i_eta],corrDiffMean[i_flav][i_eta],ptRMS[i_flav][i_eta],corrDiffRMS[i_flav][i_eta]);
    MapGraphErrors[graph_name]->Draw();

    TString save_dir = base_dir;
    if(format=="png")
      save_dir+="output/png/Fitting_Histogram_Error/";
    else
      save_dir+="output/pdf/Fitting_Histogram_Error/";

    save_dir+=type;
    save_dir+="/";
    save_dir+=graph_name;
    if(format=="png")
      save_dir+=".png";
    else
      save_dir+=".pdf";
 
    c->SaveAs(save_dir);
    c->Clear();
  }
  } // end of nested for
  

} // end of function
*/

void Fitting_Histogram::SaveFitParameter(ofstream &fout_, TString name,
                                         Double_t meanPt, Double_t rmsPt,
                                         Double_t mean, Double_t mean_error,
                                         Double_t sigma, Double_t sigma_error){

  fout_ << name << "\t\t" << 
           meanPt << "\t\t" << rmsPt << "\t\t" << 
           mean  << "\t\t" << mean_error << "\t\t" <<
           sigma << "\t\t" << sigma_error << endl;

} // end of function

