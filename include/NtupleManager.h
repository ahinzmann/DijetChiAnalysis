#ifndef NTUPLEMANAGER_H
#define NTUPLEMANAGER_H

#include "../DijetChiAnalysis/include/InputData.h"

class SCycleBase;

class NtupleManager {

public:
   NtupleManager( SCycleBase * theAnalysis );
   ~NtupleManager( void );
   
   void ConnectVariables( std::string treeName );
   void ConnectVariablesDijetTuple( std::string treeName );
   InputData getData( void ){return theData_;}
   
private:
   SCycleBase* theAnalysis_;
   InputData   theData_    ;
   
};

#endif // NTUPLEMANAGER_H
