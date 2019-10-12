#include "FakeBackgroundEstimator.h"

FakeBackgroundEstimator::FakeBackgroundEstimator() : 
IgnoreNoHist(false),
HasLooseLepton(false)
{

  histDir = TDirectoryHelper::GetTempDirectory("FakeBackgroundEstimator");

}

void FakeBackgroundEstimator::ReadHistograms(){

  TString datapath = getenv("DATA_DIR");
  datapath = datapath+"/"+TString::Itoa(DataYear,10)+"/FakeRate/";

  TDirectory* origDir = gDirectory;

  string elline;
  ifstream in(datapath+"/histmap_Electron.txt");
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString a,b,c,d,e;
    is >> a; // <ID>
    is >> b; // <rootfilename>
    TFile *file = new TFile(datapath+"/"+b);
    TList *histlist = file->GetListOfKeys();
    for(int i=0;i<histlist->Capacity();i++){
      TString this_frname = histlist->At(i)->GetName();
      histDir->cd();
      map_hist_Electron[a+"_"+this_frname] = (TH2D *)file->Get(this_frname)->Clone();
      file->Close();
      delete file;
      origDir->cd();
      //cout << "[FakeBackgroundEstimator::FakeBackgroundEstimator] map_hist_Electron : " << a+"_"+this_frname << endl;
    }
  }

  string elline2;
  ifstream in2(datapath+"/histmap_Muon.txt");
  while(getline(in2,elline2)){
    std::istringstream is( elline2 );
    TString a,b,c,d,e;
    is >> a; // <ID>
    is >> b; // <rootfilename>
    TFile *file = new TFile(datapath+"/"+b);
    TList *histlist = file->GetListOfKeys();
    for(int i=0;i<histlist->Capacity();i++){
      TString this_frname = histlist->At(i)->GetName();
      histDir->cd();
      map_hist_Muon[a+"_"+this_frname] = (TH2D *)file->Get(this_frname)->Clone();
      file->Close();
      delete file;
      origDir->cd();
      //cout << "[FakeBackgroundEstimator::FakeBackgroundEstimator] map_hist_Muon : " << a+"_"+this_frname << endl;
    }
  }

}

FakeBackgroundEstimator::~FakeBackgroundEstimator(){

}

void FakeBackgroundEstimator::SetDataYear(int i){
  DataYear = i;
}

double FakeBackgroundEstimator::GetElectronFakeRate(TString ID, TString key, double eta, double pt, int sys){

  //cout << "[FakeBackgroundEstimator::GetElectronFakeRate] ID = " << ID << ", key = " << key << endl;
  //cout << "[FakeBackgroundEstimator::GetElectronFakeRate] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

//  if(pt>=200) pt = 199;
//  if(eta>=2.5) eta = 2.49;
  if(pt>=60) pt = 59;
  //==== HOTFIX FIXME
//  if(eta>=1.479 && pt>=150) pt = 149.;

  std::map< TString, TH2D* >::const_iterator mapit;
  mapit = map_hist_Electron.find(ID+"_"+key);

  if(mapit==map_hist_Electron.end()){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[FakeBackgroundEstimator::GetElectronFakeRate] No"<< ID+"_"+key <<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = (mapit->second)->FindBin(pt,eta);
  value = (mapit->second)->GetBinContent(this_bin);
  error = (mapit->second)->GetBinError(this_bin);

  //cout << "[FakeBackgroundEstimator::FakeBackgroundEstimator] value = " << value << endl;

  return value+double(sys)*error;

}

double FakeBackgroundEstimator::GetMuonFakeRate(TString ID, TString key, double eta, double pt, int sys){

  //cout << "[FakeBackgroundEstimator::GetMuonFakeRate] ID = " << ID << ", key = " << key << endl;
  //cout << "[FakeBackgroundEstimator::GetMuonFakeRate] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

//  if(pt>=200) pt = 199;
//  if(eta>=2.5) eta = 2.49;
  if(pt>=60) pt = 59;
  //==== HOTFIX FIXME
//  if(eta<0.8 && pt>=150) pt = 149.;

  std::map< TString, TH2D* >::const_iterator mapit;
  mapit = map_hist_Muon.find(ID+"_"+key);

  if(mapit==map_hist_Muon.end()){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[FakeBackgroundEstimator::GetMuonFakeRate] No"<< ID+"_"+key <<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = (mapit->second)->FindBin(pt,eta);
  value = (mapit->second)->GetBinContent(this_bin);
  error = (mapit->second)->GetBinError(this_bin);

  //cout << "[FakeBackgroundEstimator::FakeBackgroundEstimator] value = " << value << endl;

  return value+double(sys)*error;

}

double FakeBackgroundEstimator::GetWeight(vector<Lepton *> lepptrs, AnalyzerParameter param, int sys, bool prompt_one){

    double this_weight = -1.;
    // assume prompt ratio = 1
    if(prompt_one){
        vector<double> FRs;
        for(unsigned int i=0; i<lepptrs.size(); i++){
             
            double this_fr = -999.;
        
            if(lepptrs.at(i)->LeptonFlavour()==Lepton::ELECTRON){
        
              Electron *el = (Electron *)( lepptrs.at(i) );
              if( el->PassID(param.Electron_Tight_ID) ) continue;
        
              double this_pt = el->Pt();
              if(param.Electron_UsePtCone) this_pt = el->PtCone();
              this_fr = GetElectronFakeRate(param.Electron_FR_ID, param.Electron_FR_Key, fabs(el->scEta()), this_pt, sys);
        
              this_weight *= -1.*this_fr/(1.-this_fr);
        
              FRs.push_back(this_fr);
            }
            else{
        
              Muon *mu = (Muon *)( lepptrs.at(i) );
              if( mu->PassID(param.Muon_Tight_ID) ) continue;
        
              double this_pt = mu->Pt();
              if(param.Muon_UsePtCone) this_pt = mu->PtCone();
              this_fr = GetMuonFakeRate(param.Muon_FR_ID, param.Muon_FR_Key, fabs(mu->Eta()), this_pt, sys);
        
              this_weight *= -1.*this_fr/(1.-this_fr);
        
              FRs.push_back(this_fr);
            }
        }
        
        /*
          for(unsigned int i=0; i<FRs.size(); i++){
            cout << FRs.at(i) << endl;
          }
        */
        
        if(FRs.size()==0){
          HasLooseLepton = false;
          return 0;
        }
        else{
          HasLooseLepton = true;
          return this_weight;
        }
    }
    // 
    else{
        cout << "calculate fake weight witout assumption p=1..." << endl;
        int nTight = 0;
        int tightLepton_index = -1;
        double weight_fp = 0;
        double weight_ff = 0; 
        vector<double> lepton_fake_ratio, lepton_prompt_ratio;

        double prompt_ratio = 0.95;
        // count number of tight leptons and save its index
        for(unsigned int i=0; i<lepptrs.size(); i++){

            if(lepptrs.at(i)->LeptonFlavour()==Lepton::ELECTRON){
            
                Electron *el = (Electron *)( lepptrs.at(i) );
                if( el->PassID(param.Electron_Tight_ID) ){
                    nTight++;
                    tightLepton_index = i;
                }
                double this_pt = el->Pt();
                if(param.Electron_UsePtCone) this_pt = el->PtCone();
                lepton_fake_ratio.push_back(GetElectronFakeRate(param.Electron_FR_ID, param.Electron_FR_Key, fabs(el->scEta()), this_pt, sys));
                lepton_prompt_ratio.push_back(prompt_ratio);
            }
            else{
                
                Muon *mu = (Muon *)( lepptrs.at(i) );
                if( mu->PassID(param.Muon_Tight_ID) ){
                    nTight++;
                    tightLepton_index = i;
                }
                double this_pt = mu->Pt();
                if(param.Muon_UsePtCone) this_pt = mu->PtCone();
                lepton_fake_ratio.push_back(GetMuonFakeRate(param.Muon_FR_ID, param.Muon_FR_Key, fabs(mu->Eta()), this_pt, sys));
                lepton_prompt_ratio.push_back(prompt_ratio);
            }
        }// lepton loop

        double global_factor1 = 0., global_factor2 = 0.;
        double global_factor = 0.;
        // outside the braket
        global_factor1 = 1./(lepton_prompt_ratio.at(0)-lepton_fake_ratio.at(0));
        global_factor2 = 1./(lepton_prompt_ratio.at(1)-lepton_fake_ratio.at(1));
        global_factor = global_factor1 * global_factor2;

        if(nTight == 0){
            double weight_fp1 = 0., weight_fp2 = 0.;
            double fake_ratio = 0., prompt_ratio = 0.;

            // inside the braket
            fake_ratio   = lepton_fake_ratio.at(0);
            prompt_ratio = lepton_prompt_ratio.at(1);
            weight_fp1 = (-1.*(fake_ratio*prompt_ratio))*fake_ratio*prompt_ratio; 

            fake_ratio   = lepton_fake_ratio.at(1);
            prompt_ratio = lepton_prompt_ratio.at(0);
            weight_fp2 = (-1.*(fake_ratio*prompt_ratio))*fake_ratio*prompt_ratio; 

            weight_fp = weight_fp1 + weight_fp2;
            weight_ff = ((lepton_prompt_ratio.at(0)*lepton_prompt_ratio.at(1)))*lepton_fake_ratio.at(0)*lepton_fake_ratio.at(1);
        }
        else if(nTight == 1){
            double fake_ratio = 0., prompt_ratio = 0.;
            double one_minus_fake_ratio = 0., one_minus_prompt_ratio = 0.;
            int looseLepton_index = -1;
            if(tightLepton_index == 0 ) looseLepton_index = 1; 
            else looseLepton_index = 0;

            // inside the braket
            fake_ratio   = lepton_fake_ratio.at(looseLepton_index);
            prompt_ratio = lepton_prompt_ratio.at(looseLepton_index);
            one_minus_fake_ratio   = 1.-lepton_fake_ratio.at(tightLepton_index);
            one_minus_prompt_ratio = 1.-lepton_prompt_ratio.at(tightLepton_index);

            weight_fp = (fake_ratio*one_minus_prompt_ratio + prompt_ratio*one_minus_fake_ratio)*fake_ratio*prompt_ratio; 
            weight_ff = (-1.*prompt_ratio*one_minus_prompt_ratio)*lepton_fake_ratio.at(0)*lepton_fake_ratio.at(1);
        }
        else if(nTight == 2){

            double weight_fp1 = 0., weight_fp2 = 0.;
            double one_minus_fake_ratio = 0., one_minus_prompt_ratio = 0.;

            // inside the braket
            one_minus_fake_ratio   = 1.-lepton_fake_ratio.at(0);
            one_minus_prompt_ratio = 1.-lepton_prompt_ratio.at(1);
            weight_fp1 = (-1.*(one_minus_fake_ratio*one_minus_prompt_ratio))*lepton_fake_ratio.at(0)*lepton_prompt_ratio.at(1);

            one_minus_fake_ratio   = 1.-lepton_fake_ratio.at(1);
            one_minus_prompt_ratio = 1.-lepton_prompt_ratio.at(0);
            weight_fp2 = (-1.*(one_minus_fake_ratio*one_minus_prompt_ratio))*lepton_fake_ratio.at(1)*lepton_prompt_ratio.at(0);

            weight_fp = weight_fp1 + weight_fp2; 
            weight_ff = ((1.-lepton_prompt_ratio.at(1))*(1.-lepton_prompt_ratio.at(0)))*lepton_fake_ratio.at(0)*lepton_fake_ratio.at(1);
            weight_fp = 0.;
            weight_ff = 0.;
        }
        else{
            cout << "[FakeBackgroundEstimator::GetElectronFakeRate] Check total number of leptons equals 2"<<endl;
            exit(EXIT_FAILURE);
        }
    //cout << "number of passing tight id: " << nTight << endl;
    //cout << "weight_fp: " << weight_fp << " weight_ff: " << weight_ff << " global_factor: " << global_factor << endl;
    return global_factor * ( weight_fp + weight_ff); 
    }

}

