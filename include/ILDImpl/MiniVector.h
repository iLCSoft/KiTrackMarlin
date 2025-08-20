#ifndef MINIVECTOR_H
#define MINIVECTOR_H 1

#include <lcio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <EVENT/TrackerHit.h>
#include "UTIL/LCTrackerConf.h"
#include "KiTrack/IHit.h"

#include "marlin/VerbosityLevels.h"

#include "ILDImpl/SectorSystemVXD.h"

#include <vector>
#include <math.h>

#include <marlin/Global.h>

using namespace lcio ;


namespace KiTrackMarlin{
  
  
  class MiniVector : public IHit{

  public:
    
    TrackerHitVec HitVec{};
    
    // Class constructor
    MiniVector(EVENT::TrackerHit * outer, EVENT::TrackerHit * inner);
    
    MiniVector(TrackerHitVec hitPair);
    
    MiniVector(const MiniVector&) = default;
    MiniVector& operator=(const MiniVector&) = default;
    MiniVector( MiniVector&&) = default;
    MiniVector& operator=(MiniVector&&) = default;
    ~MiniVector() override = default;

    // returns the TrackerHitVec 
    TrackerHitVec getTrackerHitVec() ;
    
    // Gives the layer of the inner hit
    //int getLayer() ;
    
    // Gives the azimuth angle of the mini-vector
    double getPhi() ;
    
    // Gives the polar angle of the mini-vector
    double getTheta() ;
    
    // Gives the 2-D angle between two minivectors
    //double get2DAngle(MiniVector MinVec1, MiniVector MinVec2) ;
    
    // Gives the 3-D angle between two minivectors
    double get3DAngleMV(MiniVector *MinVec2) ;
    
    double * getXYZ() ;
    
    // Gives the position of the mini-vector
    double * getPosition() ;

    const ISectorSystem* getSectorSystem() const override { return _sectorSystemVXD; };


  protected:

    const SectorSystemVXD* _sectorSystemVXD{nullptr};
    
  };

}




#endif
