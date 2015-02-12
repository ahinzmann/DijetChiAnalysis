// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $
#ifndef ChiAnalysis_H
#define ChiAnalysis_H

// SFrame include(s):
#include "core/include/SCycleBase.h"

#include "TLorentzVector.h"

#include "../DijetChiAnalysis/include/InputData.h"
#include "../DijetChiAnalysis/include/PUWeight.h"
#include "../DijetChiAnalysis/include/LHEWeight.h"
#include "../DijetChiAnalysis/include/LumiWeight.h"

class HistosManager;
class NtupleManager;

/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here
 * @version $Revision: 344 $
 */
class ChiAnalysis : public SCycleBase {

public:
   /// Default constructor
   ChiAnalysis();
   /// Default destructor
   ~ChiAnalysis();

   /// Function called at the beginning of the cycle
   virtual void BeginCycle() throw( SError );
   /// Function called at the end of the cycle
   virtual void EndCycle() throw( SError );

   /// Function called at the beginning of a new input data
   virtual void BeginInputData( const SInputData& ) throw( SError );
   /// Function called after finishing to process an input data
   virtual void EndInputData  ( const SInputData& ) throw( SError );

   /// Function called after opening each new input file
   virtual void BeginInputFile( const SInputData& ) throw( SError );

   /// Function called for every event
   virtual void ExecuteEvent( const SInputData&, Double_t ) throw( SError );

   void setWeight                 ( TString infile );
   void initWeight                ( void );
   
   void initData                  ( void );
   void reset                     ( void );
   InputData& getData             ( void ){ return data_; }
   void setNtupleManager          ( NtupleManager* ntupleManager ){ theNtupleManager_ = ntupleManager; }
   void printCutFlow              ( void );

   void fillHistos                ( void );

   bool passedSelections          ( void );
   bool passedTrigger             ( void );

private:
   //
   // Put all your private variables here
   //

   // Macro adding the functions for dictionary generation
   ClassDef( ChiAnalysis, 0 );

   HistosManager* theHistosManager_;
   NtupleManager* theNtupleManager_;
   InputData      data_            ;
   PUWeight       PUWeight_        ;
   LHEWeight      LHEWeight_       ;
   LumiWeight     LumiWeight_      ;

   // XML configuration //
   
   /* general settings */         
   std::string    InputTreeName_   ;
   std::string    OutputTreeName_  ;   
   bool           isSignal_        ;
   bool           runOnMC_         ;
   bool           Trigger_         ;

   /* weights settings */            
   std::string    LHEsample_       ;
   double         xSec_            ;
   double         genEvents_       ;
   double         Lumi_            ;
   std::string    PUProfileData_   ;
      
   float weight_      ;
   float lheweight_   ;
   float puweight_    ;
   float lumiweight_  ;

   float  dijet_mass  ;
   float  dijet_chi   ;
   float  dijet_yboost;
   
   int    nEvents_    ;
   int    nPassedTrigger_         ;  
   int    n2Jets_         ;  
   int    nJetID_         ;  
   int    nJetPt_         ;  
   int    nJetRapidity_         ;  
   int    nDijetChi_         ;  
   int    nDijetYboost_         ;  
   int    nDijetMass_         ;  

   TLorentzVector jet1, jet2, dijet;

}; // class ChiAnalysis

#endif // ChiAnalysis_H

