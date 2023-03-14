

add_library(io
"Files/Shader/IOShader.cpp" "Files/Shader/IOShader.h" 
"Files/Texture/IOTexture.h" "Files/Texture/IOTexture.cpp" 
Files/IOFonts.h Files/IOFonts.cpp 
"Files/Texture/lodepng.cpp" "Files/Texture/lodepng.h"  
  
"Files/Path/FilePathContainer.h" 
"Files/Path/FilePathContainer.cpp" "Files/Path/FilePath.h" "Files/Path/FilePath.cpp" 
"Files/IOContainer.h" "Files/Shader/ShaderCode.h"
"Files/Shader/ShaderCompiler.h" "Files/Shader/ShaderCompiler.cpp" 
 "Files/Shader/DefaultShaderCode.h" "Files/Shader/DefaultShaderCode.cpp")

target_link_libraries(io glm glfw)
