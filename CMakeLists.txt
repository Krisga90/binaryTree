cmake_minimum_required(VERSION 3.16)

project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(LIBRARY_NAME Library)
set(EXECUTABLE_NAME app)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(AddGitSubmodule)
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v2.13.9
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG  v1.13.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(configured)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)
