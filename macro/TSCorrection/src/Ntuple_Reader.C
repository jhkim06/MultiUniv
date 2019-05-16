#include "Ntuple_Reader.h"

Ntuple_Reader::Ntuple_Reader(){

  base_dir = std::getenv("TSCorrWD");

  Read_Files();
  Read_Variables();
} // end of function


Ntuple_Reader::~Ntuple_Reader(){

  for(map<TString,TFile*>::iterator it=MapTFile.begin(); it!=MapTFile.end(); it++){
    delete it->second;
  }
  for(map<TString,TNtuple*>::iterator it=MapTNtuple.begin(); it!=MapTNtuple.end(); it++){
    delete it->second;
  }

} // end of function


void Ntuple_Reader::Read_Files(){

  TString fname;
  fname = std::getenv("TSCorrInputTextDir");
  fname += "root_file_list.txt";

  TString input_root_dir = std::getenv("TSCorrInputRootDir");
  ifstream reader(fname);
  if(reader.is_open()){
    TString name, dir, able;
    while(reader >> name >> dir >> able){
      /*
      cout << "  >> Ntuple_Reader::Read_Files ,  "
           << name << "\t\t"
           << dir << "\t\t"
           << able << "\t\t" << endl; */
      if(able=="disable") continue;
      MapTFile[name] = new TFile(input_root_dir + dir,"READ");
      MapTNtuple[name] = (TNtuple*)MapTFile[name]->Get("TSCorr_tree");
      if(MapTFile[name]->IsZombie()){
        cout << "  Error  :    Ntuple_Reader::Read_Files ,    " << name << " is not opened!" << endl;
        exit(1);
      }
    }
  }
  else{
    cout << "  Error  :    Ntuple_Reader::Read_Files ,    file is not opened!" << endl;
    exit(1);
  }

} // end of function


void Ntuple_Reader::Read_Variables(){

  if(MapTNtuple.empty()){
    cout << " Error  :    Ntuple_Reader::Read_Variables ,    MapTNtuple is empty!" << endl;
    exit(1);
  }

  for(map<TString,TNtuple*>::iterator mapit=MapTNtuple.begin(); mapit!=MapTNtuple.end(); mapit++){
    if(!mapit->second){
      cout << " Ntuple_Reader::Read_Variables ,    " << mapit->first << "   is an NULL pointer!" << endl;
      exit(1);
    }

    //obj. reco
    mapit->second->SetBranchAddress("b_jet_from_top",&b_jet_from_top);
    mapit->second->SetBranchAddress("b_jet_from_anti_top",&b_jet_from_anti_top);
    mapit->second->SetBranchAddress("down_type_jet_from_w_ch",&down_type_jet_from_w_ch);
    mapit->second->SetBranchAddress("up_type_jet_from_w_ch",&up_type_jet_from_w_ch);
    mapit->second->SetBranchAddress("lepton",&lepton);
    mapit->second->SetBranchAddress("METv",&METv);
    //obj. truth
    mapit->second->SetBranchAddress("b_parton_from_top",&b_parton_from_top);
    mapit->second->SetBranchAddress("b_parton_from_anti_top",&b_parton_from_anti_top);
    mapit->second->SetBranchAddress("down_type_parton_from_w_ch",&down_type_parton_from_w_ch);
    mapit->second->SetBranchAddress("up_type_parton_from_w_ch",&up_type_parton_from_w_ch);
    mapit->second->SetBranchAddress("down_type_parton_flavour",&down_type_parton_flavour);
    mapit->second->SetBranchAddress("up_type_parton_flavour",&up_type_parton_flavour);


  } // end of for
 
} // end of function

