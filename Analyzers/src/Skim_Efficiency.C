#include "Skim_Efficiency.h"

void Skim_Efficiency::initializeAnalyzer(){

  // initializeAnalyzerTools();
  // Skim_Efficiency just adds SFs for ID Iso Trigger (i.e., without skimming)
  // If there are leptons passing some lepton ID  condition, it just calculate ID Iso Reco SFs for each leptons 
  // TODO add option to select 2016, 2017, and 2018, currently checked only for 2017

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  cout << "initializeAnalyzer" << endl;

  if(DataYear==2016){

        // muon
        muWPs["POGTight"]["Id"].push_back("POGTight"); // set name to be used to select muons
        muWPs["POGTight"]["Iso"].push_back("TightIso");
        muWPs["POGTight"]["Iso"].push_back("LooseIso");
        muWPs["POGTight"]["Trigger"].push_back("IsoMu24");
        muWPs["POGTight"]["Trigger"].push_back("IsoMu24_LooseIso");

        muKEYs["POGTight"]["Id"].push_back("NUM_TightID_DEN_genTracks"); // TODO is there function to find keys for selection already? if not let's make it
        muKEYs["POGTight"]["Iso"].push_back("NUM_TightRelIso_DEN_TightIDandIPCut");
        muKEYs["POGTight"]["Iso"].push_back("NUM_LooseRelTkIso_DEN_HighPtIDandIPCut");
        muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(0)].push_back("IsoMu24_POGTight");
        muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(1)].push_back("NA");

        // electron
        eleWPs["POGTight"]["Id"].push_back("passTightID");
        eleWPs["POGTight"]["Id"].push_back("passTightID_vetoIso");
        eleWPs["POGTight"]["Trigger"].push_back("HLT_Ele27_WPTight_Gsf");
        eleWPs["POGTight"]["Trigger"].push_back("HLT_Ele27_WPTight_Gsf_vetoIso");


        eleKEYs["POGTight"]["Id"].push_back("passTightID");
        eleKEYs["POGTight"]["Id"].push_back("NA");
        eleKEYs["POGTight"][eleWPs["POGTight"]["Trigger"].at(0)].push_back("NA");
        eleKEYs["POGTight"][eleWPs["POGTight"]["Trigger"].at(1)].push_back("NA");

  }
  else if(DataYear==2017){

	// muon
  	muWPs["POGTight"]["Id"].push_back("POGTight"); // set name to be used to select muons
  	muWPs["POGTight"]["Iso"].push_back("TightIso");
  	muWPs["POGTight"]["Iso"].push_back("LooseIso");
  	muWPs["POGTight"]["Trigger"].push_back("IsoMu27");
  	muWPs["POGTight"]["Trigger"].push_back("IsoMu27_LooseIso");

  	muKEYs["POGTight"]["Id"].push_back("NUM_TightID_DEN_genTracks"); // TODO is there function to find keys for selection already? if not let's make it
  	muKEYs["POGTight"]["Iso"].push_back("NUM_TightRelIso_DEN_TightIDandIPCut");
  	muKEYs["POGTight"]["Iso"].push_back("NUM_LooseRelTkIso_DEN_HighPtIDandIPCut");
  	muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(0)].push_back("IsoMu27_POGTight");
  	muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(1)].push_back("NA");

	// electron
  	eleWPs["POGTight"]["Id"].push_back("passTightID");
  	eleWPs["POGTight"]["Id"].push_back("passTightID_vetoIso");
  	eleWPs["POGTight"]["Trigger"].push_back("HLT_Ele27_WPTight_Gsf");
  	eleWPs["POGTight"]["Trigger"].push_back("HLT_Ele27_WPTight_Gsf_vetoIso");


  	eleKEYs["POGTight"]["Id"].push_back("passTightID");
  	eleKEYs["POGTight"]["Id"].push_back("NA");
  	eleKEYs["POGTight"][eleWPs["POGTight"]["Trigger"].at(0)].push_back("NA");
  	eleKEYs["POGTight"][eleWPs["POGTight"]["Trigger"].at(1)].push_back("NA");
  }
  else if(DataYear==2018){

        // muon
        muWPs["POGTight"]["Id"].push_back("POGTight"); // set name to be used to select muons
        muWPs["POGTight"]["Iso"].push_back("TightIso");
        muWPs["POGTight"]["Iso"].push_back("LooseIso");
        muWPs["POGTight"]["Trigger"].push_back("IsoMu24");
        muWPs["POGTight"]["Trigger"].push_back("IsoMu24_LooseIso");

        muKEYs["POGTight"]["Id"].push_back("NUM_TightID_DEN_genTracks"); // TODO is there function to find keys for selection already? if not let's make it
        muKEYs["POGTight"]["Iso"].push_back("NUM_TightRelIso_DEN_TightIDandIPCut");
        muKEYs["POGTight"]["Iso"].push_back("NUM_LooseRelTkIso_DEN_HighPtIDandIPCut");
        muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(0)].push_back("IsoMu24_POGTight");
        muKEYs["POGTight"][muWPs["POGTight"]["Trigger"].at(1)].push_back("NA");

        // electron
        eleWPs["POGTight"]["Id"].push_back("passTightID");
        eleWPs["POGTight"]["Id"].push_back("passTightID_vetoIso");
        eleWPs["POGTight"]["Trigger"].push_back("HLT_Ele27_WPTight_Gsf");
        eleWPs["POGTight"]["Trigger"].push_back("HLT_Ele27_WPTight_Gsf_vetoIso");


        eleKEYs["POGTight"]["Id"].push_back("passTightID");
        eleKEYs["POGTight"]["Id"].push_back("NA");
        eleKEYs["POGTight"][eleWPs["POGTight"]["Trigger"].at(0)].push_back("NA");
        eleKEYs["POGTight"][eleWPs["POGTight"]["Trigger"].at(1)].push_back("NA");

  }

  // set muon SF branches
  std::map<TString, std::map<TString, std::vector<TString>>>::iterator it = muWPs.begin();
  while(it != muWPs.end()){

	int nIso = (it->second)["Iso"].size();
  	int nTrg = (it->second)["Trigger"].size();
	int nId = (it->second)["Id"].size();

  	for(int i = 0; i < 4; i++){

		for(int k = 0; k < nId;  k++){
  			for(int j = 0; j < nIso; j++){
  	     			if( i != 3){ 

  	     				newtree->Branch(SFs[i] + "_mu_" + (it->second)["Id"].at(k) + (it->second)["Iso"].at(j), 
  	     					        &lepSFs["mu"+(it->second)["Id"].at(k) + (it->second)["Iso"].at(j)][SFs[i]]);

  	     			}
  	     			else if(i == 3){ // for trigger SF

  	     					newtree->Branch(SFs[i] + "_" + (it->second)["Trigger"].at(j) + "_" + "mu_" + (it->second)["Id"].at(k) + (it->second)["Iso"].at(j), 
  	     						        &lepSFs["mu"+(it->second)["Id"].at(k) + (it->second)["Iso"].at(j) + (it->second)["Trigger"].at(j)][SFs[i]]);
  	    			}// for trigger 
  			}// nIso
		}// nId
  	}
	it++;
  }

  // set electron SF branches
  it = eleWPs.begin();
  while(it != eleWPs.end()){

        int nTrg = (it->second)["Trigger"].size();
        int nId = (it->second)["Id"].size();

        for(int i = 0; i < 4; i++){

                for(int k = 0; k < nId;  k++){
                                if( i != 3){

                                        newtree->Branch(SFs[i] + "_ele_" + (it->second)["Id"].at(k),
                                                        &lepSFs["ele"+(it->second)["Id"].at(k)][SFs[i]]);

                                }
                                else if(i == 3){ // for trigger SF

                                                newtree->Branch(SFs[i] + "_" + (it->second)["Trigger"].at(k) + "_" + "ele_" + (it->second)["Id"].at(k),
                                                                &lepSFs["ele"+(it->second)["Id"].at(k) + (it->second)["Trigger"].at(k)][SFs[i]]);
                                }// for trigger 
                }// nId
        }
        it++;
  }


}

void Skim_Efficiency::executeEvent(){
 
  AllMuons = GetAllMuons();
  AllElectrons = GetAllElectrons();

  AnalyzerParameter param; // TODO make EfficiencyParameter class

  //
  std::map<TString, std::map<TString, std::vector<TString>>>::iterator it = muWPs.begin();
  while(it != muWPs.end()){
  	int nIso = (it->second)["Iso"].size();
  	int nId = (it->second)["Id"].size();

	for(int k = 0; k < nId;  k++){
  		for(int i = 0; i < nIso; i++){

  		      param.Lepton_ID     = (it->second)["Id"].at(k);
  		      param.Lepton_ISO_ID =     (it->second)["Iso"].at(i);
  		 
  		      // set keys
  		      param.Lepton_ID_SF_Key = muKEYs[it->first]["Id"].at(k);
  		      param.Lepton_ISO_SF_Key = muKEYs[it->first]["Iso"].at(i);

  		      int nTrg = (it->second)["Trigger"].size();
  		      for(int l = 0; l < muKEYs[it->first][(it->second)["Trigger"].at(i)].size(); l++){
  		      	        (param.Lepton_Trigger_map)[it->second["Trigger"].at(i)].push_back(muKEYs[it->first][(it->second)["Trigger"].at(i)].at(l));
  		      }
  		      executeEventFromParameter(param);
  		      param.Clear();

  		}
	}
	it++;
  }

  it = eleWPs.begin();
  while(it != eleWPs.end()){
        int nId = (it->second)["Id"].size();

        for(int k = 0; k < nId;  k++){

                      param.Lepton_ID     = (it->second)["Id"].at(k);

                      // set keys
                      param.Lepton_ID_SF_Key = eleKEYs[it->first]["Id"].at(k);

                      int nTrg = (it->second)["Trigger"].size();
                      for(int i = 0; i < eleKEYs[it->first][(it->second)["Trigger"].at(k)].size(); i++){
                                (param.Lepton_Trigger_map)[it->second["Trigger"].at(k)].push_back(eleKEYs[it->first][(it->second)["Trigger"].at(k)].at(i));
                        }
                      }
                      executeEventFromParameter(param, false);
                      param.Clear();

        }
        it++;
  }


  AllMuons.clear();
  AllElectrons.clear(); 

  newtree->Fill();

  return;

}


void Skim_Efficiency::executeEventFromParameter(AnalyzerParameter param, bool isMu){

  evt = new Event;
  *evt = GetEvent();

  vector<Muon> this_AllMuons = AllMuons; 
  vector<Electron> this_AllElectrons = AllElectrons; 

  if(param.syst_ == AnalyzerParameter::Central){ }

  vector<Muon> muons;
  vector<Electron> electrons;
  std::vector<Lepton*> leps;

  TString prefix;

  if(isMu){
	muons = SelectMuons(this_AllMuons, param.Lepton_ID+"With"+param.Lepton_ISO_ID, 7., 2.4);
	std::sort(muons.begin(), muons.end(),PtComparing);
	leps=MakeLeptonPointerVector(muons);

        LeptonReco_SF = NULL;
        LeptonTrg_SF = &MCCorrection::MuonTrigger_SF;
        LeptonID_SF   =&MCCorrection::MuonID_SF;
        LeptonISO_SF  =&MCCorrection::MuonISO_SF;
	
	prefix = "mu";
  }
  else{

        electrons = SelectElectrons(this_AllElectrons, param.Lepton_ID, 9., 2.5);
        std::sort(electrons.begin(), electrons.end(),PtComparing);
        leps=MakeLeptonPointerVector(electrons);

        LeptonReco_SF = &MCCorrection::ElectronReco_SF;
        LeptonTrg_SF = NULL;
        LeptonID_SF   =&MCCorrection::ElectronID_SF;
        LeptonISO_SF  =NULL;

        prefix = "ele";
  }

  if(!IsDATA){

		lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["RecoSF"].clear();
		lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IdSF"].clear();
		lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IsoSF"].clear();

		std::map<TString, std::vector<TString>>::iterator it = param.Lepton_Trigger_map.begin();
		while(it != param.Lepton_Trigger_map.end()){

			lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID+it->first]["TrgSF"].clear();

			// check wheter it is single or double trigger by counting the number of trigger keys
			int nKeys = (it->second).size();
			if(nKeys == 1){ // single trigger
				if(leps.size() > 0){

					if(isMu){
						std::vector<Muon> temp_muon;
						temp_muon.push_back((*(Muon*)leps.at(0))); // the first lepton, the largest pt?
						if((it->first).CompareTo("NA") !=0)lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID+it->first]["TrgSF"].push_back( LeptonTrg_SF?(mcCorr->*LeptonTrg_SF)(param.Lepton_ID, it->first, temp_muon,  0) : 1. ); 
						else lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID+it->first]["TrgSF"].push_back( 1.); 
					}
					else{
						std::vector<Electron> temp_electron;
						temp_electron.push_back((*(Electron*)leps.at(0))); // the first lepton, the largest pt?
						//if((it->first).CompareTo("NA") !=0)lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID+it->first]["TrgSF"].push_back( LeptonTrg_SF?(mcCorr->*LeptonTrg_SF)(param.Lepton_ID, it->first, temp_electron,  0) : 1. ); 
						//else lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID+it->first]["TrgSF"].push_back( 1.); 
						lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID+it->first]["TrgSF"].push_back( 1.); 
					}
				}
				else{// no lepton passing ID requirement
					lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID+it->first]["TrgSF"].push_back( 1.); 
				}
			}// single triger

			it++;
		}// trigger parameter map loop

    		for( int i(0); i<leps.size() ; i++){

			if(isMu){
				// Reco SF: just set 1. since this is for muon
    				lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["RecoSF"].push_back( 1.);

				// ID SF
    		  		if((param.Lepton_ID_SF_Key).CompareTo("NA") !=0) lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IdSF"].push_back(LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.);
				else lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IdSF"].push_back(1.);

				// Iso SF
    		  		if((param.Lepton_ISO_SF_Key).CompareTo("NA") !=0) lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IsoSF"].push_back(LeptonISO_SF?(mcCorr->*LeptonISO_SF)(param.Lepton_ISO_SF_Key, leps.at(i)->Eta(), ((Muon*)leps.at(i))->MiniAODPt(),  0) : 1.);
				else lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IsoSF"].push_back(1.);
			}
			else{
				// Reco SF
    				lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["RecoSF"].push_back( LeptonReco_SF?(mcCorr->*LeptonReco_SF)(((Electron*)leps.at(i))->scEta(), leps.at(i)->Pt(),  0) : 1.);

				// ID SF
    		  		if((param.Lepton_ID_SF_Key).CompareTo("NA") !=0) lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IdSF"].push_back(LeptonID_SF?(mcCorr->*LeptonID_SF)(param.Lepton_ID_SF_Key, ((Electron*)leps.at(i))->scEta(), leps.at(i)->Pt(),  0) : 1.);
				else lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IdSF"].push_back(1.);

				// Iso SF: just set 1. since this is for electron
				lepSFs[prefix+param.Lepton_ID+param.Lepton_ISO_ID]["IsoSF"].push_back(1.);
			}
    		}// loop over leptons passing ID

  }// for MC

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

