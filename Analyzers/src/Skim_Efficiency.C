#include "Skim_Efficiency.h"

void Skim_Efficiency::initializeAnalyzer(){

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  cout << "initializeAnalyzer" << endl;

  if(DataYear==2016){
        muonWPs.push_back(new LeptonSFs(LeptonType::muon, 2, "POGTight", "TightIso", "DoubleMuon", 2016, ""));
        electronWPs.push_back(new LeptonSFs(LeptonType::electron, 2, "passMediumID", "", "DoubleElectron", 2016, "DZfilter"));
  }
  else if(DataYear==2017){
        muonWPs.push_back(new LeptonSFs(LeptonType::muon, 2, "POGTight", "TightIso", "DoubleMuon", 2017));
        electronWPs.push_back(new LeptonSFs(LeptonType::electron, 2, "passMediumID", "", "DoubleElectron", 2017, ""));
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

  Double_t total_RECOSF = 1.,     total_RECOSFUp = 1.,     total_RECOSFDn = 1.;
  Double_t total_IDSF = 1.,       total_IDSFUp = 1.,       total_IDSFDn = 1.;
  Double_t total_ISOSF = 1.,      total_ISOSFUp = 1.,      total_ISOSFDn = 1.;
  Double_t total_TRGSF = 1.,      total_TRGSFUp = 1.,      total_TRGSFDn = 1.;
  Double_t total_EXTRATRGSF = 1., total_EXTRATRGSFUp = 1., total_EXTRATRGSFDn = 1.;

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
            Double_t temp_trgSFUp = mcCorr->DiLeptonTrg_SF(param.Lepton_Trigger_map[param.Lepton_TRIGGER].at(0), param.Lepton_Trigger_map[param.Lepton_TRIGGER].at(1), leps, 1);
            Double_t temp_trgSFDn = mcCorr->DiLeptonTrg_SF(param.Lepton_Trigger_map[param.Lepton_TRIGGER].at(0), param.Lepton_Trigger_map[param.Lepton_TRIGGER].at(1), leps, -1);
            if(!(temp_trgSF > 10.)) total_TRGSF *= temp_trgSF; // just to avoid saving meaninglessly huge numbers...
            if(!(temp_trgSFUp > 10.)) total_TRGSFUp *= temp_trgSFUp; // just to avoid saving meaninglessly huge numbers...
            if(!(temp_trgSFDn > 10.)) total_TRGSFDn *= temp_trgSFDn; // just to avoid saving meaninglessly huge numbers...

            if(param.Lepton_EXTRATRG_SF_Key != "" && !isMu){
                total_EXTRATRGSF *= mcCorr->ElectronDZfilter_SF(param.Lepton_EXTRATRG_SF_Key, leps, nPV, 0);
                total_EXTRATRGSFUp *= mcCorr->ElectronDZfilter_SF(param.Lepton_EXTRATRG_SF_Key, leps, nPV, 1);
                total_EXTRATRGSFDn *= mcCorr->ElectronDZfilter_SF(param.Lepton_EXTRATRG_SF_Key, leps, nPV, -1);
            }
        }
      
        // now Id, Iso 
        for( unsigned int i(0); i< requiredLeptonSize; i++){

       	    if(isMu){
                // ID SF
                Double_t tempIDSF = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                Double_t tempIDSFUp = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  1) : 1.;
                Double_t tempIDSFDn = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  -1) : 1.;
                total_IDSF *= tempIDSF;
                total_IDSFUp *= tempIDSFUp;
                total_IDSFDn *= tempIDSFDn;
                
                // Iso SF
                Double_t tempISOSF = LeptonISO_SF?(mcCorr->*LeptonISO_SF)(param.Lepton_ISO_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                Double_t tempISOSFUp = LeptonISO_SF?(mcCorr->*LeptonISO_SF)(param.Lepton_ISO_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  1) : 1.;
                Double_t tempISOSFDn = LeptonISO_SF?(mcCorr->*LeptonISO_SF)(param.Lepton_ISO_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  -1) : 1.;
                total_ISOSF *= tempISOSF;
                total_ISOSFUp *= tempISOSFUp;
                total_ISOSFDn *= tempISOSFDn;
       	    }

            if(!isMu){
                // ID SF
                Double_t tempIDSF = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  0) : 1.;
                Double_t tempIDSFUp = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  1) : 1.;
                Double_t tempIDSFDn = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  -1) : 1.;
                total_IDSF *= tempIDSF;
                total_IDSFUp *= tempIDSFUp;
                total_IDSFDn *= tempIDSFDn;

                Double_t tempRECOSF = LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  0) : 1.;
                Double_t tempRECOSFUp = LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  1) : 1.;
                Double_t tempRECOSFDn = LeptonReco_SF?(mcCorr->*LeptonReco_SF)( ( (Electron*)leps.at(i) )->scEta(), leps.at(i)->Pt(),  -1) : 1.;
                total_RECOSF *= tempRECOSF;
                total_RECOSFUp *= tempRECOSFUp;
                total_RECOSFDn *= tempRECOSFDn;

            }

        }// loop over leptons passing ID

    }// check if number of selected leptons > 0
  }// for MC

  if(isMu){
    muonWPs.at(ithWP)->setTriggerSF(total_TRGSF, SysUpDown::Central);
    muonWPs.at(ithWP)->setRECOSF(total_RECOSF, SysUpDown::Central);
    muonWPs.at(ithWP)->setIDSF(total_IDSF, SysUpDown::Central);
    muonWPs.at(ithWP)->setISOSF(total_ISOSF, SysUpDown::Central);

    muonWPs.at(ithWP)->setTriggerSF(total_TRGSFUp, SysUpDown::Up);
    muonWPs.at(ithWP)->setRECOSF(total_RECOSFUp, SysUpDown::Up);
    muonWPs.at(ithWP)->setIDSF(total_IDSFUp, SysUpDown::Up);
    muonWPs.at(ithWP)->setISOSF(total_ISOSFUp, SysUpDown::Up);

    muonWPs.at(ithWP)->setTriggerSF(total_TRGSFDn, SysUpDown::Down);
    muonWPs.at(ithWP)->setRECOSF(total_RECOSFDn, SysUpDown::Down);
    muonWPs.at(ithWP)->setIDSF(total_IDSFDn, SysUpDown::Down);
    muonWPs.at(ithWP)->setISOSF(total_ISOSFDn, SysUpDown::Down);
  }
  else{
    electronWPs.at(ithWP)->setTriggerSF(total_TRGSF, SysUpDown::Central);
    electronWPs.at(ithWP)->setRECOSF(total_RECOSF, SysUpDown::Central);
    electronWPs.at(ithWP)->setIDSF(total_IDSF, SysUpDown::Central);
    electronWPs.at(ithWP)->setISOSF(total_ISOSF, SysUpDown::Central);

    electronWPs.at(ithWP)->setTriggerSF(total_TRGSFUp, SysUpDown::Up);
    electronWPs.at(ithWP)->setRECOSF(total_RECOSFUp, SysUpDown::Up);
    electronWPs.at(ithWP)->setIDSF(total_IDSFUp, SysUpDown::Up);
    electronWPs.at(ithWP)->setISOSF(total_ISOSFUp, SysUpDown::Up);

    electronWPs.at(ithWP)->setTriggerSF(total_TRGSFDn, SysUpDown::Down);
    electronWPs.at(ithWP)->setRECOSF(total_RECOSFDn, SysUpDown::Down);
    electronWPs.at(ithWP)->setIDSF(total_IDSFDn, SysUpDown::Down);
    electronWPs.at(ithWP)->setISOSF(total_ISOSFDn, SysUpDown::Down);

    if(param.Lepton_EXTRATRG_SF_Key != ""){
        electronWPs.at(ithWP)->setExtraTrigSF(total_EXTRATRGSF, SysUpDown::Central);
        electronWPs.at(ithWP)->setExtraTrigSF(total_EXTRATRGSFUp, SysUpDown::Up);
        electronWPs.at(ithWP)->setExtraTrigSF(total_EXTRATRGSFDn, SysUpDown::Down);
    }
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

