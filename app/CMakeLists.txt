#################################
#  RobustPalmRoi library cmake  #
#################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(LIBRARY_NAME robust_palm_roi)
PROJECT(${LIBRARY_NAME})
SET(PROJECT_ROOT ${CMAKE_BINARY_DIR}/..)

FIND_PACKAGE(OpenCV REQUIRED)

IF(${CMAKE_BUILD_TEST})
  SET(GCC_COVERAGE_COMPILE_FLAGS "-ggdb -coverage -fprofile-arcs -ftest-coverage")
  SET(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
ENDIF()
SET(CMAKE_CXX_FLAGS  "--std=c++11 ${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Download and unpack yaml-cpp at configure time
CONFIGURE_FILE(${PROJECT_ROOT}/thirdparty/yaml-cpp/CMakeLists.txt.in
  ${CMAKE_BINARY_DIR}/yaml-cpp-download/CMakeLists.txt)
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/yaml-cpp-download )
IF(result)
  MESSAGE(FATAL_ERROR "CMake step for yaml-cpp failed: ${result}")
ENDIF()
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/yaml-cpp-download )
IF(result)
  MESSAGE(FATAL_ERROR "Build step for yaml-cpp failed: ${result}")
ENDIF()

SET(APP_ROOT ${PROJECT_SOURCE_DIR})
SET(THIRDPARTY_ROOT ${PROJECT_ROOT}/thirdparty)

SET(BUILD_SHARED_LIBS ON CACHE BOOL "build yaml shared lib")
SET(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
SET(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
SET(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")
ADD_SUBDIRECTORY(${CMAKE_BINARY_DIR}/yaml-cpp-src
  ${CMAKE_BINARY_DIR}/yaml-cpp-build
  EXCLUDE_FROM_ALL)

INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_BINARY_DIR}/yaml-cpp-build/include")
INCLUDE_DIRECTORIES(${APP_ROOT})

FILE(GLOB_RECURSE SRC_FILES *.c *.cc *.cpp)
FILE(GLOB_RECURSE HEADER_FILES *.h *.hpp)

SET(LIBRARIES
  ${OpenCV_LIBS}
  yaml-cpp)

ADD_LIBRARY(${LIBRARY_NAME} SHARED ${HEADER_FILES} ${SRC_FILES})
TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${LIBRARIES})
