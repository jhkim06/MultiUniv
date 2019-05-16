#include "functions.h"
#include "TF1.h"

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

TString Double_t_to_TString(Double_t num){
  std::stringstream s;
  s << fixed << setprecision(2) << num; // two decimal place precision.
  return s.str();
}
