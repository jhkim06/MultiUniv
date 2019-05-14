#ifndef Ntuple_Reader_H
#define Ntuple_Reader_H

#include "stdio.h"
#include <iostream>
#include <fstream>
#include <map>

#include "TString.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TLorentzVector.h"

using namespace std;

class Ntuple_Reader{

  public:
    Ntuple_Reader();
    ~Ntuple_Reader();


  protected:
    TString base_dir;
   
    map<TString,TFile*> MapTFile;
    map<TString,TNtuple*> MapTNtuple;


    void Read_Files();
    void Read_Variables();

    //obj. reco
    TLorentzVector *b_jet_from_top;
    TLorentzVector *b_jet_from_anti_top;
    TLorentzVector *down_type_jet_from_w_ch;
    TLorentzVector *up_type_jet_from_w_ch;
    TLorentzVector *lepton;
    TLorentzVector *METv;

    //obj. truth
    TLorentzVector *b_parton_from_top;
    TLorentzVector *b_parton_from_anti_top;
    TLorentzVector *down_type_parton_from_w_ch;
    TLorentzVector *up_type_parton_from_w_ch;
    TLorentzVector *neutrino;

    int down_type_parton_flavour;
    int up_type_parton_flavour;

};
#endif
