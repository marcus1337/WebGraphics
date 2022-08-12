
add_library(io
Files/IOShader.cpp Files/IOShader.h 
Files/IOTexture.h Files/IOTexture.cpp 
Files/IOFonts.h Files/IOFonts.cpp 
Files/lodepng.cpp Files/lodepng.h Files/TextureData.h Files/ShaderData.h
Files/FolderPaths.h Files/FolderPaths.cpp 
Controller/Mouse.h Controller/Mouse.cpp Controller/Keyboard.h Controller/Keyboard.cpp  
  
"Files/IOLogs.h" "Files/IOLogs.cpp" "Files/FileChecker.h" "Files/FileChecker.cpp")

target_link_libraries(io utility)
