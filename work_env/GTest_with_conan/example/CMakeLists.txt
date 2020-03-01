CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT ("FP_project")
MESSAGE (STATUS ${CMAKE_PROJECT_NAME})

SET (CMAKE_CXX_FLAGS_DEBUG "-O0")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")

SET (CMAKE_BUILD_TYPE Debug)

#빌드과정 모두출력
SET (CMAKE_VERBOSE_MAKEFILE true)


######FOR 4CH START
SET (SRCS
    bind2nd.cc
    )
SET (EXENAME
    ch4exe
    )
######FOR 4CH END

ADD_EXECUTABLE(${EXENAME} ${SRCS})

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/..
    )


######FOR GTEST START
INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

ADD_EXECUTABLE(testexe gtest_main.cc)

TARGET_LINK_LIBRARIES(testexe
    gtest
    gtest_main
    pthread
    )
######FOR GTEST END

ADD_COMPILE_OPTIONS (
    -std=c++14
    -g    #Debug 심볼 테이블 포함
    -Wall #모든 경로메시지 포함
    )

MESSAGE (WARNING ${CMAKE_C_COMPILER})# /usr/bin/cc) #COMPILER 경로 설정
MESSAGE (WARNING ${CMAKE_CURRENT_SOURCE_DIR})
