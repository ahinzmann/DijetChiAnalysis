// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $

// Local include(s):
#include "../DijetChiAnalysis/include/ChiAnalysis.h"
#include "../DijetChiAnalysis/include/Utilities.h"
#include "../DijetChiAnalysis/include/HistosManager.h"
#include "../DijetChiAnalysis/include/NtupleManager.h"
#include "../DijetChiAnalysis/include/MatchingTools.h"

#include <iostream>

ClassImp( ChiAnalysis );

ChiAnalysis::ChiAnalysis()
   : SCycleBase()
   , weight_(1.)
   , lheweight_(1.)
   , puweight_(1.)
   , lumiweight_(1.) {

   SetLogName( GetName() );

   /* general settings */   
   DeclareProperty( "InputTreeName"    , InputTreeName_     );
   DeclareProperty( "OutputTreeName"   , OutputTreeName_    );
   DeclareProperty( "isSignal"         , isSignal_	    );
   DeclareProperty( "runOnMC"          , runOnMC_	    );
   DeclareProperty( "Trigger"          , Trigger_	    );
   DeclareProperty( "runOnDijetTuple"          , runOnDijetTuple_	    );

   /* weights settings */
   DeclareProperty( "LHEsample"         , LHEsample_	      );
   DeclareProperty( "xSec"              , xSec_  	      );
   DeclareProperty( "genEvents"         , genEvents_	      );
   DeclareProperty( "Lumi"              , Lumi_  	      );
   DeclareProperty( "PUdata"            , PUProfileData_      );
      
   theHistosManager_ = new HistosManager( this );
   theNtupleManager_ = new NtupleManager( this );
   
   nEvents_                 = 0;
   nPassedTrigger_                 = 0;
   n2Jets_	   = 0;  
   nJetID_	   = 0;  
   nJetPt_	   = 0;  
   nJetRapidity_	 = 0;  
   nDijetChi_	      = 0;  
   nDijetYboost_	 = 0;  
   nDijetMass_         = 0;  
}

ChiAnalysis::~ChiAnalysis() {

   if( theHistosManager_ ){
      delete theHistosManager_;
      theHistosManager_ = 0;
   }
   
   if( theNtupleManager_ ){
      delete theNtupleManager_;
      theNtupleManager_ = 0;
   }

}

void ChiAnalysis::BeginCycle() throw( SError ) {

   initWeight();    

   return;

}

//==============================================================================================
void ChiAnalysis::initWeight( void ){

   PUWeight::Scenario sc = PUWeight_.toScenario("PUS10");
   PUWeight_.initPUWeights(PUProfileData_,sc); 

   LHEWeight::Sample sm = LHEWeight_.toSample(LHEsample_);
   LHEWeight_.initLHEWeights(sm);

}

void ChiAnalysis::EndCycle() throw( SError ) {

   return;

}

void ChiAnalysis::BeginInputData( const SInputData& ) throw( SError ) {

   theHistosManager_->bookHistos(); 

   DeclareVariable( dijet_mass  , "dijet_mass"   , OutputTreeName_.c_str() );
   DeclareVariable( dijet_chi   , "dijet_chi"	 , OutputTreeName_.c_str() );  
   DeclareVariable( dijet_yboost, "dijet_yboost" , OutputTreeName_.c_str() );  
   DeclareVariable( weight_     , "weight"    , OutputTreeName_.c_str() );
   DeclareVariable( puweight_   , "puweight"  , OutputTreeName_.c_str() );
   DeclareVariable( lumiweight_ , "lumiweight", OutputTreeName_.c_str() );
     
   return;

}

//==============================================================================================
void ChiAnalysis::initData( void ){

   data_ = theNtupleManager_->getData();
   
}

//==============================================================================================
void ChiAnalysis::setWeight( TString infile ){

   if( !runOnMC_ ) return;

   //for( unsigned int v = 0; v < (data_.nPUTrue)->size(); ++v ){
   //   if( (*data_.bX)[v] == 0 ) puweight_ = PUWeight_.getPUWeight( (*data_.nPUTrue)[v] );
   //}
      
   //lheweight_ = LHEWeight_.getLHEWeight(data_.lheV_pt);
   lheweight_ = data_.genWeight;
      
   double lumiw = xSec_/genEvents_;
      
   lumiweight_ = lumiw*LumiWeight_.getLumiWeight( infile );
      
   weight_ = puweight_*lheweight_*lumiweight_;

   //std::cout << "pu w " << puweight_ << " lumi w " << lumiweight_;
   //std::cout << " tot w " << weight_ << std::endl; 
   
}


void ChiAnalysis::EndInputData( const SInputData& ) throw( SError ) {

   printCutFlow();                  
   theHistosManager_->formatHistos();

   Hist( "nEvents"                 )->SetBinContent(0,genEvents_              );
   Hist( "nEvents"	    	   )->SetBinContent(1,nEvents_  	      );
   Hist( "nEvents"         	   )->SetBinContent(2,nPassedTrigger_	      );
   Hist( "nEvents"         	   )->SetBinContent(3,n2Jets_	      );
   Hist( "nEvents"         	   )->SetBinContent(4,nJetID_	      );
   Hist( "nEvents"         	   )->SetBinContent(5,nJetPt_	      );
   Hist( "nEvents"         	   )->SetBinContent(6,nJetRapidity_	      );
   Hist( "nEvents"         	   )->SetBinContent(7,nDijetYboost_	      );
   Hist( "nEvents"         	   )->SetBinContent(8,nDijetChi_	      );
   Hist( "nEvents"         	   )->SetBinContent(9,nDijetMass_	      );
   
   m_logger << INFO << std::endl; 
   m_logger << INFO << "############ Cut flow: ############" << std::endl;     
   m_logger << INFO << "number of events		                         " << nEvents_ << std::endl;
   m_logger << INFO << "passed trigger		                                 " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 

   m_logger << INFO << std::endl; 
   
   return;

}

void ChiAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {

   if (runOnDijetTuple_)
     theNtupleManager_->ConnectVariablesDijetTuple( InputTreeName_ );
   else 
     theNtupleManager_->ConnectVariables( InputTreeName_ );

   return;

}

void ChiAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {

   initData();
      
   nEvents_++;
   
   passedTrigger_=passedTrigger();
   if(passedTrigger_)
      nPassedTrigger_++;
   if ( (Trigger_) && (!passedTrigger_) ) throw SError( SError::SkipEvent );  

   if( passedSelections() ){

       TString infile = TString(this->GetHistInputFile()->GetName());
	                       
       setWeight(infile);
       
       fillHistos();
   } 
   else 
      throw SError( SError::SkipEvent );
         
   return;

}

//==============================================================================================
bool ChiAnalysis::passedTrigger( void ){

   if( data_.isFired_HLT_PFHT900_v1 ){ return true;}
   else if( data_.isFired_HLT_AK8PFJet360TrimMod_Mass30_v1 ){ return true;}
   else if(data_.triggerResult) {
     bool pass=false;
     for( unsigned int v = 0; v < (data_.triggerResult)->size(); ++v )
        if((*data_.triggerResult)[v]) pass=true;
     return pass;
   }

   return false;
    
}

//==============================================================================================
bool ChiAnalysis::passedSelections( void ){

   if(data_.njetsAK4<2) return false;
   n2Jets_++;  
   if(data_.jetAK4_IDLoose) {
      if( (*data_.jetAK4_IDLoose)[0] != 1 ) return false;
      if( (*data_.jetAK4_IDLoose)[1] != 1 ) return false;
   } else if(data_.jetAK4_IDLooseInt) {
      if( (*data_.jetAK4_IDLooseInt)[0] != 1 ) return false;
      if( (*data_.jetAK4_IDLooseInt)[1] != 1 ) return false;
   } else return false;
   nJetID_++;  

   jet1.SetPtEtaPhiE( (*data_.jetAK4_pt)[0], (*data_.jetAK4_eta)[0], (*data_.jetAK4_phi)[0], (*data_.jetAK4_e)[0] );
   jet2.SetPtEtaPhiE( (*data_.jetAK4_pt)[1], (*data_.jetAK4_eta)[1], (*data_.jetAK4_phi)[1], (*data_.jetAK4_e)[1] );
   dijet=jet1+jet2;

   dijet_mass = dijet.M();
   dijet_chi = exp(fabs(jet1.Rapidity()-jet2.Rapidity()));
   dijet_yboost = fabs(jet1.Rapidity()+jet2.Rapidity());

   if( jet1.Pt() <= 100. ) return false;
   if( jet2.Pt() <= 100. ) return false;
   nJetPt_++;  

   if( jet1.Rapidity() >= 2.5 ) return false;
   if( jet2.Rapidity() >= 2.5 ) return false;
   nJetRapidity_++;  

   if( dijet_yboost >= 1.11 ) return false;
   nDijetYboost_++;  
   if( dijet_chi >= 16. ) return false;
   nDijetChi_++;  
   if( dijet_mass<=500. ) return false;
   nDijetMass_++;  

   return true;

}

//==============================================================================================
void ChiAnalysis::fillHistos( void ){
         
   /* dijet */
   Hist( "dijet_mass"            )->Fill( dijet_mass, weight_ );
   Hist( "dijet_mass_triggered"            )->Fill( dijet_mass, weight_*passedTrigger_ );
   Hist( "dijet_chi"             )->Fill( dijet_chi, weight_ );
   Hist( "dijet_yboost"          )->Fill( dijet_yboost, weight_ );
   Hist( "jet1_pt"          )->Fill( jet1.Pt(), weight_ );
   Hist( "jet2_pt"          )->Fill( jet2.Pt(), weight_ );
   Hist( "jet1_y"          )->Fill( jet1.Rapidity(), weight_ );
   Hist( "jet2_y"          )->Fill( jet2.Rapidity(), weight_ );
   Hist( "jet1_phi"          )->Fill( jet1.Phi(), weight_ );
   Hist( "jet2_phi"          )->Fill( jet2.Phi(), weight_ );
   Hist( "deltaPtSumPt"          )->Fill( (jet1.Pt()-jet2.Pt())/(jet1.Pt()+jet2.Pt()), weight_ );
   Hist( "sumPt"          )->Fill( jet1.Pt()+jet2.Pt(), weight_ );
//   if(MET>0)
//     Hist( "metSumEt"          )->Fill( data_.MET/data_.sumEt, weight_ );
//   else
//     Hist( "metSumEt"          )->Fill( (*data_.MET_et)[0]/(*data_.MET_sumEt)[0], weight_ );
   
   /* other histos */
   Hist( "genweight"        	 )->Fill( lheweight_ );
   Hist( "PUWeights"        	 )->Fill( puweight_ );
   Hist( "nVertices"        	 )->Fill( data_.nPVs, weight_ );

}

//==============================================================================================
void ChiAnalysis::printCutFlow( void ) {

   std::cout << std::endl; 
   std::cout << "############ Cut flow: ############" << std::endl;	
   std::cout << "number of events		                         " << nEvents_ << std::endl;
   std::cout << "passed trigger		                                 " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
   std::cout << "2 jets		                                 " << n2Jets_ << " --- eff = " << (double)n2Jets_/nEvents_ << std::endl; 
   std::cout << "jet ID		                                 " << nJetID_ << " --- eff = " << (double)nJetID_/nEvents_ << std::endl; 
   std::cout << "jet pT		                                 " << nJetPt_ << " --- eff = " << (double)nJetPt_/nEvents_ << std::endl; 
   std::cout << "jet rapidity		                                 " << nJetRapidity_ << " --- eff = " << (double)nJetRapidity_/nEvents_ << std::endl; 
   std::cout << "dijet yboost		                                 " << nDijetYboost_ << " --- eff = " << (double)nDijetYboost_/nEvents_ << std::endl; 
   std::cout << "dijet chi		                                 " << nDijetChi_ << " --- eff = " << (double)nDijetChi_/nEvents_ << std::endl; 
   std::cout << "dijet mass		                                 " << nDijetMass_ << " --- eff = " << (double)nDijetMass_/nEvents_ << std::endl; 

   std::cout << std::endl; 

   
}
