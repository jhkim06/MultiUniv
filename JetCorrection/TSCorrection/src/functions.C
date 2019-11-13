#include "functions.h"
#include "TF1.h"

Double_t DoubleSidedSrystalFnc(Double_t* x, Double_t* par){

  Double_t xcur = x[0];
  Double_t N = par[0];
  Double_t mu = par[1];
  Double_t sigma = par[2];
  Double_t alpha_low = fabs(par[3]);
  Double_t n_low = par[4];
  Double_t alpha_high = fabs(par[5]);
  Double_t n_high = par[6];
  
  Double_t z = (xcur - mu)/sigma;
  Double_t f=0.;

  if(z<-alpha_low){
    f = N*exp(-0.5*alpha_low*alpha_low)*pow(alpha_low/n_low*(n_low/alpha_low-alpha_low-z),-n_low);
  }
  else if(z>alpha_high){
    f = N*exp(-0.5*alpha_high*alpha_high)*pow(alpha_high/n_high*(n_high/alpha_high-alpha_high+z),-n_high);
  }
  else{
    f = N*exp(-0.5*z*z);
  }

  return f;
}


Double_t CrystalFnc(Double_t* x, Double_t* par){

  Double_t xcur = x[0];
  Double_t N = par[0];
  Double_t mu = par[1];
  Double_t sigma = par[2];
  Double_t alpha =par[3];
  Double_t n = par[4];
  TF1* exp = new TF1("exp","exp(x)",1e-20,1e20);
 
  Double_t A; Double_t B; Double_t C; Double_t D;

  A = pow((n/alpha), n)*exp->Eval(-alpha*alpha/2);
  B = n/alpha - alpha;	
  Double_t f;
  if ((xcur-mu)/sigma > (-1)*alpha)
    f = N*exp->Eval((-1)*(xcur-mu)*(xcur-mu)/(2*sigma*sigma));
  else
    f = N*A*pow((B-(xcur-mu)/sigma),(-1*n));
  delete exp;

 return f;
} // end of function

Double_t ResponseFittingFunction(Double_t *x, Double_t *par){

  return par[0]+par[1]*sqrt(x[0])+par[2]*x[0]+par[3]/x[0];

} // end of function

Double_t SigmaErrorFittingFunction(Double_t *x, Double_t *par) {
  return exp(par[0]+par[1]*x[0]+par[2]/x[0])+par[3];
} // end of function

TString ResponseFittingFunction(){
  return "%f+%f*sqrt(x)+%f*x+%f/x";
} // end of function

TString SigmaErrorFittingFunction(){
 return "exp(%f+%f*x+%f/x)+%f";
} // end of function

TString Double_t_to_TString(Double_t num){
  std::stringstream s;
  s << fixed << setprecision(2) << num; // two decimal place precision.
  return s.str();
}

void AddCMSSimulation(TCanvas* c1){
  /*
  c1.cd();
  TString cmsText = "CMS";
  TString extraText = "Simulation";
  int cmsTextFont = 61;
  int extraTextFont = 52;
  double cmsTextSize = 0.95;
  double extraTextSize = cmsTextSize*0.76;

  TLatex latex = TLatex();
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  latex.SetTextFont(cmsTextFont);
  latex.SetTextSize(cmsTextSize);
  //latex.SetTextAlign();
  latex.DrawLatex(posX_,poxY_,cmsText);
  //
  latex.SetTextFont(extraTextFont);
  latex.SetTextSize(extraTextSize);
  //latex.SetTextAlign();

  latex.DrawLatex(posX_,posY_-extra_posY,extraText);
  */
}

