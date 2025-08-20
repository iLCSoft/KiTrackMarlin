#ifndef VXDHitSimple_h
#define VXDHitSimple_h

#include "KiTrack/IHit.h"

#include "ILDImpl/SectorSystemVXD.h"



namespace KiTrackMarlin{
   
   
   /** A hit 
    */   
   class VXDHitSimple : public IHit{
      
      
   public:
      
      VXDHitSimple( float x , float y , float z , int layer , int phi, int theta, const SectorSystemVXD* const sectorSystemVXD );
      
      VXDHitSimple(const VXDHitSimple&) = default;
      VXDHitSimple& operator=(const VXDHitSimple&) = default;
      VXDHitSimple( VXDHitSimple&&) = default;
      VXDHitSimple& operator=(VXDHitSimple&&) = default;
      ~VXDHitSimple() override = default;

      const ISectorSystem* getSectorSystem() const override { return _sectorSystemVXD; };

   private:
      
      int _layer;
      int _phi;
      int _theta;
      
      const SectorSystemVXD* _sectorSystemVXD;
      
      //void calculateSector(){ _sector = _sectorSystemVXD->getSector( _side, _layer , _module , _sensor ); }
      
   };
   
}


#endif

