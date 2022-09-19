

add_library(engine Engine.h Engine.cpp "Graphics.h" "Graphics.cpp" "AspectRatio.h" "AspectRatio.cpp")

if(WIN32)
	target_link_libraries(engine io window utility graphics audio)
endif()

if(NOT EMSCRIPTEN AND UNIX)
	target_link_libraries(engine io window utility graphics GL GLU glut GLEW -lpthread -lSDL2 audio)
endif()

if(EMSCRIPTEN)
	target_link_libraries(engine io window utility graphics GL GLU glut GLEW audio)
endif()