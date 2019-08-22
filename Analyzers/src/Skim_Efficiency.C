#include "Skim_Efficiency.h"

void Skim_Efficiency::initializeAnalyzer(){

  // initializeAnalyzerTools();
  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  cout << "initializeAnalyzer" << endl;

  if(DataYear==2016){
        muonWPs.push_back(new LeptonSFs(LeptonType::muon, 2, "POGTight", "TightIso", "DoubleMuon", 2016));
        muonWPs.push_back(new LeptonSFs(LeptonType::muon, 1, "POGTight", "TightIso", "IsoMu24", 2016));

        electronWPs.push_back(new LeptonSFs(LeptonType::electron, 2, "passMediumID", "", "DoubleElectron", 2016));
  }
  else if(DataYear==2017){
        muonWPs.push_back(new LeptonSFs(LeptonType::muon, 2, "POGTight", "TightIso", "IsoMu27", 2017));
  }
  else if(DataYear==2018){
        muonWPs.push_back(new LeptonSFs(LeptonType::muon, 2, "POGTight", "TightIso", "IsoMu24", 2018));
  }

  for(unsigned int iWP= 0; iWP < muonWPs.size(); iWP++){
    muonWPs.at(iWP)->setBranchForSFs(newtree);
  }

  for(unsigned int iWP= 0; iWP < electronWPs.size(); iWP++){
    electronWPs.at(iWP)->setBranchForSFs(newtree);
  }
}

void Skim_Efficiency::executeEvent(){
 
  AnalyzerParameter param; // TODO make EfficiencyParameter class

  for(unsigned int iWP= 0; iWP < muonWPs.size(); iWP++){
    muonWPs.at(iWP)->resetSFs();
    muonWPs.at(iWP)->setAnalyzerParameter(param);
    executeEventFromParameter(param, iWP);
    param.Clear();
  }

  for(unsigned int iWP= 0; iWP < electronWPs.size(); iWP++){
    electronWPs.at(iWP)->resetSFs();
    electronWPs.at(iWP)->setAnalyzerParameter(param);
    executeEventFromParameter(param, iWP, false);
    param.Clear();
  }


  newtree->Fill();

  return;

}


void Skim_Efficiency::executeEventFromParameter(AnalyzerParameter param, unsigned int ithWP, bool isMu){

  evt = new Event;
  *evt = GetEvent();

  vector<Muon> this_AllMuons = GetAllMuons(); 
  vector<Electron> this_AllElectrons = GetAllElectrons(); 

  if(param.syst_ == AnalyzerParameter::Central){ }

  vector<Muon>     muons;
  vector<Electron> electrons;
  std::vector<Lepton*> leps;

  // get leptons with desired ID, Iso, Trigger
  if(isMu){
    muons = SelectMuons(this_AllMuons, param.Lepton_ID+"With"+param.Lepton_ISO_ID, 7., 2.4);
    std::sort(muons.begin(), muons.end(),PtComparing);
    leps=MakeLeptonPointerVector(muons);
    
    LeptonReco_SF = NULL;
    LeptonID_SF   =&MCCorrection::MuonID_SF;
    LeptonISO_SF  =&MCCorrection::MuonISO_SF;
    LeptonTrg_SF = &MCCorrection::MuonTrigger_SF;
  }

  if(!isMu){
    electrons = SelectElectrons(this_AllElectrons, param.Lepton_ID, 7., 2.5);
    std::sort(electrons.begin(), electrons.end(),PtComparing);
    leps=MakeLeptonPointerVector(electrons);

    LeptonReco_SF = &MCCorrection::ElectronReco_SF;
    LeptonID_SF   = &MCCorrection::ElectronID_SF;
    LeptonTrg_SF  = NULL;
    LeptonISO_SF  = NULL;
  }

  Double_t total_RECOSF = 1.;
  Double_t total_IDSF = 1.;
  Double_t total_ISOSF = 1.;
  Double_t total_TRGSF = 1.;

  if(!IsDATA){

    unsigned int requiredLeptonSize;
    if(isMu) requiredLeptonSize = muonWPs.at(ithWP)->getNLeptons();
    else requiredLeptonSize = electronWPs.at(ithWP)->getNLeptons();

    if(requiredLeptonSize <= leps.size()){
        // trigger first
        // check wheter it is single or double trigger by counting the number of trigger keys
        unsigned int nKeys = param.Lepton_Trigger_map[param.Lepton_TRIGGER].size();
        
        if(nKeys == 1){
            if(isMu){ // TODO update for single electron triggers
                unsigned int ikey = 0;
                std::vector<Muon> temp_muon;
                temp_muon.push_back((*(Muon*)leps.at(ikey))); 
                // get SFs using uncorrected lepton inside the MuonTrigger_SF 
                // for single muon trigger
                Double_t temp_trgSF = LeptonTrg_SF?(mcCorr->*LeptonTrg_SF)(param.Lepton_ID, param.Lepton_TRIGGER, temp_muon,  0) : 1.;
                total_TRGSF *= temp_trgSF;
            }
        }
       
        // for double muon trigger 
        if(nKeys == 2){
            Double_t temp_trgSF = mcCorr->DiLeptonTrg_SF(param.Lepton_Trigger_map[param.Lepton_TRIGGER].at(0), param.Lepton_Trigger_map[param.Lepton_TRIGGER].at(1), leps, 0);
            if(!(temp_trgSF > 10.)) total_TRGSF *= temp_trgSF; // just to avoid to save meaninglessly huge numbers...
        }
      
        // now Id, Iso 
        for( unsigned int i(0); i< requiredLeptonSize; i++){

       	    if(isMu){
                // ID SF
                Double_t tempIDSF = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                total_IDSF *= tempIDSF;
                
                // Iso SF
                Double_t tempISOSF = LeptonISO_SF?(mcCorr->*LeptonISO_SF)(param.Lepton_ISO_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                total_ISOSF *= tempISOSF;
       	    }

            if(!isMu){
                // ID SF
                Double_t tempIDSF = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                total_IDSF *= tempIDSF;

                Double_t tempRECOSF = LeptonReco_SF?(mcCorr->*LeptonReco_SF)(((Electron*)leps.at(i))->scEta(), leps.at(i)->Pt(),  0) : 1.;
                total_RECOSF *= tempRECOSF;

            }

        }// loop over leptons passing ID

    }// check if number of selected leptons > 0
  }// for MC

  if(isMu){
    muonWPs.at(ithWP)->setTriggerSF(total_TRGSF, SysUpDown::Central);
    muonWPs.at(ithWP)->setRECOSF(total_RECOSF, SysUpDown::Central);
    muonWPs.at(ithWP)->setIDSF(total_IDSF, SysUpDown::Central);
    muonWPs.at(ithWP)->setISOSF(total_ISOSF, SysUpDown::Central);
  }
  else{
    electronWPs.at(ithWP)->setTriggerSF(total_TRGSF, SysUpDown::Central);
    electronWPs.at(ithWP)->setRECOSF(total_RECOSF, SysUpDown::Central);
    electronWPs.at(ithWP)->setIDSF(total_IDSF, SysUpDown::Central);
    electronWPs.at(ithWP)->setISOSF(total_ISOSF, SysUpDown::Central);
  }

  this_AllMuons.clear();
  this_AllElectrons.clear(); 

  delete evt;
}

Skim_Efficiency::Skim_Efficiency(){

}

Skim_Efficiency::~Skim_Efficiency(){

}

void Skim_Efficiency::WriteHist(){

  newtree->AutoSave();
  outfile->cd();

  for(std::map< TString, TH1D* >::iterator mapit = maphist_TH1D.begin(); mapit!=maphist_TH1D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
  }
  for(std::map< TString, TH2D* >::iterator mapit = maphist_TH2D.begin(); mapit!=maphist_TH2D.end(); mapit++){
    TString this_fullname=mapit->second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_suffix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);
    mapit->second->Write(this_name);
  }

  outfile->cd();
  for(std::map< TString, std::map<TString, TH1D*> >::iterator mapit=JSmaphist_TH1D.begin(); mapit!=JSmaphist_TH1D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH1D* > this_maphist = mapit->second;


    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH1D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }

  for(std::map< TString, std::map<TString, TH2D*> >::iterator mapit=JSmaphist_TH2D.begin(); mapit!=JSmaphist_TH2D.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TH2D* > this_maphist = mapit->second;

    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TH2D* >::iterator mapit = this_maphist.begin(); mapit!=this_maphist.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }

}

