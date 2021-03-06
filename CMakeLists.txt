cmake_minimum_required(VERSION 3.5.1)

#set clang as the default compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(powehi)

#set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libraries")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/tools/cmake")
set(CTEST_BINARY_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

#set the standard
set(CMAKE_CXX_STANDARD 14)

# check the operating system and add the appropriate flags
set(CMAKE_CXX_FLAGS "-fPIC -Wno-deprecated-declarations")

# if we are compiling for debug add the debug flags
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# if we are compiling for release
elseif(CMAKE_BUILD_TYPE MATCHES Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
endif()

#set the directories with the common header files
include_directories("${PROJECT_SOURCE_DIR}/benchmark/src/headers")

# specify the source files
file(GLOB SOURCE "${PROJECT_SOURCE_DIR}/benchmark/src/source/*.cc")

#to build the library
add_library(powehi OBJECT ${SOURCE})

#set the testAllocator build target
set(SOURCE_FILES_TEST_ALLOCATOR ${PROJECT_SOURCE_DIR}/tests/TestAllocator.cc $<TARGET_OBJECTS:powehi>)
add_executable(testAllocator ${SOURCE_FILES_TEST_ALLOCATOR})

set(SOURCE_FILES_TEST_CREATION ${PROJECT_SOURCE_DIR}/tests/TestTensorCreation.cc $<TARGET_OBJECTS:powehi>)
add_executable(testCreation ${SOURCE_FILES_TEST_CREATION})

set(SOURCE_FILES_TEST_GRADIENTS ${PROJECT_SOURCE_DIR}/tests/TestGradientsCreation.cc $<TARGET_OBJECTS:powehi>)
add_executable(testGradients ${SOURCE_FILES_TEST_GRADIENTS})

set(SOURCE_FILES_TEST_OPT_GRADIENTS ${PROJECT_SOURCE_DIR}/tests/TestOptimizedGradientsCreation.cc $<TARGET_OBJECTS:powehi>)
add_executable(testOptGradients ${SOURCE_FILES_TEST_OPT_GRADIENTS})

set(SOURCE_FILES_TEST_INTEGRATED ${PROJECT_SOURCE_DIR}/tests/Test.cc $<TARGET_OBJECTS:powehi>)
add_executable(testIntegrated ${SOURCE_FILES_TEST_INTEGRATED})

set(SOURCE_FILES_TEST_SPARSE ${PROJECT_SOURCE_DIR}/tests/TestSparseTensorCreation.cc $<TARGET_OBJECTS:powehi>)
add_executable(testSparse ${SOURCE_FILES_TEST_SPARSE})
