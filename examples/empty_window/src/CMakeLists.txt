cmake_minimum_required(VERSION 3.17.4)

project(Empty_App)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("${PROJECT_SOURCE_DIR}/../../../" "${CMAKE_CURRENT_BINARY_DIR}/anilib")
include_directories("${PROJECT_SOURCE_DIR}/../../")

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE AniLib)


