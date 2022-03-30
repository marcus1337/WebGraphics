add_library(graphics ImageObject.cpp Shader.cpp TextObject.cpp ImageObject.h Shader.h TextObject.h "FrameBuffer.cpp" "FrameBuffer.h" )

target_link_libraries(graphics io window utility)