#include "ABCDNormalizationEstimator.h"

ABCDNormalizationEstimator::ABCDNormalizationEstimator() : 
IgnoreNoHist(false),
HasLooseLepton(false)
{

}

void ABCDNormalizationEstimator::ReadHistograms(){

  TString datapath = getenv("DATA_DIR");
  datapath = datapath+"/"+TString::Itoa(DataYear,10)+"/ABCDNormalization/";

  string elline;
  ifstream in(datapath+"/histmap_Electron.txt");
  while(getline(in,elline)){
    std::istringstream is( elline );
    TString a,b,c,d,e;
    is >> a; // <ID>
    is >> b; // <rootfilename>
    is >> c; // <histogram type> TH1D or TH2D
    TFile *file = new TFile(datapath+"/"+b);
    TList *histlist = file->GetListOfKeys();
    for(int i=0;i<histlist->Capacity();i++){
      TString this_frname = histlist->At(i)->GetName();
      if(c=="TH2D")
        map_hist_Electron_2D[a+"_"+this_frname] = (TH2D *)file->Get(this_frname);
      else if(c=="TH1D"){
        map_hist_Electron_1D[a+"_"+this_frname] = (TH1D *)file->Get(this_frname);
      }
      else{
        cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] map_hist_Electron_2D : " << a+"_"+this_frname << "   type:" << c  << endl;
        exit(EXIT_FAILURE);
      }
      //cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] map_hist_Electron_2D : " << a+"_"+this_frname << endl;
    }
  }

  string elline2;
  ifstream in2(datapath+"/histmap_Muon.txt");
  while(getline(in2,elline2)){
    std::istringstream is( elline2 );
    TString a,b,c,d,e;
    is >> a; // <ID>
    is >> b; // <rootfilename>
    is >> c; // <histogram type> TH1D or TH2D
    TFile *file = new TFile(datapath+"/"+b);
    TList *histlist = file->GetListOfKeys();
    for(int i=0;i<histlist->Capacity();i++){
      TString this_frname = histlist->At(i)->GetName();
      if(c=="TH2D")
        map_hist_Muon_2D[a+"_"+this_frname] = (TH2D *)file->Get(this_frname);
      else if(c=="TH1D"){
        map_hist_Muon_1D[a+"_"+this_frname] = (TH1D *)file->Get(this_frname);
      }
      else{
        cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] map_hist_Muon_2D : " << a+"_"+this_frname << "   type:" << c  << endl;
        exit(EXIT_FAILURE);
      }
      //cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] map_hist_Muon_2D : " << a+"_"+this_frname << endl;
    }
  }

}

ABCDNormalizationEstimator::~ABCDNormalizationEstimator(){

}

void ABCDNormalizationEstimator::SetDataYear(int i){
  DataYear = i;
}

double ABCDNormalizationEstimator::GetElectronABCDNormalization_1D(TString ID, TString key, double sceta, int stat){

  //cout << "[ABCDNormalizationEstimator::GetElectronABCDNormalization_1D] ID = " << ID << ", key = " << key << endl;
  //cout << "[ABCDNormalizationEstimator::GetElectronABCDNormalization_1D] sceta = " << sceta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  sceta = fabs(sceta);

  if(sceta>=2.5) sceta = 2.49;

  std::map< TString, TH1D* >::const_iterator mapit;
  mapit = map_hist_Electron_1D.find(ID+"_"+key);

  if(mapit==map_hist_Electron_1D.end()){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[ABCDNormalizationEstimator::GetElectronABCDNormalization_1D] No"<< ID+"_"+key <<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = (mapit->second)->FindBin(sceta);
  value = (mapit->second)->GetBinContent(this_bin);
  error = (mapit->second)->GetBinError(this_bin);

  //cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] value = " << value << endl;

  return value+double(stat)*error;

}

double ABCDNormalizationEstimator::GetMuonABCDNormalization_1D(TString ID, TString key, double eta, int stat){

  //cout << "[ABCDNormalizationEstimator::GetMuonABCDNormalization_1D] ID = " << ID << ", key = " << key << endl;
  //cout << "[ABCDNormalizationEstimator::GetMuonABCDNormalization_1D] eta = " << eta << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  eta = fabs(eta);

  if(eta>=2.4) eta = 2.39;

  std::map< TString, TH1D* >::const_iterator mapit;
  mapit = map_hist_Muon_1D.find(ID+"_"+key);

  if(mapit==map_hist_Muon_1D.end()){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[ABCDNormalizationEstimator::GetMuonABCDNormalization_1D] No"<< ID+"_"+key <<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = (mapit->second)->FindBin(eta);
  value = (mapit->second)->GetBinContent(this_bin);
  error = (mapit->second)->GetBinError(this_bin);

  //cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] value = " << value << endl;

  return value+double(stat)*error;

}

double ABCDNormalizationEstimator::GetElectronABCDNormalization_2D(TString ID, TString key, double mass, double pt, int stat){

  //cout << "[ABCDNormalizationEstimator::GetElectronABCDNormalization_2D] ID = " << ID << ", key = " << key << endl;
  //cout << "[ABCDNormalizationEstimator::GetElectronABCDNormalization_2D] mass = " << mass << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  mass = fabs(mass);
  //bin for ISR
  //massbin={50, 65, 80, 100, 200, 350}
  //ptbin={0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.}
  if(pt>=100) pt = 99; //FIXME: pt cut ?
  if(mass>=350) mass = 349; //FIXME: mass cut ?

  std::map< TString, TH2D* >::const_iterator mapit;
  mapit = map_hist_Electron_2D.find(ID+"_"+key);

  if(mapit==map_hist_Electron_2D.end()){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[ABCDNormalizationEstimator::GetElectronABCDNormalization_2D] No"<< ID+"_"+key <<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = (mapit->second)->FindBin(mass,pt);
  value = (mapit->second)->GetBinContent(this_bin);
  error = (mapit->second)->GetBinError(this_bin);

  //cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] value = " << value << endl;

  return value+double(stat)*error;

}

double ABCDNormalizationEstimator::GetMuonABCDNormalization_2D(TString ID, TString key, double mass, double pt, int stat){

  //cout << "[ABCDNormalizationEstimator::GetMuonABCDNormalization_2D] ID = " << ID << ", key = " << key << endl;
  //cout << "[ABCDNormalizationEstimator::GetMuonABCDNormalization_2D] mass = " << mass << ", pt = " << pt << endl;

  double value = 1.;
  double error = 0.;

  mass = fabs(mass);
  //bin for ISR
  //massbin={50, 65, 80, 100, 200, 350}
  //ptbin={0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.}
  if(pt>=100) pt = 99;
  if(mass>=350) mass = 349;

  std::map< TString, TH2D* >::const_iterator mapit;
  mapit = map_hist_Muon_2D.find(ID+"_"+key);

  if(mapit==map_hist_Muon_2D.end()){
    if(IgnoreNoHist) return 1.;
    else{
      cout << "[ABCDNormalizationEstimator::GetMuonABCDNormalization_2D] No"<< ID+"_"+key <<endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = (mapit->second)->FindBin(mass,pt);
  value = (mapit->second)->GetBinContent(this_bin);
  error = (mapit->second)->GetBinError(this_bin);

  //cout << "[ABCDNormalizationEstimator::ABCDNormalizationEstimator] value = " << value << endl;

  return value+double(stat)*error;

}

