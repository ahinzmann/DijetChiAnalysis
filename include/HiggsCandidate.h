#ifndef HIGGSCANDIDATE_H
#define HIGGSCANDIDATE_H

#include "../DijetChiAnalysis/include/RecoCandidate.h"

class HiggsCandidate : public RecoCandidate {

public:
   HiggsCandidate( TLorentzVector tlv );
   ~HiggsCandidate( void );
      
private:

};

#endif // HIGGSCANDIDATE_H



