cmake_minimum_required(VERSION 3.17.4)

if(WIN32)
    set(VCPKG_PATH "C:/Users/Maccc/Documents/Coding/vcpkg/scripts/buildsystems") # <----- insert your own path to "VCPKG" here.
    include("${VCPKG_PATH}/vcpkg.cmake")
endif()

project(AniLib)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("${PROJECT_SOURCE_DIR}/../external/glm" "${CMAKE_CURRENT_BINARY_DIR}/external/glm")
list(APPEND INCLUDE_DIRS "external/glm")
list(APPEND LINK_LIBS glm)

if(EMSCRIPTEN)
    #--embed-file res
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --bind -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_FREETYPE=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -Wno-unused-command-line-argument") #Debug-flags (causes problems for external users): -g -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1
endif(EMSCRIPTEN)
if(NOT EMSCRIPTEN)
    FIND_PACKAGE(SDL2 REQUIRED)
    list(APPEND INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
    list(APPEND LINK_LIBS ${SDL2_LIBRARIES})

    FIND_PACKAGE(OpenGL REQUIRED)
    list(APPEND LINK_LIBS ${OPENGL_LIBRARIES} OpenGL::GL)

    find_package(GLEW REQUIRED)
    list(APPEND INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
    list(APPEND LINK_LIBS ${GLEW_LIBRARIES})

    find_package(Freetype REQUIRED)
    list(APPEND INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS})
    list(APPEND LINK_LIBS ${FREETYPE_LIBRARIES})

    find_package(glfw3 REQUIRED)
    list(APPEND LINK_LIBS glfw)

    find_package(GLUT REQUIRED)
    list(APPEND INCLUDE_DIRS ${GLUT_INCLUDE_DIRS})
    list(APPEND LINK_LIBS ${GLUT_LIBRARIES})

    include_directories(${FREETYPE_INCLUDE_DIRS})
endif()

if(NOT EMSCRIPTEN AND UNIX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-error=unused-value -Wno-error=misleading-indentation -Wno-error=invalid-offsetof -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder -lstdc++fs -std=c++2a -lfreetype")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
    include_directories (/usr/include/freetype2) # <--- download freetype2 with a package manager
endif()

include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(Audio)
list(APPEND LIB_DIRS "Audio")
list(APPEND INCLUDE_DIRS "Audio")
list(APPEND LINK_LIBS audio)

add_subdirectory(IO)
list(APPEND LIB_DIRS "IO")
list(APPEND INCLUDE_DIRS "IO")
list(APPEND LINK_LIBS io)

add_subdirectory(Window)
list(APPEND LIB_DIRS "Window")
list(APPEND INCLUDE_DIRS "Window")
list(APPEND LINK_LIBS window)

add_subdirectory(Graphics)
list(APPEND LIB_DIRS "Graphics")
list(APPEND INCLUDE_DIRS "Graphics")
list(APPEND LINK_LIBS graphics)

add_subdirectory(Drawables)
list(APPEND LIB_DIRS "Drawables")
list(APPEND INCLUDE_DIRS "Drawables")
list(APPEND LINK_LIBS drawables)

add_subdirectory(UI)
list(APPEND LIB_DIRS "UI")
list(APPEND INCLUDE_DIRS "UI")
list(APPEND LINK_LIBS ui)

add_subdirectory(Engine)
list(APPEND LIB_DIRS "Engine")
list(APPEND INCLUDE_DIRS "Engine")
list(APPEND LINK_LIBS engine)

add_subdirectory(Game)
list(APPEND LIB_DIRS "Game")
list(APPEND INCLUDE_DIRS "Game")
list(APPEND LINK_LIBS game)

add_subdirectory(App)
list(APPEND LIB_DIRS "App")
list(APPEND INCLUDE_DIRS "App")
list(APPEND LINK_LIBS app)

add_executable(${PROJECT_NAME} "main.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBS})


####### vvvv these should be deleted once directory paths are inserted via code or arguments vvvvv
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/../res)
endif(WIN32)
