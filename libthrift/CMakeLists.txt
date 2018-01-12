cmake_minimum_required(VERSION 3.1)

project(libthrift)

include(ExternalProject)
ExternalProject_Add(thrift_project
    GIT_REPOSITORY https://git-wip-us.apache.org/repos/asf/thrift.git
    UPDATE_DISCONNECTED 1
    GIT_SHALLOW 1
    CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=$<CONFIG>
    -DBUILD_COMPILER=OFF
    -DBUILD_TESTING=OFF
    -DBUILD_TUTORIALS=OFF
    -DBUILD_EXAMPLES=OFF
    -DBUILD_PYTHON=OFF
    -DWITH_SHARED_LIB=OFF
    -DWITH_STATIC_LIB=ON
    -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    )

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(${PROJECT_NAME} STATIC IMPORTED GLOBAL)
add_dependencies(${PROJECT_NAME} thrift_project)
set_target_properties(${PROJECT_NAME} PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/lib/thriftmdd.lib
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/include
    )
