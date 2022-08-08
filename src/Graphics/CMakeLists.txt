add_library(graphics "Objects/ImageObject.cpp" "Shaders/Shader.cpp" "Objects/TextObject.cpp" "Objects/ImageObject.h" "Shaders/Shader.h" "Objects/TextObject.h" "FrameBuffer.cpp" "FrameBuffer.h"  "GlyphTextureCreator.h" "GlyphTextureCreator.cpp" "Shaders/ImageShader.h" "Shaders/ImageShader.cpp" "Shaders/TextShader.h" "Shaders/TextShader.cpp" "Objects/VertexObject.h" "Objects/VertexObject.cpp")

set(FREETYPE_LIB "")
if(UNIX)
	set(FREETYPE_LIB "freetype")
endif(UNIX)

target_link_libraries(graphics io window utility ${FREETYPE_LIB})