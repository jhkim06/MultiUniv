#include "Skim_Efficiency.h"

void Skim_Efficiency::initializeAnalyzer(){

  // initializeAnalyzerTools();

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  cout << "initializeAnalyzer" << endl;

  if(DataYear==2016){
  }
  else if(DataYear==2017){
        muonWPs =  new LeptonSFs(LeptonType::muon, 1, "POGTight", "TightIso", "IsoMu27");
        muonWPs->setBranchForSFs(newtree);
  }
  else if(DataYear==2018){
  }
}

void Skim_Efficiency::executeEvent(){
 
  AnalyzerParameter param; // TODO make EfficiencyParameter class

  muonWPs->resetSFs();
  muonWPs->setAnalyzerParameter(param);
  executeEventFromParameter(param);
  param.Clear();

  newtree->Fill();

  return;

}


void Skim_Efficiency::executeEventFromParameter(AnalyzerParameter param, bool isMu){

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

  if(!IsDATA){

    if(leps.size() > 0){
        // trigger first
        // check wheter it is single or double trigger by counting the number of trigger keys
        unsigned int nKeys = param.Lepton_Trigger_map[param.Lepton_TRIGGER].size();
        for(unsigned int ikey = 0; ikey < nKeys; ikey++){
            if(isMu){
            	std::vector<Muon> temp_muon;
            	temp_muon.push_back((*(Muon*)leps.at(ikey))); 

                // get SFs using uncorrected lepton inside the MuonTrigger_SF 
                Double_t temp_trgSF = LeptonTrg_SF?(mcCorr->*LeptonTrg_SF)(param.Lepton_ID, param.Lepton_TRIGGER, temp_muon,  0) : 1.;
                muonWPs->setTriggerSF(temp_trgSF, SysUpDown::Central);
            }
        }
       
        Double_t total_RECOSF = 1.;
        Double_t total_IDSF = 1.;
        Double_t total_ISOSF = 1.; 

        for( unsigned int i(0); i< muonWPs->getNLeptons(); i++){

       	    if(isMu){
                // ID SF
                Double_t tempIDSF = LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                total_IDSF *= tempIDSF;
                
                // Iso SF
                Double_t tempISOSF = LeptonISO_SF?(mcCorr->*LeptonISO_SF)(param.Lepton_ISO_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.;
                total_ISOSF *= tempISOSF;
       	    }
        }// loop over leptons passing ID

        muonWPs->setIDSF(total_IDSF, SysUpDown::Central);
        muonWPs->setISOSF(total_ISOSF, SysUpDown::Central);
    }// check if number of selected leptons > 0
  }// for MC

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

