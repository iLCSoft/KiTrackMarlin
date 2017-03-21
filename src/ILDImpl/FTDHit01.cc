#include "ILDImpl/FTDHit01.h"


#include "UTIL/LCTrackerConf.h"

using namespace KiTrackMarlin;


FTDHit01::FTDHit01( TrackerHit* trackerHit , const SectorSystemFTD* const sectorSystemFTD ){
   
   
   _sectorSystemFTD = sectorSystemFTD;
   
   _trackerHit = trackerHit;

   //Set the position of the FTDHit01
   const double* pos= trackerHit->getPosition();
   _x = pos[0];
   _y = pos[1]; 
   _z = pos[2]; 


   //find out layer, module, sensor

   UTIL::BitField64  cellID( LCTrackerCellID::encoding_string() );

   cellID.setValue( trackerHit->getCellID0() );
     
   _side   = cellID[ LCTrackerCellID::side() ];
   _module = cellID[ LCTrackerCellID::module() ];
   _sensor = cellID[ LCTrackerCellID::sensor() ] - 1;
   _layer = cellID[ LCTrackerCellID::layer() ] + 1;
   
   
   calculateSector();
   
   
   //We assume a real hit. If it is virtual, this has to be set.
   _isVirtual = false;
   
   
}


