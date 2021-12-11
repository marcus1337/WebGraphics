
add_library(io Files/IOStuff.cpp Files/IOStuff.h Files/IOShader.cpp Files/IOShader.h 
Files/IOTexture.h Files/IOTexture.cpp Files/lodepng.cpp Files/lodepng.h Files/TextureData.h Files/ShaderData.h
Controller/Mouse.h Controller/Mouse.cpp Controller/Keyboard.h Controller/Keyboard.cpp )

target_link_libraries(io utility)
