# CMake generated Testfile for 
# Source directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import
# Build directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-build/tests/cmake_import
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_import_configure "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "-G" "Ninja" "-A" "" "-DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++" "-Dnlohmann_json_DIR=/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-build" "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import/project")
set_tests_properties(cmake_import_configure PROPERTIES  FIXTURES_SETUP "cmake_import" LABELS "not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import/CMakeLists.txt;1;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import/CMakeLists.txt;0;")
add_test(cmake_import_build "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "--build" ".")
set_tests_properties(cmake_import_build PROPERTIES  FIXTURES_REQUIRED "cmake_import" LABELS "not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import/CMakeLists.txt;9;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import/CMakeLists.txt;0;")
