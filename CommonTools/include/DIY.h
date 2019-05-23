#ifndef DIY_h
#define DIY_h

#include <vector>

using namespace std;
typedef vector<double>::const_iterator doubleIter;


namespace DIY {

struct orderingD{
  bool operator () (pair<size_t, doubleIter> const& a, pair<size_t, doubleIter> const& b){
    return *(a.second) > *(b.second);
  }
};

}

#endif
