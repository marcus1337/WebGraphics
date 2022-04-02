add_library(graphics ImageObject.cpp Shader.cpp TextObject.cpp ImageObject.h Shader.h TextObject.h "FrameBuffer.cpp" "FrameBuffer.h" )

set(FREETYPE_LIB "")
if(UNIX)
	set(FREETYPE_LIB "freetype")
endif(UNIX)

target_link_libraries(graphics io window utility ${FREETYPE_LIB})