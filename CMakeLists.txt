cmake_minimum_required(VERSION 3.9)

project("lfn-chess" CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)


# Base options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# enable compiler warnings
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# enable cache system
include(cmake/Cache.cmake)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
  #
  # consider breaking this out per project as necessary
  target_precompile_headers(
    project_options
    INTERFACE
    <vector>
    <string>)
endif()

#####################################################
set(SOURCE_FILES src/main.cc)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

include_directories(src)
include_directories(include)
#####################################################

# Build tests

if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests")
  add_subdirectory(tests)
endif()

#####################################################
