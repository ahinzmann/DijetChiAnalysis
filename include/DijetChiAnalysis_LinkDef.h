// Dear emacs, this is -*- c++ -*-
// $Id$
#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

// Add the declarations of your cycles, and any other classes for which you
// want to generate a dictionary, here. The usual format is:
//
// #pragma link C++ class MySuperClass+;

#pragma link C++ class ChiAnalysis+;
#pragma link C++ class std::vector< std::vector<int> >+;
#pragma link C++ class std::vector< std::vector<float> >+;
#pragma link C++ class std::vector< TLorentzVector >+;

#endif // __CINT__
