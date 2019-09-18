# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.13/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

#conan_check(VERSION 1.0.0 REQUIRED)

conan_add_remote(NAME bincrafters
  URL https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(REQUIRES 
  boost_filesystem/1.69.0@bincrafters/stable
  BASIC_SETUP CMAKE_TARGETS NO_OUTPUT_DIRS
  BUILD missing
)

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/third_party/FMI2/ )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR} )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/src/EnergyPlus/public )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/src/EnergyPlus )

set(src
  EPFMI.hpp
  EPFMI.cpp
  EPFMI_Export.hpp
  Variables.hpp
  Variables.cpp
  ../EnergyPlus/CommandLineInterface.hh 
  ../EnergyPlus/CommandLineInterface.cc 
  ../EnergyPlus/EnergyPlusPgm.cc 
  ../EnergyPlus/public/EnergyPlusPgm.hh 
)

add_library( epfmi SHARED ${src} )
set_target_properties( epfmi PROPERTIES OUTPUT_NAME "epfmi" )

target_link_libraries( epfmi energypluslib CONAN_PKG::boost_filesystem)

install( TARGETS epfmi
  RUNTIME DESTINATION ./bin
  LIBRARY DESTINATION ./lib
  ARCHIVE DESTINATION ./lib
)

install( FILES EPFMI.hpp DESTINATION ./include )

export(TARGETS epfmi APPEND FILE energyplus-exports.cmake)

add_library( epvariables STATIC
  Variables.hpp
  Variables.cpp
  ../EnergyPlus/InputProcessing/IdfParser.hh
  ../EnergyPlus/InputProcessing/IdfParser.cc
)

target_include_directories(epvariables INTERFACE "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/third_party/ObjexxFCL/src/")
target_link_libraries(epvariables energypluslib)

set(test_src
  Test/EPFMI_Test.cpp
  Test/main.cc
)

configure_file( Test/config.h.in "${CMAKE_CURRENT_BINARY_DIR}/test-config.h" )

CREATE_TEST_TARGETS( epfmi "${test_src}" "epfmi" )

set(MY_FMU_RESOURCES "${CMAKE_CURRENT_BINARY_DIR}/MyFMU/resources/")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${MY_FMU_RESOURCES}")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different 
  "${PROJECT_SOURCE_DIR}/testfiles/RefBldgSmallHotelNew2004_Chicago.idf" 
  "${PROJECT_SOURCE_DIR}/weather/USA_IL_Chicago-OHare_TMY2.epw"
  "${PROJECT_BINARY_DIR}/Products/Energy+.idd"
  "${MY_FMU_RESOURCES}/"
)

