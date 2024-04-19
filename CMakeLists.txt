cmake_minimum_required(VERSION 3.27)
project(NutriSort)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

cmake_policy(SET CMP0148 NEW)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.6.2
)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)

set(CPR_BUILD_TESTS_SSL OFF)

FetchContent_MakeAvailable(SFML cpr json)

include_directories(${cpr_SOURCE_DIR}/include)  # Placed after FetchContent_MakeAvailable

add_executable(NutriSort main.cpp Food.h Food.cpp)

if(json_POPULATED)
    include_directories(${json_SOURCE_DIR}/single_include)
endif()


target_link_libraries(NutriSort PRIVATE cpr::cpr sfml-system sfml-window sfml-graphics sfml-audio)


install(TARGETS NutriSort)
