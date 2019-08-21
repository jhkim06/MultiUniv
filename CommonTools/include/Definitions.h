#ifndef Definitions_h
#define Definitions_h
#define DEFAULT -9999

enum class DiLepCh{
  ElElOS, ElElPP,ElElMM, MuMuOS, MuMuPP, MuMuMM, NA
};

enum class SingleLepCh{
  Mu, El, NA
};

enum class LeptonType{
    electron, muon
};

enum class SysUpDown{
    Central, Up, Down
};

#endif
