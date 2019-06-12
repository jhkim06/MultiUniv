#include "Skim_Efficiency.h"

void Skim_Efficiency::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //Skim_Efficiency just adds SFs for ID Iso Trigger (i.e., without skimming)
  //If there are leptons passing some ID, Iso or Trigger condition, it just calculate SFs for those leptons up to two leptons 
  //TODO add option to select 2016, 2017, and 2018, currently checked only for 2017

  outfile->mkdir("recoTree");
  outfile->cd("recoTree");
  newtree = fChain->CloneTree(0);

  // New Branch
  // assume the input ntuple don't have below SFs branch, so just create new branches

  El_IdSF.insert(std::make_pair("passMediumID", 1.));
  ElEl_IdSF.insert(std::make_pair("passMediumID", 1.));
  El_IdSF_Trigger.insert(std::make_pair("passMediumID", "HLT_Ele35_WPTight_Gsf_v"));  
  ElEl_IdSF_Trigger.insert(std::make_pair("passMediumID", "DoubleElectron")); 

  El_IdSF.insert(std::make_pair("passTightID", 1.));
  ElEl_IdSF.insert(std::make_pair("passTightID", 1.));
  El_IdSF_Trigger.insert(std::make_pair("passTightID", "HLT_Ele35_WPTight_Gsf_v")); 
  ElEl_IdSF_Trigger.insert(std::make_pair("passTightID", "DoubleElectron")); 

  El_IdSF.insert(std::make_pair("passTightID_vetoIso", 1.));
  ElEl_IdSF.insert(std::make_pair("passTightID_vetoIso", 1.));
  El_IdSF_Trigger.insert(std::make_pair("passTightID_vetoIso", "HLT_Ele35_WPTight_Gsf_v")); 
  ElEl_IdSF_Trigger.insert(std::make_pair("passTightID_vetoIso", "DoubleElectron")); 

  // LepIDSF_2_ele_POGTightID_mu_POGTightID
  // LepTightIsoSF_2_ele_POGTightID_mu_POGTightID
  // LepRecoSF_2_ele_POGTightID_mu_POGTightID
  // LepTrgSF_2_ele_POGTightID_mu_POGTightID

  std::map<TString, double>::iterator it = El_IdSF.begin();
  while(it !=El_IdSF.end()){
       El_RecoSF.insert(std::make_pair(it->first, 1.));
       ElEl_RecoSF.insert(std::make_pair(it->first, 1.));
       El_TriggerSF.insert(std::make_pair(it->first+El_IdSF_Trigger[it->first], 1.)); // map to save trigger SFs
       ElEl_TriggerSF.insert(std::make_pair(it->first+ElEl_IdSF_Trigger[it->first], 1.)); // map to save trigger SFs

       newtree->Branch("El_IdSF_"+it->first,                                        &it->second,                                         "El_IdSF_"+it->first+"/D"  ); 
       newtree->Branch("El_RecoSF_"+it->first,                                      &El_RecoSF[it->first],                               "El_RecoSF_"+it->first+"/D"  ); 
       newtree->Branch("El_TriggerSF_"+El_IdSF_Trigger[it->first]+"_"+it->first,    &El_TriggerSF[it->first+El_IdSF_Trigger[it->first]], "El_TriggerSF_"+El_IdSF_Trigger[it->first]+"_"+it->first+"/D"  ); 

       newtree->Branch("ElEl_IdSF_"+it->first,                                          &ElEl_IdSF[it->first],                                   "ElEl_IdSF_"+it->first+"/D"  ); 
       newtree->Branch("ElEl_RecoSF_"+it->first,                                        &ElEl_RecoSF[it->first],                                 "ElEl_RecoSF_"+it->first+"/D"  ); 
       newtree->Branch("ElEl_TriggerSF_"+ElEl_IdSF_Trigger[it->first]+"_"+it->first,    &ElEl_TriggerSF[it->first+ElEl_IdSF_Trigger[it->first]], "ElEl_TriggerSF_"+ElEl_IdSF_Trigger[it->first]+"_"+it->first+"/D"  ); 
       it++;
  }

  Mu_IdSF.insert(std::make_pair("POGTightWithTightIso", 1.));
  MuMu_IdSF.insert(std::make_pair("POGTightWithTightIso", 1.));
  Mu_IdSF_Iso.insert(std::make_pair("POGTightWithTightIso", "TightIso")); 
  Mu_IdSF_Trigger.insert(std::make_pair("POGTightWithTightIso", "HLT_IsoMu27_v")); 
  MuMu_IdSF_Trigger.insert(std::make_pair("POGTightWithTightIso", "DoubleMu")); 

  it = Mu_IdSF.begin();
  while(it !=Mu_IdSF.end()){

       Mu_IsoSF.insert(std::make_pair(it->first+Mu_IdSF_Iso[it->first], 1.)); 
       MuMu_IsoSF.insert(std::make_pair(it->first+Mu_IdSF_Iso[it->first], 1.)); 
 
       Mu_TriggerSF.insert(std::make_pair(it->first+Mu_IdSF_Trigger[it->first], 1.)); // map to save trigger SFs
       MuMu_TriggerSF.insert(std::make_pair(it->first+MuMu_IdSF_Trigger[it->first], 1.)); // map to save trigger SFs

       newtree->Branch("Mu_IdSF_"+it->first,                                        &it->second,                                         "Mu_IdSF_"+it->first+"/D"  );
       newtree->Branch("Mu_IsoSF_"+it->first,                                       &Mu_IsoSF[it->first],                                "Mu_IsoSF_"+it->first+"/D"  );
       newtree->Branch("Mu_TriggerSF_"+Mu_IdSF_Trigger[it->first]+"_"+it->first,    &Mu_TriggerSF[it->first+Mu_IdSF_Trigger[it->first]], "Mu_TriggerSF_"+Mu_IdSF_Trigger[it->first]+"_"+it->first+"/D"  );

       newtree->Branch("MuMu_IdSF_"+it->first,                                          &MuMu_IdSF[it->first],                                   "MuMu_IdSF_"+it->first+"/D"  );
       newtree->Branch("MuMu_IsoSF_"+it->first,                                         &MuMu_IsoSF[it->first],                                  "MuMu_IsoSF_"+it->first+"/D"  );
       newtree->Branch("MuMu_TriggerSF_"+MuMu_IdSF_Trigger[it->first]+"_"+it->first,    &MuMu_TriggerSF[it->first+MuMu_IdSF_Trigger[it->first]], "MuMu_TriggerSF_"+MuMu_IdSF_Trigger[it->first]+"_"+it->first+"/D"  );
       it++;
  }

}

void Skim_Efficiency::executeEvent(){

  muons.clear();
  electrons.clear();
  leps.clear();

  evt = new Event;
  *evt = GetEvent();

  std::map<TString, double>::iterator it = El_IdSF.begin();
  while(it !=El_IdSF.end()){

        // get electrons passing ID
        electrons=GetElectrons(it->first,9.,2.5); 

        // initialise
        El_IdSF[it->first] = 1.;
        El_RecoSF[it->first] = 1.;
        El_TriggerSF[it->first+El_IdSF_Trigger[it->first]] = 1.;

        ElEl_IdSF[it->first] = 1.;
        ElEl_RecoSF[it->first] = 1.;
        ElEl_TriggerSF[it->first+ElEl_IdSF_Trigger[it->first]] = 1.;

        if(!IsData){

          // save SFs regarding Electrons
          for( int i(0); i<electrons.size() ; i++){

             if( i == 2 ) break; // only consider up to two leptons  

             TString ElectronID_key;
             if(it->first == "passTightID") ElectronID_key = "passTightID"; 
             if(it->first == "passMediumID") ElectronID_key = "passMediumID"; 
             if(it->first == "passTightID_vetoIso") ElectronID_key = "Default"; 
          
             if(i==0){   
                El_IdSF[it->first]      *= mcCorr->ElectronID_SF(ElectronID_key, electrons.at(i).scEta(), electrons.at(i).Pt(),  0);
                El_RecoSF[it->first]    *= mcCorr->ElectronReco_SF(electrons.at(i).scEta(), electrons.at(i).Pt(),  0);
                El_TriggerSF[it->first+El_IdSF_Trigger[it->first]] *= 1.;  // TODO make a function to get single electron trigger SF
             }

             if(i==1){   
                leps=MakeLeptonPointerVector(electrons);
                TString trgSF_key0, trgSF_key1;

                if(it->first.Contains("MediumID")){
     		  trgSF_key0 = "LeadEle23_MediumID";
     		  trgSF_key1 = "TailEle12_MediumID";
                }
		else{
     		  trgSF_key0 = "Default";
     		  trgSF_key1 = "Default";
                }

                ElEl_IdSF[it->first]      = El_IdSF[it->first]   * mcCorr->ElectronID_SF(ElectronID_key, electrons.at(i).scEta(), electrons.at(i).Pt(),  0);
                ElEl_RecoSF[it->first]    = El_RecoSF[it->first] * mcCorr->ElectronReco_SF(electrons.at(i).scEta(), electrons.at(i).Pt(),  0);
                ElEl_TriggerSF[it->first+ElEl_IdSF_Trigger[it->first]] *= mcCorr->DiLeptonTrg_SF(trgSF_key0, trgSF_key0, leps,  0);
             }
          }
          // save SFs regarding Muons

        }// save SFs for MC
        // initialise electrons 
        electrons.clear();
        electrons.shrink_to_fit();
        leps.clear();
        leps.shrink_to_fit();
        it++;
  }

  it = Mu_IdSF.begin();
  while(it !=Mu_IdSF.end()){

        // get muons passing ID
        muons=GetMuons(it->first,9.,2.4); 

        // initialise
        Mu_IdSF[it->first] = 1.; 
        Mu_IsoSF[it->first] = 1.; 
        Mu_TriggerSF[it->first+Mu_IdSF_Trigger[it->first]] = 1.; 

        MuMu_IdSF[it->first] = 1.; 
        MuMu_IsoSF[it->first] = 1.; 
        MuMu_TriggerSF[it->first+MuMu_IdSF_Trigger[it->first]] = 1.; 

        if(!IsData){

          // save SFs regarding Muectrons
          for( int i(0); i<muons.size() ; i++){

             if( i == 2 ) break; // only consider up to two leptons  

             TString MuonID_key;
             if(it->first.Contains("POGTight"))  MuonID_key = "NUM_TightID_DEN_genTracks"; 
             if(it->first.Contains("POGMedium")) MuonID_key = "NUM_MediumID_DEN_genTracks"; 
             if(it->first.Contains("POGLoose"))  MuonID_key = "Default"; 

             TString MuonIso_key;
             if(it->first.Contains("TightIso"))  MuonIso_key = "NUM_TightRelIso_DEN_TightIDandIPCut"; 
             if(it->first.Contains("MediumIso")) MuonIso_key = "Default"; 
             if(it->first.Contains("LooseIso"))  MuonIso_key = "Default"; 
    
             if(i==0){   
                Mu_IdSF[it->first]     *= mcCorr->MuonID_SF(MuonID_key, muons.at(i).Eta(), muons.at(i).MiniAODPt(),  0); 
                Mu_IsoSF[it->first]    *= mcCorr->MuonISO_SF(MuonIso_key, muons.at(i).Eta(), muons.at(i).MiniAODPt(),  0); 
                Mu_TriggerSF[it->first+Mu_IdSF_Trigger[it->first]] *= mcCorr->MuonTrigger_SF(MuonID_key,Mu_IdSF_Trigger[it->first], muons, 0);  // TODO currently, only for IsoMu24, IsoMu27, Mu50
             }   

             if(i==1){   
                leps=MakeLeptonPointerVector(muons);
                TString trgSF_key0, trgSF_key1;

                if(it->first.Contains("POGTight")){
                  trgSF_key0 = "Lead17_POGTight";
                  trgSF_key1 = "Lead8_POGTight";
                }   
                else{
                  trgSF_key0 = "Default";
                  trgSF_key1 = "Default";
                }   

                MuMu_IdSF[it->first]     = Mu_IdSF[it->first]  * mcCorr->MuonID_SF(MuonID_key, muons.at(i).Eta(), muons.at(i).MiniAODPt(),  0); 
                MuMu_IsoSF[it->first]    = Mu_IsoSF[it->first] * mcCorr->MuonISO_SF(MuonIso_key, muons.at(i).Eta(), muons.at(i).MiniAODPt(),  0); 
                MuMu_TriggerSF[it->first+MuMu_IdSF_Trigger[it->first]] *= mcCorr->DiLeptonTrg_SF(trgSF_key0, trgSF_key0, leps,  0); 
             }   
          }   
          // save SFs regarding Muons

        }// save SFs for MC
        // initialise muons 
        muons.clear();
        muons.shrink_to_fit();
        leps.clear();
        leps.shrink_to_fit();
        it++;
  }

  newtree->Fill();

  return;

}


void Skim_Efficiency::executeEventFromParameter(AnalyzerParameter param){

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

