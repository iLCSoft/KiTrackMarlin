#include "ILDImpl/VXDTrack.h"


#include <algorithm>

#include "UTIL/ILDConf.h"

// Root, for calculating the chi2 probability. 
#include "Math/ProbFunc.h"



using namespace KiTrackMarlin;

// FIX ME
/** @return if the radius of hit a is bigger than that of hit b */

bool compare_IHit_R_3Dhits( IHit* a, IHit* b ){

  double r2_a = fabs((a->getX()*a->getX()) + (a->getY()*a->getY()));
  double r2_b = fabs((b->getX()*b->getX()) + (b->getY()*b->getY()));
   
   return ( r2_a < r2_b ); //compare their radii
   
}



VXDTrack::VXDTrack( MarlinTrk::IMarlinTrkSystem* trkSystem ){
   
   _trkSystem = trkSystem;
   _chi2Prob = 0.;
 
   _lcioTrack = new TrackImpl();
   
   
}
/*
VXDTrack::VXDTrack( std::vector< IVXDHit* > hits , MarlinTrk::IMarlinTrkSystem* trkSystem ){
   
   
   _trkSystem = trkSystem;
   _chi2Prob = 0.;
   
   _lcioTrack = new TrackImpl();
   
   for( unsigned i=0; i < hits.size(); i++ ){
      
      addHit( hits[i] );
      
      
   }
   
}
*/

VXDTrack::VXDTrack( std::vector< IMiniVector* > hits , MarlinTrk::IMarlinTrkSystem* trkSystem ){
   
   
   _trkSystem = trkSystem;
   _chi2Prob = 0.;
   
   _lcioTrack = new TrackImpl();
   
   for( unsigned i=0; i < hits.size(); i++ ){
      
      addHit( hits[i] );
      
      
   }
   
}




VXDTrack::VXDTrack( const VXDTrack& f ){

   //make a new copied lcio track
   _lcioTrack = new TrackImpl( *f._lcioTrack );
   
   
   _hits = f._hits;
   _chi2Prob = f._chi2Prob;
   _trkSystem = f._trkSystem;

}

VXDTrack & VXDTrack::operator= (const VXDTrack & f){
   
   if (this == &f) return *this;   //protect against self assignment
   
   //make a new copied lcio track
   _lcioTrack = new TrackImpl( *f._lcioTrack );
   
   
   _hits = f._hits;
   _chi2Prob = f._chi2Prob;
   _trkSystem = f._trkSystem;
   
   return *this;
   
}


/*
void VXDTrack::addHit( IVXDHit* hit ){
   
   
   
   if ( hit != NULL ){
      
      _hits.push_back( hit );
      
      // and sort the track again
      sort( _hits.begin(), _hits.end(), compare_IHit_R_3Dhits );
      
      
      _lcioTrack->addHit( hit->getTrackerHit() );
      
   }
   
}
*/



void VXDTrack::addHit( IMiniVector* MV ){
   
   
   
   if ( MV != NULL ){

     _hits.push_back( MV );  // so to be able to check the tracks compatibilty

     MiniVector *MinVec = MV->getMiniVector();
     TrackerHitVec HitVec = MinVec->getTrackerHitVec() ;
 
 	  
     for (EVENT::TrackerHitVec::iterator it = HitVec.begin(); it != HitVec.end() ; ++it ){

       EVENT::TrackerHit *trkHit = *it ;   
       
       //_trkhits.push_back( trkHit );
     
       _lcioTrack->addHit( trkHit );
       
     }
     
     // and sort the track again
     //sort( _trkhits.begin(), _trkhits.end(), compare_IHit_R_3Dhits );
     
   }
   
}





void VXDTrack::fit() throw( FitterException ){
   
   
  Fitter fitter( _lcioTrack , _trkSystem , 1 );
   
   
   _lcioTrack->setChi2( fitter.getChi2( lcio::TrackState::AtIP ) );
   _lcioTrack->setNdf( fitter.getNdf( lcio::TrackState::AtIP ) );
   _chi2Prob = fitter.getChi2Prob( lcio::TrackState::AtIP );
   
   TrackStateImpl* trkState = new TrackStateImpl( *fitter.getTrackState( lcio::TrackState::AtIP ) ) ;
   trkState->setLocation( TrackState::AtIP ) ;
   _lcioTrack->addTrackState( trkState );
   
   
}


double VXDTrack::getQI() const{
  
   
   double QI = _chi2Prob;
   
   // make sure QI is between 0 and 1
   if (QI > 1. ) QI = 1.;
   if (QI < 0. ) QI = 0.;
   
   return QI;
   
}

/*
double VXDTrack::getPT() const{

  double Omega = _lcioTrack->getOmega();
  double PT = fabs((0.3*3.5)/(1000*Omega));

  return PT ;

}
*/



