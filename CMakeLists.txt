cmake_minimum_required(VERSION 3.9)
project("lfn-chess" CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -ggdb")

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-Weverything COMPILER_SUPPORTS_EVERYTHING)
if(COMPILER_SUPPORTS_EVERYTHING)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything  -ggdb")
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} supports -Weverything.")
endif()


#####################################################
set(SOURCE_FILES src/main.cc)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

include_directories(src)
include_directories(include)
#####################################################

# Build tests
add_subdirectory(tests)
#####################################################

# Doxygen Build
option(BUILD_DOC "Build Documentation" ON)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR ${CMAKE_SOURCE_DIR}/build/docs)
    if(NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif()

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
#####################################################
