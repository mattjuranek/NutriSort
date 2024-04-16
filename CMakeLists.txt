cmake_minimum_required(VERSION 3.27)
project(Project3DSA)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3DSA main.cpp
        Food.h
        Food.cpp)

include(FetchContent)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG        1.6.2
)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(json)

if(json_POPULATED)
    include_directories(${json_SOURCE_DIR}/single_include)
endif()

set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(Project3DSA PRIVATE cpr::cpr sfml-system sfml-window sfml-graphics sfml-audio)