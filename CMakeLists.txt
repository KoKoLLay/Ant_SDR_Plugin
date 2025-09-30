cmake_minimum_required(VERSION 3.14)

project(AntSDRPlugin LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FindPkgConfig)

############################ Suscan AD9361 plugin ##############################
pkg_check_modules(SIGUTILS  REQUIRED sigutils>=0.3)
pkg_check_modules(SUSCAN    REQUIRED suscan>=0.3)
pkg_check_modules(SNDFILE   REQUIRED sndfile>=1.0.2)
pkg_check_modules(FFTW3     REQUIRED fftw3f>=3.0)
pkg_check_modules(LIBIIO    REQUIRED libiio>=0.24)
pkg_check_modules(LIBAD9361 REQUIRED libad9361>=0.2)
file(REAL_PATH "~/.suscan/plugins" SUSCAN_DEFAULT_PLUGIN_PATH EXPAND_TILDE)
set(PLUGIN_DIRECTORY "${SUSCAN_DEFAULT_PLUGIN_PATH}" CACHE STRING "Suscan plugin installation directory")

# AD9361 plugin
set(AD9361_SOURCES 2rx_ad9361.c Registration_ad9361.c)
set(AD9361_HEADERS 2rx_ad9361.h)

add_library(2rx_ad9361 SHARED ${AD9361_SOURCES} ${AD9361_HEADERS})

target_include_directories(
  2rx_ad9361 SYSTEM PUBLIC
  ${SNDFILE_INCLUDE_DIRS}
  ${SIGUTILS_INCLUDE_DIRS}
  ${SUSCAN_INCLUDE_DIRS}
  ${FFTW3_INCLUDE_DIRS}
  ${LIBIIO_INCLUDE_DIRS}
  ${LIBAD9361_INCLUDE_DIRS})

target_compile_options(2rx_ad9361 PRIVATE ${SIGUTILS_CFLAGS} ${SUSCAN_CFLAGS})

target_link_libraries(
  2rx_ad9361
  PRIVATE ${LIBIIO_LIBRARIES} ${LIBAD9361_LIBRARIES})

target_include_directories(2rx_ad9361 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

########################### SigDigger AntSDR plugin ############################
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets OpenGLWidgets)

list(TRANSFORM Qt6Core_INCLUDE_DIRS APPEND "/.." OUTPUT_VARIABLE DEFAULT_PLUGIN_PREFIX)

set(SUWIDGETS_PREFIX "${DEFAULT_PLUGIN_PREFIX}" CACHE STRING "SuWidgets install directory prefix")
set(SIGDIGGER_PREFIX "${DEFAULT_PLUGIN_PREFIX}" CACHE STRING "SigDigger install directory prefix")

list(TRANSFORM SUWIDGETS_PREFIX APPEND "/include/SuWidgets" OUTPUT_VARIABLE SUWIDGETS_INSTALL_HEADERS)
list(TRANSFORM SIGDIGGER_PREFIX APPEND "/include/SigDigger" OUTPUT_VARIABLE SIGDIGGER_INSTALL_HEADERS)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

set(ANTSDRPLUGIN_SOURCES
  Registration_AntSDRPlugin.cpp
  AD9361SourcePage.cpp
  AD9361SourcePageFactory.cpp
  CoherentChannelForwarder.cpp
  CoherentDetector.cpp
  PhaseComparator.cpp
  PhaseComparatorFactory.cpp
  PhasePlotPage.cpp
  PhasePlotPageFactory.cpp
  Polarimeter.cpp
  PolarimeterFactory.cpp
  PolarimetryPage.cpp
  PolarimetryPageFactory.cpp
  RawChannelForwarder.cpp
  SimplePhaseComparator.cpp)

set(ANTSDRPLUGIN_HEADERS
  AD9361SourcePage.h
  AD9361SourcePageFactory.h
  CoherentChannelForwarder.h
  CoherentDetector.h
  PhaseComparator.h
  PhaseComparatorFactory.h
  PhasePlotPage.h
  PhasePlotPageFactory.h
  Polarimeter.h
  PolarimeterFactory.h
  PolarimetryPage.h
  PolarimetryPageFactory.h
  RawChannelForwarder.h
  SimplePhaseComparator.h)

set(ANTSDRPLUGIN_UI
  AD9361SourcePage.ui
  PhaseComparator.ui
  PhasePlotPage.ui
  Polarimeter.ui
  PolarimetryPage.ui)

qt_standard_project_setup()

qt_add_library(
  AntSDRPlugin SHARED 
  ${ANTSDRPLUGIN_SOURCES}
  ${ANTSDRPLUGIN_HEADERS}
  ${ANTSDRPLUGIN_UI})

target_include_directories(
  AntSDRPlugin SYSTEM PUBLIC
  ${SUWIDGETS_INSTALL_HEADERS}
  ${SIGDIGGER_INSTALL_HEADERS}
  ${SNDFILE_INCLUDE_DIRS}
  ${SIGUTILS_INCLUDE_DIRS}
  ${SUSCAN_INCLUDE_DIRS}
  ${FFTW3_INCLUDE_DIRS})

target_compile_options(
  AntSDRPlugin PRIVATE
  ${SIGUTILS_CFLAGS} ${SUSCAN_CFLAGS})

target_link_libraries(
  AntSDRPlugin
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

target_compile_definitions(AntSDRPlugin PRIVATE ANTSDRPLUGIN_LIBRARY)

target_include_directories(AntSDRPlugin INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


############################# Plugin install ###################################
install(TARGETS AntSDRPlugin 2rx_ad9361 DESTINATION ${PLUGIN_DIRECTORY})

