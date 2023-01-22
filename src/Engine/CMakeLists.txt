

add_library(engine Engine.h Engine.cpp)

if(WIN32)
	target_link_libraries(engine io window graphics)
endif()

if(NOT EMSCRIPTEN AND UNIX)
	target_link_libraries(engine io window graphics GL GLU glut GLEW -lpthread -lSDL2)
endif()

if(EMSCRIPTEN)
	target_link_libraries(engine io window graphics GL GLU glut GLEW)
endif()