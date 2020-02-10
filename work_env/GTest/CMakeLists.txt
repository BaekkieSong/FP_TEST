CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT ("GTestTest")
MESSAGE (STATUS ${CMAKE_PROJECT_NAME})

#Notice: Check googletest/googletest path
SET (USER ~/)
SET (GTEST_DIR ${USER}/googletest/googletest)
MESSAGE (Warning "Check googletest path: " + ${GTEST_DIR})

SET (CMAKE_CXX_FLAGS_DEBUG "-O0")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")

SET (CMAKE_BUILD_TYPE Debug)

#빌드과정 모두출력
SET (CMAKE_VERBOSE_MAKEFILE true)

#set(CMAKE_CXX_STANDARD 11)

SET (EXAMPLES
    src/example/case_expect_n_assert.cc
    src/example/case_sum.cc
    )

SET (SRCS
    src/test_main.cc
    ${EXAMPLES}
    )
SET (EXENAME
    gtest.exe
    )

INCLUDE_DIRECTORIES( #헤더만...
    ${CMAKE_SOURCE_DIR}/src
    ${GTEST_DIR}/include
    )
LINK_DIRECTORIES(
    ${GTEST_DIR}/build/lib
    )

ADD_EXECUTABLE(${EXENAME} ${SRCS})

ADD_COMPILE_OPTIONS (
    -std=c++11
    -g    #Debug 심볼 테이블 포함
    -Wall #모든 경로메시지 포함
    )

#FIND_LIBRARY (gtest-lib gtest)
TARGET_LINK_LIBRARIES (${EXENAME}
    gtest
    gtest_main
    pthread
#${GTEST_DIR}/build/lib/gmock
    )
#add_test(${EXENAME} ${EXENAME})
MESSAGE (WARNING ${GTEST_DIR}/build/lib/gtest)
MESSAGE (WARNING ${CMAKE_C_COMPILER})# /usr/bin/cc) #COMPILER 경로 설정
#MESSAGE (WARNING ${CMAKE_CURRENT_SOURCE_DIR})
#MESSAGE (WARNING ${CMAKE_COMMAND}) #cmake
#MESSAGE (WARNING ${CMAKE_BUILD_TOOL}) #gmake
MESSAGE (WARNING ${CMAKE_SOURCE_DIR})

add_custom_target(clean-all
#    COMMAND ${CMAKE_COMAND} clean
    COMMAND rm -r CMakeCache.txt Makefile CMakeFiles *.cmake gtest.exe 
    )
