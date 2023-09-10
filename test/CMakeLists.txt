cmake_minimum_required(VERSION 3.20)

project(OrionEngineTests)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG 2d4f208765af7fa376b878860a7677ecc0bc390a
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  rapidcheck
  GIT_REPOSITORY https://github.com/emil-e/rapidcheck.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(rapidcheck)

# Add the extras/gtest include directory to the project's include paths
include_directories(${rapidcheck_SOURCE_DIR}/extras/gtest/include)

enable_testing()

add_executable(
  hello_test
  hello_test.cc
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  rapidcheck
  OrionEngineLib
)

include(GoogleTest)
gtest_discover_tests(hello_test)