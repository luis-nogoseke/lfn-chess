find_package(GTest REQUIRED)

add_executable(unit_tests bitboard_tests.cc board_tests.cc square_tests.cc)

target_link_libraries(unit_tests PRIVATE GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
