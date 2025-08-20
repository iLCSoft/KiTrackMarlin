########################################################
# cmake file for building Marlin example Package
# @author Jan Engels, Desy IT
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################


# project name
PROJECT( KiTrackMarlin )


# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 1 )
SET( ${PROJECT_NAME}_VERSION_MINOR 13 )
SET( ${PROJECT_NAME}_VERSION_PATCH 2 )

cmake_policy(SET CMP0008 NEW)

### DEPENDENCIES ############################################################

FIND_PACKAGE( ILCUTIL REQUIRED COMPONENTS ILCSOFT_CMAKE_MODULES ILCTEST )

# load default settings from ILCSOFT_CMAKE_MODULES
INCLUDE( ilcsoft_default_settings )

FIND_PACKAGE( Marlin 1.0 REQUIRED ) # minimum required Marlin version
INCLUDE_DIRECTORIES( SYSTEM ${Marlin_INCLUDE_DIRS} )
LINK_LIBRARIES( ${Marlin_LIBRARIES} )
ADD_DEFINITIONS( ${Marlin_DEFINITIONS} )

FIND_PACKAGE( MarlinUtil 1.0 REQUIRED ) # minimum required MarlinUtil version
INCLUDE_DIRECTORIES( SYSTEM ${MarlinUtil_INCLUDE_DIRS} )
LINK_LIBRARIES( ${MarlinUtil_LIBRARIES} )
ADD_DEFINITIONS( ${MarlinUtil_DEFINITIONS} )

FIND_PACKAGE( KiTrack REQUIRED ) 
INCLUDE_DIRECTORIES( SYSTEM ${KiTrack_INCLUDE_DIRS} )
LINK_LIBRARIES( ${KiTrack_LIBRARIES} )
ADD_DEFINITIONS( ${KiTrack_DEFINITIONS} )

FIND_PACKAGE( MarlinTrk REQUIRED ) 
INCLUDE_DIRECTORIES( SYSTEM ${MarlinTrk_INCLUDE_DIRS} )
LINK_LIBRARIES( ${MarlinTrk_LIBRARIES} )
ADD_DEFINITIONS( ${MarlinTrk_DEFINITIONS} )

FIND_PACKAGE( ROOT REQUIRED ) 
INCLUDE_DIRECTORIES( SYSTEM ${ROOT_INCLUDE_DIRS} )
LINK_LIBRARIES( ${ROOT_LIBRARIES} )
ADD_DEFINITIONS( ${ROOT_DEFINITIONS} )

FIND_PACKAGE( GSL REQUIRED ) 
INCLUDE_DIRECTORIES( SYSTEM ${GSL_INCLUDE_DIRS} )
LINK_LIBRARIES( ${GSL_LIBRARIES} )
ADD_DEFINITIONS( ${GSL_DEFINITIONS} )

FIND_PACKAGE( DD4hep REQUIRED ) 
INCLUDE_DIRECTORIES( SYSTEM ${DD4hep_INCLUDE_DIRS} )
LINK_LIBRARIES( ${DD4hep_LIBRARIES} )
ADD_DEFINITIONS( ${DD4hep_DEFINITIONS} )


FIND_PACKAGE( CLHEP REQUIRED )
IF( CLHEP_FOUND )
        INCLUDE_DIRECTORIES( SYSTEM ${CLHEP_INCLUDE_DIRS} )
        LINK_LIBRARIES( ${CLHEP_LIBRARIES} )
        ADD_DEFINITIONS( ${CLHEP_DEFINITIONS} )
        MESSAGE( STATUS "CLHEP -- found" )
ELSE()
        MESSAGE( STATUS "CLHEP -- not found" )
ENDIF()


### DOCUMENTATION ###########################################################

OPTION( INSTALL_DOC "Set to OFF to skip build/install Documentation" OFF )

IF( INSTALL_DOC AND EXISTS "${PROJECT_SOURCE_DIR}/doc/CMakeLists.txt" )
    ADD_SUBDIRECTORY( ./doc )
ENDIF()



### LIBRARY #################################################################

# definitions to pass to the compiler
#ADD_DEFINITIONS( "-Wall -ansi -pedantic" )
#ADD_DEFINITIONS( "-Wno-long-long" )

# include directories
INCLUDE_DIRECTORIES( BEFORE
   ./include
   )
INSTALL_DIRECTORY( ./include DESTINATION . FILES_MATCHING PATTERN "*.h" )

# add library
AUX_SOURCE_DIRECTORY( ./src/ILDImpl library_sources )
AUX_SOURCE_DIRECTORY( ./src/Tools library_sources )


IF(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
    # exclude Timer.cc on arm64 systems, since it has some x86 assembly statements
    LIST(FILTER library_sources EXCLUDE REGEX "./src/Tools/Timer.cc")
ENDIF()


ADD_SHARED_LIBRARY( ${PROJECT_NAME} ${library_sources} )
INSTALL_SHARED_LIBRARY( ${PROJECT_NAME} DESTINATION lib )


### TESTING #################################################################

MACRO( ADD_UNIT_TEST _name )
    IF( BUILD_TESTING )
        ADD_EXECUTABLE( test_${_name} ${ARGN} )
    ELSE()
        ADD_EXECUTABLE( test_${_name} EXCLUDE_FROM_ALL ${ARGN} )
    ENDIF()        
    TARGET_LINK_LIBRARIES( test_${_name} ${PROJECT_NAME} )
    GET_TARGET_PROPERTY( _executable test_${_name} LOCATION )
    ADD_TEST( t_${_name} ${_executable} )
ENDMACRO()

INCLUDE_DIRECTORIES( ${ILCTEST_INCLUDE_DIRS} )



# display some variables and write them to cache
DISPLAY_STD_VARIABLES()

# generate and install following configuration files
GENERATE_PACKAGE_CONFIGURATION_FILES( KiTrackMarlinConfig.cmake KiTrackMarlinConfigVersion.cmake KiTrackMarlinLibDeps.cmake )
