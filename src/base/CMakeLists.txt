CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT ("std Test")
MESSAGE (STATUS ${CMAKE_PROJECT_NAME})

#Notice: Check googletest/googletest path
SET (USER /root)
SET (GTEST_DIR ${USER}/googletest/googletest)
MESSAGE (Warning "Check googletest path: " + ${GTEST_DIR})

SET (CMAKE_CXX_FLAGS_DEBUG "-O0")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")

SET (CMAKE_BUILD_TYPE Debug)

#빌드과정 모두출력
SET (CMAKE_VERBOSE_MAKEFILE true)

SET (TESTSTRING
    test/str_test.cc
    )

SET (SRCS
#    src/str_main.cc
#    ${EXAMPLES}
    ../../work_env/GTest/src/test_main.cc
    ${TESTSTRING}
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

#Directory보다 아래!!!!!
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
    )

#add_test(${EXENAME} ${EXENAME})
MESSAGE (WARNING ${GTEST_DIR}/build/lib/gtest)
MESSAGE (WARNING ${CMAKE_C_COMPILER})# /usr/bin/cc) #COMPILER 경로 설정
MESSAGE (WARNING ${CMAKE_SOURCE_DIR})

add_custom_target(clean-all
#    COMMAND ${CMAKE_COMAND} clean
    COMMAND rm -r CMakeCache.txt Makefile CMakeFiles *.cmake gtest.exe 
    )
