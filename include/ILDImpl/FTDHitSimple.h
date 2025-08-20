#ifndef FTDHitSimple_h
#define FTDHitSimple_h

#include "KiTrack/IHit.h"

#include "ILDImpl/SectorSystemFTD.h"



namespace KiTrackMarlin{
   
   
   /** A hit 
    */   
   class FTDHitSimple : public IHit{
      
      
   public:
      
      FTDHitSimple( float x , float y , float z , int side, unsigned layer , unsigned module, unsigned sensor, const SectorSystemFTD* const sectorSystemFTD );

      FTDHitSimple(const FTDHitSimple&) = default;
      FTDHitSimple& operator=(const FTDHitSimple&) = default;
      FTDHitSimple( FTDHitSimple&&) = default;
      FTDHitSimple& operator=(FTDHitSimple&&) = default;
      ~FTDHitSimple() override = default;

      const ISectorSystem* getSectorSystem() const override { return _sectorSystemFTD; };
      

   private:
      
      int _side;
      unsigned _layer;
      unsigned _module;
      unsigned _sensor;
      
      const SectorSystemFTD* _sectorSystemFTD;
      
      void calculateSector(){ _sector = _sectorSystemFTD->getSector( _side, _layer , _module , _sensor ); }
      
   };
   
}


#endif

