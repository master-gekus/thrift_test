cmake_minimum_required(VERSION 3.1)

project(thrift_test_server)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} libthrift thrifts)
