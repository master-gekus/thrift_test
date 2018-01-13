cmake_minimum_required(VERSION 3.1)

project(libthrift)

if (MSVC)
    set(_mdtype "md")
    set(_no_compiler -DBUILD_COMPILER=OFF)
endif()

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(_postfix "d")
endif()

if(NOT WIN32)
    include(FindFLEX)
    if(FLEX_VERSION VERSION_LESS 2.5)
        message(FATAL_ERROR "FLEX version invalid. "
            "Building of thrift-compiler requires FLEX version 2.5 or greater"
            "(found version: ${FLEX_VERSION}).")
    endif()

    include(FindBISON)
    if(BISON_VERSION VERSION_LESS 3.0)
        message(FATAL_ERROR "BISON version invalid. "
            "Building of thrift-compiler requires BISON version 3.0 or greater "
            "(found version: ${BISON_VERSION}).")
    endif()
endif(NOT WIN32)

include(ExternalProject)

ExternalProject_Add(thrift_project
    GIT_REPOSITORY https://git-wip-us.apache.org/repos/asf/thrift.git
    UPDATE_DISCONNECTED 1
    GIT_SHALLOW 1
    CMAKE_ARGS
    ${_no_compiler}
    -DCMAKE_BUILD_TYPE=$<CONFIG>
    -DBUILD_TESTING=OFF
    -DBUILD_TUTORIALS=OFF
    -DBUILD_EXAMPLES=OFF
    -DBUILD_PYTHON=OFF
    -DWITH_SHARED_LIB=OFF
    -DWITH_STATIC_LIB=ON
    -DWITH_C_GLIB=OFF
    -DWITH_JAVA=OFF
    -DWITH_PYTHON=OFF
    -DWITH_QT4=OFF
    -DWITH_QT5=OFF
    -DWITH_ZLIB=OFF
    -DWITH_STDTHREADS=ON
    -DWITH_LIBEVENT=OFF
    -DWITH_OPENSSL=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    INSTALL_COMMAND ""
    )

ExternalProject_Get_Property(thrift_project SOURCE_DIR)
set(THRIFT_INCLUDE_DIRS ${SOURCE_DIR}/lib/cpp/src)

ExternalProject_Get_Property(thrift_project BINARY_DIR)
set(THRIFT_LIBS_DIR ${BINARY_DIR}/lib)

file(MAKE_DIRECTORY ${THRIFT_INCLUDE_DIRS})
add_library(${PROJECT_NAME} STATIC IMPORTED GLOBAL)
add_dependencies(${PROJECT_NAME} thrift_project)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES
    ${THRIFT_INCLUDE_DIRS}
    IMPORTED_LOCATION
    ${THRIFT_LIBS_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}thrift${_mdtype}${_postfix}${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BINARY_DIR})

if (MSVC)
    set(THRIFT_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/thrift-0.11.0.exe PARENT_SCOPE)
else(MSVC)
    set(THRIFT_COMPILER ${BINARY_DIR}/compiler/cpp/bin/thrift PARENT_SCOPE)
endif(MSVC)

