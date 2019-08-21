#include "LeptonSFs.h"

using namespace std;

// destructor
LeptonSFs::~LeptonSFs(){

}

map<TString, TString> LeptonSFs::muon_IDname_key_map = {
   {"POGTight",             "NUM_TightID_DEN_genTracks"},
};

map<TString, map<TString, TString>> LeptonSFs::muon_ISOname_key_map = {
   {"TightIso", {{"POGTight", "NUM_TightRelIso_DEN_TightIDandIPCut"}, } },
};

map<TString, map<TString, vector<TString>>> LeptonSFs::muon_TRIGname_key_map = {
    {"IsoMu27",  {{"POGTight", {"IsoMu27_POGTight"}}, {"POGMedium", {"IsoMu27_POGMedium"}} } } ,
};


// constructor
LeptonSFs::LeptonSFs(LeptonType leptonType, const unsigned int nLepton, const TString idName, const TString isoName, const TString trigName){

    // set lepton type
    if( leptonType == LeptonType::electron || leptonType == LeptonType::muon ){
        leptonType_ = leptonType;

        if(leptonType_ == LeptonType::electron)
            leptonName = "electron";
        if(leptonType_ == LeptonType::muon)
            leptonName = "muon";
    }
    else{
        cout << "LeptonSFs: LeptonType::electron or LeptonType::muon allowd" << endl;
        exit (EXIT_FAILURE);
    }

    // set number of leptons
    if( nLepton <= 2 && nLepton > 0 ){
        nLepton_ = nLepton;
        if(nLepton_ == 1)
            strLeptonN = "single";
        if(nLepton_ == 2)
            strLeptonN = "double";
    }
    else{
        cout << "set LeptonSFs.nLepton_ <= 2 and LeptonSFs.nLepton_ > 0" << endl;
        exit (EXIT_FAILURE);
    }

    // set lepton Id, Iso, Trig name and its key
    if( leptonType_ == LeptonType::muon ){

        TString fullIdIsoName;
        idName_ = idName;
        isoName_ = isoName;

        idName_key[idName_]= muon_IDname_key_map[idName_];
        isoName_key[isoName_] = muon_ISOname_key_map[isoName_][idName_];

        trigName_ = trigName;

        if (isoName_ != NULL)
            fullIdIsoName = idName_+"With"+isoName_;
        else 
            fullIdIsoName = idName;

        unsigned int trig_key_size = muon_TRIGname_key_map[trigName_][idName_].size();
        for(unsigned int ikey = 0; ikey < trig_key_size; ikey++){
            trigName_key[trigName_].push_back(muon_TRIGname_key_map[trigName_][idName_].at(ikey));
        }
        // make branch names
        outIdBranchName   = leptonName + "_" + strLeptonN + "_idSF_" + fullIdIsoName;
        outIsoBranchName   = leptonName + "_" + strLeptonN + "_isoSF_" + fullIdIsoName;
        outTrigBranchName = leptonName + "_" + strLeptonN + "_trigSF_" + trigName_ + "_" + fullIdIsoName;

        cout << "name check id: " << outIdBranchName << endl;
        cout << "name check trig: " << outTrigBranchName << endl;
    }

}

void LeptonSFs::resetSFs(){
    recoSF = 1.;
    idSF = 1.;
    isoSF = 1.;
    trigSF = 1.;
    additionalSF = 1.;
}

void LeptonSFs::setAnalyzerParameter(AnalyzerParameter & param){


    param.Lepton_ID     = idName_;
    param.Lepton_ISO_ID = isoName_;
    param.Lepton_TRIGGER = trigName_;
    
    // set keys
    param.Lepton_ID_SF_Key = idName_key[idName_];
    param.Lepton_ISO_SF_Key = isoName_key[isoName_];
    
    for(unsigned int l = 0; l < trigName_key[trigName_].size(); l++){
              (param.Lepton_Trigger_map)[trigName_].push_back(trigName_key[trigName_].at(l));
    }

}

void LeptonSFs::setBranchForSFs(TTree *tree){

    tree->Branch(outIdBranchName, &idSF);
    tree->Branch(outIsoBranchName, &isoSF);
    tree->Branch(outTrigBranchName, &trigSF);

}

void LeptonSFs::setIDSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        idSF = sf;
    } 
}

void LeptonSFs::setISOSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        isoSF = sf;
    }
}

void LeptonSFs::setTriggerSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        trigSF = sf;
    }
}

unsigned int LeptonSFs::getNLeptons(){
    return nLepton_;
}
