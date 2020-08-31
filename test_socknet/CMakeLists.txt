cmake_minimum_required(VERSION 3.13)

project(unit_test)

find_package(GTest)

IF(GTest_FOUND)
    # test_code
    set(TEST_APP test_socknet)
    add_executable(${TEST_APP} main.cpp)
    target_link_libraries(${TEST_APP} PRIVATE socknet ${GTEST_BOTH_LIBRARIES} gmock gmock_main pthread)
    get_filename_component(GTEST_LIB_DIR ${GTEST_LIBRARY} DIRECTORY)
    target_link_directories(${TEST_APP} PRIVATE ${GTEST_LIB_DIR})
    target_include_directories(${TEST_APP} PRIVATE ${GTEST_INCLUDE_DIRS})
ENDIF()