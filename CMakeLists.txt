cmake_minimum_required(VERSION 3.27)
project()

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3DSA main.cpp)

include(FetchContent)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG        1.6.2
)

FetchContent_MakeAvailable(cpr)
target_link_libraries(Project3DSA PRIVATE cpr::cpr)