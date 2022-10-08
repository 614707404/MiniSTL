cmake_minimum_required(VERSION 3.20)
project(MiniSTL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://gitee.com/mirrors/googletest/repository/archive/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()
# set(CMAKE_BUILD_TYPE RELEASE)
include_directories(include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(src SRC_LIST)
aux_source_directory(test TEST_LIST)
add_executable(main ${SRC_LIST})
add_executable(UniTest ${TEST_LIST})

target_link_libraries(
  UniTest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(UniTest)