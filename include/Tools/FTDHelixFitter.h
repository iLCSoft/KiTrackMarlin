#ifndef FTDHelixFitter_h
#define FTDHelixFitter_h

#include "EVENT/Track.h"
#include "EVENT/TrackerHit.h"

#include "lcio.h"



using namespace lcio;



class FTDHelixFitterException : public std::exception {
   
   
protected:
   std::string message ;
   
   FTDHelixFitterException(){  /*no_op*/ ; } 
   
public: 
   virtual ~FTDHelixFitterException() throw() { /*no_op*/; } 
   
   FTDHelixFitterException( const std::string& text ){
      message = "FTDHelixFitterException: " + text ;
   }
   
   virtual const char* what() const  throw() { return  message.c_str() ; } 
   
};



/** A class to make it quick to fit a track or hits and get back the chi2 and Ndf values and
 * also bundle the code used for that, so it doesn't have to be copied all over the places.
 * Uses a helix fit from the MarlinTrk class HelixFit.cc
 * It is named FTDHelixFitter, because it makes some assumptions about the hits, that come from them
 * being on the FTD. Specifically the errors passed to the helix fit are calculated on the assumption,
 * that du and dv are errors in the xy plane.
 * If this class is intended to be used for hits on different detectors, a careful redesign is necessary!
 */
class FTDHelixFitter{
   
   
public:
   
   FTDHelixFitter( Track* track ) throw( FTDHelixFitterException );
   FTDHelixFitter( std::vector < TrackerHit* > trackerHits ) throw( FTDHelixFitterException );
   
   
   double getChi2(){ return _chi2; }
   int getNdf(){ return _Ndf; }
   
   
   
private:
   
  
   
   void fit()throw( FTDHelixFitterException );
   
   double _chi2;
   int _Ndf;
   
   std::vector< TrackerHit* > _trackerHits;
  
   
};

#endif
