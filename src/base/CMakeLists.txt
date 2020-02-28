CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT ("std Test")
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

SET (TEST_ETC
    test/etc/str_test.cc
    test/etc/cstring_test.cc
    test/etc/fstream_test.cc
    )

SET (STUDY_MODERN
    test/study/modern/01_core_test.cc
    test/study/modern/02_thread_test.cc
    test/study/modern/03_tostring_test.cc
    )
SET (STUDY_CORE
    test/study/core/01_variant_test.cc
    test/study/core/02_assert_test.cc
    test/study/core/03_algorithm_test.cc
    test/study/core/04_initializelist_test.cc
    )

SET (SRCS
    ../../work_env/GTest/src/test_main.cc
    ${TESTSTRING}
    ${TEST_ETC}
    ${STUDY_MODERN}
    ${STUDY_CORE}
    )

SET (EXENAME
    gtest.exe
    )

#Directory보다 아래!!!!!
ADD_EXECUTABLE(${EXENAME} ${SRCS})

SET (CXX_STANDARD 17)

if (${CXX_STANDARD} MATCHES 11) #CMAKE_VERSION VERSION_LESS "3.1")
  ADD_DEFINITIONS(-std=c++11)
else()
  ADD_DEFINITIONS(-std=c++17)
  ADD_DEFINITIONS(-DSTD_VERSION17)
#  SET(CMAKE_CXX_STANDARD 17)           //not applied...why?
#  SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#  SET(CMAKE_CXX_EXTENSIONS OFF)
endif()

ADD_COMPILE_OPTIONS (
#    -std=c++14
#    -g    #Debug 심볼 테이블 포함
#    -Wall #모든 경로메시지 포함
    )

#FIND_LIBRARY (gtest-lib gtest)
TARGET_LINK_LIBRARIES (${EXENAME}
    gtest
    gtest_main
    pthread
    )

add_custom_target(clean-all
#    COMMAND ${CMAKE_COMAND} clean
    COMMAND rm -r CMakeCache.txt Makefile CMakeFiles *.cmake gtest.exe 
    )
