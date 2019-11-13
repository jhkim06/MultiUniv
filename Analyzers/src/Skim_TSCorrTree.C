#include "Skim_TSCorrTree.h"

void Skim_TSCorrTree::initializeAnalyzer(){

  //initializeAnalyzerTools();
  //=================================
  // set pointers
  //=================================
  //out obj. reco
  b_jet_from_top = new TLorentzVector(0.,0.,0.,0.);
  b_jet_from_anti_top = new TLorentzVector(0.,0.,0.,0.);
  down_type_jet_from_w_ch = new TLorentzVector(0.,0.,0.,0.);
  up_type_jet_from_w_ch = new TLorentzVector(0.,0.,0.,0.);
  lepton = new TLorentzVector(0.,0.,0.,0.);
  METv = new TLorentzVector(0.,0.,0.,0.);
  //out obj. truth
  b_parton_from_top = new TLorentzVector(0.,0.,0.,0.);
  b_parton_from_anti_top = new TLorentzVector(0.,0.,0.,0.);
  down_type_parton_from_w_ch = new TLorentzVector(0.,0.,0.,0.);
  up_type_parton_from_w_ch = new TLorentzVector(0.,0.,0.,0.);
  neutrino = new TLorentzVector(0.,0.,0.,0.);  

  outfile->cd();
  newtree = fChain->CloneTree(0);
  newtree->SetBranchStatus("*",0);
  //=================================
  // init
  //=================================
  
  response["Pt"] = NULL;
  response["Et"] = NULL;
  response["Eta"] = NULL;
  response["Phi"] = NULL;

  flavour["uds"] = new TFormula("uds","abs(x[0])<4");
  flavour["udsc"] = new TFormula("udsc","abs(x[0])<5");
  flavour["c"] = new TFormula("b","abs(x[0])==4");
  flavour["b"] = new TFormula("b","abs(x[0])==5");
  flavour["udscb"] = new TFormula("b","1");

  ptBin["pt_20to22.5"] = new TFormula("pt_20to22.5","x[0]>=20&&x[0]<22.5");
  ptBin["pt_22.5to25"] = new TFormula("pt_22.5to25","x[0]>=22.5&&x[0]<25");
  ptBin["pt_25to27.5"] = new TFormula("pt_25to27.5","x[0]>=25&&x[0]<27.5");
  ptBin["pt_27.5to30"] = new TFormula("pt_27.5to30","x[0]>=27.5&&x[0]<30");
  ptBin["pt_30to32.5"] = new TFormula("pt_30to32.5","x[0]>=30&&x[0]<32.5");
  ptBin["pt_32.5to35"] = new TFormula("pt_32.5to35","x[0]>=32.5&&x[0]<35");
  ptBin["pt_35to37.5"] = new TFormula("pt_35to37.5","x[0]>=35&&x[0]<37.5");
  ptBin["pt_37.5to40"] = new TFormula("pt_37.5to40","x[0]>=37.5&&x[0]<40");
  ptBin["pt_40to45"] = new TFormula("pt_40to45","x[0]>=40&&x[0]<45");
  ptBin["pt_45to50"] = new TFormula("pt_45to50","x[0]>=45&&x[0]<50");
  ptBin["pt_50to55"] = new TFormula("pt_50to55","x[0]>=50&&x[0]<55");
  ptBin["pt_55to60"] = new TFormula("pt_55to60","x[0]>=55&&x[0]<60");
  ptBin["pt_60to70"] = new TFormula("pt_60to70","x[0]>=60&&x[0]<70");
  ptBin["pt_70to80"] = new TFormula("pt_70to80","x[0]>=70&&x[0]<80");
  ptBin["pt_80to90"] = new TFormula("pt_80to90","x[0]>=80&&x[0]<90");
  ptBin["pt_90to100"] = new TFormula("pt_90to100","x[0]>=90&&x[0]<100");
  ptBin["pt_100to120"] = new TFormula("pt_100to120","x[0]>=100&&x[0]<120");
  ptBin["pt_120to150"] = new TFormula("pt_120to150","x[0]>=120&&x[0]<150");
  ptBin["pt_150toINF"] = new TFormula("pt_150toINF","x[0]>=150");

  etaBin["eta_0.174"] = new TFormula("eta_0.174","abs(x[0])<0.174");
  etaBin["eta_0.348"] = new TFormula("eta_0.348","abs(x[0])>0.174&&abs(x[0])<0.348");
  etaBin["eta_0.522"] = new TFormula("eta_0.522","abs(x[0])>0.348&&abs(x[0])<0.522");
  etaBin["eta_0.696"] = new TFormula("eta_0.696","abs(x[0])>0.522&&abs(x[0])<0.696");
  etaBin["eta_0.879"] = new TFormula("eta_0.879","abs(x[0])>0.696&&abs(x[0])<0.879");
  etaBin["eta_1.131"] = new TFormula("eta_1.131","abs(x[0])>0.879&&abs(x[0])<1.131");
  etaBin["eta_1.392"] = new TFormula("eta_1.392","abs(x[0])>1.131&&abs(x[0])<1.392");
  etaBin["eta_1.74"] = new TFormula("eta_1.74","abs(x[0])>1.392&&abs(x[0])<1.74");
  etaBin["eta_2.4"] = new TFormula("eta_2.4","abs(x[0])>1.74&&abs(x[0])<2.4");
  

  gen_matcher = new GenMatching_CHToCB();
  //ts_correction = new TSCorrection(DataYear);
  //ts_correction->ReadFittedError("fit_error_pythia.txt");
  //ts_correction->ReadFittedMean("fit_mean_pythia.txt");
}

void Skim_TSCorrTree::executeEvent(){

  muons.clear();
  electrons.clear();
  muons_loose.clear();
  electrons_veto.clear();
  
  evt = new Event;
  *evt = GetEvent();

  if(IsDATA){
    baseW = 1.;
  }else{ 
    baseW = weight_norm_1invpb*evt->MCweight()*evt->GetTriggerLumi("Full");
    baseW *= mcCorr->GetPileUpWeight(nPileUp,0);
  }
  muons=GetMuons("POGTightWithTightIso",20.,2.4);
  electrons=GetElectrons("passTightID",20.,2.5);
  if(muons.size()+electrons.size() !=1) return; // 1 tight lepton

  TLorentzVector reco_lepton;
  if(muons.size()==1) reco_lepton = muons.at(0);
  else if(electrons.size()==1) reco_lepton = electrons.at(0);
  FillHist("CutFlow",2,1,30,0,30);
  
  muons_loose=GetMuons("POGLooseWithLooseIso",15.,2.4);
  electrons_veto=GetElectrons("passVetoID",15.,2.5);
  if(muons_loose.size()+electrons_veto.size() !=1) return; // veto extra lepton
  FillHist("CutFlow",3,1,30,0,30);
  
  TLorentzVector MET_vector = evt->GetMETVector();
  if(MET_vector.Et()<20) return;
  FillHist("CutFlow",4,1,30,0,30);

  vector<Jet> this_AllJets = GetAllJets();
  vector<Gen> this_AllGens = GetGens();
  vector<Jet> jets = SelectJets(this_AllJets, "tight", 5., 2.4);
  jets = JetsVetoLeptonInside(jets, electrons, muons);
  std::sort(jets.begin(), jets.end(), PtComparing);
  if(jets.size()<4) return;
  FillHist("CutFlow",5,1,30,0,30);

  gen_matcher->SetGens(this_AllGens);
  gen_matcher->SetJets(jets);
  if(!gen_matcher->FindHardProcessParton()) return; // find parton from hard process
  FillHist("CutFlow",6,1,30,0,30);

  if(!gen_matcher->MatchJets()) return; // match parton-jet min-delta R
  FillHist("CutFlow",7,1,30,0,30);

  if(!gen_matcher->CheckFlavour()) return; // check flavour
  FillHist("CutFlow",8,1,30,0,30);
  if(!gen_matcher->CheckAmbiguity()) return; // check ambiguity matching
  FillHist("CutFlow",9,1,30,0,30);

  *b_jet_from_top = gen_matcher->Get_hadronic_top_b_jet()->matched_jet;
  *b_jet_from_anti_top = gen_matcher->Get_leptonic_top_b_jet()->matched_jet;
  *down_type_jet_from_w_ch = gen_matcher->Get_down_type_jet()->matched_jet;
  *up_type_jet_from_w_ch = gen_matcher->Get_up_type_jet()->matched_jet;
  *lepton = reco_lepton;
  *METv = MET_vector;

  //out obj. truth
  *b_parton_from_top = gen_matcher->Get_hadronic_top_b_jet()->matched_parton;
  *b_parton_from_anti_top = gen_matcher->Get_leptonic_top_b_jet()->matched_parton;
  *down_type_parton_from_w_ch = gen_matcher->Get_down_type_jet()->matched_parton;
  *up_type_parton_from_w_ch = gen_matcher->Get_up_type_jet()->matched_parton;
  *neutrino = gen_matcher->Get_neutrino()->matched_parton;

  down_type_parton_flavour = gen_matcher->Get_down_type_jet()->parton_flavour;
  up_type_parton_flavour = gen_matcher->Get_up_type_jet()->parton_flavour;

  
  //fill histogram
  for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
    // initialized as false, if a response is filled at corresponding pt,eta bin, reset as true
    bool isFilled_top_b = false, isFilled_anti_top_b = false;
    bool isFilled_up_type = false, isFilled_down_type = false;
    for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
    for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
      // check if all response was filled at corresponding pt,eta bin
      if(isFilled_top_b && isFilled_anti_top_b && isFilled_up_type && isFilled_down_type) break;
      // name of response histogram
      TString name = Form("%s_%s_%s_%s",it_res->first.Data(),
                                        it_flav->first.Data(),
                                        it_pt->first.Data(),
                                        it_eta->first.Data()
                         );
      if(!isFilled_top_b &&
         it_flav->second->Eval(5) &&
         it_eta->second->Eval( b_jet_from_top->Eta() ) &&
         it_pt->second->Eval( b_jet_from_top->Pt() )){

         double response_top_b = this->GetResponse(it_res->first, b_jet_from_top, b_parton_from_top);
         JSFillHist("response_histogram",name,response_top_b, baseW, 160, -0.8, 0.8);
         isFilled_top_b = true;

      }
      if(!isFilled_anti_top_b &&
         it_flav->second->Eval(5) &&
         it_eta->second->Eval( b_jet_from_anti_top->Eta() ) && 
         it_pt->second->Eval( b_jet_from_anti_top->Pt() )){

         double response_anti_top_b = this->GetResponse(it_res->first, b_jet_from_anti_top, b_parton_from_anti_top);
         JSFillHist("response_histogram",name,response_anti_top_b, baseW, 160, -0.8, 0.8);
         isFilled_anti_top_b = true;

      }
      if(!isFilled_up_type &&
         it_flav->second->Eval(up_type_parton_flavour) &&
         it_eta->second->Eval( up_type_jet_from_w_ch->Eta() ) && 
         it_pt->second->Eval( up_type_jet_from_w_ch->Pt() )){

         double response_up_type_flav = this->GetResponse(it_res->first, up_type_jet_from_w_ch, up_type_parton_from_w_ch);
         JSFillHist("response_histogram",name,response_up_type_flav, baseW, 160, -0.8, 0.8);
         isFilled_up_type = true;

      }
      if(!isFilled_down_type &&
         it_flav->second->Eval(down_type_parton_flavour) &&
         it_eta->second->Eval( down_type_jet_from_w_ch->Eta() ) && 
         it_pt->second->Eval( down_type_jet_from_w_ch->Pt() )){

         double response_down_type_flav = this->GetResponse(it_res->first, down_type_jet_from_w_ch, down_type_parton_from_w_ch);
         JSFillHist("response_histogram",name,response_down_type_flav, baseW, 160, -0.8, 0.8);
         isFilled_down_type = true;
      }
    }
    }
  }
  }
  // fill pt distribution
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
    bool isFilled_top_b = false, isFilled_anti_top_b = false;
    bool isFilled_up_type = false, isFilled_down_type = false;
    for(map<TString,TFormula*>::iterator it_pt=ptBin.begin(); it_pt!=ptBin.end(); it_pt++){
    for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
      if(isFilled_top_b && isFilled_anti_top_b && isFilled_up_type && isFilled_down_type) break;
      TString name = Form("%s_%s_%s_%s",it_flav->first.Data(),it_pt->first.Data(),it_eta->first.Data(),"jet_pt");
      if(!isFilled_top_b &&
         it_flav->second->Eval(5) &&
         it_eta->second->Eval( b_jet_from_top->Eta() ) && 
         it_pt->second->Eval( b_jet_from_top->Pt() )){

         JSFillHist("pt_histogram",name, b_jet_from_top->Pt(), baseW, 300, 0, 300);
         isFilled_top_b = true;

      }
      if(!isFilled_anti_top_b &&
         it_flav->second->Eval(5) &&
         it_eta->second->Eval( b_jet_from_anti_top->Eta() ) &&
         it_pt->second->Eval( b_jet_from_anti_top->Pt() )){

         JSFillHist("pt_histogram",name, b_jet_from_anti_top->Pt(), baseW, 300, 0, 300);
         isFilled_anti_top_b = true;

      }
      if(!isFilled_up_type &&
         it_flav->second->Eval(up_type_parton_flavour) &&
         it_eta->second->Eval( up_type_jet_from_w_ch->Eta() ) &&
         it_pt->second->Eval( up_type_jet_from_w_ch->Pt() )){

         JSFillHist("pt_histogram",name, up_type_jet_from_w_ch->Pt(), baseW, 300, 0, 300);
         isFilled_up_type = true;

      }
      if(!isFilled_down_type &&
         it_flav->second->Eval(down_type_parton_flavour) &&
         it_eta->second->Eval( down_type_jet_from_w_ch->Eta() ) &&
         it_pt->second->Eval( down_type_jet_from_w_ch->Pt() )){

         JSFillHist("pt_histogram",name, down_type_jet_from_w_ch->Pt(), baseW, 300, 0, 300);
         isFilled_down_type = true;

      }
    }
    }
  } 
  //fill profile
  for(map<TString,TFormula*>::iterator it_res=response.begin(); it_res!=response.end(); it_res++){
  for(map<TString,TFormula*>::iterator it_flav=flavour.begin(); it_flav!=flavour.end(); it_flav++){
    // initialized as false, if a response is filled at corresponding pt,eta bin, reset as true
    bool isFilled_top_b = false, isFilled_anti_top_b = false;
    bool isFilled_up_type = false, isFilled_down_type = false;
    for(map<TString,TFormula*>::iterator it_eta=etaBin.begin(); it_eta!=etaBin.end(); it_eta++){
      // check if all response was filled at corresponding pt,eta bin
      if(isFilled_top_b && isFilled_anti_top_b && isFilled_up_type && isFilled_down_type) break;
      // name of response histogram
      TString name = Form("%s_%s_%s",it_res->first.Data(),
                                        it_flav->first.Data(),
                                        it_eta->first.Data()
                         );
      if(!isFilled_top_b &&
         it_flav->second->Eval(5) &&
         it_eta->second->Eval( b_jet_from_top->Eta() )
        ){

         double response_top_b = this->GetResponse(it_res->first, b_jet_from_top, b_parton_from_top);
         /*if(ts_correction->PassResponseCut(name,b_jet_from_top->Pt(),response_top_b)){
           BHFillProfile("response_profile",name,
                          b_jet_from_top->Pt(),response_top_b,
                          baseW);
         }*/
         BHFillProfile("response_profile_nocut",name,
                        b_jet_from_top->Pt(),response_top_b,
                        baseW);
         isFilled_top_b = true;

      }
      if(!isFilled_anti_top_b &&
         it_flav->second->Eval(5) &&
         it_eta->second->Eval( b_jet_from_anti_top->Eta() )
        ){

         double response_anti_top_b = this->GetResponse(it_res->first, b_jet_from_anti_top, b_parton_from_anti_top);
         /*if(ts_correction->PassResponseCut(name,b_jet_from_anti_top->Pt(),response_anti_top_b)){
           BHFillProfile("response_profile",name,
                         b_jet_from_anti_top->Pt(),response_anti_top_b,
                         baseW);
         }*/
         BHFillProfile("response_profile_nocut",name,
                       b_jet_from_anti_top->Pt(),response_anti_top_b,
                       baseW);
         isFilled_anti_top_b = true;

      }
      if(!isFilled_up_type &&
         it_flav->second->Eval(up_type_parton_flavour) &&
         it_eta->second->Eval( up_type_jet_from_w_ch->Eta() )
        ){

         double response_up_type_flav = this->GetResponse(it_res->first, up_type_jet_from_w_ch, up_type_parton_from_w_ch);
         /*if(ts_correction->PassResponseCut(name,up_type_jet_from_w_ch->Pt(),response_up_type_flav)){
           BHFillProfile("response_profile",name,
                         up_type_jet_from_w_ch->Pt(),response_up_type_flav,
                         baseW);
         }*/
         BHFillProfile("response_profile_nocut",name,
                       up_type_jet_from_w_ch->Pt(),response_up_type_flav,
                       baseW);
         isFilled_up_type = true;

      }
      if(!isFilled_down_type &&
         it_flav->second->Eval(down_type_parton_flavour) &&
         it_eta->second->Eval( down_type_jet_from_w_ch->Eta() )
        ){

         double response_down_type_flav = this->GetResponse(it_res->first, down_type_jet_from_w_ch, down_type_parton_from_w_ch);
         /*if(ts_correction->PassResponseCut(name,down_type_jet_from_w_ch->Pt(),response_down_type_flav)){
           BHFillProfile("response_profile",name,
                         down_type_jet_from_w_ch->Pt(),response_down_type_flav,
                         baseW);
         }*/
         BHFillProfile("response_profile_nocut",name,
                       down_type_jet_from_w_ch->Pt(),response_down_type_flav,
                       baseW);
         isFilled_down_type = true;
      }
    }
  }
  } 
  return;

}


void Skim_TSCorrTree::executeEventFromParameter(AnalyzerParameter param){

}

Skim_TSCorrTree::Skim_TSCorrTree(){

}

Skim_TSCorrTree::~Skim_TSCorrTree(){
  //out obj. reco
  delete b_jet_from_top;
  delete b_jet_from_anti_top;
  delete down_type_jet_from_w_ch;
  delete up_type_jet_from_w_ch;
  delete lepton;
  delete METv;

  //out obj. truth
  delete b_parton_from_top;
  delete b_parton_from_anti_top;
  delete down_type_parton_from_w_ch;
  delete up_type_parton_from_w_ch;
  delete neutrino;

  
  for(map<TString,TFormula*>::iterator it=response.begin(); it!=response.end(); it++){
    delete it->second;
  }
  for(map<TString,TFormula*>::iterator it=flavour.begin(); it!=flavour.end(); it++){
    delete it->second;
  }
  for(map<TString,TFormula*>::iterator it=ptBin.begin(); it!=ptBin.end(); it++){
    delete it->second;
  }
  for(map<TString,TFormula*>::iterator it=etaBin.begin(); it!=etaBin.end(); it++){
    delete it->second;
  }
  
  delete gen_matcher;
}

void Skim_TSCorrTree::WriteHist(){

  //outfile->mkdir("recoTree");
  //outfile->cd("recoTree"); Already at Skim_Leptons::initializeAnalyzer
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

  for(std::map< TString, std::map<TString, TProfile*> >::iterator mapit=BHmapprofile.begin(); mapit!=BHmapprofile.end(); mapit++){

    TString this_suffix = mapit->first;
    std::map< TString, TProfile* > this_mapprofile = mapit->second;

    TDirectory *dir = outfile->GetDirectory(this_suffix);
    if(!dir){
      outfile->mkdir(this_suffix);
    }
    outfile->cd(this_suffix);

    for(std::map< TString, TProfile* >::iterator mapit = this_mapprofile.begin(); mapit!=this_mapprofile.end(); mapit++){
      mapit->second->Write();
    }

    outfile->cd();

  }
}

double Skim_TSCorrTree::GetResponse(TString var, TLorentzVector *jet, TLorentzVector *parton){
  if(var=="Pt"){
    return this->GetResponse_Pt(jet, parton);
  }
  else if(var=="Et"){
    return this->GetResponse_Et(jet, parton);
  }
  else if(var=="Eta"){
    return this->GetResponse_Eta(jet, parton);
  }
  else if(var=="Phi"){
    return this->GetResponse_Phi(jet, parton);
  }
  else{
    cout <<"    >>  Skim_TSCorrTree::GetResponse    : " << var  << " is not exist" << endl;
    exit(1);
  }
  return 1.;
}


double Skim_TSCorrTree::GetResponse_Pt(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Pt = jet->Pt(), parton_Pt = parton->Pt();
  return (parton_Pt - jet_Pt)/jet_Pt;
}


double Skim_TSCorrTree::GetResponse_Et(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Et = jet->Et(), parton_Et = parton->Et();
  return (parton_Et - jet_Et)/jet_Et;
}


double Skim_TSCorrTree::GetResponse_Eta(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Eta = jet->Eta(), parton_Eta = parton->Eta();
  return (parton_Eta - jet_Eta)/jet_Eta;
}


double Skim_TSCorrTree::GetResponse_Phi(TLorentzVector *jet, TLorentzVector *parton){
  double jet_Phi = jet->Phi(), parton_Phi = parton->Phi();
  return (parton_Phi - jet_Phi)/jet_Phi;
}


