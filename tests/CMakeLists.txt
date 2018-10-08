############################################
#   RobustPalmRoi test cmake configuration #
############################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJECT_NAME robust_palm_roi_test)
PROJECT(${PROJECT_NAME})
SET(PROJECT_ROOT ${CMAKE_BINARY_DIR}/..)

SET(CMAKE_BUILD_TEST "1" CACHE INTERNAL "Is build test" )
IF(${CMAKE_BUILD_TEST})
        SET(GCC_COVERAGE_COMPILE_FLAGS "-ggdb -coverage -fprofile-arcs -ftest-coverage")
        SET(GCC_COVERAGE_LINK_FLAGS    "-coverage")
ENDIF()
SET(CMAKE_CXX_FLAGS  "--std=c++11 ${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Download and unpack googletest at configure time
CONFIGURE_FILE(${PROJECT_ROOT}/thirdparty/gtest/CMakeLists.txt.in googletest-download/CMakeLists.txt)
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
IF(result)
        MESSAGE(FATAL_ERROR "CMake step for googletest failed: ${result}")
ENDIF()
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
IF(result)
        MESSAGE(FATAL_ERROR "Build step for googletest failed: ${result}")
ENDIF()

SET(APP_ROOT ${PROJECT_SOURCE_DIR}/../app)
SET(TEST_ROOT ${PROJECT_SOURCE_DIR})

ADD_SUBDIRECTORY(${APP_ROOT} ${CMAKE_BINARY_DIR}/robust_palm_roi)
ADD_SUBDIRECTORY(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

INCLUDE_DIRECTORIES(${APP_ROOT})
INCLUDE_DIRECTORIES(${TEST_ROOT})
IF(CMAKE_VERSION VERSION_LESS 2.8.11)
        INCLUDE_DIRECTORIES("${gtest_SOURCE_DIR}/include")
ENDIF()

FILE(GLOB_RECURSE SRC_FILES *.c *.cc *.cpp)
FILE(GLOB_RECURSE HEADER_FILES *.h *.hpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${HEADER_FILES} ${SRC_FILES})

SET(LIBRARIES
    robust_palm_roi
    gtest_main)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

EXECUTE_PROCESS(COMMAND ${CMAKE_SOURCE_DIR}/palm_data/download.sh)

ADD_TEST(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
ADD_CUSTOM_TARGET(build_and_test
                COMMAND ${PROJECT_NAME}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
