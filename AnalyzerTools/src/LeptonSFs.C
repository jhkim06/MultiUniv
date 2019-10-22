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

map<TString, TString> LeptonSFs::electron_2016_Extraname_key_map = {
   {"DZfilter",             "DZfilter"},
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

// 2017 electron
map<TString, TString> LeptonSFs::electron_2017_IDname_key_map = {
   {"passMediumID",             "passMediumID"},
};

map<TString, map<TString, vector<TString>>> LeptonSFs::electron_2017_TRIGname_key_map = {
    {"DoubleElectron",  {{"passMediumID", {"LeadEle23_MediumID","TailEle12_MediumID"}}, } } ,
};

// 2017 muon
map<TString, TString> LeptonSFs::muon_2017_IDname_key_map = {
   {"POGTight",             "NUM_TightID_DEN_genTracks"},
};

map<TString, map<TString, TString>> LeptonSFs::muon_2017_ISOname_key_map = {
   {"TightIso", {{"POGTight", "NUM_TightRelIso_DEN_TightIDandIPCut"}, } },
};

map<TString, map<TString, vector<TString>>> LeptonSFs::muon_2017_TRIGname_key_map = {
    {"DoubleMuon",  {{"POGTight", {"LeadMu17_POGTight","TailMu8_POGTight"}}, } } ,
};

// 2018 electron
map<TString, TString> LeptonSFs::electron_2018_IDname_key_map = {
   {"passMediumID",             "passMediumID"},
};

map<TString, map<TString, vector<TString>>> LeptonSFs::electron_2018_TRIGname_key_map = {
    {"DoubleElectron",  {{"passMediumID", {"Default","Default"}}, } } ,
};

// 2018 muon
map<TString, TString> LeptonSFs::muon_2018_IDname_key_map = {
   {"POGTight",             "NUM_TightID_DEN_genTracks"},
};

map<TString, map<TString, TString>> LeptonSFs::muon_2018_ISOname_key_map = {
   {"TightIso", {{"POGTight", "NUM_TightRelIso_DEN_TightIDandIPCut"}, } },
};

map<TString, map<TString, vector<TString>>> LeptonSFs::muon_2018_TRIGname_key_map = {
    {"DoubleMuon",  {{"POGTight", {"Default","Default"}}, } } ,
};




LeptonSFs::LeptonSFs(LeptonType leptonType, const unsigned int nLepton, const TString idName, const TString isoName, const TString trigName, unsigned int dataYear, const TString extraTrigName): LeptonSFs(leptonType, nLepton, idName, isoName, trigName, dataYear){

    extraTrigName_ = extraTrigName;
    outExtraBranchName = leptonName + "_" + strLeptonN + "_extraTrigSF_" + fullIdIsoName;
    outExtraBranchName_up = leptonName + "_" + strLeptonN + "_extraTrigSFUp_" + fullIdIsoName;
    outExtraBranchName_down = leptonName + "_" + strLeptonN + "_extraTrigSFDn_" + fullIdIsoName;

    if( leptonType_ == LeptonType::electron ){

        if(dataYear == 2016){
            extraTrigName_key[extraTrigName_] = electron_2016_Extraname_key_map[extraTrigName_];
        }

    }

}

// constructor
LeptonSFs::LeptonSFs(LeptonType leptonType, const unsigned int nLepton, const TString idName, const TString isoName, const TString trigName, unsigned int dataYear): extraTrigName_("") {

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
        else if(dataYear == 2017){
            idName_key[idName_]= muon_2017_IDname_key_map[idName_];
            isoName_key[isoName_] = muon_2017_ISOname_key_map[isoName_][idName_];
        }
        else if(dataYear == 2018){
            idName_key[idName_]= muon_2018_IDname_key_map[idName_];
            isoName_key[isoName_] = muon_2018_ISOname_key_map[isoName_][idName_];
        }
        else{
            cout << "only 2016, 2017, 2018 currently" << endl;
            exit (EXIT_FAILURE);
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
        else if(dataYear == 2017){
            unsigned int trig_key_size = muon_2017_TRIGname_key_map[trigName_][idName_].size();
            for(unsigned int ikey = 0; ikey < trig_key_size; ikey++){
                trigName_key[trigName_].push_back(muon_2017_TRIGname_key_map[trigName_][idName_].at(ikey));
            }
        }
        else if(dataYear == 2018){
            unsigned int trig_key_size = muon_2018_TRIGname_key_map[trigName_][idName_].size();
            for(unsigned int ikey = 0; ikey < trig_key_size; ikey++){
                trigName_key[trigName_].push_back(muon_2018_TRIGname_key_map[trigName_][idName_].at(ikey));
            }
        }
        else{
            cout << "only 2016, 2017 currently" << endl;
            exit (EXIT_FAILURE);
        }
    }

    if( leptonType_ == LeptonType::electron ){
        idName_ = idName;
        isoName_ = isoName;

        if(dataYear == 2016){
            idName_key[idName_]= electron_2016_IDname_key_map[idName_];
        }
        else if(dataYear == 2017){
            idName_key[idName_]= electron_2017_IDname_key_map[idName_];
        }
        else if(dataYear == 2018){
            idName_key[idName_]= electron_2018_IDname_key_map[idName_];
        }
        else{
            cout << "only 2016, 2017, 2018 currently" << endl;
            exit (EXIT_FAILURE);
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
            extraTrigName_key[extraTrigName_] = electron_2016_Extraname_key_map[extraTrigName_];
        }
        else if(dataYear == 2017){
            unsigned int trig_key_size = electron_2017_TRIGname_key_map[trigName_][idName_].size();
            for(unsigned int ikey = 0; ikey < trig_key_size; ikey++){
                trigName_key[trigName_].push_back(electron_2017_TRIGname_key_map[trigName_][idName_].at(ikey));
            }
        }
        else if(dataYear == 2018){
            unsigned int trig_key_size = electron_2018_TRIGname_key_map[trigName_][idName_].size();
            for(unsigned int ikey = 0; ikey < trig_key_size; ikey++){
                trigName_key[trigName_].push_back(electron_2018_TRIGname_key_map[trigName_][idName_].at(ikey));
            }
        }
        else{
            cout << "only 2016, 2017, 2018 currently" << endl;
            exit (EXIT_FAILURE);

        }
        
    }


    // make branch names
    outRecoBranchName   = leptonName + "_" + strLeptonN + "_recoSF_" + fullIdIsoName;
    outRecoBranchName_up   = leptonName + "_" + strLeptonN + "_recoSFUp_" + fullIdIsoName;
    outRecoBranchName_down   = leptonName + "_" + strLeptonN + "_recoSFDn_" + fullIdIsoName;

    outIdBranchName   = leptonName + "_" + strLeptonN + "_idSF_" + fullIdIsoName;
    outIdBranchName_up   = leptonName + "_" + strLeptonN + "_idSFUp_" + fullIdIsoName;
    outIdBranchName_down   = leptonName + "_" + strLeptonN + "_idSFDn_" + fullIdIsoName;

    outIsoBranchName   = leptonName + "_" + strLeptonN + "_isoSF_" + fullIdIsoName;
    outIsoBranchName_up   = leptonName + "_" + strLeptonN + "_isoSFUp_" + fullIdIsoName;
    outIsoBranchName_down   = leptonName + "_" + strLeptonN + "_isoSFDn_" + fullIdIsoName;

    outTrigBranchName = leptonName + "_" + strLeptonN + "_trigSF_" + trigName_ + "_" + fullIdIsoName;
    outTrigBranchName_up = leptonName + "_" + strLeptonN + "_trigSFUp_" + trigName_ + "_" + fullIdIsoName;
    outTrigBranchName_down = leptonName + "_" + strLeptonN + "_trigSFDn_" + trigName_ + "_" + fullIdIsoName;

    cout << "name check id: " << outIdBranchName << endl;
    cout << "name check trig: " << outTrigBranchName << endl;
}

void LeptonSFs::resetSFs(){
    recoSF = 1.;
    recoSFUp = 1.;
    recoSFDown = 1.;
    idSF = 1.;
    idSFUp = 1.;
    idSFDown = 1.;
    isoSF = 1.;
    isoSFUp = 1.;
    isoSFDown = 1.;
    trigSF = 1.;
    trigSFUp = 1.;
    trigSFDown = 1.;
    extraTrigSF = 1.;
    extraTrigSFUp = 1.;
    extraTrigSFDown = 1.;
}

void LeptonSFs::setAnalyzerParameter(AnalyzerParameter & param){

    param.Lepton_ID     = idName_;
    param.Lepton_ISO_ID = isoName_;
    param.Lepton_TRIGGER = trigName_;
    param.Lepton_EXTRATRG = extraTrigName_;
    
    // set keys
    param.Lepton_ID_SF_Key = idName_key[idName_];
    param.Lepton_ISO_SF_Key = isoName_key[isoName_];
    param.Lepton_EXTRATRG_SF_Key = extraTrigName_key[extraTrigName_];
    if(extraTrigName_ != "") param.Lepton_EXTRATRG_SF_Key = extraTrigName_key[extraTrigName_];
    
    for(unsigned int l = 0; l < trigName_key[trigName_].size(); l++){
              (param.Lepton_Trigger_map)[trigName_].push_back(trigName_key[trigName_].at(l));
    }
}

void LeptonSFs::setBranchForSFs(TTree *tree){

    tree->Branch(outRecoBranchName, &recoSF);
    tree->Branch(outRecoBranchName_up, &recoSFUp);
    tree->Branch(outRecoBranchName_down, &recoSFDown);

    tree->Branch(outIdBranchName, &idSF);
    tree->Branch(outIdBranchName_up, &idSFUp);
    tree->Branch(outIdBranchName_down, &idSFDown);

    tree->Branch(outIsoBranchName, &isoSF);
    tree->Branch(outIsoBranchName_up, &isoSFUp);
    tree->Branch(outIsoBranchName_down, &isoSFDown);

    tree->Branch(outTrigBranchName, &trigSF);
    tree->Branch(outTrigBranchName_up, &trigSFUp);
    tree->Branch(outTrigBranchName_down, &trigSFDown);

    if(extraTrigName_ != ""){
        tree->Branch(outExtraBranchName, &extraTrigSF);
        tree->Branch(outExtraBranchName_up, &extraTrigSFUp);
        tree->Branch(outExtraBranchName_down, &extraTrigSFDown);
    }

}

void LeptonSFs::setRECOSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        recoSF = sf; 
    }
    else if (sys == SysUpDown::Up){
        recoSFUp = sf; 
    }
    else if (sys == SysUpDown::Down){
        recoSFDown = sf; 
    }
    else{
        cout << "LeptonSFs::setRECOSF only central, up, down allowed" << endl;
        exit (EXIT_FAILURE);
    } 
}

void LeptonSFs::setIDSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        idSF = sf;
    } 
    else if (sys == SysUpDown::Up){
        idSFUp = sf;
    }
    else if (sys == SysUpDown::Down){
        idSFDown = sf;
    }
    else{
        cout << "LeptonSFs::setIDSF only central, up, down allowed" << endl;
        exit (EXIT_FAILURE);
    }
}

void LeptonSFs::setISOSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        isoSF = sf;
    }
    else if (sys == SysUpDown::Up){
        isoSFUp = sf;
    }
    else if (sys == SysUpDown::Down){
        isoSFDown = sf;
    }
    else{
        cout << "LeptonSFs::setISOSF only central, up, down allowed" << endl;
        exit (EXIT_FAILURE);
    }
}

void LeptonSFs::setTriggerSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        trigSF = sf;
    }
    else if (sys == SysUpDown::Up){
        trigSFUp = sf;
    }
    else if (sys == SysUpDown::Down){
        trigSFDown = sf;
    }
    else{
        cout << "LeptonSFs::setTriggerSF only central, up, down allowed" << endl;
        exit (EXIT_FAILURE);
    }
}

void LeptonSFs::setExtraTrigSF(Double_t sf, SysUpDown sys){

    if(sys == SysUpDown::Central){
        extraTrigSF = sf;
    }
    else if (sys == SysUpDown::Up){
        extraTrigSFUp = sf;
    }
    else if (sys == SysUpDown::Down){
        extraTrigSFDown = sf;
    }
    else{
        cout << "LeptonSFs::setExtraTrigSF only central, up, down allowed" << endl;
        exit (EXIT_FAILURE);
    }
}

unsigned int LeptonSFs::getNLeptons(){
    return nLepton_;
}
