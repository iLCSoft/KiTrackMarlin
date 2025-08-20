#include "ILDImpl/VXDSectorConnector.h"


using namespace KiTrackMarlin;


// Constructor
VXDSectorConnector::VXDSectorConnector( const SectorSystemVXD* sectorSystemVXD , unsigned layerStepMax, unsigned lastLayerToIP, int neighPhi, int neighTheta, int layerMax ) :
   _sectorSystemVXD  (sectorSystemVXD ),
   _layerStepMax  (layerStepMax ),
   _nLayers  (sectorSystemVXD->getNLayers()),
   _lastLayerToIP  (lastLayerToIP ),
   _nDivisionsInPhi  (sectorSystemVXD->getPhiSectors()),
   _nDivisionsInTheta  (sectorSystemVXD->getThetaSectors()),
   _layerMax  (layerMax ),
   _neighTheta  (neighTheta ),
   _neighPhi  (neighPhi )
{}



std::set< int > VXDSectorConnector::getTargetSectors ( int sector ){
   
   
   std::set <int> targetSectors;

   //std::cout << " check : n layers " << _nLayers << " n phi divisions " << _nDivisionsInPhi << " n theta divisions " << _nDivisionsInTheta << std::endl ;

   // Decode the sector integer,  and take the layer, phi and theta bin
   
   int iTheta = sector/(_nLayers*_nDivisionsInPhi) ;
   
   int iPhi = ((sector - (iTheta*_nLayers*_nDivisionsInPhi)) / _nLayers) ;
   
   int layer = sector - (iTheta*_nLayers*_nDivisionsInPhi) - (iPhi*_nLayers) ; 

   // search for sectors at the neighbouring theta nad phi bins

   int iPhi_Up    = iPhi + _neighPhi;
   int iPhi_Low   = iPhi - _neighPhi;
   int iTheta_Up  = iTheta + _neighTheta; 
   int iTheta_Low = iTheta - _neighTheta;
   if (iTheta_Low < 0) iTheta_Low = 0;
   if (static_cast<unsigned>(iTheta_Up)  >= _nDivisionsInTheta) iTheta_Up = _nDivisionsInTheta-1;
   
   //*************************************************************************************

   //streamlog_out(DEBUG2) << " checking sector " << sector << " layer " << layer << " phi " << iPhi << " theta " << iTheta <<std::endl ;
   
   for( unsigned layerStep = 1; layerStep <= _layerStepMax; layerStep++ ){
     
     if ( layer >= static_cast<int>(layerStep) ){ // +1 makes sense if I use IP as innermost layer
       
       int layerTarget = layer - layerStep;

        if (layerTarget >= 0 && layerTarget < _layerMax ){   // just a test to run cellular automaton over the whole VXD - SIT
	 
	 for (int jPhi = iPhi_Low ; jPhi <= iPhi_Up ; jPhi++){

	   int ip = jPhi;
	   
	   // catch wrap-around
	   if (ip < 0) ip = _nDivisionsInPhi-1;          
	   if (ip >= static_cast<int>(_nDivisionsInPhi)) ip = ip - _nDivisionsInPhi;
	   
	   for (int jTheta = iTheta_Low ; jTheta <= iTheta_Up ; jTheta++){
	     
	     targetSectors.insert( _sectorSystemVXD->getSector ( layerTarget , ip , jTheta ) );
	     
	   }
	 }
       }
     }
   }
   

   if ( layer > 0 && ( layer <= static_cast<int>(_lastLayerToIP) ) ){
      
     unsigned layerTarget = 0;
      
     for (int ip = iPhi_Low ; ip <= iPhi_Up ; ip++){
       
       for (int jTheta = iTheta_Low ; jTheta <= iTheta_Up ; jTheta++){
	 
	 streamlog_out(DEBUG1) << " VXDSectorConnector: from layer " << layer << " to layer " << layerTarget << std::endl ;
	 
	 targetSectors.insert( 0 ) ;
       }
     }
   }
   
										 
   return targetSectors;
   
   
}


