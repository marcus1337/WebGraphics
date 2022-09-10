add_library(engine Engine.h Engine.cpp "Graphics.h" "Graphics.cpp" "AspectRatio.h" "AspectRatio.cpp"  "Audio/Audio.h" "Audio/Audio.cpp")

if(WIN32)
	target_link_libraries(engine io window utility graphics)
endif()

if(NOT WIN32)
	target_link_libraries(engine io window utility graphics GL GLU glut GLEW)
endif()
