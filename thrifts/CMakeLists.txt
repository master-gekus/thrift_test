cmake_minimum_required(VERSION 3.1)

project(thrifts)

if (NOT THRIFT_COMPILER)
    message(FATAL_ERROR "Thrift compiler not found!")
endif(NOT THRIFT_COMPILER)

set(GENERATED_FILES
    SharedService.cpp
    thrifts_constants.cpp
    thrifts_types.cpp
    SharedService.h
    thrifts_constants.h
    thrifts_types.h
    )

add_custom_command(
    OUTPUT ${GENERATED_FILES}
    COMMAND ${THRIFT_COMPILER} -r -gen cpp:no_skeleton -out ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/thrifts.thrift
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/thrifts.thrift
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/thrifts.thrift
    )

add_library(${PROJECT_NAME} STATIC ${GENERATED_FILES})
target_link_libraries(${PROJECT_NAME} libthrift)
set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR})

