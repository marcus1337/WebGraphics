
add_library(io IOStuff.cpp IOStuff.h IOShader.cpp IOShader.h IOTexture.h IOTexture.cpp lodepng.cpp lodepng.h TextureData.h ShaderData.h)

target_link_libraries(io utility)
