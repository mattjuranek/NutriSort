# CMake generated Testfile for 
# Source directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_fetch_content2
# Build directory: /Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-build/tests/cmake_fetch_content2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_fetch_content2_configure "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "-G" "Ninja" "-DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++" "-Dnlohmann_json_source=/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src" "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_fetch_content2/project")
set_tests_properties(cmake_fetch_content2_configure PROPERTIES  FIXTURES_SETUP "cmake_fetch_content2" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_fetch_content2/CMakeLists.txt;2;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_fetch_content2/CMakeLists.txt;0;")
add_test(cmake_fetch_content2_build "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake" "--build" ".")
set_tests_properties(cmake_fetch_content2_build PROPERTIES  FIXTURES_REQUIRED "cmake_fetch_content2" LABELS "git_required;not_reproducible" _BACKTRACE_TRIPLES "/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_fetch_content2/CMakeLists.txt;9;add_test;/Users/matthewjuranek/Project3DSA/cmake-build-debug/_deps/json-src/tests/cmake_fetch_content2/CMakeLists.txt;0;")
