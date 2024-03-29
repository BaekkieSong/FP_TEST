CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT ("temp_project")
MESSAGE (STATUS ${CMAKE_PROJECT_NAME})

CONFIGURE_FILE (version.h.in version.h)

SET (CMAKE_CXX_FLAGS_DEBUG "-O0")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3") #SET ( CMAKE_C_FLAGS_RELEASE "-DCONFIG_RELEASE -O3" )
#SET (CMAKE_EXE_LINKER_FLAGS_DEBUG "-DCONFIG_DEBUG -Wl,-whole-archive")

SET (CMAKE_BUILD_TYPE Release)

#빌드과정 모두출력
SET (CMAKE_VERBOSE_MAKEFILE true)   

SET (SRCS
    main.c
    foo.c
    bar.c
    )
SET (MAIN
    twomain.c
    )
SET (name sharedapp)

ADD_EXECUTABLE (${name} ${MAIN})
#ADD_EXECUTABLE (${name} EXCLUDE_FROM_ALL ${MAIN} ${SH_FILE})
SET (SH_FILE browser)
ADD_LIBRARY (${SH_FILE} SHARED ${SRCS})
ADD_LIBRARY (imported-gl SHARED IMPORTED)
SET_TARGET_PROPERTIES (${imported-gl}
    PROPERTIES 
    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/ligGL.so"
    )

INCLUDE_DIRECTORIES ( #-I  헤더파일 경로
    ${CMAKE_CURRENT_SOURCE_DIR}/bin
    ${CMAKE_CURRENT_SOURCE_DIR}/sup
    ${CMAKE_CURRENT_SOURCE_DIR}
    .
    )
LINK_DIRECTORIES ( #-L
    ${CMAKE_CURRENT_SOURCE_DIR}/sup
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
FIND_LIBRARY (test-gl GL) #와...이게 되네?;;
TARGET_LINK_LIBRARIES (${name}
    ${SH_FILE}
    ${test-gl}
    )
TARGET_INCLUDE_DIRECTORIES (${name} PUBLIC #-I
    ${CMAKE_CURRENT_SOURCE_DIR}/bin
    ${CMAKE_CURRENT_SOURCE_DIR}/sup
    ${CMAKE_CURRENT_SOURCE_DIR}
    .
    )
SET_TARGET_PROPERTIES (${SH_FILE} PROPERTIES
   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/sup/lib${SH_FILE}.so"
   INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}"
    )

MESSAGE (WARNING ${CMAKE_CURRENT_SOURCE_DIR}/sup)

MESSAGE (WARNING ${CMAKE_C_COMPILER})# /usr/bin/cc) #COMPILER 경로 설정

ADD_COMPILE_OPTIONS (
    -std=c++14
    -g    #Debug 심볼 테이블 포함
    -Wall #모든 경로메시지 포함
    )
#SET_TARGET_PROPERTIES (${name} PROPERTIES COMPILE_FLAGS "-std=c++14 -g")
#SET_TARGET_PROPERTIES (${name} PROPERTIES LINK_FLAGS "-L${CMAKE_CURRENT_SOURCE_DIR}/sup")
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

MESSAGE (WARNING ${CMAKE_CURRENT_SOURCE_DIR})
ADD_CUSTOM_TARGET (chrome ALL
    COMMENT "이거나 출력해라 ${CMAKE_CURRENT_SOURCE_DIR}"
    PRE_BUILD
    WORKING_DIRECTORY ./dir
    COMMAND cat prebuild
    DEPENDS sharedapp
    )
ADD_CUSTOM_TARGET (chrome2 ALL
    COMMENT "이거나 출력해라2 ${CMAKE_CURRENT_SOURCE_DIR}"
    PRE_LINK
    WORKING_DIRECTORY ./dir
    COMMAND cat prelink
    DEPENDS sharedapp
    )
ADD_CUSTOM_TARGET (chrome3 ALL
    COMMENT "이거나 출력해라3 ${CMAKE_CURRENT_SOURCE_DIR}"
    POST_BUILD
    WORKING_DIRECTORY ./dir
    COMMAND cat postbuild
    DEPENDS sharedapp
    )
#ADD_DEPENDENCIES (chrome sharedapp)
#ADD_DEFINITIONS( -DMY_DEBUG=1 -D전처리기전달값 ...) #-D


SET (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}) #INSTALL 상대경로 지정
#SET ( RUNTIME_OUTPUT_DIRECTORY ./bin )
#SET ( LIBRARY_OUTPUT_DIRECTORY ./sup )
INSTALL (TARGETS ${name} ${SH_FILE} ${chrome}
    RUNTIME DESTINATION ./bin         #PREFIX를 기준으로 경로 결정됨
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/sup
#ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/static
    )


#외부 프로젝트 가져오기 예시
#add_subdirectory(../far-far-away            # CMakeList가 위치한 source dir
#    ./build/far-far-away-dir    # 빌드 결과물을 배치할 binary dir을 지정
