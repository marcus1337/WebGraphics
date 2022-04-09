cmake_minimum_required(VERSION 3.17.4)

if(NOT EMSCRIPTEN AND WIN32)
    #set(CMAKE_CXX_COMPILER 20)
    #set(VCPKG_TARGET_TRIPLET x64-windows)
    include("C:/Users/Maccc/Documents/Coding/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(AniLib)
set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} Main.cpp App.cpp App.h)

if(EMSCRIPTEN)
    message("COMPILING WITH EMSCRIPTEN")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --bind --embed-file res -s USE_FREETYPE=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -Wno-unused-command-line-argument")
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

        #include_directories(${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    endif(NOT EMSCRIPTEN)

endif(UNIX)

add_subdirectory("${PROJECT_SOURCE_DIR}/../external/glm" "${CMAKE_CURRENT_BINARY_DIR}/external/glm")
list(APPEND EXTRA_INCLUDE_DIRS "external/glm")
list(APPEND EXTRA_LINK_DIRS glm)


if(NOT EMSCRIPTEN AND WIN32)
    find_package(OpenGL REQUIRED)
    list(APPEND EXTRA_LINK_DIRS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} OpenGL::GL)

    find_package(GLEW REQUIRED)
    list(APPEND EXTRA_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
    list(APPEND EXTRA_LINK_DIRS ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

    find_package(glfw3 REQUIRED)
    list(APPEND EXTRA_LINK_DIRS glfw)

    find_package(Freetype REQUIRED)
    list(APPEND EXTRA_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS})
    list(APPEND EXTRA_LINK_DIRS ${FREETYPE_LIBRARIES})

    include_directories(${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif()

include_directories("${PROJECT_SOURCE_DIR}")
include_directories(include)

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

add_subdirectory(Graphics)
list(APPEND EXTRA_LIB_DIRS "Graphics")
list(APPEND EXTRA_INCLUDE_DIRS "Graphics")
list(APPEND EXTRA_LINK_DIRS graphics)

add_subdirectory(Drawables)
list(APPEND EXTRA_LIB_DIRS "Drawables")
list(APPEND EXTRA_INCLUDE_DIRS "Drawables")
list(APPEND EXTRA_LINK_DIRS drawables)

add_subdirectory(Engine)
list(APPEND EXTRA_LIB_DIRS "Engine")
list(APPEND EXTRA_INCLUDE_DIRS "Engine")
list(APPEND EXTRA_LINK_DIRS engine)


target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${EXTRA_LIB_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LINK_DIRS})


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/../res)
endif(WIN32)