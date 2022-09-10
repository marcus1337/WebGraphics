file(GLOB soloud_SRC
     "Audio/soloud/*.h"
     "Audio/soloud/*.cpp"
	 "Audio/soloud/audiosource/speech/*.h"
     "Audio/soloud/audiosource/speech/*.cpp"
	 "Audio/soloud/audiosource/wav/*.h"
     "Audio/soloud/audiosource/wav/*.cpp"
	 "Audio/soloud/audiosource/wav/*.c"
	 "Audio/soloud/filter/*.h"
     "Audio/soloud/filter/*.cpp"
)

add_library(engine Engine.h Engine.cpp "Graphics.h" "Graphics.cpp" "AspectRatio.h" "AspectRatio.cpp"  "Audio/Audio.h" "Audio/Audio.cpp" 
${soloud_SRC})

if(WIN32)
	target_link_libraries(engine io window utility graphics)
endif()

if(NOT WIN32)
	target_link_libraries(engine io window utility graphics GL GLU glut GLEW -lpthread -lSDL2)
endif()
