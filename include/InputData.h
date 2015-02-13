#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <vector>
#include <TLorentzVector.h>

class InputData {

public:
   InputData( void );
   ~InputData( void );

   float                           lheV_pt               ;
   float                           genWeight             ;
   std::vector<int  >*		   genParticle_pdgId 	 ;
   std::vector<int  >*		   genParticle_status 	 ;
   std::vector<float>*		   genParticle_pt    	 ;
   std::vector<float>*  	   genParticle_mass  	 ;
   std::vector<float>*		   genParticle_e     	 ;
   std::vector<float>*		   genParticle_eta   	 ;
   std::vector<float>*		   genParticle_phi   	 ;
   std::vector<std::vector<int> >* genParticle_mother 	 ;
   std::vector<std::vector<int> >* genParticle_dau   	 ;
   
   int                             nlep              	 ;
   std::vector<float>*    	   lep_e             	 ;
   std::vector<float>*  	   lep_eta           	 ;
   std::vector<float>*  	   lep_pt            	 ;
   std::vector<float>*  	   lep_phi           	 ;
   std::vector<int  >*  	   lep_type	     	 ;
   std::vector<float>*  	   lep_pfDeltaCorrRelIso ;
   std::vector<float>*  	   lep_trackIso          ;   
   std::vector<int  >*  	   lep_tightId           ;
   std::vector<int  >*  	   lep_isHEEP            ;   
   std::vector<float>*             lep_chargedHadIsoBoost;
   std::vector<float>*             lep_neutralHadIsoBoost;
   std::vector<float>*             lep_photonIsoBoost    ;
   std::vector<int  >*             lep_isHighPtMuon      ;
   std::vector<int  >*  	   lep_isGlobalMuon	 ;
   
   float 	           	   MET                   ;
   std::vector<float>* 	           MET_et                ;
//   std::vector<float>* 	           MET_sumEt             ;
   std::vector<float>* 	           MET_phi               ;
   
   int                             njetsAK4          	 ;
   std::vector<float>*		   jetAK4_pt	     	 ;
   std::vector<float>*		   jetAK4_eta	     	 ;
   std::vector<float>*		   jetAK4_phi	     	 ;
   std::vector<float>*		   jetAK4_e	     	 ;
   std::vector<float>*		   jetAK4_csv	     	 ;
   std::vector<int  >*		   jetAK4_flavor	 ;
   std::vector<bool  >*  	   jetAK4_IDLoose        ;  
   std::vector<int  >*  	   jetAK4_IDLooseInt        ;  
   std::vector<float>*             jetAK4_JEC            ;
   
   int                             njetsAK8          	 ;
   std::vector<float>*		   jetAK8_pt	     	 ;
   std::vector<float>*		   jetAK8_eta	     	 ;
   std::vector<float>*		   jetAK8_phi	     	 ;
   std::vector<float>*		   jetAK8_e	     	 ;
   std::vector<float>*		   jetAK8_mass	     	 ;
   std::vector<float>*  	   jetAK8_prunedmass     ;
   std::vector<float>*  	   jetAK8_softdropmass   ;
   std::vector<float>*		   jetAK8_csv	     	 ;
   std::vector<int  >*             jetAK8_nm             ;
   std::vector<int  >*             jetAK8_cm             ;
   std::vector<float>*             jetAK8_che            ;
   std::vector<float>*             jetAK8_ne             ;
   std::vector<float>*		   jetAK8_tau1	     	 ;
   std::vector<float>*		   jetAK8_tau2	     	 ;
   std::vector<float>*		   jetAK8_tau3	     	 ;
   std::vector<bool  >*  	   jetAK8_IDLoose        ;  
   std::vector<int  >*  	   jetAK8_IDLooseInt        ;  
   std::vector<int   >*  	   jetAK8_flavor         ;
   std::vector<int   >*  	   jetAK8_nconstituents  ;
   std::vector<float>*             jetAK8_JEC            ;
      
   int                             njetsAK8pruned    	 ;
   std::vector<float>*		   jetAK8pruned_pt   	 ;
   std::vector<float>*		   jetAK8pruned_eta  	 ;
   std::vector<float>*		   jetAK8pruned_phi  	 ;
   std::vector<float>*		   jetAK8pruned_e    	 ;
   std::vector<float>*		   jetAK8pruned_mass 	 ;

   int                             njetsAK8softdrop    	 ;
   std::vector<float>*		   jetAK8softdrop_pt   	 ;
   std::vector<float>*		   jetAK8softdrop_eta  	 ;
   std::vector<float>*		   jetAK8softdrop_phi  	 ;
   std::vector<float>*		   jetAK8softdrop_e    	 ;
   std::vector<float>*		   jetAK8softdrop_mass 	 ;

   std::vector<int  >*             nPUTrue               ;
   std::vector<int  >*             bX                    ;
   int                             nPVs                  ; 
   float                           rho                   ;
   int                             EVENT_event           ;
   int                             EVENT_run             ;
   int                             EVENT_lumi            ;

   std::vector<bool>*              triggerResult;
   bool isFired_HLT_PFHT900_v1 ;
   bool isFired_HLT_AK8PFJet360TrimMod_Mass30_v1;
              
private:
   
};

#endif // INPUTDATA_H
