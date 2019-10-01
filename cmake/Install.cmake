######################################################################################################################################################
#                                                        D E F A U L T    G E N E R A T O R S                                                        #
######################################################################################################################################################


# Default the Binary generators: problem is that none of the CPACK_BINARY_<GenName> will show up in CMakeCache,
# which makes it less clear what will happen in terms of package generation
#if(WIN32)
  #set(CPACK_GENERATOR "IFW;ZIP")
#elseif(APPLE)
  #set(CPACK_GENERATOR "IFW;TGZ")
#elseif(UNIX)
  #set(CPACK_GENERATOR "STGZ;TGZ")
#endif()



# So instead, let's cache the default value we want for the individual options for CPACK_BINARY_<GenName>
if (UNIX)

  # Set everything to off for now
  set(CPACK_BINARY_DEB     OFF CACHE BOOL "Recommended OFF")
  set(CPACK_BINARY_FREEBSD OFF CACHE BOOL "Recommended OFF")
  set(CPACK_BINARY_RPM     OFF CACHE BOOL "Recommended OFF")
  set(CPACK_BINARY_TBZ2    OFF CACHE BOOL "Recommended OFF")
  set(CPACK_BINARY_NSIS    OFF CACHE BOOL "Recommended OFF")

  if(APPLE)
    set(CPACK_BINARY_IFW ON CACHE BOOL "Enable to build IFW package, which is the recommended method")
    set(CPACK_BINARY_STGZ    OFF CACHE BOOL "Recommended OFF")

    # Mac Specific options to turn off
    set(CPACK_BINARY_BUNDLE        OFF CACHE BOOL "Recommended OFF")
    set(CPACK_BINARY_DRAGNDROP     OFF CACHE BOOL "Recommended OFF")
    set(CPACK_BINARY_OSXX11        OFF CACHE BOOL "Recommended OFF")
    set(CPACK_BINARY_PACKAGEMAKER  OFF CACHE BOOL "This was the legacy method on Apple, superseded by IFW.")
    set(CPACK_BINRARY_PRODUCTBUILD OFF CACHE BOOL "Recommended OFF")

  else()
    set(CPACK_BINARY_IFW     OFF CACHE BOOL "This should be off")
    set(CPACK_BINARY_STGZ ON CACHE BOOL "Enable to build a Linux sh installer script, which is the recommended method") # Uses STGZ currently (install .sh script CACHE BOOL)

    # Unix (non Apple CACHE BOOL) specific option to turn off
    set(CPACK_BINARY_TZ  OFF CACHE BOOL "Recommended OFF")
  endif()
  # Tar.gz for inclusion in other programs for eg
  set(CPACK_BINARY_TGZ    ON CACHE BOOL "Enable to build a tar.gz package, recommended for an official release")


elseif(WIN32)
  set(CPACK_BINARY_IFW    ON CACHE BOOL "Enable to build IFW package, which is the recommend method")
  set(CPACK_BINARY_ZIP    ON CACHE BOOL "Enable to build a ZIP package, recommended for an official release")

  set(CPACK_BINARY_NSIS  OFF CACHE BOOL "This was the legacy method on Windows, superseded by IFW")
  set(CPACK_BINARY_7Z    OFF CACHE BOOL "Recommended OFF")
  set(CPACK_BINARY_NUGET OFF CACHE BOOL "Recommended OFF")
  set(CPACK_BINARY_WIX   OFF CACHE BOOL "Recommended OFF")


  # TODO: the "FORCE" is temporary to avoid people having an existing build directory build IFW, remove after next release
  # We want to force update the cache to avoid user suddenly getting build errors
  if(CPACK_BINARY_NSIS)
    set(CPACK_BINARY_NSIS  OFF CACHE BOOL "This was the legacy method on Windows, superseded by IFW" FORCE)
    set(CPACK_BINARY_IFW    ON CACHE BOOL "Enable to build IFW package, which is the recommend method" FORCE)
    message("Switching from NSIS to IFW as the supported generator has changed on Windows")
  endif()

endif()


# Turn off source generators
# Need a list, which can't be empty, but not have sensible defined value. So a list of two empty element works as
# a workaround
# list(CPACK_SOURCE_GENERATOR ";")

# Instead use indiv CPACK_SOURCE_<GenName>: all to OFF
if (UNIX)

  set(CPACK_SOURCE_RPM  OFF CACHE BOOL "Recommended OFF")
  set(CPACK_SOURCE_TBZ2 OFF CACHE BOOL "Recommended OFF")
  set(CPACK_SOURCE_TGZ  OFF CACHE BOOL "Recommended OFF")
  set(CPACK_SOURCE_TXZ  OFF CACHE BOOL "Recommended OFF")
  set(CPACK_SOURCE_TZ   OFF CACHE BOOL "Recommended OFF")
  set(CPACK_SOURCE_ZIP  OFF CACHE BOOL "Recommended OFF")

elseif(WIN32)

  set(CPACK_SOURCE_7Z  OFF CACHE BOOL "Recommended OFF")
  set(CPACK_SOURCE_ZIP OFF CACHE BOOL "Recommended OFF")
endif()


######################################################################################################################################################
#                                              B A S E    I N S T A L L   &    P R O J E C T    I N F O                                              #
######################################################################################################################################################

# Base install
set(CPACK_INSTALL_CMAKE_PROJECTS
  "${CMAKE_BINARY_DIR};EnergyPlus;ALL;/"
)

if( BUILD_FORTRAN )
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/ExpandObjects/;ExpandObjects;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/ReadVars/;ReadVars;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/Transition/;Transition;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/Basement/;Basement;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/HVAC-Diagram/;HVAC-Diagram;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/ParametricPreprocessor/;ParametricPreprocessor;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/Slab/;Slab;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/ConvertESOMTR/;ConvertESOMTR;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/CalcSoilSurfTemp/;CalcSoilSurfTemp;ALL;/")
  list(APPEND CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}/src/AppGPostProcess/;AppGPostProcess;ALL;/")
endif()

set(CPACK_PACKAGE_VENDOR "US Department of Energy" )
set(CPACK_IFW_PACKAGE_PUBLISHER "${CPACK_PACKAGE_VENDOR}")

set(CPACK_PACKAGE_CONTACT "Edwin Lee <edwin.lee@nrel.gov>")
set(CPACK_PACKAGE_DESCRIPTION "EnergyPlus is a whole building energy simulation program that engineers, architects, and researchers use to model both energy consumption and water use in buildings.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "EnergyPlus is a whole building energy simulation program.")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/Modules")

set(CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_VERSION_MAJOR}" )
set(CPACK_PACKAGE_VERSION_MINOR "${CMAKE_VERSION_MINOR}" )
set(CPACK_PACKAGE_VERSION_PATCH "${CMAKE_VERSION_PATCH}" )
set(CPACK_PACKAGE_VERSION_BUILD "${CMAKE_VERSION_BUILD}" )

set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${CPACK_PACKAGE_VERSION_BUILD}")
# Default the debian package name to include version to allow several versions to be installed concurrently instead of overwriting any existing one
# set(CPACK_DEBIAN_PACKAGE_NAME "energyplus-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(CPACK_IFW_PRODUCT_URL "https://www.energyplus.net")
# set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://www.energyplus.net")

include(cmake/TargetArch.cmake)
target_architecture(TARGET_ARCH)

if ( "${CMAKE_BUILD_TYPE}" STREQUAL "" OR "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${TARGET_ARCH}")
else()
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${TARGET_ARCH}-${CMAKE_BUILD_TYPE}")
endif()

# Installation directory on the target system (common to all CPack Genrators)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}-${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH}")

if( WIN32 AND NOT UNIX )
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
  include(InstallRequiredSystemLibraries)
  if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
    install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION "./")
  endif()
endif()

install(FILES "${CMAKE_SOURCE_DIR}/LICENSE.txt" DESTINATION "./" COMPONENT Licenses)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")

install( FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Energy+.idd" DESTINATION ./ )
install( FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Energy+.schema.epJSON" DESTINATION ./ )

INCLUDE(CPack)

