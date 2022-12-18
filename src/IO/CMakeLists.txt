

add_library(io
Files/IOShader.cpp Files/IOShader.h 
Files/IOTexture.h Files/IOTexture.cpp 
Files/IOFonts.h Files/IOFonts.cpp 
Files/lodepng.cpp Files/lodepng.h  
Files/FolderPaths.h Files/FolderPaths.cpp 
"Files/IOLogs.h" "Files/IOLogs.cpp"   "Files/IOBinary.h" "Files/IOBinary.cpp" "Files/FilePathContainer.h" "Files/FilePathContainer.cpp" "Files/FilePath.h" "Files/FilePath.cpp")

include_directories("${PROJECT_SOURCE_DIR}/IO/Bitsery")
add_subdirectory(Bitsery)

target_link_libraries(io bitsery glm glfw)
