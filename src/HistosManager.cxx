#include "include/HistosManager.h"
#include "include/ChiAnalysis.h"
#include "include/Utilities.h"

#include <TH1F.h>
#include <TH2F.h>

////////////////////////////////////////////////////////////////////
HistosManager::HistosManager( ChiAnalysis* theAnalysis ):theAnalysis_( theAnalysis )
{

}

////////////////////////////////////////////////////////////////////
HistosManager::~HistosManager( void ){

}

////////////////////////////////////////////////////////////////////
void HistosManager::bookHistos( void ){

   /* dijet */
   theAnalysis_->Book( TH1F( "dijet_mass"    	    , "dijet mass" 	     ,    130,  0. , 13000.) );
   theAnalysis_->Book( TH1F( "dijet_chi"    	    , "dijet chi" 	     ,    15,   1. ,  16.  ) );
   theAnalysis_->Book( TH1F( "dijet_yboost"    	    , "dijet yboost" 	     ,    15,   0. ,  1.5  ) );
   theAnalysis_->Book( TH1F( "jet1_pt"    	    , "jet 1 pt" 	     ,    60,  0. , 6000.) );
   theAnalysis_->Book( TH1F( "jet2_pt"    	    , "jet 2 pt" 	     ,    60,  0. , 6000.) );
   theAnalysis_->Book( TH1F( "jet1_y"    	    , "jet 1 y" 	     ,    60,  -2.5 , 2.5) );
   theAnalysis_->Book( TH1F( "jet2_y"    	    , "jet 2 y" 	     ,    60,  -2.5 , 2.5) );
   theAnalysis_->Book( TH1F( "jet1_phi"    	    , "jet 1 phi" 	     ,    60,  -3.41 , 3.41) );
   theAnalysis_->Book( TH1F( "jet2_phi"    	    , "jet 2 phi" 	     ,    60,  -3.41 , 3.41) );
   theAnalysis_->Book( TH1F( "deltaPtSumPt"    	    , "deltaPt / sumPt" 	     ,    50,  0.,1.) );
   theAnalysis_->Book( TH1F( "sumPt"    	    , "sumPt" 	     ,    130,  0. , 13000.) );
//   theAnalysis_->Book( TH1F( "metSumEt"    	    , "met / sumEt" 	     ,    50,  -1.,1.) );
 
   /* other histos */
   theAnalysis_->Book( TH1F( "genweight"            , "gen weight"           ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "PUWeights"            , "pu weights"           ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "nVertices"            , "number of PVs"        ,    40,  0. ,   40.  ) );
  
}

////////////////////////////////////////////////////////////////////
void HistosManager::formatHistos( void ){

   /* MWH */         
   theAnalysis_->Hist( "dijet_mass"        )->GetXaxis()->SetTitle( "dijet mass [GeV]"           	    );
   theAnalysis_->Hist( "dijet_chi"        )->GetXaxis()->SetTitle( "#chi_{dijet}"           	    );
   theAnalysis_->Hist( "dijet_yboost"        )->GetXaxis()->SetTitle( "y_{boost}"           	    );
   theAnalysis_->Hist( "jet1_pt"        )->GetXaxis()->SetTitle( "p_{T,1}"           	    );
   theAnalysis_->Hist( "jet2_pt"        )->GetXaxis()->SetTitle( "p_{T,2}"           	    );
   theAnalysis_->Hist( "jet1_y"        )->GetXaxis()->SetTitle( "y_{1}"           	    );
   theAnalysis_->Hist( "jet2_y"        )->GetXaxis()->SetTitle( "y_{2}"           	    );
   theAnalysis_->Hist( "jet1_phi"        )->GetXaxis()->SetTitle( "#phi_{1}"           	    );
   theAnalysis_->Hist( "jet2_phi"        )->GetXaxis()->SetTitle( "#phi_{2}"           	    );
   theAnalysis_->Hist( "deltaPtSumPt"        )->GetXaxis()->SetTitle( "(p_{T,1}-p_{T,2})/(p_{T,1}+p_{T,2})"           	    );
   theAnalysis_->Hist( "sumPt"        )->GetXaxis()->SetTitle( "(p_{T,1}+p_{T,2})"           	    );
//   theAnalysis_->Hist( "metSumEt"        )->GetXaxis()->SetTitle( "E_{T}^{miss} / #Sum E_{T}"           	    );

   theAnalysis_->Book( TH1F( "nEvents"                , "nEvents"	    	 ,   11, -0.5,    10.5 ) );

   /* other histos */
   theAnalysis_->Hist( "genweight"            )->GetXaxis()->SetTitle( "gen weight"			    );
   theAnalysis_->Hist( "PUWeights"            )->GetXaxis()->SetTitle( "PU weights"			    );
   theAnalysis_->Hist( "nVertices"            )->GetXaxis()->SetTitle( "# primary vertices"                 );

   Utilities::OverflowToLast( theAnalysis_->Hist( "dijet_mass"	      ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "genweight"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "PUWeights"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "nVertices"         ) );
      
}
