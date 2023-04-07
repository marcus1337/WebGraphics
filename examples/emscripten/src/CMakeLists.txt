cmake_minimum_required(VERSION 3.17.4)

project(Simple_App)
set(CMAKE_CXX_STANDARD 20)

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --bind --embed-file res -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_FREETYPE=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -Wno-unused-command-line-argument")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/../../../" "${CMAKE_CURRENT_BINARY_DIR}/anilib")
include_directories("${PROJECT_SOURCE_DIR}/../../../")

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE AniLib)

####Copy resources folder to target solution directory.
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/../res)
endif(WIN32)
#####
