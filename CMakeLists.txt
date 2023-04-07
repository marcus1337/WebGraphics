cmake_minimum_required(VERSION 3.17.4)

if(WIN32)
    set(VCPKG_PATH "C:/Users/Maccc/Documents/Coding/vcpkg/scripts/buildsystems") # <----- insert your own path to "VCPKG" here.
    include("${VCPKG_PATH}/vcpkg.cmake")
endif()

project(AniLib)
set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)
list(APPEND INCLUDE_DIRS ${GLM_INCLUDE_DIRS})

if(EMSCRIPTEN)
    #--embed-file res
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --bind -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_FREETYPE=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -Wno-unused-command-line-argument") #Debug-flags (causes problems for external users): -g -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1
endif(EMSCRIPTEN)

if(NOT EMSCRIPTEN)
    FIND_PACKAGE(SDL2 REQUIRED)
    FIND_PACKAGE(OpenGL REQUIRED)
    FIND_PACKAGE(GLEW REQUIRED)
    FIND_PACKAGE(Freetype REQUIRED)
    FIND_PACKAGE(glfw3 REQUIRED)
    FIND_PACKAGE(GLUT REQUIRED)

    list(APPEND INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
    list(APPEND INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
    list(APPEND INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS})
    list(APPEND INCLUDE_DIRS ${GLUT_INCLUDE_DIRS})

    list(APPEND LINK_LIBS ${SDL2_LIBRARIES})
    list(APPEND LINK_LIBS ${OPENGL_LIBRARIES} OpenGL::GL)
    list(APPEND LINK_LIBS ${GLEW_LIBRARIES})
    list(APPEND LINK_LIBS ${FREETYPE_LIBRARIES})
    list(APPEND LINK_LIBS glfw)
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

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(${PROJECT_NAME} STATIC 

"src/Drawables/Drawable.cpp"
"src/Drawables/Image.cpp"
"src/Drawables/Text.cpp"
"src/Drawables/Line.cpp"
"src/Drawables/Rect.cpp"
"src/Drawables/View.cpp"

"src/Engine/Looper.cpp"
"src/Engine/Engine.cpp"
"src/Engine/Resources.cpp"

"src/Graphics/MainView.cpp"
"src/Graphics/Graphics.cpp"
"src/Graphics/GlyphTextureCreator.cpp"
"src/Graphics/FrameBuffer.cpp"
"src/Graphics/Objects/ImageObject.cpp"
"src/Graphics/Objects/TextObject.cpp"
"src/Graphics/Objects/VertexObject.cpp"
"src/Graphics/Objects/ObjectContainer.cpp"
"src/Graphics/Shaders/ImageShader.cpp"
"src/Graphics/Shaders/Shader.cpp"
"src/Graphics/Shaders/TextShader.cpp"

"src/IO/Files/IOFonts.cpp"
"src/IO/Files/IOContainer.cpp"
"src/IO/Files/Path/FilePath.cpp"
"src/IO/Files/Path/FilePathContainer.cpp"
"src/IO/Files/Shader/DefaultShaderCode.cpp"
"src/IO/Files/Shader/IOShader.cpp"
"src/IO/Files/Shader/ShaderCompiler.cpp"

"src/IO/Files/Texture/IOTexture.cpp"
"src/IO/Files/Texture/lodepng.cpp"

"src/Window/Canvas.cpp"
"src/Window/CanvasCallbacks.cpp"
"src/Window/CanvasSettings.cpp"

"src/Window/InputDevices/Keyboard.cpp"
"src/Window/InputDevices/Mouse.cpp"

)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBS})

