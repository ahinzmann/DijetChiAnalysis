#ifndef HISTOSMANAGER_H
#define HISTOSMANAGER_H

class ChiAnalysis;

class HistosManager {

public:
   HistosManager( ChiAnalysis * theAnalysis );
   ~HistosManager( void );

   void bookHistos       ( void );
   void formatHistos     ( void );
   
private:
   ChiAnalysis* theAnalysis_;
   
};

#endif // HISTOSMANAGER_H
