#ifndef RootHelper_h
#define RootHelper_h

#include "TH2.h"

//using namespace std;
//
//class RootHelper{
//  public:
//    RootHelper();
//    ~RootHelper();
//
//    double GetBinContentUser(TH2* hist,double valx,double valy,int sys);
//
//  private:
//    int abc;
//
//    //ClassDef(RootHelper,1)
//};
//
namespace RootHelper {
  double GetBinContentUser(TH2* hist,double valx,double valy,int sys);
}

#endif
