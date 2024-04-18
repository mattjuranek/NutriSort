cmake_minimum_required(VERSION 3.27)
project(Project3DSA)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_executable(Project3DSA main.cpp
        Food.h
        Food.cpp)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

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

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(json)

if(json_POPULATED)
    include_directories(${json_SOURCE_DIR}/single_include)
endif()


set(SFML_DIR $ENV{SFML_DIR})
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(Project3DSA PRIVATE cpr::cpr sfml-system sfml-window sfml-graphics sfml-audio)
target_compile_features(Project3DSA PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET Project3DSA
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Project3DSA>
            VERBATIM)
endif()

install(TARGETS Project3DSA)