cmake_minimum_required(VERSION 4.2)

project(minuetlang VERSION 0.1.0 LANGUAGES CXX)

# set(MINUET_TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(MINUET_LANG_DEMO_DIR ${CMAKE_SOURCE_DIR}/test_suite)

if (NOT DEFINED MINUET_LANG_SRC_DIR)
    message(FATAL_ERROR "Preset invalid because it is missing the MINUET_LANG_SRC_DIR variable.")
endif ()

add_subdirectory(${MINUET_LANG_SRC_DIR})
# enable_testing()
# add_subdirectory(${MINUET_LANG_UNIT_TEST_DIR})
