# v01-11

* 2017-06-20 Andre Sailer ([PR#4](https://github.com/iLCSoft/KiTrackMarlin/pull/4))
  - Adapt to DD4hep namespace change

* 2017-05-18 Frank Gaede ([PR#3](https://github.com/iLCSoft/KiTrackMarlin/pull/3))
  - remove all references to Gear and MarlinKalTest

# v01-10


# v01-09
F. Gaede
* made compatible with c++11
* removed -ansi -pedantic -Wno-long-long
* fixed narrowing in initializer lists
* added std to i/ofstream

Y. Voutsinas
* VXD cellular automaton can cope with mini-vectors made of 1 D hits


# v01-08
* M /KiTrackMarlin/trunk/src/Tools/Fitter.cc
* make track state at calo compatible with old sim/rec again
* fixed creation of track state at calo


# v01-07
* added workaround to Tools/Fitter.cc for getting the correct system ID of the calorimeter face (barrel and endcap) if run w/ lcgeo output ( F.Gaede ) -> depends now on DD4hep


# v01-06
* replaced hardcoded B-Field in tools/Fitter with gear::BField ( R.Simoniello)

# v01-05
* Implementation of classes for tracking at VXD using mini* vectors, based on the cellular automaton algorithm

# v01-04
* KiTrackMarlinTools: added convenience methods for output of track-hit information


# v01-03-01
* Modified to match TrackStateImpl copy constructor, uses const reference instead of pointer. 


# v01-03
* Removed FTDHit00 as it is not used or supported anymore
* Removed FTDSecCon00 as it is not used or supported anymore
* Renamed FTDSecCon01 to FTDSectorConnector
* Changed weight of chi2 in RPhi and Z for the FTDHelixFitter 

# v01-02
* Fitter now accepts 6 degrees of freedom or more (instead of 8 as until now)
* Added FTDHelixFitter class, to fast fit a track with the HelixFit class from MarlinTrk

# v01-01
* no more dynamic castings in FTDTrack -> the added hits have to be IFTDHits
* Added doxygen mainpage

# v01-00
* first version: splitted the software from the ForwardTracking package at version v01-02
