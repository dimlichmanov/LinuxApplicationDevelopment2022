# You can run tests with ctest
# ctest --verbose gives more information
# make test gives the same result
# running "make DoCov" gives verbose test information and generates HTML report


cmake_minimum_required(VERSION 3.14)
project(11_Testing)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

# Header-only library Growable Buffers for C99
add_library(GB INTERFACE)
target_include_directories(GB INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/GB99)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CodeCoverage)
append_coverage_compiler_flags()

#I have chosen Unity framnework for testing. Static library libunity.a is put to the Unity root directory
add_executable(testage test.c)
target_link_libraries(testage gcov ${CMAKE_CURRENT_SOURCE_DIR}/Unity/libunity.a GB)
target_include_directories(testage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Unity/src)

# Needs gcovr to generate HTML
setup_target_for_coverage_gcovr_html(
            NAME DoCov
            EXECUTABLE testage
    )


add_test(suite_1_test testage)