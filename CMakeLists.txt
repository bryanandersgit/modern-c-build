# CMakeLists.txt - Modern C Project Template
cmake_minimum_required(VERSION 3.20)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE) # automatic vcpktg
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message(STATUS "Using vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif()

project(ModernCBuild
    VERSION 1.0.0 # set these vars, step 1 of cmake project discovery
    DESCRIPTION "Modern C Build Exploration"
    LANGUAGES C)


find_package(cJSON CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)

# Set C standard
set(CMAKE_C_STANDARD 17) # parsing sets is step 2 of cmake project discovery
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Compiler-specific flags
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    # common warnings, extra warnings, non-standard c features warnings, string format checking, warning about inplicit type conversions
    add_compile_options(-Wall -Wextra -Wpedantic -Wformat=2 -Wconversion)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    # Wall is _all_ warnings, Wno-padded disabled padding warnings
    add_compile_options(-Wall -Wextra -Wpedantic -Weverything -Wno-padded)
endif()

# Debug/Release configurations
# include debugging symbols, no optimization, define debug macro
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
# maximum optimization, disables assert macros
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Create directories
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Example 1: Simple executable
add_executable(hello_modern src/hello_modern.c) # add executable and add library are step 3 of cmake project discovery

# Example 2: Executable with multiple sources
add_executable(calculator 
    src/calculator.c 
    src/math_utils.c)
# create an include/ dir for calculator only used by calculator
target_include_directories(calculator PRIVATE include) # duplicate imports in TargetDirectory.txt caused by duplicate includes in these statements

target_link_libraries(calculator PRIVATE
        cjson
        CURL::libcurl
        SQLite::SQLite3
)

# Example 3: Static library
add_library(myutils STATIC # creates a static library (.a file in linux, .lib on windows)
    src/string_utils.c
    src/file_utils.c
    src/math_utils.c)
# creates an include path that is included for any target that links myutils
target_include_directories(myutils PUBLIC include)

# Example 4: Executable using the library
add_executable(demo src/demo.c)
target_link_libraries(demo myutils) # links myutils library to demos executable, which passes on the public includes
target_include_directories(demo PRIVATE include)

# Enable testing
enable_testing() # dnables CMake's testing framework

# Enable dashboard scripting (creates DartConfiguration.tcl)
include(CTest)

# Add test executable
add_executable(tests test/test_runner.c)
target_link_libraries(tests myutils)
target_include_directories(tests PRIVATE include)

# Register test
add_test(NAME unit_tests COMMAND tests) # registers the tests executable as unit_tests

# Install targets
install(TARGETS hello_modern calculator demo DESTINATION bin) # executables go in bin
install(TARGETS myutils DESTINATION lib) # libraries go in lib
install(DIRECTORY include/ DESTINATION include) # headers on in include

# CPack configuration for packaging
set(CPACK_GENERATOR "TGZ") # creates a tar.gz
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
include(CPack)
