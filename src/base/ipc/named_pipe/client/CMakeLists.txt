CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT ("base_project")
MESSAGE (STATUS ${CMAKE_PROJECT_NAME})

SET (CMAKE_CXX_FLAGS_DEBUG "-O0")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")

SET (CMAKE_BUILD_TYPE Debug)

#빌드과정 모두출력
SET (CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_BUILD_DIRECTORY ${CMAKE_CURRENT_DIR}/build)

SET (SRCS
    named_pipe_client.cc
    )
SET (EXENAME
    process.exe
    )

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/..
    )
#LINK_DIRECTORIES (
#    /usr/lib
#    /system/lib/x86_64-linux-gnu/
#    )

ADD_EXECUTABLE(${EXENAME} ${SRCS})

#clang++ -std=c++14 -g -Wall -pthread thread.cc -o out
ADD_COMPILE_OPTIONS (
    -std=c++14
#    -pthread
    -g    #Debug 심볼 테이블 포함
    -Wall #모든 경로메시지 포함
    )

#얘는 반드시 실행파일보다 밑에 정의되어야 함!
TARGET_LINK_LIBRARIES (${EXENAME}
    pthread
    )

MESSAGE (WARNING ${CMAKE_C_COMPILER})# /usr/bin/cc) #COMPILER 경로 설정
MESSAGE (WARNING ${CMAKE_CURRENT_SOURCE_DIR})
