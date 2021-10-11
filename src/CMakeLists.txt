cmake_minimum_required(VERSION 3.17.4)

project(AniLib)

set(CMAKE_CXX_STANDARD 20)


if(EMSCRIPTEN)
    message("COMPILING WITH EMSCRIPTEN")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --bind --embed-file res -s USE_FREETYPE=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1")
endif(EMSCRIPTEN)


if(UNIX)
    if(NOT EMSCRIPTEN)
        message(STATUS "GCC detected, adding compile flags")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-error=invalid-offsetof -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder -lstdc++fs -std=c++2a -lfreetype")
        set(CMAKE_CXX_FLAGS_DEBUG "-g")
        set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

        FIND_PACKAGE(OpenGL REQUIRED)
        list(APPEND EXTRA_LINK_DIRS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} OpenGL::GL)

        find_package(GLEW REQUIRED)
        list(APPEND EXTRA_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
        list(APPEND EXTRA_LINK_DIRS ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

        find_package(Freetype REQUIRED)
        list(APPEND EXTRA_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS})
        list(APPEND EXTRA_LINK_DIRS ${FREETYPE_LIBRARIES})
        include_directories (/usr/include/freetype2)
    endif(NOT EMSCRIPTEN)

endif(UNIX)

add_executable(${PROJECT_NAME} Main.cpp App.cpp )

add_subdirectory("${PROJECT_SOURCE_DIR}/../external/glm" "${CMAKE_CURRENT_BINARY_DIR}/external/glm")
list(APPEND EXTRA_INCLUDE_DIRS "external/glm")
list(APPEND EXTRA_LINK_DIRS glm)

if(NOT EMSCRIPTEN)
    add_subdirectory("${PROJECT_SOURCE_DIR}/../external/glfw" "${CMAKE_CURRENT_BINARY_DIR}/external/glfw")
    list(APPEND EXTRA_INCLUDE_DIRS "external/glfw/include")
    list(APPEND EXTRA_LIB_DIRS "external/glfw/src")
    list(APPEND EXTRA_LINK_DIRS glfw)
endif(NOT EMSCRIPTEN)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/../external/include")

add_subdirectory(Utility)
list(APPEND EXTRA_LIB_DIRS "Utility")
list(APPEND EXTRA_INCLUDE_DIRS "Utility")
list(APPEND EXTRA_LINK_DIRS utility)

add_subdirectory(Window)
list(APPEND EXTRA_LIB_DIRS "Window")
list(APPEND EXTRA_INCLUDE_DIRS "Window")
list(APPEND EXTRA_LINK_DIRS window)

add_subdirectory(IO)
list(APPEND EXTRA_LIB_DIRS "IO")
list(APPEND EXTRA_INCLUDE_DIRS "IO")
list(APPEND EXTRA_LINK_DIRS io)

add_subdirectory(Model)
list(APPEND EXTRA_LIB_DIRS "Model")
list(APPEND EXTRA_INCLUDE_DIRS "Model")
list(APPEND EXTRA_LINK_DIRS model)


target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${EXTRA_LIB_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LINK_DIRS})


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/../res)
endif(WIN32)