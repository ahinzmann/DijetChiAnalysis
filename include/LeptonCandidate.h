#ifndef LEPTONCANDIDATE_H
#define LEPTONCANDIDATE_H

#include "../DijetChiAnalysis/include/RecoCandidate.h"

class LeptonCandidate : public RecoCandidate {

public:
   LeptonCandidate( TLorentzVector tlv );
   ~LeptonCandidate( void );
     
   double iso;
   double scale;
      
private:

};

#endif // LEPTONCANDIDATE_H


