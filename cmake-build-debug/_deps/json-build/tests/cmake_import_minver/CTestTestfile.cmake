# CMake generated Testfile for 
# Source directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import_minver
# Build directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-build/tests/cmake_import_minver
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_import_minver_configure "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "-G" "Ninja" "-A" "" "-DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++" "-Dnlohmann_json_DIR=/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-build" "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import_minver/project")
set_tests_properties(cmake_import_minver_configure PROPERTIES  FIXTURES_SETUP "cmake_import_minver" LABELS "not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import_minver/CMakeLists.txt;1;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import_minver/CMakeLists.txt;0;")
add_test(cmake_import_minver_build "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "--build" ".")
set_tests_properties(cmake_import_minver_build PROPERTIES  FIXTURES_REQUIRED "cmake_import_minver" LABELS "not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import_minver/CMakeLists.txt;9;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_import_minver/CMakeLists.txt;0;")
