#include "RocCorrUtil.h"

RocCorrUtil::RocCorrUtil(TString data){
  cout<<"[RocCorrUtil: initilizeing RoccoR as: "<<data.Data()<<endl;
  RC.init( data.Data() );
}
RocCorrUtil::~RocCorrUtil(){
}

void RocCorrUtil::CalcScaleAndError(Muon& mu, int s, int m, const ULong64_t event, vector<Gen> gens, const bool IsDATA ){
   //TODO check from Rochester correctiontwiki 
	 /*
	 -------------------------------------------------------------------------------------
	 Following variations are provided to estimate uncertainties.
	 -------------------------------------------------------------------------------------
	          set        nmembers    comment
	 Default  0          1           default, reference based on madgraph sample, with adhoc ewk (sw2eff and Z width) and Z pt (to match data) weights.
	 Stat     1          100         pre-generated stat. replicas;
	 Zpt      2          1           derived without reweighting reference pt to data.
	 Ewk      3          1           derived without applying ad-hoc ewk weights
	 deltaM   4          1           one representative set for alternative profile deltaM mass window
	 Ewk2     5          1           weight reference from constant to s-dependent Z width
	 -------------------------------------------------------------------------------------
	 For statistical replicas, std. dev. gives uncertainty.
	 For the rest, difference wrt the cental is assigned as syst. error.
	 Total uncertainty is calculated as a quadrature sum of all components.
	 -------------------------------------------------------------------------------------
	 -------------------------------------------------------------------------------------
	 */

    // copy & pasted from SKFlatMaker: https://github.com/CMSSNU/SKFlatMaker/blob/Run2Legacy_v3/SKFlatMaker/src/SKFlatMaker.cc#L1815
    double this_roccor = 1.;
    double this_roccor_err = 0.;

    if(mu.Pt()>10.){

      //==== Data
      if(IsDATA){
        this_roccor = RC.kScaleDT(mu.Charge(), mu.Pt(), mu.Eta(), mu.Phi(), 0, 0); //data
        this_roccor_err = RC.kScaleDTerror(mu.Charge(), mu.Pt(), mu.Eta(), mu.Phi());
      }
      else{
	  gRandom->SetSeed( event );
          double u = gRandom->Rndm();

          // check there is a matched gen muon then use the gen pt in kSpreadMC() 
          int counter=0;
          double this_genpt=-999.;
          double mindr = 0.2;
          for(unsigned int i=0; i<gens.size(); i++){

            Gen gen = gens.at(i);

            if( fabs(gen.PID()) != 13 ) continue;
            if( gen.Status() != 1 ) continue;

            double this_dr = gen.DeltaR( mu );
            if( this_dr < mindr ){
              this_genpt = gen.Pt();
              mindr = this_dr;
            }
         }



         if(this_genpt>0){
           this_roccor     = RC.kSpreadMC     (mu.Charge(), mu.Pt(), mu.Eta(), mu.Phi(), this_genpt, s, m);
           this_roccor_err = RC.kSpreadMCerror(mu.Charge(), mu.Pt(), mu.Eta(), mu.Phi(), this_genpt);
         }
         else{
           this_roccor     = RC.kSmearMC     (mu.Charge(), mu.Pt(), mu.Eta(), mu.Phi(), mu.GetTrackerLayersWithMeasurement(), u, s, m);
           this_roccor_err = RC.kSmearMCerror(mu.Charge(), mu.Pt(), mu.Eta(), mu.Phi(), mu.GetTrackerLayersWithMeasurement(), u);
         }
      }
    }
    mu.SetMomentumScaleAndError(this_roccor, this_roccor_err);
}
