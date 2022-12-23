

add_library(engine Engine.h Engine.cpp)

if(WIN32)
	target_link_libraries(engine io window graphics audio)
endif()

if(NOT EMSCRIPTEN AND UNIX)
	target_link_libraries(engine io window graphics GL GLU glut GLEW -lpthread -lSDL2 audio)
endif()

if(EMSCRIPTEN)
	target_link_libraries(engine io window graphics GL GLU glut GLEW audio)
endif()