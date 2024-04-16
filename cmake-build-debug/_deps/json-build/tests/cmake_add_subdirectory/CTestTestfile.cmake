# CMake generated Testfile for 
# Source directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_add_subdirectory
# Build directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-build/tests/cmake_add_subdirectory
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_add_subdirectory_configure "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "-G" "Ninja" "-DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++" "-Dnlohmann_json_source=/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src" "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_add_subdirectory/project")
set_tests_properties(cmake_add_subdirectory_configure PROPERTIES  FIXTURES_SETUP "cmake_add_subdirectory" LABELS "not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_add_subdirectory/CMakeLists.txt;1;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_add_subdirectory/CMakeLists.txt;0;")
add_test(cmake_add_subdirectory_build "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "--build" ".")
set_tests_properties(cmake_add_subdirectory_build PROPERTIES  FIXTURES_REQUIRED "cmake_add_subdirectory" LABELS "not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_add_subdirectory/CMakeLists.txt;8;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_add_subdirectory/CMakeLists.txt;0;")
