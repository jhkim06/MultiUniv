#include "Skim_Efficiency.h"

void Skim_Efficiency::initializeAnalyzer(){

  // initializeAnalyzerTools();
  // Skim_Efficiency just adds SFs for ID Iso Trigger (i.e., without skimming)
  // If there are leptons passing some ID, Iso or Trigger condition, it just calculate SFs for those leptons up to two leptons 
  // TODO add option to select 2016, 2017, and 2018, currently checked only for 2017

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  // ID ISO RECO TRG
  // ex)  IdSF_Nlep_1_ele_"POGTightID_TightISO_HLT_Ele27_WPTight_Gsf"_v_mu_"POGTightID_TightIso_HLT_IsoMu24_v"
  // ex) IsoSF_Nlep_1_ele_POGTightID_TightISO_HLT_Ele27_WPTight_Gsf_v_mu_POGTightID_TightIso_HLT_IsoMu24_v
  // ex) TrgSF_Nlep_1_ele_POGTightID_TightISO_HLT_Ele27_WPTight_Gsf_v_mu_POGTightID_TightIso_HLT_IsoMu24_v

  cout << "initializeAnalyzer" << endl;

  // set lepton selections: by ID
  muWPs["POGTight"]["Id"].push_back("POGTight");
  muWPs["POGTight"]["Iso"].push_back("TightIso");
  muWPs["POGTight"]["Iso"].push_back("LooseIso");
  muWPs["POGTight"]["Trigger"].push_back("IsoMu27");

  eleWPs["POGTight"]["Id"].push_back("passTightID");
  eleWPs["POGTight"]["Iso"].push_back("");
  eleWPs["POGTight"]["Iso"].push_back("LooseIso");
  eleWPs["POGTight"]["Trigger"].push_back("HLT_Ele27_WPTight_Gsf_v");

  muKEYs["POGTight"]["Id"].push_back("NUM_TightID_DEN_genTracks"); // TODO is there function to find keys for selection already? if not let's make it
  muKEYs["POGTight"]["Iso"].push_back("NUM_TightRelIso_DEN_TightIDandIPCut");
  muKEYs["POGTight"]["Iso"].push_back("NUM_LooseRelTkIso_DEN_HighPtIDandIPCut");
  muKEYs["POGTight"]["IsoMu27"].push_back("IsoMu27_POGTight");

  eleKEYs["POGTight"]["Id"].push_back("passTightID");
  eleKEYs["POGTight"]["Iso"].push_back("");
  eleKEYs["POGTight"]["Iso"].push_back("");
  eleKEYs["POGTight"]["HLT_Ele27_WPTight_Gsf_v"].push_back("NA");

  int nIso = muWPs["POGTight"]["Iso"].size();
  int nTrg = muWPs["POGTight"]["Trigger"].size();
  for(int i = 0; i < 4; i++){
  	for(int j = 0; j < nIso; j++){
       		if( i != 3){ 
       			newtree->Branch(SFs[i] + "_mu_" + "POGTight" + muWPs["POGTight"]["Iso"].at(j), 
       				        &lepSFs["POGTight" + muWPs["POGTight"]["Iso"].at(j)][SFs[i]]);
       		}
       		else if(i == 3){ // for trigger SF
       			for(int k = 0; k < nTrg; k++){
       				newtree->Branch(SFs[i] + "_" + muWPs["POGTight"]["Trigger"].at(k) + "_" + "mu_" + "POGTight" + muWPs["POGTight"]["Iso"].at(j), 
       					        &lepSFs["POGTight" + muWPs["POGTight"]["Iso"].at(j) + muWPs["POGTight"]["Trigger"].at(k)][SFs[i]]);
        	 	}
      		} 
       	// if i==3 i.e. trigger then specify trigger name in the branch
  	}
  }


}

void Skim_Efficiency::executeEvent(){
 
  AllMuons = GetAllMuons();
  AllElectrons = GetAllElectrons();

  AnalyzerParameter param; // TODO make EfficiencyParameter class

  //std::map<TString, std::map<TString,double>>::iterator it = evtSFs.begin();

  //
  int nIso = muWPs["POGTight"]["Iso"].size();
  for(int i = 0; i < nIso; i++){

        param.Muon_ID     = muWPs["POGTight"]["Id"].at(0);
        param.Muon_ISO_ID =     muWPs["POGTight"]["Iso"].at(i);
	//if(param.Muon_ISO_ID.CompareTo("NA") param.Muon_ID += "With" + param.Muon_ISO_ID;
   
        // set keys
        param.Muon_ID_SF_Key = muKEYs["POGTight"]["Id"].at(0);
        param.Muon_ISO_SF_Key = muKEYs["POGTight"]["Iso"].at(i);

	int nTrg = muWPs["POGTight"]["Trigger"].size();
	for(int j = 0; j < nTrg; j++){
        	for(int i = 0; i < muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(j)].size(); i++){
		        (param.Muon_Trigger_map)[muWPs["POGTight"]["Trigger"].at(j)].push_back(muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(j)].at(i));
        	}
	}
       	executeEventFromParameter(param);
       	param.Clear();

  }

  AllMuons.clear();
  AllElectrons.clear(); 

  newtree->Fill();

  return;

}


void Skim_Efficiency::executeEventFromParameter(AnalyzerParameter param){

  evt = new Event;
  *evt = GetEvent();

  vector<Muon> this_AllMuons = AllMuons; 
  vector<Electron> this_AllElectrons = AllElectrons; 

  if(param.syst_ == AnalyzerParameter::Central){ }

  vector<Muon> muons = SelectMuons(this_AllMuons, param.Muon_ID+"With"+param.Muon_ISO_ID, 7., 2.4);
  std::sort(muons.begin(), muons.end(),PtComparing);

  LeptonReco_SF = NULL;
  LeptonTrg_SF = &MCCorrection::MuonTrigger_SF;
  LeptonID_SF   =&MCCorrection::MuonID_SF;
  LeptonISO_SF  =&MCCorrection::MuonISO_SF;

  if(!IsDATA){

	lepSFs[param.Muon_ID+param.Muon_ISO_ID]["RecoSF"].clear();
	lepSFs[param.Muon_ID+param.Muon_ISO_ID]["IdSF"].clear();
	lepSFs[param.Muon_ID+param.Muon_ISO_ID]["IsoSF"].clear();
	std::map<TString, std::vector<TString>>::iterator it = param.Muon_Trigger_map.begin();
	while(it != param.Muon_Trigger_map.end()){
		lepSFs[param.Muon_ID+param.Muon_ISO_ID+it->first]["TrgSF"].clear();

		// check wheter it is single or double trigger by counting the number of trigger keys
		int nKeys = (it->second).size();
		if(nKeys == 1){ // single trigger
			if(muons.size() > 0){
				std::vector<Muon> temp_muon;
				temp_muon.push_back(muons.at(0));
				lepSFs[param.Muon_ID+param.Muon_ISO_ID+it->first]["TrgSF"].push_back( LeptonTrg_SF?(mcCorr->*LeptonTrg_SF)(param.Muon_ID, it->first, temp_muon,  0) : 1. ); 
			}
			else{
				lepSFs[param.Muon_ID+param.Muon_ISO_ID+it->first]["TrgSF"].push_back( 1.); 
			}
			//MCCorrection::MuonTrigger_Eff(TString ID, TString trig, int DataOrMC, double eta, double pt, int sys)
		}// single triger
		it++;
	}

    for( int i(0); i<muons.size() ; i++){

      lepSFs[param.Muon_ID+param.Muon_ISO_ID]["RecoSF"].push_back( LeptonReco_SF?(mcCorr->*LeptonReco_SF)(muons.at(i).Eta(), muons.at(i).Pt(),  0) : 1.);
      lepSFs[param.Muon_ID+param.Muon_ISO_ID]["IdSF"].push_back(LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Muon_ID_SF_Key, muons.at(i).Eta(), muons.at(i).Pt(),  0) : 1.);
      lepSFs[param.Muon_ID+param.Muon_ISO_ID]["IsoSF"].push_back(LeptonISO_SF?(mcCorr->*LeptonISO_SF)(param.Muon_ISO_SF_Key, muons.at(i).Eta(), muons.at(i).Pt(),  0) : 1.);
    }
    //trgSF      = mcCorr->DiLeptonTrg_SF(trgSF_key0, trgSF_key1, leps,  0);
  }

  delete evt;
}

Skim_Efficiency::Skim_Efficiency(){

}

Skim_Efficiency::~Skim_Efficiency(){

}

void Skim_Efficiency::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_Efficiency::initializeAnalyzer
  newtree->AutoSave();
  //newtree->Write();
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

