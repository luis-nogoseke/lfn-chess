project(${CMAKE_PROJECT_NAME}_tests)

# Clone Google Test
set(GOOGLETEST_DIR ${CMAKE_SOURCE_DIR}/tests/lib/googletest)
if(NOT EXISTS ${GOOGLETEST_DIR})
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone https://github.com/google/googletest ${GOOGLETEST_DIR}
    )
endif()

set(CMAKE_CXX_FLAGS "-Wno-c++98-compat")
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Unit_Tests_run
    bitboard_tests.cc
    board_tests.cc
)

target_link_libraries(Unit_Tests_run gtest gtest_main)
