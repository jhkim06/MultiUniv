// binning definition for pt
TUnfoldBinning* ptBinningRec = NULL;
TUnfoldBinning* ptBinningGen = NULL;

// binning definition for mass
TUnfoldBinning* massBinningRec = NULL;
TUnfoldBinning* massBinningGen = NULL;

// {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 50., 60., 72., 85., 100.} // 28 bins
// {0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 37., 50., 72., 100.} // 14 bins
// {0., 4., 8., 12., 18., 28., 50., 100.} // 7 bins
//
// {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 31., 34., 37., 40., 43., 46., 50., 55., 60., 65., 70., 75., 80., 85., 90., 100.} // 36 bins
// {0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 34., 40., 46., 55., 65., 75., 85., 100.} // 18 bins
// {0., 4., 8., 12., 18., 28., 40., 55., 75., 100.} // 9 bins

const int nptBinFine=17;
double ptBinFine[nptBinFine+1]={0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.};

const int nptBinCoarse=9;
double ptBinCoarse[nptBinCoarse+1]={0., 4., 8., 12., 18., 28., 40., 55., 75., 100.};

const int nptBinZptWeight=22;
double ptBinZptWeight[nptBinZptWeight+1]={0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 35, 42, 50, 60, 72, 85, 100};

const int nMassBinforPt_electron = 5;
const int nMassBinforPt_muon = 5;
const Double_t massBinforPt_muon[nMassBinforPt_muon+1] = {40, 64, 81, 101, 200, 320};
const Double_t massBinforPt_electron[nMassBinforPt_electron+1] = {50, 64, 81, 101, 200, 320};

const int nMassBinZptWeightforPt_electron = 3;
const int nMassBinZptWeightforPt_muon = 3;
const Double_t massBinZptWeightforPt_muon[nMassBinZptWeightforPt_muon+1] = {40, 81, 101, 320};
const Double_t massBinZptWeightforPt_electron[nMassBinZptWeightforPt_electron+1] = {50, 81, 101, 320};

const int nptBin_forMass = 1;
const Double_t ptBin_forMass[nptBin_forMass+1] = {0,100};

// for mass 1D histogram bins
const int nMassBinFine_muon = 58;
const int nMassBinCoarse_muon = 29;
const Double_t massBinFine_muon[nMassBinFine_muon+1] = {40,42.5,45,47.5,50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350};
const Double_t massBinCoarse_muon[nMassBinCoarse_muon+1] = {40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350};

const int nMassBinFine_electron = 54;
const int nMassBinCoarse_electron = 27;
const Double_t massBinFine_electron[nMassBinFine_electron+1] = {50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350};
const Double_t massBinCoarse_electron[nMassBinCoarse_electron+1] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350};

//const int nMassBin = 41;
//const Double_t massBin[nMassBin+1] = {15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510, 600, 700, 830, 1000};
const int nMassBin = 34;
const Double_t massBin[nMassBin+1] = {15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76, 81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141, 150, 160, 171, 185, 200, 220, 243, 273, 320};

// Set bin definitions
// For momentum unfold
void SetPtBinningRec(std::pair<TString, TString>& binDef)
{

    // Create TUnfoldBinning object
    ptBinningRec= new TUnfoldBinning("Rec_Pt");

    if(binDef.second == "CoarseCoarse")
    {
        ptBinningRec->AddAxis("pt",nptBinCoarse,ptBinCoarse,false,true);
        if( binDef.first == "electron") ptBinningRec->AddAxis("mass", nMassBinforPt_electron, massBinforPt_electron, true, true);
        if( binDef.first == "muon")     ptBinningRec->AddAxis("mass", nMassBinforPt_muon, massBinforPt_muon, true, true);
    }
    else if(binDef.second == "FineCoarse")
    {
        //
        ptBinningRec->AddAxis("pt",nptBinFine,ptBinFine,false,true);
        if( binDef.first == "electron") ptBinningRec->AddAxis("mass", nMassBinforPt_electron, massBinforPt_electron, true, true);
        if( binDef.first == "muon")     ptBinningRec->AddAxis("mass", nMassBinforPt_muon, massBinforPt_muon, true, true);
    }
    else if(binDef.second == "FineFine")
    {
        //
        ptBinningRec->AddAxis("pt",nptBinFine,ptBinFine,false,true);
        if( binDef.first == "electron") ptBinningRec->AddAxis("mass", nMassBinforPt_electron, massBinforPt_electron, true, true);
        if( binDef.first == "muon")     ptBinningRec->AddAxis("mass", nMassBinforPt_muon, massBinforPt_muon, true, true);
    }
    else if(binDef.second == "ZptWeight")
    {
        //
        ptBinningRec->AddAxis("pt",nptBinZptWeight,ptBinZptWeight,false,false);
        if( binDef.first == "electron") ptBinningRec->AddAxis("mass", nMassBinZptWeightforPt_electron, massBinZptWeightforPt_electron, false, false);
        if( binDef.first == "muon")     ptBinningRec->AddAxis("mass", nMassBinZptWeightforPt_muon, massBinZptWeightforPt_muon, false, false);
    }
    else
    {
        //
    }
}

void SetPtBinningGen(std::pair<TString, TString>& binDef)
{

    // Create TUnfoldBinning object
    ptBinningGen=(new TUnfoldBinning("Gen_Pt"));

    if(binDef.second == "CoarseCoarse")
    {
        ptBinningGen->AddAxis("pt",nptBinCoarse,ptBinCoarse,false, true);
        if( binDef.first == "electron") ptBinningGen->AddAxis("mass", nMassBinforPt_electron,massBinforPt_electron, true, true);
        if( binDef.first == "muon")     ptBinningGen->AddAxis("mass", nMassBinforPt_muon,massBinforPt_muon, true, true);
    }
    else if(binDef.second == "FineCoarse")
    {
        //
        ptBinningGen->AddAxis("pt",nptBinCoarse,ptBinCoarse,false, true);
        if( binDef.first == "electron") ptBinningGen->AddAxis("mass", nMassBinforPt_electron,massBinforPt_electron, true, true);
        if( binDef.first == "muon")     ptBinningGen->AddAxis("mass", nMassBinforPt_muon,massBinforPt_muon, true, true);
    }
    else if(binDef.second == "FineFine")
    {
        //
        ptBinningGen->AddAxis("pt",nptBinFine,ptBinFine,false, true);
        if( binDef.first == "electron") ptBinningGen->AddAxis("mass", nMassBinforPt_electron,massBinforPt_electron, true, true);
        if( binDef.first == "muon")     ptBinningGen->AddAxis("mass", nMassBinforPt_muon,massBinforPt_muon, true, true);
    }
    else
    {
        //
    }
}

// For mass unfold
void SetMassBinningRec()
{

    massBinningRec=(new TUnfoldBinning("Rec_Mass"));

    //if( channel.CompareTo("electron") == 0 ) massBinningRec->AddAxis("mass", nMassBin, massBin, true, true);
    //if( channel.CompareTo("muon") == 0 )     massBinningRec->AddAxis("mass", nMassBin, massBin, true, true);
    massBinningRec->AddAxis("mass", nMassBin, massBin, true, true);
    massBinningRec->AddAxis("pt", nptBin_forMass,  ptBin_forMass, false, true);
}

void SetMassBinningGen()
{

 massBinningGen=(new TUnfoldBinning("Gen_Mass"));

 //if( channel.CompareTo("electron") == 0 ) massBinningGen->AddAxis("mass", nMassBin, massBin, true, true);
 //if( channel.CompareTo("muon") == 0 )     massBinningGen->AddAxis("mass", nMassBin, massBin, true, true);
 massBinningGen->AddAxis("mass", nMassBin, massBin, true, true);
 massBinningGen->AddAxis("pt", nptBin_forMass,  ptBin_forMass, false, true);
}

/*------------------------------ functions to be used in the TTree::Draw() -----------------------------------*/
// create histograms 
TH1* get2DHistogramPtRec(TString hname){

    return ptBinningRec->CreateHistogram(hname);
}

TH2* getMigrationMforPt(TString hname){

    return TUnfoldBinning::CreateHistogramOfMigrations(ptBinningGen, ptBinningRec, hname);
}

TH1* get2DHistogramMassRec(TString hname){

    return massBinningRec->CreateHistogram(hname);
}

TH2* getMigrationMforMass(TString hname){

    return TUnfoldBinning::CreateHistogramOfMigrations(massBinningGen, massBinningRec, hname);
}

TH1* get2DHistogramPtGen(TString hname){

    return ptBinningGen->CreateHistogram(hname);
}

TH2* getFSRMigrationMforPt(TString hname){

    return TUnfoldBinning::CreateHistogramOfMigrations(ptBinningGen, ptBinningGen, hname);
}

TH1* get2DHistogramMassGen(TString hname){

    return massBinningGen->CreateHistogram(hname);
}

TH2* getFSRMigrationMforMass(TString hname){

    return TUnfoldBinning::CreateHistogramOfMigrations(massBinningGen, massBinningGen, hname);
}

// get bin index
double Get2DPtGenBinIndex(double pt = -999, double mass = -999.){

    return ptBinningGen->GetGlobalBinNumber(pt,mass);
}

double Get2DMassGenBinIndex(double mass = -999., double pt = -999){

    return massBinningGen->GetGlobalBinNumber(mass, pt);
}

double Get2DPtRecBinIndex(double pt = -999, double mass = -999.){

    return ptBinningRec->GetGlobalBinNumber(pt,mass);
}

double Get2DMassRecBinIndex(double mass = -999., double pt = -999){

    return massBinningRec->GetGlobalBinNumber(mass, pt);
}

void ClearUnfoldBins(){

 delete ptBinningRec;
 delete ptBinningGen;

 delete massBinningRec;
 delete massBinningGen;

}



