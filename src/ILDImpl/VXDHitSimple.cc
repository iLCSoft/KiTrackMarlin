#include "ILDImpl/VXDHitSimple.h"


using namespace KiTrackMarlin;

VXDHitSimple::VXDHitSimple( float x , float y , float z , int layer , int phi, int theta, const SectorSystemVXD* const sectorSystemVXD ) :
   _layer(layer), _phi(phi), _theta(theta), _sectorSystemVXD(sectorSystemVXD)
{
   _x = x;
   _y = y; 
   _z = z; 

   _sector = _sectorSystemVXD->getSector( layer, phi, theta );  // maybe a good idea to calculate a sector for the IP hit as well  
   //calculateSector();
   
   
   //We assume a real hit. If it is virtual, this has to be set.
   _isVirtual = false;
}
