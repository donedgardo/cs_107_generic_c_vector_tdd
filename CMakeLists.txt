cmake_minimum_required(VERSION 3.14)
project(vector-kata)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  vector_test 
  tests/vector_tests.cc
)

add_library(vector STATIC
  src/vector.h
  src/vector.c
  src/vector_error.h
  src/bool.h
)
target_include_directories(vector PUBLIC src)
set_target_properties(vector PROPERTIES LINKER_LANGUAGE C)

target_link_libraries(vector_test 
  PRIVATE 
    vector
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector_test)
