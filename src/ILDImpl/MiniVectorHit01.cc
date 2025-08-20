#include "ILDImpl/MiniVectorHit01.h"
#include "ILDImpl/SectorSystemVXD.h"

#include "UTIL/LCTrackerConf.h"
#include <UTIL/ILDConf.h>

#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace KiTrackMarlin;


MiniVectorHit01::MiniVectorHit01( MiniVector* miniVector , const SectorSystemVXD* const sectorSystemVXD ){
   
   
   _sectorSystemVXD = sectorSystemVXD;
   
   _miniVector = miniVector;

   _phiMV = miniVector->getPhi() ;

   _thetaMV = miniVector->getTheta() ;

   TrackerHitVec HitVec = miniVector->getTrackerHitVec();

   UTIL::BitField64  cellID( LCTrackerCellID::encoding_string() );
   cellID.setValue( HitVec[1]->getCellID0() );
   
   int layer = cellID[ LCTrackerCellID::layer() ] ; // +1 to take into account the IP (considered as layer 0 ) 
   int det_id = 0 ;
   det_id  = cellID[lcio::LCTrackerCellID::subdet()] ;
   if ( det_id == lcio::ILDDetID::SIT) { layer = layer + 6; } 
   
   //Set the position of the VXDHit01
   const double* pos= miniVector->getPosition();
   _x = pos[0];
   _y = pos[1]; 
   _z = pos[2]; 

   double _cosTheta = cos(miniVector->getTheta());
   double phi = miniVector->getPhi();
   // double theta = miniVector->getTheta() ;

   if (phi < 0.) phi = phi + 2*M_PI;

   // YV, for debugging. Calculate sector here and not through the IVXHit base class
   //calculateSector();
   _sector = _sectorSystemVXD->getSector( layer, phi, _cosTheta );
   
   //We assume a real hit. If it is virtual, this has to be set.
   _isVirtual = false;
   
   
}


