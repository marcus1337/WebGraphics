

add_library(io
"Files/Shader/IOShader.cpp" "Files/Shader/IOShader.h" 
"Files/Texture/IOTexture.h" "Files/Texture/IOTexture.cpp" 
Files/IOFonts.h Files/IOFonts.cpp 
"Files/Texture/lodepng.cpp" "Files/Texture/lodepng.h"  
  
"Files/IOLogs.h" "Files/IOLogs.cpp"     "Files/Path/FilePathContainer.h" 
"Files/Path/FilePathContainer.cpp" "Files/Path/FilePath.h" "Files/Path/FilePath.cpp" 
"Files/IOContainer.h" "Files/Shader/ShaderCode.h"
"Files/Shader/ShaderCompiler.h" "Files/Shader/ShaderCompiler.cpp" 
 "Files/Shader/DefaultShaderCode.h" "Files/Shader/DefaultShaderCode.cpp")

include_directories("${PROJECT_SOURCE_DIR}/IO/Bitsery")
add_subdirectory(Bitsery)

target_link_libraries(io bitsery glm glfw)
