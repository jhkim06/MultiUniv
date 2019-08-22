#include "LeptonSFs.h"

using namespace std;

// destructor
LeptonSFs::~LeptonSFs(){

}

/////////////////////////////////////////// 2016 Lepton SF info ///////////////////////////////////////////////////////////////////
/////////////////////////////////////// electron ////////////////////////////////////////////////////////////////
map<TString, TString> LeptonSFs::electron_2016_IDname_key_map = {
   {"passMediumID",             "passMediumID"},
};

map<TString, map<TString, vector<TString>>> LeptonSFs::electron_2016_TRIGname_key_map = {
    {"DoubleElectron",  {{"passMediumID", {"LeadEle23_MediumID","TailEle12_MediumID"}}, } } ,
};

//////////////////////////////////////// muon //////////////////////////////////////////////////////////////////
map<TString, TString> LeptonSFs::muon_2016_IDname_key_map = {
   {"POGTight",             "NUM_TightID_DEN_genTracks"},
};

map<TString, map<TString, TString>> LeptonSFs::muon_2016_ISOname_key_map = {
   {"TightIso", {{"POGTight", "NUM_TightRelIso_DEN_TightIDandIPCut"}, } },
};

map<TString, map<TString, vector<TString>>> LeptonSFs::muon_2016_TRIGname_key_map = {
    {"DoubleMuon",  {{"POGTight", {"Lead17_POGTight","Tail8_POGTight"}}, } } ,
    {"IsoMu24",  {{"POGTight", {"IsoMu24_POGTight"}}, } } ,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// End of 2016 ///////////////////////////////////////////////////////////////////

// 2017 muon
map<TString, TString> LeptonSFs::muon_IDname_key_map = {
   {"POGTight",             "NUM_TightID_DEN_genTracks"},
};

map<TString, map<TString, TString>> LeptonSFs::muon_ISOname_key_map = {
   {"TightIso", {{"POGTight", "NUM_TightRelIso_DEN_TightIDandIPCut"}, } },
};

map<TString, map<TString, vector<TString>>> LeptonSFs::muon_TRIGname_key_map = {
    {"IsoMu24",  {{"POGTight", {"IsoMu24_POGTight"}}, } } ,
};




// constructor
LeptonSFs::LeptonSFs(LeptonType leptonType, const unsigned int nLepton, const TString idName, const TString isoName, const TString trigName, unsigned int dataYear){

    TString fullIdIsoName;
    dataYear_ = dataYear;
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
        idName_ = idName;
        isoName_ = isoName;

        if(dataYear == 2016){
            idName_key[idName_]= muon_2016_IDname_key_map[idName_];
            isoName_key[isoName_] = muon_2016_ISOname_key_map[isoName_][idName_];
        }

        trigName_ = trigName;

        if (isoName_ != "")
            fullIdIsoName = idName_+"With"+isoName_;
        else 
            fullIdIsoName = idName;

        if(dataYear == 2016){
            unsigned int trig_key_size = muon_2016_TRIGname_key_map[trigName_][idName_].size();
            for(unsigned int ikey = 0; ikey < trig_key_size; ikey++){
                trigName_key[trigName_].push_back(muon_2016_TRIGname_key_map[trigName_][idName_].at(ikey));
            }
        }
    }

    if( leptonType_ == LeptonType::electron ){
        idName_ = idName;
        isoName_ = isoName;

        if(dataYear == 2016){
            idName_key[idName_]= electron_2016_IDname_key_map[idName_];
        }

        trigName_ = trigName;

        if (isoName_ != "") // TODO check how names are defined for ID with seperated isolation condition
            fullIdIsoName = idName_+"With"+isoName_;
        else
            fullIdIsoName = idName;

        if(dataYear == 2016){
            unsigned int trig_key_size = electron_2016_TRIGname_key_map[trigName_][idName_].size();
            for(unsigned int ikey = 0; ikey < trig_key_size; ikey++){
                trigName_key[trigName_].push_back(electron_2016_TRIGname_key_map[trigName_][idName_].at(ikey));
            }
        }
    }


    // make branch names
    outRecoBranchName   = leptonName + "_" + strLeptonN + "_recoSF_" + fullIdIsoName;
    outIdBranchName   = leptonName + "_" + strLeptonN + "_idSF_" + fullIdIsoName;
    outIsoBranchName   = leptonName + "_" + strLeptonN + "_isoSF_" + fullIdIsoName;
    outTrigBranchName = leptonName + "_" + strLeptonN + "_trigSF_" + trigName_ + "_" + fullIdIsoName;

    cout << "name check id: " << outIdBranchName << endl;
    cout << "name check trig: " << outTrigBranchName << endl;


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

    tree->Branch(outRecoBranchName, &recoSF);
    tree->Branch(outIdBranchName, &idSF);
    tree->Branch(outIsoBranchName, &isoSF);
    tree->Branch(outTrigBranchName, &trigSF);

}

void LeptonSFs::setRECOSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        recoSF = sf; 
    }   
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
