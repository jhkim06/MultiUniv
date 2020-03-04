// binning definition for pt
TUnfoldBinning* ptBinningRec = NULL;
TUnfoldBinning* ptBinningGen = NULL;

// binning definition for mass
TUnfoldBinning* massBinningRec = NULL;
TUnfoldBinning* massBinningGen = NULL;

// for pt,mass 2D histogram bins 
const int nptbin_fine=17;
double ptbin_fine[nptbin_fine+1]={0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 35., 45., 55., 65., 75., 85., 100.};
// {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 32., 37., 43., 50., 60., 72., 85., 100.} // 28 bins
// {0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 37., 50., 72., 100.} // 14 bins
// {0., 4., 8., 12., 18., 28., 50., 100.} // 7 bins
//
// {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 16., 18., 20., 22., 25., 28., 31., 34., 37., 40., 43., 46., 50., 55., 60., 65., 70., 75., 80., 85., 90., 100.} // 36 bins
// {0., 2., 4., 6., 8., 10., 12., 14., 18., 22., 28., 34., 40., 46., 55., 65., 75., 85., 100.} // 18 bins
// {0., 4., 8., 12., 18., 28., 40., 55., 75., 100.} // 9 bins

const int nptbin_wide=9;
double ptbin_wide[nptbin_wide+1]={0., 4., 8., 12., 18., 28., 40., 55., 75., 100.};

const int nmassbin_forPt = 5;
const Double_t massbin_forPt_muon[nmassbin_forPt+1] =     {40,60,80,100,200,350};
const Double_t massbin_forPt_electron[nmassbin_forPt+1] = {50,65,80,100,200,350};

const int nmassbin_forPt_preFSR = 10;
const Double_t massbin_forPt_preFSR[nmassbin_forPt_preFSR+1] = {50,60,70,80,90,100,110,150,200,300,350};

const int nptbin_forMass = 1;
const Double_t ptbin_forMass[nptbin_forMass+1] = {0,100};

// for mass 1D histogram bins
const int nmassbin_fine_muon = 58;
const int nmassbin_wide_muon = 29;
const Double_t massbin_fine_muon[nmassbin_fine_muon+1] =     {40,42.5,45,47.5,50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350};
const Double_t massbin_wide_muon[nmassbin_wide_muon+1] =     {40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350};

const int nmassbin_fine_electron = 54;
const int nmassbin_wide_electron = 27;
const Double_t massbin_fine_electron[nmassbin_fine_electron+1] = {50,52.5,55,57.5,60,62.5,65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115,117.5,120,123,126,129.5,133,137,141,145.5,150,155,160,165.5,171,178,185,192.5,200,209,218,229,240,254,268,284,300,325,350};
const Double_t massbin_wide_electron[nmassbin_wide_electron+1] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,126,133,141,150,160,171,185,200,218,240,268,300,350};


// set bin definitions
void SetPtBinningRec(TString channel = "electron"){

 ptBinningRec= new TUnfoldBinning("Rec_Pt");
 ptBinningRec->AddAxis("pt",nptbin_fine,ptbin_fine,false,true);
 if( channel.CompareTo("electron") == 0 ) ptBinningRec->AddAxis("mass", nmassbin_forPt, massbin_forPt_electron, true, true);
 if( channel.CompareTo("muon") == 0 )     ptBinningRec->AddAxis("mass", nmassbin_forPt, massbin_forPt_muon, true, true);
}

void SetPtBinningGen(TString channel = "electron"){

 ptBinningGen=(new TUnfoldBinning("Gen_Pt"));
 ptBinningGen->AddAxis("pt",nptbin_wide,ptbin_wide,false,true);
 if( channel.CompareTo("electron") == 0 ) ptBinningGen->AddAxis("mass", nmassbin_forPt, massbin_forPt_electron, true, true);
 if( channel.CompareTo("muon") == 0 )     ptBinningGen->AddAxis("mass", nmassbin_forPt, massbin_forPt_muon, true, true);
}

void SetMassBinningRec(TString channel = "electron"){

 massBinningRec=(new TUnfoldBinning("Rec_Mass"));
 if( channel.CompareTo("electron") == 0 ) massBinningRec->AddAxis("mass", nmassbin_fine_electron, massbin_fine_electron, true, true);
 if( channel.CompareTo("muon") == 0 )     massBinningRec->AddAxis("mass", nmassbin_fine_muon,     massbin_fine_muon, true, true);
 massBinningRec->AddAxis("pt", nptbin_forMass,  ptbin_forMass, false, true);
}

void SetMassBinningGen(TString channel = "electron"){

 massBinningGen=(new TUnfoldBinning("Gen_Mass"));
 if( channel.CompareTo("electron") == 0 ) massBinningGen->AddAxis("mass", nmassbin_wide_electron, massbin_wide_electron, true, true);
 if( channel.CompareTo("muon") == 0 )     massBinningGen->AddAxis("mass", nmassbin_wide_muon,     massbin_wide_muon,     true, true);
 massBinningGen->AddAxis("pt", nptbin_forMass,  ptbin_forMass, false, true);
}

/////////////////// functions to be used in the TTree::Draw() ////////////////////////////////////
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



